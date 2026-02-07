// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.ErrorStatus;
import android.hardware.neuralnetworks.Request;
import android.hardware.neuralnetworks.IExecutionCallback;

/**
 * Prepared model for execution
 */
@VintfStability
interface PreparedModel {
    /**
     * Execute the prepared model
     */
    void execute(
        in Request request,
        in int64_t deadlineNanoseconds,
        in IFencedExecutionCallback callback,
        in IExecutionCallback executionCallback
    );

    /**
     * Execute the prepared model asynchronously
     */
    void executeSynchronously(
        in Request request,
        in int64_t deadlineNanoseconds
    );

    /**
     * Execute with burst mode
     */
    void executeFenced(
        in Request request,
        in int64_t deadlineNanoseconds,
        in int64_t durationNanoseconds
    );

    /**
     * Configure execution burst
     */
    void configureExecutionBurst(
        in int64_t durationNanoseconds
    );

    /**
     * Get supported operation types
     */
    int[] getSupportedOperationTypes();
}