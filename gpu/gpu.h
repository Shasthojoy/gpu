#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <tuple>

namespace gpu {

    struct OpenCL {
    };
    struct Metal {
    };
    struct Vulkan {
    };

    template<typename Tag>
    struct device_queue;

    template<typename Tag>
    struct device {
    };

    template<typename Tag>
    struct fence {
    };

    template<typename Tag>
    struct device_queue {
    };

    template <typename Tag, typename T>
    struct buffer {

    };

    template<typename Tag>
    class device_list {
    public:
        enum flags {
            gpu,
            cpu
        };

        using ListImpl = std::vector<device<Tag>>;
        using iterator = typename ListImpl::iterator;
        using const_iterator = typename ListImpl::const_iterator;

        device<Tag> &operator[](std::size_t idx) { return devices_[idx]; }

        auto begin() { return devices_.begin(); }

        auto end() { return devices_.end(); }

        auto cbegin() { return devices_.cbegin(); }

        auto cend() { return devices_.cend(); }

        device_list(device_list<Tag> const &rhs) = delete;

        device_list<Tag> &operator=(device_list<Tag> const &rhs) = delete;

        device_list(device_list<Tag> &&rhs)
                : devices_(std::move(rhs.devices_)) {}

        device_list(ListImpl &&devices)
                : devices_(std::move(devices)) {}

        device_list<Tag> &operator=(device_list<Tag> &&rhs) {
            devices_ = std::move(rhs.devices_);
            return *this;
        }

    private:
        ListImpl devices_;
    };

    namespace command {
        template <typename Tag, typename T>
        struct copy {
            buffer<Tag, T> src;
            buffer<Tag, T> dst;
        };

        template <typename Tag, typename T>
        struct fill {
            T src;
            buffer<Tag, T> dst;
        };

        template <typename Tag, typename T>
        struct read {
            buffer<Tag, T> src;
            T* dst;
        };

        template <typename Tag, typename T>
        struct write {
            T* src;
            buffer<Tag, T> dst;
        };

        template <typename Tag, typename... T>
        struct launch {
            std::tuple<T...> args;
        };

    }
}

#ifdef GPU_ENABLE_VULKAN

#include "gpu-vk.inl.h"

#endif

namespace gpu {
    template<typename Tag>
    inline device_list<Tag> create_device_list(typename device_list<Tag>::flags f, std::uint32_t max_devices) {
        return create_device_list(f, max_devices, Tag{});
    }
}