#ifndef HAUPTFENSTER_H
#define HAUPTFENSTER_H

#include <QtGui/QWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QCheckBox>
#include <QtGui/QLabel>

#include "Energieverbrauchsrechner.h"

class Hauptfenster : public QWidget
{
public:
    explicit Hauptfenster(QWidget *parent = nullptr);
    ~Hauptfenster();

private:
    void berechne();
    void zuruecksetzen();

private:
    Energieverbrauchsrechner *rechner;

    QDoubleSpinBox *spinLeistung{};
    QDoubleSpinBox *spinLaufzeit{};
    QDoubleSpinBox *spinPreis{};
    QCheckBox      *checkMwst{};
    QLabel         *labelAusgabe{};
};

#endif
