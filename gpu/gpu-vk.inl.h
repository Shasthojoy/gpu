
// Include Vulkan headers here

namespace gpu {

    template <>
    struct command<Vulkan> {

    };

    template <>
    struct device<Vulkan> {
        std::string name_;
    };

    template <>
    struct device_queue<Vulkan> {
        device_queue<Vulkan>(device<Vulkan>& dev)
                : device_(dev) {
        }

        auto get_device() { return device_; }

        void push_command(command<Vulkan> const& command) {

        }

        void flush() {

        }

        void finish() {

        }


        device_queue<Vulkan>(device_queue<Vulkan> const&) = delete;
        device_queue<Vulkan>& operator = (device_queue<Vulkan> const&) = delete;

    private:
        device<Vulkan>& device_;
    };

    inline device_list<Vulkan> create_device_list(typename device_list<Vulkan>::flags, std::uint32_t, Vulkan) {
        device_list<Vulkan>::ListImpl impl = {device<Vulkan>{"foo"}, device<Vulkan>{"bar"}};
        return device_list<Vulkan>(std::move(impl));
    }
}