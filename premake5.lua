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

project "Hoowan"
	location "Hoowan"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HW_PLATFORM_WINDOWS",
			"HW_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "HW_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HW_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HW_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Hoowan/src"
	}

	links
	{
		"Hoowan"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HW_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HW_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HW_DIST"
		optimize "On"
		