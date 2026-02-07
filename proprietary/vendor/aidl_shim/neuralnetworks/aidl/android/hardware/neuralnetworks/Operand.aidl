// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.OperandType;
import android.hardware.neuralnetworks.OperandLifeTime;

/**
 * Operand definition
 */
@VintfStability
parcelable Operand {
    // Operand type
    OperandType type;
    // Operand dimensions
    int[] dimensions;
    // Scale for quantized types
    float scale;
    // Zero point for quantized types
    int zeroPoint;
    // Lifetime of the operand
    OperandLifeTime lifetime;
    // Location of operand data (if constant)
    @nullable byte[] data;
    // Additional properties
    @nullable byte[] extraParams;
}