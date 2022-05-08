#pragma once

#include <functional>
#include <filesystem>
namespace Hazel
{
	class KansFileSystem 
	{
		public:
			static bool Exists(const std::string& filepath);
	};
}