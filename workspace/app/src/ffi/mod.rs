/* automatically generated by rust-bindgen 0.55.1 */

#![allow(unused_variables)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]
#![allow(non_upper_case_globals)]

pub const _SAL_VERSION: u32 = 20;
pub const __SAL_H_VERSION: u32 = 180000000;
pub const _USE_DECLSPECS_FOR_SAL: u32 = 0;
pub const _USE_ATTRIBUTES_FOR_SAL: u32 = 0;
pub const _CRT_PACKING: u32 = 8;
pub const _HAS_EXCEPTIONS: u32 = 1;
pub const WCHAR_MIN: u32 = 0;
pub const WCHAR_MAX: u32 = 65535;
pub const WINT_MIN: u32 = 0;
pub const WINT_MAX: u32 = 65535;
pub type va_list = *mut ::std::os::raw::c_char;
extern "C" {
    pub fn __va_start(arg1: *mut *mut ::std::os::raw::c_char, ...);
}
pub type size_t = ::std::os::raw::c_ulonglong;
pub type __vcrt_bool = bool;
pub type wchar_t = ::std::os::raw::c_ushort;
extern "C" {
    pub fn __security_init_cookie();
}
extern "C" {
    pub fn __security_check_cookie(_StackCookie: usize);
}
extern "C" {
    pub fn __report_gsfailure(_StackCookie: usize);
}
extern "C" {
    pub static mut __security_cookie: usize;
}
pub type int_least8_t = ::std::os::raw::c_schar;
pub type int_least16_t = ::std::os::raw::c_short;
pub type int_least32_t = ::std::os::raw::c_int;
pub type int_least64_t = ::std::os::raw::c_longlong;
pub type uint_least8_t = ::std::os::raw::c_uchar;
pub type uint_least16_t = ::std::os::raw::c_ushort;
pub type uint_least32_t = ::std::os::raw::c_uint;
pub type uint_least64_t = ::std::os::raw::c_ulonglong;
pub type int_fast8_t = ::std::os::raw::c_schar;
pub type int_fast16_t = ::std::os::raw::c_int;
pub type int_fast32_t = ::std::os::raw::c_int;
pub type int_fast64_t = ::std::os::raw::c_longlong;
pub type uint_fast8_t = ::std::os::raw::c_uchar;
pub type uint_fast16_t = ::std::os::raw::c_uint;
pub type uint_fast32_t = ::std::os::raw::c_uint;
pub type uint_fast64_t = ::std::os::raw::c_ulonglong;
pub type intmax_t = ::std::os::raw::c_longlong;
pub type uintmax_t = ::std::os::raw::c_ulonglong;
pub type ErrorCode = i32;
pub const Apriori2Error_SUCCESS: Apriori2Error = 0;
pub const Apriori2Error_OUT_OF_MEMORY: Apriori2Error = 1;
pub const Apriori2Error_DEBUG_REPORTER_CREATION: Apriori2Error = 2;
pub type Apriori2Error = ::std::os::raw::c_int;
pub const ErrorTag_Apriori2: ErrorTag = 0;
pub const ErrorTag_Vulkan: ErrorTag = 1;
pub type ErrorTag = ::std::os::raw::c_int;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct ErrorDescriptor {
    pub tag: ErrorTag,
    pub code: ErrorCode,
}
#[test]
fn bindgen_test_layout_ErrorDescriptor() {
    assert_eq!(
        ::std::mem::size_of::<ErrorDescriptor>(),
        8usize,
        concat!("Size of: ", stringify!(ErrorDescriptor))
    );
    assert_eq!(
        ::std::mem::align_of::<ErrorDescriptor>(),
        4usize,
        concat!("Alignment of ", stringify!(ErrorDescriptor))
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<ErrorDescriptor>())).tag as *const _ as usize },
        0usize,
        concat!(
            "Offset of field: ",
            stringify!(ErrorDescriptor),
            "::",
            stringify!(tag)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<ErrorDescriptor>())).code as *const _ as usize },
        4usize,
        concat!(
            "Offset of field: ",
            stringify!(ErrorDescriptor),
            "::",
            stringify!(code)
        )
    );
}
pub type Handle = *mut ::std::os::raw::c_void;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct Result {
    pub error: ErrorDescriptor,
    pub object: Handle,
}
#[test]
fn bindgen_test_layout_Result() {
    assert_eq!(
        ::std::mem::size_of::<Result>(),
        16usize,
        concat!("Size of: ", stringify!(Result))
    );
    assert_eq!(
        ::std::mem::align_of::<Result>(),
        8usize,
        concat!("Alignment of ", stringify!(Result))
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<Result>())).error as *const _ as usize },
        0usize,
        concat!(
            "Offset of field: ",
            stringify!(Result),
            "::",
            stringify!(error)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<Result>())).object as *const _ as usize },
        8usize,
        concat!(
            "Offset of field: ",
            stringify!(Result),
            "::",
            stringify!(object)
        )
    );
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct VulkanInstanceFFI {
    _unused: [u8; 0],
}
pub type VulkanInstance = *mut VulkanInstanceFFI;
extern "C" {
    pub fn new_vk_instance() -> Result;
}
extern "C" {
    pub fn vk_handle(instance: VulkanInstance) -> Handle;
}
extern "C" {
    pub fn drop_vk_instance(instance: VulkanInstance);
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct RendererFFI {
    _unused: [u8; 0],
}
pub type Renderer = *mut RendererFFI;
extern "C" {
    pub fn new_renderer(vulkan_instance: VulkanInstance) -> Result;
}
extern "C" {
    pub fn drop_renderer(renderer: Renderer);
}
