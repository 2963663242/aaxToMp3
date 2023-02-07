
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
set(PROJECT_SOURCES ${SOURCE_FILES})
add_library(libAudibleConverter SHARED ${PROJECT_SOURCES}
)
# add_library(libAudibleConverter SHARED
#   # ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
#   # ${CMAKE_CURRENT_SOURCE_DIR}/AudibleMeta.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/AudibleMeta.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/IAudibleConvert.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/IAudibleConvert.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/AudibleConvert.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/AudibleConvert.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/functions.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/settings.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/settings.cpp
# )
target_link_libraries(libAudibleConverter Qt${QT_VERSION_MAJOR}::Core)

# SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
SET_TARGET_PROPERTIES(libAudibleConverter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})


add_custom_command(
  TARGET libAudibleConverter POST_BUILD
  COMMAND xcopy  "\"$(SolutionDir)../sdk/win/bin\"" "\"$(OutDir)\""  /E /Y
  )
  
# set_target_properties(libAudibleConverter PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")

