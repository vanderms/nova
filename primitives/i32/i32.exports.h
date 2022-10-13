#pragma once
#include <base/base.h>

struct nova_ns_primitives_i32 {
	let (*create)(int32_t value);
	int32_t (*get)(let self);
	void (*set)(let self, int32_t value);
};

extern const struct nova_ns_primitives_i32 nova_ns_primitives_i32_instance;
