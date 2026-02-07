// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.Subgraph;
import android.hardware.neuralnetworks.Operand;
import android.hardware.neuralnetworks.Operation;

/**
 * Neural network model definition
 */
@VintfStability
parcelable Model {
    // Main subgraph (index 0)
    Subgraph main;
    // Referenced subgraphs (for control flow operations)
    Subgraph[] referenced;
    // Vendor extension name prefix (empty if no extensions)
    @utf8InCpp String[] vendorExtensions;
    // Additional extension data
    @nullable byte[] extensionData;
}