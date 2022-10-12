#pragma once
#include "boolean.exports.h"
#include <let/let.exports.h>

static const struct nova_ns_let* lt = &nova_ns_let_instance;

static let create(bool value);
static void destructor (let self);
static bool get(let self);
static void set(let self, bool value);
static int32_t compare(let self, let other);
