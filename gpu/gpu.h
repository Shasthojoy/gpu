#pragma once

#include <cstdint>
#include <vector>
#include <string>

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
    struct command {
    };

    template<typename Tag>
    struct device_queue {
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