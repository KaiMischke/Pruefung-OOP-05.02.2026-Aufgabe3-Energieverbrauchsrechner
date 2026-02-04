//Include-Guard zum Schutz vor Mehrfacheinbindung
//Er verhindert, dass die Header-Datei mehrfach eingebunden wird und es zu Compiler-Fehlern kommt
#ifndef HAUPTFENSTER_H
#define HAUPTFENSTER_H

//Einbindung der benötigten GUI-Klassen
//QWidget ist die Basisklasse aller grafischen Elemente in Copperspice,
//jedes Fenser, jeder Button, jedes Eingabefeld, etc. basiert darauf
//Die Klasse Hauptfenster erbt von QWidget, übernimmt also Eigenschaften und
//Methoden der Klasse QWidget
#include <QtGui/QWidget>

//Ein Widget für die numerische Eingabe mit Dezimalzahlen, ermöglicht die Werteeingabe
//über die Tastatur und über Pfeiltasten in der GUI (Im Programm verwendet für Leistung, Laufzeit und Stromprei
#include <QtGui/QDoubleSpinBox>

//Ein CheckBox-Widget, liefert einen booleschen Wert
//Angehakt = true, nicht angehakt = false (Im Programm verwendet zur An- und Abwahl der Mehrwertsteuer)
#include <QtGui/QCheckBox>

//Ein Widget zur Textanzeige, bietet nur eine Ausgabe- keine Eingabemöglichkeit
#include <QtGui/QLabel>

//Einbindung des Headers der eigenen Logikklasse (Berechnungslogik)
//Der Klasse `Hauptfenster` wird damit die (Logik)Klasse `Energieverbrauchsrechner` und 
//das struct `Ergebnis` bekannt gemacht
#include "Energieverbrauchsrechner.h"

// Definition der Klasse `Hauptfenster`, sie erbt öffentlich Methoden und Eigenschaften von der 
// Basisklasse `QWidget`
class Hauptfenster : public QWidget
{
public:
    //Deklarartion des Konstruktors der Klasse, wird aufgerufen, wenn ein Hauptfenster erzeugt wird
    explicit Hauptfenster(QWidget *parent = nullptr);
    //Deklaration des Destruktors der Klasse, wird aufgerufen, wenn ein Fenster zerstört (geschlossen) wird
    ~Hauptfenster();

private:
    //Deklaration der Klassenmethoden
    void berechne();
    void zuruecksetzen();

private:
    //Deklaration der Daten der Klasse
    Energieverbrauchsrechner *rechner;

    QDoubleSpinBox *spinLeistung{};
    QDoubleSpinBox *spinLaufzeit{};
    QDoubleSpinBox *spinPreis{};
    QCheckBox      *checkMwst{};
    QLabel         *labelAusgabe{};

//Ende der Klasse
};

//Ende des Include-Guards
#endif
