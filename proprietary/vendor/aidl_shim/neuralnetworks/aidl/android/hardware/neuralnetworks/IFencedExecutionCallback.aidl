// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.ErrorStatus;

/**
 * Fenced execution callback interface
 */
@VintfStability
interface IFencedExecutionCallback {
    /**
     * Get the sync fence file descriptor
     */
    ParcelFileDescriptor getSyncFence();

    /**
     * Notify when execution is complete
     */
    void notify(
        in ErrorStatus errorStatus,
        in int64_t executionTimeNs,
        in int64_t durationNs
    );
}