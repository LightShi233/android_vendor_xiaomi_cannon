// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.ErrorStatus;
import android.hardware.neuralnetworks.Request;

/**
 * Execution information
 */
@VintfStability
parcelable Execution {
    // Execution status
    ErrorStatus status;
    // Input request
    Request request;
    // Execution timing information
    long executionTimeNs;
    // Additional metadata
    @nullable byte[] metadata;
}