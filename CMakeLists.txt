cmake_minimum_required(VERSION 3.16)
project(energieverbrauch_lean_cs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CopperSpice REQUIRED)

# -------------------------------------------------------
# 1) Eigene Library: Berechnungslogik (ohne GUI-Abhängigkeit)
# -------------------------------------------------------
add_library(energieverbrauch STATIC
  src/Energieverbrauchsrechner.cpp
)

target_include_directories(energieverbrauch PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(energieverbrauch PROPERTIES
  OUTPUT_NAME "energieverbrauch"
)

# -------------------------------------------------------
# 2) Executable: GUI
# -------------------------------------------------------
add_executable(Energieverbrauchsrechner
  src/main.cpp
  src/Hauptfenster.cpp
)

target_link_libraries(Energieverbrauchsrechner PRIVATE
  energieverbrauch
  CopperSpice::CsCore
  CopperSpice::CsGui
)

# --- RPATH: Binary findet libs relativ zu sich selbst ---
set_target_properties(Energieverbrauchsrechner PROPERTIES
  BUILD_RPATH "\$ORIGIN/../lib"
  INSTALL_RPATH "\$ORIGIN/../lib"
)

# -------------------------------------------------------
# Install / Deploy
# -------------------------------------------------------

# Binary nach bin
install(TARGETS Energieverbrauchsrechner RUNTIME DESTINATION bin)

# (Optional, zeigt "Library" auch beim Install)
install(TARGETS energieverbrauch ARCHIVE DESTINATION lib)
install(FILES src/Energieverbrauchsrechner.h DESTINATION include)

# CopperSpice libs + Plugin aus lokalem SDK nach deploy kopieren
set(CS_PREFIX "$ENV{HOME}/cs_demo/copperspice_lib")

install(FILES
  "${CS_PREFIX}/lib/libCsCore1.9.so"
  "${CS_PREFIX}/lib/libCsGui1.9.so"
  "${CS_PREFIX}/lib/libCsXcbSupport1.9.so"
  DESTINATION lib
)

install(FILES
  "${CS_PREFIX}/plugins/platforms/CsGuiXcb1.9.so"
  DESTINATION plugins/platforms
)
