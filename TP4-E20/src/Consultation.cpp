//! Class Consultation
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "Consultation.h"
#include <iostream>
#include <string>

//! Constructeur par paramètres de la classe abstraite Consultation
//! \param medecin Le medecin responsable de la consultation
//! \param patient Le patient qui demande une consultation
//! \param date    La date de la consultation
Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date) :
	medecin_(&medecin), patient_(&patient), date_(date), prix_(PRIX_DE_BASE)
{
}

//! Méthode qui affiche les informations d'une consultation
//! \param os Le stream dans lequel afficher
void Consultation::afficher(std::ostream& os) const
{
	std::string typeConsultation = typeid(*this).name();
	std::string typeMedecin = typeid(*medecin_).name();
	std::string typePatient = typeid(*patient_).name();
	os << "Consultation: "
		<< "\n\tType: " << typeConsultation.substr(6, typeConsultation.length() - 6 + 1)
		<< "\n\t\t" << typeMedecin.substr(6, typeMedecin.length() - 6 + 1) << ": " << medecin_->getId()
		<< "\n\t\t" << typePatient.substr(6, typePatient.length() - 6 + 1) << ": " << patient_->getNumeroAssuranceMaladie()
		<< "\n\t\t" << "Date de consultation: " << date_;
}

//! Méthode qui retourne le médecin de la consultation
//! \return medecin_ le pointeur vers le médecin de la consultation
Medecin* Consultation::getMedecin() const
{
	return medecin_;
}


//! Méthode qui retourne le patient de la consultation
//! \return patient_ le pointeur vers le patient de la consultation
Patient* Consultation::getPatient() const
{
	return patient_;
}

//! Méthode qui retourne la date de la consultation
//! \return date_ la date de la consultation
const std::string& Consultation::getDate() const
{

	return date_;
}
