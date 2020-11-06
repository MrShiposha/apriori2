#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <vulkan/vulkan.h>

#include "renderer.h"
#include "ffi/def.h"
#include "ffi/log.h"
#include "ffi/error.h"
#include "ffi/export/vulkan_instance.h"
#include "ffi/result_fns.h"

struct RendererFFI {
    VulkanInstance vk_instance;
    uint32_t phy_device_count;
    VkPhysicalDevice *phy_devices;
};

Result new_renderer(VulkanInstance vulkan_instance) {
    Result result = { 0 };

    Renderer renderer = calloc(1, sizeof(struct RendererFFI));
    if (renderer == NULL) {
        result.error = OUT_OF_MEMORY;
        goto failure;
    }
    result.object = renderer;

    renderer->vk_instance = vulkan_instance;

    result.error = vkEnumeratePhysicalDevices(
        vk_handle(renderer->vk_instance),
        &renderer->phy_device_count,
        NULL
    );
    if (result.error != VK_SUCCESS)
        goto failure;

    renderer->phy_devices = calloc(
        renderer->phy_device_count,
        sizeof(VkPhysicalDevice)
    );
    if (renderer->phy_devices == NULL) {
        result.error = OUT_OF_MEMORY;
        goto failure;
    }

    result.error = vkEnumeratePhysicalDevices(
        vk_handle(renderer->vk_instance),
        &renderer->phy_device_count,
        renderer->phy_devices
    );
    if (result.error != VK_SUCCESS)
        goto failure;

    return new_result(renderer, SUCCESS);

failure:
    drop_renderer(result.object);

    return result;
}

void drop_renderer(Renderer renderer) {
    if (renderer == NULL)
        return;

    free(renderer->phy_devices);
    free(renderer);
}