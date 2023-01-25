find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)


add_executable(AudibleConverter 
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	)
target_include_directories(AudibleConverter PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/../libAudibleConverter
)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/build)


target_link_libraries(AudibleConverter Qt${QT_VERSION_MAJOR}::Core)

target_link_libraries(AudibleConverter 
	${CMAKE_HOME_DIRECTORY}/build/src/libAudibleConverter/Debug/libAudibleConverter.lib)
set_target_properties(AudibleConverter PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")