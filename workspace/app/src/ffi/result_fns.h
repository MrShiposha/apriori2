#ifndef ___APRIORI2_RESULT_FNS_H___
#define ___APRIORI2_RESULT_FNS_H___

#include <vulkan/vulkan.h>

#include "def.h"
#include "result.h"

Result new_result(Handle object, Apriori2Error error);
Result new_vk_result(Handle object, VkResult error);
Result new_tag_result(Handle object, ErrorTag tag, ErrorCode error);

Result apriori2_success();
Result tag_error(ErrorTag tag, ErrorCode error);
Result apriori2_error(Apriori2Error error);
Result vulkan_error(VkResult error);

#endif // ___APRIORI2_RESULT_FNS_H___