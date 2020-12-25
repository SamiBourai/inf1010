
/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe ConsultationEnligen.h.
-----------------------------------------------------------------------------------------------------------------------------
*/
#include"ConsultationEnligne.h"
#include "PatientEtudiant.h"
#include <iostream>
#include <string>

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : ConsultationEnligne::ConsultationEnligne()
* Description : Constructeur par paramètre pour intialiser les attributs de la classe.
* Parametre : un medecin ,un patient et la date de la consultation
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
ConsultationEnligne::ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date):
Consultation(medecin,patient,date),diagnostique__(""),rabaisConsultationEnLigne__(TAUX_RABAIS_CONSULTATION_ENLIGNE){}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : ConsultationEnligne::calculerPrix()
* Description :  methode qui retourne le nombre  le prix d'une consultaion en ligne
* Parametre : rien
* Retour :    prix
----------------------------------------------------------------------------------------------------------------------------
*/
const double ConsultationEnligne::calculerPrix() const
{
	double prix = medecin_->getPrixConsultation();

	PatientEtudiant* izi = dynamic_cast<PatientEtudiant*>(patient_);
	if (izi!=nullptr) {
		double rabais= prix*izi->getTauxRabais();
		prix -= rabais;
		
	}
	double rabaisEnligne=(1-getRabaisConsultationEnligne());

	return prix*=rabaisEnligne;
}





/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : ConsultationEnligne::getDiagnostique()
* Description :  methode qui retourne le diagnostique
* Parametre : rien
* Retour :    diagnostique_
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& ConsultationEnligne::getDiagnostique() const
{
	return diagnostique__;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : ConsultationEnligne::getRabaisConsultationEnligne()
* Description :  methode qui retourne le rabais de consultaion en ligne
* Parametre : rien
* Retour :  rabaisConsutlationEnligne_
----------------------------------------------------------------------------------------------------------------------------
*/
double ConsultationEnligne::getRabaisConsultationEnligne() const
{
	return rabaisConsultationEnLigne__;
}
