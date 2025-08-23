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
IncludeDir["Glad"] = "AbyssalEngine/vendor/Glad/include"
IncludeDir["imgui"] = "AbyssalEngine/vendor/imgui"
IncludeDir["glm"] = "AbyssalEngine/vendor/glm"

include "AbyssalEngine/vendor/GLFW"
include "AbyssalEngine/vendor/Glad"
include "AbyssalEngine/vendor/imgui"

project "AbyssalEngine"
	location "AbyssalEngine"
	kind "StaticLib"
	language "C++"
    staticruntime "on"
    cppdialect "C++20"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui",
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions "/utf-8"

		defines
		{
			"ABYSSAL_PLATFORM_WINDOWS",
			"ABYSSAL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "ABYSSAL_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "ABYSSAL_RELEASE"
			runtime "Release"
			optimize "on"


		filter "configurations:Dist"
			defines "ABYSSAL_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++20"
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
		"AbyssalEngine/vendor/spdlog/include",
		"AbyssalEngine/src",
		"AbyssalEngine/vendor",
		"%{IncludeDir.glm}"
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
		systemversion "latest"

		buildoptions "/utf-8"

		defines
		{
			"ABYSSAL_PLATFORM_WINDOWS",
		}

		filter "configurations:Debug"
			defines "ABYSSAL_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "ABYSSAL_RELEASE"
			runtime "Release"
			optimize "on"


		filter "configurations:Dist"
			defines "ABYSSAL_DIST"
			runtime "Release"
			optimize "on"