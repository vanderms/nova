#pragma once
#include <base/base.h>

struct nova_ns_let {
	void* (*allocate)(size_t size);
	let (*build)(void* value, const struct type* type);
	void (*cleanup)(let* ref);
	void* (*get)(let self, const struct type* type);
	const struct type* (*getType)(let self);
	bool (*is)(let self, const struct type* type);
};

extern const struct nova_ns_let nova_ns_let_instance;
