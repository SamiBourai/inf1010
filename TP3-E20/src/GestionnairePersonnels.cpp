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

//! Méthode qui cherche un personnel par son id
//! \param id L'identifiant du personnel à chercher
//! \return Un pointeur vers le personnel. Le pointeur est nullptr si le personnel n'existe pas dans la liste des personnels.
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id)
{
	for (const auto& personnel : personnels_)
	{
		if (*personnel == id)
		{
			return personnel.get();
		}
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

//! Operateur qui ajoute un personnel à la liste des personnels
//! \param personnel Le personnel à ajouter
//! \return          Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePersonnels::operator+=(Personnel* personnel)
{
	if (personnel && !chercherPersonnel(personnel->getId()))
	{
		

		MedecinResident* ptr_PE = dynamic_cast<MedecinResident*>(personnel);
		Medecin* ptr_M = dynamic_cast<Medecin*>(personnel);
		//TODO : vérifier si personnel est un MedecinResidant. Conversion dynamique
		if (ptr_PE != nullptr) {
			//TODO : Ajouter un objet de type MedecinResident au personnels_. Conversion dynamique
			personnels_.push_back(std::make_shared<MedecinResident>(*ptr_PE));
		}
		
		//TODO : vérifier si personnel est un Medecin. Conversion dynamique
		else if (ptr_M!=nullptr) {
			//TODO : Ajouter un objet de type Medecin au personnels_. Conversion dynamique
			personnels_.push_back(std::make_shared<Medecin>(*ptr_M));
		}
		else {
			assert(false);
		}

		return true;
	}

	return false;
}

//! Operateur qui supprime un personnel de la liste des personnels en rendant son statut estActif à false
//! \param id	  L'identifiant du personnel à supprimer
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePersonnels::operator-=(const std::string& id)
{
	int indexPersonnel = trouverIndexPersonnel(id);
	if (indexPersonnel != PERSONNEL_INEXSISTANT)
	{
		personnels_[indexPersonnel]->setEstActif(false);
		return true;
	}

	return false;
}

//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePersonnels)
{
	for (const auto& personnel : gestionnairePersonnels.personnels_)
	{
		personnel->afficher(os);
		os << '\n';// Afficher les information d'un personnel
	}

	return os;
}

//! Méthode qui retourne la liste de tout le personnel de l'hôpital
//! \return personnels_ la liste du personnel
const std::vector<std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels() const
{	
	return personnels_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :GestionnairePersonnels::getMedecins()
* Description : Chercher les médecins  parmis tous les personnels  le mettre dans le vecteur declaré
* Parametre : rien
* Retour :    Retourner un vecteur de Medecin*

----------------------------------------------------------------------------------------------------------------------------
*/
const std::vector<Medecin*> GestionnairePersonnels::getMedecins() const {



	std::vector <Medecin*>tousMedecin;

	
	for (size_t i = 0; i < personnels_.size(); i++)
	{
		Medecin* ptr_M = dynamic_cast<Medecin*>(&*personnels_[i]);

		if (ptr_M != nullptr)
		{
			tousMedecin.push_back(ptr_M);
		}
	}


	return tousMedecin;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePersonnels::getMedecinsResidents()
* Description : Chercher les medecin resident  parmis tous les personnels  et le mettre dans le vecteur declaré
* Parametre : rien
* Retour :    Retourner un vecteur de MedecinResident*

----------------------------------------------------------------------------------------------------------------------------
*/
const std::vector<MedecinResident*> GestionnairePersonnels::getMedecinsResidents() const {

	std::vector <MedecinResident*>tousMedecinResident;

	for (size_t i = 0; i < personnels_.size(); i++)
	{
		MedecinResident* ptr_M = dynamic_cast<MedecinResident*>(&*personnels_[i]);

		if (ptr_M != nullptr)
		{
			tousMedecinResident.push_back((ptr_M));
		}
	}


	return tousMedecinResident;
}




/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePersonnels::getNbPersonnels() 
* Description : Retourner le nombre des personnels
* Parametre : rien
* Retour :    Retourner le nombre des personnels
----------------------------------------------------------------------------------------------------------------------------
*/
size_t GestionnairePersonnels::getNbPersonnels() const {
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
size_t GestionnairePersonnels::getNbMedecins() const {

	return getMedecins().size();
}




/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :   GestionnairePersonnels::getNbMedecinsResidents()
* Description :  Retourner le nombre de medecinsResident
* Parametre : rien
* Retour :     Retourner le nombre de medecinsResidents
----------------------------------------------------------------------------------------------------------------------------
*/
size_t GestionnairePersonnels::getNbMedecinsResidents() const { 
	return getMedecinsResidents().size(); 
}


//! Méthode qui lit les attributs d'un personnel
//! \param ligne  Le string qui contient les attributs
//! \retourne un bool si l'operation a reussi ou echouer

bool GestionnairePersonnels::lireLignePersonnel(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePersonnel;
	std::string nomPersonnel;
	std::string id;

	std::string dateDeNaissance;
	std::string matricule;
	std::string etablissement;

	int indexSpecialite;

	if (stream >> indexTypePersonnel >> std::quoted(nomPersonnel) >> std::quoted(id))
	{
		
		 
		switch (to_enum<GestionnairePersonnels::TypePersonnel, int>(indexTypePersonnel)) {

		case TypePersonnel::Medecin:
			stream >> indexSpecialite;
			
			 *this += new Medecin(nomPersonnel, id, to_enum<Medecin::Specialite, int>(indexSpecialite));
			return true;

			case TypePersonnel::MedecinResident:
			stream >>std::quoted(dateDeNaissance) >> std::quoted(matricule) >>  std::quoted(etablissement) >> indexSpecialite;

			
			*this += new MedecinResident(nomPersonnel,dateDeNaissance,matricule, etablissement,id, to_enum<Medecin::Specialite, int>(indexSpecialite));
			 
			return true;
			default:
				assert(false);
		}


	}

	return false;
}

//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
//! \return             int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
int GestionnairePersonnels::trouverIndexPersonnel(const std::string& id)
{
	for (std::size_t i = 0; i < personnels_.size(); i++)
	{
		if (*personnels_[i] == id)
		{
			return static_cast<int>(i);
		}
	}
	return PERSONNEL_INEXSISTANT;
}
