import chokidar from "chokidar";
import fs from "fs";
import { FileHandler } from "./files.js";
import { MethodHandler } from "./methods.js";
import { AnnotationHandler } from "./annotations.js";

class Parser {
  static run() {
    chokidar
      .watch("./src/**/*.component.h")
      .on("add", (path) => this.update(path))
      .on("change", (path) => this.update(path));
  }

  static update(path) {
    const data = fs.readFileSync(path);
    MethodHandler.update(data);
    FileHandler.update(path);
    AnnotationHandler.update(data);
    AnnotationHandler.processAnnotations();
    FileHandler.write();
  }
}

Parser.run();
