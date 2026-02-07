// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.Operand;
import android.hardware.neuralnetworks.Operation;

/**
 * Subgraph definition for model execution
 */
@VintfStability
parcelable Subgraph {
    // All operands in the subgraph
    Operand[] operands;
    // All operations in the subgraph
    Operation[] operations;
    // Indices to input operands
    int[] inputIndexes;
    // Indices to output operands
    int[] outputIndexes;
}