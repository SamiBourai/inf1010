/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 07-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Hopital.h.
-----------------------------------------------------------------------------------------------------------------------------
*/
#include "Hopital.h"
#include "ConsultationPhysique.h"
#include"ConsultationEnligne.h"

//! Constructeur par paramètre  de la classe Hopital
//! \param nom      Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse) :nom_(nom), adresse_(adresse)
{
}

//! Methode pour charger la base de donnees de l'hopital
//! \param nomFichierMedecins  le nom du fichier qui contient les informations des medecins
//! \param adresse  nomFichierPatients le nom du fichier qui contient les informations des patients
bool Hopital::chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients)
{
	return gestionnairePersonnels_.chargerDepuisFichier(nomFichierMedecins)
		&& gestionnairePatients_.chargerDepuisFichier(nomFichierPatients);
}

//! Operateur qui ajoute une consultation à un hopital
//! \param consultation à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Consultation& consultation)
{	
	
		if (dynamic_cast<Medecin*>(getGestionnairePersonnels().chercherPersonnel(consultation.getMedecin()->getId()))&& consultation.getMedecin()->getEstActif())
		{ //TODO utiliser chercherPersonnel de GestionnairePersonnel pour avoir un pointeur vers le medecin de la consultation.);
			
			if (!getGestionnairePatients().chercherPatient(consultation.getPatient()->getNumeroAssuranceMaladie()))
			{
				return false;
				//Si le medecin existe et actif, vérifier si le patient n'existe pas dans gestionnaire patient et retourner false.
			}
			else
			{
				// si le patient existe , ajouter la conversation à consultations_ après voir vérifier son type: connsultatioEnligne ou ConsultaitionPhysique
				//Chercher si le patient est associé à ce médecin sinon à ajouter le patient au médecin

				ConsultationPhysique* consultaionPhysique1 = dynamic_cast<ConsultationPhysique*>(&const_cast<Consultation&>(consultation));
				ConsultationEnligne* consultaionEnligne1 = dynamic_cast<ConsultationEnligne*>(&const_cast<Consultation&>(consultation));
				if (consultaionPhysique1) {

					consultations_.push_back(std::make_shared<ConsultationPhysique>(*consultaionPhysique1));
				}
				else if (consultaionEnligne1)
					consultations_.push_back(std::make_shared<ConsultationEnligne>(*consultaionEnligne1));
					

				if (!consultation.getMedecin()->chercherPatient(consultation.getPatient()->getNumeroAssuranceMaladie()))
				{
						*(consultation.getMedecin()) += consultation.getPatient();

				}
				consultation.getMedecin()->incrementNombreConsultations();
				//incrementer le nombre de consultation du medecin.
			}
		}


	
		return true;
}

//! Operateur qui ajoute un médecin à un hopital
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Medecin& medecin)
{
	std::shared_ptr<Medecin>medecin1 = std::make_shared<Medecin>(medecin);
	return gestionnairePersonnels_ += &*medecin1;
}

//! Operateur qui ajoute un patient à un hopital
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Patient& patient)
{
	std::shared_ptr<Patient>patient1 = std::make_shared<Patient>(patient);
	return gestionnairePatients_ += &*patient1;
}

//! Méthode qui retourne le nom de l'hopital
//! \return le nom de l'hopital 
const std::string& Hopital::getNom() const
{
	return nom_;
}

//! Méthode qui retourne l'adresse de l'hopital
//! \return l'adresse de l'hopital 
const std::string& Hopital::getAdresse() const
{
	return adresse_;
}

//! Méthode qui retourne le gestionnaire des medecins
//! \return gestionnaire des medecins
GestionnairePersonnels& Hopital::getGestionnairePersonnels()
{
	return gestionnairePersonnels_;
}

//! Méthode qui retourne le gestionnaire des patients
//! \return gestionnaire des patients
GestionnairePatients& Hopital::getGestionnairePatients()
{
	return gestionnairePatients_;
}

//! Méthode qui retourne les consultaions de l'hopital
//! \return consultations_
const std::vector<std::shared_ptr<Consultation>>& Hopital::getConsultations() const
{
	return consultations_;
}

//! Méthode qui permet de mettre à jour le nom de l'hopital
//! \Param nom Le nom de l'hopital
void Hopital::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour l'adresse de l'hopital
//! \Param adresse  l'adresse de l'hopital
void Hopital::setAdresse(const std::string& adresse)
{
	adresse_ = adresse;
}

