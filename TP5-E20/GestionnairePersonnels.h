//! Class GestionnairePersonnel
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef GESTIONNAIREPERSONNELS_H
#define GESTIONNAIREPERSONNELS_H

#include <memory>
#include "Medecin.h"
#include "MedecinResident.h"
#include <unordered_map>

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

    bool ajouterPersonnel(Personnel& personnel);

	bool supprimerPersonnel(const std::string& id);

	friend std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePesonnel);

	const std::unordered_map<std::string, std::shared_ptr<Personnel>>& getPersonnels() const;

	template< typename T >
	std::unordered_map<std::string, T*> getPersonnelsAvecType() const;

	std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> getPersonnelsTriesSuivantSalaireAnnuel() const;

	size_t getNbPersonnels() const;
	size_t getNbMedecins() const;
	size_t getNbMedecinsResidents() const;

private:

	std::unordered_map<std::string, std::shared_ptr<Personnel>> personnels_;
};

#endif // GESTIONNAIREPERSONNELS_H
