#pragma once
#include <base/base.h>

struct nova_ns_let {
	void* (*allocate)(size_t size);
	let (*build)(void* value, Type* type);
	void (*delete)(let self);
	void* (*getp)(let self, Type* type);
};

extern const struct nova_ns_let nova_ns_let_instance;
