//Einbindung der Klasse `QApplication`
//`QApplication` ist das zentrale Objekt für eine GUI-Anwendung und verwaltet
//das Event-System (Mausklicks, Tastatureingaben, Fenster-Events), initialisiert
//die GUI-Umgebung und stellt die Event-Schleife (exec()) bereit
//Ohne `QApplication` kann die Copperspice-GUI nicht laufen
#include <QtGui/QApplication>
//Einbindung des Hauptfenster-Headers, damit der Compiler die Klasse `Hauptfenster` kennt
#include "Hauptfenster.h"

int main(int argc, char *argv[])
{
    //Erzeugung des zentralen App-Objekts
    //Initialisiert die GUI-Umgebung und verwaltet die Event-Schleife
    QApplication app(argc, argv);

    //Erzeugung einer Instanz `fenster` der Klasse `Hauptfenster`
    //Dadurch wird der Konstruktor der Klasse `Hauptfenster` aufgerufen und
    //Widgets erstellt, Layouts gesetzt und connect()-Verbindungen eingerichtet
    Hauptfenster fenster;
    //Fenstergröße setzen
    fenster.resize(440, 260);
    //Fenster anzeigen
    fenster.show();

    //Start der Event-Schleife
    //exec() läuft so lange, bis die Anwendung beendet wird (Hauptfenster schließen)
    return app.exec();
}
