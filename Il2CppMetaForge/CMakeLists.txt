cmake_minimum_required(VERSION 3.10)
project(Il2CppMetaForge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include 디렉토리 추가
include_directories(${CMAKE_SOURCE_DIR}/include)

# 소스 파일 자동 수집
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# 실행파일 정의
add_executable(Il2CppMetaForge ${SOURCES} ${HEADERS})

# 플랫폼 정의 추가
if (WIN32)
    message(STATUS "Detected platform: Windows")
    target_compile_definitions(Il2CppMetaForge PRIVATE PLATFORM_WINDOWS)
elseif(UNIX)
    message(STATUS "Detected platform: Linux/Unix")
    target_compile_definitions(Il2CppMetaForge PRIVATE PLATFORM_LINUX)
endif()
