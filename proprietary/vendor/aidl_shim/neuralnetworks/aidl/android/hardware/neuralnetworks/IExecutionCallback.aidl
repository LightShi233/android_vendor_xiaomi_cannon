// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.ErrorStatus;

/**
 * Execution completion callback
 */
@VintfStability
interface IExecutionCallback {
    /**
     * Called when execution is complete
     */
    void notify(
        in ErrorStatus errorStatus,
        in int64_t executionTimeNs
    );
}