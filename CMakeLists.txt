cmake_minimum_required(VERSION 3.16)
project(nosmoke LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_executable(nosmoke
	platform/main_sdl.c
	platform/pad_sdl.c
	platform/music_stub.c
	platform/render_sdl.c
	Data/stateManager.c
	Data/introState.c
	Data/menuState.c
	Data/gameState.c
	Data/textToGraphics.c
	Data/overState.c
)

target_compile_definitions(nosmoke PRIVATE NOSMOKE_PLATFORM_SDL)
target_include_directories(nosmoke PRIVATE
	${CMAKE_SOURCE_DIR}/Data/include
)

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
	pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
	pkg_check_modules(SDL2IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
	target_link_libraries(nosmoke PRIVATE PkgConfig::SDL2 PkgConfig::SDL2IMAGE)
else()
	find_package(SDL2 CONFIG REQUIRED)
	find_package(SDL2_image CONFIG REQUIRED)
	target_link_libraries(nosmoke PRIVATE SDL2::SDL2 SDL2::SDL2_image)
endif()
