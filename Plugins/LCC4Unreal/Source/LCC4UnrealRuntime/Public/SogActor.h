/*********************************************
 * Copyright: XGrids Corporation
 * Author   : Kiro
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "LCCActorBase.h"
#include "SogActor.generated.h"

class ULCC2Component;

/**
 * Dedicated actor for loading and rendering standalone .sog files.
 * Internally uses ULCC2Component via a virtual FLCC2MetaInfo to reuse the full LCC2 rendering pipeline.
 */
UCLASS(BlueprintType)
class LCC4UNREALRUNTIME_API ASogActor : public ALCCActorBase
{
    GENERATED_UCLASS_BODY()

public:
    /** Open file dialog filtered for .sog files */
    virtual void SelectFile() override;
};
