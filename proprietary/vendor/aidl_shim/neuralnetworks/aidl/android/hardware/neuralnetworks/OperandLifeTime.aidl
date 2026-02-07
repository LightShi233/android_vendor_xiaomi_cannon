// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

/**
 * Operand lifetime
 */
@VintfStability
enum OperandLifeTime {
    TEMPORARY_VARIABLE = 0,
    SUBGRAPH_INPUT = 1,
    SUBGRAPH_OUTPUT = 2,
    CONSTANT_COPY = 3,
    CONSTANT_REFERENCE = 4,
    NO_VALUE = 5,
    SUBGRAPH = 6,
}