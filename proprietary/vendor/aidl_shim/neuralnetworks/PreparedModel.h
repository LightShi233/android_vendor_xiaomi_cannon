/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#ifndef PREPARED_MODEL_H
#define PREPARED_MODEL_H

#include <aidl/android/hardware/neuralnetworks/BnPreparedModel.h>
#include <aidl/android/hardware/neuralnetworks/Model.h>
#include <aidl/android/hardware/neuralnetworks/Request.h>
#include <aidl/android/hardware/neuralnetworks/ErrorStatus.h>
#include <aidl/android/hardware/neuralnetworks/IFencedExecutionCallback.h>
#include <aidl/android/hardware/neuralnetworks/IExecutionCallback.h>

namespace android {
namespace hardware {
namespace neuralnetworks {
namespace aidl_shim {

using ::aidl::android::hardware::neuralnetworks::BnPreparedModel;
using ::aidl::android::hardware::neuralnetworks::Model;
using ::aidl::android::hardware::neuralnetworks::Request;
using ::aidl::android::hardware::neuralnetworks::ErrorStatus;
using ::aidl::android::hardware::neuralnetworks::IFencedExecutionCallback;
using ::aidl::android::hardware::neuralnetworks::IExecutionCallback;
using ::ndk::ScopedAStatus;

class PreparedModel : public BnPreparedModel {
public:
    explicit PreparedModel(const Model& model);
    ~PreparedModel();

    // AIDL interface implementations
    ScopedAStatus execute(
        const Request& request,
        int64_t deadlineNanoseconds,
        const std::shared_ptr<IFencedExecutionCallback>& callback,
        const std::shared_ptr<IExecutionCallback>& executionCallback) override;
    
    ScopedAStatus executeSynchronously(
        const Request& request,
        int64_t deadlineNanoseconds) override;
    
    ScopedAStatus executeFenced(
        const Request& request,
        int64_t deadlineNanoseconds,
        int64_t durationNanoseconds) override;
    
    ScopedAStatus configureExecutionBurst(int64_t durationNanoseconds) override;
    
    ScopedAStatus getSupportedOperationTypes(std::vector<int32_t>* outTypes) override;

    // Factory method
    static std::shared_ptr<PreparedModel> make(const Model& model);

private:
    Model mModel;
};

// Type alias for shared pointer
using SharedPreparedModel = std::shared_ptr<PreparedModel>;

} // namespace aidl_shim
} // namespace neuralnetworks
} // namespace hardware
} // namespace android

#endif // PREPARED_MODEL_H
