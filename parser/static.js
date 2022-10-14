import { methodPattern } from "./regex.js";

export class StaticHandler {
  static updateModule(manager) {
    this.manager = manager;
  }

  static handleStatic(annotation) {
    const pattern = methodPattern();
    pattern.lastIndex = annotation.index;

    switch (true) {
      case annotation.params.length === 0:
        return this.handleStaticExport(pattern);

      case annotation.params[0] === "constructor":
        return this.handleConstructor(annotation, pattern);

      case annotation.params[0] === "destructor":
        return console.log("destructor");

      case annotation.params[0] === "method":
        return console.log("method");
    }
  }

  static handleStatic(annotation) {
    const pattern = this.manager.methodPattern();
    pattern.lastIndex = annotation.index;
    const method = pattern.exec(this.manager.data)[0];
    const pointer = this.manager.getPointer(method);

    this.manager.methods[method].shouldExport = true;
    this.manager.methods[method].pointer = pointer;
    this.manager.methods[method].assign = this.manager.methods[method].name;
  }
}
