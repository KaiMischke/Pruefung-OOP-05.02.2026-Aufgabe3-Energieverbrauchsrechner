#include "Energieverbrauchsrechner.h"

Energieverbrauchsrechner::Energieverbrauchsrechner() = default;
Energieverbrauchsrechner::~Energieverbrauchsrechner() = default;

void Energieverbrauchsrechner::begrenze(double &wert, double min, double max) const
{
    if (wert < min) {
        wert = min;
    } else if (wert > max) {
        wert = max;
    }
}

Ergebnis Energieverbrauchsrechner::berechne(double leistung_kW,
                                            double laufzeit_h,
                                            double preis_eur_kWh,
                                            bool mwst_aktiv) const
{
    begrenze(leistung_kW,   0.0, 100000.0);
    begrenze(laufzeit_h,    0.0, 100000.0);
    begrenze(preis_eur_kWh, 0.0, 1000.0);

    Ergebnis erg{};
    erg.energie_kWh  = leistung_kW * laufzeit_h;
    erg.kosten_netto = erg.energie_kWh * preis_eur_kWh;

    if (mwst_aktiv) {
        erg.kosten_brutto = erg.kosten_netto * (1.0 + MEHRWERTSTEUER);
    } else {
        erg.kosten_brutto = erg.kosten_netto;
    }

    return erg;
}
