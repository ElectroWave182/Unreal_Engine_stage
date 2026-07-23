/*********************************************
* Copyright: XGrids Corporation
 * Author   : Feng HaiLiang
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LCC2ProxyMesh.generated.h"


class UStaticMeshComponent;

/**
 * Approximated white-box proxy actor that pairs with ALCC2Actor in ProxyMesh
 * NormalGenerationMode. It writes CustomDepth so that the render-thread
 * extensions can detect pixels where the ProxyMesh is the front-most geometry
 * (Visible_ProxyMesh_Pixel) and cooperate purely in screen space.
 *
 * ProxyMesh_Actor holds no explicit reference to any ALCC2Actor; the pairing
 * is spatial only.
 */
UCLASS(hidecategories=(Input), showcategories=("Input|MouseInput", "Input|TouchInput"), ConversionRoot, ComponentWrapperClass, meta=(ChildCanTick))
class LCC4UNREALRUNTIME_API ALCC2ProxyMesh : public AActor
{
    GENERATED_UCLASS_BODY()

public:
    /** Root static mesh component that supplies scene depth and GBuffers. */
    UPROPERTY(Category = XGrids, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh"))
    TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

#if WITH_EDITOR
    /** Re-validate CustomDepth state after StaticMesh is assigned / cleared. */
    virtual void PostEditChangeProperty(FPropertyChangedEvent& Event) override;
#endif

    virtual void PostLoad() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    /**
     * Enable / disable CustomDepth based on whether StaticMesh is valid.
     * Emits at most one throttled warning per actor when mesh is null.
     */
    void RefreshCustomDepthState();

    /** Guards the throttled null-mesh warning to at most one emission per instance. */
    bool bLoggedNullMeshWarning = false;

#if WITH_DEV_AUTOMATION_TESTS
public:
    /** TEST-ONLY: exposes the throttled warning flag so automation tests
     *  can assert that exactly one warning was logged without capturing
     *  log output through a feedback context.
     */
    bool HasLoggedNullMeshWarning() const { return bLoggedNullMeshWarning; }

    /** TEST-ONLY: invokes the private RefreshCustomDepthState so tests
     *  can drive the throttle without going through a Tick() path that
     *  requires a registered UWorld.
     */
    void InvokeRefreshCustomDepthStateForTest() { RefreshCustomDepthState(); }
#endif // WITH_DEV_AUTOMATION_TESTS
};
