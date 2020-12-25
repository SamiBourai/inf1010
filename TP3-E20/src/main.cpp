//! Fonction main qui test le programme
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 07 Mai 2020

#include <algorithm>
#include <stdio.h>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include <assert.h>
#include "Patient.h"
#include "PatientEtudiant.h"
#include "debogageMemoire.h"
#include "GestionnairePatients.h"
#include "Medecin.h"
#include "MedecinResident.h"
#include "GestionnairePersonnels.h"
#include "typesafe_enum.h"
#include "Consultation.h"
#include "ConsultationEnligne.h"
#include "ConsultationPhysique.h"
#include "Hopital.h"

// NOTE: Pour que le programme compile, vous pouvez changer tous les #if true à des #if false,
// et mettre en commentaire tout le code qui a été écrit pour vous. Ainsi, vous pourrez
// graduellement les #if true et tester des petits blocs de code à la fois.

int main()
{
	initDebogageMemoire();

	GestionnairePersonnels gestionnairePersonnels;
	GestionnairePatients gestionnairePatients;
	Patient patientTest = Patient("Simon", "25/10/92", "P003");
	PatientEtudiant patientEtudiantTest = PatientEtudiant("Timon", "05/06/1998", "PE0002", "100002", "HEC Montreal");
	Medecin medecinTest = Medecin("Tamard", "M003", Medecin::Specialite::Cardiologue);
	MedecinResident medecinResidentTest = MedecinResident("Tira", "12/11/1991", "111113", "University Of Toronto", "MR003", Medecin::Specialite::Gynecologue);
	
	std::vector<bool> tests;

	// Test 1 : tester la classe PatientEtudiant , Patient et implicaitement Etudiant
#if true
	/**/
	// Tester l'affichage du patient --------------------------------111111-----------------------------------
	std::stringstream patientStream;
	patientTest.afficher(patientStream);
	std::string patientString = patientStream.str();
	std::cout << patientString << '\n';
	const std::string sortieAttenduePatient =
		"Patient:Type:PatientNom:Simon|Datedenaissance:25/10/92|Numerod'assurancemaladie:P003";

	patientString.erase(
		std::remove_if(patientString.begin(), patientString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		patientString.end());

	tests.push_back(sortieAttenduePatient == patientString);

	// Tester l'affichage du patientEtudiant-------------------------------22222222222222222-------------------------------
	std::stringstream patientEtudiantStream;
	patientEtudiantTest.afficher(patientEtudiantStream);
	std::string patientEtudiantString = patientEtudiantStream.str();
	std::cout << patientEtudiantString << '\n';
	const std::string sortieAttenduePatientEtudiant =
		"Patient:Type:PatientEtudiantNom:Timon|Datedenaissance:05/06/1998|Numerod'assurancemaladie:PE0002|Matricule:100002Etablissement:HECMontreal|Tauxderabais:0.2";

	patientEtudiantString.erase(
		std::remove_if(patientEtudiantString.begin(), patientEtudiantString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		patientEtudiantString.end());

	tests.push_back(sortieAttenduePatientEtudiant == patientEtudiantString);

	// Tester le polymorphisme de l'affichage--------------------------------333333333333333333333----------------------------
	std::shared_ptr<Patient> p = std::make_shared<PatientEtudiant>(patientEtudiantTest);
	std::stringstream pStream;
	p->afficher(pStream);
	std::string pString = pStream.str();
	std::cout << pString << '\n';

	pString.erase(
		std::remove_if(pString.begin(), pString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		pString.end());

	tests.push_back(pString == sortieAttenduePatientEtudiant);
#else
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
#endif

	// Test 2 : tester la classe Medecin, MedecinResident et implicitement Personnel
#if true

	// Tester l'affichage du medecin (incluant le test du polymorphisme de la methode)------------------------44444444444444-----------------
	std::stringstream medecinStream;
	medecinTest.afficher(medecinStream);
	std::string medecinString = medecinStream.str();
	std::cout << medecinString << '\n';

	std::string sortieAttendueMedecin =
		"Personnel:TamardType:MedecinIdentifiant:M003Statut:ActifSpecialite:CardiologueAucunpatientn'estsuiviparcemedecin.";

	medecinString.erase(
		std::remove_if(medecinString.begin(), medecinString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		medecinString.end());

	tests.push_back(sortieAttendueMedecin == medecinString);

	// Tester le polymorphisme de l'affichage du medecin----------------------------555555----------------------
	std::shared_ptr<Personnel> m = std::make_shared<Medecin>(medecinTest);
	std::stringstream mStream;
	m->afficher(mStream);
	std::string mString = mStream.str();
	std::cout << mString << '\n';

	mString.erase(
		std::remove_if(mString.begin(), mString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		mString.end());

	tests.push_back(mString == sortieAttendueMedecin);

	// Tester la methode incrementNombreConsultations , getSalaireAnnuel et getPrixConsultation du medecin------------------6666--------------------
	for (size_t i = 0; i < 100; i++) medecinTest.incrementNombreConsultations();
	tests.push_back(medecinTest.getNombreConsultations() == 100 
		&& medecinTest.getSalaireAnnuel() == (Medecin::SALAIRE_DE_BASE_MEDECIN + (double)medecinTest.getNombreConsultations()*(double)medecinTest.getPrixConsultation()));

	// Tester l'affichage du medecin (incluant le test du polymorphisme de la methode)-----------------777777-------------------------------------
	std::stringstream medecinResidentStream;
	medecinResidentTest.afficher(medecinResidentStream);
	std::string medecinResidentString = medecinResidentStream.str();
	std::cout << medecinResidentString << '\n';

	std::string sortieAttendueMedecinResident =
		"Personnel:TiraType:MedecinResidentIdentifiant:MR003Statut:ActifSpecialite:GynecologueAucunpatientn'estsuiviparcemedecin.Matricule:111113Etablissement:UniversityOfToronto";

  	medecinResidentString.erase(
		std::remove_if(medecinResidentString.begin(), medecinResidentString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		medecinResidentString.end());

	tests.push_back(sortieAttendueMedecinResident == medecinResidentString);

	// Tester le polymorphisme de l'affichage du medecinResident-------------------------------------8888888------------------------------------
	std::shared_ptr<Personnel> mr = std::make_shared<MedecinResident>(medecinResidentTest);
	std::stringstream mrStream;
	mr->afficher(mrStream);
	std::string mrString = mrStream.str();
	std::cout << mrString << '\n';

	mrString.erase(
		std::remove_if(mrString.begin(), mrString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		mrString.end());

	tests.push_back(mrString == sortieAttendueMedecinResident);

	// Tester la methode incrementNombreConsultations , getSalaireAnnuel et getPrixConsultation du medecin----------------99999-------------
	for (size_t i = 0; i < 100; i++) medecinResidentTest.incrementNombreConsultations();
	tests.push_back(medecinResidentTest.getNombreConsultations() == 100
		&& medecinResidentTest.getSalaireAnnuel() == (MedecinResident::SALAIRE_DE_BASE_MEDECIN_RESIDENT + (double)medecinResidentTest.getNombreConsultations() * (double)medecinResidentTest.getPrixConsultation()));

#else
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
#endif

	// Test 3 : tester la classe GestionnairePatients
#if true

	// Tester le chargement de fichier---------------------------10-------------------------------------------10---------------
	bool resultatLecturePatients = gestionnairePatients.chargerDepuisFichier("patients.txt") &&
		gestionnairePatients.chargerDepuisFichier("patients.txt");
	tests.push_back(resultatLecturePatients);

	// Tester l 'affichage, lireLignePatient et l'operateur += de patient-----------------------------------11---------------11------------------
	std::stringstream patientsStream;
	patientsStream << gestionnairePatients << std::endl;
	std::string patientsString = patientsStream.str();
	std::cout << patientsString << '\n';
	const std::string sortieAttenduePatients =
		"Patient:Type:PatientNom:JohnLourdes|Datedenaissance:12/12/2001|Numerod'assurancemaladie:P001"
		"Patient:Type:PatientNom:GeorgeLucas|Datedenaissance:01/04/1984|Numerod'assurancemaladie:P002"
		"Patient:Type:PatientEtudiantNom:ChristopherLavoie|Datedenaissance:01/04/1999|Numerod'assurancemaladie:PE001|Matricule:100001Etablissement:PolytechniqueMontreal|Tauxderabais:0.2";

	patientsString.erase(
		std::remove_if(patientsString.begin(), patientsString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		patientsString.end());

	tests.push_back(sortieAttenduePatients == patientsString
		&& gestionnairePatients.getNbPatients() == 3);

	// Tester getPatientsEtudiants() et getNbPatientsEtudiants()---------------------------12-------------------------12------------------
	tests.push_back(gestionnairePatients.getNbPatientsEtudiants() == 1
		&& gestionnairePatients.chercherPatient(gestionnairePatients.getPatientsEtudiants()[0]->getNumeroAssuranceMaladie()) == gestionnairePatients.getPatients()[2].get());

#else
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
#endif

	// Test 4 : tester la classe GestionnairePersonnels
#if true

	// Tester le chargement de fichier----------------------------------------13-------------------13--------------------
	bool resultatLecturePersonnels= gestionnairePersonnels.chargerDepuisFichier("personnels.txt") &&
		gestionnairePersonnels.chargerDepuisFichier("personnels.txt");
	assert(resultatLecturePersonnels); // devrait passer => n est pas noté

	// Tester l 'affichage, lireLignePersonnel et l'operateur += de personnel--------------------------14-----------------------14---------
	std::stringstream personnelsStream;
	personnelsStream << gestionnairePersonnels << std::endl;
	std::string personnelsString = personnelsStream.str();
	std::cout << personnelsString << '\n';
	const std::string sortieAttenduePersonnels =
		"Personnel:LourdesJohnType:MedecinIdentifiant:M001Statut:ActifSpecialite:CardiologueAucunpatientn'estsuiviparcemedecin."
		"Personnel:GeorgeLucasType:MedecinIdentifiant:M002Statut:ActifSpecialite:DermatologueAucunpatientn'estsuiviparcemedecin."
		"Personnel:JohnnyKharasanType:MedecinResidentIdentifiant:MR001Statut:ActifSpecialite:CardiologueAucunpatientn'estsuiviparcemedecin.Matricule:111111Etablissement:UdeM"
		"Personnel:TomasLevaconType:MedecinResidentIdentifiant:MR002Statut:ActifSpecialite:CardiologueAucunpatientn'estsuiviparcemedecin.Matricule:111112Etablissement:McGill";

	personnelsString.erase(
		std::remove_if(personnelsString.begin(), personnelsString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		personnelsString.end());

	tests.push_back(sortieAttenduePersonnels == personnelsString
		&& gestionnairePersonnels.getNbPersonnels() == 4);

	tests.push_back(gestionnairePersonnels.getNbMedecins() == 4
		&& gestionnairePersonnels.getNbMedecinsResidents() == 2);

#else
	tests.push_back(false);
	tests.push_back(false);
#endif

	// Test 5 : tester la classe ConsultationEnLigne, ConsultationPhysique et implicitement Consultation
#if true
	// Tester l 'affichage de la consultation------------------------15------------15-----------------
	ConsultationEnligne consultationEnLigneTest = ConsultationEnligne(medecinResidentTest, patientEtudiantTest, "02/05/2020");
	ConsultationPhysique consultationPhysiqueTest = ConsultationPhysique(medecinTest, patientTest, "02/05/2020");

	std::stringstream consultationStream;
	consultationEnLigneTest.afficher(consultationStream);
	std::string consultationString = consultationStream.str();
	std::cout << consultationString << '\n';
	const std::string sortieAttendueConsultation =
		"Consultation:Type:ConsultationEnligneMedecinResident:MR003PatientEtudiant:PE0002Datedeconsultation:02/05/2020";

	consultationString.erase(
		std::remove_if(consultationString.begin(), consultationString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		consultationString.end());

	std::cout << consultationEnLigneTest.calculerPrix() << " " << consultationPhysiqueTest.calculerPrix();

	tests.push_back(sortieAttendueConsultation == consultationString);

	// Tester le calcul du prix de la consultation avec et sans le rabais (polymorphisme inclus dans le test) ----------------16--------------16---------
	tests.push_back(consultationEnLigneTest.calculerPrix()==40.0 && consultationPhysiqueTest.calculerPrix()==120.0);
#else
	tests.push_back(false);
	tests.push_back(false);
#endif

	// Test 6 : tester la classe Hopital
#if true
	Hopital hopital = Hopital("CHUM", "1051 Rue Sanguinet, Montréal, QC H2X 3E4");

	// Tester le chargement de la base de données------------------------------17-------------17---------------------------
	bool resultatLectureBaseDeDonnees = hopital.chargerBaseDeDonnees("personnels.txt", "patients.txt")
		&& hopital.chargerBaseDeDonnees("personnels.txt", "patients.txt");

	assert(hopital.getGestionnairePersonnels().getNbMedecins() == 4 
		&& hopital.getGestionnairePersonnels().getNbMedecinsResidents() == 2
		&& hopital.getGestionnairePatients().getNbPatients() == 3
		&& resultatLectureBaseDeDonnees); // pas noter car deja enoter dans test 4 => devrait passer

	// Tester l'ajout d'une consultation (operator+=)-----------------------------18--------------18-----------------
	bool testAjoutNonReussi;
	size_t tailleInitialeConsultations = hopital.getConsultations().size();
	Medecin* medecinDansHopital = hopital.getGestionnairePersonnels().getMedecins()[3];
	ConsultationEnligne consultationEnLigneTest2 = ConsultationEnligne(*medecinDansHopital, patientEtudiantTest, "02/05/2020");
	hopital += consultationEnLigneTest2;
	testAjoutNonReussi = medecinDansHopital->getNombreConsultations() == 0
		&& medecinDansHopital->getNombrePatientsAssocies() == 0
		&& hopital.getConsultations().size() == tailleInitialeConsultations;
	
	bool testAjoutReussi;
	tailleInitialeConsultations = hopital.getConsultations().size();
	medecinDansHopital = hopital.getGestionnairePersonnels().getMedecins()[1];
	Patient* patientDansHopital = hopital.getGestionnairePatients().getPatients()[1].get();
	ConsultationEnligne consultationEnLigneTest3 = ConsultationEnligne(*medecinDansHopital, *patientDansHopital, "02/05/2020");
	hopital += consultationEnLigneTest3;
	testAjoutReussi = medecinDansHopital->getNombreConsultations() == 1
		&& medecinDansHopital->getNombrePatientsAssocies() == 1
		&& hopital.getConsultations().size() == 1;

	tests.push_back(testAjoutNonReussi && testAjoutReussi);
#else
	tests.push_back(false);
#endif

	std::vector<float> ponderationTests = { 0.25, 0.25,	0.25,
											0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
											1, 1, 0.5,
											1.5, 1.5,
											0.5, 0.5,
											0.75
	};

	// Affichage
	float totalPoints = 0;
	for (std::size_t i = 0; i < tests.size(); i++)
	{
		std::string output = "Test " + std::to_string(i + 1) + ": ";
		if (tests[i] == true)
		{
			output += "OK!";
			std::stringstream stream;
			stream << ponderationTests[i] << '/' << ponderationTests[i];
			std::cout << std::left << std::setw(15) << std::left << output << stream.str() << '\n';
			totalPoints += ponderationTests[i];
		}
		else
		{
			output += "ECHEC!";
			std::stringstream stream;
			stream << '0' << '/' << ponderationTests[i];
			std::cerr << std::left << std::setw(15) << output << "0/" << ponderationTests[i] << '\n';
		}
	}
	std::stringstream stream;
	stream << totalPoints << "/"
		<< std::accumulate(ponderationTests.begin(), ponderationTests.end(), 0.0f);
	std::cout << std::left << std::setw(16) << "TOTAL: " << stream.str() << '\n';
}
