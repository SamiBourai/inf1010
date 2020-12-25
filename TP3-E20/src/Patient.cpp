
/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
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

//! Opérateur qui compare un string avec le numero d'assurance maladie du patient avec patient comme opérande de gauche
//! \param numeroAssuranceMaladie le numero d'assurance  avec le quel on veut comparé le patient
//! \return vrai si les les numeros d'assurance sont identiques, faux sinon
bool Patient::operator==(const std::string& numeroAssuranceMaladie) const
{
	return (numeroAssuranceMaladie_ == numeroAssuranceMaladie);
}

//! Opérateur qui compare le numero d'assurance maladie du patient avec le numero d'assurance comme opérande de gauche.
//! \param numeroAssuranceMaladie le numero d'assurance avec le quel on veut comparé le patient
//! \param patient le patient avec lequel on compare le numero d'assurance
bool operator==(const std::string& numeroAssuranceMaladie, const Patient& patient)
{
	return (numeroAssuranceMaladie == patient.numeroAssuranceMaladie_);
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient::afficher();
* Description :  Méthode qui affiche les informations d'un patient
* Parametre : param stream
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Patient::afficher(std::ostream& stream) const
{
	stream << "Patient: ";
	std::string typePatient;// TODO: Chercher le nom de la classe. Il peut être Patient ou PatientEtudiant. Utiliser typeid().name()

	typePatient = typeid(*this).name();
	
	typePatient.erase(0, 6);
	
	stream << "\n\tType: " << typePatient << "\n"; //Extraire le nom de la classe du string typePatient;
	stream << "\n\tNom: " << nom_ << " | Date de naissance: " << dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << numeroAssuranceMaladie_;
}

//! Méthode qui retourne le nom du patient
//! \return nom_ le nom du patient
const std::string& Patient::getNom() const
{

	return nom_;
}

//! Méthode qui retourne le numéro d'assurance maladie du patient
//! \return numeroAssuranceMaladie_ le numéro d'assurance maladie du patient
const std::string& Patient::getNumeroAssuranceMaladie() const
{

	return numeroAssuranceMaladie_;
}



//! Méthode qui retourne la date de naissance du patient
//! \return dateDeNaissance_la date de naissnace du patient 
const std::string& Patient::getDateDeNaissance() const
{

	return dateDeNaissance_;
}

//! Méthode qui permet de mettre à jour le nom du patient
//! \Param nom Le nom du patient
void Patient::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour le nom du numero d'assurance maladie du patient
//! \Param numeroAssuranceMaladie Le numero d'assurance maladie
void Patient::setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie)
{
	numeroAssuranceMaladie_ = numeroAssuranceMaladie;
}

//! Méthode qui permet de mettre à jour la date de naissance du patient
//! \Param dateDeNaissance La date de naissance du patient
void Patient::setDateDeNaissance(const std::string& dateDeNaissance)
{
	dateDeNaissance_ = dateDeNaissance;
}
