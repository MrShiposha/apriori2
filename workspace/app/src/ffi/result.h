#ifndef ___APRIORI2_RESULT_H___
#define ___APRIORI2_RESULT_H___

#include "error.h"
#include "def.h"

// TODO logs
#define RESULT_UNWRAP(out_object, result) do { \
    if ( \
        (result).error.tag == Apriori2 \
        && (result).error.code != SUCCESS \
    ) { \
        (result).object = NULL; \
        (out_object) = NULL; \
        goto failure; \
    } \
    else if ( \
        (result).error.tag == Vulkan \
        && (result).error.code != VK_SUCCESS \
    ) { \
        (result).object = NULL; \
        (out_object) = NULL; \
        goto failure; \
    } \
    else (out_object) = (result).object; \
} while(0)

typedef struct Result {
    ErrorDescriptor error;
    Handle object;
} Result;

#endif // ___APRIORI2_RESULT_H___