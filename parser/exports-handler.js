import { MethodsHandler } from "./methods-handler.js";

export class ExportsHandler {
  constructor(files, data) {
    this.files = files;
    this.data = data;
  }

  handleExport(annotation) {
   
    
    const pattern = MethodsHandler.getMethodPattern();
    pattern.lastIndex = annotation.index;
    
    if (annotation.params.includes("method")) {
      this.handleMethodExport(annotation, pattern);
    } else {
      this.handleStaticExport(annotation, pattern);
    }
  }

  handleStaticExport(annotation, pattern) {
    const method = pattern.exec(this.data)[0];
    console.log(1, method);
  }

  handleMethodExport(annotation, pattern) {
    
  }
}
