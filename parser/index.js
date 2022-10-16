import chokidar from "chokidar";
import fs from "fs";

class Parser {
  static run() {
    const parser = new Parser();
    chokidar
      .watch("./src/**/*.component.h")
      .on("add", (path) => parser.onUpdate(path))
      .on("change", (path) => parser.onUpdate(path));
  }

  onUpdate(path) {
   
  }
}

Parser.run();
