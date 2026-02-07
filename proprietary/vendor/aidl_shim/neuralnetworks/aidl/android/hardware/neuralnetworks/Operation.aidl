// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.OperationType;

/**
 * Operation definition
 */
@VintfStability
parcelable Operation {
    // Operation type
    OperationType type;
    // Indices of input operands
    int[] inputs;
    // Indices of output operands
    int[] outputs;
}