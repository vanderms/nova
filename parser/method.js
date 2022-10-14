export class MethodHandler {
  static updateModule(manager) {
    this.manager = manager;
  }

  static handleMethod(annotation) {
    const pattern = this.manager.methodPattern();
    pattern.lastIndex = annotation.index;
    const result = pattern.exec(this.manager.data);
    if (!result) return;
    const method = result[0];
    const methodDetails = this.manager.methods[method];
    const wrapper = method
      .replace(/\(\s*(\w+)\s+/, "(let ")
      .replace(/(\w+)\s*\(/, "nv$1(");

    this.manager.files.source.append("");
    this.manager.files.source.append(wrapper + "{");
    this.manager.files.source.append(
      "  void* self_ = nvnova_.get(self, &NVTYPE);"
    );
    let params = methodDetails.params.slice(1).join(",").trim();
    if (params !== "") {
      params = ", " + params;
    }
    let includeReturn = method.match(/void\s+\w+/) ? "" : "return ";

    this.manager.files.source.append(
      `  ${includeReturn}${methodDetails.name}(self_${params});`
    );
    this.manager.files.source.append("}");

    methodDetails.shouldExport = true;
    methodDetails.assign = "nv" + methodDetails.name;
    methodDetails.pointer = this.manager.getPointer(
      wrapper.replace(methodDetails.assign, methodDetails.name)
    );
  }
}
