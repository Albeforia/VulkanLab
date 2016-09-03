#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <functional>
#include "VkDeleter.h"

#include "VkQueue.h"
#include "SwapChain.h"

#include <vector>
#include <iostream>

class HelloTriangleApp {

public:

	HelloTriangleApp(uint32_t width = 800, uint32_t height = 600);

	void run();

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

private:

	void initWindow();
	void initVulkan();
	void mainLoop();
	void createInstance();
	bool checkValidationLayers();
	void setupDebugCallback();

	vklab::QueueFamilyIndices pickPhysicalDevice();
	vklab::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
	void createLogicalDevice(const vklab::QueueFamilyIndices&);

	void createSurface();
	vklab::SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice);
	void createSwapChain();
	void recreateSwapChain();

	void createImageViews();
	void createFramebuffers();

	void createShaderModule(const std::vector<char>& code,
							vklab::VkDeleter<VkShaderModule>&);
	void createRenderPass();
	void createGraphicsPipeline();

	void createCommandPool();
	void createCommandBuffers();

	void createSemaphores();
	void drawFrame();

	std::vector<const char*> getRequiredInstanceExts();
	void checkInstanceExts(std::vector<const char*> extensions);
	bool checkDeviceExts(VkPhysicalDevice);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	GLFWwindow* window;
	uint32_t width;
	uint32_t height;

	vklab::VkDeleter<VkInstance> instance;
	vklab::VkDeleter<VkDebugReportCallbackEXT> callback;

	VkPhysicalDevice physicalDevice;
	vklab::VkDeleter<VkDevice> device;
	VkQueue graphicsQueue;

	vklab::VkDeleter<VkSurfaceKHR> surface;
	VkQueue presentQueue;
	vklab::VkDeleter<VkSwapchainKHR> swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	std::vector<vklab::VkDeleter<VkImageView>> swapChainImageViews;
	std::vector<vklab::VkDeleter<VkFramebuffer>> swapChainFramebuffers;

	vklab::VkDeleter<VkRenderPass> renderPass;
	vklab::VkDeleter<VkPipelineLayout> pipelineLayout;
	vklab::VkDeleter<VkPipeline> graphicsPipeline;

	vklab::VkDeleter<VkCommandPool> commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	vklab::VkDeleter<VkSemaphore> imageAvailableSemaphore;
	vklab::VkDeleter<VkSemaphore> renderFinishedSemaphore;

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
		std::cerr << "validation layer: " << msg << std::endl;
		return VK_FALSE;
	}

	static void onWindowResized(GLFWwindow* window, int width, int height) {
		if (width == 0 || height == 0) return;

		auto* app = reinterpret_cast<HelloTriangleApp*>(glfwGetWindowUserPointer(window));
		app->recreateSwapChain();
	}

};
