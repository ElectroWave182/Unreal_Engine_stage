/*********************************************
 * Copyright: XGrids Corporation
 * Author   : Feng HaiLiang
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "LCCDefinition.h"
#include "PhysicsEngine/BodySetup.h"
#include "Containers/Queue.h"
#include "LCCComponentBase.generated.h"

class ALCCSectionPlane;
class ALCCClippingVolume;
class UBodySetup;
class UPostProcessComponent;
class LCCNodeManager;
class ULCCRenderSystem;
class LCCCollisionManagerBase;
class AGeoReferencingSystem;
struct FLCCClippingVolume;
struct FLCCSectionPlane;
struct FLCCComponentRenderParams;

/**
 * Adds support for importing, processing and rendering of LCC(XGrids) format 3D Gaussian Splatting.
 */
UCLASS(ClassGroup = Rendering,
    ShowCategories = (Rendering),
    hidecategories = (Object, LOD, Activation, Materials, Cooking, Input, HLOD, Mobile, Replication, DataLayers
        , WorldPartition, TextureStreaming, Networking, LevelInstance, Navigation, LOD, AssetUserData, Object,Lighting,
        RayTracing,Physics,Collision))
class LCC4UNREALRUNTIME_API ULCCComponentBase : public UPrimitiveComponent, public IInterface_CollisionDataProvider
{
    GENERATED_BODY()

public:
    /**
     * Default meta.lcc load path.
     * If you use absolute path loading, similar to D:\lcc\Tower\meta.lcc
     * If you use relative path(relative to project content folder) loading, similar to Tower/meta.lcc
     */
    UPROPERTY(EditAnywhere, Category = "XGrids")
    FString DefaultLoadPath;

    /**
     * Several options that affect performance
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, Category = "XGrids|Performance",DisplayName="Base")
    FRenderInfo Performance;

    /**
     * Not Allows using custom-built material for the point cloud.
     */
    UPROPERTY(Transient)
    TObjectPtr<UMaterialInterface> CustomMaterial;

    /**
    * Provides a mode for render filter
    */
    UPROPERTY(Interp, EditAnywhere, BlueprintSetter="SetLoadMode", Category = "XGrids")
    ELoadMode LoadMode;

    /**
    * If true,lcc scene will render as point cloud
    */
    UPROPERTY(Interp, EditAnywhere, BlueprintSetter="SetRenderMode", Category = "XGrids")
    ERenderMode RenderMode;

    UPROPERTY(EditDefaultsOnly, Category = "XGrids")
    bool bCanSetShcoef;

    /**
    * If true,will use shcoef to improve lighting quality
    */
    UPROPERTY(Interp, EditAnywhere, Category = "XGrids", BlueprintSetter="SetUseShcoef",
        meta=(EditCondition="bCanSetShcoef && RenderMode == ERenderMode::Splatting", EditConditionHides))
    bool bUseShcoef;

    /**
    * If true,lcc scene will affect by lighting,May reduce performance
    */
    UPROPERTY(Interp, EditAnywhere, Category = "XGrids", BlueprintSetter="SetLightMode",
        meta = (EditCondition = "RenderMode == ERenderMode::Splatting", EditConditionHides))
    ELightMode LightMode;

    /**
    * Control splat quad size
    */
    UPROPERTY(Interp, EditAnywhere, Category = "XGrids", BlueprintSetter="SetSplatScale",
        meta = (ClampMin = "0.001", ClampMax = "1", EditCondition = "RenderMode == ERenderMode::Splatting",
            EditConditionHides))
    float SplatScale;

    /**
    * Control splat quad alpha
    */
    UPROPERTY(Interp, EditAnywhere, BlueprintSetter="SetGlobalAlpha", Category = "XGrids",
        meta = (ClampMin = "0.0", ClampMax = "1", EditCondition = "RenderMode == ERenderMode::Splatting",
            EditConditionHides))
    float GlobalAlpha;

    /**
    * Control point cloud alpha
    */
    UPROPERTY(Interp, EditAnywhere, BlueprintSetter="SetGlobalAlpha_PointCloud", Category = "XGrids",
        meta = (ClampMin = "0.0", ClampMax = "1", EditCondition = "RenderMode == ERenderMode::PointCloud",
            EditConditionHides))
    float GlobalAlpha_PointCloud;

    /**
     * If true,lcc scene will load collision data.
     */
    UPROPERTY(EditAnywhere, BlueprintSetter="SetLCCCollisionEnable", Category = "XGrids")
    bool bEnableCollision;

    //todo:Color Adjustment 
    UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, BlueprintSetter="SetSaturation",
        Category = "XGrids|Color Adjustment",
        meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation",
            ShiftMouseMovePixelPerDelta = "10"))
    FVector4 Saturation;

    UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, BlueprintSetter="SetContrast",
        Category = "XGrids|Color Adjustment",
        meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta
            = "10"))
    FVector4 Contrast;

    UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, BlueprintSetter="SetGamma",
        Category = "XGrids|Color Adjustment",
        meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta =
            "10"))
    FVector4 Gamma;

    /** Affects the emissive strength of the color. Useful to create Bloom and light bleed effects. */
    // UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Color Adjustment",
    // meta = (UIMin = "0.0", UIMax = "1.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta =
    // "10"))
    // FVector4 Gain;

    /** Applied additively, 0 being neutral. */
    UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, BlueprintSetter="SetOffset",
        Category = "XGrids|Color Adjustment",
        meta = (UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta
            = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true"))
    FVector4 Offset;

    /** Specifies the tint to apply to the points. */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, BlueprintSetter="SetColorTint",
        Category = "XGrids|Color Adjustment")
    FLinearColor ColorTint;

    /**
    * Whether the lcc scene receives shadows(Lcc scene must render as 3DGS).
    * Enabling this feature may have a large impact on performance.
    */
    UPROPERTY(Interp, EditAnywhere, Category = "XGrids|Experimental")
    bool bReceiveShadows;

    /**
     * For 3DGS or point cloud data rendering, the TSR and TAA anti-aliasing methods will cause ghosting when moving.
     * If you turn this switch on, the system will set the anti-aliasing method according to the configuration in ProjectSetting/Plugins/LCC4Unreal. 
     */
    UPROPERTY(Interp, EditAnywhere, Category = "XGrids")
    bool bAffectAntiAliasingMethod;

    /** Specifies the bottom color of the elevation-based gradient. */
    UPROPERTY(Interp, EditAnywhere, BlueprintSetter="SetElevationColorBottom", Category = "XGrids|Point Cloud")
    FLinearColor ElevationColorBottom;

    /** Specifies the top color of the elevation-based gradient. */
    UPROPERTY(Interp, EditAnywhere, BlueprintSetter="SetElevationColorTop", Category = "XGrids|Point Cloud")
    FLinearColor ElevationColorTop;

    /**
     * Because the engine's built-in tonemap will cause LCC color errors, tonemap is turned off by default.
     * This will cause coloring errors for other objects in the scene.
     * You can turn this off to get the correct coloring of other objects (You can use TonemapScale to adjust the LCC scene color)
     *
     * 2025-12-18
     * We use SceneExtension to resolve Tonemap Issue,and this var should always be true
     */
    // UPROPERTY(Interp, EditAnywhere, BlueprintSetter="SetReplaceTonemap", Category = "XGrids")
    bool bReplaceTonemap;

    /** You can add up to 500 Clipping Volumes to clip LCC scenes.*/
    UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, Category = "XGrids")
    TArray<ALCCClippingVolume*> ClippingVolumes;

    /** You can add up to 500 section planes to section the lcc scenes.*/
    UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, Category = "XGrids")
    TArray<ALCCSectionPlane*> SectionPlanes;

    /**
     * If true,LCC will use this custom fov for first camera
     */
    UPROPERTY(Interp, EditAnywhere, Category = "XGrids", meta = (InlineEditConditionToggle))
    bool bUseCustomFOV;

    /**
     * If true,LCC will use this custom fov for first camera
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "XGrids",
        meta=(EditCondition="bUseCustomFOV", UIMin="5.0", UIMax="180", ClampMin="5.0", ClampMax="180"))
    float OverrideMainCameraFOV;

    /**
     * If true,this actor will sort by distance and set translucent sort priority.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "XGrids",
        DisplayName="Enable Multiple LCCActor Auto Sort")
    bool bEnableMultipleLCCActorAutoSort;

    /**
     * If enabled, LCC will load collision data even in editor mode.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "XGrids")
    bool bEnableEditorCollision;
    /**
     * Whether to enable the LCC scene to be placed in the world with latitude and longitude.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XGrids|GIS")
    bool bEnableGeoPlace;

    /**
     * When bEnableGeoPlace is true, this property will be used to set the LCC scene's latitude and longitude offset.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XGrids|GIS")
    FVector GeoLocationOffset;

    /**
     * When bEnableGeoPlace is true, this property will be used to set the LCC scene's rotation offset.
     * TODO:can not use now
     */
    // UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XGrids|GIS")
    FRotator GeoRotatorOffset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XGrids|GIS|Advanced")
    FVector GeoMultiply;

    /**
     * When bEnableAnimation is true, LCC will load with animation.
     * Loading Animation has two stages:
     * First Stage: Delay (FirstStageDelay) then Scale from 0 to (FirstStageScale),
     * Second Stage: Delay (SecondStageDelay) then (FirstStageScale) to (SplatScale)
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation")
    bool bEnableAnimation;

    /**
     * This determines the speed of the loading animation.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation",
        meta=(EditCondition = bEnableAnimation, UIMin="0.0", ClampMin="0.0"), DisplayName="Speed")
    float AnimationSpeed;

    /**
     * This determines the scale of the point cloud during the first stage of loading animation.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation", DisplayName="First Stage Scale",
        meta=(EditCondition = bEnableAnimation, UIMin="0.0001", ClampMin="0.0001", UIMax="1.0", ClampMax="1.0"))
    float AnimationMinScale;

    /**
     * This determines the first stage of loading animation with a delay.
     * Unit: seconds
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation",
        meta=(EditCondition = bEnableAnimation, UIMin="0.0", ClampMin="0.0"))
    float FirstStageDelay;

    /**
     * This determines the second stage of loading animation with a delay.
     * Unit: seconds
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation",
        meta=(EditCondition = bEnableAnimation, UIMin="0.0", ClampMin="0.0"))
    float SecondStageDelay;

    /**
     * This determines the start time of the environment.
     * Environment data has no animation, so the environment data will be loaded after lcc load function is called.
     * Unit: seconds
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation",
        meta=(EditCondition = bEnableAnimation, UIMin="0.0", ClampMin="0.0"))
    float EnvironmentDelay;

    /**
     * The default animation starts with LCCActor origin location(0,0,0), but you can also set a custom offset.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation", DisplayName="OriginOffset",
        meta=(EditCondition = bEnableAnimation))
    FVector3f AnimationOriginOffset;

    UPROPERTY(EditAnywhere, Category = "XGrids", meta = (InlineEditConditionToggle))
    bool bUseFirstStageColor;

    /**
     * Color of the scan line for the first stage of loading animation.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation|ScanLine",
        meta=(EditCondition = bUseFirstStageColor))
    FLinearColor FirstStageColor;

    UPROPERTY(EditAnywhere, Category = "XGrids", meta = (InlineEditConditionToggle))
    bool bUseSecondStageColor;

    /**
     * Color of the scan line for the second stage of loading animation.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation|ScanLine",
        meta=(EditCondition = bUseSecondStageColor))
    FLinearColor SecondStageColor;

    /**
     * The thickness of the scan line.
     */
    UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "XGrids|Animation|ScanLine",
        meta=(EditCondition = bEnableAnimation, UIMin="0.0", ClampMin="0.0"))
    float ScanLineThickness;

    ULCCComponentBase();

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void Refresh();

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    bool Load(FString LCCPath);

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    virtual void UnLoad();

    UFUNCTION(BlueprintPure, Category = "XGrids")
    virtual bool CheckIfLoaded() const;

    /**
     * Check if input lcc file valid
     * LCC need data.bin and index.bin
     * LCC2 do not need this
     */
    virtual bool CheckIfLCCValid(const FString Path, FString& OutWorkPath) const;

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    bool CanSetShcoef() const { return GetMetaInfo().GetFileType() == EFileType::Quality; }

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE int32 GetMaxDistance() const { return Performance.GetMaxDistance(); }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    FORCEINLINE void SetMaxDistance(const int32 InDistance)
    {
        Performance.bDistanceLimit = true;
        Performance.MaxDistance = InDistance;
    }

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE int32 GetMaxSplatNum() const { return Performance.GetMaxSplatNum(); }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    FORCEINLINE void SetMaxSplatNum(const int32 InSplatNum)
    {
        Performance.bMaxSplatNumLimit = true;
        Performance.MaxSplatNum = InSplatNum;
    }

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE float GetLevelFactor() const { return Performance.GetLevelFactor(); }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    FORCEINLINE void SetLevelFactor(const float InLevelFactor)
    {
        Performance.bCanSetLevelFactor = true;
        Performance.LevelFactor = InLevelFactor;
    }

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE int32 GetPreloadDistance() const { return Performance.PreloadDistance; }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    FORCEINLINE void SetPreloadDistance(const int32 InPreloadDistance)
    {
        Performance.bPreloadDistanceLimit = true;
        Performance.PreloadDistance = InPreloadDistance;
    }

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE int32 GetStartLevel() const { return Performance.GetStartLevel(); }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    FORCEINLINE void SetStartLevel(const int32 InStartLevel)
    {
        Performance.bCanSetStartLevel = true;
        Performance.StartLevel = InStartLevel;
    }

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE int32 GetEndLevel() const { return Performance.GetEndLevel(); }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    FORCEINLINE void SetEndLevel(const int32 InEndLevel)
    {
        Performance.bCanSetEndLevel = true;
        Performance.EndLevel = InEndLevel;
    }

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE int32 GetMaxCollisionDistance() const { return Performance.GetMaxCollisionDistance(); }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    FORCEINLINE void SetMaxCollisionDistance(const int32 InMaxCollisionDistance)
    {
        Performance.bCollisionDistanceLimit = true;
        Performance.CollisionLoadMaxDistance = InMaxCollisionDistance;
    }

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE ELoadMode GetLoadMode() const { return LoadMode; }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetLoadMode(ELoadMode Mode);

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE bool GetUseShcoef() const { return bUseShcoef; }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetUseShcoef(bool InUseShcoef);

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE ELightMode GetLightMode() const { return LightMode; }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetLightMode(ELightMode InLightMode);

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void EnableReceiveShadows();
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void DisableReceiveShadows();

    UFUNCTION(BlueprintPure, Category = "XGrids|PointCloud")
    FORCEINLINE FLinearColor GetElevationColorBottom() const { return ElevationColorBottom; }

    UFUNCTION(BlueprintCallable, Category = "XGrids|PointCloud")
    void SetElevationColorBottom(FLinearColor InElevationColorBottom);

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE float GetSplatScale() const { return SplatScale; }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetSplatScale(float InSplatScale);

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE ERenderMode GetRenderMode() const { return RenderMode; }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetRenderMode(ERenderMode InRenderMode);

    UFUNCTION(BlueprintPure, Category = "XGrids|PointCloud")
    FORCEINLINE FLinearColor GetElevationColorTop() const { return ElevationColorTop; }

    UFUNCTION(BlueprintCallable, Category = "XGrids|PointCloud")
    void SetElevationColorTop(FLinearColor InElevationColorTop);

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE float GetGlobalAlpha() const { return GlobalAlpha; }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetGlobalAlpha(float InGlobalAlpha);

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE float GetGlobalAlpha_PointCloud() const { return GlobalAlpha_PointCloud; }

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetGlobalAlpha_PointCloud(float InGlobalAlpha);

    UFUNCTION(BlueprintPure, Category = "XGrids")
    FORCEINLINE bool GetReplaceTonemap() const { return bReplaceTonemap; }

    // we can't use this function now
    // wu must ensure bReplaceTonemap is true
    // we use SceneExtension to resolve Tonemap Issue,and this need PostProcessMaterial 
    // UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetReplaceTonemap(bool InReplaceTonemap);

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    int GetSplatNumber() const;

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    virtual bool HaveValidSplatData();

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    bool HaveValidCollisionData();

    /**
    * Toggle PointCloud and Normal mode in commandline
    */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void ToggleRenderMode();

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void ToggleShcoef();

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void ToggleLightMode();

    virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    virtual bool CanRender() const;

    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    void SetSaturation(const FVector4 InSaturation);
    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    FORCEINLINE FVector4 GetSaturation() const { return Saturation; }

    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    void SetContrast(const FVector4 InContrast);
    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    FORCEINLINE FVector4 GetContrast() const { return Contrast; }

    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    void SetGamma(const FVector4 InGamma);
    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    FORCEINLINE FVector4 GetGamma() const { return Gamma; }

    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    void SetOffset(const FVector4 InOffset);
    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    FORCEINLINE FVector4 GetOffset() const { return Offset; }

    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    void SetColorTint(const FLinearColor InColor);
    UFUNCTION(BlueprintCallable, Category = "XGrids|Color")
    FORCEINLINE FLinearColor GetColorTint() const { return ColorTint; }

    UFUNCTION(BlueprintPure, Category = "XGrids")
    virtual FMetaInfoBase GetMetaInfo() const;

    /**
     * Force lcc scene update, this will update the lcc scene in the next frame.
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void ForceUpdate();

    /**
     * Set lcc scene collision enable
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetLCCCollisionEnable(const bool InEnable);

    /**
     * Set playerControl load mode,this will change the lcc scene loadmode in the next frame.
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetPlayerLoadMode(class APlayerController* PlayerController, ELoadMode InLoadMode);

    /**
     * Set SceneCapture load mode,this will change the lcc scene loadmode in the next frame.
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetSceneCaptureLoadMode(class USceneCaptureComponent2D* InCapture2D, ELoadMode InLoadMode);

    /**
     * Set playerControl render mode,this will change the lcc scene rendermode in the next frame.
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetPlayerRenderMode(class APlayerController* PlayerController, ERenderMode InRenderMode);

    /**
     * Set SceneCapture render mode,this will change the lcc scene rendermode in the next frame.
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetSceneCaptureRenderMode(class USceneCaptureComponent2D* InCapture2D, ERenderMode InRenderMode);

    /**
     * Modify player transform,this will override this player's transform for this LCCActor.
     * You can use this function before teleport to avoid some node not load.
     * Should use CancelModifyPlayerTransform after teleport
     * eg: ModifyPlayerTransform --> delay a few seconds(like 0.2s) --> teleport -->delay a few seconds(like 0.2s) --> CancelModifyPlayerTransform
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void ModifyPlayerTransform(class APlayerController* PlayerController, FTransform InTransform);

    /**
     * Cancel Modify player transform,this will cancel transform override,just use realtime transform.
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void CancelModifyPlayerTransform(class APlayerController* PlayerController);

    /**
     * Whether the LCC scene is enabled for geo place
     * @param InEnable true:enable geo place,false:disable geo place
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void SetGeoPlacement(bool InEnable);

    /**
     * Get GeoReferencingSystem
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    AGeoReferencingSystem* GetGeoReferencingSystem() const { return GeoReferencingSystem.Get(); };

    /**
     * Check if can use geo place
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    bool CanUseGeoPlace() const;

    /**
     * Get RTK base location base on Meta.lcc
     * @return RTKBaseLocation
     */
    UFUNCTION(BlueprintCallable, Category = "XGrids")
    FVector GetRTKBaseLocation() const;

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void AddClippingVolume(ALCCClippingVolume* InClippingVolume);

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void RemoveClippingVolume(ALCCClippingVolume* InClippingVolume);

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void AddSectionPlane(ALCCSectionPlane* InSectionPlane);

    UFUNCTION(BlueprintCallable, Category = "XGrids")
    void RemoveSectionPlane(ALCCSectionPlane* InSectionPlane);

    /**
     * @return If this actor is sort by distance
     */
    virtual bool NeedSortActor() const;

    FLCCComponentRenderParams GetRenderParams() const;;

    /**
     * Get all clipping volumes in the scene
     */
    TArray<FLCCClippingVolume> GetClipVolumes();

    /**
     * Get all section planes in the scene
     */
    TArray<FLCCSectionPlane> GetSectionPlanes();

protected:
    //override
    virtual void BeginPlay() override;
    virtual void PostLoad() override;
    virtual void OnComponentCreated() override;
    virtual void BeginDestroy() override;
    virtual void OnRegister() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
    virtual void OnUnregister() override;
    virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

    friend class ULCCRenderSystem;
    friend class LCCCollisionManager;
    friend class LCC2CollisionManager;
    friend class LCCCollisionManagerBase;

    void Update(FCameraInfo Camera);
    /**
    * Toggle PointCloud and Normal mode need some change
    */
    void AdjustRenderMode();

    /**
     * Change material by LightMode
     * @param InLightMode Current LightMode
     */
    void ToggleLightModeMaterial(ELightMode InLightMode);

    /**
     * Load lcc scene
     * @param Path Lcc meta.lcc path
     */
    virtual void LoadLCC(const FString& Path);
    void SetActorGeoLocation();
    UFUNCTION()
    void ResetGeoreferencingSystem();
    void LoadCollision();
    /**
     * Create collision manager. called by LoadCollision
     */
    virtual TSharedPtr<LCCCollisionManagerBase> CreateCollisionManager();
    void SetAntiAliasingMethod() const;

    friend class LCCRendering;
    friend class FLCC2SceneProxy;

    virtual void BeginFrame(FCameraInfo& Camera, const FRenderInfo& InRenderInfo);

    /**
     * Get collision manager
     */
    LCCCollisionManagerBase* GetCollisionManager() const;

    /**
     * Check if meta info is valid.
     */
    virtual bool IsMetaInfoValid() const;
	
    /**
     * Add offset for actor when lcc use geo position
     */
    void SetGeoOffset(const FVector& LocationOffset, const FRotator& RotatorOffset) const;


#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
    virtual bool CanEditChange(const FProperty* InProperty) const override;

#endif

    virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* InMaterial) override;
    virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

    //CollisionManager need call UpdateCollision
    friend class LCCCollisionManager;
    void UpdateCollision(const bool InUseAsync);
    void WaitForAsyncCookComplete();
    void ClearCollision();
    void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* InBodySetup);
    virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;
    virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;
    virtual bool GetTriMeshSizeEstimates(struct FTriMeshCollisionDataEstimates& OutTriMeshEstimates,
                                         bool bInUseAllTriData) const override;
    virtual bool PollAsyncPhysicsTriMeshData(bool InUseAllTriData) const override;
    virtual bool WantsNegXTriMesh() override;
    virtual void GetMeshId(FString& OutMeshId) override;
    virtual UBodySetup* GetBodySetup() override;
    UBodySetup* CreateBodySetupHelper();
    bool SetCollisionData(const TArray<FVector3f>& Vertices, const TArray<FTriIndices>& Indices);

    UPROPERTY(Transient)
    TObjectPtr<UMaterialInterface> Material;
    UPROPERTY(Transient)
    TObjectPtr<UMaterialInterface> BaseMaterial_Unlit;
    UPROPERTY(Transient)
    TObjectPtr<UMaterialInterface> BaseMaterial_Lit;
    UPROPERTY(Transient)
    TObjectPtr<UMaterialInterface> ReplaceTonemapMaterial;
    UPROPERTY(Transient)
    TObjectPtr<UMaterialInterface> BaseMaterial_ReceiveShadows;
    UPROPERTY(Transient)
    TObjectPtr<UPostProcessComponent> PostProcessComponent;
    UPROPERTY(Transient)
    TObjectPtr<class UBodySetup> BodySetup;
    /** Queue for async body setups that are being cooked */
    UPROPERTY(transient)
    TArray<TObjectPtr<UBodySetup>> AsyncBodySetupQueue;
    /** Shared cancel flag for the async physics cook thread */
    FEvent* AsyncCookDoneEvent = nullptr;
    bool CacheShcoef;
    ELightMode CacheLightMode;

    TSharedPtr<LCCCollisionManagerBase> CollisionManager;
    //lcc file path without filename
    FString WorkPath;
    FString CurrentLCCPath;
    FBoxSphereBounds LocalBounds;
    //Even if camera and renderInfo not change,wo wish refresh lcc scene
    bool bForceUpdate;
    //Last transform,if transform change,need update lcc scene
    FTransform LastTransform;
    //if bForceUpdate and transform change has been applied,consider multi camera
    //make sure all camera has been applied
    bool bAlreadyApplyChange;
    //Every Player can have its own LoadMode
    TMap<int32, ELoadMode> PlayerLoadModeMap;
    //Every Player can have its own RenderMode
    TMap<int32, ERenderMode> PlayerRenderModeMap;
    //If the Player needs to teleport, at the moment of teleportation, there will be a situation where only the environment node is loaded and the main node is still not rendered.
    //Therefore, by providing this attribute, users can set the position of the Player to the destination in advance for all nodes to load before teleportation, and then teleport it over without flickering 
    TMap<int32, FCameraInfo> PlayerCameraMap;
    FDelegateHandle OnLoadModeSetDel;
    FDelegateHandle OnRenderModeSetDel;
    //Collision type for lcc scene
    ECollisionType CollisionType;
    //CollisionManager need update once at least
    //for example,LCCActor is hidden at begin and collision will not load
    //when lccActor need show then collision load will cause lag
    bool AtLeastUpdateOnce;
    UPROPERTY(Transient)
    TObjectPtr<AGeoReferencingSystem> GeoReferencingSystem;
    FVector OriginLocation;
    FRotator OriginRotation;
    bool bFullLoad;
    TQueue<TArray<FVector3f>> CollisionVertices;
    TQueue<TArray<FTriIndices>> CollisionIndices;
    double FirstRenderTime;
};
