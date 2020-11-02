use super::{ffi, Result};

pub struct VulkanInstance {
    pub instance_ffi: ffi::VulkanInstance
}

impl VulkanInstance {
    pub fn new() -> Result<Self> {
        let instance;
        unsafe  {
            instance = Self {
                instance_ffi: ffi::new_vk_instance().try_unwrap()?
            };
        }

        Ok(instance)
    }
}