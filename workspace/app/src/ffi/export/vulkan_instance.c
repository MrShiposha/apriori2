#include <assert.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

#include "ffi/log.h"

#include "vulkan_instance.h"
#include "ffi/app_info.h"
#include "ffi/result_fns.h"

#include "ffi/util.h"
#include "ffi/def.h"

#ifdef ___windows___
#   define VULKAN_PLATFORM_EXTENSION MACRO_EXPAND(VK_KHR_WIN32_SURFACE_EXTENSION_NAME)
#elif ___macos___
#   define VULKAN_PLATFORM_EXTENSION MACRO_EXPAND(VK_EXT_metal_surface)
#elif ___linux___
#   error "linux is not supported yet"
#elif ___unknown___
#   error "this target OS is not supported yet"
#endif // os

struct VulkanInstanceFFI {
    VkInstance vk_handle;
};

Result new_vk_instance() {
    VulkanInstance instance = malloc(sizeof(VulkanInstance));
    if (instance == NULL)
        return apriori2_error(OUT_OF_MEMORY);

    VkApplicationInfo app_info = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = APRIORI2_APPLICATION_NAME,
        .applicationVersion = APRIORI2_VK_VERSION
    };

    const char *layer_names[] = {
        "VK_LAYER_LUNARG_standard_validation"
     };
    const char *extension_names[] = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VULKAN_PLATFORM_EXTENSION

#   ifdef ___debug___
        , VK_EXT_DEBUG_REPORT_EXTENSION_NAME
#   endif // ___debug___
     };

    // TODO check layers and extensions are availible

    VkInstanceCreateInfo instance_ci = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &app_info,
        .enabledLayerCount = STATIC_ARRAY_SIZE(layer_names),
        .enabledExtensionCount = STATIC_ARRAY_SIZE(extension_names),
        .ppEnabledLayerNames = layer_names,
        .ppEnabledExtensionNames = extension_names
    };

    VkResult error = vkCreateInstance(&instance_ci, NULL, &instance->vk_handle);

    return new_vk_result(instance, error);
}

Handle vk_handle(VulkanInstance instance) {
    if (instance == NULL)
        return NULL;
    else
        return instance->vk_handle;
}

void drop_vk_instance(VulkanInstance instance) {
    if (instance == NULL)
        return;

    vkDestroyInstance(instance->vk_handle, NULL);
    free(instance);
}