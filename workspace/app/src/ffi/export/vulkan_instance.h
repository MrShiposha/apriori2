#ifndef ___APRIORI2_VULKAN_INSTANCE_H___
#define ___APRIORI2_VULKAN_INSTANCE_H___

#include "ffi/result.h"

typedef struct VulkanInstanceFFI *VulkanInstance;

Result new_vk_instance();

Handle vk_handle(VulkanInstance instance);

void drop_vk_instance(VulkanInstance instance);

#endif // ___APRIORI2_VULKAN_INSTANCE_H___