//! Class Medecin
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include "Patient.h"
#include "Personnel.h"
#include <vector>

class Medecin : public Personnel
{
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

   
    Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite, const tm& dateDebut);
    Medecin() = default;
    bool operator+=(Patient* patient);
    bool operator-=(const std::string& numeroAssuranceMaladiePatient);

    virtual void afficher(std::ostream& stream) const override;
    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    void incrementNombreConsultations();

    virtual double getSalaireAnnuel() const override;

    double getPrixConsultation() const;
    const Specialite getSpecialite() const;
    const size_t getNombrePatientsAssocies() const;
    const size_t getNombreConsultations() const;

    const std::vector<Patient*>& getPatientsAssocies() const;

    void setSpecialite(Specialite specialite);

    static constexpr double SALAIRE_DE_BASE_MEDECIN = 100000;

private:
    int trouverIndexPatient(const std::string& numeroAssuranceMaladie);

protected:
    // Attributs
    Specialite specialite_;
    std::vector<Patient*> patientsAssocies_;
    size_t nombreConsultations_;
};

#endif // MEDECIN_H