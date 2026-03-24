cmake_minimum_required(VERSION 4.1)
project(lab4 C)

set(CMAKE_C_STANDARD 99)

# Указываем текущую директорию для поиска заголовков
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем исполняемый файл
add_executable(lab4
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/triangle.c
        triangle.c
)

# Подключаем математическую библиотеку
target_link_libraries(lab4 m)
