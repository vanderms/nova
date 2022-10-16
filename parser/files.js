import fs from "fs";

export class FileHandler {
  static update(path) {
    this.public = new File(path.replace(".component.h", ".public.h"));
    this.private = new File(path.replace(".component.h", ".private.h"));
    this.source = new File(path.replace(".component.h", ".c"));
    const name = path.match(/(\w+)\.component\.h/)[1];
    this.setHeaders(name);
  }

  static setHeaders(name) {
    this.public.append("#include <modules/nova/nova.model.h>");
    this.private.append(`#include "${name}.public.h"`);
    this.source.append(`#include "${name}.private.h"`);
  }

  static write() {
    FileHandler.private.write();
    FileHandler.public.write();
    FileHandler.source.write();
  }
}

export class File {
  constructor(path) {
    this.path = path;
    this.lines = [];    
  }

  append(line) {
    this.lines.push(line);
  }

  write() {  
    fs.writeFileSync(this.path, this.lines.join("\n") + "\n");
  }
}
