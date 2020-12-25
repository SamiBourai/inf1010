/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Etudiant.h.
-----------------------------------------------------------------------------------------------------------------------------
*/
#include "Etudiant.h"
#include <iostream>
#include <string>


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Etudiant::Etudiant().
* Description :  c'est le conctructeur par paramètre de la classe Etudiant en utilisant la liste d'initialisation
* Parametre : l'etablissement, Nom du patient, Date de naissance du patient, son matricule en tant qu'etudiant
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/
Etudiant::Etudiant(const std::string& etablissement, const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule)
	:nom_(nom),matricule_(matricule),dateDeNaissance_(dateDeNaissance) ,etablissement_(etablissement){}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Etudiant::afficher();
* Description :  Méthode qui affiche les informations d'un Etudiant (matricule,etablissement)
* Parametre : param stream
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/

void Etudiant::afficher(std::ostream& stream) const
{
	stream << "Matricule: " << matricule_ << "\n\tEtablissement: " << etablissement_;
}


//! Méthode qui retourne le nom de l'etudiant
//! \return nom_ le nom de l'etudiant
const std::string& Etudiant::getNom() const { return nom_; }


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Etudiant::getMatricule();
* Description :  methode qui retourne le matricule de l'etudiant
* Parametre : rien
* Retour :   matricule_
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& Etudiant::getMatricule() const { return matricule_; }


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Etudiant:: getEtablissement();
* Description :  methode qui retourne l'etablissement de l'etudiant
* Parametre : rien
* Retour :   etablissement_
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& Etudiant::getEtablissement() const { return etablissement_; }


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Etudiant::  getDateDeNaissance();
* Description :  methode qui retourne la date de naissance de l'etudiant
* Parametre : rien
* Retour :   dateDeNaissance_
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& Etudiant::getDateDeNaissance() const { return dateDeNaissance_; }


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Etudiant:: setNom();
* Description :  methode qui set le nom de l'etudiant
* Parametre : nom
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/

void Etudiant::setNom(const std::string& nom) { nom_ = nom; }


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Etudiant:: setMatricule();
* Description :  methode qui set le matricule de l'etudiant // j'ai garder assurance maladie meme si c'est matricule
* Parametre : matricule 
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Etudiant::setMatricule(const std::string& numeroAssuranceMaladie) { matricule_ = numeroAssuranceMaladie; } 


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Etudiant:: setDateDeNaissancex();
* Description :  methode qui set la date de naissance de l'etudiant 
* Parametre : dateDeNaissance
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Etudiant::setDateDeNaissance(const std::string& dateDeNaissance) { dateDeNaissance_ = dateDeNaissance; }


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Etudiant:: setEtablissement();
* Description :  methode qui set l'etablissement l'etudiant
* Parametre : etablissement
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Etudiant::setEtablissement(const std::string& etablissement) { etablissement_ = etablissement; }
