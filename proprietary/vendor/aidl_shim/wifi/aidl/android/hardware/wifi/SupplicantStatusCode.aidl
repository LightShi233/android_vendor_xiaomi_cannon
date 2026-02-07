// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.wifi;

/**
 * Supplicant status codes
 */
@VintfStability
enum SupplicantStatusCode {
    SUCCESS = 0,
    FAILURE_UNKNOWN = 1,
    FAILURE_ARGS_INVALID = 2,
    FAILURE_IFACE_EXISTS = 3,
    FAILURE_IFACE_UNKNOWN = 4,
    FAILURE_UNSUPPORTED = 5,
}