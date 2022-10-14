export class Namespace {
  constructor(name, type, instance, include) {
    this.name = name;
    this.type = type;
    this.instance = instance;
    this.include = include;
  }

  static fromName(name) {
    const type = `nv${name.replaceAll(".", "")}`.replace("nvmodules", "nv");
    const instance = `${type}_`;
    const single = name.match(/\.?\w+$/)[0].replace(".", "");
    const include = `#include <${name.replaceAll(
      ".",
      "/"
    )}/${single}.exports.h>`;

    return new Namespace(name, type, instance, include);
  }

  static fromPath(path) {
    const directories = path.replace(/(src\/|modules\/)/g, "");
    const namespace = directories.slice(0, directories.lastIndexOf("/")).trim();
    const type = `nv${namespace.replaceAll("/", "")}`;
    const name = namespace.replaceAll("/", ".");
    const include = `#include <${directories}>`.replace(
      ".component",
      ".exports"
    );
    const instance = `${type}_`;
    return new Namespace(name, type, instance, include);
  }
}
