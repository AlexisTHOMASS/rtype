cmake_minimum_required(VERSION 3.8)

set (PROJ "r-type")
project(${PROJ})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (RTYPE_CLIENT "r-type_client")

if (NOT APPLE)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
    conan_basic_setup(KEEP_RPATHS)
    include_directories(${CMAKE_INCLUDE_PATH})
    find_package(asio REQUIRED)
else()
    include_directories(${CMAKE_INCLUDE_PATH} /usr/local/include/)
endif()


file (
    GLOB_RECURSE
    RTYPE_CLIENT_SRC
    ../client/src/*.cpp
    ../client/src/*/*.cpp
    ../common/src/*.cpp
    ../common/src/*/*.cpp
)


add_executable(${RTYPE_CLIENT} ${RTYPE_CLIENT_SRC})


find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_include_directories (
    ${RTYPE_CLIENT} PUBLIC
    ../common/include
    ../client/include
    ../common/include/ecs
    ../common/include/components
    ../common/include/systems
    ../protocol
)


target_compile_features(${RTYPE_CLIENT} PRIVATE cxx_std_20)

if (APPLE)
    target_link_libraries(${RTYPE_CLIENT} pthread sfml-graphics sfml-audio)
elseif (UNIX)
    target_link_libraries(${RTYPE_CLIENT} ${CONAN_LIBS} pthread)
    target_compile_options(${RTYPE_CLIENT} PRIVATE -Wall -Wextra -g3)

elseif (WIN32)
    target_link_libraries(${RTYPE_CLIENT} Threads::Threads ${CONAN_LIBS})
    target_compile_options(${RTYPE_CLIENT} PRIVATE -Wall -DWIN32_LEAN_AND_MEAN)
endif()