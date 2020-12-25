#ifndef MEDECIN_H
#define MEDECIN_H
#include"Personnel.h"
#include <memory>
#include <string>
#include "Patient.h"
#include <vector>


class Medecin : public Personnel {
public:
    enum class Specialite
    {
        first_ = -1,
        Generaliste,
        Cardiologue,
        Dermatologue,
        Gynecologue,
        Pediatre,
        Ophtalmologue,
        Autre,
        last_
    };

    Medecin() = default;
    Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite);

    bool operator+=(Patient* patient);
    bool operator-=(const std::string& numeroAssuranceMaladiePatient);

    
    void virtual afficher(std::ostream& stream) const;

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    void incrementNombreConsultations();

   
    double virtual getSalaireAnnuel() const ;
    double getPrixConsultation() const;

    
    const Specialite getSpecialite() const;
    const size_t getNombrePatientsAssocies() const;
    const std::vector<Patient*>& getPatientsAssocies() const;
    const size_t getNombreConsultations()const;
   
    void setSpecialite(Specialite specialite);
    void setNbConsultations(size_t nombreConsultaion);
    

    static constexpr size_t SALAIRE_DE_BASE_MEDECIN = 100000;


protected:
   
    Specialite specialite_;
  
    size_t nbConsultations_;
    std::vector<Patient*> patientsAssocies_;

private:
    int trouverIndexPatient(const std::string& numeroAssuranceMaladie);

};

#endif // MEDECIN_H