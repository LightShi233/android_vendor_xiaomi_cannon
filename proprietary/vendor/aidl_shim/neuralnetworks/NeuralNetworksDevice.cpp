/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#include "NeuralNetworksDevice.h"
#include "../common/NeuronApiShim.h"
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <log/log.h>

namespace android {
namespace hardware {
namespace neuralnetworks {
namespace aidl_shim {

using ndk::ScopedAStatus;

NeuralNetworksDevice::NeuralNetworksDevice() {
    // Initialize MTK Neuron HAL
    if (!NeuronShimLoader::getInstance().initialize()) {
        ALOGE("Failed to initialize MTK Neuron HAL");
    }
}

NeuralNetworksDevice::~NeuralNetworksDevice() {
    // Cleanup if needed
}

ScopedAStatus NeuralNetworksDevice::getCapabilities(Capabilities* outCapabilities) {
    ALOGI("getCapabilities called");
    
    auto& loader = NeuronShimLoader::getInstance();
    if (!loader.isInitialized()) {
        ALOGE("MTK Neuron HAL not initialized");
        return ScopedAStatus::fromServiceSpecificError(
            static_cast<int32_t>(ErrorStatus::DEVICE_UNAVAILABLE));
    }

    // Get capabilities from MTK HAL
    // MTK capabilities structure (simplified)
    struct MtkCapabilities {
        float float32Perf[3];  // opsPerSecond, powerUsage, execTime
        float quantized8Perf[3];
        float quantized16Perf[3];
        float asymmetric8Perf[3];
    } mtkCaps;

    if (loader.neuronGetCapabilities) {
        int result = loader.neuronGetCapabilities(&mtkCaps);
        if (result != 0) {
            ALOGE("Failed to get capabilities from MTK HAL: %d", result);
            return ScopedAStatus::fromServiceSpecificError(
                static_cast<int32_t>(ErrorStatus::GENERAL_FAILURE));
        }
    }

    // Convert to AIDL format
    outCapabilities->float32Performance.opsPerSecond = mtkCaps.float32Perf[0];
    outCapabilities->float32Performance.powerUsage = mtkCaps.float32Perf[1];
    outCapabilities->float32Performance.execTime = mtkCaps.float32Perf[2];

    outCapabilities->quantized8Performance.opsPerSecond = mtkCaps.quantized8Perf[0];
    outCapabilities->quantized8Performance.powerUsage = mtkCaps.quantized8Perf[1];
    outCapabilities->quantized8Performance.execTime = mtkCaps.quantized8Perf[2];

    outCapabilities->quantized16Performance.opsPerSecond = mtkCaps.quantized16Perf[0];
    outCapabilities->quantized16Performance.powerUsage = mtkCaps.quantized16Perf[1];
    outCapabilities->quantized16Performance.execTime = mtkCaps.quantized16Perf[2];

    outCapabilities->quantized8AsymmetricPerformance.opsPerSecond = mtkCaps.asymmetric8Perf[0];
    outCapabilities->quantized8AsymmetricPerformance.powerUsage = mtkCaps.asymmetric8Perf[1];
    outCapabilities->quantized8AsymmetricPerformance.execTime = mtkCaps.asymmetric8Perf[2];

    // Set default values for 1.4+ fields
    outCapabilities->relaxedFloat32toFloat16PerformanceFloat32 = outCapabilities->float32Performance;
    outCapabilities->relaxedFloat32toFloat16PerformanceFloat16 = outCapabilities->float32Performance;
    outCapabilities->ifPerformance = outCapabilities->float32Performance;
    outCapabilities->whilePerformance = outCapabilities->float32Performance;

    return ScopedAStatus::ok();
}

ScopedAStatus NeuralNetworksDevice::getCapabilities_1_4(Capabilities* outCapabilities) {
    // Same as getCapabilities for shim
    return getCapabilities(outCapabilities);
}

ScopedAStatus NeuralNetworksDevice::getSupportedOperations(
    const Model& model,
    std::vector<bool>* outSupportedOperations) {
    
    ALOGI("getSupportedOperations called");
    
    auto& loader = NeuronShimLoader::getInstance();
    if (!loader.isInitialized()) {
        ALOGE("MTK Neuron HAL not initialized");
        return ScopedAStatus::fromServiceSpecificError(
            static_cast<int32_t>(ErrorStatus::DEVICE_UNAVAILABLE));
    }

    // For shim, assume all operations are supported
    // In a real implementation, this would query the MTK HAL
    size_t numOperations = model.main.operations.size();
    outSupportedOperations->resize(numOperations, true);

    ALOGI("Returning %zu supported operations", numOperations);
    return ScopedAStatus::ok();
}

ScopedAStatus NeuralNetworksDevice::getSupportedOperations_1_4(
    const Model& model,
    std::vector<bool>* outSupportedOperations) {
    
    return getSupportedOperations(model, outSupportedOperations);
}

ScopedAStatus NeuralNetworksDevice::prepareModel(
    const Model& model,
    ExecutionPreference preference,
    Priority priority,
    int64_t deadlineNanoseconds,
    const std::vector<ndk::ScopedFileDescriptor>& modelCache,
    const std::vector<ndk::ScopedFileDescriptor>& dataCache,
    const std::vector<uint8_t>& token,
    const std::shared_ptr<IFencedExecutionCallback>& callback,
    const std::shared_ptr<IPreparedModelCallback>& preparedModelCallback) {
    
    ALOGI("prepareModel called with preference=%d, priority=%d", 
          static_cast<int>(preference), static_cast<int>(priority));

    auto& loader = NeuronShimLoader::getInstance();
    if (!loader.isInitialized()) {
        ALOGE("MTK Neuron HAL not initialized");
        if (preparedModelCallback) {
            preparedModelCallback->notify(ErrorStatus::DEVICE_UNAVAILABLE, nullptr);
        }
        return ScopedAStatus::ok();
    }

    // Create prepared model
    auto preparedModel = SharedPreparedModel::make(model);
    if (!preparedModel) {
        ALOGE("Failed to create prepared model");
        if (preparedModelCallback) {
            preparedModelCallback->notify(ErrorStatus::GENERAL_FAILURE, nullptr);
        }
        return ScopedAStatus::ok();
    }

    // Notify success
    if (preparedModelCallback) {
        preparedModelCallback->notify(ErrorStatus::NONE, preparedModel);
    }

    ALOGI("Model prepared successfully");
    return ScopedAStatus::ok();
}

ScopedAStatus NeuralNetworksDevice::getType(std::string* outType) {
    ALOGI("getType called");
    
    auto& loader = NeuronShimLoader::getInstance();
    if (loader.isInitialized() && loader.neuronGetType) {
        const char* type = loader.neuronGetType();
        if (type) {
            *outType = type;
            return ScopedAStatus::ok();
        }
    }
    
    // Default type
    *outType = "mtk-neuron";
    return ScopedAStatus::ok();
}

ScopedAStatus NeuralNetworksDevice::getVersionString(std::string* outVersion) {
    ALOGI("getVersionString called");
    
    auto& loader = NeuronShimLoader::getInstance();
    if (loader.isInitialized() && loader.neuronGetVersion) {
        const char* version = loader.neuronGetVersion();
        if (version) {
            *outVersion = version;
            return ScopedAStatus::ok();
        }
    }
    
    // Default version
    *outVersion = "MTK Neuron 1.3 (AIDL Shim 1.0)";
    return ScopedAStatus::ok();
}

ScopedAStatus NeuralNetworksDevice::getNumberOfCacheFilesNeeded(
    int32_t* outNumModelCacheFiles, int32_t* outNumDataCacheFiles) {
    
    ALOGI("getNumberOfCacheFilesNeeded called");
    
    // MTK Neuron 1.3 doesn't support caching, return 0
    *outNumModelCacheFiles = 0;
    *outNumDataCacheFiles = 0;
    
    return ScopedAStatus::ok();
}

ScopedAStatus NeuralNetworksDevice::getSupportedExtensions(
    std::vector<Extension>* outExtensions) {
    
    ALOGI("getSupportedExtensions called");
    
    // MTK Neuron 1.3 doesn't support extensions, return empty
    outExtensions->clear();
    
    return ScopedAStatus::ok();
}

ScopedAStatus NeuralNetworksDevice::getSupportedExtensionsWithVersioning(
    std::vector<Extension>* outExtensions) {
    
    ALOGI("getSupportedExtensionsWithVersioning called");
    
    // Return empty as 1.3 doesn't support extensions
    outExtensions->clear();
    
    return ScopedAStatus::ok();
}

// Service registration
void NeuralNetworksDevice::registerService() {
    auto service = ndk::SharedRefBase::make<NeuralNetworksDevice>();
    const std::string instanceName = std::string(Device::descriptor) + "/default";
    
    binder_status_t status = AServiceManager_addService(
        service->asBinder().get(), instanceName.c_str());
    
    if (status != STATUS_OK) {
        ALOGE("Failed to register NeuralNetworks AIDL service: %d", status);
    } else {
        ALOGI("Successfully registered NeuralNetworks AIDL service: %s", instanceName.c_str());
    }
}

} // namespace aidl_shim
} // namespace neuralnetworks
} // namespace hardware
} // namespace android