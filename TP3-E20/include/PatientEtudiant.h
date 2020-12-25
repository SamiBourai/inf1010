#ifndef PATIENTETUDIAT_H
#define PATIENTETUDIAT_H

#include "Patient.h"
#include "Etudiant.h"

class PatientEtudiant : public Etudiant, public Patient
{
public:
	PatientEtudiant() = default;
	
	
	PatientEtudiant(const std::string& nom, const std::string& dateNaissance, const std::string& asssuranceMaladie, const std::string& matricule, const std::string& etablissement);
	
	void afficher(std::ostream& stream)const;
	
	double getTauxRabais()const;
	void setTauxRabais(double tauxRabais);

	const double TAUX_RABAIS = 0.2;

private:
	double tauxRabais_;
};

#endif // PATIENTETUDIAT_H