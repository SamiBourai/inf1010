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
#include <iterator>
#include <Foncteurs.h>


//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients() : patients_(std::vector<std::shared_ptr<Patient>>())
{
}

//! Méhode qui cherche un patient par son numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	auto variable_Izi =std::find_if(patients_.begin(), patients_.end(),ComparateurEstEgalAvecId<Patient>(numeroAssuranceMaladie) );

	if (variable_Izi==patients_.end())
	{
		return nullptr;
	}
	return variable_Izi->get();
	
	
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

//! methode qui ajoute un patient à la liste des patients
//! \La méthode prend une référence vers l'objet à jouter
//! \return        Un bool qui indique si l'opération a bien fonctionnée

template<typename T>
bool GestionnairePatients::ajouterPatient( Patient& patient)
{


	if (chercherPatient(patient.getNumeroAssuranceMaladie())==nullptr)
	{
		if (patients_.size() >= NB_PATIENT_MAX)
		{
			return false;
		}
		else {
			patients_.push_back(std::make_shared<T>(*dynamic_cast<T*>(&patient)));
		}

		//*dynamic_cast<T*>(&patient))
		return true;
	}
	else
	{
		return false;

	}
	
}


//! methode qui supprime un patient de la liste des patients
//! \Les paramètres : numero d'assurance Maladie de type string patient à supprimer
//! \return        Un bool qui indique si l'opération a bien fonctionnée

bool GestionnairePatients::supprimerPatient(const std::string& assuranceMaladie) {

	auto it = std::remove_if(patients_.begin(), patients_.end(), ComparateurEstEgalAvecId<Patient>(assuranceMaladie));
	bool siYaChangement = it != patients_.end();
	patients_.erase(it, patients_.end());
	return siYaChangement;

}

//! opérateur qui affiche les patients
//! \param os Le stream dans lequel afficher
//! \param gestionnairePatients le gestionnaire de patient que l'on veut afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatients)
{
	
	if constexpr (false)
	{
		for (auto it = gestionnairePatients.patients_.cbegin(); it != gestionnairePatients.patients_.cend(); ++it)
		{
			(*it)->afficher(os);
			os << '\n';
		}
		return os;
	}
	
	else
	{
		// utiliser une boucle for range-based
		for (auto i : gestionnairePatients.patients_)
		{
			(*i).afficher(os);
			os << '\n';
		}
		return os;
		
	}
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
* Retour :  Elle retourne un vecteur de pointeur shared_ptr vers Patient

----------------------------------------------------------------------------------------------------------------------------
*/
std::vector<std::shared_ptr<Patient>> GestionnairePatients::getPatientsEtudiants() const
{
	std::vector<std::shared_ptr<Patient>> patientsEtudiants;
	std::copy_if(patients_.begin(), patients_.end(), std::back_inserter(patientsEtudiants), ComparateurTypePatient<PatientEtudiant>());
	return patientsEtudiants;
}

//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{

	return patients_.size();
}

//! Méthode qui retourne le nombre des patients étudiants dans la liste
//! \return Le nombre de patients étudiants dans la liste
size_t GestionnairePatients::getNbPatientsEtudiants() const
{
	return getPatientsEtudiants().size();
}


//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
// return un bool si l'operation a marcher ou pas 
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePatient;
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;
	std::string dateAdhesion;

	std::string matricule;
	std::string etablissement;

	if (stream >> indexTypePatient >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie))
		
	{tm dateTransformeeEnTm = convertirStringDate(dateAdhesion);
	Patient m;
	
		switch (to_enum<GestionnairePatients::TypePatient, int>(indexTypePatient)) {
		case TypePatient::Patient:
			m = Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, dateTransformeeEnTm);
			return ajouterPatient<Patient>(m);

			
		case TypePatient::PatientEtudiant:
			 
			stream >> std::quoted(matricule) >> std::quoted(etablissement);
			{PatientEtudiant mdz = PatientEtudiant(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, dateTransformeeEnTm, matricule, etablissement);
			return ajouterPatient<PatientEtudiant>(mdz); }
			//break;
			//return true;
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
		}

	
	}

	return false;
}
