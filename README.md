# Pruefung-OOP-05.02.2026-Aufgabe3-Energieverbrauchsrechner

Dieses Projekt ist ein **C++-GUI-Programm** (Copperspice), das den **Energieverbrauch** und die **Stromkosten** eines elektrischen Geräts berechnet.

Dazu gibt der Benutzer über die GUI folgende Daten ein:
- **Leistung** in Kilowatt (kW)
- **Laufzeit** in Stunden (h)
- **Strompreis** in Euro pro kWh
- optional: **Mehrwertsteuer (19%)** (Kann über eine Checkbox an- oder abgewählt) werden.

Das Programm berechnet daraus dann:
- **Energieverbrauch** in kWh
- **Stromskosten** in Euro (netto brutto, je nachdem, ob die Mehrwertsteuer-Checkbox aktiv oder inaktiv ist)

---

## Projektstruktur

Pruefung-OOP-05.02.2026-Aufgabe3-Energieverbrauchsrechner/
├─ CMakeLists.txt

├─ README.md

└─ src/

|  ├─ main.cpp
  
|  ├─ Hauptfenster.h
  
|  ├─ Hauptfenster.cpp
  
|  ├─ Energieverbrauchsrechner.h
  
|  ├─ Energieverbrauchsrechner.cpp

## Aufteilung
- **Library (`energieverbrauch`)**
  - Energieverbrauchsrechner.h / .cpp
  - Enthält die Berechnungslogik

- **GUI-Anwendung**
  - Hauptfenster.h / .cpp
  - Benutzerinteraktion und Darstellung

- **main.cpp**
  - Startpunkt der Anwendung

## Voraussetzungen
- Linux mit X11 (z. B. Ubuntu)
- C++ Compiler mit C++17 (z. B. g++)
- CMake ≥ 3.16
- CopperSpice SDK lokal installiert

# Programm kompilieren und ausführen

## 1) Build-Ordner anlegen

`rm -rf build`

`mkdir build`

`cd build`

## 1) CMake konfigurieren

In diesem Prüfugnsprojekt wird CopperSpice über folgenden lokalen Pfad eingebunden:

**/home/misch/cs_demo/copperspice_lib/lib/cmake/CopperSpice**


**Wichtiger Hinweis:**

Wenn CopperSpice auf dem Zielrechner an einem anderen Ort installiert ist, muss der Pfad entsprechend angepasst werden, da der Befehl `find_package(CopperSpice REQUIRED)` (siehe CMakeLists.txt) sonst nicht die benötigten CopperSpice Libraries finden kann und der Build-Versuch eine Fehlermeldung ausgibt!

Über den Befehl

`cmake .. -DCMAKE_PREFIX_PATH=/home/misch/cs_demo/copperspice_lib/lib/cmake/CopperSpice`

wird cmake der Ablageort von CopperSpice und seinen Libraries bekannt gemacht.

## 2) Kompilieren

`cmake --build .`

## 3) Deploy/Installation

Für ein lauffähiges Paket, wird das Programm inklusive aller benötigter Libraries und Plugins in ein eigenes Verzeichnis installiert:

`cmake --install . --prefix=deploy`

Dadurch wird im Projekt-Verzeichnis folgende Struktur angelegt:

build/deploy/

├─ bin/

|  └─ Energieverbrauchsrechner

├─ include/

|  └─ Energievebrauchsrechner.h

├─ lib/

|  └─ libCsCore1.9.so

|  └─ libCsGui1.9.so

|  └─ libCsXcbSupport1.9.so

|  └─ libenergieverbrauch.a

├─ plugins/

|  ├─ platforms/

|  |  └─ CsGuiXcb1.9.so

## 4) Programm starten

Zum Starten des Programms wird ein Skript im Verzeichnis build/deploy/ angelegt, das die nötigen Laufzeitpfade setzt:

`touch run.sh`

```
#!/usr/bin/env bash
DIR="$(cd "$(dirname "$0")" && pwd)"
export DISPLAY=:0
export LD_LIBRARY_PATH="$DIR/lib:${LD_LIBRARY_PATH}"
export CS_PLUGIN_PATH="$DIR/plugins"
exec "$DIR/bin/Energieverbrauchsrechner"
```

Anschließend wird das Skript mit dem nachfolgenden Befehl ausführbar gemacht:

`chmod +x run.sh`

und dann über `./run.sh` gestartet.


