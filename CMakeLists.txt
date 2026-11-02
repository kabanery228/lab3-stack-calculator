cmake_minimum_required(VERSION 3.30)
project(lab3_stack_calculator CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Создаём исполняемый файл, явно указывая путь к исходнику
add_executable(calculator "${SRC_DIR}/a.cpp")

# Опционально: если в будущем появятся заголовочные файлы в src, 
# можно добавить эту директорию в пути поиска include
target_include_directories(calculator PRIVATE "${SRC_DIR}")