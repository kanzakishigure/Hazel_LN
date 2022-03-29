#pragma once
#include "Hazel/Renderer/Texture.h"
#include "glm/glm.hpp"
namespace Hazel
{
	class SubTexture2D
	{
	public:
		SubTexture2D(Ref<Texture2D> texture, glm::vec2 min, glm::vec2 max);
		static Ref<SubTexture2D> CreateFromCroods(Ref<Texture2D> texture,glm::vec2 croods,glm::vec2 sprtesize);
	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_SubTexCroods[4];
	};
}