// Include Vulkan headers here

namespace gpu {

    template<>
    struct device<Vulkan> {
        std::string name_;
    };

    template<>
    class device_queue<Vulkan> {
        using MyType = device_queue<Vulkan>;
        using MyDevice = device<Vulkan>;
    public:
        device_queue<Vulkan>(MyDevice& dev)
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

        device_queue<Vulkan>(MyType const&) = delete;

        MyType& operator=(MyType const&) = delete;

    private:
        MyType& device_;
    };

    inline device_list<Vulkan> create_device_list(
        typename device_list<Vulkan>::flags, std::uint32_t, Vulkan) {
        device_list<Vulkan>::ListImpl impl = { 
            device<Vulkan>{"foo"}, 
            device<Vulkan>{"bar"}};
        return device_list<Vulkan>(std::move(impl));
    }
}
