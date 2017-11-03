find_package(Vulkan)

add_library(GPU INTERFACE)
target_include_directories(GPU INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(GPU INTERFACE 
	${CMAKE_CURRENT_SOURCE_DIR}/gpu.h
	${CMAKE_CURRENT_SOURCE_DIR}/gpu-vk.inl.h)
target_link_libraries(GPU INTERFACE Vulkan::Vulkan)