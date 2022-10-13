#pragma once
#include "f64.exports.h"
#include <let/let.exports.h>

static const struct nova_ns_let* lt = &nova_ns_let_instance;

static let create(double value);
static void destructor (let self);
static double get(let self);
static void set(let self, double value);
static int32_t compare(let self, let other);
