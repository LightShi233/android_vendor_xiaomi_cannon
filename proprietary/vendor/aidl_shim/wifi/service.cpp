/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#include "WifiSupplicantShim.h"
#include <android/binder_process.h>
#include <log/log.h>

using android::hardware::wifi::aidl_shim::WifiSupplicantShim;

#define LOG_TAG "WifiSupplicantAidlShim"

int main() {
    ALOGI("Starting WiFi Supplicant AIDL HAL Shim Service");

    // Register the service
    WifiSupplicantShim::registerService();

    // Start the binder thread pool
    ABinderProcess_startThreadPool();

    ALOGI("WiFi Supplicant AIDL HAL Shim Service is running");

    // Join the thread pool
    ABinderProcess_joinThreadPool();

    ALOGI("WiFi Supplicant AIDL HAL Shim Service exited");

    return 0;
}
