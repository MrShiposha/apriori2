#ifndef ___APRIORI2_ERROR_H___
#define ___APRIORI2_ERROR_H___

#include <stdint.h>

typedef int32_t ErrorCode;

typedef enum Apriori2Error {
    SUCCESS = 0,
    OUT_OF_MEMORY,
    DEBUG_REPORTER_CREATION,
    LAYERS_NOT_FOUND,
    EXTENSIONS_NOT_FOUND
} Apriori2Error;

typedef enum ErrorTag {
    Apriori2,
    Vulkan
} ErrorTag;

typedef struct ErrorDescriptor {
    ErrorTag tag;
    ErrorCode code;
} ErrorDescriptor;

#endif // ___APRIORI2_ERROR_H___