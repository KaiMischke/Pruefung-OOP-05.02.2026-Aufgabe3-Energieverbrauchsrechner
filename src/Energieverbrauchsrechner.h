//Beginn Include-Guard
//Schutz vor Mehrfacheinbindung der Header-Datei
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

//Deklaration der Logikklasse
class Energieverbrauchsrechner
{
public:
    //Deklaration des Konstruktors
    Energieverbrauchsrechner();
    //Deklaration des Destruktors
    ~Energieverbrauchsrechner();

    //Deklaration der Klassenmethode `berechne`
    Ergebnis berechne(double leistung_kW,
                      double laufzeit_h,
                      double preis_eur_kWh,
                      bool mwst_aktiv) const;

private:
    //Deklaration der Klassenmethode `begrenze`
    void begrenze(double &wert, double min, double max) const;

//Ende der Klassendeklaration 
};

//Ende des Include-Guards
#endif

