// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

/**
 * Execution preference for model compilation
 */
@VintfStability
enum ExecutionPreference {
    LOW_POWER = 0,
    FAST_SINGLE_ANSWER = 1,
    SUSTAINED_SPEED = 2,
}