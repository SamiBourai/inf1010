/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 23-may-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Medecin.h.
-----------------------------------------------------------------------------------------------------------------------------
*/

#include <iostream>
#include "Medecin.h"
#include "typesafe_enum.h"

constexpr std::size_t CAPACITE_PATIENTS_INITIALE = 2;



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::Medecin().
* Description :  c'est le conctructeur par paramètre  de la classe Medecin avec une liste d'initialisation
* Parametre :Nom du medecin, Numero de licence du medecin et Specialite du medecin
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/

Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite)
	: nom_(nom), 
	numeroLicence_(numeroLicence), 
	specialite_(specialite), 
	patientsAssocies_(std::vector<Patient*>(0)) { }



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : l'operateur +=
* Description :  Méthode qui ajoute un patien à liste des patients associes au medecin.
* Parametre : Patient patient à ajouter
* Retour :    false si l'operation a echouee sinon un vrai si elle a reussi.
----------------------------------------------------------------------------------------------------------------------------
*/


bool Medecin::operator+=(const Patient& patient1) {

	bool estAjouter = false;
//sizeof(patientsAssocies_)/sizeof(Patient)>=patientsAssocies_.capacity()
	if (chercherPatient(patient1.getNumeroAssuranceMaladie()))
	{
		return estAjouter;
	}
	else
	{
		patientsAssocies_.push_back(new Patient (patient1));

		return true;

	}
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : l'operateur -=
* Description :  methode qui supprime un patient en usant son numeroAssuranceMaladie
* Parametre : numeroAssuranceMaladie
* Retour :   false si l'operation a echouee sinon un vrai si elle a reussi.
----------------------------------------------------------------------------------------------------------------------------
*/

bool Medecin::operator-=(const std::string& numAssuranceMaladie) {
	bool patientEstSuprime = false;
	for (int i = 0; i < patientsAssocies_.size(); i++)
	{
		if (patientEstSuprime)
		{
			patientsAssocies_[i] = patientsAssocies_[i+1];
		}
		if (patientsAssocies_[i]->getNumeroAssuranceMaladie()==numAssuranceMaladie)
		{
			patientsAssocies_.pop_back();
			patientEstSuprime = true;
		}
	}
	
	return patientEstSuprime;
}



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : operator <<
* Description :  Méthode qui affiche les informations d'un Medecin
* Parametre : display
* Retour :   display.
----------------------------------------------------------------------------------------------------------------------------
*/
std::ostream& operator << (std::ostream& display, const Medecin& medecin1) {
	static const std::string SPECIALITES[] = { "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre" };
	auto index = enum_value(medecin1.specialite_);
	assert(valid_as_enum<Medecin::Specialite>(index));
	std::string specialite = SPECIALITES[index];

	std::string statut = medecin1.estActif_ ? "Actif" : "Inactif";

	display << "\nMedecin: " << medecin1.nom_
		<< "\n\tNumero de licence: " << medecin1.numeroLicence_
		<< "\n\tSpecialite: " << specialite
		<< "\n\tStatut: " << statut
		<< (medecin1.patientsAssocies_.size() == 0 ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");

	for (std::size_t i = 0; i < medecin1.patientsAssocies_.size(); i++)
	{
		display << "\n\t\t";
		display << *(medecin1.patientsAssocies_[i]);  
	}
	display << '\n';



	return display;

}



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Opérateur ==
* Description : qui compare un string avec le numero d'assurance maladie du patient avec patient comme opérande de gauche
* Parametre : assuranceMaladie et un patient
* Retour :   un bool, vrai si oui c'est egale, sinon faux
----------------------------------------------------------------------------------------------------------------------------
*/
bool operator==( const std::string& numLicence, const  Medecin& medecin1) {
	
	return medecin1.comparaisonLicenceMedecin(numLicence);
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Opérateur ==
* Description : qui compare le numero d'assurance maladie du patient avec le numero d'assurance comme opérande de gauche.
* Parametre : assuranceMaladie
* Retour :   un bool, vrai si oui c'est egale, sinon faux
----------------------------------------------------------------------------------------------------------------------------
*/

bool Medecin::operator==(const std::string& numLicence) {

	return comparaisonLicenceMedecin(numLicence);
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient* Medecin::chercherPatient()
* Description :  Chercher un patient dans la liste patients_ par son numéro d'assurance maladie
* Parametre :const std::string& numeroAssuranceMaladie
* Retour : Retourner le pointeur vers le patient si trouvé, sinon retourner nullptr
----------------------------------------------------------------------------------------------------------------------------
*/

Patient* Medecin::chercherPatient(const std::string& numeroAssuranceMaladie) {    // a verifier 
	Patient* patient1=nullptr;

	for (size_t i = 0; i < patientsAssocies_.size(); i++)
	{
		if (numeroAssuranceMaladie==patientsAssocies_[i]->getNumeroAssuranceMaladie())
		{
			 patient1= patientsAssocies_[i];
			
			 return  patient1;
		}
	}
	return nullptr;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::getNom() const
* Description :  getter 
* Parametre : rien
* Retour :  nom medecin
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& Medecin::getNom() const
{

	return nom_;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::getNumeroLicence()
* Description :  getter qui retourne  le numéro de licence / comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour :  retourner le numéro d'assurance maladie
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& Medecin::getNumeroLicence() const
{

	return numeroLicence_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::getEstActif()
* Description :  attribut estActif_) / comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour :  retourner  l'état du médecin (attribut estActif_)
----------------------------------------------------------------------------------------------------------------------------
*/
bool Medecin::getEstActif() const
{

	return estActif_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin:: getSpecialite()
* Description :  getter\comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour : retourner la spécialité
----------------------------------------------------------------------------------------------------------------------------
*/
const Medecin::Specialite Medecin::getSpecialite() const
{

	return specialite_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin:: getNombrePatientsAssocies()
* Description :  getter\comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour : retourner le nombre de patients dans le tableau patientsAssocies_
----------------------------------------------------------------------------------------------------------------------------
*/
const size_t Medecin::getNombrePatientsAssocies() const
{

	return patientsAssocies_.size();
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : const size_t Medecin::getCapacitePatientAssocies()
* Description : Méthode qui retourne la capacité du tableau patientsAssocies_
* Parametre : rien.
* Retour : return la capacité du tableau patientsAssocies_
----------------------------------------------------------------------------------------------------------------------------
*/

const size_t Medecin::getCapacitePatientAssocies() const
{

	return patientsAssocies_.capacity();
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin:: getPatientsAssocies()
* Description :  getter\comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour : liste de patients associes
----------------------------------------------------------------------------------------------------------------------------
*/
std::vector<Patient*> Medecin::getPatientsAssocies() const
{
	return patientsAssocies_;
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::setNom()
* Description : set le nom
* Parametre : nom
* Retour : rien
----------------------------------------------------------------------------------------------------------------------------
*/

void Medecin::setNom(const std::string& nom)
{
	nom_ = nom;
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : void Medecin::setNumeroLicence()
* Description :  set  le numéro de licence
* Parametre : numeroLicence
* Retour : rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Medecin::setNumeroLicence(const std::string& numeroLicence)
{
	numeroLicence_ = numeroLicence;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : void Medecin::setEstActif()
* Description :  set le bool estActif
* Parametre : estActif
* Retour : rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Medecin::setEstActif(bool estActif)
{

	estActif_ = estActif;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : setSpecialite()
* Description :  set la spécialité
* Parametre : Specialite specialite
* Retour : rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : bool Medecin::comparaisonLicenceMedecin()
* Description :  compare deux numero de licence 
* Parametre : numeroLicence
* Retour : bool : vrai si sont egale, faux si le cas contraire
----------------------------------------------------------------------------------------------------------------------------
*/
bool Medecin::comparaisonLicenceMedecin(const std::string& numLicence)const {
	bool bon = false;
	if (numeroLicence_==numLicence)
	{
		return !bon;
	}
	return bon;
}