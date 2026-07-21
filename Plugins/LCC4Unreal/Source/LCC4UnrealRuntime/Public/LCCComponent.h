/*********************************************
 * Copyright: XGrids Corporation
 * Author   : Feng HaiLiang
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "LCCComponentBase.h"
#include "Components/PrimitiveComponent.h"
#include "LCCDefinition.h"
#include "Containers/Queue.h"
#include "LCCComponent.generated.h"

/**
 * Adds support for importing, processing and rendering of LCC(XGrids) format 3D Gaussian Splatting.
 */
UCLASS()
class LCC4UNREALRUNTIME_API ULCCComponent : public ULCCComponentBase
{
    GENERATED_BODY()

public:
    ULCCComponent();

    /**
    * If enabled, LCC will crop seam issues caused by tiled rendering, which may have improved the situation before LCC version 5.0, and this option will automatically turn on after 5.0.
    */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "XGrids")
    bool bEnableSeamCutting;

    // Several options that affect lcc performance
    UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, Category = "XGrids|Performance", DisplayName="LCC")
    FLCCRenderInfo LCCPerformance;

    LCCNodeManager* GetNodeManager() const { return NodeManager.Get(); }
    /**
     * If use seam cut in shader
     * Only when LCC file version > 5.0,this function will return true
     * @return true if use seam cut
     */
    bool GetUseSeamCut() const;;

protected:
    /** Current LCC meta info*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XGrids", meta = (AllowPrivateAccess = "true"))
    FLCCMetaInfo MetaInfo;

    /**
    * Load lcc scene
    * @param Path Lcc meta.lcc path
    */
    virtual void LoadLCC(const FString& Path) override;
    virtual bool CheckIfLCCValid(const FString Path, FString& OutWorkPath) const override;
    void LoadMeta(FString Path);
    void LoadIndex(const FLCCMetaInfo& Info);
    void LoadEnvironment() const;
    virtual void UnLoad() override;
    virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
    virtual void BeginFrame(FCameraInfo& Camera, const FRenderInfo& InRenderInfo) override;
    virtual bool CheckIfLoaded() const override;
    virtual bool CanRender() const override;
    virtual FMetaInfoBase GetMetaInfo() const override;

    /**
     * Check if meta info is valid.
     */
    virtual bool IsMetaInfoValid() const override;

    virtual bool HaveValidSplatData() override;
    virtual TSharedPtr<LCCCollisionManagerBase> CreateCollisionManager() override;

    /**
     * Performs a raycast test against the lcc.
     * Populates OutHit with the results.
     * Returns true it anything has been hit.
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids|Raycast")
    bool LineTraceSingleWithRadius(const FVector& Start, const FVector& End, float Radius, FLCCSplat& OutHit,
                                   bool bDrawDebugLine, float Duration, float Thickness) const;

    /**
     * Performs a raycast test against the lcc.
     * Populates OutHit with the results.
     * Returns true it anything has been hit.
     * Default radius is 10cm
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids|Raycast")
    bool LineTraceSingle(const FVector& Start, const FVector& End, FLCCSplat& OutHit, bool bDrawDebugLine,
                         float Duration, float Thickness) const;

    /**
     * Performs a raycast test against the lcc.
     * Populates OutHits array with the results.
     * Returns true it anything has been hit.
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids|Raycast")
    bool LineTraceMultiWithRadius(const FVector& Start, const FVector& End, float Radius,
                                  bool bDrawDebugLine, float Duration, float Thickness,
                                  TArray<FLCCSplat>& OutHits) const;

    /**
     * Performs a raycast test against the lcc.
     * Populates OutHits array with the results.
     * Returns true it anything has been hit.
     * Default radius is 10cm
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids|Raycast")
    bool LineTraceMulti(const FVector& Start, const FVector& End, bool bDrawDebugLine, float Duration, float
                        Thickness, TArray<FLCCSplat>& OutHits) const;

    virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

    //NodeManager can not be raw pointer
    TSharedPtr<LCCNodeManager> NodeManager;
};
