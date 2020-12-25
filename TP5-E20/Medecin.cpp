//! Class Medecin
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include <iostream>
#include "Medecin.h"

constexpr int PATIENT_INEXSISTANT = -1;

//! Constructeur par défaut  de la classe Medecin
Medecin::Medecin():specialite_(Medecin::Specialite::Autre), nombreConsultations_(0)
{
}

//! Constructeur par paramètre  de la classe Medecin
//! \param nom              Le nom du medecin
//! \param numeroLicence    Le numero de licence du medecin
//! \param specialite       La specialite du medecin
Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite, const tm& dateAdhesion)
	: Personnel(nom, numeroLicence, dateAdhesion)
	, specialite_(specialite)
	, patientsAssocies_(std::vector<Patient*>())
	, nombreConsultations_(0)
{
}

//! Operateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return        Un bool qui indique si l'opération a bien fonctionnée
bool Medecin::operator+=(Patient* patient)
{
	if (patient && !chercherPatient(patient->getNumeroAssuranceMaladie())) {
		patientsAssocies_.push_back(patient);

		return true;
	}

	return false;
}

//! Operateur qui supprime un patient de la liste des patients
//! \param numeroAssuranceMaladiePatient Le patient à ajouter
//! \return      Un bool qui indique si l'opération a bien fonctionnée
bool Medecin::operator-=(const std::string& numeroAssuranceMaladiePatient)
{
	int indexPatient = trouverIndexPatient(numeroAssuranceMaladiePatient);
	if (indexPatient == PATIENT_INEXSISTANT)
	{
		return false;
	}

	patientsAssocies_.erase(patientsAssocies_.begin() + indexPatient);

	return true;
}

//! Méhode qui cherche un patient par numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* Medecin::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (auto & patientsAssocie : patientsAssocies_)
	{
		if (*patientsAssocie == numeroAssuranceMaladie)
		{
			return patientsAssocie;
		}
	}

	return nullptr;
}

void Medecin::incrementNombreConsultations()
{
	nombreConsultations_++;
}

//! Méthode qui retourne le salaire d'un médecin
//! \return le salaire
double Medecin::getSalaireAnnuel() const
{

	return SALAIRE_DE_BASE_MEDECIN + static_cast<double>(nombreConsultations_) * getPrixConsultation();
}

//! Méthode qui retourne le prix de la consultation selon la spécialité du médecin
//! \return le prix de la spécialité
double Medecin::getPrixConsultation() const
{
	double prix = 0.0;
	switch (specialite_) {
	case Specialite::Gynecologue:
	case Specialite::Ophtalmologue:
		prix = 100;
		break;
	case Specialite::Pediatre:
		prix = 80;
		break;
	case Specialite::Cardiologue:
	case Specialite::Dermatologue:
		prix = 120;
		break;
	case Specialite::Generaliste:
	case Specialite::Autre:
		prix = 60;
		break;
	default:
		throw "La spécialite du médecin n'est pas définie";
	}

	return prix;
}

//! Méthode qui retourne la specialite du medecin
//! \return la specialite des medecins
Medecin::Specialite Medecin::getSpecialite() const
{

	return specialite_;
}

//! Méthode qui retourne le nombre de patients associés
//! \return le nombre de patients associés
size_t Medecin::getNombrePatientsAssocies() const
{

	return patientsAssocies_.size();
}

//! Méthode qui retourne le nombre de consultations effectuées par le medecin
//! \return nombreConsultations
size_t Medecin::getNombreConsultations() const
{
	return nombreConsultations_;
}


//! Méthode qui retourne la liste des patients associes au medecin
//! \return la liste des patients
const std::vector<Patient*>& Medecin::getPatientsAssocies() const
{
	return patientsAssocies_;
}

//! Méthode qui met a jours la specialité du medecin
//! \pararm  specialite  specialité du medecin
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}

//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroAssuranceMaladie Le numero de licence du medecin
//! \return entier qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
int Medecin::trouverIndexPatient(const std::string& numeroAssuranceMaladie)
{
	for (std::size_t i = 0; i < patientsAssocies_.size(); i++)
	{
		if (*patientsAssocies_[i] == numeroAssuranceMaladie)
		{
			return static_cast<int>(i);
		}
	}
	return PATIENT_INEXSISTANT;
}
