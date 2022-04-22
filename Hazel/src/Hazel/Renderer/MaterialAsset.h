#pragma once
#include "Hazel/Renderer/Texture.h"
#include "Hazel/Renderer/Material.h"
namespace Hazel
{
	enum class MaterialType
	{
		BlingPhongMaterial = 0, PBRMaterial
	};
	//BlingPhong Material
	//TODO use texture compress
		
	// value
		//漫反射项
		static const std::string s_DiffuseUniform = "U_Diffuse";
		//高光项			
		static const std::string s_SpecularUniform = "U_Specular";
		//自发光项		  
		static const std::string s_EmissionUniform = "U_Emission";
		//高光度			
		static const std::string s_ShininessUniform = "U_Shininess";
		
		 //Texture			  
		//漫反射项		  
		static const std::string s_DiffuseMapUniform = "U_DiffuseTexture";
		//高光项			
		static const std::string s_SpecularMapUniform = "U_SpecularTexture";
		//自发光项		   
		static const std::string s_EmissionMapUnifrom = "U_EmissionTexture";
		//法线
		static const std::string s_NormalMapUnifrom = "U_NormalTexture";
	//PBR Material		  

	class MaterialAsset
	{
	public: 
		MaterialAsset();
		MaterialAsset(const Ref<Material> material);
		MaterialAsset(const MaterialAsset& ) =default;
		~MaterialAsset();


		//BlingPhong
		 //Set value
		void SetDiffuse(const glm::vec3& value);
		void SetSpecular(const glm::vec3& value);
		void SetEmission(const glm::vec3& value);
		void SetShininess(float value);
		//Set TexureMap
		void SetDiffuseMap(Ref<Texture2D> diffusemap);
		void SetSpecularMap(Ref<Texture2D> specularmap);
		void SetEmissionMap(Ref<Texture2D> emissionmap);
		void SetNormalMap(Ref<Texture2D> normalmap);

		Ref<Material> GetMaterial() const { return m_Material; }
	private:
		Ref<Material> m_Material;
		MaterialType m_MaterialType;
	};

	//MeshComponent will handle this;
	class MaterialTable
	{
	public:
		MaterialTable(uint32_t materialCount = 1);
		~MaterialTable() = default;
		void SetMaterial(uint32_t index,const Ref<MaterialAsset> material);
		bool HasMaterial(uint32_t index);
		const Ref<MaterialAsset>& GetMaterialAsset(uint32_t index);
		void CleanMaterial(uint32_t index);
		void Clean();
	private:
		uint32_t m_MaterialCount;
		std::map<uint32_t, Ref<MaterialAsset>> m_MaterialTable;
	};
}