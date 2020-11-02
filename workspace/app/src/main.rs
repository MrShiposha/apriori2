mod graphics;
mod core;
mod ffi;

use graphics::Renderer;

fn main() {
    let vk_instance = core::VulkanInstance::new().unwrap();
    let _renderer = Renderer::new(&vk_instance).unwrap();

    println!("Vulkan works!");
    // unimplemented!("a priori collision system 2");
}
