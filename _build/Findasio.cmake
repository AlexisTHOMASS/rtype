

function(conan_message MESSAGE_OUTPUT)
    if(NOT CONAN_CMAKE_SILENT_OUTPUT)
        message(${ARGV${0}})
    endif()
endfunction()


macro(conan_find_apple_frameworks FRAMEWORKS_FOUND FRAMEWORKS FRAMEWORKS_DIRS)
    if(APPLE)
        foreach(_FRAMEWORK ${FRAMEWORKS})
            # https://cmake.org/pipermail/cmake-developers/2017-August/030199.html
            find_library(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND NAME ${_FRAMEWORK} PATHS ${FRAMEWORKS_DIRS} CMAKE_FIND_ROOT_PATH_BOTH)
            if(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND)
                list(APPEND ${FRAMEWORKS_FOUND} ${CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND})
            else()
                message(FATAL_ERROR "Framework library ${_FRAMEWORK} not found in paths: ${FRAMEWORKS_DIRS}")
            endif()
        endforeach()
    endif()
endmacro()


function(conan_package_library_targets libraries package_libdir deps out_libraries out_libraries_target build_type package_name)
    unset(_CONAN_ACTUAL_TARGETS CACHE)
    unset(_CONAN_FOUND_SYSTEM_LIBS CACHE)
    foreach(_LIBRARY_NAME ${libraries})
        find_library(CONAN_FOUND_LIBRARY NAME ${_LIBRARY_NAME} PATHS ${package_libdir}
                     NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if(CONAN_FOUND_LIBRARY)
            conan_message(STATUS "Library ${_LIBRARY_NAME} found ${CONAN_FOUND_LIBRARY}")
            list(APPEND _out_libraries ${CONAN_FOUND_LIBRARY})
            if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
                # Create a micro-target for each lib/a found
                string(REGEX REPLACE "[^A-Za-z0-9.+_-]" "_" _LIBRARY_NAME ${_LIBRARY_NAME})
                set(_LIB_NAME CONAN_LIB::${package_name}_${_LIBRARY_NAME}${build_type})
                if(NOT TARGET ${_LIB_NAME})
                    # Create a micro-target for each lib/a found
                    add_library(${_LIB_NAME} UNKNOWN IMPORTED)
                    set_target_properties(${_LIB_NAME} PROPERTIES IMPORTED_LOCATION ${CONAN_FOUND_LIBRARY})
                    set(_CONAN_ACTUAL_TARGETS ${_CONAN_ACTUAL_TARGETS} ${_LIB_NAME})
                else()
                    conan_message(STATUS "Skipping already existing target: ${_LIB_NAME}")
                endif()
                list(APPEND _out_libraries_target ${_LIB_NAME})
            endif()
            conan_message(STATUS "Found: ${CONAN_FOUND_LIBRARY}")
        else()
            conan_message(STATUS "Library ${_LIBRARY_NAME} not found in package, might be system one")
            list(APPEND _out_libraries_target ${_LIBRARY_NAME})
            list(APPEND _out_libraries ${_LIBRARY_NAME})
            set(_CONAN_FOUND_SYSTEM_LIBS "${_CONAN_FOUND_SYSTEM_LIBS};${_LIBRARY_NAME}")
        endif()
        unset(CONAN_FOUND_LIBRARY CACHE)
    endforeach()

    if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
        # Add all dependencies to all targets
        string(REPLACE " " ";" deps_list "${deps}")
        foreach(_CONAN_ACTUAL_TARGET ${_CONAN_ACTUAL_TARGETS})
            set_property(TARGET ${_CONAN_ACTUAL_TARGET} PROPERTY INTERFACE_LINK_LIBRARIES "${_CONAN_FOUND_SYSTEM_LIBS};${deps_list}")
        endforeach()
    endif()

    set(${out_libraries} ${_out_libraries} PARENT_SCOPE)
    set(${out_libraries_target} ${_out_libraries_target} PARENT_SCOPE)
endfunction()


include(FindPackageHandleStandardArgs)

conan_message(STATUS "Conan: Using autogenerated Findasio.cmake")
# Global approach
set(asio_FOUND 1)
set(asio_VERSION "1.19.2")

find_package_handle_standard_args(asio REQUIRED_VARS
                                  asio_VERSION VERSION_VAR asio_VERSION)
mark_as_advanced(asio_FOUND asio_VERSION)


set(asio_INCLUDE_DIRS "/home/Alexis/.conan/data/asio/1.19.2/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include")
set(asio_INCLUDE_DIR "/home/Alexis/.conan/data/asio/1.19.2/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include")
set(asio_INCLUDES "/home/Alexis/.conan/data/asio/1.19.2/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include")
set(asio_RES_DIRS )
set(asio_DEFINITIONS "-DASIO_STANDALONE")
set(asio_LINKER_FLAGS_LIST
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>"
)
set(asio_COMPILE_DEFINITIONS "ASIO_STANDALONE")
set(asio_COMPILE_OPTIONS_LIST "" "")
set(asio_COMPILE_OPTIONS_C "")
set(asio_COMPILE_OPTIONS_CXX "")
set(asio_LIBRARIES_TARGETS "") # Will be filled later, if CMake 3
set(asio_LIBRARIES "") # Will be filled later
set(asio_LIBS "") # Same as asio_LIBRARIES
set(asio_SYSTEM_LIBS pthread)
set(asio_FRAMEWORK_DIRS )
set(asio_FRAMEWORKS )
set(asio_FRAMEWORKS_FOUND "") # Will be filled later
set(asio_BUILD_MODULES_PATHS )

conan_find_apple_frameworks(asio_FRAMEWORKS_FOUND "${asio_FRAMEWORKS}" "${asio_FRAMEWORK_DIRS}")

mark_as_advanced(asio_INCLUDE_DIRS
                 asio_INCLUDE_DIR
                 asio_INCLUDES
                 asio_DEFINITIONS
                 asio_LINKER_FLAGS_LIST
                 asio_COMPILE_DEFINITIONS
                 asio_COMPILE_OPTIONS_LIST
                 asio_LIBRARIES
                 asio_LIBS
                 asio_LIBRARIES_TARGETS)

# Find the real .lib/.a and add them to asio_LIBS and asio_LIBRARY_LIST
set(asio_LIBRARY_LIST )
set(asio_LIB_DIRS )

# Gather all the libraries that should be linked to the targets (do not touch existing variables):
set(_asio_DEPENDENCIES "${asio_FRAMEWORKS_FOUND} ${asio_SYSTEM_LIBS} ")

conan_package_library_targets("${asio_LIBRARY_LIST}"  # libraries
                              "${asio_LIB_DIRS}"      # package_libdir
                              "${_asio_DEPENDENCIES}"  # deps
                              asio_LIBRARIES            # out_libraries
                              asio_LIBRARIES_TARGETS    # out_libraries_targets
                              ""                          # build_type
                              "asio")                                      # package_name

set(asio_LIBS ${asio_LIBRARIES})

foreach(_FRAMEWORK ${asio_FRAMEWORKS_FOUND})
    list(APPEND asio_LIBRARIES_TARGETS ${_FRAMEWORK})
    list(APPEND asio_LIBRARIES ${_FRAMEWORK})
endforeach()

foreach(_SYSTEM_LIB ${asio_SYSTEM_LIBS})
    list(APPEND asio_LIBRARIES_TARGETS ${_SYSTEM_LIB})
    list(APPEND asio_LIBRARIES ${_SYSTEM_LIB})
endforeach()

# We need to add our requirements too
set(asio_LIBRARIES_TARGETS "${asio_LIBRARIES_TARGETS};")
set(asio_LIBRARIES "${asio_LIBRARIES};")

set(CMAKE_MODULE_PATH "/home/Alexis/.conan/data/asio/1.19.2/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "/home/Alexis/.conan/data/asio/1.19.2/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/" ${CMAKE_PREFIX_PATH})

if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
    # Target approach
    if(NOT TARGET asio::asio)
        add_library(asio::asio INTERFACE IMPORTED)
        if(asio_INCLUDE_DIRS)
            set_target_properties(asio::asio PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                  "${asio_INCLUDE_DIRS}")
        endif()
        set_property(TARGET asio::asio PROPERTY INTERFACE_LINK_LIBRARIES
                     "${asio_LIBRARIES_TARGETS};${asio_LINKER_FLAGS_LIST}")
        set_property(TARGET asio::asio PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     ${asio_COMPILE_DEFINITIONS})
        set_property(TARGET asio::asio PROPERTY INTERFACE_COMPILE_OPTIONS
                     "${asio_COMPILE_OPTIONS_LIST}")
        
    endif()
endif()

foreach(_BUILD_MODULE_PATH ${asio_BUILD_MODULES_PATHS})
    include(${_BUILD_MODULE_PATH})
endforeach()
