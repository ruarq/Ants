workspace "Ants"
	configurations { "Debug", "Release" }

project "Ants"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	defines { "VERSION=\"1.0.0\"" }

	targetdir "Bin/%{cfg.buildcfg}"
	objdir "Obj"

	files { "Source/**.hpp", "Source/**.cpp" }
	links { "sfml-system", "sfml-window", "sfml-graphics" }

	filter { "configurations:Debug" }
		symbols "On"
		defines { "DEBUG" }

	filter { "configurations:Release" }
		optimize "On"
		defines { "RELEASE" }