//! Class MedecinResident
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "MedecinResident.h"
#include <iostream>
#include <string>

//! Constructeur par paramétres de la classe de MedecinResidant
//! \param nom				          Le nom du medecin résidant
//! \param dateDeNaissance            La date de naissance du medecin résidant
//! \param matricule		          Le matricule du medecin résidant
//! \param etablissement              L'établissement d'étude du medecin résidant
//! \param NumeroLicenceProvisoire    Le numero de licence provisoir du medecin résidant
//! \param specialite				  La specialite du medecin résidant
MedecinResident::MedecinResident(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule,
					            const std::string& etablissement, const std::string NumeroLicenceProvisoire, Specialite specialite, const tm& dateAdhesion)
								:Etudiant(nom, dateDeNaissance, matricule, etablissement)
								,Medecin(nom, NumeroLicenceProvisoire, specialite, dateAdhesion)
{
}

//! Méthode qui affiche les informations d'un medecin résidant
//! \param stream Le stream dans lequel afficher.
void MedecinResident::afficher(std::ostream& stream) const
{
	Medecin::afficher(stream);
	stream << "\n\t";
	Etudiant::afficher(stream);
}

//! Méthode qui retourne le salaire d'un médecin résidant
//! \return le salaire du médecin résidant
double MedecinResident::getSalaireAnnuel() const
{
	return SALAIRE_DE_BASE_MEDECIN_RESIDENT + static_cast<double>(nombreConsultations_) * getPrixConsultation();
}

