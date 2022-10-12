#pragma once
#include <base/base.h>

struct nova_ns_primitives_boolean {
	let (*create)(bool value);
	bool (*get)(let self);
	void (*set)(let self, bool value);
};

extern const struct nova_ns_primitives_boolean nova_ns_primitives_boolean_instance;
