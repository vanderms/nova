import chokidar from "chokidar";
import fs from "fs";
import { File } from "./file.js";
import { Namespace } from "./namespace.js";
import { ImportsHandler } from "./imports.js";
import { ExportsHandler } from "./exports.js";

class Parser {
  static run() {
    const parser = new Parser();
    chokidar
      .watch("./src/**/*.component.h")
      .on("add", (path) => parser.onUpdate(path))
      .on("change", (path) => parser.onUpdate(path));
  }

  onUpdate(path) {
    this.setVariables(path);

    ExportsHandler.updateModule(this.files, this.data, this.namespace);
    ImportsHandler.updateModule(this.files, this.data);

    this.addHeaders();

    const annotations = this.findAnnotations();

    annotations.forEach((annotation) => {
      if (
        annotation.directive === "import" ||
        annotation.directive === "type"
      ) {
        ImportsHandler.handleImport(annotation);
      } else {
        ExportsHandler.handleExports(annotation);
      }
    });

    ImportsHandler.writeImports();
    ExportsHandler.writeExports();
    this.addSpaceAndWriteFiles();
  }

  setVariables(path) {
    this.files = {
      imports: new File(path, "imports.h"),
      source: new File(path, "c"),
      exports: new File(path, "exports.h"),
    };
    this.data = fs.readFileSync(path).toString();
    this.name = path.slice(path.lastIndexOf("/") + 1, path.indexOf("."));
    this.namespace = Namespace.fromPath(path);
  }

  addHeaders() {
    this.files.imports.append("#pragma once");
    this.files.imports.append(`#include "${this.name}.exports.h"`);
    this.files.exports.append("#pragma once");
    this.files.exports.append("#include <modules/nova/nova.model.h>");
    this.files.exports.append("");
    this.files.source.append(`#include "${this.name}.component.h"`);
    this.files.source.append("");
  }

  addSpaceAndWriteFiles() {
    Object.values(this.files).forEach((file) => {
      file.append("");
      file.write();
    });
  }

  findAnnotations() {
    const pattern = /annotation\s*\(.*\)/g;
    const annotations = [];
    do {
      const result = pattern.exec(this.data);
      if (result) {
        const [directive, ...params] = result[0]
          .match(/\(.*\)/)[0]
          .replace(/[\(\)]/g, "")
          .split("|");
        annotations.push({
          text: result[0],
          index: result.index,
          directive: directive.trim(),
          params: params.map((p) => p.trim()),
        });
      }
    } while (pattern.lastIndex != 0);
    return annotations;
  }
}

Parser.run();

function update(source) {
  const files = {};

  fs.readFile(source, (err, data) => {
    if (err) {
      console.log(err.message);
    }
    parse(data.toString(), files);
  });
}

function parse(content, files) {
  const methods = extractMethods(content).filter((x) => x[0] !== "#");
  writeImportsHeader(content, files, methods);
  writeExportsHeaderAndSource(files, methods);
}

function extractMethods(content) {
  return (
    content.match(
      /(\#?export(\s+method)?|static)\s+(inline\s+)?(const\s+)?(struct\s+|union\s+|enum\s+)?\w+\*?\s+\w+\s?\(.*\)/g
    ) ?? []
  );
}

function parseNamespace(path, isImportPath) {
  if (isImportPath) {
  }
  return path
    .slice(path.indexOf("src/") + 4, path.lastIndexOf("/"))
    .replaceAll("/", "")
    .replace("modules", "NVM_")
    .replace("app", "NVA_")
    .toUpperCase();
}

function writeImportsHeader(content, files, methods) {
  const start = files.exports.lastIndexOf("/") + 1;
  const include = files.exports.slice(start);

  let lines = {
    includes: ["#pragma once", `#include "${include}"`],
    namespaces: [],
  };

  parseImports(content, lines);
  const declarations = methods.map(
    (x) => x.replace("export", "static").trim() + ";"
  );

  lines = [...lines.includes, "", ...lines.namespaces, "", ...declarations, ""];
  const text = lines.join("\n");

  fs.writeFileSync(files.imports, text);
}

function parseImports(content, lines) {
  content
    .match(/(\#?)import\([\.\w]+\s?,\s?\w+\)/g)
    ?.filter((directive) => directive[0] !== "#")
    .forEach((directive) => {
      directive = directive.replace(/import\(/, "");
      directive = directive.replace(")", "");
      const [path, identifier] = directive.split(",").map((x) => x.trim());

      const pathTokens = path.split(".");
      const include = `#include <${pathTokens.join("/")}/${
        pathTokens[pathTokens.length - 1]
      }.exports.h>`;
      const pathSnake = `NS${pathTokens.join("")}`.toUpperCase();
      const namespace = `static const struct ${pathSnake} ${identifier} = ${pathSnake}_instance;`;
      lines.includes.push(include);
      lines.namespaces.push(namespace);
    });
}

function writeExportsHeaderAndSource(files, methods) {
  const start = files.source.lastIndexOf("/") + 1;
  const componentHeader = files.source
    .replace(".c", ".component.h")
    .slice(start);

  let lines = {
    includes: ["#pragma once", "#include <modules/nova/nova.model.h>"],
    struct: [],
    source: [`#include "${componentHeader}"`],
  };

  if (parseExports(files, lines, methods)) {
    lines.source.push("");
    const variable = lines.struct[lines.struct.length - 1]
      .replace("extern", "")
      .replace(";", " = {")
      .trim();
    lines.source.push(variable);
    const exported = extractExported(methods);

    exported.forEach((method) => {
      const name = method.match(/\w+\s?\(/g)[0].replace("(", "");
      lines.source.push(`\t.${name} = ${name},`);
    });
    lines.source.push("};");
  }
  lines.source.push("");
  console.log(lines.source);

  const linesExports = [...lines.includes, "", ...lines.struct, ""];
  const textExports = linesExports.join("\n");

  const textSource = lines.source.join("\n");

  fs.writeFileSync(files.exports, textExports);
  fs.writeFileSync(files.source, textSource);
}

function extractExported(methods) {
  return methods
    .filter((method) => method.includes("export"))
    .map((method) =>
      method
        .replace(/(export|inline)/g, "")
        .replace(/\s+/g, " ")
        .trim()
    );
}

function parseExports(files, lines, methods) {
  const exported = extractExported(methods);

  if (exported.length === 0) {
    return false;
  }

  const namespace = parseNamespace(files.source, false);
  lines.struct.push("struct " + namespace + " {");

  exported.forEach((method) => {
    const name = method.match(/\w+\s?\(/g)[0].replace("(", "");
    method = method.replace(/\w+\s?\(/, `(*${name})(`);
    lines.struct.push("\t" + method + ";");
  });

  lines.struct.push("};");
  lines.struct.push("");
  lines.struct.push(`extern const struct ${namespace} ${namespace}_;`);
  return true;
}
