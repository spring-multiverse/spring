# Place executables and shared libs under "build-dir/",
# instead of under "build-dir/rts/"
# This way, we have the build-dir structure more like the install-dir one,
# which makes testing spring in the builddir easier, eg. like this:
# cd build-dir
# SPRING_DATADIR=$(pwd) ./spring
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

SET(ENGINE_SRC_ROOT_DIR "${CMAKE_SOURCE_DIR}/rts")


### Assemble defines
SET(USE_MMGR FALSE CACHE BOOL "Use memory manager?")
if (USE_MMGR)
	ADD_DEFINITIONS(-DUSE_MMGR)
endif (USE_MMGR)

SET(TRACE_SYNC FALSE CACHE BOOL "Enable sync tracker")
if (TRACE_SYNC)
	ADD_DEFINITIONS(-DTRACE_SYNC)
endif (TRACE_SYNC)

SET(SYNCDEBUG FALSE CACHE BOOL "Enable sync debugger (needs SYNCCHECK=true)")
if (SYNCDEBUG)
	ADD_DEFINITIONS(-DSYNCDEBUG)
endif (SYNCDEBUG)

# Only used by GML build, but used in builds/GML and lib/gml
SET(USE_GML_DEBUG FALSE CACHE BOOL "Use GML call debugging?")



### Assemble common incude dirs
INCLUDE_DIRECTORIES(BEFORE lib/lua/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/AL)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/System/)



### Assemble common libraries
Add_Subdirectory(System/Sound)
if    (NO_SOUND)
	ADD_DEFINITIONS(-DNO_SOUND)
endif (NO_SOUND)

LIST(APPEND engineCommonLibraries ${DEVIL_IL_LIBRARY})

### Find include directories and add platform specific libraries
LIST(APPEND engineCommonLibraries ${Boost_REGEX_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_SIGNALS_LIBRARY})

LIST(APPEND engineCommonLibraries lua 7zip oscpack minizip streflop lobby assimp)

IF    (UNIX)
	# Needed for dynamically loading shared libraries (on some OS)
	LIST(APPEND engineCommonLibraries dl)
ENDIF (UNIX)

IF (MINGW)
	LIST(APPEND engineCommonLibraries ${WIN32_LIBRARIES} mingw32)
ENDIF (MINGW)


### Assemble engine sources
Add_Subdirectory(Game)
Add_Subdirectory(Lua)
Add_Subdirectory(ExternalAI)
Add_Subdirectory(Rendering)
Add_Subdirectory(aGui)
Add_Subdirectory(Menu)
Add_Subdirectory(Map)
Add_Subdirectory(Sim)
Add_Subdirectory(System)

SET(engineSources
		${sources_engine_Game}
		${sources_engine_Lua}
		${sources_engine_Map}
		${sources_engine_Rendering}
		${sources_engine_aGui}
		${sources_engine_Menu}
		${sources_engine_Sim}
		${sources_engine_System}
		${sources_engine_ExternalAI}
		${nedmalloc_obj} # TODO remove? (seems never to be set)
	)

### Add headers for generated project files (e.g. Code::Blocks)
file(GLOB_RECURSE engineHeaders "*.h" "*.hpp")


### Add icon and manifest to exe using windres
IF    (WIN32)
	SET(ENGINE_ICON_DIR "${ENGINE_SRC_ROOT_DIR}")
	SET(ENGINE_ICON_RES "${ENGINE_SRC_ROOT_DIR}/icon.rc")
	SET(ENGINE_ICON_OBJ "${CMAKE_CURRENT_BINARY_DIR}/icon.o")
	CreateResourceCompileCommand(ENGINE_ICON "${ENGINE_ICON_DIR}" "${ENGINE_ICON_RES}" "${ENGINE_ICON_OBJ}")
ELSE  (WIN32)
	SET(ENGINE_ICON "")
ENDIF (WIN32)


Add_Subdirectory(builds)
