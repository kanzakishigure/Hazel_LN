#pragma once
#include "glm/glm.hpp"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Math/BindingBox.h"
#include "Hazel/Renderer/Material.h"


#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


namespace Hazel
{
	//c++有个优秀的性质，struct在内存中是连续存储的
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 Texturecroods;
		glm::vec4 BaseColor;
	};
	struct Index
	{
		uint32_t V0, V1, V2;
	};

	class SubMesh
	{
	public:
		std::vector <Vertex> Verteices;
		std::vector <Index> Indices;
		uint32_t MaterialIndex;

		glm::mat4 Transform{ 1.0f }; // World transform
		glm::mat4 LocalTransform{ 1.0f };
		BindBox BoundingBox;
	};
	class MeshSource
	{
	public:
		MeshSource(const std::string& path);
		MeshSource() = default;

		MeshSource(const Vertex* verteices, const Index* indices);

		void ProcessNode(const aiNode* node, const aiScene* scene,int level);
		SubMesh ProcessMesh(const aiMesh* mesh, const aiScene* scene,int level);

		const std::vector<SubMesh>& GetSubMesh() { return m_SubMeshes; }

		void SetMaterial(const Ref<Material> material) { m_Material = material; }
		const Ref<Material> GetMaterial() { return m_Material; }

		const std::vector<Ref<VertexArray>>& GetVertexArray() const { return m_VertexArray; }
		
		//temp function to renderer mesh
		void GenVertexArry();
		

	private:
		Scope<Assimp::Importer> m_Importer;

		
		std::vector<SubMesh> m_SubMeshes;

		std::vector<Ref<VertexArray>> m_VertexArray;

		Ref<Material> m_Material;
		Ref<Shader> m_MeshShader;
		const aiScene* m_Scene;
		glm::mat4 transform;

		std::string m_LoadPath;
		//用于物理碰撞计算，光线追踪加速
		BindBox m_BindingBox;

	};
	class Mesh
	{
	public:
		Mesh(const MeshSource& source);
		~Mesh();
	private:
		std::vector<SubMesh> SubMesh;
	};



}