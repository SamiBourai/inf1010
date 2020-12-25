//! Class ConsultationEnligne
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "ConsultationEnligne.h"
#include "PatientEtudiant.h"

//! Constructeur par paramètres de la classe ConsultationEnligne
//! \param medecin Le medecin responsable de la consultation
//! \param patient Le patient qui demande une consultation
//! \param date    La date de la consultation
ConsultationEnligne::ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date)
	:Consultation(medecin, patient, date)
	, diagnostique_("")
	, rabaisConsultationEnLigne_(TAUX_RABAIS_CONSULTATION_ENLIGNE)
{
}

//! Méthode  qui calcule le prix de la consultation
//! \return prix de la consultation
const double ConsultationEnligne::calculerPrix() const
{
	double prixConsultation = medecin_->getPrixConsultation();
	PatientEtudiant* patientEtudiant = dynamic_cast<PatientEtudiant*>(patient_);

	if (patientEtudiant) {
		prixConsultation *= (1 - patientEtudiant->getTauxRabais());
	}

	return prixConsultation * (1 - rabaisConsultationEnLigne_);
}

//! Méthode qui retourne le diagnostique 
//! \return diagnostique_  le diagnostique
const std::string& ConsultationEnligne::getDiagnostique() const
{
	return diagnostique_;
}

//! Méthode qui retourne le rabais de la consultation 
//! \return rabaisConsultationEnLigne_  le rabaix appliqué à cette consulation
double ConsultationEnligne::getRabaisConsultationEnLigne() const
{
	return rabaisConsultationEnLigne_;
}

// !Méthode qui modifie le rabais de la consultation
//! \Param tauxRabais le taux du rabais
void ConsultationEnligne::setRabaisConsultationEnLigne(double tauxRabais)
{
	rabaisConsultationEnLigne_ = tauxRabais;
}

// !Méthode qui met à jours le diagnostique
//! \Param diagnostique le diagnostique
void ConsultationEnligne::setDiagnostique(const std::string diagnostique)
{
	diagnostique_ = diagnostique;
}
