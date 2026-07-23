/*********************************************
 * Copyright: XGrids Corporation
 * Author   : Kiro
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "LCCActorBase.h"
#include "PlyActor.generated.h"

class ULCC2Component;

/**
 * Dedicated actor for loading and rendering standalone .ply files.
 * Internally uses ULCC2Component via a virtual FLCC2MetaInfo to reuse the full LCC2 rendering pipeline.
 */
UCLASS(BlueprintType)
class LCC4UNREALRUNTIME_API APlyActor : public ALCCActorBase
{
    GENERATED_UCLASS_BODY()

public:
    /** Open file dialog filtered for .ply files */
    virtual void SelectFile() override;

    /** Load a standalone .ply file. Rejects any path whose extension is not .ply. */
    virtual void Load(const FString& String) const override;
};
