

/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 11-may-2020
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
* Parametre : ce dernier prend comme parametre tous les attributs de la classe Patient.h.
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/

// TODO : compléter Constructeur par paramètre  de la classe Patient en utilisant la liste d'initialisation

Patient::Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie): 
	nom_(nom), numeroAssuranceMaladie_(numeroAssuranceMaladie), dateDeNaissance_(dateDeNaissance){}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::afficher();
* Description :  Méthode qui affiche les informations d'un patient
* Parametre : param stream Le stream dans lequel afficher.
* Retour :   ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/

void Patient::afficher(std::ostream& stream) const
{
	// Ne modifiez pas cette fonction
	stream << "Patient: " << nom_ << " | Date de naissance: " << dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << numeroAssuranceMaladie_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::getNom();
* Description :  getter qui retourne le nom / comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour :   nom_;
----------------------------------------------------------------------------------------------------------------------------
*/

const std::string& Patient::getNom() const {        
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

const std::string& Patient::getNumeroAssuranceMaladie()const {		

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

const std::string& Patient::getDateDeNaissance()const {    // comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST

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

void Patient::setNom(const std::string& nom) {

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
void Patient::setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie) {

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

void Patient::setDateDeNaissance(const std::string& dateDeNaissance) {

	dateDeNaissance_ = dateDeNaissance;
}
