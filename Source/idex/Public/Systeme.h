#pragma once

#include <iostream>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Systeme.generated.h"

using namespace std;


UCLASS ()
class IDEX_API USysteme: public UBlueprintFunctionLibrary
{
    GENERATED_BODY ()

    UFUNCTION (BlueprintCallable, Category = "IDEX | Systeme")
    static bool executer (
        FString executable,
        FString parametres,
        bool masque
    );
};
