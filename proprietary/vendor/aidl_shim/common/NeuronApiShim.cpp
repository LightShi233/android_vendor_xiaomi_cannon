/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#include "NeuronApiShim.h"
#include <cstring>
#include <cstdlib>

namespace android {
namespace hardware {
namespace neuralnetworks {
namespace aidl_shim {

NeuronShimLoader& NeuronShimLoader::getInstance() {
    static NeuronShimLoader instance;
    return instance;
}

NeuronShimLoader::~NeuronShimLoader() {
    deinitialize();
}

bool NeuronShimLoader::initialize() {
    if (mInitialized) {
        return true;
    }

    // Try to load the MTK Neuron library
    mHandle = dlopen(NEURON_LIB_PATH, RTLD_NOW | RTLD_LOCAL);
    if (!mHandle) {
        ALOGE("Failed to load %s: %s", NEURON_LIB_PATH, dlerror());
        
        // Try backup path
        mHandle = dlopen(NEURON_BACKUP_PATH, RTLD_NOW | RTLD_LOCAL);
        if (!mHandle) {
            ALOGE("Failed to load %s: %s", NEURON_BACKUP_PATH, dlerror());
            return false;
        }
    }

    ALOGI("Successfully loaded MTK Neuron library");

    // Load function pointers
    neuronGetCapabilities = (NeuronGetCapabilitiesFn)dlsym(mHandle, "Neuron_getCapabilities");
    neuronPrepareModel = (NeuronPrepareModelFn)dlsym(mHandle, "NeuronModel_prepare");
    neuronExecute = (NeuronExecuteFn)dlsym(mHandle, "NeuronExecution_compute");
    neuronGetSupportedOperations = (NeuronGetSupportedOperationsFn)dlsym(mHandle, "NeuronModel_getSupportedOperations");
    neuronReleaseModel = (NeuronReleaseModelFn)dlsym(mHandle, "NeuronModel_free");
    neuronGetType = (NeuronGetTypeFn)dlsym(mHandle, "NeuronDevice_getType");
    neuronGetVersion = (NeuronGetVersionFn)dlsym(mHandle, "NeuronDevice_getVersion");

    // Check critical functions
    if (!neuronGetCapabilities || !neuronPrepareModel || !neuronExecute) {
        ALOGE("Failed to load critical Neuron functions");
        deinitialize();
        return false;
    }

    mInitialized = true;
    ALOGI("MTK Neuron HAL shim initialized successfully");
    return true;
}

void NeuronShimLoader::deinitialize() {
    if (mHandle) {
        dlclose(mHandle);
        mHandle = nullptr;
    }
    
    neuronGetCapabilities = nullptr;
    neuronPrepareModel = nullptr;
    neuronExecute = nullptr;
    neuronGetSupportedOperations = nullptr;
    neuronReleaseModel = nullptr;
    neuronGetType = nullptr;
    neuronGetVersion = nullptr;
    
    mInitialized = false;
    ALOGI("MTK Neuron HAL shim deinitialized");
}

// ShimUtils implementation
void ShimUtils::convertCapabilitiesAidlToMtk(const void* aidlCaps, void* mtkCaps) {
    // This is a placeholder - actual implementation would need to
    // match the MTK internal structures exactly
    if (aidlCaps && mtkCaps) {
        std::memcpy(mtkCaps, aidlCaps, sizeof(float) * 3); // opsPerSecond, powerUsage, execTime
    }
}

void ShimUtils::convertCapabilitiesMtkToAidl(const void* mtkCaps, void* aidlCaps) {
    if (mtkCaps && aidlCaps) {
        std::memcpy(aidlCaps, mtkCaps, sizeof(float) * 3);
    }
}

bool ShimUtils::convertModelAidlToMtk(const void* aidlModel, void** mtkModel) {
    // Placeholder - would need MTK internal structures
    *mtkModel = const_cast<void*>(aidlModel); // Simplified for now
    return true;
}

void ShimUtils::freeMtkModel(void* mtkModel) {
    // Placeholder
    (void)mtkModel;
}

bool ShimUtils::convertRequestAidlToMtk(const void* aidlRequest, void** mtkRequest) {
    *mtkRequest = const_cast<void*>(aidlRequest);
    return true;
}

void ShimUtils::freeMtkRequest(void* mtkRequest) {
    (void)mtkRequest;
}

int ShimUtils::compareVersions(const char* v1, const char* v2) {
    if (!v1 || !v2) return 0;
    return std::strcmp(v1, v2);
}

bool ShimUtils::isVersionCompatible(const char* requiredVersion, const char* actualVersion) {
    if (!requiredVersion || !actualVersion) return false;
    // Simple version check - could be more sophisticated
    return std::strcmp(actualVersion, requiredVersion) >= 0;
}

} // namespace aidl_shim
} // namespace neuralnetworks
} // namespace hardware
} // namespace android