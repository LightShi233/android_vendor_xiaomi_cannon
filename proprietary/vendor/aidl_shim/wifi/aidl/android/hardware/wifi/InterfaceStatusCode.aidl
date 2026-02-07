// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.wifi;

/**
 * Interface status codes
 */
@VintfStability
enum InterfaceStatusCode {
    INACTIVE = 0,
    SCANNING = 1,
    AUTHENTICATING = 2,
    ASSOCIATING = 3,
    ASSOCIATED = 4,
    FOURWAY_HANDSHAKE = 5,
    GROUP_HANDSHAKE = 6,
    COMPLETED = 7,
    DISCONNECTED = 8,
}