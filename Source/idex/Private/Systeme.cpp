#include <iostream>
#include "Systeme.h"

using namespace std;


bool USysteme:: executer (
    FString executable,
    FString parametres,
    bool masque
) {
    FProcHandle resultat = FPlatformProcess:: CreateProc (
        * executable,
        * parametres,
        false,
        masque,
        masque,
        nullptr,
        0,
        nullptr,
        nullptr,
        nullptr
    );
    return resultat. IsValid ();
}
