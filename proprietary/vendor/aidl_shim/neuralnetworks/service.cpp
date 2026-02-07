/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#include "NeuralNetworksDevice.h"
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <log/log.h>

using android::hardware::neuralnetworks::aidl_shim::NeuralNetworksDevice;

#define LOG_TAG "NeuralNetworksAidlShim"

int main() {
    ALOGI("Starting Neural Networks AIDL HAL Shim Service");

    // Register the service
    NeuralNetworksDevice::registerService();

    // Start the binder thread pool
    ABinderProcess_startThreadPool();

    ALOGI("Neural Networks AIDL HAL Shim Service is running");

    // Join the thread pool
    ABinderProcess_joinThreadPool();

    ALOGI("Neural Networks AIDL HAL Shim Service exited");

    return 0;
}
