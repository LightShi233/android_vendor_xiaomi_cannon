// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

/**
 * Data location within a memory pool
 */
@VintfStability
parcelable DataLocation {
    // Memory pool index
    int poolIndex;
    // Offset within the pool
    long offset;
    // Length of the data
    long length;
}