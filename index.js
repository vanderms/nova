import chokidar from "chokidar";
import fs from "fs";

const watcher = chokidar.watch("./src/**/*.component.h");

watcher.on("add", update).on("change", update);

function update(source) {
  const files = {
    imports: source.replace(".component.h", ".imports.h"),
    source: source.replace(".component.h", ".c"),
    exports: source.replace(".component.h", ".exports.h"),
  };

  fs.readFile(source, (err, data) => {
    if (err) {
      console.log(err.message);
    }
    parse(data.toString(), files);
  });
}

function parse(content, files) {
  const methods = getStaticMethods(content).filter((x) => x[0] !== "#");
  writeImportsHeader(content, files, methods);
  writeExportsHeaderAndSource(content, files, methods);
}

function getStaticMethods(content) {
  return (
    content.match(
      /(\#?export\s+)?static\s+(inline\s+)?(struct\s+|union\s+|enum\s+)?\w+\*?\s+\w+\s?\(.*\)/g
    ) ?? []
  );
}

function writeImportsHeader(content, files, methods) {
  const start = files.exports.lastIndexOf("/") + 1;
  const include = files.exports.slice(start);

  let lines = {
    includes: ["#pragma once", `#include "${include}"`],
    namespaces: [],
  };

  parseImports(content, lines);
  const declarations = methods.map((x) => x.replace("export", "").trim() + ";");

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
      const pathSnake = `nova_ns_${pathTokens.join("_")}`;
      const namespace = `const struct ${pathSnake} ${identifier} = ${pathSnake}_instance;`;
      lines.includes.push(include);
      lines.namespaces.push(namespace);
    });
}

function writeExportsHeaderAndSource(content, files, methods) {
  let lines = {
    includes: ["#pragma once", "#include <base/base.h>"],
    struct: [],
    source: [],
  };


  if(parseExports(files, lines, methods)){
    const variable = lines.struct[lines.struct.length - 1].replace('extern', '').replace(";", " = {").trim();
    console.log(variable);    
  }

  lines = [...lines.includes, "", ...lines.struct, ""];
  const text = lines.join("\n");

  fs.writeFileSync(files.exports, text);
}
//create dest file

function parseExports(files, lines, methods) {
  const exportedMethods = methods.filter((method) => method.includes("export"));
  if (exportedMethods.length === 0) {
    return false;
  }

  const start = files.source.indexOf("/");
  const end = files.source.lastIndexOf("/");
  const namespace = `nova_ns${files.source
    .slice(start, end)
    .replaceAll("/", "_")}`;
  lines.struct.push("struct " + namespace + " {");

  exportedMethods
    .map((method) =>
      method
        .replace(/(static|export|inline)/g, "")
        .replace(/\s+/g, " ")
        .trim()
    )
    .forEach((method) => {
      const name = method.match(/\w+\s?\(/g)[0].replace("(", "");
      method = method.replace(name, `(*${name})`);
      lines.struct.push("\t" + method + ";");
    });

  lines.struct.push("};");
  lines.struct.push("");
  lines.struct.push(`extern const struct ${namespace} ${namespace}_instance;`);
  return true;
}
