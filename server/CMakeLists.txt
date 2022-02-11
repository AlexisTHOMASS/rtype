cmake_minimum_required(VERSION 3.8)

set (PROJ "r-type")
project(${PROJ})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (RTYPE_SERVER "r-type_server")

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
    RTYPE_SERVER_SRC
    ../server/src/*.cpp
    ../common/src/*.cpp
    ../common/src/*/*.cpp
)

add_executable(${RTYPE_SERVER} ${RTYPE_SERVER_SRC})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_include_directories (
    ${RTYPE_SERVER} PUBLIC
    ../common/include
    ../server/include
    ../common/include/ecs
    ../common/include/components
    ../common/include/systems
    ../protocol
)

target_compile_features(${RTYPE_SERVER} PRIVATE cxx_std_20)

if (APPLE)
    target_link_libraries(${RTYPE_SERVER} pthread sfml-graphics sfml-audio)
elseif (UNIX)
    target_link_libraries(${RTYPE_SERVER} ${CONAN_LIBS} pthread)
    target_compile_options(${RTYPE_SERVER} PRIVATE -Wall -Wextra -g3)

elseif (WIN32)
    target_link_libraries(${RTYPE_SERVER} Threads::Threads ${CONAN_LIBS})
    target_compile_options(${RTYPE_SERVER} PRIVATE -Wall)

endif()