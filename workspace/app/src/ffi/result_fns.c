#include "result_fns.h"

Result new_result(void *object, Apriori2Error error) {
    ErrorDescriptor error_desc = {
        .tag = Apriori2,
        .code = (ErrorCode)error
    };

    Result result = {
        .error = error_desc,
        .object = object
    };

    return result;
}

Result new_vk_result(void *object, VkResult error) {
    ErrorDescriptor error_desc = {
        .tag = Vulkan,
        .code = (uint32_t)error
    };

    Result result = {
        .error = error_desc,
        .object = object
    };

    return result;
}

Result apriori2_error(Apriori2Error error) {
    return new_result(NULL, error);
}

Result vulkan_error(VkResult error) {
    return new_vk_result(NULL, error);
}