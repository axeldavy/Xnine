find_library(GTEST gtest REQUIRED)
find_library(PTHREAD pthread REQUIRED)

add_executable(NineTests NineTests.cpp ${COMMON_SOURCES} ${XNINE_SOURCES})
target_link_libraries(NineTests PRIVATE ${COMMON_LIBS} ${GTEST} ${PTHREAD} ${GL} ${EGL})
target_include_directories(NineTests PRIVATE ${PROJECT_SOURCE_DIR})
target_compile_definitions(NineTests PRIVATE XNINE_FORCE_C_D3D9_INTERFACE)

# Suppress the return-type warning
add_compile_options(-Wno-return-type)

# We compile C code as C++ where some pointer conversions are not allowed
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(NineTests PRIVATE -fpermissive)
else()
  message( SEND_ERROR "Building with ${CMAKE_CXX_COMPILER_ID} is not supported.")
endif()

