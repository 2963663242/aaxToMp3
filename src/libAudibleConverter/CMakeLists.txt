
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_executable(libAudibleConverter
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AudibleMeta.h
  ${CMAKE_CURRENT_SOURCE_DIR}/AudibleMeta.cpp
)
target_link_libraries(libAudibleConverter Qt${QT_VERSION_MAJOR}::Core)
