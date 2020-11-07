#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <vulkan/vulkan.h>

#include "ffi/export/renderer.h"
#include "renderer.h"
#include "vulkan_instance.h"
#include "ffi/def.h"
#include "ffi/log.h"
#include "ffi/error.h"
#include "ffi/export/vulkan_instance.h"
#include "ffi/result_fns.h"

uint32_t rate_phy_device_suitability(VkPhysicalDevice device) {
    uint32_t score = 0;
    VkPhysicalDeviceProperties dev_props = { 0 };
    vkGetPhysicalDeviceProperties(device, &dev_props);

    switch(dev_props.deviceType) {
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
        score += 1000;
        break;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
        score += 100;
        break;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
        score += 10;
        break;
    }

    return score;
}

VkPhysicalDevice select_phy_device(VulkanInstance instance) {
    uint32_t score = 0;
    uint32_t current_score = 0;
    VkPhysicalDevice winner_device = VK_NULL_HANDLE;

    for (uint32_t i = 0; i < instance->phy_device_count; ++i) {
        current_score = rate_phy_device_suitability(
            instance->phy_devices[i]
        );

        if (current_score > score) {
            score = current_score;
            winner_device = instance->phy_devices[i];
        }
    }

    assert(
        winner_device != VK_NULL_HANDLE
        && "Renderer: physical device must be selected"
    );

    return winner_device;
}

Apriori2Error init_renderer_queues(struct RendererQueues *queues, VkPhysicalDevice device) {
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(
        device,
        &queue_family_count,
        NULL
    );

    VkQueueFamilyProperties *family_props = calloc(
        queue_family_count, sizeof(VkQueueFamilyProperties)
    );
    if (family_props == NULL)
        return OUT_OF_MEMORY;

    vkGetPhysicalDeviceQueueFamilyProperties(
        device,
        &queue_family_count,
        family_props
    );

    bool is_graphics_queue_found = false;

    VkQueueFamilyProperties *current = NULL;
    for (uint32_t i = 0; i < queue_family_count; ++i) {
        current = family_props + i;

        if (current->queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queues->graphics_idx = i;
            is_graphics_queue_found = true;
        }
    }

    free(family_props);

    if (!is_graphics_queue_found) {
        return GRAPHICS_QUEUE_FAMILY_NOT_FOUND;
    } else {
        return SUCCESS;
    }
}

Result new_renderer(VulkanInstance vulkan_instance) {
    Result result = { 0 };

    result.object = calloc(1, sizeof(struct RendererFFI));
    if (result.object == NULL) {
        result.error = OUT_OF_MEMORY;
        goto failure;
    }

    Renderer renderer = AS(result.object, Renderer);
    renderer->vk_instance = vulkan_instance;

    VkPhysicalDevice phy_device = select_phy_device(vulkan_instance);
    result.error = init_renderer_queues(&renderer->queues, phy_device);
    EXPECT_SUCCESS(result);

    return result;

failure:
    drop_renderer(result.object);

    return result;
}

void drop_renderer(Renderer renderer) {
    if (renderer == NULL)
        return;

    free(renderer);
}