/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Medecin.h.
-----------------------------------------------------------------------------------------------------------------------------
*/
#include <iostream>
#include "Medecin.h"
#include "typesafe_enum.h"


constexpr int PATIENT_INEXSISTANT = -1;


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :Medecin::Medecin()
* Description : Constructeur par paramètre pour intialiser les attributs de la classe. 
* Parametre : nom numeroLicence et specialite
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite) : 
	Personnel(nom, numeroLicence), specialite_(specialite),nbConsultations_(0),patientsAssocies_(std::vector<Patient*>()){}

//! Operateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
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

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::afficher();
* Description :  Méthode qui affiche les informations reliées a un medecin
* Parametre : param stream
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Medecin::afficher(std::ostream& stream) const
{
	static const std::string SPECIALITES[] = { "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre" };
	auto index = enum_value(specialite_);
	assert(valid_as_enum<Medecin::Specialite>(index));
	std::string specialite = SPECIALITES[index];

	// Afficher les informations du médecin liées à la classe Personnel

	Personnel::afficher(stream);

	stream << "\n\tSpecialite: " << specialite
		<< (patientsAssocies_.empty() ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");

	for (const auto& patient : patientsAssocies_)
	{
		stream << "\n\t\t";
		patient->afficher(stream);
		// Afficher les informations du Patient
	}
}

//! Méhode qui cherche un patient par numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* Medecin::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (auto& patientsAssocie : patientsAssocies_)
	{
		if (*patientsAssocie == numeroAssuranceMaladie)
		{
			return patientsAssocie;
		}
	}

	return nullptr;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Medecin::incrementNombreConsultations()
* Description :   Incrementer le nombre de consultaions
* Parametre : rien
* Retour :  rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Medecin::incrementNombreConsultations() { nbConsultations_++; }


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Medecin::getSalaireAnnuel()
* Description :  methode qui retourne le salaire annuel d'un medecin
* Parametre : rien
* Retour :   salaireAnnuel =  salaire de base du médecin + nombre de consultations * le prix de consultation
----------------------------------------------------------------------------------------------------------------------------
*/
double  Medecin::getSalaireAnnuel() const {
	return SALAIRE_DE_BASE_MEDECIN + (nbConsultations_ * getPrixConsultation());
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :   Medecin::getPrixConsultation()
* Description :  methode qui retourne le nombre  nombre de consultation d'un medecin
* Parametre : rien
* Retour :   nbConsultations_
----------------------------------------------------------------------------------------------------------------------------
*/
double Medecin::getPrixConsultation() const {
		
	switch (getSpecialite())
	{
		
	case Specialite::Gynecologue: return 100.00;
	case Specialite::Ophtalmologue: return 100.00;

	case Specialite::Cardiologue: return 120.00;
	case Specialite::Dermatologue: return 120.00;

	case Specialite::Pediatre: return 80.00;

	
	case Specialite::Generaliste: return 60.00;
	case Specialite::Autre: return 60.00;
	
	default:
		throw "La spécialite du médecin n'est pas définie";
	}
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Medecin::getNombreConsultations() 
* Description :  methode qui retourne le nombre  nombre de consultation d'un medecin
* Parametre : rien
* Retour :   nbConsultations_
----------------------------------------------------------------------------------------------------------------------------
*/
const size_t Medecin::getNombreConsultations() const {
	return nbConsultations_;
}


//! Méthode qui retourne la specialite du medecin
//! \return la specialite des medecins
const Medecin::Specialite Medecin::getSpecialite() const
{

	return specialite_;
}

//! Méthode qui retourne le nombre de patients associés
//! \return le nombre de patients associés
const size_t Medecin::getNombrePatientsAssocies() const
{

	return patientsAssocies_.size();
}


//! Méthode qui retourne la liste des patients associes au medecin
//! \return la liste des patients
const std::vector<Patient*>& Medecin::getPatientsAssocies() const
{
	return patientsAssocies_;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Medecin::setNbConsultations();
* Description :  methode qui set la specialite d'un medecin
* Parametre : specialite
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Medecin::setNbConsultations();
* Description :  methode qui set le nombre de consultation d'un medecin
* Parametre : nombreConsultaion
* Retour :   rien
----------------------------------------------------------------------------------------------------------------------------
*/
void Medecin::setNbConsultations(size_t nombreConsultaion) {
	nbConsultations_ = nombreConsultaion;
}


//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
//! \return             int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
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

