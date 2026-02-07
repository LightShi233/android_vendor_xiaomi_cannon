// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.wifi;

import android.hardware.wifi.SupplicantStatus;
import android.hardware.wifi.IfaceType;

/**
 * Supplicant interface
 */
@VintfStability
interface ISupplicantIface {
    /**
     * Get interface name
     */
    void getName(out @utf8InCpp String name, out SupplicantStatus status);

    /**
     * Get interface type
     */
    void getType(out IfaceType type, out SupplicantStatus status);
}