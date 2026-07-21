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
//clip volume max num
#define LCC_MAX_CLIPPING_VOLUME 500
//section plane max num
#define LCC_MAX_SECTION_PLANE 500
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
#define LCC_AUTH_URL_FOREIGN TEXT("https://api-gw.xgrids.com/lixel-front-api/dev/sdk/authentication")
#define LCC_REGISTER_URL_FOREIGN TEXT("https://developer.xgrids.com/#/authentication")
#define LCC_DOC_URL_FOREIGN TEXT("https://developer.xgrids.com/#/document?titleId=en-1720509312452")
#define LCC_TUTORIAL_URL_FOREIGN TEXT("https://developer.xgrids.com/#/tutorial?page=UE_SDK")
#define LCC_SUPPORT_URL_FOREIGN TEXT("https://developer.xgrids.com/#/forum")
#define LCC_CHANGELOG_URL_FOREIGN TEXT("https://developer.xgrids.com/#/document?titleId=en-1720509717058")
#define LCC_HOME_URL_FOREIGN TEXT("https://developer.xgrids.com/#/")

//Domestic website
#define LCC_AUTH_URL_DOMESTIC TEXT("https://api-gw.xgrids.cloud/lixel-front-api/dev/sdk/authentication")
#define LCC_REGISTER_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/authentication")
#define LCC_DOC_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/document?titleId=cn-1720170162723")
#define LCC_TUTORIAL_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/tutorial?page=UE_SDK")
#define LCC_SUPPORT_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/forum")
#define LCC_CHANGELOG_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/document?titleId=cn-1720170723795")
#define LCC_HOME_URL_DOMESTIC TEXT("https://developer.xgrids.cn/#/")

//Stg website
#define LCC_AUTH_URL_STG TEXT("https://stg-api-gw.xgrids.cloud/lixel-front-api/dev/sdk/authentication")

//watermark image
#define LCC_WATER_MARK_IMAGE "iVBORw0KGgoAAAANSUhEUgAAAE4AAAANCAYAAAAHZljfAAAAAXNSR0IArs4c6QAAAARzQklUCAgICHwIZIgAAAL6SURBVEiJ3Zetk+JAEMV/vbUCGRmJjFyJjEQikciVJ+/PWLkyEolEIpFI5MrIyLh3YnqWYUhCrm7VvaqpgqR7uvtNf0yQVEsqmAFJW0lvc2T/d5iTtgX2ZtYBSKqALzPr/fcSOAEF0Ee5n8DIofVm1s+Q+0buk6RFuoekBbCYsjHgW65z03WBFVADjZm1kmqgAvYuuHNDnxNGVsAK+BwIuvQ9GjNr/VkFrAmHkePLzJpEvyIc7hT2ZnZ1+Tdglfor6TePJPTA2cxOmb8LYEPgYAj9K4CZnV14J6kxs5OkZQzW105SFZ0bwJVAXNyjdyciadeEtOjYxfVy5Bm98GeHEdtb7kkpeCRpARyBNvlfAivPzmMiW/u7ZsReIA7AyQIPnJBt79wy5WNkk6jfud4u2aPgRloadOU6R/4CZvY19FzSZMklaLM9rpKuwLuk1swu/nwJXMbsAby44UpS6Sl7IQRbcGN851kyCe8zDeE0dwyTFvHQw9I1ZUfSwuVKbysFw5n7FF4FV+7LsgXeJC3H/HpNBN8lHc3sGMuWQMInoRTWjJdK6kgn6eD63Qhpd/Dg6+zZIcmAHGsgne7HZ43+CVpClkWcuB38HSR1QBN7XCfpBGwkFWZ2kLRxxU8za7z5P4WfysadKSRtZpB3JmR6xI7hoRFx4hZo8wNTfknSV32/j5HMXwPbl0T47A7VklYe7JVQpoW/n4Qb2hHKsPFV+SGk6Emat5n1ZtbFlcgMImkJANs5bWTC5xLvaUN28uVy5asrvxN6URwQa2+W35nnk3L0ZHPSvHTaODAk1cnYb4GFpDWPvWlJyLaWCQwNoxnlWnp8ERWh5O8GgccylvE18BV73IlwcnG69oSybTLyHu5oCWIp71MZvxc2rn81szbpg+tEL6IDDtlE6xnIwIy8Eog6HY9Xmt7t5bYe7nGEnl4ORhl09hbvZn5vq+PF0/9/l4438Py+88/I+8hYVudfAnPfpTLM/HKY/GKIOpJ+eZ0/haTVXNn/HX8AWSQLzxm37JIAAAAASUVORK5CYII="
