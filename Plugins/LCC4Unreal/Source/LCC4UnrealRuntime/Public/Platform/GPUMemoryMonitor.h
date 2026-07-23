/*********************************************
 * Copyright: XGrids Corporation
 * Author   : Finn
 * ******************************************/

#pragma once

#include "GPUMemory/IGPUMemoryProvider.h"

/**
 * Facade for querying OS-level GPU memory usage.
 *
 * Singleton with built-in caching and thread safety.
 * Automatically selects the best available provider on initialization:
 *   1. Windows: PDH+DXGI (vendor-agnostic, system-wide)
 *   2. Linux: Multi-vendor (AMD sysfs, NVIDIA NVML, Intel sysfs+RHI)
 *   3. Fallback: RHI (process-level only, all platforms)
 *
 * Usage:
 *   FGPUMemoryMonitor::Get().Initialize();   // Call once at module startup
 *   FGPUMemoryInfo Info = FGPUMemoryMonitor::Get().GetMemoryInfo();
 *   FGPUMemoryMonitor::Get().Shutdown();     // Call once at module shutdown
 */
class LCC4UNREALRUNTIME_API FGPUMemoryMonitor
{
public:
	/** Get the singleton instance */
	static FGPUMemoryMonitor& Get();

	/** Initialize with automatic provider selection. Call at module startup. */
	void Initialize();

	/** Shutdown and release resources. Call at module shutdown. */
	void Shutdown();

	/**
	 * Get cached GPU memory info.
	 * Automatically refreshes based on configured cache interval.
	 * Thread-safe.
	 */
	FGPUMemoryInfo GetMemoryInfo(uint32 DeviceIndex = 0);

	/** Force an immediate refresh, ignoring cache interval. Thread-safe. */
	FGPUMemoryInfo ForceRefresh(uint32 DeviceIndex = 0);

	/** Set cache interval in seconds. 0 = no caching (query every time). */
	void SetCacheInterval(float InSeconds);

	/** Get the name of the active provider for logging/debugging */
	FString GetActiveProviderName() const;

private:
	FGPUMemoryMonitor() = default;
	~FGPUMemoryMonitor() { Shutdown(); }

	TUniquePtr<IGPUMemoryProvider> ActiveProvider;

	// Cache
	FGPUMemoryInfo CachedInfo;
	double LastQueryTime = 0.0;
	float CacheIntervalSeconds = 1.0f;
	FCriticalSection CacheLock;
};
