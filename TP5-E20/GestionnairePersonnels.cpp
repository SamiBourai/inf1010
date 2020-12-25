//! Class GestionnairePersonnel
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "GestionnairePersonnels.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "Foncteurs.h"

//! Trouve et retourne un personnel en le cherchant à partir de son identifiant.
//! \param id   L'identifiant du personnel à trouver.
//! \return     Un pointeur vers le personnel ou nullptr si aucun personnel avec l'identifiant ne peut être trouvé.
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id) const
{
	auto it = personnels_.find(id);
	if (it != personnels_.end())
	{
		return it->second.get();
	}
	return nullptr;
}

//! Fonciton générique qui ajoute un personnel à la liste des personnels
//! \param personnel Le personnel à ajouter
//! \return          Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePersonnels::ajouterPersonnel(Personnel& personnel)
{
	if (!chercherPersonnel(personnel.getId()))
	{
        return personnels_.emplace(personnel.getId(), std::shared_ptr<Personnel>(&personnel)).second;
	}

	return false;
}

//! Fonction qui supprime un personnel de la liste des personnels en rendant son statut estActif à false
//! \param id	  L'identifiant du personnel à supprimer
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePersonnels::supprimerPersonnel(const std::string& id)
{
	Personnel* personnel = chercherPersonnel(id);
	if (personnel)
	{
		personnel->setEstActif(false);
		return true;
	}

	return false;
}

//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gp)
{
    for (const auto& personnel : gp.personnels_)
    {
        personnel.second->afficher(os);
        os << '\n';
    }

    return os;

}

//! Méthode qui retourne la liste de tout le personnel de l'hôpital
//! \return personnels_ la liste du personnel
const std::unordered_map<std::string, std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels() const
{
	return personnels_;
}

//! Méthode générique qui retourne la liste des personnel de type T de l'hôpital
//! \return la liste des personnels
template< typename T >
std::unordered_map<std::string, T*> GestionnairePersonnels::getPersonnelsAvecType() const
{
	std::unordered_map<std::string, T*> personnels;

	for (const auto& personnel : personnels_) {
		T* castedPersonnel = dynamic_cast<T*>(personnel.second.get());
		if (castedPersonnel) {
			personnels.emplace(castedPersonnel->getId(), castedPersonnel);
		}
	}

	return personnels;
}

//! Méthode qui permet de trier les personnels de l'hôpital par le salaire annuel.
//! \return un vecteur des personnels triés
std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> GestionnairePersonnels::getPersonnelsTriesSuivantSalaireAnnuel() const
{
	std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> personnelsOrdonnees(personnels_.begin(), personnels_.end());
    std::sort(personnelsOrdonnees.begin(), personnelsOrdonnees.end(), ComparateurSecondElementPaire<std::string, std::shared_ptr<Personnel>>());

	return personnelsOrdonnees;
}

//! Méthode qui retourne le nombre des personnels
//! \return le nombre de tous le pesonnels
size_t GestionnairePersonnels::getNbPersonnels() const
{
	return personnels_.size();
}

//! Méthode qui retourne le nombre des médecins
//! \return le nombre des médecins
size_t GestionnairePersonnels::getNbMedecins() const
{
	return getPersonnelsAvecType<Medecin>().size();
}

//! Méthode qui retourne le nombre des médecins résidants
//! \return le nombre des médecins résidents
size_t GestionnairePersonnels::getNbMedecinsResidents() const
{
	return getPersonnelsAvecType<MedecinResident>().size();
}
