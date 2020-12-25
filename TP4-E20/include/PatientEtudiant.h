//! Class PatientEtudiant
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef PATIENTETUDIAT_H
#define PATIENTETUDIAT_H

#include "Patient.h"
#include "Etudiant.h"

class PatientEtudiant : public Patient, public Etudiant
{
public:
	PatientEtudiant() = default;
	
	PatientEtudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie,const tm& dateAdhesion, const std::string& matricule, const std::string& etablissement );

	void afficher(std::ostream& stream) const override;

	const double getTauxRabais() const;

	void setTauxRabais(double tauxRabais);

	const double TAUX_RABAIS = 0.2;

private:
	double tauxRabais_ = TAUX_RABAIS;
};

#endif // PATIENTETUDIAT_H