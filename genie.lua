project "LumixRayTracer"
	libType()
	files { "src/**.h",
			"src/**.inl",
			"src/**.cpp",
			"genie.lua"
	}
	includedirs { "../LumixRayTracer/src" }
	defines { "BUILDING_RAYTRACER" }
	links { "engine" }

	defaultConfigurations()