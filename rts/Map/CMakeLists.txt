
# This list was created using this *nix shell command:
# > find . -name "*.cpp"" | sort
SET(sources_engine_Map
		"${CMAKE_CURRENT_SOURCE_DIR}/BaseGroundDrawer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/BasicMapDamage.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Ground.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/HeightLinePalette.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/HeightMapTexture.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MapDamage.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MapInfo.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MapParser.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MetalMap.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/NoMapDamage.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/ReadMap.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/Frustum.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/Plane.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/Sm3GroundDrawer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/Sm3Map.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/terrain/Lightcalc.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/terrain/QuadRenderData.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/terrain/Terrain.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/terrain/TerrainTexEnvCombine.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/terrain/TerrainTexture.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/terrain/TerrainTextureGLSL.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/terrain/TerrainUtil.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/terrain/TerrainVertexBuffer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SM3/terrain/Textures.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SMF/BFGroundDrawer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SMF/BFGroundTextures.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SMF/SmfMapFile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SMF/SmfReadMap.cpp"
	)

MakeGlobal(sources_engine_Map)
