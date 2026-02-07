// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

/**
 * Performance information for an operation type
 */
@VintfStability
parcelable PerformanceInfo {
    // Number of operations that can be executed per second
    float opsPerSecond;
    // Power consumption (not used in shim)
    float powerUsage;
    // Additional performance metric
    float execTime;
}