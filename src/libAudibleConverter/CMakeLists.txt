
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_executable(libAudibleConverter
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  # ${CMAKE_CURRENT_SOURCE_DIR}/AudibleMeta.h
  ${CMAKE_CURRENT_SOURCE_DIR}/AudibleMeta.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/IAudibleConvert.h
  ${CMAKE_CURRENT_SOURCE_DIR}/IAudibleConvert.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AudibleConvert.h
  ${CMAKE_CURRENT_SOURCE_DIR}/AudibleConvert.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/functions.h
  ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/settings.h
  ${CMAKE_CURRENT_SOURCE_DIR}/settings.cpp
)
target_link_libraries(libAudibleConverter Qt${QT_VERSION_MAJOR}::Core)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/build)

add_custom_command(
  TARGET libAudibleConverter POST_BUILD
  COMMAND xcopy  "\"$(SolutionDir)../sdk/win/bin\"" "\"$(OutDir)\""  /E /Y
  )
  
set_target_properties(libAudibleConverter PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")

