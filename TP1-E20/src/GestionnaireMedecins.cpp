

/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 11-may-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe GestionnaireMedecin.h .
-----------------------------------------------------------------------------------------------------------------------------
*/

// TODO: Inclure la définition de la classe appropriée
#include"GestionnaireMedecins.h"
#include "typesafe_enum.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

constexpr size_t CAPACITE_MEDECINS_INITIALE = 2;
constexpr int MEDECIN_INEXSISTANT = -1;

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnaireMedecins::GestionnaireMedecins()
* Description : Constructeur par défaut en utilisant la liste d'initialisation
	 Utilisez CAPACITE_MEDECINS_INITIALE pour la taille initiale de medecins_ (tableau de taille dynamique)

* Parametre : ce dernier prend comme parametre tous les attributs de la classe GestionnaireMedecins
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/

GestionnaireMedecins::GestionnaireMedecins(): nbMedecins_(0),capaciteMedecins_(CAPACITE_MEDECINS_INITIALE), 
medecins_(std::make_unique<std::shared_ptr<Medecin>[]>(CAPACITE_MEDECINS_INITIALE))
{
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnaireMedecins::ajouterMedecin()
* Description :  Méthode qui ajoute un médecin à la liste des patients
* Parametre : std::unique_ptr<Medecin> medecin
* Retour : rien
----------------------------------------------------------------------------------------------------------------------------
*/

void GestionnaireMedecins::ajouterMedecin(std::unique_ptr<Medecin> medecin)
{
	

	constexpr unsigned int AUGMENTATION_NOMBRE_MEDECINS = 2;
	


	if (nbMedecins_ >= capaciteMedecins_)
	{
		// Si pas assez de mémoire, doubler la taille du tableau (AUGMENTATION_NOMBRE_MEDECINS)
		capaciteMedecins_ *= AUGMENTATION_NOMBRE_MEDECINS;

		

		std::unique_ptr < std::shared_ptr<Medecin>[]> medecinXX = std::make_unique<std::shared_ptr<Medecin>[]>(capaciteMedecins_);

		
		for (size_t i = 0; i < nbMedecins_; i++)
		{
			medecinXX[i] = medecins_[i];    //(medecins_[i]); // Ajouter le medecin au tableau
			
		}
		medecins_ = std::move(medecinXX);// Utiliser std::unique_ptr<std::shared_ptr<Medecin>[]> ainsi que std::move pour transférer le ownership
	}

	medecins_[nbMedecins_] = std::move(medecin); //std::make_shared<Medecin>(medecin);// du tableau temporaire vers le tableau membre medecins_

	nbMedecins_++;



}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : std::shared_ptr<Medecin> GestionnaireMedecins::chercherMedecin()
* Description :  Méthode qui cherche un médecin à la liste des medecins
* Parametre : const std::string& numeroLicence
* Retour :  Retourner le pointeur vers le medecin si trouvé sinon retourner nullptr
----------------------------------------------------------------------------------------------------------------------------
*/
std::shared_ptr<Medecin> GestionnaireMedecins::chercherMedecin(const std::string& numeroLicence) {

	
	

	for (size_t i = 0; i < nbMedecins_; i++)
	{
		if (trouverIndexMedecin(numeroLicence)!= MEDECIN_INEXSISTANT)
		{
			return medecins_[trouverIndexMedecin(numeroLicence)]; 
		}
		else
		{
			return nullptr;
		}
	}
	
	

}



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : bool GestionnaireMedecins::chargerDepuisFichier()
* Description : Méthode  qui permet de charger les informations des medecins depuis un fichier
* Parametre : const std::string& nomFichier
* Retour :   Un bool qui indique si le fichier a été chargé avec succes
----------------------------------------------------------------------------------------------------------------------------
*/

bool GestionnaireMedecins::chargerDepuisFichier(const std::string& nomFichier)
{
	std::string ligneComplete;
	std::ifstream fichier(nomFichier);
	nbMedecins_ = 0;
	if (fichier)
	{
		// TODO : Envoyer chaque ligne à lireLigneMedecin()

			while (getline(fichier,ligneComplete))
			{
				//std::getline(fichier, ligneComplete);
				if (!lireLigneMedecin(ligneComplete))
					return false;

			}
			return true;

		
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";

	return false;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :supprimerMedecin(const std::string& numeroLicence)
* Description : Méthode  Chercher l'index du medecin dans le tableau medecins_ en faisant appel à la fonction trouverIndexMedecin
   et Rend le medecin inactif. Attention : il ne fait pas retirer le medecin du tableau medecins_
* Parametre : onst std::string& numeroLicence
* Retour :   Retourner true si le medein est trouvé et rendu inactif, sinon retourné false
----------------------------------------------------------------------------------------------------------------------------
*/

bool GestionnaireMedecins::supprimerMedecin(const std::string& numeroLicence) {
	bool medecinEstSupprime= false;
	
	if (trouverIndexMedecin(numeroLicence) ==MEDECIN_INEXSISTANT)
	{
		return medecinEstSupprime;
	}
	else {
		medecins_[trouverIndexMedecin(numeroLicence)]->setEstActif(false);
		
		medecinEstSupprime = true;
	}

	return medecinEstSupprime;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  GestionnaireMedecins::afficher()
* Description : Afficher tous les medecins contenus dans le tableau medecins_ en utilisant le stream
* Parametre : ostream& stream
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/


void GestionnaireMedecins::afficher(std::ostream& stream) const {
	for (size_t i = 0; i < nbMedecins_; i++)
	{
		medecins_[i]->afficher(stream);
		stream << '\n';
	}
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  GestionnaireMedecins::getNbMedecins()
* Description : getter
* Parametre : rien
* Retour :   retourner nbMedecins_
----------------------------------------------------------------------------------------------------------------------------
*/

size_t GestionnaireMedecins::getNbMedecins() {
	return nbMedecins_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :   GestionnaireMedecins::getCapaciteMedecins()
* Description : getter
* Parametre : rien
* Retour :   retourner capaciteMedecins_
----------------------------------------------------------------------------------------------------------------------------
*/


size_t GestionnaireMedecins::getCapaciteMedecins() {
	return capaciteMedecins_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :   GestionnaireMedecins::getCapaciteMedecins()
* Description : Méthode qui lit les attributs d'un medecin
* Parametre : const std::string& ligne  / param ligne  Le string qui contient les attributs
* Retour :   retourner true si l'opération a réussi, sinon false
----------------------------------------------------------------------------------------------------------------------------
*/

bool GestionnaireMedecins::lireLigneMedecin(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomMedecin;
	std::string numeroLicence;
	int indexSpecialite;

	

	stream >> std::quoted(nomMedecin);
	stream >> std::quoted(numeroLicence);
	stream >> (indexSpecialite);


	if (nomMedecin == "" || numeroLicence == "" || indexSpecialite<0||indexSpecialite>7)
	{
		return false;
	}
	ajouterMedecin(std::make_unique<Medecin>(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite))); 
	return true;
	

}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :   GestionnaireMedecins::trouverIndexMedecin()
* Description : Méthode trouve l'index d'un medecin et qui le retourne et ce, grace au numero de licence
* Parametre : const std::string& numeroLicenc
* Retour :   Si le medecin n'existe pas, retourner -1 (MEDECIN_INEXSISTANT)
----------------------------------------------------------------------------------------------------------------------------
*/

int  GestionnaireMedecins::trouverIndexMedecin(const std::string& numeroLicence) {

	for (int i = 0; i < nbMedecins_; i++)
	{
		
		if (medecins_[i]->getNumeroLicence()==numeroLicence)
		{
			return i;
		} 
		
	}
	return MEDECIN_INEXSISTANT;
}