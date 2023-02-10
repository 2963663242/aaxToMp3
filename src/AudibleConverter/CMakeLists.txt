find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)


file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
set(PROJECT_SOURCES ${SOURCE_FILES})

IF(MSVC)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
ENDIF()
add_executable(AudibleConverter 
	${PROJECT_SOURCES}
	)
target_include_directories(AudibleConverter PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/../libAudibleConverter
)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

add_compile_options("/utf-8")

IF(APPLE)
target_link_libraries(AudibleConverter "-framework CoreFoundation")
ENDIF()
# target_link_libraries(AudibleConverter libAudibleConverter)

target_link_libraries(AudibleConverter  libAudibleConverter Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

# target_link_libraries(AudibleConverter 
# 	${CMAKE_HOME_DIRECTORY}/build/src/libAudibleConverter/Debug/libAudibleConverter.lib)
set_target_properties(AudibleConverter PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
# set_target_properties(AudibleConverter PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/Debug)
