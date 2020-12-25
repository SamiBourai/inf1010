//! Class Etudiant
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "Etudiant.h"
#include <iostream>
#include <string>

//! Constructeur par paramétres de la classe de base Etudiant
//! \param nom				Le nom de l'étudiant
//! \param dateDeNaissance  La date de naissance de l'étudiant
//! \param matricule		Le matricule de l'étudiant
//! \param etablissement    L'établissement d'étude de l'étudiant
Etudiant::Etudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablissement)
	:etablissement_(etablissement)
	, nom_(nom)
	, matricule_(matricule)
	, dateDeNaissance_(dateDeNaissance)
{
}

//! Méthode qui affiche les informations de l'étudiant
//! \param os Le stream dans lequel afficher
void Etudiant::afficher(std::ostream& stream) const
{
	stream << "Matricule: " << matricule_ << "\n\tEtablissement: " << etablissement_;
}

//! Méthode qui retourne le nom de l'étudiant
//! \return nom_ le nom du l'étudiant  
const std::string& Etudiant::getNom() const
{

	return nom_;
}


//! Méthode qui retourne le matricule de l'étudiant
//! \return matricule_ le matricule
const std::string& Etudiant::getMatricule() const
{

	return matricule_;
}

//! Méthode qui retourne  l'établissement de l'étudiant
//! \return  etablissement_ l'établissement de l'étudiant
const std::string& Etudiant::getEtablissement() const
{
	return etablissement_;
}

//! Méthode qui retourne la date de naissance de l'étudiant
//! \return dateDeNaissance_ la date de naissance
const std::string& Etudiant::getDateDeNaissance() const
{
	return dateDeNaissance_;
}

//! Méthode qui met a jours le nom  de l'étudiant
//! \pararm  nom  Le nom de l'étudiant
void Etudiant::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui met a jours le matricule de l'étudiant
//! \pararm  matircule le matricule de l'étudiant
void Etudiant::setMatricule(const std::string& matricule)
{
	matricule_ = matricule;
}

//! Méthode qui met a jours la date de naissance de l'étudiant
//! \pararm  dateDeNaissance la date de naissance de l'étudiant
void Etudiant::setDateDeNaissance(const std::string& dateDeNaissance)
{
	dateDeNaissance_ = dateDeNaissance;
}

//! Méthode qui met a jours l'établissement de l'étudiant
//! \pararm  etablissement l'établissement de l'étudiant
void Etudiant::setEtablissement(const std::string& etablissement)
{
	etablissement_ = etablissement;
}