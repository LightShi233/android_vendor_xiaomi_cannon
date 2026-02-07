/*
 * Copyright (C) 2024 Xiaomi Corporation
 * Licensed under the Apache License, Version 2.0
 */

#ifndef NEURON_API_SHIM_H
#define NEURON_API_SHIM_H

#include <android/log.h>
#include <dlfcn.h>
#include <string>
#include <vector>
#include <functional>

#define LOG_TAG "NeuralNetworksAidlShim"
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace android {
namespace hardware {
namespace neuralnetworks {
namespace aidl_shim {

// MTK Neuron HAL function pointers
class NeuronShimLoader {
public:
    static NeuronShimLoader& getInstance();
    
    bool initialize();
    void deinitialize();
    bool isInitialized() const { return mInitialized; }
    
    // Function pointer types for MTK Neuron HAL
    using NeuronGetCapabilitiesFn = int (*)(void* capabilities);
    using NeuronPrepareModelFn = int (*)(const void* model, void** preparedModel);
    using NeuronExecuteFn = int (*)(void* preparedModel, const void* request);
    using NeuronGetSupportedOperationsFn = int (*)(const void* model, bool* supportedOps);
    using NeuronReleaseModelFn = int (*)(void* preparedModel);
    using NeuronGetTypeFn = const char* (*)();
    using NeuronGetVersionFn = const char* (*)();
    
    // Function pointers
    NeuronGetCapabilitiesFn neuronGetCapabilities = nullptr;
    NeuronPrepareModelFn neuronPrepareModel = nullptr;
    NeuronExecuteFn neuronExecute = nullptr;
    NeuronGetSupportedOperationsFn neuronGetSupportedOperations = nullptr;
    NeuronReleaseModelFn neuronReleaseModel = nullptr;
    NeuronGetTypeFn neuronGetType = nullptr;
    NeuronGetVersionFn neuronGetVersion = nullptr;

private:
    NeuronShimLoader() = default;
    ~NeuronShimLoader();
    
    NeuronShimLoader(const NeuronShimLoader&) = delete;
    NeuronShimLoader& operator=(const NeuronShimLoader&) = delete;
    
    void* mHandle = nullptr;
    bool mInitialized = false;
    
    // MTK Neuron library paths
    static constexpr const char* NEURON_LIB_PATH = "/vendor/lib64/libneuron_runtime.so";
    static constexpr const char* NEURON_BACKUP_PATH = 
"/vendor/lib64/libneuron_runtime.5.so";
};

// Utility functions for type conversion
class ShimUtils {
public:
    // Convert AIDL Capabilities to MTK internal format
    static void convertCapabilitiesAidlToMtk(const void* aidlCaps, void* mtkCaps);
    
    // Convert MTK Capabilities to AIDL format
    static void convertCapabilitiesMtkToAidl(const void* mtkCaps, void* aidlCaps);
    
    // Convert AIDL Model to MTK internal format
    static bool convertModelAidlToMtk(const void* aidlModel, void** mtkModel);
    
    // Convert MTK Model to AIDL format  
    static void freeMtkModel(void* mtkModel);
    
    // Convert AIDL Request to MTK internal format
    static bool convertRequestAidlToMtk(const void* aidlRequest, void** mtkRequest);
    static void freeMtkRequest(void* mtkRequest);
    
    // Version utilities
    static int compareVersions(const char* v1, const char* v2);
    static bool isVersionCompatible(const char* requiredVersion, const char* actualVersion);
};

} // namespace aidl_shim
} // namespace neuralnetworks
} // namespace hardware
} // namespace android

#endif // NEURON_API_SHIM_H