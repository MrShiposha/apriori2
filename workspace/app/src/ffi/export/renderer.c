#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <vulkan/vulkan.h>

#include "renderer.h"
#include "ffi/log.h"
#include "ffi/export/vulkan_instance.h"
#include "ffi/result_fns.h"

#ifdef ___debug___
#   include "ffi/vk_debug_reporter.h"

    VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(
        VkFlags flags,
        VkDebugReportObjectTypeEXT object_type,
        uint64_t source_object,
        size_t location,
        uint32_t message_code,
        const char *layer_prefix,
        const char *message,
        void *user_data
    ) {
        if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
            error("VULKAN ERROR", "%s: %s, code = %d\n", layer_prefix, message, message_code);
        } else if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
            warn("VULKAN WARNING", "%s: %s, code = %d\n", layer_prefix, message, message_code);
        } else if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
            info("VULKAN INFO", "%s: %s, code = %d\n", layer_prefix, message, message_code);
        } else if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
            warn("VULKAN PERF WARNING", "%s: %s, code = %d\n", layer_prefix, message, message_code);
        } else if (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
            debug("VULKAN DEBUG", "%s: %s, code = %d\n", layer_prefix, message, message_code);
        }

        // See PFN_vkDebugReportCallbackEXT in Vulkan spec.
        // Quote: The application should always return VK_FALSE.
        //        The VK_TRUE value is reserved for use in layer development.
        return VK_FALSE;
    }
#endif // ___debug___

struct RendererFFI {
    Handle vk_instance;

#ifdef ___debug___
    DebugReporter *dbg_reporter;
#endif // ___debug___
};

Result new_renderer(Handle vulkan_instance) {
    Renderer renderer = malloc(sizeof(struct RendererFFI));
    if (renderer == NULL)
        return apriori2_error(OUT_OF_MEMORY);

    Result result = apriori2_error(SUCCESS);

    renderer->vk_instance = vulkan_instance;

#ifdef ___debug___
    result = new_debug_reporter(
        renderer->vk_instance,
        debug_report
    );

    RESULT_UNWRAP(renderer->dbg_reporter, result);
#endif // ___debug___

    return result;

failure:
    drop_renderer(renderer);
    return result;
}

void drop_renderer(Renderer renderer) {
    if (renderer == NULL)
        return;

#ifdef ___debug___
    drop_debug_reporter(renderer->dbg_reporter);
#endif // ___debug___

    drop_vk_instance(renderer->vk_instance);
    free(renderer);
}