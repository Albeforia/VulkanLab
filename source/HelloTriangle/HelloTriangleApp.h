#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <functional>
#include "VkDeleter.h"

#include "VkQueue.h"
#include "SwapChain.h"
#include "Vertex.h"

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

	void createImageView(VkImage, VkFormat, VkImageAspectFlags, vklab::VkDeleter<VkImageView>&);

	void createShaderModule(const std::vector<char>& code,
							vklab::VkDeleter<VkShaderModule>&);
	void createRenderPass();
	void createDescriptorSetLayout();
	void createGraphicsPipeline();

	void createDescriptorPool();
	void createDescriptorSet();

	void createBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags,
					  vklab::VkDeleter<VkBuffer>&, vklab::VkDeleter<VkDeviceMemory>&);
	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffer();
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize);

	void createCommandPool();
	void createCommandBuffers();

	void createSemaphores();
	void drawFrame();
	void updateUniformBuffer();

	void createTextureImage();
	void createImage(uint32_t width, uint32_t height, VkFormat,
					 VkImageTiling, VkImageUsageFlags, VkMemoryPropertyFlags,
					 vklab::VkDeleter<VkImage>&, vklab::VkDeleter<VkDeviceMemory>&);
	void copyImage(VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height);
	void transitionImageLayout(VkImage, VkImageLayout oldLayout, VkImageLayout newLayout);
	void createTextureImageView();
	void createTextureSampler();

	void createDepthResources();

	void loadModel();

	std::vector<const char*> getRequiredInstanceExts();
	void checkInstanceExts(std::vector<const char*> extensions);
	bool checkDeviceExts(VkPhysicalDevice);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags);
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling, VkFormatFeatureFlags);

	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer);

	//

	GLFWwindow* window;
	uint32_t width;
	uint32_t height;

	vklab::VkDeleter<VkInstance> instance;
	vklab::VkDeleter<VkDebugReportCallbackEXT> callback;
	vklab::VkDeleter<VkSurfaceKHR> surface;

	VkPhysicalDevice physicalDevice;
	vklab::VkDeleter<VkDevice> device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	vklab::VkDeleter<VkSwapchainKHR> swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<vklab::VkDeleter<VkImageView>> swapChainImageViews;
	std::vector<vklab::VkDeleter<VkFramebuffer>> swapChainFramebuffers;

	vklab::VkDeleter<VkRenderPass> renderPass;
	vklab::VkDeleter<VkDescriptorSetLayout> descriptorSetLayout;
	vklab::VkDeleter<VkPipelineLayout> pipelineLayout;
	vklab::VkDeleter<VkPipeline> graphicsPipeline;

	vklab::VkDeleter<VkCommandPool> commandPool;

	vklab::VkDeleter<VkImage> depthImage;
	vklab::VkDeleter<VkDeviceMemory> depthImageMemory;
	vklab::VkDeleter<VkImageView> depthImageView;

	std::vector<vklab::Vertex> vertices;
	std::vector<uint32_t> indices;

	vklab::VkDeleter<VkBuffer> vertexBuffer;
	vklab::VkDeleter<VkDeviceMemory> vertexBufferMemory;
	vklab::VkDeleter<VkBuffer> indexBuffer;
	vklab::VkDeleter<VkDeviceMemory> indexBufferMemory;
	vklab::VkDeleter<VkBuffer> uniformStagingBuffer;
	vklab::VkDeleter<VkDeviceMemory> uniformStagingBufferMemory;
	vklab::VkDeleter<VkBuffer> uniformBuffer;
	vklab::VkDeleter<VkDeviceMemory> uniformBufferMemory;

	vklab::VkDeleter<VkImage> textureImage;
	vklab::VkDeleter<VkDeviceMemory> textureImageMemory;
	vklab::VkDeleter<VkImageView> textureImageView;
	vklab::VkDeleter<VkSampler> textureSampler;

	vklab::VkDeleter<VkDescriptorPool> descriptorPool;
	VkDescriptorSet descriptorSet;

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
