#pragma once
#include "app.exports.h"
#include <primitives/i32/i32.exports.h>
#include <primitives/i64/i64.exports.h>
#include <let/let.exports.h>

static const struct nova_ns_primitives_i32* integer = &nova_ns_primitives_i32_instance;
static const struct nova_ns_primitives_i64* i64 = &nova_ns_primitives_i64_instance;
static const struct nova_ns_let* lt = &nova_ns_let_instance;

