#pragma once
#include <base/base.h>

struct nova_ns_let {
	void* (*allocate)(size_t size);
	let (*build)(void* value, struct type* type);
	void (*delete)(let self);
	void* (*get)(let self, struct type* type);
};

extern const struct nova_ns_let nova_ns_let_instance;
