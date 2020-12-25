/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe ConsultationPhysique.h.
-----------------------------------------------------------------------------------------------------------------------------
*/

#include "..\include\ConsultationPhysique.h"
#include"PatientEtudiant.h"



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : ConsultationEnligne::ConsultationPhysique()
* Description : Constructeur par paramètre pour intialiser les attributs de la classe.
* Parametre : un medecin ,un patient et la date de la consultation
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
ConsultationPhysique::ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date):
Consultation(medecin,patient,date), prescription_(""){}



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : ConsultationPhysique::calculerPrix()
* Description :  methode qui retourne le nombre  le prix d'une consultaion en physique
* Parametre : rien
* Retour :    prix
----------------------------------------------------------------------------------------------------------------------------
*/
const double ConsultationPhysique::calculerPrix() const

{
	
	double prix = medecin_->getPrixConsultation();

	PatientEtudiant* izi = dynamic_cast<PatientEtudiant*>(patient_);

	if (izi != nullptr) {
		double rabais = prix * izi->TAUX_RABAIS;
		prix -= rabais;

	}
	//prix -= getRabaisConsultationEnligne();

	return prix;
	
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : ConsultationEnligne::getPrescription()
* Description :  methode qui retourne la prescription
* Parametre : rien
* Retour :    prescription_
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& ConsultationPhysique::getPrescription() const
{
	return prescription_;
	
}
