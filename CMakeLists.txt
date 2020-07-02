cmake_minimum_required(VERSION 3.10)
project(celadon VERSION 0.0.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_SIZEOF_VOID_P} EQUAL "8")
    set (PROJECT_ARCHITECTURE "x64")
else ()
    set (PROJECT_ARCHITECTURE "x86")
endif ()

find_package (OpenGL REQUIRED)

set (PROJECT_LINK_LIBS glfw3)
link_directories (${CMAKE_SOURCE_DIR}/lib)

include_directories (${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/ext ${OPENGL_INCLUDE_DIR})

file (GLOB_RECURSE SOURCES "src/*.cpp")
file (GLOB_RECURSE HEADERS "src/*.hpp")

# include(CTest)
# enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_executable (celadon ${SOURCES} ${HEADERS})
set_property(TARGET celadon PROPERTY CXX_STANDARD 17)
target_link_libraries (celadon ${PROJECT_LINK_LIBS} ${OPENGL_LIBRARIES})

if (MSVC)
    message ("MSVC detected")
elseif (UNIX)
    message ("Unix environment detected")
    target_link_libraries (sanso -lpthread -lXi -ldrm -lXdamage -lXxf86vm -lXext 
    -lX11 -lGL -ldl -lglfw3 -lGLU -lX11 -lXrandr -lXi -lXcursor -lXinerama -lrt -lm)
endif()