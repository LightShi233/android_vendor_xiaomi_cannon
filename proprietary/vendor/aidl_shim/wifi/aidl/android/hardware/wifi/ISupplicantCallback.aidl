// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.wifi;

import android.hardware.wifi.InterfaceStatusCode;

/**
 * Supplicant callback interface
 */
@VintfStability
interface ISupplicantCallback {
    /**
     * Called when an interface is created
     */
    void onInterfaceCreated(@utf8InCpp String ifname);

    /**
     * Called when an interface is removed
     */
    void onInterfaceRemoved(@utf8InCpp String ifname);

    /**
     * Called when interface state changes
     */
    void onInterfaceStateChanged(@utf8InCpp String ifname, InterfaceStatusCode status);
}