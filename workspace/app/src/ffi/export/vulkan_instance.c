#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

Result check_all_layers_available(const char **layers, uint32_t num_layers) {
    ErrorTag tag = Vulkan;
    ErrorCode err = SUCCESS;

    VkLayerProperties *layer_props = NULL;

    uint32_t property_count = 0;
    tag = Vulkan;
    err = vkEnumerateInstanceLayerProperties(&property_count, NULL);
    if (err != VK_SUCCESS) {
        goto exit;
    }

    tag = Apriori2;
    layer_props = malloc(property_count * sizeof(VkLayerProperties));
    if (layer_props == NULL) {
        err = OUT_OF_MEMORY;
        goto exit;
    }

    tag = Vulkan;
    err = vkEnumerateInstanceLayerProperties(&property_count, layer_props);
    if (err != VK_SUCCESS)
        goto exit;

    tag = Apriori2;
    for (uint32_t i = 0, j = 0; i < num_layers; ++i) {
        for (j = 0; j < property_count; ++j) {
            if (!strcmp(layers[i], layer_props[j].layerName))
                break;
        }

        // Some layer was not found
        if (j == property_count) {
            err = LAYERS_NOT_FOUND;
            error("Vulkan Instance", "Layer \"%s\" is not found", layers[i]);
        }
    }

exit:
    free(layer_props);
    return tag_error(tag, err);
}

Result check_all_extensions_available(const char **extensions, uint32_t num_extensions) {
    ErrorTag tag = Vulkan;
    ErrorCode err = SUCCESS;
    VkExtensionProperties *extension_props = NULL;

    uint32_t property_count = 0;
    tag = Vulkan;
    err = vkEnumerateInstanceExtensionProperties(NULL, &property_count, NULL);
    if (err != VK_SUCCESS) {
        goto exit;
    }

    tag = Apriori2;
    extension_props = malloc(property_count * sizeof(VkLayerProperties));
    if (extension_props == NULL) {
        err = OUT_OF_MEMORY;
        goto exit;
    }

    tag = Vulkan;
    err = vkEnumerateInstanceExtensionProperties(NULL, &property_count, extension_props);
    if (err != VK_SUCCESS)
        goto exit;

    tag = Apriori2;
    for (uint32_t i = 0, j = 0; i < num_extensions; ++i) {
        for (j = 0; j < property_count; ++j) {
            if (!strcmp(extensions[i], extension_props[j].extensionName))
                break;
        }

        // Some extensions was not found
        if (j == property_count) {
            err = LAYERS_NOT_FOUND;
            error("Vulkan Instance", "Layer \"%s\" is not found", extensions[i]);
        }
    }

exit:
    free(extension_props);
    return tag_error(tag, err);
}

Result new_vk_instance() {
    VulkanInstance instance = malloc(sizeof(VulkanInstance));
    if (instance == NULL)
        return apriori2_error(OUT_OF_MEMORY);

    static VkApplicationInfo app_info = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = APRIORI2_APPLICATION_NAME,
        .applicationVersion = APRIORI2_VK_VERSION
    };

#   ifdef ___debug___
    const char *layer_names[] = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    const uint32_t layer_names_count = STATIC_ARRAY_SIZE(layer_names);
#   else
    const char *layer_names = NULL;
    const uint32_t layer_names_count = 0;
#   endif // ___debug___

    const char *extension_names[] = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VULKAN_PLATFORM_EXTENSION

#   ifdef ___debug___
        , VK_EXT_DEBUG_REPORT_EXTENSION_NAME
#   endif // ___debug___
    };

    Result result = check_all_layers_available(
        layer_names,
        layer_names_count
    );
    if (result.error.code != SUCCESS)
        goto failure;

    result = check_all_extensions_available(
        extension_names,
        STATIC_ARRAY_SIZE(extension_names)
    );
    if (result.error.code != SUCCESS)
        goto failure;

    VkInstanceCreateInfo instance_ci = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &app_info,
        .enabledLayerCount = layer_names_count,
        .enabledExtensionCount = STATIC_ARRAY_SIZE(extension_names)
    };
    instance_ci.ppEnabledLayerNames = layer_names;
    instance_ci.ppEnabledExtensionNames = extension_names;

    VkResult err = vkCreateInstance(&instance_ci, NULL, &instance->vk_handle);

    return new_vk_result(instance, err);

failure:
    free(instance);

    error(
        "Vulkan Instance",
        "instance creation failed: tag = %d, error = %d",
        result.error.tag, result.error.code
    );
    return result;
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