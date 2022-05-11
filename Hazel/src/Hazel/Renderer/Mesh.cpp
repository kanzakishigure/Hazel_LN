#include "hzpch.h"

#include "Mesh.h"


const uint32_t importFlag = aiProcess_CalcTangentSpace | //�������߿ռ�
							aiProcess_Triangulate | //��֤һ��ÿ��ͼԪ�Ļ�����λ�������Σ�����ֶ������
							aiProcess_JoinIdenticalVertices |
							aiProcess_SortByPType;

namespace Hazel
{
	
	MeshSource::MeshSource(const std::string& path)
		:m_LoadPath(path)
	{
		Scope<Assimp::Importer>m_Importer = std::make_unique<Assimp::Importer>();
		m_Scene =  m_Importer->ReadFile(path,importFlag);
		HZ_INFO("load mesh path {0}", path.c_str());
		if (!m_Scene || m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_Scene->mRootNode)
		{
			HZ_ERROR(m_Importer->GetErrorString());
			HZ_ASSERT(m_Scene, "assimp load file fail ");
		}
		m_SubMeshes.reserve(m_Scene->mNumMeshes);
		ProcessNode(m_Scene->mRootNode, m_Scene,0);
		GenVertexArry();

	}
#if 1

	void MeshSource::ProcessNode(const aiNode* node, const aiScene* scene, int level)
	{
		HZ_INFO("process level: {0}", level);
		HZ_INFO("node-meshNum:  {0}", node->mNumMeshes);
		//processCurrentNode
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_SubMeshes.push_back(ProcessMesh(mesh, scene,level+1));

		}

		//ProsessChildNode
		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], m_Scene,level+1);

		}
		
	}

	SubMesh MeshSource::ProcessMesh(const aiMesh* mesh, const aiScene* scene, int level)
	{
		SubMesh submesh;
		//Vertex
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex v;

			v.Position = { mesh->mVertices[i].x,
						   mesh->mVertices[i].y,
						   mesh->mVertices[i].z };
			v.Normal =	 { mesh->mNormals[i].x,
						   mesh->mNormals[i].y,
						   mesh->mNormals[i].z };
			if (mesh->mTextureCoords[0]) // �����Ƿ����������ꣿ
			{
				v.Texturecroods = { mesh->mTextureCoords[0][i].x,
									mesh->mTextureCoords[0][i].y,};
			}
			else
			{
				v.Texturecroods = glm::vec2(0.0f);
			}
			if (mesh->HasVertexColors(i))
			{
				v.BaseColor = {	mesh->mColors[i]->r,
								mesh->mColors[i]->g,
								mesh->mColors[i]->b,
								mesh->mColors[i]->a };
			}
			else
			{
				v.BaseColor = glm::vec4(1.0f);
			}
			submesh.Verteices.push_back(v);
			
		}
		//Index
		std::vector <Index> indices;
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{

			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j+=3)
			{
				m_Indices.push_back({ face.mIndices[j],face.mIndices[j+1],face.mIndices[j+2]});
				submesh.IndexCount++;
			}
		}
		//Material
		{
			HZ_PROFILE_SCOPE("Import mesh Material ");
			if (scene->HasMaterials())
			{
				aiMaterial* aimaterial = scene->mMaterials[mesh->mMaterialIndex];
				std::string mtlName = aimaterial->GetName().C_Str();
				auto mtl = Material::Create(m_MeshShader, mtlName);
				//BlingPhong material
				{

					//DIFFUSE;
					{
						int materialcount = 0;
						materialcount = aimaterial->GetTextureCount(aiTextureType_DIFFUSE);
						if (materialcount)
						{
							aiString aistr = {};
							aimaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aistr);
							HZ_TRACE("{0} DIFFUSE texture: {1} ", mtlName.c_str(), aistr.C_Str());
							std::string texturepath = m_LoadPath + "/" + aistr.C_Str();
							auto texture = Texture2D::Create(texturepath);
							mtl->Set(MaterialAsset::GetDiffuseMapLocation(), texture);
							
							{
								//LightMap
								std::string Lightmappath = texturepath;
								auto index = Lightmappath.find_last_of(".");
								Lightmappath.insert(index, "_Light");
								if (KansFileSystem::Exists(texturepath))
								{
									auto lighttexture = Texture2D::Create(texturepath);
									mtl->Set(MaterialAsset::GetToneLightMapLocation(), lighttexture);
									HZ_TRACE("{0} Light texture: {1} ", mtlName.c_str(), Lightmappath.c_str());
								}
								else
								{
									HZ_WARN("{0} don't have Light texture", mtlName.c_str());
									mtl->Set(MaterialAsset::GetToneLightMapLocation(), Renderer::GetWhiteTexture());
								}
							}
							{
								//RampMap
								std::string Rampmappath = texturepath;
								auto index = Rampmappath.find_last_of(".");
								Rampmappath.insert(index, "_Ramp");

								if (KansFileSystem::Exists(Rampmappath))
								{
									auto ramptexture = Texture2D::Create(Rampmappath);
									mtl->Set(MaterialAsset::GetToneRampMapLocation(), ramptexture);
									HZ_TRACE("{0} Ramp texture: {1} ", mtlName.c_str(), Rampmappath.c_str());
								}
								else
								{
									HZ_WARN("{0} don't have Ramp texture", mtlName.c_str());
									mtl->Set(MaterialAsset::GetToneRampMapLocation(), Renderer::GetWhiteTexture());
								}
							}
						}
						else
						{
							HZ_WARN("{0} don't have DIFFUSE texture", mtlName.c_str());
							mtl->Set(MaterialAsset::GetDiffuseMapLocation(), Renderer::GetWhiteTexture());
						}
					}
					//SPECULAR
					{
						int materialcount = 0;
						materialcount = aimaterial->GetTextureCount(aiTextureType_SPECULAR);
						if (materialcount)
						{
							aiString aistr = {};
							aimaterial->GetTexture(aiTextureType_SPECULAR, 0, &aistr);
							HZ_TRACE("{0} SPECULAR texture: {1} ", mtlName.c_str(), aistr.C_Str());
							std::string texturepath = m_LoadPath + "/" + aistr.C_Str();
							auto texture = Texture2D::Create(texturepath);
							mtl->Set(MaterialAsset::GetSpecularMapLocation(), texture);

						}
						else
						{
							HZ_WARN("{0} don't have Specular texture", mtlName.c_str());
							mtl->Set(MaterialAsset::GetSpecularMapLocation(), Renderer::GetBlackTexture());
						}
					}
					//Normal
					{
						int materialcount = 0;
						materialcount = aimaterial->GetTextureCount(aiTextureType_SPECULAR);
						if (materialcount)
						{
							int materialcount = 0;
							materialcount = aimaterial->GetTextureCount(aiTextureType_NORMALS);
							if (materialcount)
							{
								aiString aistr;
								aimaterial->GetTexture(aiTextureType_NORMALS, 0, &aistr);
								HZ_INFO("{0} Normal texture: {1} ", mtlName.c_str(), aistr.C_Str());
								std::string texturepath = m_LoadPath + "/" + aistr.C_Str();
								auto texture = Texture2D::Create(texturepath);
								mtl->Set("U_NormalTexture", texture);
							}
						}
						else
						{
							HZ_WARN("{0} don't have Normal texture", mtlName.c_str());
						}
					}
					//shininess
					{
						float shininess;
						if (aimaterial->Get(AI_MATKEY_SHININESS, shininess) != aiReturn_SUCCESS)
							shininess = 80.0f; // Default value
						//mtl->Set(MaterialAsset::GetShininessLocation(), shininess);
					}
				}
				//PBR material
				{

				}

				m_Material.push_back(mtl);
			}
			else
			{
				//TO do use the defualt material;
			}
		}
		submesh.Indices = indices;
		return submesh;
	}

	void MeshSource::GenVertexArry()
	{
		
		BufferLayout layout = {
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float3,"a_Normal"},
			{ShaderDataType::Float2,"a_TextureCroods"},
			{ShaderDataType::Float4,"a_BaseColor"}
		};
		for (SubMesh& smesh :m_SubMeshes)
		{
			auto& VA = VertexArray::Create();
			VA->Bind();
			
			auto& VB = VertexBuffer::Create((float*)&(smesh.Verteices[0]),smesh.Verteices.size()*sizeof(Vertex));
			VB->Bind();
			VB->SetBufferLayout(layout);
			VA->AddVertexBuffer(VB);

			auto& IB = IndexBuffer::Create((uint32_t*)&(smesh.Indices[0]), 3*smesh.Indices.size());
			IB->Bind();
			VA->SetIndexBuffer(IB);
			m_VertexArray.push_back(VA);
		}
		
	}

#endif
	

}
