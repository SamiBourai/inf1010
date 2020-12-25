#ifndef GESTIONNAIREPERSONNELS_H
#define GESTIONNAIREPERSONNELS_H

#include <memory>
#include "Medecin.h"
#include "MedecinResident.h"
#include <unordered_map>
#include"Foncteurs.h"

class GestionnairePersonnels
{
public:
	enum class TypePersonnel
	{
		first_ = -1,
		Medecin,
		MedecinResident,
		last_
	};

	GestionnairePersonnels() = default;

	Personnel* chercherPersonnel(const std::string& id) const;
	bool chargerDepuisFichier(const std::string& nomFichiers);

	
	template<typename T>
	bool ajouterPersonnel(Personnel& personnel);
	
	template<typename T>
	bool supprimerPersonnel(const std::string& id);

	friend std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePesonnel);

	
	const std::unordered_map<std::string, std::shared_ptr<Personnel>> getPersonnels() const;


	template<typename T>
	const std::unordered_map<std::string, T*> getPersonnelsAvecType()const;


	
	const std::vector< std::pair<std::string, std::shared_ptr<Personnel>>>getPersonnelsTriesSuivantSalaireAnnuel()const;


	size_t getNbPersonnels() const;
	size_t getNbMedecins() const;
	size_t getNbMedecinsResidents() const;

	static const int NB_PATIENT_MAX = 100;

private:
	bool lireLignePersonnel(const std::string& ligne);
	std::unordered_map<std::string, std::shared_ptr<Personnel>> personnels_;
};

#endif // GESTIONNAIREPERSONNELS_H

