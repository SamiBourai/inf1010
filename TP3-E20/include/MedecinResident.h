#ifndef MEDECINRESIDENT_H
#define MEDECINRESIDENT_H

#include <string>
#include "Etudiant.h"
#include"Medecin.h"


class MedecinResident: public Medecin, public Etudiant {
public: 
	 MedecinResident() = default;


	MedecinResident (const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablisssement, const std::string& numeroLicence, Specialite specialite);


	 void afficher(std::ostream& stream) const override ;




	double getSalaireAnnuel()const override;


	static constexpr size_t SALAIRE_DE_BASE_MEDECIN_RESIDENT = 50000;



};
#endif // MEDECINRESIDENT_H