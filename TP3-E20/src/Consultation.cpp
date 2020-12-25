
/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Consultation.h.
-----------------------------------------------------------------------------------------------------------------------------
*/

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
//Chercher le nom de la classe. Elle peut être ConsultationEnligne ou ConsultationPhysique.
								  //Utiliser typeid().name()

	std::string typeConsultation = typeid(*this).name();
	
	
	if (typeConsultation == "class ConsultationEnligne")typeConsultation = " ConsultationEnligne";
		
	else typeConsultation = " ConsultationPhysique";
	

	std::string typeMedecin = typeid(*medecin_).name();
	
	if (typeMedecin == "class MedecinResident")typeMedecin = " MedecinResident";
		
	else typeMedecin = " Medecin";

	std::string typePatient = typeid(*patient_).name();

	if (typePatient == "class PatientEtudiant")typePatient = " PatientEtudiant";

	else typePatient = " Patient";


	
	

	os << "Consultation: "
		<< "\n\tType: " <<	typeConsultation					//Extraire le nom de la classe du string typeConsultation
		<< "\n\t\t" << typeMedecin  << " : " <<(*medecin_).getId()			//Extraire le nom de la classe du string typeMedecin << ": " << // afficher Id du medecin
		<< "\n\t\t" << typePatient <<" : " <<(*patient_).getNumeroAssuranceMaladie()	//Extraire le nom de la classe du string typePatient  << ": " << // afficher le numero d'assurance maladie du patient
		<< "\n\t\t" << "Date de consultation : " << getDate();							//Afficher date_
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

