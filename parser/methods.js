export class MethodHandler {
  static update(data) {
    this.methods = [];
    const pattern = /static\s+(inline\s+)?((\w+\*?\s+)+)(\w+)\s*\((.*)\)/g;
    do {
      const result = pattern.exec(data);
      if (result) {
        Method.createMethod(result);
      }
    } while (pattern.lastIndex != 0);
  }
}

export class Method {
  constructor(regex, exp) {
    this.params = [];
    this.exp = exp;
    if (regex) {
      this.declaration = regex[0];
      this.returnValue = regex[2];
      this.identifier = regex[4];
      this.assign = this.identifier;
      this.index = regex.index;
      const params = regex[5].trim();
      this.void = params === "void";

      if (!this.void) {
        params.split(",").forEach((param) => {
          const tokens = param.split(" ");
          const name = tokens[tokens.length - 1].trim();
          const type = tokens
            .slice(0, tokens.length - 1)
            .join(" ")
            .trim();
          this.createParam(name, type);
        });
      }
    }
  }

  static createMethod(regex) {
    MethodHandler.methods.push(new Method(regex, false));
  }

  createParam(name, type) {
    this.params.push({ name, type });
  }
}
