#ifndef GESTIONNAIREPATIENTS_H
#define GESTIONNAIREPATIENTS_H

#include <string>
#include "Patient.h"
#include <memory>
#include <vector>

class GestionnairePatients
{
public:
    GestionnairePatients();  // defautl constructure
    GestionnairePatients(const GestionnairePatients& gestionnairePatiens);  // copy constructure
    GestionnairePatients& operator=(const GestionnairePatients& gestionnairePatients); // operator affectation


   

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);
   

    // TODO : signature des opérateurs à surcharger.

    // opérateur<< qui remplace afficher // void afficher(std::ostream& stream) const;
    friend std::ostream& operator << (std::ostream& display, const GestionnairePatients& patients);


    // opérateur+= qui remplace ajouterPatient //bool ajouterPatient(const Patient& patient);
    bool operator+=(const Patient& patient1);

    
    // TODO : signature de getPatients()  retourne une reference constante vers le vecteur patients_
    std::vector < std::shared_ptr<Patient>> getPatients() const;

    static constexpr size_t NB_PATIENT_MAX = 16;
    size_t getNbPatients() const;

private:
    bool lireLignePatient(const std::string& ligne);

    //TODO : remplacer le tableau par un vecteur de shared_ptr de Patient
    std::vector < std::shared_ptr<Patient>> patients_;
   
   
};

#endif // GESTIONNAIREPATIENTS_H