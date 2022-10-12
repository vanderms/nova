#include "let.component.h"

const struct nova_ns_let nova_ns_let_instance = {
	.allocate = allocate,
	.build = build,
	.cleanup = cleanup,
	.get = get,
	.getType = getType,
	.is = is,
};
