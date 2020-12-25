/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe GestionnairePersonnels.h.
-----------------------------------------------------------------------------------------------------------------------------
*/


#include "GestionnairePersonnels.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr int PERSONNEL_INEXSISTANT = -1;

//! Méhode qui cherche un personnel par son id
//! \param id  du personnel à chercher
//! \return Un pointeur vers le personnel. Le pointeur est nullptr si le personnel n'existe pas dans la liste des personnels.
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id) const
{

	auto variable_Izi = personnels_.find(id);

	if (variable_Izi != personnels_.end())
	{
		return &*variable_Izi->second;
		
	}
	return nullptr;
}

//! Méthode  qui permet de charger les informations des personnels
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succes
bool GestionnairePersonnels::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		personnels_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLignePersonnel(ligne))
			{
				return false;
			}
		}
		return true;
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";

	return false;
}

//! methode qui ajoute un personnel à la liste des personnels
//! \La méthode prend une référence vers l'objet à jouter
//! \return        Un bool qui indique si l'opération a bien fonctionnée
template<typename T>
bool GestionnairePersonnels::ajouterPersonnel(Personnel &personnel)
{
	if (chercherPersonnel(personnel.getId()) == nullptr)
	{
		
		personnels_.insert(std::make_pair(personnel.getId(), std::make_shared<T>(*dynamic_cast<T*> (&personnel))));
		
		return true;
	}

	return false;

}


//! methode qui supprime un personnel de la liste des personnels
//! \Les paramètres : id du personnel a supprimer
//! \return        Un bool qui indique si l'opération a bien fonctionnée

template<typename T>
bool GestionnairePersonnels::supprimerPersonnel(const std::string& id)
{
	
	Personnel* personnelRetourne=chercherPersonnel(id);
	if (personnelRetourne)
	{
		personnelRetourne->setEstActif(false);
		return true;
	}

	return false;
}

//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePersonnels)
{
	
	if constexpr (false)
	{
		for (auto it = gestionnairePersonnels.personnels_.cbegin(); it != gestionnairePersonnels.personnels_.cend(); ++it)
		{
			it->second->afficher(os);
			os << '\n';
		}
		return os;
	}
	
	else
	{
		for (auto i : gestionnairePersonnels.personnels_)
		{
			(i).second->afficher(os);
			os << '\n';
		}
		return os;
		
	}
}

//! Méthode qui retourne la liste de tout le personnel de l'hôpital
//! \return personnels_ la liste du personnel
const std::unordered_map<std::string, std::shared_ptr<Personnel>> GestionnairePersonnels::getPersonnels() const
{
	return personnels_;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :   GestionnairePersonnels::getPersonnelsAvecType()
* Description :  méthode générique Elle retourne unordered_map de string et un pointeur vers le personnel
* Parametre : rien
* Retour :     La méthode parcours personnels_ et retourne un unordered_map de type désiré
----------------------------------------------------------------------------------------------------------------------------
*/
template<typename T>
const std::unordered_map<std::string, T*> GestionnairePersonnels::getPersonnelsAvecType() const{
	
	std::unordered_map<std::string, T*> medecins;

	for (const auto& personnel : personnels_) {
		T* medecin = dynamic_cast<T*>(personnel.second.get());
		if (medecin) {
			medecins.insert(std::pair<std::string,T*>(medecin->getId(),medecin));
		}
	}

	return medecins;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :   GestionnairePersonnels::getPersonnelsTriesSuivantSalaireAnnuel()
* Description : Elle trie le personnel de l’hôpital suivant le salaire annuel
* Parametre : rien
* Retour :    Elle retourne un vecteur de pair de string est shared_ptr<Pesonnel>
----------------------------------------------------------------------------------------------------------------------------
*/
const std::vector< std::pair<std::string, std::shared_ptr<Personnel>>>GestionnairePersonnels:: getPersonnelsTriesSuivantSalaireAnnuel()const {
	
	std::vector< std::pair<std::string, std::shared_ptr<Personnel>>> tabSalairePersonnelTrie;
	
	std::copy(personnels_.begin(), personnels_.end(),back_inserter(tabSalairePersonnelTrie));
	std::sort(tabSalairePersonnelTrie.begin(),tabSalairePersonnelTrie.end(), ComparateurSecondElementPaire<std::string,std::shared_ptr<Personnel>>());
	return tabSalairePersonnelTrie;
}

//! Méthode qui retourne le nombre des personnels
//! \return le nombre de tous le pesonnels
size_t GestionnairePersonnels::getNbPersonnels() const
{
	return personnels_.size();
}



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  GestionnairePersonnels::getNbMedecins()
* Description :  Retourner le nombre de medecins
* Parametre : rien
* Retour :     Retourner le nombre de medecins
----------------------------------------------------------------------------------------------------------------------------
*/
size_t GestionnairePersonnels::getNbMedecins() const
{
	return getPersonnelsAvecType<Medecin>().size();
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :   GestionnairePersonnels::getNbMedecinsResidents()
* Description :  Retourner le nombre de medecinsResident
* Parametre : rien
* Retour :     Retourner le nombre de medecinsResidents
----------------------------------------------------------------------------------------------------------------------------
*/
size_t GestionnairePersonnels::getNbMedecinsResidents() const
{
	return getPersonnelsAvecType<MedecinResident>().size();
}



//! Méthode qui lit les attributs d'un medecin
//! \param ligne  Le string qui contient les attributs
// return un bool si l'operation a marcher ou pas 
bool GestionnairePersonnels::lireLignePersonnel(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePersonnel;
	std::string nomPersonnel;
	std::string id;
	std::string dateAdhesion;

	std::string dateDeNaissance;
	std::string matricule;
	std::string etablissement;

	int indexSpecialite;

	if (stream >> indexTypePersonnel >> std::quoted(nomPersonnel) >> std::quoted(id)>> std::quoted(dateAdhesion))
	{	tm dateTransformeeEnTm = convertirStringDate(dateAdhesion);
	Medecin m; MedecinResident mR;
		switch (to_enum<GestionnairePersonnels::TypePersonnel, int>(indexTypePersonnel)) {
		case TypePersonnel::Medecin:
			stream >> indexSpecialite;
			 m= Medecin(nomPersonnel, id, to_enum<Medecin::Specialite, int>(indexSpecialite), dateTransformeeEnTm);
			ajouterPersonnel<Medecin>(m);
			break;
		case TypePersonnel::MedecinResident:
			stream >> std::quoted(dateDeNaissance) >> std::quoted(matricule) >> std::quoted(etablissement) >> indexSpecialite;
			 mR= MedecinResident(nomPersonnel, dateDeNaissance, matricule, etablissement, id, to_enum<Medecin::Specialite, int>(indexSpecialite), dateTransformeeEnTm);
			 ajouterPersonnel<MedecinResident>(mR);
			 break;
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
		}
		return true;
	}

	return false;
}