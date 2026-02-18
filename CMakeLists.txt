cmake_minimum_required(VERSION 3.16)
project(sil_tools LANGUAGES CXX)

# Automatika pro Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Najde Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Definice spustitelného souboru
add_executable(sil_tools main.cpp header.h)

# Linkování knihoven
target_link_libraries(sil_tools PRIVATE Qt6::Widgets)

# --- AUTOMATICKÉ KOPÍROVÁNÍ SOUBORŮ ---
file(COPY 
    start.txt 
    c_dev.txt 
    web_dev.txt 
    asm_dev.txt 
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)