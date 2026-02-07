// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.ErrorStatus;
import android.hardware.neuralnetworks.PreparedModel;

/**
 * Callback for model preparation completion
 */
@VintfStability
interface IPreparedModelCallback {
    /**
     * Called when model preparation is complete
     */
    void notify(
        in ErrorStatus errorStatus,
        in @nullable PreparedModel preparedModel
    );
}