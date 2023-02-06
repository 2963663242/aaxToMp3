find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)


file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
set(PROJECT_SOURCES ${SOURCE_FILES})

add_executable(AudibleConverter 
	${PROJECT_SOURCES}
	)
target_include_directories(AudibleConverter PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/../libAudibleConverter
)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/build)

target_link_libraries(AudibleConverter libAudibleConverter)
target_link_libraries(AudibleConverter Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

# target_link_libraries(AudibleConverter 
# 	${CMAKE_HOME_DIRECTORY}/build/src/libAudibleConverter/Debug/libAudibleConverter.lib)
# set_target_properties(AudibleConverter PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
set_target_properties(AudibleConverter PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/Debug)