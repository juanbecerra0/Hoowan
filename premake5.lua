workspace "Hoowan"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hoowan/vendor/GLFW/include"
IncludeDir["Glad"] = "Hoowan/vendor/Glad/include"
IncludeDir["ImGui"] = "Hoowan/vendor/imgui"
IncludeDir["glm"] = "Hoowan/vendor/glm"
IncludeDir["stb_image"] = "Hoowan/vendor/stb_image"

group "Dependencies"
	include "Hoowan/vendor/GLFW"
	include "Hoowan/vendor/Glad"
	include "Hoowan/vendor/imgui"
	
group ""

project "Hoowan"
	location "Hoowan"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hwpch.h"
	pchsource "Hoowan/src/hwpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HW_PLATFORM_WINDOWS",
			"HW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "HW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HW_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hoowan/vendor/spdlog/include",
		"Hoowan/src",
		"Hoowan/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Hoowan"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HW_DIST"
		runtime "Release"
		optimize "on"
