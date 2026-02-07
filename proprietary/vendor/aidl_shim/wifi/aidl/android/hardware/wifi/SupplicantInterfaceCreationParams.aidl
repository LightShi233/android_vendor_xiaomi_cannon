// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.wifi;

/**
 * Parameters for creating a supplicant interface
 */
@VintfStability
parcelable SupplicantInterfaceCreationParams {
    // Interface name
    @utf8InCpp String ifaceName;
    // Interface type
    IfaceType ifaceType;
    // Configuration parameters
    @nullable byte[] configParams;
}