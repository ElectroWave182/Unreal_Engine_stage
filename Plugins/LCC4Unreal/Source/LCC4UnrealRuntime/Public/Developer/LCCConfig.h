/*********************************************
 * Copyright: XGrids Corporation
 * Author   : Feng HaiLiang
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "LCCDefinition.h"
#include "SceneUtils.h"
#include "LCCConfig.generated.h"

/**
 * LCC4Unreal Setting
 */
UCLASS(config = LCC4Unreal, defaultconfig, meta = (DisplayName = "LCC4Unreal"))
class LCC4UNREALRUNTIME_API ULCCConfig : public UDeveloperSettingsBackedByCVars
{
    GENERATED_BODY()

public:
    // UPROPERTY(config, VisibleAnywhere, Category = "LCC", meta = (
    //     DisplayName = "Splat Size(Byte)",
    //     ToolTip = "Splat data size in data.bin.",
    //     ConfigRestartRequired = false))
    uint32 SplatSize;

    // UPROPERTY(config, VisibleAnywhere, Category = "LCC", meta = (
    //     DisplayName = "Shcoef Size(Byte)",
    //     ToolTip = "Shcoef data size in data.bin.",
    //     ConfigRestartRequired = false))
    uint32 ShcoefSize;

    UPROPERTY(config, EditAnywhere, Category = "LCC", meta = (
        DisplayName = "AutoExposure Enable",
        ToolTip = "AutoExposure will be disable default.",
        ConfigRestartRequired = true))
    bool bEnableAutoExposure;

    UPROPERTY(config, EditAnywhere, Category = "LCC", meta = (
        DisplayName = "SceneCaptureComponent Support",
        ToolTip = "This will have a slight impact on performance.",
        ConfigRestartRequired = false))
    bool bSupportSceneCapture;

    UPROPERTY(config, EditAnywhere, Category = "LCC", meta = (
        DisplayName = "Splat Number For Discard Per Node",
        ToolTip =
        "In some cases, there are only one or two Splats in a large number of nodes. In this case, when the number of nodes is less than this value, the data of that node will be ignored,After changing the values, it is necessary to reload the LCC to take effect."
        ,
        ConfigRestartRequired = false))
    uint32 DefaultSplatNumForDiscardPerNode;

    UPROPERTY(config, EditAnywhere, Category = "AntiAliasing", meta = (
        DisplayName = "LCC1 Splat Anti-aliasing Method",
        ToolTip = "Determines the anti-aliasing method when rendering LCC1 3DGS (no depth). Default: FXAA.",
        ConfigRestartRequired = false))
    TEnumAsByte<EAntiAliasingMethod> LCC1SplatMethod;

    UPROPERTY(config, EditAnywhere, Category = "AntiAliasing", meta = (
        DisplayName = "LCC2 Splat Anti-aliasing Method",
        ToolTip = "Determines the anti-aliasing method when rendering LCC2 3DGS (with depth). Default: TSR.",
        ConfigRestartRequired = false))
    TEnumAsByte<EAntiAliasingMethod> LCC2SplatMethod;

    UPROPERTY(config, EditAnywhere, Category = "AntiAliasing", meta = (
        DisplayName = "LCC1 Point Cloud Anti-aliasing Method",
        ToolTip =
        "Determines the anti-aliasing method when rendering LCC1 point cloud (no depth). Default: MSAA.",
        ConfigRestartRequired = false))
    TEnumAsByte<EAntiAliasingMethod> LCC1PointCloudMethod;

    UPROPERTY(config, EditAnywhere, Category = "AntiAliasing", meta = (
        DisplayName = "LCC2 Point Cloud Anti-aliasing Method",
        ToolTip = "Determines the anti-aliasing method when rendering LCC2 point cloud (with depth). Default: TSR.",
        ConfigRestartRequired = false))
    TEnumAsByte<EAntiAliasingMethod> LCC2PointCloudMethod;

    UPROPERTY(config, EditAnywhere, Category = "Usage", meta = (
        //ConsoleVariable = "XGrids.MaxCPUUsagePercentageForRelease",
        DisplayName = "Max CPU Usage Percetage For Free(%)",
        ToolTip = "Determine the maximum CPU usage that needs to be released.",
        ConfigRestartRequired = false,
        ClampMin = "50",
        ClampMax = "100"))
    uint32 MaxCPUUsagePercentageForRelease;

    UPROPERTY(config, EditAnywhere, Category = "Usage", meta = (
        //ConsoleVariable = "XGrids.CPUReleasePercentage",
        DisplayName = "CPU Release Percetage(%)",
        ToolTip = "The Percetage of cleanup when the CPU usage reaches the maximum value.",
        ConfigRestartRequired = false,
        ClampMin = "10",
        ClampMax = "100"))
    uint32 CPUReleasePercentage;

    UPROPERTY(config, EditAnywhere, Category = "Usage", meta = (
        //ConsoleVariable = "XGrids.MaxGPUUsagePercentageForRelease",
        DisplayName = "Max GPU Usage Percetage For Free(%)",
        ToolTip = "Determine the maximum GPU usage that needs to be released.",
        ConfigRestartRequired = false,
        ClampMin = "50",
        ClampMax = "100"))
    uint32 MaxGPUUsagePercentageForRelease;

    UPROPERTY(config, EditAnywhere, Category = "Usage", meta = (
        //ConsoleVariable = "XGrids.GPUReleasePercentage",
        DisplayName = "GPU Release Percetage(%)",
        ToolTip = "The Percetage of cleanup when the GPU usage reaches the maximum value.",
        ConfigRestartRequired = false,
        ClampMin = "10",
        ClampMax = "100"))
    uint32 GPUReleasePercentage;

    UPROPERTY(config, EditAnywhere, Category = "Usage", meta = (
        DisplayName = "LCC2 GPU Memory Budget (MB)",
        ToolTip = "Maximum GPU memory budget for a single LCC2 model (all buffers combined). Higher values allow more splats to be GPU-resident simultaneously. Actual budget may be lower due to platform buffer size limits or available VRAM. Requires restart to take effect.",
        ConfigRestartRequired = true,
        ClampMin = "2048",
        ClampMax = "8192"))
    uint32 LCC2GPUMemoryBudget;

    UPROPERTY(config, EditAnywhere, Category = "Import / Export", meta = (
        //ConsoleVariable = "XGrids.ImportScale",
        DisplayName = "Import Scale",
        ToolTip = "Scale to apply during import.",
        ConfigRestartRequired = false,
        ClampMin = "0.0001"))
    float ImportScale;

    UPROPERTY(config, EditAnywhere, Category = "Import / Export", meta = (
        //ConsoleVariable = "XGrids.ExportScale",
        DisplayName = "Export Scale",
        ToolTip = "Scale to apply during export. In most cases, this should be equal to an inverted ImportScale.",
        ConfigRestartRequired = false,
        ClampMin = "0.0001"))
    float ExportScale;

    UPROPERTY(config, EditAnywhere, EditFixedSize, Category = "Level", meta = (
        DisplayName = "Range For Level",
        ToolTip = "Determines the distance corresponding to each level.",
        ConfigRestartRequired = false,
        EditFixedOrder
    ))
    TArray<float> RangeForLevel;

    UPROPERTY(config, EditAnywhere, Category = "Loader", meta = (
        //ConsoleVariable = "XGrids.MaxLoaderThreadNum",
        DisplayName = "Max Loader Thread Number",
        ToolTip = "Maximum number of loading threads.",
        ConfigRestartRequired = false,
        ClampMin = "5",
        ClampMax = "100"))
    int32 MaxLoaderThreadNum;

    UPROPERTY(config, EditAnywhere, Category = "Loader", meta = (
        //ConsoleVariable = "XGrids.PreCreateLoaderThreadNum",
        DisplayName = "Pre-Create Loader Thread Number",
        ToolTip = "Maximum number of pre-created loading threads.",
        ConfigRestartRequired = false,
        ClampMin = "0",
        ClampMax = "100"))
    int32 PreCreateLoaderThreadNum;

    UPROPERTY(config, EditAnywhere, Category = "Exporter", meta = (
        //ConsoleVariable = "XGrids.MaxExporterThreadNum",
        DisplayName = "Max Exporter Thread Number",
        ToolTip = "Maximum number of exporter threads.",
        ConfigRestartRequired = false,
        ClampMin = "5",
        ClampMax = "100"))
    int32 MaxExporterThreadNum;

    UPROPERTY(config, EditAnywhere, Category = "Exporter", meta = (
        //ConsoleVariable = "XGrids.PreCreateExporterThreadNum",
        DisplayName = "Pre-Create Exporter Thread Number",
        ToolTip = "Maximum number of pre-created exporter threads.",
        ConfigRestartRequired = false,
        ClampMin = "0",
        ClampMax = "100"))
    int32 PreCreateExporterThreadNum;

    UPROPERTY(config, EditAnywhere, Category = "Traversal", meta = (
        DisplayName = "Default Traversal Type",
        ToolTip = "Default traversal method when rendering in nodes.",
        ConfigRestartRequired = true))
    ETraversalType DefaultTraversalType;

    UPROPERTY(config, EditAnywhere, Category = "Traversal", meta = (
        //ConsoleVariable = "XGrids.MaxTraversalThreadNum",
        DisplayName = "Max Traversal Thread Number",
        ToolTip = "Maximum number of traversal threads.",
        ConfigRestartRequired = false,
        ClampMin = "5",
        ClampMax = "100"))
    int32 MaxTraversalThreadNum;

    UPROPERTY(config, EditAnywhere, Category = "Traversal", meta = (
        //ConsoleVariable = "XGrids.PreCreateTraversalThreadNum",
        DisplayName = "Pre-Create Traversal Thread Number",
        ToolTip = "Maximum number of pre-created traversal threads.",
        ConfigRestartRequired = false,
        ClampMin = "0",
        ClampMax = "100"))
    int32 PreCreateTraversalThreadNum;

    UPROPERTY(config, EditAnywhere, EditFixedSize, Category = "Level", meta = (
        DisplayName = "Sort Frequency For Level",
        ToolTip = "Determines the sort frequency corresponding to each level.",
        ConfigRestartRequired = false,
        EditFixedOrder
    ))
    TArray<float> SortFrequencyForLevel;

    //todo:use async compute cause render error,use compute now
    //UPROPERTY(config, EditAnywhere, Category = "Sort", meta = (
    //    DisplayName = "Default Compute Type",
    //    ToolTip = "Determines which Pass the GPU sorts on.",
    //    ConfigRestartRequired = false))
    EComputeType DefaultComputeType;

    UPROPERTY(config, EditAnywhere, Category = "Sort", meta = (
        DisplayName = "Default Sort Method",
        ToolTip = "Default translucent rendering sorting method.",
        ConfigRestartRequired = true))
    ESortMethod DefaultSortMethod;

    // SortBits is no longer user-configurable.
    // Adaptive sort strategy: 24-bit while camera moves, 32-bit on final stationary frame.
    // UPROPERTY(config, EditAnywhere, Category = "Sort", meta = (
    //     ConsoleVariable = "r.LCC2.SortBits",
    //     DisplayName = "Sort Precision (Bits)",
    //     ToolTip = "Radix sort key precision. 32 = full quality (4 passes), 24 = faster (3 passes). Lower values improve sort performance but may cause minor z-ordering artifacts in dense areas.",
    //     ConfigRestartRequired = false,
    //     ClampMin = "8", ClampMax = "32"))
    int32 SortBits;

    UPROPERTY(config, EditAnywhere, Category = "Rendering", meta = (
        DisplayName = "Enable Post Process",
        ToolTip = "When enabled, LCC pixels undergo InverseACES tonemap to participate in engine post-processing pipeline. When disabled, pre-tonemap snapshot is restored after tonemap via alpha blending. All LCC components in the scene use the same mode.",
        ConfigRestartRequired = false))
    bool bEnablePostProcess = true;

    UPROPERTY(config, EditAnywhere, Category = "Rendering", meta = (
        DisplayName = "Apply Tonemap Inverse",
        ToolTip = "When enabled, applies FilmToneMapInverse to LCC color during color-space conversion so that the engine tonemap reproduces the original captured appearance. Applies to both LCC1 and LCC2.",
        ConfigRestartRequired = false))
    bool bApplyTonemapInverse = false;

    UPROPERTY(config, EditAnywhere, Category = "Rendering", meta = (
        ConsoleVariable = "r.LCC2.QuadExtentThreshold",
        DisplayName = "Quad Extent Threshold",
        ToolTip = "Controls how far the splat quad extends from the Gaussian center. Higher values produce tighter quads with less overdraw, but may clip edges of semi-transparent splats. Default: 0.006, Original: 0.004 (1/255).",
        ConfigRestartRequired = false,
        ClampMin = "0.001", ClampMax = "0.1"))
    float QuadExtentThreshold;

    UPROPERTY(config, EditAnywhere, Category = "Rendering", meta = (
        ConsoleVariable = "r.LCC2.SmallSplatThreshold",
        DisplayName = "Small Splat Threshold (px)",
        ToolTip = "Splats smaller than this screen-space size (in pixels) collapse to a single pixel and skip SH evaluation. 0 = disabled. Higher values improve performance but may cause graininess in distant views.",
        ConfigRestartRequired = false,
        ClampMin = "0.0", ClampMax = "4.0"))
    float SmallSplatThreshold;

    UPROPERTY(config, EditAnywhere, Category = "Rendering", meta = (
        ConsoleVariable = "r.LCC2.FrustumMargin",
        DisplayName = "Frustum Cull Margin",
        ToolTip = "Frustum margin multiplier for per-splat culling. Values > 1.0 extend the frustum to avoid popping at screen edges. Default: 1.2.",
        ConfigRestartRequired = false,
        ClampMin = "1.0", ClampMax = "2.0"))
    float FrustumMargin;

    UPROPERTY(config, EditAnywhere, Category = "Sort", meta = (
        //ConsoleVariable = "XGrids.MaxSortThreadNum",
        DisplayName = "Max Sort Thread Number",
        ToolTip = "Maximum number of sort threads.",
        ConfigRestartRequired = false,
        ClampMin = "5",
        ClampMax = "100"))
    int32 MaxSortThreadNum;

    UPROPERTY(config, EditAnywhere, Category = "Sort", meta = (
        //ConsoleVariable = "XGrids.PreCreateSortThreadNum",
        DisplayName = "Pre-Create Sort Thread Number",
        ToolTip = "Maximum number of pre-created sort threads.",
        ConfigRestartRequired = false,
        ClampMin = "0",
        ClampMax = "100"))
    int32 PreCreateSortThreadNum;

    ULCCConfig();
    virtual FName GetCategoryName() const override;

#if WITH_EDITOR
    /** Show a notification if PropagateAlpha is disabled (required for correct alpha blending). */
    static void NotifyPropagateAlphaIfNeeded();
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
