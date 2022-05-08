#include "hzpch.h"
#include "Hazel/Utilities/FileSystem/FileSystem.h"
namespace Hazel{


	bool KansFileSystem::Exists(const std::string& filepath)
	{
		return std::filesystem::exists(filepath);
	}

}