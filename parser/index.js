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
    try {
      this.setVariables(path);

      ExportsHandler.updateModule(this.files, this.data, this.namespace);
      ImportsHandler.updateModule(this.files, this.data);

      this.addHeaders();

      const annotations = this.findAnnotations();

      annotations.forEach((annotation) => {
        if (annotation.directive === "import") {
          ImportsHandler.handleImport(annotation);
        } else if (annotation.directive === "type") {
          ImportsHandler.handleType(annotation);
        } else {
          ExportsHandler.handleExports(annotation);
        }
      });

      ImportsHandler.writeImports();
      ExportsHandler.writeExports();
      this.addSpaceAndWriteFiles();
    } catch (err) {
      console.log(err.message);
    }
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
          .split(",");
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
