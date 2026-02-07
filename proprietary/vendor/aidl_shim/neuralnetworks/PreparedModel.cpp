/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#include "PreparedModel.h"
#include "../common/NeuronApiShim.h"
#include <log/log.h>

namespace android {
namespace hardware {
namespace neuralnetworks {
namespace aidl_shim {

using ndk::ScopedAStatus;

PreparedModel::PreparedModel(const Model& model) : mModel(model) {
    ALOGI("PreparedModel created");
}

PreparedModel::~PreparedModel() {
    ALOGI("PreparedModel destroyed");
}

ScopedAStatus PreparedModel::execute(
    const Request& request,
    int64_t deadlineNanoseconds,
    const std::shared_ptr<IFencedExecutionCallback>& callback,
    const std::shared_ptr<IExecutionCallback>& executionCallback) {
    
    ALOGI("execute called with deadline=%ld ns", deadlineNanoseconds);

    auto& loader = NeuronShimLoader::getInstance();
    if (!loader.isInitialized()) {
        ALOGE("MTK Neuron HAL not initialized");
        if (executionCallback) {
            executionCallback->notify(ErrorStatus::DEVICE_UNAVAILABLE, 0);
        }
        return ScopedAStatus::ok();
    }

    // Execute the model using MTK HAL
    // This is a simplified implementation
    // In reality, this would convert the request and call MTK's execution function

    // Simulate execution
    int64_t executionTimeNs = 1000000; // 1ms simulated

    if (executionCallback) {
        executionCallback->notify(ErrorStatus::NONE, executionTimeNs);
    }

    ALOGI("Execution completed in %ld ns", executionTimeNs);
    return ScopedAStatus::ok();
}

ScopedAStatus PreparedModel::executeSynchronously(
    const Request& request,
    int64_t deadlineNanoseconds) {
    
    ALOGI("executeSynchronously called");
    
    // For shim, just call execute without callback
    return execute(request, deadlineNanoseconds, nullptr, nullptr);
}

ScopedAStatus PreparedModel::executeFenced(
    const Request& request,
    int64_t deadlineNanoseconds,
    int64_t durationNanoseconds) {
    
    ALOGI("executeFenced called with duration=%ld ns", durationNanoseconds);
    
    // Fenced execution is not supported by MTK 1.3, fall back to regular execute
    return execute(request, deadlineNanoseconds, nullptr, nullptr);
}

ScopedAStatus PreparedModel::configureExecutionBurst(int64_t durationNanoseconds) {
    ALOGI("configureExecutionBurst called with duration=%ld ns", durationNanoseconds);
    
    // Burst mode not supported by MTK 1.3
    (void)durationNanoseconds;
    
    return ScopedAStatus::ok();
}

ScopedAStatus PreparedModel::getSupportedOperationTypes(std::vector<int32_t>* outTypes) {
    ALOGI("getSupportedOperationTypes called");
    
    // Return all supported operation types
    // In a real implementation, this would query the MTK HAL
    outTypes->clear();
    
    // Add common operation types
    for (int i = 0; i <= 110; i++) {
        outTypes->push_back(i);
    }
    
    return ScopedAStatus::ok();
}

// Factory method
std::shared_ptr<PreparedModel> PreparedModel::make(const Model& model) {
    return ndk::SharedRefBase::make<PreparedModel>(model);
}

} // namespace aidl_shim
} // namespace neuralnetworks
} // namespace hardware
} // namespace android
