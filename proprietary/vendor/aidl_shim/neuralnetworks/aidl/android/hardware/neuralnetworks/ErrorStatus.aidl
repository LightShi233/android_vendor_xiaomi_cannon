// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

/**
 * Error status codes for Neural Networks HAL
 */
@VintfStability
enum ErrorStatus {
    NONE = 0,
    DEVICE_UNAVAILABLE = 1,
    GENERAL_FAILURE = 2,
    OUTPUT_INSUFFICIENT_SIZE = 3,
    INVALID_ARGUMENT = 4,
    MISSED_DEADLINE_TRANSIENT = 5,
    MISSED_DEADLINE_PERSISTENT = 6,
    RESOURCE_EXHAUSTED_TRANSIENT = 7,
    RESOURCE_EXHAUSTED_PERSISTENT = 8,
    DEAD_OBJECT = 9,
}