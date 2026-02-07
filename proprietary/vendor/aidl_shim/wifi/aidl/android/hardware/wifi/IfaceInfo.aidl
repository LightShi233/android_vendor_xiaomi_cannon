// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.wifi;

/**
 * Interface information
 */
@VintfStability
parcelable IfaceInfo {
    // Interface name
    @utf8InCpp String name;
    // Interface type
    IfaceType type;
}