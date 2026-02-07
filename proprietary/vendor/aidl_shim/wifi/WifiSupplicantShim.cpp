/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#include "WifiSupplicantShim.h"
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <log/log.h>

namespace android {
namespace hardware {
namespace wifi {
namespace aidl_shim {

#define LOG_TAG "WifiSupplicantAidlShim"

WifiSupplicantShim::WifiSupplicantShim() {
    ALOGI("WiFi Supplicant AIDL Shim created");
}

WifiSupplicantShim::~WifiSupplicantShim() {
    ALOGI("WiFi Supplicant AIDL Shim destroyed");
}

bool WifiSupplicantShim::initialize() {
    if (mInitialized) {
        return true;
    }

    // Get HIDL 1.4 service
    mHidlSupplicant = ISupplicant::getService();
    if (!mHidlSupplicant) {
        ALOGE("Failed to get HIDL 1.4 supplicant service");
        return false;
    }

    mInitialized = true;
    ALOGI("WiFi Supplicant AIDL Shim initialized successfully");
    return true;
}

ScopedAStatus WifiSupplicantShim::getInterface(const std::string& in_ifname,
                                               std::shared_ptr<ISupplicantIface>* out_iface,
                                               SupplicantStatus* out_status) {
    ALOGI("getInterface called for %s", in_ifname.c_str());

    if (!mInitialized) {
        ALOGE("Shim not initialized");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "Shim not initialized"};
        return ScopedAStatus::ok();
    }

    // Call HIDL 1.4 service
    Return<void> ret = mHidlSupplicant->getInterface(in_ifname.c_str(),
        [this, out_iface, out_status](const ::android::hardware::wifi::supplicant::V1_4::SupplicantStatus& hidlStatus,
                                      const sp<::android::hardware::wifi::supplicant::V1_4::ISupplicantIface>& hidlIface) {
            *out_status = convertHidlStatusToAidl(static_cast<int32_t>(hidlStatus.code));
            if (hidlStatus.code == ::android::hardware::wifi::supplicant::V1_4::SupplicantStatusCode::SUCCESS) {
                // TODO: Create AIDL wrapper for HIDL interface
                ALOGI("Successfully got interface from HIDL");
            }
        });

    if (!ret.isOk()) {
        ALOGE("HIDL call failed");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "HIDL call failed"};
    }

    return ScopedAStatus::ok();
}

ScopedAStatus WifiSupplicantShim::listInterfaces(std::vector<IfaceInfo>* out_ifaces,
                                                 SupplicantStatus* out_status) {
    ALOGI("listInterfaces called");

    if (!mInitialized) {
        ALOGE("Shim not initialized");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "Shim not initialized"};
        return ScopedAStatus::ok();
    }

    // Call HIDL 1.4 service
    Return<void> ret = mHidlSupplicant->listInterfaces(
        [this, out_ifaces, out_status](const ::android::hardware::wifi::supplicant::V1_4::SupplicantStatus& hidlStatus,
                                       const hidl_vec<::android::hardware::wifi::supplicant::V1_4::ISupplicant::IfaceInfo>& hidlIfaces) {
            *out_status = convertHidlStatusToAidl(static_cast<int32_t>(hidlStatus.code));
            if (hidlStatus.code == ::android::hardware::wifi::supplicant::V1_4::SupplicantStatusCode::SUCCESS) {
                out_ifaces->clear();
                for (const auto& hidlInfo : hidlIfaces) {
                    IfaceInfo info;
                    info.name = std::string(hidlInfo.name.c_str());
                    info.type = convertIfaceTypeHidlToAidl(hidlInfo.type);
                    out_ifaces->push_back(info);
                }
                ALOGI("Found %zu interfaces", out_ifaces->size());
            }
        });

    if (!ret.isOk()) {
        ALOGE("HIDL call failed");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "HIDL call failed"};
    }

    return ScopedAStatus::ok();
}

ScopedAStatus WifiSupplicantShim::registerCallback(const std::shared_ptr<ISupplicantCallback>& in_callback,
                                                   SupplicantStatus* out_status) {
    ALOGI("registerCallback called");
    
    if (!mInitialized) {
        ALOGE("Shim not initialized");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "Shim not initialized"};
        return ScopedAStatus::ok();
    }

    // TODO: Implement callback forwarding
    // For now, just return success
    *out_status = SupplicantStatus{SupplicantStatusCode::SUCCESS, ""};
    return ScopedAStatus::ok();
}

ScopedAStatus WifiSupplicantShim::createInterface(const SupplicantInterfaceCreationParams& in_params,
                                                  std::shared_ptr<ISupplicantIface>* out_iface,
                                                  SupplicantStatus* out_status) {
    ALOGI("createInterface called for %s", in_params.ifaceName.c_str());

    if (!mInitialized) {
        ALOGE("Shim not initialized");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "Shim not initialized"};
        return ScopedAStatus::ok();
    }

    // Convert params to HIDL format
    ::android::hardware::wifi::supplicant::V1_4::ISupplicant::SupplicantInterfaceCreationParams hidlParams;
    hidlParams.ifaceName = in_params.ifaceName;
    hidlParams.ifaceType = convertIfaceTypeAidlToHidl(in_params.ifaceType);

    Return<void> ret = mHidlSupplicant->createInterface(hidlParams,
        [this, out_iface, out_status](const ::android::hardware::wifi::supplicant::V1_4::SupplicantStatus& hidlStatus,
                                      const sp<::android::hardware::wifi::supplicant::V1_4::ISupplicantIface>& hidlIface) {
            *out_status = convertHidlStatusToAidl(static_cast<int32_t>(hidlStatus.code));
            if (hidlStatus.code == ::android::hardware::wifi::supplicant::V1_4::SupplicantStatusCode::SUCCESS) {
                ALOGI("Successfully created interface");
            }
        });

    if (!ret.isOk()) {
        ALOGE("HIDL call failed");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "HIDL call failed"};
    }

    return ScopedAStatus::ok();
}

ScopedAStatus WifiSupplicantShim::removeInterface(const std::string& in_ifname,
                                                  SupplicantStatus* out_status) {
    ALOGI("removeInterface called for %s", in_ifname.c_str());

    if (!mInitialized) {
        ALOGE("Shim not initialized");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "Shim not initialized"};
        return ScopedAStatus::ok();
    }

    Return<::android::hardware::wifi::supplicant::V1_4::SupplicantStatus> ret = 
        mHidlSupplicant->removeInterface(in_ifname.c_str());

    if (!ret.isOk()) {
        ALOGE("HIDL call failed");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "HIDL call failed"};
    } else {
        *out_status = convertHidlStatusToAidl(static_cast<int32_t>(ret->code));
    }

    return ScopedAStatus::ok();
}

ScopedAStatus WifiSupplicantShim::getSdkMode(int32_t* out_sdkMode,
                                             SupplicantStatus* out_status) {
    ALOGI("getSdkMode called");
    
    if (!mInitialized) {
        ALOGE("Shim not initialized");
        *out_status = SupplicantStatus{SupplicantStatusCode::FAILURE_UNKNOWN, "Shim not initialized"};
        return ScopedAStatus::ok();
    }

    // SDK mode is 1.5 feature, return 0 for 1.4
    *out_sdkMode = 0;
    *out_status = SupplicantStatus{SupplicantStatusCode::SUCCESS, ""};
    
    return ScopedAStatus::ok();
}

ScopedAStatus WifiSupplicantShim::setDebugLevel(int32_t in_level,
                                                SupplicantStatus* out_status) {
    ALOGI("setDebugLevel called with level %d", in_level);
    
    // Debug level is 1.5 feature, return success for shim
    (void)in_level;
    *out_status = SupplicantStatus{SupplicantStatusCode::SUCCESS, ""};
    
    return ScopedAStatus::ok();
}

ScopedAStatus WifiSupplicantShim::getDebugLevel(int32_t* out_level,
                                                SupplicantStatus* out_status) {
    ALOGI("getDebugLevel called");
    
    // Debug level is 1.5 feature, return default 0
    *out_level = 0;
    *out_status = SupplicantStatus{SupplicantStatusCode::SUCCESS, ""};
    
    return ScopedAStatus::ok();
}

SupplicantStatus WifiSupplicantShim::convertHidlStatusToAidl(int32_t hidlStatus) {
    SupplicantStatusCode code;
    switch (hidlStatus) {
        case 0: // SUCCESS
            code = SupplicantStatusCode::SUCCESS;
            break;
        case 1: // FAILURE_UNKNOWN
            code = SupplicantStatusCode::FAILURE_UNKNOWN;
            break;
        case 2: // FAILURE_ARGS_INVALID
            code = SupplicantStatusCode::FAILURE_ARGS_INVALID;
            break;
        case 3: // FAILURE_IFACE_EXISTS
            code = SupplicantStatusCode::FAILURE_IFACE_EXISTS;
            break;
        case 4: // FAILURE_IFACE_UNKNOWN
            code = SupplicantStatusCode::FAILURE_IFACE_UNKNOWN;
            break;
        case 5: // FAILURE_UNSUPPORTED
            code = SupplicantStatusCode::FAILURE_UNSUPPORTED;
            break;
        default:
            code = SupplicantStatusCode::FAILURE_UNKNOWN;
            break;
    }
    return SupplicantStatus{code, ""};
}

::android::hardware::wifi::supplicant::V1_4::IfaceType WifiSupplicantShim::convertIfaceTypeAidlToHidl(IfaceType aidlType) {
    using HidlType = ::android::hardware::wifi::supplicant::V1_4::IfaceType;
    switch (aidlType) {
        case IfaceType::STA:
            return HidlType::STA;
        case IfaceType::AP:
            return HidlType::AP;
        case IfaceType::P2P:
            return HidlType::P2P;
        case IfaceType::NAN:
            return HidlType::NAN;
        default:
            return HidlType::STA;
    }
}

IfaceType WifiSupplicantShim::convertIfaceTypeHidlToAidl(::android::hardware::wifi::supplicant::V1_4::IfaceType hidlType) {
    using HidlType = ::android::hardware::wifi::supplicant::V1_4::IfaceType;
    switch (hidlType) {
        case HidlType::STA:
            return IfaceType::STA;
        case HidlType::AP:
            return IfaceType::AP;
        case HidlType::P2P:
            return IfaceType::P2P;
        case HidlType::NAN:
            return IfaceType::NAN;
        default:
            return IfaceType::STA;
    }
}

void WifiSupplicantShim::registerService() {
    auto service = ndk::SharedRefBase::make<WifiSupplicantShim>();
    
    if (!service->initialize()) {
        ALOGE("Failed to initialize WiFi Supplicant AIDL Shim");
        return;
    }

    const std::string instanceName = std::string("android.hardware.wifi.Supplicant/default");
    
    binder_status_t status = AServiceManager_addService(
        service->asBinder().get(), instanceName.c_str());
    
    if (status != STATUS_OK) {
        ALOGE("Failed to register WiFi Supplicant AIDL service: %d", status);
    } else {
        ALOGI("Successfully registered WiFi Supplicant AIDL service: %s", instanceName.c_str());
    }
}

} // namespace aidl_shim
} // namespace wifi
} // namespace hardware
} // namespace android
