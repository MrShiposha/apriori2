#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <vulkan/vulkan.h>

#include "renderer.h"
#include "ffi/def.h"
#include "ffi/log.h"
#include "ffi/export/vulkan_instance.h"
#include "ffi/result_fns.h"

struct RendererFFI {
    VulkanInstance vk_instance;
};

Result new_renderer(VulkanInstance vulkan_instance) {
    Renderer renderer = malloc(sizeof(struct RendererFFI));
    if (renderer == NULL)
        return apriori2_error(OUT_OF_MEMORY);

    renderer->vk_instance = vulkan_instance;

    return new_result(renderer, SUCCESS);
}

void drop_renderer(Renderer renderer) {
    if (renderer == NULL)
        return;

    drop_vk_instance(renderer->vk_instance);
    free(renderer);
}