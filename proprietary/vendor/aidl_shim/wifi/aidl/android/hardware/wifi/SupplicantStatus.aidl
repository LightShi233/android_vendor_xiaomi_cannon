// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.wifi;

/**
 * Supplicant status codes
 */
@VintfStability
parcelable SupplicantStatus {
    // Status code
    SupplicantStatusCode code;
    // Error message (if any)
    @utf8InCpp String message;
}