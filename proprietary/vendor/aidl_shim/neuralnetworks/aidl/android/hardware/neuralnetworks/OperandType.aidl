// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

/**
 * Operand data types
 */
@VintfStability
enum OperandType {
    FLOAT32 = 0,
    INT32 = 1,
    UINT32 = 2,
    TENSOR_FLOAT32 = 3,
    TENSOR_INT32 = 4,
    TENSOR_QUANT8_ASYMM = 5,
    BOOL = 6,
    TENSOR_QUANT16_SYMM = 7,
    TENSOR_FLOAT16 = 8,
    TENSOR_BOOL = 9,
    FLOAT16 = 10,
    TENSOR_QUANT8_SYMM_PER_CHANNEL = 11,
    TENSOR_QUANT16_ASYMM = 12,
    TENSOR_QUANT8_SYMM = 13,
    TENSOR_QUANT8_ASYMM_SIGNED = 14,
    SUBGRAPH = 15,
    // Extension range starts at 0x00010000
}