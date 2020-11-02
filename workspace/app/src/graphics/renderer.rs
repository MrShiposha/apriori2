use crate::{
    ffi,
    core::{Result, VulkanInstance}
};

pub struct Renderer {
    renderer_ffi: ffi::Renderer
}

impl Renderer {
    pub fn new(vk_instance: &VulkanInstance) -> Result<Self> {
        let renderer;
        unsafe {
            renderer = Self {
                renderer_ffi: ffi::new_renderer(
                    vk_instance.instance_ffi
                ).try_unwrap()?
            }
        }

        Ok(renderer)
    }
}

impl Drop for Renderer {
    fn drop(&mut self) {
        unsafe  {
            ffi::drop_renderer(self.renderer_ffi);
        }
    }
}