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
        std::cout << "Device name: " << v.name() << "\n";
        std::cout << "Number of memory heaps: " << v.num_memory_heaps() << "\n";

        for (auto i = 0u; i < v.num_memory_heaps(); ++i) {
            std::cout << "Heap " << i << "\n";
            std::cout << "Size: " << v.memory_heap_size(i) << "\n";
        }
    }

    return 0;
}