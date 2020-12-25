/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe MedecinResident.h.
-----------------------------------------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include"MedecinResident.h"
#include "Medecin.h"
#include"Etudiant.h"

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :MedecinResident::MedecinResident()
* Description : Constructeur par paramètre pour intialiser les attributs de la classe.
* Parametre : nom, dateDeNaissance, matricule, etablisssemnt, numeroLicence et specialite
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
MedecinResident::MedecinResident(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablisssement,const std::string& numeroLicence, Specialite specialite)
	:Medecin( nom,  numeroLicence,  specialite),Etudiant(etablisssement,nom,dateDeNaissance, matricule){}





/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : MedecinResident::afficher();
* Description :  Méthode qui affiche les informations reliées a un medecinResident
* Parametre : param stream
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
void MedecinResident::afficher(std::ostream& stream) const {

	Medecin::afficher(stream);		// 1- Afficher les informations liées à la classe Medecin
	stream << "\n\t";					// 2- Afficher "\n\t"
	Etudiant::afficher(stream);			// 3-  Afficher les informations liées à la classe Etudiant


}




/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : MedecinResident::getSalaireAnnuel()
* Description :  methode qui retourne le nombre  nombre de consultation d'un medecin
* Parametre : rien
* Retour :    Retourner le Salaire annuel qui est:  salaire de base du médecin résidant + nombre de consultations * le prix de consultation du médecin
----------------------------------------------------------------------------------------------------------------------------
*/

double MedecinResident::getSalaireAnnuel() const{
	return SALAIRE_DE_BASE_MEDECIN_RESIDENT + (getNombreConsultations() * getPrixConsultation());
}