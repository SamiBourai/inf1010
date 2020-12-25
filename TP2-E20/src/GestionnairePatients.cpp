/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 23-may-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe GestionnairePatients.h .
-----------------------------------------------------------------------------------------------------------------------------
*/
#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePatients::GestionnairePatients()
* Description :  c'est le conctructeur par default de la classe GestionnairePatients 
* Parametre : -
* Retour : -
----------------------------------------------------------------------------------------------------------------------------
*/
GestionnairePatients::GestionnairePatients(){}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePatients::GestionnairePatients()
* Description :  c'est le conctructeur par copie  de la classe GestionnairePatients 
* Parametre : const GestionnairePatients& gestionnairePatiens
* Retour :  il ne retourne rien.
----------------------------------------------------------------------------------------------------------------------------
*/
GestionnairePatients::GestionnairePatients(const GestionnairePatients& gestionnairePatiens) {
	for (size_t i = 0; i < gestionnairePatiens.patients_.size(); i++)
		patients_.push_back(std::make_shared<Patient>(*gestionnairePatiens.patients_[i]));


}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :GestionnairePatients& GestionnairePatients::operator=()
* Description : operateur d'affectation 
* Parametre : const GestionnairePatients& gestionnairePatients
* Retour : *this
----------------------------------------------------------------------------------------------------------------------------
*/
GestionnairePatients& GestionnairePatients::operator=(const GestionnairePatients& gestionnairePatients) {
	
	if (this!=&gestionnairePatients)
	{
		for (size_t i = 0; i < gestionnairePatients.patients_.size(); i++)
		{
			patients_.push_back(gestionnairePatients.patients_[i]);
		}

	}
	

	return *this;

	/*
	Company& operator=(const Company & company) {
		if (this != &company) {
			employees_ = company.employees_;
			president_ = make_unique<Employee>(*company.president_);
		}
		return *this;
	*/
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Patient* GestionnairePatients::chercherPatient()
* Description :  Chercher un patient dans la liste patients_ par son numéro d'assurance maladie
* Parametre :const std::string& numeroAssuranceMaladie
* Retour : Retourner le pointeur vers le patient si trouvé, sinon retourner nullptr
----------------------------------------------------------------------------------------------------------------------------
*/

Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (int i=0;i<patients_.size();i++)
	{
		// À adapter au vecteur et pour l'opérateur==
		if (patients_[i]->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			return &*patients_[i];
			
			//boost::shared_ptr<foo> foo_ptr(new foo());
			//c_library_function(&*foo_ptr);
			//https://stackoverflow.com/questions/505143/getting-a-normal-ptr-from-shared-ptr
			
		}
	}


	return nullptr;
}



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : bool GestionnairePatients::chargerDepuisFichier()
* Description :  Méthode  qui permet de charger les informations des patients depuis un fichier
* Parametre : param nomFichier   Le nom du fichier à charger
* Retour : Un bool qui indique si le fichier a été chargé avec succès
----------------------------------------------------------------------------------------------------------------------------
*/

bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (!fichier.fail())
	{
		
		patients_.clear(); // equivalent a patient_={};
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (lireLignePatient(ligne) == false)
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
/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : l'operateur +=
* Description :  Méthode qui ajoute un patient a liste de patient
* Parametre : Patient patient à ajouter
* Retour :    false si l'operation a echouee sinon un vrai si elle a reussi.
----------------------------------------------------------------------------------------------------------------------------
*/

bool GestionnairePatients::operator+=(const Patient& patient1){

	bool estInExistant = chercherPatient(patient1.getNumeroAssuranceMaladie()); // pour verifier si il existe
	int nbPatients = getNbPatients(); // pour savoir combien y a de patients et donc si la limite est atteinte ou pas

	if (nbPatients>=NB_PATIENT_MAX || estInExistant==true)
	{
		return false;
	}
	else
	{
		patients_.push_back(std::make_shared<Patient>(patient1));
		return true;
	}
	
}


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : operator <<
* Description :  Méthode qui affiche les informations d'un Patient
* Parametre : display et const GestionnairePatients& patients
* Retour :   display.
----------------------------------------------------------------------------------------------------------------------------
*/
std::ostream& operator << (std::ostream& display, const GestionnairePatients& patients) {
	for (size_t i = 0; i < patients.patients_.size(); i++)
	{
		display<<*patients.patients_[i]<< '\n';
		
	}
	return display;
}



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : GestionnairePatients::getNbPatients()
* Description : getter
* Parametre : rien
* Retour :  nbPatients_
----------------------------------------------------------------------------------------------------------------------------
*/
size_t GestionnairePatients::getNbPatients() const
{
	return patients_.size();
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : std::vector < std::shared_ptr<Patient>> GestionnairePatients::getPatients() const
* Description :getter
* Parametre : -
* Retour :patient_
----------------------------------------------------------------------------------------------------------------------------
*/
std::vector < std::shared_ptr<Patient>> GestionnairePatients::getPatients() const {
	
	return  patients_;
}

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :GestionnairePatients::lireLignePatient()
* Description : Méthode qui lit les attributs d'un patient
* Parametre : const std::string& ligne  /param ligne  Le string qui contient les attributs
* Retour : bool- true si y a eu succes /false si y a eu echec
----------------------------------------------------------------------------------------------------------------------------
*/
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;


	

	if (stream >> quoted(nomPatient) >> quoted(anneeDeNaissance) >> quoted(numeroAssuranceMaladie))
	{
		bool enLu = *this += Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie);
		return enLu;
		
	}
	return false;
}
