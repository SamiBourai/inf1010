
// TODO: Faire l'entête de fichier

/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 11-may-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Medecin.h.
-----------------------------------------------------------------------------------------------------------------------------
*/


#include"Medecin.h"           
#include"Patient.h"				
#include <iostream>
#include "typesafe_enum.h"
#include <memory>



constexpr std::size_t CAPACITE_PATIENTS_INITIALE = 2;


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::Medecin().
* Description :  c'est le conctructeur par paramètre  de la classe Medecin avec une liste d'initialisation 
  Utilisez CAPACIT_PATIENTS_INITIALE pour la taille initiale de patientsAssocies_ (tableau de taille dynamique)
* Parametre : ce dernier prend comme parametre tous les attributs de la classe Medecin.
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/

Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite) :

	nom_(nom), numeroLicence_(numeroLicence), specialite_(specialite), estActif_(true), nbPatientsAssocies_(0),
	capacitePatientsAssocies_(CAPACITE_PATIENTS_INITIALE), patientsAssocies_(std::make_unique<std::shared_ptr<Patient>[]> (CAPACITE_PATIENTS_INITIALE) )
{}



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : void Medecin::ajouterPatient();
* Description :  Méthode qui ajoute un patien à liste des patients associes au medecin.
* Parametre : Patient patient à ajouter
* Retour :   ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/

void Medecin::ajouterPatient(Patient patient)
{
	static constexpr unsigned int AUGMENTATION_NOMBRE_PATIENTS = 2;
	// TODO
	// Verifier si assez de mémoire est allouée
	if (nbPatientsAssocies_>=capacitePatientsAssocies_)
	{// Si pas assez de mémoire, doubler la taille du tableau (AUGMENTATION_NOMBRE_PATIENTS)

		capacitePatientsAssocies_ *= AUGMENTATION_NOMBRE_PATIENTS;

		// Ajouter le patient au tableau
		// Utiliser std::unique_ptr<std::shared_ptr<Patient>[]> ainsi que std::move pour transférer le ownership
		// du tableau temporaire vers le tableau membre patientsAssocies_;


		std::unique_ptr < std::shared_ptr<Patient>[]> patientXX = std::make_unique<std::shared_ptr<Patient>[]>(capacitePatientsAssocies_);

		//A verifier ce qui marche pas 
		for (size_t i = 0; i < nbPatientsAssocies_; i++)
		{
			patientXX[i] = patientsAssocies_[i];
		}
		patientsAssocies_ = std::move(patientXX);
	}
	
	patientsAssocies_[nbPatientsAssocies_]= std::make_shared<Patient>(patient);

	nbPatientsAssocies_++;
	
	
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : bool Medecin::supprimerPatient();
* Description :  methode qui supprime un patient en usant son numeroAssuranceMaladie
* Parametre : numeroAssuranceMaladie
* Retour :   false si l'operation a echouee sinon un vrai si elle a reussi.
----------------------------------------------------------------------------------------------------------------------------
*/


bool Medecin::supprimerPatient(const std::string& numeroAssuranceMaladie) {
	
	bool patientEstSuprime = false;

	for (size_t i = 0; i < nbPatientsAssocies_; i++)
	{
		if (patientEstSuprime)
		{
			patientsAssocies_[i - 1] = patientsAssocies_[i];
		}

		if (patientsAssocies_[i]->getNumeroAssuranceMaladie()==numeroAssuranceMaladie)
		{ 
			patientsAssocies_[i] = 0;

			patientEstSuprime = true;


		}
		
	}
	if (patientEstSuprime)
	{
		nbPatientsAssocies_--;
	}

	return  patientEstSuprime;
}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::afficher();
* Description :  Méthode qui affiche les informations d'un Medecin
* Parametre : stream
* Retour :   ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/
void Medecin::afficher(std::ostream& stream) const
{
	static const std::string SPECIALITES[] = {  "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre"};
	auto index = enum_value(specialite_);
	assert(valid_as_enum<Specialite>(index));
	std::string specialite = SPECIALITES[index];

	std::string statut = estActif_ ? "Actif" : "Inactif";

    stream << "\nMedecin: " << nom_
           << "\n\tNumero de licence: " << numeroLicence_ 
		   << "\n\tSpecialite: " << specialite
		   << "\n\tStatut: " << statut
           << (nbPatientsAssocies_ == 0 ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");
	
	// TODO : afficher les patients associés au medecin
	for (size_t i = 0; i < nbPatientsAssocies_; i++)
	{
		 stream << '\n' << '\t'<< '\t';
		 patientsAssocies_[i]->afficher(stream);
		
	}
	stream << "\n";
	
}



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::getNom();
* Description :  getter qui retourne le nom / comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour :   nom_;
----------------------------------------------------------------------------------------------------------------------------
*/
const std::string& Medecin::getNom() const {
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
const std::string& Medecin::getNumeroLicence() const {
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

bool Medecin::getEstActif() const {
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


const Medecin::Specialite Medecin::getSpecialite() const {
	return specialite_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin:: getCapacitePatientAssocies()
* Description :  getter\comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour : retourner la capacité du tableau patientsAssocies_
----------------------------------------------------------------------------------------------------------------------------
*/

const size_t Medecin::getCapacitePatientAssocies() const {
	return capacitePatientsAssocies_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin:: getNombrePatientsAssocies()
* Description :  getter\comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour : retourner le nombre de patients dans le tableau patientsAssocies_
----------------------------------------------------------------------------------------------------------------------------
*/

const size_t Medecin::getNombrePatientsAssocies() const {
	return nbPatientsAssocies_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin:: getPatientsAssocies()
* Description :  getter\comme c'est une fonction qui ne modifie pas les objet alors on la declare comme CONST
* Parametre : rien.
* Retour : retourner le tableau des patients associés au médecin (attribut patientsAssocies_)
----------------------------------------------------------------------------------------------------------------------------
*/

std::unique_ptr<std::shared_ptr<Patient>[]> Medecin::getPatientsAssocies() {

	return std::move(patientsAssocies_);

}
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin:: setNom()
* Description :  set le nom
* Parametre : nom
* Retour : rien
----------------------------------------------------------------------------------------------------------------------------
*/


void Medecin::setNom(const std::string& nom) {
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


void Medecin::setNumeroLicence(const std::string& numeroLicence) {
	numeroLicence_ = numeroLicence;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : void Medecin::setNumeroLicence()
* Description :  set le bool estActif
* Parametre : estActif
* Retour : rien
----------------------------------------------------------------------------------------------------------------------------
*/

void Medecin::setEstActif(bool estActif) {
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


void Medecin::setSpecialite(Specialite specialite) {
	specialite_ = specialite;
}