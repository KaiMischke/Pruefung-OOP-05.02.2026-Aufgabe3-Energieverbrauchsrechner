#ifndef ENERGIEVERBRAUCHSRECHNER_H
#define ENERGIEVERBRAUCHSRECHNER_H

// MwSt als Konstante
constexpr double MEHRWERTSTEUER = 0.19; // 19%

// Ergebnis-Datentyp
struct Ergebnis {
    double energie_kWh;
    double kosten_netto;
    double kosten_brutto;
};

class Energieverbrauchsrechner
{
public:
    Energieverbrauchsrechner();
    ~Energieverbrauchsrechner();

    Ergebnis berechne(double leistung_kW,
                      double laufzeit_h,
                      double preis_eur_kWh,
                      bool mwst_aktiv) const;

private:
    void begrenze(double &wert, double min, double max) const;
};

#endif
