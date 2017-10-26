// Device abstraction layer is aimed at exposing uniform API
// for higher level components which they can use to talk to
// an underlying GPU(s).
#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <tuple>
#include <array>

namespace gpu {
    // API selector tags.
    struct OpenCL {
    };
    struct Metal {
    };
    struct Vulkan {
    };

    // Represents GPU device with private physical and virtual memory spaces
    // and capable of asynchronous kernels execution.
    template<typename Tag>
    struct device {
    };

    // Represents a queue of commands the device executes. Devices are required
    // to support at least one default queue, but are free to support more.
    enum class device_queue_flags {
        graphics = 1,
        compute = 2,
        dma = 4
    };

    template<typename Tag>
    struct device_queue {
    };

    template<typename Tag, typename T>
    struct device_pointer {
    };

    struct allocator {

    };

    // Represents typed region of virtual device memory space. Buffers support 
    // custom polymorphic allocators (stateful, supplied at construction time,
    // not included into buffer static type) and STL-style iterator-based 
    // initialization.
    template <typename Tag, typename T>
    struct buffer {
    };

    // Represents an iterable colleciton of devices.
    template<typename Tag>
    class device_list {
        using MyType = device_list<Tag>;
        using MyDevice = device<Tag>;
    public:
        enum flags {
            gpu,
            cpu
        };

        using ListImpl = std::vector<MyDevice>;
        using iterator = typename ListImpl::iterator;
        using const_iterator = typename ListImpl::const_iterator;

        MyDevice& operator[](std::size_t idx) { return devices_[idx]; }
        auto begin() { return devices_.begin(); }
        auto end() { return devices_.end(); }
        auto cbegin() { return devices_.cbegin(); }
        auto cend() { return devices_.cend(); }

        device_list(MyType const &rhs) = delete;
        device_list(MyType &&rhs)
                : devices_(std::move(rhs.devices_)) {}
        device_list(ListImpl&& devices)
                : devices_(std::move(devices)) {}

        MyType& operator=(MyType const &rhs) = delete;
        MyType& operator=(MyType &&rhs) {
            devices_ = std::move(rhs.devices_);
            return *this;
        }

    private:
        // Internal container
        ListImpl devices_;
    };

    // Command is a single unit of work submission in the queue.
    // Example commands: kernel launch, copy data, wait on a fence.
    namespace command {
        // Copy data between two GPU buffers.
        template <typename Tag, typename T>
        struct copy {
            buffer<Tag, T> src;
            buffer<Tag, T> dst;
        };
        // Fill buffer with a constant value.
        template <typename Tag, typename T>
        struct fill {
            T src;
            buffer<Tag, T> dst;
        };
        // Read data from GPU buffer into system memory.
        template <typename Tag, typename T>
        struct read {
            buffer<Tag, T> src;
            T* dst;
        };
        // Write data from system memory into GPU buffer.
        template <typename Tag, typename T>
        struct write {
            T* src;
            buffer<Tag, T> dst;
        };
        // Launch GPU-size function.
        template <typename Tag, typename... T>
        struct launch {
            std::uint32_t num_dimensions = 1;
            std::array<std::uint32_t, 3> dimensions;
            std::tuple<T...> args;
        };
    }
}

#ifdef GPU_ENABLE_VULKAN

#include "gpu-vk.inl.h"

#endif

namespace gpu {
    template<typename Tag>
    inline device_list<Tag> create_device_list(
        typename device_list<Tag>::flags f, std::uint32_t max_devices) {
        return create_device_list(f, max_devices, Tag{});
    }
}