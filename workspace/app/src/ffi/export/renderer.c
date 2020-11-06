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
};

Result new_renderer(VulkanInstance vulkan_instance) {
    Result result = { 0 };

    result.object = calloc(1, sizeof(struct RendererFFI));
    if (result.object == NULL) {
        result.error = OUT_OF_MEMORY;
        drop_renderer(result.object);
    } else {
        AS(result.object, Renderer)->vk_instance = vulkan_instance;
    }

    return result;
}

void drop_renderer(Renderer renderer) {
    if (renderer == NULL)
        return;

    free(renderer);
}