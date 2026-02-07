// Copyright (C) 2024 Xiaomi Corporation
// Licensed under the Apache License, Version 2.0

package android.hardware.neuralnetworks;

import android.hardware.neuralnetworks.PerformanceInfo;

/**
 * Capabilities of the neural network device
 */
@VintfStability
parcelable Capabilities {
    // Float32 performance
    PerformanceInfo float32Performance;
    // Quantized 8-bit performance
    PerformanceInfo quantized8Performance;
    // Relaxed float32 to float16 performance (float32 path)
    PerformanceInfo relaxedFloat32toFloat16PerformanceFloat32;
    // Relaxed float32 to float16 performance (float16 path)
    PerformanceInfo relaxedFloat32toFloat16PerformanceFloat16;
    // Quantized 16-bit performance
    PerformanceInfo quantized16Performance;
    // Quantized asymmetric 8-bit performance
    PerformanceInfo quantized8AsymmetricPerformance;
    // Performance of IF operations
    PerformanceInfo ifPerformance;
    // Performance of WHILE operations
    PerformanceInfo whilePerformance;
}