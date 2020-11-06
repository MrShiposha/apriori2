pub mod vulkan_instance;
pub mod log;

use crate::ffi;

pub use vulkan_instance::VulkanInstance;

#[derive(Debug)]
pub enum Error {
    Apriori2FFI(ffi::Apriori2Error)
}

impl From<ffi::Apriori2Error> for Error {
    fn from(err: ffi::Apriori2Error) -> Self {
        Self::Apriori2FFI(err)
    }
}

pub type Result<T> = std::result::Result<T, Error>;

impl ffi::Result {
    pub fn try_unwrap<T>(&self) -> Result<*mut T> {
        let result;
        unsafe {
            if self.error == ffi::Apriori2Error_SUCCESS {
                result = std::mem::transmute::<ffi::Handle, *mut T>(self.object);
            } else {
                return Err(self.error.into())
            }
        }

        Ok(result)
    }
}