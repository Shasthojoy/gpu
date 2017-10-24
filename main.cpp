#define GPU_ENABLE_VULKAN
#include "gpu/gpu.h"

#include <iostream>

int main() {
	auto list = gpu::create_device_list<gpu::Vulkan>(gpu::device_list<gpu::Vulkan>::flags::gpu, 2);
	auto& device = list[0];
    gpu::device_queue<gpu::Vulkan> queue{device};

    gpu::buffer<gpu::Vulkan, int> src, dst;
    queue.push_command(gpu::command::copy<gpu::Vulkan, int>{src, dst});

	for (auto& v : list) {
		std::cout << v.name_ << "\n";
	}

    std::cout << queue.get_device().name_ << "\n";

	return 0;
}