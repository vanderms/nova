#include "let.component.h"

const struct nova_ns_let nova_ns_let_instance = {
	.allocate = allocate,
	.build = build,
	.delete = delete,
	.get = get,
};
