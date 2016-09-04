#pragma once

#include <glm\glm.hpp>
#include <vulkan\vulkan.h>

#include <array>

#include <glm/gtx/hash.hpp>

namespace vklab {

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 texCoord;

		bool operator==(const Vertex& other) const {
			return pos == other.pos && color == other.color && texCoord == other.texCoord;
		}

		static VkVertexInputBindingDescription getBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

	};

}

namespace std {
	template<> struct hash<vklab::Vertex> {
		size_t operator()(vklab::Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^
					 (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}
