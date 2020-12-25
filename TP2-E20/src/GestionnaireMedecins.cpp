/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 23-may-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe GestionnaireMedecin.h .
-----------------------------------------------------------------------------------------------------------------------------
*/

#include "GestionnaireMedecins.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr size_t CAPACITE_MEDECINS_INITIALE = 2;
constexpr int MEDECIN_INEXSISTANT = -1;
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :GestionnaireMedecins::GestionnaireMedecins()
* Description :  c'est le conctructeur par default de la classe GestionnairePatients
* Parametre : -
* Retour : -
----------------------------------------------------------------------------------------------------------------------------
*/

GestionnaireMedecins::GestionnaireMedecins()
	:medecins_(std::vector<std::shared_ptr<Medecin>>(CAPACITE_MEDECINS_INITIALE))
{
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePatients::GestionnairePatients()
* Description :  c'est le conctructeur par copie  de la classe GestionnaireMedecins
* Parametre : const GestionnaireMedecins& gestionnaireMedecins
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/
GestionnaireMedecins::GestionnaireMedecins(const GestionnaireMedecins& gestionnaireMedecins) {
	for (size_t i = 0; i < gestionnaireMedecins.medecins_.size(); i++)
	{
		medecins_.push_back(std::make_shared<Medecin>(*gestionnaireMedecins.medecins_[i]));

	}
	
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :GestionnairePatients& GestionnairePatients::operator=()
* Description : operateur d'affectation
* Parametre : const GestionnaireMedecins & gestionnaireMedecins
* Retour : *this
----------------------------------------------------------------------------------------------------------------------------
*/
GestionnaireMedecins& GestionnaireMedecins:: operator = (const GestionnaireMedecins & gestionnaireMedecins){
	if (this != &gestionnaireMedecins)
	{
		for (size_t i = 0; i < gestionnaireMedecins.medecins_.size(); i++)
		{
			medecins_.push_back(gestionnaireMedecins.medecins_[i]);
		}

	}


	return *this;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin* GestionnaireMedecins::chercherMedecin()
* Description :  Chercher un Medecin dans la liste medecins_ par son numéro de licence
* Parametre :const std::string& numeroLicence
* Retour : Retourner le pointeur vers le patient si trouvé, sinon retourner nullptr
----------------------------------------------------------------------------------------------------------------------------
*/

Medecin* GestionnaireMedecins::chercherMedecin(const std::string& numeroLicence)
{
	for (size_t i = 0; i < medecins_.size(); i++)
	{

		
		if (medecins_[i]->getNumeroLicence() == numeroLicence)
		{
			return &*medecins_[i];
			
		}
	}

	return nullptr;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : bool GestionnairePatients::chargerDepuisFichier()
* Description :  Méthode  qui permet de charger les informations des patients depuis un fichier
* Parametre : param nomFichier  
* Retour : Un bool qui indique si le fichier a été chargé avec succès
----------------------------------------------------------------------------------------------------------------------------
*/


bool GestionnaireMedecins::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		
		medecins_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (lireLigneMedecin(ligne) == false)
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

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : l'operateur +=
* Description :  Méthode qui ajoute un medecin a liste de medecin
* Parametre : medecin
* Retour :    false si l'operation a echouee sinon un vrai si elle a reussi.
----------------------------------------------------------------------------------------------------------------------------
*/
bool GestionnaireMedecins::operator+=(const Medecin& medecin1) {

	bool estInExistant = chercherMedecin(medecin1.getNumeroLicence());  // ici il faut juste verifier s'il existe ou pas
	
	if (estInExistant == true)
	{
		return false;
	}
	else
	{
		medecins_.push_back(std::make_shared<Medecin>(medecin1));
		return true;
	}
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : l'operateur -=
* Description :  Méthode qui supprime un medecin a liste de medecin
* Parametre : medecin
* Retour :    false si l'operation a echouee sinon un vrai si elle a reussi.
----------------------------------------------------------------------------------------------------------------------------
*/

bool GestionnaireMedecins::operator-=(const std::string& numLicence) {
	bool activite = false;

	if (trouverIndexMedecin(numLicence)!=MEDECIN_INEXSISTANT)
	{
		medecins_[trouverIndexMedecin(numLicence)]->setEstActif(activite);
		return !activite;
	}
	else
	{
		return activite;
	}

}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : operator <<
* Description :  Méthode qui affiche les informations d'un medeicn
* Parametre :std::ostream& display, const GestionnaireMedecins& medecins
* Retour :   display.
----------------------------------------------------------------------------------------------------------------------------
*/
std::ostream& operator << (std::ostream& display, const GestionnaireMedecins& medecins) {

	for (size_t i = 0; i < medecins.medecins_.size(); i++)
	{
		display << *medecins.medecins_[i] << '\n';

	}
	return display;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : getNbMedecins() const
* Description :  getter 
* Parametre : rien
* Retour :  medecins_.size();
----------------------------------------------------------------------------------------------------------------------------
*/

size_t GestionnaireMedecins::getNbMedecins() const
{
	return medecins_.size();
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :const std::vector < std::shared_ptr<Medecin>>& GestionnaireMedecins::getMedecins() cons
* Description :  getter
* Parametre : rien
* Retour :  retourne une reference constante vers le vecteur medecins_
----------------------------------------------------------------------------------------------------------------------------
*/

const std::vector < std::shared_ptr<Medecin>>& GestionnaireMedecins::getMedecins() const {
	return medecins_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : getCapaciteMedecins() const
* Description :  getter
* Parametre : rien
* Retour :  medecins_.capacity();
----------------------------------------------------------------------------------------------------------------------------
*/
size_t GestionnaireMedecins::getCapaciteMedecins() const
{

	return medecins_.capacity();
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :GestionnairePatients::lireLigneMedecin()
* Description : Méthode qui lit les attributs d'un patient
* Parametre : const std::string & ligne
* Retour : bool - true si y a eu succes / false si y a eu echec
----------------------------------------------------------------------------------------------------------------------------
*/

bool GestionnaireMedecins::lireLigneMedecin(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomMedecin;
	std::string numeroLicence;
	int indexSpecialite;




	if (stream >> std::quoted(nomMedecin) >> std::quoted(numeroLicence) >> indexSpecialite)
	{
		

		bool enLu = *this += Medecin(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite));
		return enLu;

		
	}

	return false;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :   GestionnaireMedecins::trouverIndexMedecin()
* Description : Méthode trouve l'index d'un medecin et qui le retourne et ce, grace au numero de licence
* Parametre : const std::string& numeroLicenc
* Retour :   Si le medecin n'existe pas, retourner -1 (MEDECIN_INEXSISTANT)
----------------------------------------------------------------------------------------------------------------------------
*/
int GestionnaireMedecins::trouverIndexMedecin(const std::string& numeroLicence)
{
	
	for (std::size_t i = 0; i <medecins_.size(); i++)
	{
		if (medecins_[i]->getNumeroLicence() == numeroLicence)
		{
			return static_cast<int>(i);
		}
	}
	return MEDECIN_INEXSISTANT;
}
