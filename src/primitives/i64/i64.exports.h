#pragma once
#include <base/base.h>

struct nova_ns_primitives_i64 {
	let (*create)(int64_t value);
	int64_t (*get)(let self);
	void (*set)(let self, int64_t value);
};

extern const struct nova_ns_primitives_i64 nova_ns_primitives_i64_instance;
