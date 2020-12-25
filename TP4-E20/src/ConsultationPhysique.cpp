//! Class ConsultationPhysique
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "ConsultationPhysique.h"
#include "PatientEtudiant.h"

//! Constructeur par paramètres de la classe ConsultationEnligne
//! \param medecin Le medecin responsable de la consultation
//! \param patient Le patient qui demande une consultation
//! \param date    La date de la consultation
ConsultationPhysique::ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date)
	:Consultation(medecin, patient, date)
	, prescription_("")
{
}

//! Méthode  qui calcule le prix de la consultation
//! \return le prix de la consultation
const double ConsultationPhysique::calculerPrix() const
{
	double prixConsultation = medecin_->getPrixConsultation();
	PatientEtudiant* patientEtudiant = dynamic_cast<PatientEtudiant*>(patient_);

	if (patientEtudiant) {
		prixConsultation *= (1 - patientEtudiant->getTauxRabais());
	}

	return prixConsultation;
}

//! Méthode qui retourne la prescription 
//! \return prescription_ 
const std::string& ConsultationPhysique::getPrescription() const
{
	return prescription_;
}

//! Méthode qui met à jours la prescription 
//! \Param prescription la prescription
void ConsultationPhysique::setPrescription(const std::string prescription)
{
	prescription_ = prescription;
}
