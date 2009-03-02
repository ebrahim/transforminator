cmake_minimum_required(VERSION 2.6)

project(transforminator)

add_executable(test test.cpp)

add_executable(coin-test coin-test.cpp)
target_link_libraries(coin-test Coin)

find_package(Qt4 REQUIRED)
set(QT_USE_QTOPENGL True)
include(${QT_USE_FILE})

set(transforminator_srcs
	transforminator.cpp
	GUIMainWindow.cpp
	GUIScene.cpp
	GUITransformInput.cpp
	GUITransformGenerator.cpp
	GUITransformedMesh.cpp
	MeshLoader.cpp)

set(transforminator_moc_hdrs
	GUIMainWindow.h
	GUIScene.h
	GUITransformInput.h
	GUITransformGenerator.h
	GUITransformedMesh.h)

set(transforminator_uis
	GUITransformGenerator.ui)

qt4_wrap_cpp(transforminator_moc_srcs ${transforminator_moc_hdrs})
qt4_wrap_ui(transforminator_ui_hdrs ${transforminator_uis})

add_executable(transforminator ${transforminator_srcs} ${transforminator_moc_srcs} ${transforminator_ui_hdrs})
target_link_libraries(transforminator Coin ${QT_LIBRARIES})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_definitions(${QT_DEFINITIONS})
add_definitions(-Wall)
