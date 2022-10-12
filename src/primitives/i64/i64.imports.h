#pragma once
#include "i64.exports.h"
#include <let/let.exports.h>

static const struct nova_ns_let* lt = &nova_ns_let_instance;

static let create(int64_t value);
static void destructor (let self);
static int64_t get(let self);
static void set(let self, int64_t value);
static int32_t compare(let self, let other);
