/*********************************************
 * Copyright: XGrids Corporation
 * Author   : Kiro
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "LCCActorBase.h"
#include "SpzActor.generated.h"

class ULCC2Component;

/**
 * Dedicated actor for loading and rendering standalone .spz files.
 * Internally uses ULCC2Component via a virtual FLCC2MetaInfo to reuse the full LCC2 rendering pipeline.
 */
UCLASS(BlueprintType)
class LCC4UNREALRUNTIME_API ASpzActor : public ALCCActorBase
{
    GENERATED_UCLASS_BODY()

public:
    /** Open file dialog filtered for .spz files */
    virtual void SelectFile() override;
};
