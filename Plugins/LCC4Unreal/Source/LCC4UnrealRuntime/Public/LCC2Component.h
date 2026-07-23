/*********************************************
* Copyright: XGrids Corporation
 * Author   : Feng HaiLiang
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "LCCComponentBase.h"
#include "Components/PrimitiveComponent.h"
#include "Containers/Queue.h"
#include "Core/LCCEnum.h"
#include "Misc/Optional.h"
#include "LCC2Component.generated.h"

// Forward-declared so LCC2Component.h does not pull the private LCC2/ header.
class FLCC2GBufferCClearExtension;

/**
 * Adds support for importing, processing and rendering of LCC2(XGrids) format 3D Gaussian Splatting.
 */
UCLASS(ShowCategories=("Lighting"))
class LCC4UNREALRUNTIME_API ULCC2Component : public ULCCComponentBase
{
    GENERATED_BODY()

    ULCC2Component();

    /** Current LCC meta info*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XGrids", meta = (AllowPrivateAccess = "true"))
    FLCC2MetaInfo MetaInfo;

public:
    /**
     * Brightness of the 3DGS base color before scene lighting is applied.
     * Because the captured color already contains baked-in lighting, lower
     * values reduce over-exposure. 0 = fully driven by scene lighting, 1 = full
     * original brightness.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Lighting",
        meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
    float LightingScale = 0.0f;

    /**
     * Accumulated opacity threshold for median depth determination.
     * When front-to-back accumulated alpha reaches this value, the depth is
     * recorded as the representative depth for this pixel.
     * Lower = depth biased toward camera; Higher = depth biased away.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids", AdvancedDisplay,
        meta = (UIMin = "0.01", UIMax = "0.99", ClampMin = "0.01", ClampMax = "0.99"))
    float AlphaThreshold = 0.5f;

    /**
     * Controls how the 3DGS surface responds to scene lighting. See each value's
     * tooltip for the scenario it suits and its trade-offs.
     * - Fixed: one world normal for the whole splat (default). Flat but stable.
     * - ViewFacing: camera-facing normal; brightness follows the camera.
     * - Hemispherical: camera-independent hemisphere; smooth sun sweep.
     * - ProxyMesh: real normals/depth from a placed proxy mesh (licensed).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGrids|Lighting")
    ELCC2NormalGenerationMode NormalMode = ELCC2NormalGenerationMode::Fixed;

    /**
     * Hemispherical mode only: the direction the surface is treated as facing.
     * Adjust it to change how light and shadow move across the 3DGS as a
     * directional light rotates. Does not need to be normalized.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGrids|Lighting",
        meta = (EditCondition = "NormalMode == ELCC2NormalGenerationMode::Hemispherical", EditConditionHides))
    FVector NormalPole = FVector(1.0, 0.0, 1.0);

    /**
     * Hemispherical mode only: how strongly shading varies across the surface.
     * Smaller values give flatter, more even shading; larger values increase
     * the contrast between lit and shadowed areas.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGrids|Lighting",
        meta = (UIMin = "0.0", UIMax = "4.0", ClampMin = "0.0",
            EditCondition = "NormalMode == ELCC2NormalGenerationMode::Hemispherical", EditConditionHides))
    float NormalHemiSpread = 0.5f;

    /**
     * Fixed mode only: a single world-space normal used for the entire 3DGS.
     * Defaults to world up. Does not need to be normalized.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGrids|Lighting",
        meta = (EditCondition = "NormalMode == ELCC2NormalGenerationMode::Fixed", EditConditionHides))
    FVector FixedNormal = FVector(0.0, 0.0, 1.0);

    /**
     * Effective normal generation mode after applying the license gate.
     * Returns the stored NormalMode when licensed; forces Fixed when a gated
     * mode (ProxyMesh) is selected without a license. The stored UPROPERTY is
     * never modified.
     */
    UFUNCTION(BlueprintPure, Category = "XGrids")
    ELCC2NormalGenerationMode GetEffectiveNormalGenerationMode() const;

    FLCC2MetaInfo GetMetaInfo2();
    class LCC2Tree* GetTree() const;
    virtual ELCCVersion GetLccVersion() const override;

    TSharedPtr<class FLCC2MedianDepthExtension> GetMedianDepthExtension() const { return MedianDepthExtension; }

    /** Load from a pre-constructed MetaInfo (used by single-file actors). */
    void Load(FLCC2MetaInfo& InMetaInfo);

protected:
    virtual void LoadLCC(const FString& Path) override;
    virtual bool CheckIfLCCValid(FString Path, FString& OutWorkPath) const override;

    /**
     * Load MetaInfo from the given file path.
     * Default implementation reads meta.lcc JSON. Subclasses (SOG/SPZ components)
     * override to construct virtual MetaInfo from single-file headers.
     * @return true on success (MetaInfo populated), false on failure
     */
    virtual bool LoadMetaInfoFromPath(const FString& FullPath);

    virtual FMetaInfoBase GetMetaInfo() const override;
    virtual void UnLoad() override;
    virtual void BeginFrame(FCameraInfo& Camera, const FRenderInfo& InRenderInfo) override;
    virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
    virtual bool CanRender() const override;
    virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
    virtual FBox GetLocalVisibleBounds() const override;
    virtual bool CheckIfLoaded() const override;

    /**
     * Check if meta info is valid.
     */
    virtual bool IsMetaInfoValid() const override;

    // Lit mode need depth
    virtual void ToggleLightModeMaterial(ELightMode InLightMode) override;

private:
    TSharedPtr<LCC2Tree> Tree;
    TSharedPtr<class FLCC2MedianDepthExtension> MedianDepthExtension;

    /**
     * Per-UWorld singleton that clears GBufferC on Visible_ProxyMesh_Pixel
     * before the median-depth extension runs. Acquired in Load, released
     * in UnLoad via FLCC2GBufferCClearRegistry.
     */
    TSharedPtr<FLCC2GBufferCClearExtension, ESPMode::ThreadSafe> GBufferCClearExtension;

    /**
     * Last NormalGenerationMode reported to GBufferCClearExtension via
     * AddProxyMeshCount. Used by SyncProxyMeshCount to compute transitions.
     */
    TOptional<ELCC2NormalGenerationMode> ReportedNormalGenerationMode;

    /**
     * Game-thread only. Reconciles NormalGenerationMode with the shared
     * Clear Extension's counter, emitting +1/-1 deltas on transitions.
     */
    void SyncProxyMeshCount();

    virtual bool HaveValidSplatData() override;
    virtual TSharedPtr<LCCCollisionManagerBase> CreateCollisionManager() override;
};
