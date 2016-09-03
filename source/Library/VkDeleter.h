#pragma once

namespace vklab {

	template <typename T>
	class VkDeleter {

	public:

		VkDeleter() : VkDeleter([](T, VkAllocationCallbacks*) {}) {}

		VkDeleter(std::function<void(T, VkAllocationCallbacks*)> deletef) {
			this->deleter = [=](T obj) { deletef(obj, nullptr); };
		}

		VkDeleter(const VkDeleter<VkInstance>& instance, std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef) {
			this->deleter = [&instance, deletef](T obj) { deletef(instance, obj, nullptr); };
		}

		VkDeleter(const VkDeleter<VkDevice>& device, std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef) {
			this->deleter = [&device, deletef](T obj) { deletef(device, obj, nullptr); };
		}

		~VkDeleter() {
			cleanup();
		}

		// overloads the address-of and casting operators
		// to make the wrapper as transparent as possible
		T* operator &() {
			cleanup();		// we may want to use it to recreate an existing object
			return &object;
		}

		operator T() const {
			return object;
		}

	private:

		T object {VK_NULL_HANDLE};
		std::function<void(T)> deleter;

		void cleanup() {
			if (object != VK_NULL_HANDLE) {
				deleter(object);
			}
			object = VK_NULL_HANDLE;
		}

	};

}
