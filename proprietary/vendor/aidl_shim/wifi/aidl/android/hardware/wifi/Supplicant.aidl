// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.wifi;

import android.hardware.wifi.ISupplicantCallback;
import android.hardware.wifi.ISupplicantIface;
import android.hardware.wifi.SupplicantStatus;
import android.hardware.wifi.SupplicantInterfaceCreationParams;
import android.hardware.wifi.IfaceInfo;

/**
 * AIDL WiFi Supplicant HAL Interface
 * Android 14 compatible shim layer that bridges to MTK wpa_supplicant HAL 1.4
 */
@VintfStability
interface Supplicant {
    /**
     * Get interface by name
     */
    void getInterface(
        @utf8InCpp String ifname,
        out ISupplicantIface iface,
        out SupplicantStatus status
    );

    /**
     * List all interfaces
     */
    void listInterfaces(
        out IfaceInfo[] ifaces,
        out SupplicantStatus status
    );

    /**
     * Register callback
     */
    SupplicantStatus registerCallback(in ISupplicantCallback callback);

    /**
     * Create interface
     */
    void createInterface(
        in SupplicantInterfaceCreationParams params,
        out ISupplicantIface iface,
        out SupplicantStatus status
    );

    /**
     * Remove interface
     */
    SupplicantStatus removeInterface(@utf8InCpp String ifname);

    /**
     * Get SDK mode (1.5+)
     */
    void getSdkMode(out int sdkMode, out SupplicantStatus status);

    /**
     * Set debug level (1.5+)
     */
    SupplicantStatus setDebugLevel(int level);

    /**
     * Get debug level (1.5+)
     */
    void getDebugLevel(out int level, out SupplicantStatus status);
}