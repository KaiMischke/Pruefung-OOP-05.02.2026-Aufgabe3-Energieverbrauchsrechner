#include "Hauptfenster.h"

#include <QtGui/QPushButton>
#include <QtGui/QFormLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

Hauptfenster::Hauptfenster(QWidget *parent)
    : QWidget(parent),
      rechner(new Energieverbrauchsrechner())
{
    setWindowTitle("Energieverbrauchsrechner (Lean)");

    // Eingabe: Leistung (kW)
    spinLeistung = new QDoubleSpinBox(this);
    spinLeistung->setRange(0.0, 100000.0);
    spinLeistung->setDecimals(3);
    spinLeistung->setValue(1.5);
    spinLeistung->setSuffix(" kW");

    // Eingabe: Laufzeit (h)
    spinLaufzeit = new QDoubleSpinBox(this);
    spinLaufzeit->setRange(0.0, 100000.0);
    spinLaufzeit->setDecimals(2);
    spinLaufzeit->setValue(2.0);
    spinLaufzeit->setSuffix(" h");

    // Eingabe: Strompreis (€/kWh) - per Tastatur
    spinPreis = new QDoubleSpinBox(this);
    spinPreis->setRange(0.0, 1000.0);
    spinPreis->setDecimals(4);
    spinPreis->setValue(0.35);
    spinPreis->setSuffix(" €/kWh");

    // Option: MwSt
    checkMwst = new QCheckBox("MwSt. (19%) berücksichtigen", this);
    checkMwst->setChecked(true);

    // Ausgabe
    labelAusgabe = new QLabel("Bitte Werte eingeben und berechnen.", this);
    labelAusgabe->setWordWrap(true);

    // Buttons
    auto *btnBerechnen = new QPushButton("Berechnen", this);
    auto *btnReset     = new QPushButton("Reset", this);

    // Layout
    auto *form = new QFormLayout();
    form->addRow("Leistung:",  spinLeistung);
    form->addRow("Laufzeit:",  spinLaufzeit);
    form->addRow("Strompreis:", spinPreis);
    form->addRow("",          checkMwst);

    auto *buttons = new QHBoxLayout();
    buttons->addWidget(btnBerechnen);
    buttons->addWidget(btnReset);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(buttons);
    root->addWidget(labelAusgabe);
    setLayout(root);

    // Events (Lambda-connects wie in deinem Quiz-Projekt)
    connect(btnBerechnen, &QPushButton::clicked, this, [this] {
        berechnen();
    });

    connect(btnReset, &QPushButton::clicked, this, [this] {
        zuruecksetzen();
    });
}

Hauptfenster::~Hauptfenster()
{
    delete rechner;
}

void Hauptfenster::berechnen()
{
    Ergebnis erg = rechner->berechne(
        spinLeistung->value(),
        spinLaufzeit->value(),
        spinPreis->value(),
        checkMwst->isChecked()
    );

    QString text =
        "Energie: " + QString::number(erg.energie_kWh, 'f', 2) + " kWh\n" +
        "Kosten:  " + QString::number(erg.kosten_brutto, 'f', 2) + " €";

    labelAusgabe->setText(text);
}

void Hauptfenster::zuruecksetzen()
{
    spinLeistung->setValue(1.5);
    spinLaufzeit->setValue(2.0);
    spinPreis->setValue(0.35);
    checkMwst->setChecked(true);
    labelAusgabe->setText("Zurückgesetzt. Bitte neu berechnen.");
}
