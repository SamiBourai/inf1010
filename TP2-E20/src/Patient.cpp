/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 23-may-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Patient.h.
-----------------------------------------------------------------------------------------------------------------------------
*/

#include "Patient.h"
#include <iostream>
#include <string>
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::Patient().
* Description :  c'est le conctructeur par paramètre de la classe Patient en utilisant la liste d'initialisation
* Parametre : Nom du patient, Date de naissance du patient et Le numero d'assurance maladie du patient
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/

Patient::Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie)
	: nom_(nom)
	, numeroAssuranceMaladie_(numeroAssuranceMaladie)
	, dateDeNaissance_(dateDeNaissance)
{
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::afficher(); La methode afficher doit être remplacée par l’opérateur << 
* Description :  Méthode qui affiche les informations d'un patient
* Parametre : param display 
* Retour :   display
----------------------------------------------------------------------------------------------------------------------------
*/


std::ostream& operator << (std::ostream& display, const Patient& patient1) {

	return display << "Patient: " << patient1.nom_ << " | Date de naissance: " << patient1.dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << patient1.numeroAssuranceMaladie_;
	 
 }

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Opérateur == 
* Description : qui compare un string avec le numero d'assurance maladie du patient avec patient comme opérande de gauche
* Parametre : assuranceMaladie et un patient
* Retour :   un bool, vrai si oui c'est egale, sinon faux
----------------------------------------------------------------------------------------------------------------------------
*/

bool operator==(const std::string& assuranceMaladie, const  Patient& patient1) {

	if (assuranceMaladie==patient1.getNumeroAssuranceMaladie())
	{
		return true;
	}
	else {
		return false;
	}
 }

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Opérateur ==
* Description : qui compare le numero d'assurance maladie du patient avec le numero d'assurance comme opérande de gauche.
* Parametre : assuranceMaladie 
* Retour :   un bool, vrai si oui c'est egale, sinon faux
----------------------------------------------------------------------------------------------------------------------------
*/

bool Patient::operator == (const std::string& assuranceMaladie) {

	if (numeroAssuranceMaladie_==assuranceMaladie)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::getNom();
* Description :  getter qui retourne le nom / comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour :   nom_;
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& Patient::getNom() const
{

	return nom_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::getNumeroAssuranceMaladie().
* Description :  getter qui retourne  le numéro d'assurance maladie / comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour :  retourner le numéro d'assurance maladie
----------------------------------------------------------------------------------------------------------------------------
*/

const std::string& Patient::getNumeroAssuranceMaladie() const
{

	return numeroAssuranceMaladie_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::getDateDeNaissance()
* Description :  getter qui retourne la date de naissance / comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour : retourner la date de naissance
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& Patient::getDateDeNaissance() const
{

	return dateDeNaissance_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::setNom()
* Description :  fonction qui set l'attribut nom_
* Parametre : nom.
* Retour : rien.
----------------------------------------------------------------------------------------------------------------------------
*/
void Patient::setNom(const std::string& nom)
{
	nom_ = nom;
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::setNumeroAssuranceMaladie()
* Description :  fonction qui set le numéro d'assurance maladie
* Parametre : numeroAssuranceMaladie
* Retour : rien.
----------------------------------------------------------------------------------------------------------------------------
*/
void Patient::setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie)
{
	numeroAssuranceMaladie_ = numeroAssuranceMaladie;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::setDateDeNaissance()
* Description :  fonction qui set la date de naissance
* Parametre :dateDeNaissance
* Retour : rien.
----------------------------------------------------------------------------------------------------------------------------
*/
void Patient::setDateDeNaissance(const std::string& dateDeNaissance)
{
	dateDeNaissance_ = dateDeNaissance;
}

