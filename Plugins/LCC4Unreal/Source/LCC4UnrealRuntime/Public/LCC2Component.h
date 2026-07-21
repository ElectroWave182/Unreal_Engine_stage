/*********************************************
* Copyright: XGrids Corporation
 * Author   : Feng HaiLiang
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "LCCComponentBase.h"
#include "Components/PrimitiveComponent.h"
#include "Containers/Queue.h"
#include "LCC2Component.generated.h"

/**
 * Adds support for importing, processing and rendering of LCC2(XGrids) format 3D Gaussian Splatting.
 */
UCLASS()
class LCC4UNREALRUNTIME_API ULCC2Component : public ULCCComponentBase
{
    GENERATED_BODY()

    ULCC2Component();

    /** Current LCC meta info*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XGrids", meta = (AllowPrivateAccess = "true"))
    FLCC2MetaInfo MetaInfo;

public:
    FLCC2MetaInfo GetMetaInfo2();
    class LCC2Tree* GetTree() const;

protected:
    virtual void LoadLCC(const FString& Path) override;
    void Load(FLCC2MetaInfo& InMetaInfo);
    virtual bool CheckIfLCCValid(FString Path, FString& OutWorkPath) const override;
    virtual FMetaInfoBase GetMetaInfo() const override;
    virtual void UnLoad() override;
    virtual void BeginFrame(FCameraInfo& Camera, const FRenderInfo& InRenderInfo) override;
    virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
    virtual bool CanRender() const override;
    virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
    virtual bool CheckIfLoaded() const override;

    /**
     * Check if meta info is valid.
     */
    virtual bool IsMetaInfoValid() const override;
private:
    TSharedPtr<LCC2Tree> Tree;
    virtual bool HaveValidSplatData() override;
    virtual TSharedPtr<LCCCollisionManagerBase> CreateCollisionManager() override;
};
