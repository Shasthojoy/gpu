// Include Vulkan headers here

namespace gpu {

    template<>
    struct device<Vulkan> {
        std::string name_;
    };

    template<>
    struct device_queue<Vulkan> {
        device_queue<Vulkan>(device<Vulkan> &dev)
                : device_(dev) {
        }

        auto get_device() { return device_; }

        template <typename T>
        void push_command(command::copy<Vulkan, T> const&) {

        }

        template <typename T>
        void push_command(command::fill<Vulkan, T> const&) {

        }

        template <typename T>
        void push_command(command::read<Vulkan, T> const&) {

        }

        template <typename T>
        void push_command(command::write<Vulkan, T> const&) {

        }

        template <typename ...T>
        void push_command(command::launch<Vulkan, T...> const&) {

        }

        void flush() {
        }

        void finish() {
        }

        device_queue<Vulkan>(device_queue<Vulkan> const &) = delete;

        device_queue<Vulkan> &operator=(device_queue<Vulkan> const &) = delete;

    private:
        device<Vulkan> &device_;
    };

    inline device_list <Vulkan> create_device_list(typename device_list<Vulkan>::flags, std::uint32_t, Vulkan) {
        device_list<Vulkan>::ListImpl impl = { device<Vulkan>{"foo"}, device<Vulkan>{"bar"}};
        return device_list<Vulkan>(std::move(impl));
    }
}
