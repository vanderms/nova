import fs from "fs";

export class File {
  constructor(componentPath, extension) {
    this.path = componentPath.replace(".component.h", `.${extension}`);    
    this.text = [];
  }

  append(line) {
    this.text.push(line);
  }

  write() {
    fs.writeFileSync(this.path, this.text.join("\n"));
  }
}
