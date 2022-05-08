#pragma once
#include "Hazel/Renderer/Mesh.h"
namespace Hazel 
{
	enum class OffsetType
	{
		Default = 0,
		NormalDirection,
		FiexdOffset
	};
	class MeshUtil
	{
		public:
			static void SmoothNormal(std::vector<Vertex>& verteices, std::vector<glm::vec3>& smoothnormal);
			static void FastSmoothNormal(std::vector<Vertex>& verteices);
			static void SetMeshOffset(std::vector<Vertex>& verteices,const std::vector<SubMesh>& submushes,float offset);
			static void BackMeshNormal(std::vector<Vertex>& verteices,const std::vector<glm::vec3>& smoothnormal);

	};

}