#pragma once
#include <base/base.h>

struct nova_ns_primitives_f64 {
	let (*create)(double value);
	double (*get)(let self);
	void (*set)(let self, double value);
};

extern const struct nova_ns_primitives_f64 nova_ns_primitives_f64_instance;
