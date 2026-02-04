// Einbinden des eigenen Headers
#include "Hauptfenster.h"

//Einbinden der benötigten GUI-Klassen
#include <QtGui/QPushButton>
#include <QtGui/QFormLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

// Beginn des Konstruktors
Hauptfenster::Hauptfenster(QWidget *parent)
    : QWidget(parent),
      rechner(new Energieverbrauchsrechner())
{	
    //Fenstertitel setzen
    setWindowTitle("Energieverbrauchsrechner");
    
    //Erzeut ein neues Eingabefeld für die Leistung
    spinLeistung = new QDoubleSpinBox(this);
    //Festlegung des erlaubten Wertebereichs
    spinLeistung->setRange(0.0, 100000.0);
    //Bestimmung der Anzahl Nachkommastellen
    spinLeistung->setDecimals(3);
    //Festlegung eines Standardwertes bei Start oder Reset
    spinLeistung->setValue(1.5);
    //Anzeige der Einheit für die Leistung direkt im Eingabefeld
    spinLeistung->setSuffix(" kW");

    //Erzeugt ein neues Eingabefeld für die Lauftzeit
    spinLaufzeit = new QDoubleSpinBox(this);
    //Nachfolgende Eingaben wie schon beim Eingabefeld für die Leistung
    spinLaufzeit->setRange(0.0, 100000.0);
    spinLaufzeit->setDecimals(2);
    spinLaufzeit->setValue(2.0);
    spinLaufzeit->setSuffix(" h");

    //Erzeug ein neues Eingabefeld für den Strompreis
    spinPreis = new QDoubleSpinBox(this);
    //Nachfolgende Eingaben wie schon beim Eingabefeld für die Leistung
    spinPreis->setRange(0.0, 1000.0);
    spinPreis->setDecimals(4);
    spinPreis->setValue(0.35);
    spinPreis->setSuffix(" €/kWh");

    //Erzeugt eine Checkbox um optional die Mehrwertsteuer in der Berechnung zu berücksichtigen
    checkMwst = new QCheckBox("MwSt. (19%) berücksichtigen", this);
    //Standardmäßig ist die Checkbox aktiviert, also true
    checkMwst->setChecked(true);

    //Erzeugt ein neues Ausgabefeld für die Berechnungsergebnisse und Hinweistext
    labelAusgabe = new QLabel("Bitte Werte eingeben und berechnen.", this);
    //Erzeugt einen automatischen Zeilenumbruch, damit längerer Text nicht über das GUI-Fenster hinausläuft
    labelAusgabe->setWordWrap(true);

    //Erzeugt zwei Buttons, einen zum Start der Berechnung und einen, um den Energieverbrauchsrechner 
    //auf die Standardeinstellungen zurückzusezten.
    auto *btnBerechnen = new QPushButton("Berechnen", this);
    auto *btnReset     = new QPushButton("Reset", this);

    //Bestimmung der Anzeigereihefolge der Eingabemasken (Festlegung des Layouts der Werteeingabe)
    auto *form = new QFormLayout();
    form->addRow("Leistung:",   spinLeistung);
    form->addRow("Laufzeit:",   spinLaufzeit);
    form->addRow("Strompreis:", spinPreis);
    form->addRow("",            checkMwst);

    //Orndet die Buttons Berechnen und Reset nebeneinander an (Festlegung des Layouts der Buttoneingabe)
    auto *buttons = new QHBoxLayout();
    buttons->addWidget(btnBerechnen);
    buttons->addWidget(btnReset);

    //Legt die Anzeigereihenfolge des gesamten GUI-Fensters fest (Layout des Hauptfensters)
    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(buttons);
    root->addWidget(labelAusgabe);
    //Weist das Layout dem Fenster zu
    setLayout(root);

    //Festlegung der Signal-Slot-Verbindungen (Events)
    //Wenn der Button Berechnen angelickt wird, wird die Methode berechne() aufgerufen
    connect(btnBerechnen, &QPushButton::clicked, this, [this] {
        berechne();
    });

    //Wenn der Button Reset angelickt wird, wird die Methode zuruecksetzen() aufgerufen
    connect(btnReset, &QPushButton::clicked, this, [this] {
        zuruecksetzen();
    });

//Ende der Konstruktordefinition
}

//Definition des Destruktors
//Freigabe des reservierten Speichers
Hauptfenster::~Hauptfenster()
{
    delete rechner;
}

//Definition der Klassenmethode `berechne`
//Die GUI ruft die Klassenmethode `berechne` der Logikklasse `Energieverbrauchsrechner` auf, übergibt
//ihr die Eingabedaten (Leistung, Laufzeit, Preis, MwSt) und erhält das berechnete Ergebnis als Rückgabewert
void Hauptfenster::berechne()
{
    Ergebnis erg = rechner->berechne(
        spinLeistung->value(),
        spinLaufzeit->value(),
        spinPreis->value(),
        checkMwst->isChecked()
    );

    //Baut den Ausgabetext zusammen, legt über `f` und `Zahl` die Anzahl der Nachkommastellen fest 
    QString text =
        "Energie: " + QString::number(erg.energie_kWh, 'f', 2) + " kWh\n" +
        "Kosten:  " + QString::number(erg.kosten_brutto, 'f', 2) + " €\n" +
        "Preis:   " + QString::number(spinPreis->value(), 'f', 4) + " €/kWh";

    //Zeigt den Asugabetext in der GUI an
    labelAusgabe->setText(text);
}

//Definition der Klassenmethode zuruecksetzen
void Hauptfenster::zuruecksetzen()
{
    //Setzt Leistung, Laufzeit, Preis und MwSt auf die Standardwerte (Ausgangszustand)
    spinLeistung->setValue(1.5);
    spinLaufzeit->setValue(2.0);
    spinPreis->setValue(0.35);
    checkMwst->setChecked(true);
    //Gibt den Hinweistext aus, dass der Rechner zurückgesetzt wurde
    labelAusgabe->setText("Zurückgesetzt. Bitte neu berechnen.");
}
