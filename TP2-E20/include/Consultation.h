#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <string>
#include "Medecin.h"
#include "Patient.h"

class Consultation
{
public:
    Consultation() = default;
	Consultation(Medecin& medecin, Patient& patient, const std::string& date);
    bool verifierSiPatientAjouterAuVecteur(Medecin& medecin, Patient& patient);


    // TODO : la signature de l'opérateur à surcharger

    // opérateur<< pour afficher 
    friend std::ostream& operator << (std::ostream& display, const Consultation& consultation1);

    Medecin* getMedecin() const;
    Patient* getPatient() const;
	const std::string& getDate() const;


private:
    Medecin* medecin_;
    Patient* patient_;
    std::string date_;
};

#endif // CONSULTATION_H