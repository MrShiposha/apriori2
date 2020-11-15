mod graphics;
mod core;
mod ffi;
mod os;
mod io;

use {
    serde::{Serialize, Deserialize},
    graphics::Renderer,
    os::WindowMethods,
};

#[derive(Debug, Clone, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub enum Apriori2InputId {
    ForwardBackward,
    LeftRight,
    UpDown,
    MouseX,
    MouseY,
    MouseAction,
    ShiftAction,
    LeftShiftAction,
    OsAction,
    LeftAltAction,
    OsShiftAction,
}

fn main() {
    core::log::init().expect("unable to init log system");

    let input_map_path = "app/res/input_map.ron";
    let input_map = io::InputMap::<Apriori2InputId>::load(input_map_path).unwrap();

    let vk_instance = core::VulkanInstance::new().unwrap();
    let mut window = os::Window::<Apriori2InputId>::new(
        "apriori2",
        os::WindowSize {
            width: 800,
            height: 600
        },
        os::WindowPosition {
            x: 50,
            y: 50
        }
    ).unwrap();

    let mut forward_backward = 0.0;
    let mut left_right = 0.0;
    let mut up_down = 0.0;

    window.input_handler_mut().update_inputs(&input_map);
    window.input_handler_mut()
        .handle(Apriori2InputId::ForwardBackward).axis(move |value| {
            forward_backward += value;

            log::info!("forward-backward = {}", forward_backward);
        })
        .handle(Apriori2InputId::LeftRight).axis(move |value| {
            left_right += value;

            log::info!("left-right = {}", left_right);
        })
        .handle(Apriori2InputId::UpDown).axis(move |value| {
            up_down += value;

            log::info!("up-down = {}", up_down);
        })
        .handle(Apriori2InputId::MouseX).axis(|value| {
            log::info!("mouse X = {}", value);
        })
        .handle(Apriori2InputId::MouseY).axis(|value| {
            log::info!("mouse Y = {}", value);
        })
        .handle(Apriori2InputId::MouseAction).action(|event| {
            log::info!("mouse left {:#?}", event);
        })
        .handle(Apriori2InputId::ShiftAction).action(|event| {
            log::info!("shift action {:#?}", event);
        })
        .handle(Apriori2InputId::OsAction).action(|event| {
            log::info!("os action {:#?}", event);
        })
        .handle(Apriori2InputId::LeftAltAction).action(|event| {
            log::info!("left alt action {:#?}", event);
        })
        .handle(Apriori2InputId::OsShiftAction).action(|event| {
            log::info!("os shift action {:#?}", event);
        });

    window.show();

    let _renderer = Renderer::new(
        &vk_instance,
        &window
    ).unwrap();

    log::info!("Vulkan works!");

    io::execute().unwrap();
}
