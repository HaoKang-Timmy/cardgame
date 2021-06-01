# 最低指定的CMake版本
cmake_minimum_required(VERSION 3.0)

# 括号里面填你的工程名
PROJECT(cardgame)

# 头文件路径
INCLUDE_DIRECTORIES(include)
#INCLUDE_DIRECTORIES(/usr/local/include/)

# 查找src下的所有cpp文件，然后将结果存进指定变量名(这里是DIR_SRCS)
AUX_SOURCE_DIRECTORY(./cardgame/game DIR_SRCS)

# 指定语言要求，以下命令为c++ 11
SET(CMAKE_CXX_STANDARD 11)

# 生成可执行文件，生成的test即为可执行文件
add_executable(test ${DIR_SRCS})