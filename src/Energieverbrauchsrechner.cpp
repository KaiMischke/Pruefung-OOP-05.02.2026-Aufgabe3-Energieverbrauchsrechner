//Einbindung des eigenen Headers
#include "Energieverbrauchsrechner.h"

//Konstruktorinitialisierung 
Energieverbrauchsrechner::Energieverbrauchsrechner() = default;
//Destruktorinitialisierung
Energieverbrauchsrechner::~Energieverbrauchsrechner() = default;

//Definition der Klassenmethode `begrenze`
//Setzt `wert` bei Über- oder Unterschreitung auf 'max' oder `min`
//Durch die Referenz wird `wert` direkt geändert
void Energieverbrauchsrechner::begrenze(double &wert, double min, double max) const
{
    if (wert < min) {
        wert = min;
    } else if (wert > max) {
        wert = max;
    }
}

//Definition der Klassenmethode `berechne`, die `Ergebnis` als Rückgabewert liefert
Ergebnis Energieverbrauchsrechner::berechne(double leistung_kW,
                                            double laufzeit_h,
                                            double preis_eur_kWh,
                                            bool mwst_aktiv) const
{
    //Eingaben auf zulässigen Wertebereich absichern
    begrenze(leistung_kW,   0.0, 100000.0);
    begrenze(laufzeit_h,    0.0, 100000.0);
    begrenze(preis_eur_kWh, 0.0, 1000.0);

    //Erzeugung eines Objekts `erg` vom Typ `Ergebnis` und Initialisierung auf `0`
    Ergebnis erg{};
    //Berechnung der Energie in kWh
    erg.energie_kWh  = leistung_kW * laufzeit_h;
    //Berechnung der Netto-Stromkosten
    erg.kosten_netto = erg.energie_kWh * preis_eur_kWh;

    //Berechnung der Brutto-Stromkosten nur wenn CheckBox Mwst aktiv (true) gesetzt ist
    //Ansonsten brutto = netto
    if (mwst_aktiv) {
        erg.kosten_brutto = erg.kosten_netto * (1.0 + MEHRWERTSTEUER);
    } else {
        erg.kosten_brutto = erg.kosten_netto;
    }

    //Rückgabe des Ergebniswerts
    return erg;
}
