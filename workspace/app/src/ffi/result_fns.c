#include "result_fns.h"

Result new_tag_result(Handle object, ErrorTag tag, ErrorCode error) {
    ErrorDescriptor error_desc = { 0 };
    error_desc.tag = tag;
    error_desc.code = error;

    Result result = { 0 };
    result.error = error_desc;
    result.object = object;

    return result;
}

Result new_result(Handle object, Apriori2Error error) {
    return new_tag_result(object, Apriori2, (ErrorCode)error);
}

Result new_vk_result(Handle object, VkResult error) {
    return new_tag_result(object, Vulkan, (ErrorCode)error);
}

Result apriori2_success() {
    return new_result(NULL, SUCCESS);
}

Result tag_error(ErrorTag tag, ErrorCode error) {
    return new_tag_result(NULL, tag, error);
}

Result apriori2_error(Apriori2Error error) {
    return new_result(NULL, error);
}

Result vulkan_error(VkResult error) {
    return new_vk_result(NULL, error);
}