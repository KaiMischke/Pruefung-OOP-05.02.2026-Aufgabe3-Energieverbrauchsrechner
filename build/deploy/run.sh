#!/usr/bin/env bash

# Absoluten Pfad zum Deploy-Verzeichnis bestimmen
DIR="$(cd "$(dirname "$0")" && pwd)"

# X11-Display (Fallback auf :0)
export DISPLAY=:0

# CopperSpice: Library- und Plugin-Pfade
export LD_LIBRARY_PATH="$DIR/lib:${LD_LIBRARY_PATH}"
export CS_PLUGIN_PATH="$DIR/plugins"

# Programm starten
exec "$DIR/bin/Energieverbrauchsrechner"
