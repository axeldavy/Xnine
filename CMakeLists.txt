cmake_minimum_required(VERSION 3.1...3.28)

project(
  Xnine
  VERSION 0.1
  LANGUAGES C CXX)

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_SDL_EXAMPLE "Build the SDL triangle example" OFF)
option(WITH_DRI3 "Build with DRI3 support" ON)

find_library(LDL dl REQUIRED)
find_library(X11 X11 REQUIRED)
find_library(X11_XCB X11-xcb REQUIRED)
find_library(XCB xcb REQUIRED)
find_library(XCB_DRI3 xcb-dri3 REQUIRED)
find_library(XCB_PRESENT xcb-present REQUIRED)
find_library(XCB_XFIXES xcb-xfixes REQUIRED)
find_library(XEXT Xext REQUIRED)

if(WITH_DRI3)
  find_library(EGL EGL REQUIRED)
  find_library(GL GL REQUIRED)
  add_compile_definitions(D3DADAPTER9_WITHDRI2=0)
else()
  add_compile_definitions(D3DADAPTER9_WITHDRI2=1)
endif()

if(BUILD_SDL_EXAMPLE)
  find_package(SDL2 REQUIRED)
endif()

if(DEFINED D3DADAPTER9_LOCATION)
  set(D3DADAPTER9_LOCATION ${D3DADAPTER9_LOCATION} CACHE FILEPATH " ")
elseif(DEFINED ENV{D3DADAPTER9_LOCATION})
  set(D3DADAPTER9_LOCATION ENV{D3DADAPTER9_LOCATION} CACHE FILEPATH " ")
else()
  find_library (D3DADAPTER9_LOCATION d3dadapter9.so PATH_SUFFIXES d3d)
  if(NOT D3DADAPTER9_LOCATION)
    message(FATAL_ERROR "d3dadapter9.so library not found, please set D3DADAPTER9_LOCATION manually.")
  endif()
endif()
add_compile_definitions(D3DADAPTERPATH="${D3DADAPTER9_LOCATION}")

set(COMMON_LIBS ${LDL} ${XCB} ${XCB_DRI3} ${XCB_XFIXES} ${X11} ${X11_XCB} ${XCB_PRESENT} ${XEXT})
set(
  COMMON_SOURCES
  ${PROJECT_SOURCE_DIR}/include/D3D9/d3d9.h
  ${PROJECT_SOURCE_DIR}/dri3.c
  ${PROJECT_SOURCE_DIR}/dri3.h)

set(
  XNINE_SOURCES
  ${PROJECT_SOURCE_DIR}/Xnine.c
  ${PROJECT_SOURCE_DIR}/Xnine.h)

set(
  SDL_NINE_SOURCES
  ${PROJECT_SOURCE_DIR}/SDL_nine.c
  ${PROJECT_SOURCE_DIR}/SDL_nine.h)

include_directories(${PROJECT_SOURCE_DIR}/include/D3D9 ${PROJECT_SOURCE_DIR}/include)
link_libraries(${COMMON_LIBS})

add_executable(triangle_c triangle.c ${COMMON_SOURCES} ${XNINE_SOURCES})
add_executable(triangle_cpp triangle.cpp ${COMMON_SOURCES} ${XNINE_SOURCES})
if(BUILD_SDL_EXAMPLE)
  add_executable(triangle_sdl triangle_SDL.cpp ${COMMON_SOURCES} ${SDL_NINE_SOURCES})
  target_include_directories(triangle_sdl PRIVATE ${SDL2_INCLUDE_DIR})
  target_link_libraries(triangle_sdl PRIVATE ${SDL2_LIBRARIES})
endif()

if(NOT WITH_DRI3)
  target_link_libraries(triangle_c PRIVATE ${GL} ${EGL})
  target_link_libraries(triangle_cpp PRIVATE ${GL} ${EGL})
  if(BUILD_SDL_EXAMPLE)
    target_link_libraries(triangle_sdl PRIVATE ${GL} ${EGL})
  endif()
endif()

if(BUILD_TESTS)
  add_subdirectory(NineTests)
endif()
