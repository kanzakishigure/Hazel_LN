workspace "Hazel"
    architecture"x64"
    startproject "Sandbox"
configurations 
{ 
    "Debug", 
    "Release",
    "Dist" 
}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
--include 文件夹 采用相对路径
IncludeDir ={}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel/vendor/Glad/include"
IncludeDir["ImGui"] = "Hazel/vendor/imgui"
IncludeDir["GLM"] = "Hazel/vendor/glm"
IncludeDir["stb_image"] = "Hazel/vendor/stb_image"
include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"


--相当于将Hazel/vendor/GLFW下的remake5文件直接复制粘贴到此处
project "Hazel"    
    location"Hazel"
    kind "StaticLib"
    language "C++"
    cppdialect"c++17"
    staticruntime"on"


    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    pchheader "hzpch.h"
    pchsource "Hazel/src/hzpch.cpp"
    files 
    { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp" ,
        "%{prj.name}/vendor/stb_image/**.h", 
        "%{prj.name}/vendor/stb_image/**.cpp" ,
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }
    includedirs 
    { 
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{prj.name}/src/Hazel",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.stb_image}"
        
    }
    links
    {
        "GLFW",
        "opengl32.lib",
        "Glad",
        "ImGui"
    }
    filter "system:windows" 
        systemversion "latest" 

        defines
        {
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "_CRT_SECURE_NO_WARNINGS"
        }



    filter "configurations:Debug"
        defines "HZ_DEBUG" 
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines  "HZ_RELEASE" 
        runtime "Release"
        optimize "on"
    filter "configurations:Dist"
        defines  "HZ_DIST" 
        runtime "Release"
        optimize "on"
        

project "Sandbox"
    kind "ConsoleApp"
    location "Sandbox"
    language "C++"
    cppdialect "c++17"     
    staticruntime "on"
         
    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    files
    { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp" 
    }
    includedirs 
    { 
        "Hazel/vendor/spdlog/include",
        "Hazel/src",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.ImGui}"
    }
    links
    {
        "Hazel"
    }
    filter "system:windows"
        systemversion "latest" 

        defines
        {
            "HZ_PLATFORM_WINDOWS"      
        }



    filter "configurations:Debug"
        defines "HZ_DEBUG" 
        runtime "Debug"
        symbols "on"
    filter "configurations:Release"
        defines  "HZ_RELEASE" 
        runtime "Release"
        optimize "on"
    filter "configurations:Dist"
        defines  "HZ_DIST" 
        runtime "Release"
        optimize "on"


project "KansEditor"
        location"KansEditor"  
        kind "ConsoleApp"
        language "C++"
        cppdialect "c++17"     
        staticruntime "on"
             
        targetdir ("bin/" ..outputdir.. "/%{prj.name}")
        objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    
        files
        { 
            "%{prj.name}/src/**.h", 
            "%{prj.name}/src/**.cpp" 
        }
        includedirs 
        { 
            "Hazel/vendor/spdlog/include",
            "Hazel/src",
            "%{IncludeDir.GLM}",
            "%{IncludeDir.ImGui}"
        }
        links
        {
            "Hazel"
        }
        filter "system:windows"
            systemversion "latest" 
    
            defines
            {
                "HZ_PLATFORM_WINDOWS"      
            }
    
    
    
        filter "configurations:Debug"
            defines "HZ_DEBUG" 
            runtime "Debug"
            symbols "on"
        filter "configurations:Release"
            defines  "HZ_RELEASE" 
            runtime "Release"
            optimize "on"
        filter "configurations:Dist"
            defines  "HZ_DIST" 
            runtime "Release"
            optimize "on"