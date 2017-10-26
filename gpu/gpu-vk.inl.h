// Include Vulkan headers here
#include <vulkan/vulkan.hpp>
#include <cassert>

namespace gpu {
    namespace {
        class vk_instance {
        public:
            static auto& instance() {
                static vk_instance instance;
                return instance.instance_;
            }

            ~vk_instance() {
                instance_.destroy();
            }

        private:
            vk_instance() {
                vk::ApplicationInfo app_info = vk::ApplicationInfo()
                    .setPApplicationName("AMD GPU Compute Library")
                    .setApplicationVersion(1)
                    .setPEngineName("AMD GPU")
                    .setEngineVersion(1)
                    .setApiVersion(VK_API_VERSION_1_0);

                vk::InstanceCreateInfo inst_info = vk::InstanceCreateInfo()
                    .setFlags(vk::InstanceCreateFlags())
                    .setPApplicationInfo(&app_info)
                    .setEnabledExtensionCount(0)
                    .setPpEnabledExtensionNames(NULL);

                instance_ = vk::createInstance(inst_info);
            }

            vk::Instance instance_;
        };
    }

    template<>
    struct device<Vulkan> {
        using MyType = device<Vulkan>;
    public:
        device(vk::PhysicalDevice d) noexcept
            : physical_device_(d) {
            init_props();
            init_logical_device();
        }
        device(device&& rhs) noexcept
            : physical_device_(std::move(rhs.physical_device_))
            , device_(std::move(rhs.device_)) {
            init_props();
        }

        ~device() {
            device_.waitIdle();
            device_.destroy();
        }

        auto vk_device() const noexcept { return device_; }
        auto vk_physical_device() const noexcept { return physical_device_; }

        auto name() const {
            return std::string{ properties_.deviceName };
        }
        auto num_memory_heaps() const {
            return static_cast<std::uint32_t>(memory_properties_.memoryHeapCount);
        }
        auto num_memory_types() const {
            return static_cast<std::uint32_t>(memory_properties_.memoryTypeCount);
        }
        auto memory_heap_size(std::uint32_t idx) const {
            assert(idx < num_memory_heaps());
            return static_cast<std::size_t>(memory_properties_.memoryHeaps[idx].size);
        }

        device(MyType const&) = delete;
        MyType& operator = (MyType const&) = delete;
    private:
        void init_props() {
            properties_ = physical_device_.getProperties();
            memory_properties_ = physical_device_.getMemoryProperties();
            queue_properties_ = physical_device_.getQueueFamilyProperties();
        }
        void init_logical_device() {
            // Look for compute queue family
            std::uint32_t idx = 0;
            for (auto i = 0u; i < queue_properties_.size(); ++i) {
                if (queue_properties_[i].queueFlags & vk::QueueFlagBits::eCompute) {
                    idx = i;
                    break;
                }
            }

            vk::DeviceQueueCreateInfo queue_create_info = vk::DeviceQueueCreateInfo()
                .setQueueFamilyIndex(idx)
                .setQueueCount(1);

            vk::DeviceCreateInfo device_create_info = vk::DeviceCreateInfo()
                .setQueueCreateInfoCount(1)
                .setPQueueCreateInfos(&queue_create_info);

            device_ = physical_device_.createDevice(device_create_info);
        }

        vk::PhysicalDevice physical_device_;
        vk::PhysicalDeviceMemoryProperties memory_properties_;
        vk::PhysicalDeviceProperties properties_;
        std::vector<vk::QueueFamilyProperties> queue_properties_;
        vk::Device device_;
    };

    template<>
    class device_queue<Vulkan> {
        using MyType = device_queue<Vulkan>;
        using MyDevice = device<Vulkan>;
    public:
        device_queue(MyDevice& dev)
                : device_(dev) {
        }

        auto flags() const noexcept { return flags_; }

        auto& device() const { return device_; }

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

        device_queue(MyType const&) = delete;

        MyType& operator=(MyType const&) = delete;

    private:
        MyDevice& device_;
        device_queue_flags flags_;
    };

    inline device_list<Vulkan> create_device_list(
        typename device_list<Vulkan>::flags, std::uint32_t, Vulkan) {

        auto& instance = vk_instance::instance();
        auto devices = instance.enumeratePhysicalDevices();

        device_list<Vulkan>::ListImpl impl;

        for (auto& device : devices) {
            impl.emplace_back(device);
        }

        return device_list<Vulkan>(std::move(impl));
    }
}
