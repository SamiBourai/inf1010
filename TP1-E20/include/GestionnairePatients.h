#ifndef GESTIONNAIREPATIENTS_H
#define GESTIONNAIREPATIENTS_H

#include <string>
#include "Patient.h"
#include <memory>

class GestionnairePatients
{
public:
    GestionnairePatients();

	bool ajouterPatient(const Patient& patient);
    std::shared_ptr<Patient> chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);
    void afficher(std::ostream& stream) const;

    size_t getNbPatients()const;

    static constexpr size_t NB_PATIENT_MAX = 16;

private:
    bool lireLignePatient(const std::string& ligne);

	Patient patients_[NB_PATIENT_MAX];
    size_t nbPatients_;
};

#endif // GESTIONNAIREPATIENTS_H