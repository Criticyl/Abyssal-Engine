workspace "AbyssalEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "AbyssalEngine/vendor/GLFW/include"

include "AbyssalEngine/vendor/GLFW"

project "AbyssalEngine"
	location "AbyssalEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "abyssalpch.h"
	pchsource "AbyssalEngine/src/abyssalpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		buildoptions "/utf-8"

		defines
		{
			"ABYSSAL_PLATFORM_WINDOWS",
			"ABYSSAL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.abspath} \"%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Sandbox/\"")
		}

		filter "configurations:Debug"
			defines "ABYSSAL_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "ABYSSAL_RELEASE"
			optimize "On"


		filter "configurations:Dist"
			defines "ABYSSAL_DIST"
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
		"AbyssalEngine/vendor/spdlog/include",
		"AbyssalEngine/src"
	}

	dependson
	{
		"AbyssalEngine"
	}

	links
	{
		"AbyssalEngine"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		buildoptions "/utf-8"

		defines
		{
			"ABYSSAL_PLATFORM_WINDOWS",
		}

		filter "configurations:Debug"
			defines "ABYSSAL_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "ABYSSAL_RELEASE"
			optimize "On"


		filter "configurations:Dist"
			defines "ABYSSAL_DIST"
			optimize "On"