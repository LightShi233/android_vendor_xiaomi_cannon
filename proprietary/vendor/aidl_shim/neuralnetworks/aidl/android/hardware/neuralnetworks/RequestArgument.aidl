// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.DataLocation;

/**
 * Request argument (input/output)
 */
@VintfStability
parcelable RequestArgument {
    // Data location
    DataLocation location;
    // Data dimensions (optional, for dynamic shapes)
    @nullable int[] dimensions;
}