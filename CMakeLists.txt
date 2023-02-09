cmake_minimum_required(VERSION 3.14)

project(libAudibleConverter LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
IF(APPLE)
	set(CMAKE_GENERATOR_PLATFORM x64)
ENDIF()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/${CMAKE_GENERATOR_PLATFORM})

add_subdirectory(src/libAudibleConverter)
add_subdirectory(src/AudibleConverter)


#打印所有变量 
# function(print_directory_variables dir)
#     # Dump variables:
#     get_property(_variableNames DIRECTORY ${dir} PROPERTY VARIABLES)
#     list (SORT _variableNames)
#     foreach (_variableName ${_variableNames})
#         get_directory_property(_variableValue DIRECTORY ${dir} DEFINITION ${_variableName})
#         message(STATUS "DIR ${dir}: ${_variableName}=${_variableValue}")
#     endforeach()
# endfunction(print_directory_variables)

# #for example
# print_directory_variables(.)