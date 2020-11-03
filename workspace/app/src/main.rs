mod graphics;
mod core;
mod ffi;

use graphics::Renderer;

fn main() {
    core::log::init().expect("unable to init log system");

    let vk_instance = core::VulkanInstance::new().unwrap();
    let _renderer = Renderer::new(&vk_instance).unwrap();

    log::info!("Vulkan works!");
    // unimplemented!("a priori collision system 2");
}
