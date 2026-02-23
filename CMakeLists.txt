cmake_minimum_required(VERSION 3.16)
project(sil_tool LANGUAGES CXX)

# Automatika pro Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Najde Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

# Definice spustitelného souboru
add_executable(sil_tool main.cpp header.h)

# Linkování knihoven
target_link_libraries(sil_tool PRIVATE Qt6::Widgets Qt6::WebEngineWidgets)

# --- AUTOMATICKÉ KOPÍROVÁNÍ SOUBORŮ ---
file(COPY 
    start.html 
    c_dev.html 
    makefile.html
    asm_dev.html 
    style.css
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)