// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.ErrorStatus;
import android.hardware.neuralnetworks.Capabilities;
import android.hardware.neuralnetworks.Model;
import android.hardware.neuralnetworks.Execution;
import android.hardware.neuralnetworks.FencedExecutionCallback;
import android.hardware.neuralnetworks.ExecutionPreference;
import android.hardware.neuralnetworks.Priority;
import android.hardware.neuralnetworks.Extension;

/**
 * AIDL Neural Networks HAL Device Interface
 * Android 14 compatible shim layer that bridges to MTK Neuron HAL 1.3
 */
@VintfStability
interface Device {
    /**
     * Gets the capabilities of the driver
     */
    Capabilities getCapabilities();

    /**
     * Gets the capabilities of the driver (1.4 version)
     * Extended with additional performance metrics
     */
    Capabilities getCapabilities_1_4();

    /**
     * Gets the supported operations for a model
     */
    boolean[] getSupportedOperations(in Model model);

    /**
     * Gets the supported operations for a model (1.4 version)
     */
    boolean[] getSupportedOperations_1_4(in Model model);

    /**
     * Prepares a model for execution
     */
    void prepareModel(
        in Model model,
        in ExecutionPreference preference,
        in Priority priority,
        in long deadlineNanoseconds,
        in ParcelFileDescriptor[] modelCache,
        in ParcelFileDescriptor[] dataCache,
        in byte[] token,
        in IFencedExecutionCallback callback,
        in IPreparedModelCallback preparedModelCallback
    );

    /**
     * Gets the type of device
     */
    @utf8InCpp String getType();

    /**
     * Gets the version string
     */
    @utf8InCpp String getVersionString();

    /**
     * Gets the number of cache files needed
     */
    void getNumberOfCacheFilesNeeded(out int numModelCacheFiles, out int numDataCacheFiles);

    /**
     * Gets supported extensions
     */
    Extension[] getSupportedExtensions();

    /**
     * Gets supported extensions with versioning
     */
    Extension[] getSupportedExtensionsWithVersioning();
}