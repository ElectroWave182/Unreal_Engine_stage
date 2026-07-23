/*********************************************
 * Copyright: XGrids Corporation
 * Author   : Finn
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "RHIStats.h"

/**
 * OS-level GPU memory information.
 * When queried via NVML, this represents system-wide usage (all processes).
 * When queried via RHI fallback, bIsValid will be false since RHI cannot
 * provide system-wide data.
 */
struct FGPUMemoryInfo
{
    /** Total dedicated VRAM in bytes */
    uint64 TotalBytes = 0;

    /** System-wide used VRAM in bytes (all processes) */
    uint64 UsedBytes = 0;

    /** Available VRAM in bytes */
    uint64 FreeBytes = 0;

    /** Whether this query returned valid OS-level data */
    bool bIsValid = false;

    /**
     * Get usage as percentage.
     * @return Usage percentage in range [0, 100]. Returns 0 if bIsValid is false or TotalBytes is 0.
     */
    uint32 GetUsagePercent() const
    {
        if (!bIsValid || TotalBytes == 0)
        {
            return 0;
        }
        return static_cast<uint32>(
            static_cast<double>(UsedBytes) / static_cast<double>(TotalBytes) * 100.0);
    }
};

/**
 * Abstract interface for querying GPU memory.
 * Implement this for each GPU vendor / query backend.
 *
 * Design: Strategy Pattern - each vendor provides a concrete implementation.
 * Adding a new vendor (e.g., AMD) only requires a new IGPUMemoryProvider subclass.
 */
class IGPUMemoryProvider
{
public:
    virtual ~IGPUMemoryProvider() = default;

    /** Try to initialize this provider. Return true if the backend is available. */
    virtual bool Initialize() = 0;

    /** Shutdown and release resources. */
    virtual void Shutdown() = 0;

    /** Whether this provider is ready to query. */
    virtual bool IsAvailable() const = 0;

    /** Query memory info for the given device. */
    virtual FGPUMemoryInfo QueryMemoryInfo(uint32 DeviceIndex = 0) = 0;

    /** Human-readable name for logging. */
    virtual FString GetProviderName() const = 0;
};
