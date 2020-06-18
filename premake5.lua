workspace "Hoowan"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hoowan/vendor/GLFW/include"
IncludeDir["Glad"] = "Hoowan/vendor/Glad/include"
IncludeDir["ImGui"] = "Hoowan/vendor/imgui"
IncludeDir["glm"] = "Hoowan/vendor/glm"

include "Hoowan/vendor/GLFW"
include "Hoowan/vendor/Glad"
include "Hoowan/vendor/imgui"

project "Hoowan"
	location "Hoowan"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "hwpch.h"
	pchsource "Hoowan/src/hwpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HW_PLATFORM_WINDOWS",
			"HW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "HW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HW_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.glm}"
	}

	links
	{
		"Hoowan"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HW_DIST"
		runtime "Release"
		optimize "On"
		