#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include "Patient.h"


class Medecin
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

    Medecin() = default;
	Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite);

    void ajouterPatient(Patient patient);
    bool supprimerPatient(const std::string& numeroAssuranceMaladie);
    void afficher(std::ostream& stream) const;

    const std::string& getNom() const;
    const std::string& getNumeroLicence() const;
    bool getEstActif() const;
    const Specialite getSpecialite() const;
    const size_t getCapacitePatientAssocies() const;
    const size_t getNombrePatientsAssocies() const;
    std::unique_ptr<std::shared_ptr<Patient>[]> getPatientsAssocies();

    void setNom(const std::string& nom);
    void setNumeroLicence(const std::string& numeroLicence);
    void setEstActif(bool estActif);
    void setSpecialite(Specialite specialite);

private:
    // Attributs
    std::string nom_;
    std::string numeroLicence_;
    Specialite specialite_;
    bool estActif_ = true;

    size_t nbPatientsAssocies_;
    size_t capacitePatientsAssocies_;
    std::unique_ptr<std::shared_ptr<Patient>[]> patientsAssocies_;
};

#endif // MEDECIN_H