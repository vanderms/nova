import { MethodHandler } from "./methods.js";

export class AnnotationHandler {
  static update(data) {
    const pattern = /annotation\((.*)\)/g;
    this.annotations = [];
    do {
      const regex = pattern.exec(data);
      if (regex) {
        Annotation.createAnnotation(regex);
      }
    } while (pattern.lastIndex != 0);
  }

  static processAnnotations() {
    this.annotations.forEach((annotation) => {
      switch (annotation.directive) {
        case "import":
          return this.handleImport(annotation);
        case "method":
          return this.handleMethod(annotation);
        case "static":
          return this.handleStatic(annotation);
        case "constructor":
          return this.handleConstructor(annotation);
        case "destructor":
          return this.handleDestructor(annotation);
        case "type":
          return this.handleStatic(annotation);
        default:
          throw Error("Unknow annotation");
      }
    });
  }

  static handleImport() {}

  static handleMethod() {}

  static handleStatic(annotation) {
    const method = MethodHandler.methods.find(
      (method) => method.index > annotation.index
    );
    method.exp = true;
    method.name = annotation.params[0] ?? method.name;
  }

  static handleConstructor() {}

  static handleType() {}
  static handleDestructor() {}
}

export class Annotation {
  constructor(regex) {
    this.index = regex.index;
    const tokens = regex[1].split(",");
    this.directive = tokens[0].trim();
    this.params = tokens.slice(1).map((x) => x.trim());
  }
  static createAnnotation(regex) {
    AnnotationHandler.annotations.push(new Annotation(regex));
  }
}
