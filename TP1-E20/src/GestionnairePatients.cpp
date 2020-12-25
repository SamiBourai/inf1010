
/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 11-may-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe GestionnairePatients.h .
-----------------------------------------------------------------------------------------------------------------------------
*/




#include"GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
 


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePatients::GestionnairePatients()
* Description :  c'est le conctructeur par paramètre  de la classe GestionnairePatients en utilisant une liste d'initialisation
* Parametre : ce dernier prend comme parametre tous les attributs de la classe GestionnairePatients 
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/
GestionnairePatients::GestionnairePatients():patients_(), nbPatients_(0) {}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :bool GestionnairePatients::ajouterPatient();
* Description :  Méthode qui ajoute un patient au tableau patients_
* Parametre : Patient& patient 
* Retour : Si le tableau est plein, retourner false sinon faites l'ajout et retouner true
----------------------------------------------------------------------------------------------------------------------------
*/

bool GestionnairePatients::ajouterPatient(const Patient& patient){

	if (nbPatients_<NB_PATIENT_MAX)
	{
		patients_[nbPatients_++] = patient;
		//nbPatients_++;

		return true;
	}
	else {
		return false;
	}

}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : std::shared_ptr<Patient> GestionnairePatients::chercherPatient()
* Description :  Chercher un patient dans la liste patients_ par son numéro d'assurance maladie
* Parametre :const std::string& numeroAssuranceMaladie
* Retour : Retourner le pointeur vers le patient si trouvé, sinon retourner nullptr
----------------------------------------------------------------------------------------------------------------------------
*/
std::shared_ptr<Patient> GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie) {
	
	//nbPatients_ = 0;

	
	for (int i = 0; i < nbPatients_; i++)
	{
		if (patients_[i].getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{

			return  std::make_shared<Patient>(patients_[i]);
		}
	}
	return nullptr;
	


}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : bool GestionnairePatients::chargerDepuisFichier()
* Description :  Méthode  qui permet de charger les informations des patients depuis un fichier
* Parametre : param nomFichier   Le nom du fichier à charger
* Retour : Un bool qui indique si le fichier a été chargé avec succès
----------------------------------------------------------------------------------------------------------------------------
*/


bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier)
{
	std::string ligneAuComplet;

	std::ifstream fichier(nomFichier);
	nbPatients_ = 0;
	// TODO : Envoyer chaque ligne à lireLignePatient()

	if (fichier)
	{
		while (getline(fichier, ligneAuComplet))
		{
			
			if (!lireLignePatient(ligneAuComplet))
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
* Fonction : void GestionnairePatients::afficher()
* Description : Afficher tous les patients contenus dans le tableau patients_ en utilisant le stream
* Parametre : stream
* Retour : rien
----------------------------------------------------------------------------------------------------------------------------
*/

void GestionnairePatients::afficher(std::ostream& stream) const
{
	
	for (size_t i = 0; i < nbPatients_; i++)
	{
		patients_[i].afficher(stream);
		stream << '\n';
	}
	//aastream << '\n';
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePatients::getNbPatients()
* Description : getter
* Parametre : rien
* Retour :  nbPatients_
----------------------------------------------------------------------------------------------------------------------------
*/
std::size_t GestionnairePatients::getNbPatients() const { return nbPatients_; }


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePatients::getNbPatients()
* Description : Méthode qui lit les attributs d'un patient
* Parametre : const std::string& ligne  /param ligne  Le string qui contient les attributs
* Retour : bool- true si y a eu succes /false si y a eu echec
----------------------------------------------------------------------------------------------------------------------------
*/

bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;

	// TODO
	
	// Utiliser l'opérateur d'extraction (>>) depuis le stream
	
	stream >> std::quoted(nomPatient);

	stream >> std::quoted(anneeDeNaissance);

	stream>> std::quoted(numeroAssuranceMaladie);

	if (nomPatient==""||numeroAssuranceMaladie==""||anneeDeNaissance=="")
	{
		return false;
	}
	else
	{
		Patient patient; 
		patient.setNom(nomPatient);
		patient.setDateDeNaissance(anneeDeNaissance);
		patient.setNumeroAssuranceMaladie(numeroAssuranceMaladie);
		ajouterPatient(patient);
		return true;

	}
	
	

}