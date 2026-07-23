/*********************************************
 * Copyright: XGrids Corporation
 * Author   : Feng HaiLiang
 * ******************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLCC, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(LogLCC2, Log, All);

#define LCC_LOG(Format, ...) UE_LOG(LogLCC, Log, TEXT(Format), ##__VA_ARGS__)
#define LCC_LOG(Format, ...) UE_LOG(LogLCC, Log, TEXT(Format), ##__VA_ARGS__)
#define LCC_WARNING(Format, ...) UE_LOG(LogLCC, Warning, TEXT(Format), ##__VA_ARGS__)
#define LCC_ERROR(Format, ...) UE_LOG(LogLCC, Error, TEXT(Format), ##__VA_ARGS__)
#define LCC_DISPLAY(Format, ...) UE_LOG(LogLCC, Display, TEXT(Format), ##__VA_ARGS__)
#define LCC_FATAL(Format, ...) UE_LOG(LogLCC, Fatal, TEXT(Format), ##__VA_ARGS__)
#define LCC_VERBOSE(Format, ...) UE_LOG(LogLCC, Verbose, TEXT(Format), ##__VA_ARGS__)

#define LCC2_LOG(Format, ...) UE_LOG(LogLCC2, Log, TEXT(Format), ##__VA_ARGS__)
#define LCC2_LOG(Format, ...) UE_LOG(LogLCC2, Log, TEXT(Format), ##__VA_ARGS__)
#define LCC2_WARNING(Format, ...) UE_LOG(LogLCC2, Warning, TEXT(Format), ##__VA_ARGS__)
#define LCC2_ERROR(Format, ...) UE_LOG(LogLCC2, Error, TEXT(Format), ##__VA_ARGS__)
#define LCC2_DISPLAY(Format, ...) UE_LOG(LogLCC2, Display, TEXT(Format), ##__VA_ARGS__)
#define LCC2_FATAL(Format, ...) UE_LOG(LogLCC2, Fatal, TEXT(Format), ##__VA_ARGS__)
#define LCC2_VERBOSE(Format, ...) UE_LOG(LogLCC2, Verbose, TEXT(Format), ##__VA_ARGS__)

//similar to UE_SMALL_NUMBER,but bigger
#define LCC_SMALL_NUMBER (1.e-4f)
//represents any value
#define LCC_ANY_VALUE -1
//meter to centimeters
#define METER_TO_CENTIMETERS 100
//use quad for lcc splat,higher performance
#define LCC_USE_QUAD 1
//use ellipsoid for splat,low performance
#define LCC_USE_ELLIPSOID 0
//Lcc Render max distance
#define LCC_MAX_DISTANCE 300
//LCC max splat num
#define LCC_MAX_SPLAT 3000
//LCC max load collision data distance
#define LCC_MAX_COLLISION_DISTANCE 50
//default add extra preload
#define LCC_ADD_EXTRA_PRELOAD 1
//full load splat num
#define LCC_FULL_LOAD_Num 1500

//Foreign website
#define LCC_REGISTER_URL_FOREIGN TEXT("https://developer.xgrids.com/#/console/SDKAuthorization")
#define LCC_DOC_URL_FOREIGN TEXT("https://developer.xgrids.com/#/document?titleId=en-1720509312452")
#define LCC_TUTORIAL_URL_FOREIGN TEXT("https://developer.xgrids.com/#/tutorial?page=UE_SDK")
#define LCC_SUPPORT_URL_FOREIGN TEXT("https://developer.xgrids.com/#/forum")
#define LCC_CHANGELOG_URL_FOREIGN TEXT("https://developer.xgrids.com/#/document?titleId=en-1720509717058")
#define LCC_HOME_URL_FOREIGN TEXT("https://developer.xgrids.com/#/")

//Domestic website
#define LCC_REGISTER_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/console/SDKAuthorization")
#define LCC_DOC_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/document?titleId=cn-1720170162723")
#define LCC_TUTORIAL_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/tutorial?page=UE_SDK")
#define LCC_SUPPORT_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/forum")
#define LCC_CHANGELOG_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/document?titleId=cn-1720170723795")
#define LCC_HOME_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/")

