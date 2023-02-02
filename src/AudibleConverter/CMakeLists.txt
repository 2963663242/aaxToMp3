find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)

set(PROJECT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/MyTabWidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MyTabWidget.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ConvertWidget.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ConvertWidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskTable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskTable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ConvertTask.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ConvertTask.cpp
)

add_executable(AudibleConverter 
	${PROJECT_SOURCES}
	)
target_include_directories(AudibleConverter PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/../libAudibleConverter
)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/build)


target_link_libraries(AudibleConverter Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(AudibleConverter 
	${CMAKE_HOME_DIRECTORY}/build/src/libAudibleConverter/Debug/libAudibleConverter.lib)
# set_target_properties(AudibleConverter PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
set_target_properties(AudibleConverter PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/Debug)