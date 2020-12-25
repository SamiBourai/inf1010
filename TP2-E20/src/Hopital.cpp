/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 23-may-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Hopital.h
-----------------------------------------------------------------------------------------------------------------------------
*/

#include "Hopital.h"
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Hopital::Hopital().
* Description : Constructeur par paramètre  de la classe Hopital
* Parametre :  Nom de l'hopital et Adresse de l'hopital
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/

Hopital::Hopital(const std::string& nom, const std::string& adresse):nom_(nom), adresse_(adresse)
{
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : chargerBaseDeDonnees()
* Description : Permet de charger les médecins et les patients depuis les fichiers passés en paramètres.
* Parametre :  nomFichierMedecins,  nomFichierPatients
* Retour :  Retourne true si les fichiers sont bien chargés , false si non.
----------------------------------------------------------------------------------------------------------------------------
*/

bool Hopital::chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients) {
	return chargerPatientMedecin(nomFichierMedecins, nomFichierPatients);
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : l'operateur +=
* Description :   permet d'ajouter une consultation à la liste consutltations_
* Parametre : Consultation& consultation1
* Retour : Il ajoute la consultation et retourne true si le medecin est actif, existe dans le gestionnaire de medecins 
		   et le patient existe dans le gestionnaire de patients.
		   Si non il retourne false.
----------------------------------------------------------------------------------------------------------------------------
*/

bool Hopital::operator+=( Consultation& consultation1) {
	if (verifierCondition(consultation1) == 1) {
		consultations_.push_back(std::make_shared<Consultation>(consultation1));
		return true;
	}
	else return false;
	
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : l'operateur +=
* Description : qui ajoute un médecin au gestionnaire de médecins.
* Parametre :  prend en parametre une reference vers le medecin a ajouter
* Retour :    false si l'operation a echouee sinon un vrai si elle a reussi.
----------------------------------------------------------------------------------------------------------------------------
*/
bool Hopital::operator+=( Medecin& medecin1) {
	return gestionnaireMedecins_ += medecin1;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : l'operateur +=
* Description :  ajouté un pateint au gestionnaire de patient.
* Parametre : Il prend en parametre une reference vers le patient à ajouter
* Retour :  bool si l'ajout a reussi ou non
----------------------------------------------------------------------------------------------------------------------------
*/

bool Hopital::operator+=(Patient& patient1) {
	return gestionnairePatients_+=patient1;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :getNom()
* Description :  getter
* Parametre : -
* Retour :  Méthode qui retourne le nom de l'hopital
----------------------------------------------------------------------------------------------------------------------------
*/

const std::string& Hopital::getNom() const
{
	return nom_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction ::getAdresse()
* Description :  getter
* Parametre : -
* Retour :  Méthode qui retourne l'adresse de l'hopital
----------------------------------------------------------------------------------------------------------------------------
*/ 
const std::string& Hopital::getAdresse() const
{
	return adresse_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction ::Hopital::getGesionnaireMedecins()
* Description :  getter
* Parametre : -
* Retour :  return gestionnaire des medecins
----------------------------------------------------------------------------------------------------------------------------
*/

GestionnaireMedecins& Hopital::getGesionnaireMedecins()
{
	return gestionnaireMedecins_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Hopital::getGestionnairePatients()
* Description :  getter
* Parametre : -
* Retour : return gestionnaire des patients
----------------------------------------------------------------------------------------------------------------------------
*/
GestionnairePatients& Hopital::getGestionnairePatients()
{
	return gestionnairePatients_;
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : getConsultations()
* Description :  getter
* Parametre : -
* Retour :retourne une reference constante vers le vecteur consultation.
----------------------------------------------------------------------------------------------------------------------------
*/
const std::vector<std::shared_ptr<Consultation>>& Hopital::getConsultations() const {
	return consultations_;
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : setNom()
* Description :  Méthode qui permet de mettre à jour le nom de l'hopital
* Parametre :  Le nom de l'hopital
* Retour : -
----------------------------------------------------------------------------------------------------------------------------
*/
void Hopital::setNom(const std::string& nom)
{
	nom_ = nom;
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : setAdresse()
* Description : Méthode qui permet de mettre à jour l'adresse de l'hopital
* Parametre :  l'adresse de l'hopital
* Retour : -
----------------------------------------------------------------------------------------------------------------------------
*/

void Hopital::setAdresse(const std::string& adresse)
{
	adresse_ = adresse;
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :chagerPatientMedecin()
* Description :  Méthode qui permet de savoir si le fichier medecin et patient ont ete bel et bien charge
* Parametre : les nom des fichier
* Retour : retourne vrai si les deux sont charges sinon faux
----------------------------------------------------------------------------------------------------------------------------
*/
bool Hopital::chargerPatientMedecin(const std::string& nomFichier1, const std::string& nomFichier2) {
	bool lu = false;
	if (gestionnaireMedecins_.chargerDepuisFichier(nomFichier1) &&
		gestionnairePatients_.chargerDepuisFichier(nomFichier2)) {
		return !lu;
	}
	return lu;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : verifierCondition()
* Description :  Méthode qui permet de verifier les condition de  l'operateur +=
* Parametre : Consultation& consultation1
* Retour : retourne vrai si les 3 conditons sont vrai sinon faux 
----------------------------------------------------------------------------------------------------------------------------
*/
bool Hopital::verifierCondition( Consultation& consultation1) {
	bool retour = false;

	if (consultation1.getMedecin()->getEstActif() 
		&& gestionnaireMedecins_.chercherMedecin(consultation1.getMedecin()->getNumeroLicence()) 
		&& gestionnairePatients_.chercherPatient(consultation1.getPatient()->getNumeroAssuranceMaladie())) 
		
		return !retour; 
	else
	{
		return retour;
	}
}