import { Namespace } from "./namespace.js";

export class ImportsHandler {
  static updateModule(files, data) {
    this.files = files;
    this.data = data;
    this.definitions = [];
    this.includes = [];
    this.typedefs = [];
  }

  static handleImport(annotation) {
    if (annotation.directive === "import") {
      const namespace = Namespace.fromName(annotation.params[0]);
      this.includes.push(namespace.include);
      const slug = annotation.params[1];
      this.definitions.push(`#define ${slug} ${namespace.instance}`);
    } else if (annotation.directive === "type") {
      const pattern = /(struct|union|enum)\s+\w+\s*\{/g;
      pattern.lastIndex = annotation.index;
      console.log(1, pattern.lastIndex);
      const struct = pattern.exec(this.data)[0].replace("{", "").trim();
      const tokens = struct.split(" ");
      const typedef = `typedef ${struct}* ${tokens[tokens.length - 1]};`;
      this.typedefs.push(typedef);
    }
  }

  static writeImports() {
    this.includes.forEach((include) => {
      this.files.imports.append(include);
    });
    this.files.imports.append("");
    this.definitions.forEach((def) => {
      this.files.imports.append(def);
    });

    this.typedefs.forEach((typedef) => {
      this.files.imports.append(typedef);
    });
  }
}
