#ifndef ___APRIORI2_RESULT_FNS_H___
#define ___APRIORI2_RESULT_FNS_H___

#include <vulkan/vulkan.h>

#include "result.h"

Result new_result(void *object, Apriori2Error error);
Result new_vk_result(void *object, VkResult error);

Result apriori2_error(Apriori2Error error);
Result vulkan_error(VkResult error);

#endif // ___APRIORI2_RESULT_FNS_H___