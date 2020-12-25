//! Class MedecinResident
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef MEDECINRESIDENT_H
#define MEDECINRESIDENT_H

#include <string>
#include "Etudiant.h"
#include "Medecin.h"

class MedecinResident: public Etudiant, public Medecin
{
public:
    MedecinResident() = default;
    MedecinResident(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule,
                    const std::string& etablissement, const std::string NumeroLicenceProvisoire,
                    Specialite specialite, const tm& dateAdhesion);

    void afficher(std::ostream& stream) const override;
    
    double getSalaireAnnuel() const override;

    static constexpr double SALAIRE_DE_BASE_MEDECIN_RESIDENT = 50000;
};

#endif // MEDECINRESIDENT_H
