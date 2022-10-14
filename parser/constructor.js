export class ConstructorHandler {
  static updateModule(manager) {
    this.manager = manager;
  }

  static checkSyntax(annotation) {
    const constructorError = `Syntax error in ${this.manager.namespace.name}: more than one constructor per component.`;

    if (this.manager.constructor) {
      throw Error(constructorError);
    }
    this.manager.constructor = true;
  }

  static handleConstructor(annotation) {
    const pattern = this.manager.methodPattern();
    this.checkSyntax(annotation);   
    this.manager.type.write = true;
    pattern.lastIndex = annotation.index;
    const method = pattern.exec(this.manager.data)[0];

    const wrapper = method
      .replace(/(struct|union|enum)/, "")
      .replace(/(\w+\s*\*?\s+\w+)\s*\(/, "let nvconstructor("); 

    const methodDetails = this.manager.methods[method];

    this.manager.files.source.append("");
    this.manager.files.source.append(wrapper + "{");
    this.manager.files.source.append(
      `  return nvnova_.build(${methodDetails.name}(${methodDetails.params.join(",")}), &NVTYPE);`
    );
    this.manager.files.source.append("}");
    
    methodDetails.shouldExport = true;
    methodDetails.assign = "nvconstructor";
    methodDetails.pointer = this.manager.getPointer(wrapper.replace('nvconstructor', methodDetails.name));
  }
}
