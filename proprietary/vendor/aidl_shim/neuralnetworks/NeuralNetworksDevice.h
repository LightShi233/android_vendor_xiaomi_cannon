/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#ifndef NEURAL_NETWORKS_DEVICE_H
#define NEURAL_NETWORKS_DEVICE_H

#include <aidl/android/hardware/neuralnetworks/BnDevice.h>
#include <aidl/android/hardware/neuralnetworks/Capabilities.h>
#include <aidl/android/hardware/neuralnetworks/Model.h>
#include <aidl/android/hardware/neuralnetworks/ExecutionPreference.h>
#include <aidl/android/hardware/neuralnetworks/Priority.h>
#include <aidl/android/hardware/neuralnetworks/Extension.h>
#include <aidl/android/hardware/neuralnetworks/IFencedExecutionCallback.h>
#include <aidl/android/hardware/neuralnetworks/IPreparedModelCallback.h>
#include "PreparedModel.h"

namespace android {
namespace hardware {
namespace neuralnetworks {
namespace aidl_shim {

using ::aidl::android::hardware::neuralnetworks::BnDevice;
using ::aidl::android::hardware::neuralnetworks::Capabilities;
using ::aidl::android::hardware::neuralnetworks::Model;
using ::aidl::android::hardware::neuralnetworks::ExecutionPreference;
using ::aidl::android::hardware::neuralnetworks::Priority;
using ::aidl::android::hardware::neuralnetworks::Extension;
using ::aidl::android::hardware::neuralnetworks::IFencedExecutionCallback;
using ::aidl::android::hardware::neuralnetworks::IPreparedModelCallback;
using ::ndk::ScopedAStatus;

class NeuralNetworksDevice : public BnDevice {
public:
    NeuralNetworksDevice();
    ~NeuralNetworksDevice();

    // AIDL interface implementations
    ScopedAStatus getCapabilities(Capabilities* outCapabilities) override;
    ScopedAStatus getCapabilities_1_4(Capabilities* outCapabilities) override;
    ScopedAStatus getSupportedOperations(
        const Model& model,
        std::vector<bool>* outSupportedOperations) override;
    ScopedAStatus getSupportedOperations_1_4(
        const Model& model,
        std::vector<bool>* outSupportedOperations) override;
    ScopedAStatus prepareModel(
        const Model& model,
        ExecutionPreference preference,
        Priority priority,
        int64_t deadlineNanoseconds,
        const std::vector<ndk::ScopedFileDescriptor>& modelCache,
        const std::vector<ndk::ScopedFileDescriptor>& dataCache,
        const std::vector<uint8_t>& token,
        const std::shared_ptr<IFencedExecutionCallback>& callback,
        const std::shared_ptr<IPreparedModelCallback>& preparedModelCallback) override;
    ScopedAStatus getType(std::string* outType) override;
    ScopedAStatus getVersionString(std::string* outVersion) override;
    ScopedAStatus getNumberOfCacheFilesNeeded(
        int32_t* outNumModelCacheFiles, int32_t* outNumDataCacheFiles) override;
    ScopedAStatus getSupportedExtensions(
        std::vector<Extension>* outExtensions) override;
    ScopedAStatus getSupportedExtensionsWithVersioning(
        std::vector<Extension>* outExtensions) override;

    // Service registration
    static void registerService();
};

} // namespace aidl_shim
} // namespace neuralnetworks
} // namespace hardware
} // namespace android

#endif // NEURAL_NETWORKS_DEVICE_H
