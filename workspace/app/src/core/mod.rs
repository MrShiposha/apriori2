pub mod vulkan_instance;

use crate::ffi;

pub use vulkan_instance::VulkanInstance;

#[derive(Debug)]
pub enum Error {
    Apriori2FFI(ffi::ErrorCode),
    VulkanFFI(ffi::ErrorCode)
}

impl ffi::ErrorDescriptor {
    pub fn is_success(&self) -> bool {
        self.code == ffi::Apriori2Error_SUCCESS
    }
}

impl From<ffi::ErrorDescriptor> for Error {
    fn from(err: ffi::ErrorDescriptor) -> Self {
        match err.tag {
            ffi::ErrorTag_Apriori2 => Self::Apriori2FFI(err.code),
            ffi::ErrorTag_Vulkan => Self::VulkanFFI(err.code),
            _ => unreachable!("unknown error tag"),
        }
    }
}

pub type Result<T> = std::result::Result<T, Error>;

impl ffi::Result {
    pub fn try_unwrap<T>(&self) -> Result<*mut T> {
        let result;
        unsafe {
            if self.error.is_success() {
                result = std::mem::transmute::<ffi::Handle, *mut T>(self.object);
            } else {
                return Err(self.error.into())
            }
        }

        Ok(result)
    }
}