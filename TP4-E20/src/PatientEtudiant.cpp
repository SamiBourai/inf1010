//! Class PatientEtudiant
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "PatientEtudiant.h"
#include <iostream>
#include <string>

//! Constructeur par paramétre  de la classe PatientEtudiant
//! \param nom                    Le nom du patient
//! \param dateDeNaissance		  La date de naissance du patient
//! \param numeroAssuranceMaladie Le umero d'assurance maladie du patient
//! \param matricule		      Le matricule de l'étudiant
//! \param etablissement          L'établissement d'étude de l'étudiant
//! \ param dateAdhesion			la date d'adhesion du patientEtudiant
PatientEtudiant::PatientEtudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie, const tm& dateAdhesion, const std::string& matricule, const std::string& etablissement)
	:Patient(nom, dateDeNaissance, numeroAssuranceMaladie,dateAdhesion)
	, Etudiant(nom, dateDeNaissance, matricule, etablissement)
{
}

//! Méthode qui affiche les informations d'un patient étudiant
//! \param stream Le stream dans lequel afficher.
void PatientEtudiant::afficher(std::ostream& stream) const
{
	Patient::afficher(stream);
	stream << " | ";
	Etudiant::afficher(stream);
	stream << " | Taux de rabais: " << tauxRabais_;
}

//! Méthode qui retourne le taux de rabais appliqué pour un étudiant
//! \return tauxRabais_ le taux de rabais
const double PatientEtudiant::getTauxRabais() const
{
	return tauxRabais_;
}

//! Méthode qui met à jours le taux de rabais appliqué pour un étudiant
//! \Param tauxRabais le taux de rabais
void PatientEtudiant::setTauxRabais(double tauxRabais)
{
	tauxRabais_ = tauxRabais;
}
