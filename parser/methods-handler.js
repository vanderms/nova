export class MethodsHandler {  

  static getStaticMethodsDeclaration(data) {
    const pattern = this.getMethodPattern();
    const staticMethods = data.match(pattern);
   return staticMethods;
  }

  static getMethodPattern() {
    return /static\s+(inline\s+)?(const\s+)?(struct\s+|enum\s+|union\s+)?\w+\s*\*?\s+\w+\s*\(.*\)/g;
  }
}
