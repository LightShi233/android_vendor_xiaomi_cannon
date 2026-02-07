// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

/**
 * Extension information
 */
@VintfStability
parcelable Extension {
    // Extension name
    @utf8InCpp String name;
    // Extension version information
    long version;
    // Extension type information (if available)
    @nullable @utf8InCpp String type;
}