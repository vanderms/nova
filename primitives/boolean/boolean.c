#include "boolean.component.h"

const struct nova_ns_primitives_boolean nova_ns_primitives_boolean_instance = {
	.create = create,
	.get = get,
	.set = set,
};
