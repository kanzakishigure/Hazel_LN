#pragma once
#include <glm/glm.hpp>

namespace Hazel
{
	class KansUI
	{
	public:
		 static void DrawVec3Control(const std::string& label, glm::vec3& value, float resetvalue = 0.0f, float columwidth = 100.0f);
	};
}
