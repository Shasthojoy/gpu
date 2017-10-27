#define GPU_ENABLE_VULKAN
#include "gpu/gpu.h"

#include <iostream>

int main() {
    auto list = gpu::create_device_list<gpu::Vulkan>(gpu::device_list<gpu::Vulkan>::flags::gpu, 2);
    auto& device = list[0];
    gpu::device_queue<gpu::Vulkan> queue{device};

    //gpu::linear_allocator<gpu::Vulkan> la(device);
   // gpu::buffer<gpu::Vulkan, int> src(la, 1000);
    //gpu::buffer<gpu::Vulkan, int> dst(la, 1000);

    //queue.push_command(gpu::command::copy<gpu::Vulkan, int>{src, dst});

    std::vector<int> b(2, 10);
    //gpu::copy(b.cbegin(), b.cend(), src.begin());
    //gpu::copy(b.cbegin(), b.cend(), src.begin() + 5);
    //gpu::copy(queue, b.cbegin(), b.cend(), src.begin());

    gpu::device_pointer<gpu::Vulkan, int> p{nullptr, 100};
    p += 5;
    p += 10u;

    auto a = 5 + p;
    a -= 3;
    a = a - 3;

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