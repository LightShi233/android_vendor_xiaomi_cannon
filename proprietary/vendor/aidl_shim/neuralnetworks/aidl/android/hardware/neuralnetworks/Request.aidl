// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.RequestArgument;
import android.hardware.neuralnetworks.MeasureTiming;

/**
 * Execution request
 */
@VintfStability
parcelable Request {
    // Input arguments
    RequestArgument[] inputs;
    // Output arguments
    RequestArgument[] outputs;
    // Measure timing preference
    MeasureTiming measureTiming;
    // Memory pool identifiers
    int[] memoryPoolIds;
}