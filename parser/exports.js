import { StaticHandler } from "./static.js";
import { ConstructorHandler } from "./constructor.js";
import { MethodHandler } from "./method.js";
import { DestructorHandler } from "./destructor.js";

export class ExportsHandler {
  static updateModule(files, data, namespace) {
    this.files = files;
    this.data = data;
    this.namespace = namespace;
    this.methods = {};
    this.constructor = false;
    this.type = {
      write: false,
      destructor: "null",
    };
    this.setMethods();
    StaticHandler.updateModule(ExportsHandler);
    ConstructorHandler.updateModule(ExportsHandler);
    MethodHandler.updateModule(ExportsHandler);
    DestructorHandler.updateModules(ExportsHandler);
  }

  static setMethods() {
    const pattern = this.methodPattern();
    const declarations = this.data.match(pattern);
    declarations?.forEach((declaration) => {
      this.methods[declaration] = this.setMethodDetails(declaration);
    });
  }

  static setMethodDetails(method) {
    const declaration = method;
    const name = method
      .match(/(\w+\s*\()/)[0]
      .replace("(", "")
      .trim();
    const shouldExport = false;
    const params = method
      .match(/\(.*\)/)[0]
      .replace(/(\(|\))/g, "")
      .split(",")
      .map((param) => {
        const split = param.split(" ");
        return split[split.length - 1];
      });
    const pointer = null;
    const assign = name;

    return {
      name,
      assign,
      declaration,
      pointer,
      params,
      shouldExport,
    };
  }

  static methodPattern() {
    return /static\s+(inline\s+)?(const\s+)?(struct\s+|enum\s+|union\s+)?\w+\s*\*?\s+\w+\s*\(.*\)/g;
  }

  static handleExports(annotation) {
    switch (annotation.directive) {
      case "static":
        return StaticHandler.handleStatic(annotation);
      case "constructor":
        return ConstructorHandler.handleConstructor(annotation);
      case "destructor":
        return DestructorHandler.handleDestructor(annotation);
      case "method":
        return MethodHandler.handleMethod(annotation);
    }
  }

  static handleMethod() {
    //console.log(2, "method");
  }

  static handleConstructor() {
    //console.log(3, "constructor");
  }

  static handleDestructor() {
    //console.log(4, "destructor");
  }

  static writeExports() {
    this.writeMethodsDeclaration();
    if (Object.values(this.methods).some((method) => method.shouldExport)) {
      this.writeNamespaceStruct();
      this.writeNamespaceInstance();
    }
    if (this.type.write) {
      this.writeType();
    }
  }
  

  static writeMethodsDeclaration() {
    this.files.imports.append("");
    Object.keys(this.methods).forEach((method) =>
      this.files.imports.append(`${method};`)
    );
  }

  static writeNamespaceStruct() {
    this.files.exports.append("");
    this.files.exports.append(`struct ${this.namespace.type} {`);
    Object.values(this.methods).forEach((method) => {
      if (method.shouldExport) {
        this.files.exports.append(`  ${method.pointer};`);
      }
    });
    this.files.exports.append("};");
    this.files.exports.append("");
    this.files.exports.append(
      `extern const struct ${this.namespace.type} ${this.namespace.instance};`
    );
  }

  static writeNamespaceInstance() {
    this.files.source.append("");
    this.files.source.append(
      `const struct ${this.namespace.type} ${this.namespace.instance} = {`
    );
    Object.values(this.methods).forEach((method) => {
      if (method.shouldExport) {
        this.files.source.append(`  .${method.name} = ${method.assign},`);
      }
    });
    this.files.source.append("};");
  }

  static writeType() {
    this.files.imports.append("");
    this.files.imports.append("static const struct type NVTYPE = {");
    this.files.imports.append("  .hash = NV_LET_HASH,");
    this.files.imports.append(`  .name = "${this.namespace.name}",`);
    this.files.imports.append(`  .destructor = ${this.type.destructor}`);
    this.files.imports.append(`};`);
  }

  static getPointer(method) {
    return method
      .replace(/(static|inline)/g, "")
      .replace(/(\w+\s*\()/, "(*$1)(")
      .replace("()", ")")
      .trim();
  }
}
