cmake_minimum_required(VERSION 3.14)

project(libAudibleConverter VERSION 1.0 LANGUAGES CXX)

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


# 获取git hash
execute_process(
  COMMAND git log -1 --format=%H   
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} 
  OUTPUT_VARIABLE COMMIT_HASH
)
string(SUBSTRING ${COMMIT_HASH} 0 8 COMMIT_HASH)
message(STATUS "git hash= ${COMMIT_HASH}")

# 获取当前分支名称
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD   
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} 
  OUTPUT_VARIABLE CURRENT_BRANCH
)
string(SUBSTRING ${CURRENT_BRANCH} 0 1 CURRENT_BRANCH)
message(STATUS "git current branch = ${CURRENT_BRANCH}")

# 获取提交次数
execute_process(
  COMMAND git rev-list HEAD --count  
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} 
  OUTPUT_VARIABLE COMMIT_COUNT
)
string(STRIP ${COMMIT_COUNT} COMMIT_COUNT)
message(STATUS "git COMMIT_COUNT = ${COMMIT_COUNT}")

# 生成版本信息
set(VER "${COMMIT_COUNT}-${CURRENT_BRANCH}-${COMMIT_HASH}")
message(STATUS "version info = ${VER}")

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