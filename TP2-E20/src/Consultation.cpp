/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 23-may-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Consultation.h
-----------------------------------------------------------------------------------------------------------------------------
*/

#include "Consultation.h"
#include <iostream>
#include <string>

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Consultation::Consultation().
* Description : conctructeur par paramètre de la classe Consultation avec une liste d'initialisation
		ajouter le patient à la liste des patients assoicés au medecin s'il n'y existe pas.
* Parametre : (Medecin& medecin, Patient& patient, const std::string& date
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/

Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date):medecin_(&medecin), patient_(&patient), date_(date)
{
	if (verifierSiPatientAjouterAuVecteur(medecin,patient)== false) *medecin_ += *patient_;
	
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : operator <<
* Description :  Méthode qui affiche les informations d'une consultation. Si l'affichage n'est pas respecté, le test de l'affichage de consultation ne passera pas.
* Parametre : display et const Consultation& consultation1
* Retour :   display.
----------------------------------------------------------------------------------------------------------------------------
*/
std::ostream& operator << (std::ostream& display, const Consultation& consultation1) {

	display << "Consultation  : \n"; 
	display << "Medecin : " << consultation1.getMedecin()->getNom() << "\n";
	display << *consultation1.getPatient()<<"\n"; 
	display << "Date de consultation : " << consultation1.date_ << "\n";
	return display;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin* Consultation::getMedecin() const
* Description :  getter
* Parametre : rien.
* Retour : return Medecin*
----------------------------------------------------------------------------------------------------------------------------
*/
Medecin* Consultation::getMedecin() const
{
	return medecin_;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient* Consultation::getPatient() const
* Description :  getter
* Parametre : rien.
* Retour : return Patient*
----------------------------------------------------------------------------------------------------------------------------
*/
Patient* Consultation::getPatient() const
{
	return patient_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : const std::string& Consultation::getDate() const
* Description :  getter
* Parametre : rien.
* Retour : return const std::string
----------------------------------------------------------------------------------------------------------------------------
*/

const std::string& Consultation::getDate() const
{
	return date_;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : bool Consultation::verifierSiPatientAjouterAuVecteur()
* Description :  cette fonction verifie si le patient existe deja dans le vecteur patient_ / elle en lien directe avec le constructeur de Consultation
* Parametre : Medecin& medecin, Patient& patient
* Retour : bool,  si le patient existe dans vecteur alors retourner vrai, sinon faux 
----------------------------------------------------------------------------------------------------------------------------
*/
bool Consultation::verifierSiPatientAjouterAuVecteur(Medecin& medecin, Patient& patient) {
	bool existant = false;
	if (medecin.chercherPatient(patient.getNumeroAssuranceMaladie()) ==nullptr)
	{
		return existant;
	}
	return !existant;
	
}