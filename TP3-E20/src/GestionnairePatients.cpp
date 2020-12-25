/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe GestionnairePatients.h.
-----------------------------------------------------------------------------------------------------------------------------
*/
#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients() : patients_(std::vector<std::shared_ptr<Patient>>(0))
{
}

//! Méhode qui cherche un patient par son numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (auto& patient : patients_)
	{
		if (*patient == numeroAssuranceMaladie)
		{
			return patient.get();
		}
	}

	return nullptr;
}

//! Méthode  qui permet de charger les informations des patients depuis un fichier
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succès
bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		patients_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLignePatient(ligne))
			{
				return false;
			}
		}
		return true;
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";

	return false;
}

//! Operateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return        Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePatients::operator+=(Patient* patient)
{
	//std::shared_ptr<PatientEtudiant> patientE=std::make_shared<PatientEtudiant>();
	if (patient && !chercherPatient(patient->getNumeroAssuranceMaladie())) {

		if (patients_.size() >= NB_PATIENT_MAX)
		{
			return false;
		}
		if(dynamic_cast<PatientEtudiant*>(patient)) // // nulptr
		{	
			PatientEtudiant* ptr_P = dynamic_cast<PatientEtudiant*>(patient);

			patients_.push_back(std::make_shared<PatientEtudiant>(*ptr_P));
		}else
			patients_.push_back(std::make_shared<Patient>(*patient));
		  
		// TODO : vérifier le type de patient. S'il est PatientEtudiant, faire une conversion dynamique avant de l'ajouter 
		// au vecteur patients_
		return true;
	}
	return false;
}

//! opérateur qui affiche les patients
//! \param os Le stream dans lequel afficher
//! \param gestionnairePatients le gestionnaire de patient que l'on veut afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatients)
{
	for (const auto& patient : gestionnairePatients.patients_)
	{
		// TODO : afficher les informations du patient
		patient->afficher(os);
		os << '\n';
	}

	return os;
}

//! Méthode qui retourne tous les  patients
//! \return patients_ les patients
const std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients() const
{
	return patients_;
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePatients::getPatientsEtudiants()
* Description : Chercher les Patients étudiants parmis tous les patients et le mettre dans le vecteur declaré
* Parametre : rien
* Retour :    Retourner un vecteur de PatientEtudiant*

----------------------------------------------------------------------------------------------------------------------------
*/
std::vector<std::shared_ptr<PatientEtudiant>> GestionnairePatients::getPatientsEtudiants()const {
	

	
	std::vector < std::shared_ptr<PatientEtudiant>>tousPatientEtudiant;

	
	for (size_t i = 0; i < getNbPatients() ; i++)
	{
		PatientEtudiant* ptr_PE = dynamic_cast<PatientEtudiant*>(&*patients_[i]);

		if (ptr_PE!=nullptr)
		{
			tousPatientEtudiant.push_back(std::make_shared<PatientEtudiant>(*ptr_PE));
		}
	}
	

	return tousPatientEtudiant;
}

//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return patients_.size();
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :GestionnairePatients::getNbPatientsEtudiants()
* Description :  retourner le nombre de patient Etudiant
* Parametre : rien
* Retour :    nombre patient etudiant
----------------------------------------------------------------------------------------------------------------------------
*/
size_t GestionnairePatients::getNbPatientsEtudiants() const {
	
	return getPatientsEtudiants().size();
}

//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePatient; // Indique le type de patient. 0 : Patient , 1 : PatientEtudiant (voir l'enum TypePatient)
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;

	std::string matricule;
	std::string etablissement;

	if (stream >> indexTypePatient >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie))
	{
		

		switch (to_enum<GestionnairePatients::TypePatient, int>(indexTypePatient)) {

		case TypePatient::Patient :
			
			 *this += new Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie);
			return true;

		case TypePatient::PatientEtudiant: 
			stream >>std::quoted(matricule)>> std::quoted(etablissement)  ;

			
			*this += new PatientEtudiant(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, matricule,etablissement);
			return true;
			
		default :
			assert(false);
		}

		
	}
	
	return false;

}