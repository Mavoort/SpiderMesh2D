cmake_minimum_required(VERSION 3.20)


# Read CMAKE_TOOLCHAIN_FILE from CMakePresets.json
# if vcpkg does not exist at that path, fetch via FetchContent.
if(NOT EXISTS "${CMAKE_TOOLCHAIN_FILE}")
	message("no vcpkg installation found. Downloading via FetchContent ...")

	include(FetchContent)
	FetchContent_Declare(vcpkg
		GIT_REPOSITORY https://github.com/microsoft/vcpkg/
		GIT_TAG 2024.12.16
	)
    FetchContent_MakeAvailable(vcpkg)

	# note: this must be defined BEFORE the first project call.
	set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake")
else()
	message("vcpkg installation found.")
endif()

set(APP_NAME meshgen)

project(${APP_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


# include armadillo (Linear Algebra)
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})


qt_add_executable(${APP_NAME}
	MANUAL_FINALIZATION
	src/main.cpp
	src/mainwindow.ui
	src/mainwindow.cpp include/mainwindow.h
	src/meshview.cpp include/meshview.h
	src/meshscene.cpp include/meshscene.h
	src/spidermesh.cpp
)

target_include_directories(${APP_NAME} PRIVATE include)

target_link_libraries(${APP_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${ARMADILLO_LIBRARIES})

set_target_properties(${APP_NAME} PROPERTIES
	${BUNDLE_ID_OPTION}
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${APP_NAME}
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(${APP_NAME})


#-------------------------------------------------------------------------------


# Display the current Build Type (Debug, Release, RelWithDebInfo, MinSizeRel)
message(STATUS "Current build type: ${CMAKE_BUILD_TYPE}")

# Set compile options
target_compile_options(${APP_NAME} PRIVATE -Wall -Wextra -Wpedantic)



# Packages for Debian, Fedora and Windows
set(CPACK_PROJECT_NAME MeshGen)
set(CPACK_PACKAGE_NAME MeshGen)
set(CPACK_PACKAGE_DIRECTORY packages)

set(CPACK_PACKAGE_CONTACT "marcel.angenvoort@posteo.de")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Marcel Angenvoort")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Marcel Angenvoort")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-base-dev (>= 6.4.0), libarmadillo-dev")
set(CPACK_PACKAGE_DESCRIPTION "A simple package for generating 2d meshes.")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/logo.png")
set(CPACK_DEBIAN_PACKAGE_SECTION graphics)
set(CPACK_PACKAGE_EXECUTABLES Meshgen Meshgen)
#set(CPACK_RESOURCE_FILE_LICENSE LICENSE.txt)
set(CPACK_GENERATOR DEB RPM TGZ NSIS)
include(CPack)



# Unit Tests with Catch2
find_package(Catch2 3 REQUIRED)
add_executable(cpp_test tests/test.cpp)
target_link_libraries(cpp_test PRIVATE Catch2::Catch2WithMain)

enable_testing()

# define tests
add_test(test cpp_test)



# Documentation with Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
	add_custom_target( docs
		COMMAND ${DOXYGEN_EXECUTABLE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating documentation with Doxygen"
		VERBATIM )
else (DOXYGEN_FOUND)
	message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


# unimportant
#set(CMAKE_CONFIGURATION_TYPES "Debug;Release;")

