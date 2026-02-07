/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#ifndef WIFI_SUPPLICANT_SHIM_H
#define WIFI_SUPPLICANT_SHIM_H

#include <aidl/android/hardware/wifi/BnSupplicant.h>
#include <aidl/android/hardware/wifi/ISupplicantCallback.h>
#include <aidl/android/hardware/wifi/ISupplicantIface.h>
#include <aidl/android/hardware/wifi/SupplicantStatus.h>
#include <aidl/android/hardware/wifi/SupplicantInterfaceCreationParams.h>
#include <aidl/android/hardware/wifi/IfaceInfo.h>
#include <hidl/HidlTransportSupport.h>
#include <android/hardware/wifi/supplicant/1.4/ISupplicant.h>

namespace android {
namespace hardware {
namespace wifi {
namespace aidl_shim {

using ::aidl::android::hardware::wifi::BnSupplicant;
using ::aidl::android::hardware::wifi::ISupplicantCallback;
using ::aidl::android::hardware::wifi::ISupplicantIface;
using ::aidl::android::hardware::wifi::SupplicantStatus;
using ::aidl::android::hardware::wifi::SupplicantInterfaceCreationParams;
using ::aidl::android::hardware::wifi::IfaceInfo;
using ::aidl::android::hardware::wifi::IfaceType;
using ::aidl::android::hardware::wifi::SupplicantStatusCode;
using ::ndk::ScopedAStatus;
using ::android::hardware::wifi::supplicant::V1_4::ISupplicant;

class WifiSupplicantShim : public BnSupplicant {
public:
    WifiSupplicantShim();
    ~WifiSupplicantShim();

    // Initialize the shim by connecting to HIDL 1.4 service
    bool initialize();

    // AIDL interface implementations
    ScopedAStatus getInterface(const std::string& in_ifname,
                               std::shared_ptr<ISupplicantIface>* out_iface,
                               SupplicantStatus* out_status) override;

    ScopedAStatus listInterfaces(std::vector<IfaceInfo>* out_ifaces,
                                 SupplicantStatus* out_status) override;

    ScopedAStatus registerCallback(const std::shared_ptr<ISupplicantCallback>& in_callback,
                                   SupplicantStatus* out_status) override;

    ScopedAStatus createInterface(const SupplicantInterfaceCreationParams& in_params,
                                  std::shared_ptr<ISupplicantIface>* out_iface,
                                  SupplicantStatus* out_status) override;

    ScopedAStatus removeInterface(const std::string& in_ifname,
                                  SupplicantStatus* out_status) override;

    ScopedAStatus getSdkMode(int32_t* out_sdkMode,
                             SupplicantStatus* out_status) override;

    ScopedAStatus setDebugLevel(int32_t in_level,
                                SupplicantStatus* out_status) override;

    ScopedAStatus getDebugLevel(int32_t* out_level,
                                SupplicantStatus* out_status) override;

    // Service registration
    static void registerService();

private:
    // HIDL 1.4 service handle
    sp<ISupplicant> mHidlSupplicant;
    bool mInitialized = false;

    // Convert HIDL status to AIDL status
    SupplicantStatus convertHidlStatusToAidl(int32_t hidlStatus);

    // Convert AIDL IfaceType to HIDL IfaceType
    ::android::hardware::wifi::supplicant::V1_4::IfaceType convertIfaceTypeAidlToHidl(IfaceType aidlType);

    // Convert HIDL IfaceType to AIDL IfaceType
    IfaceType convertIfaceTypeHidlToAidl(::android::hardware::wifi::supplicant::V1_4::IfaceType hidlType);
};

} // namespace aidl_shim
} // namespace wifi
} // namespace hardware
} // namespace android

#endif // WIFI_SUPPLICANT_SHIM_H
