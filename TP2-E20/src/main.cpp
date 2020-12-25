//! Fonction main qui test le programme
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 07 Mai 2020

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include "Patient.h"
#include "debogageMemoire.h"
#include "GestionnairePatients.h"
#include "Medecin.h"
#include "GestionnaireMedecins.h"
#include "typesafe_enum.h"
#include "Consultation.h"
#include "Hopital.h"

// NOTE: Pour que le programme compile, vous pouvez changer tous les #if true à des #if false,
// et mettre en commentaire tout le code qui a été écrit pour vous. Ainsi, vous pourrez
// graduellement les #if true et tester des petits blocs de code à la fois.

int main()
{
	initDebogageMemoire();

	GestionnaireMedecins gestionnaireMedecins;
	GestionnairePatients gestionnairePatients;
	Patient patientTest = Patient("Simon", "25/10/92", "1000000");
	Medecin medecinTest = Medecin("Tamard", "1000000", Medecin::Specialite::Cardiologue);

	std::vector<bool> tests;

// Test 1 : tester la classe Patient
#if true

	// Tester l'affichage du patient
	std::stringstream patientStream;
	patientStream << patientTest << std::endl;
	std::string patientString = patientStream.str();
	std::cout << patientString << '\n';
	const std::string sortieAttenduePatient =
		"Patient:Simon|Datedenaissance:25/10/92|Numerod'assurancemaladie:1000000";

	patientString.erase(
		std::remove_if(patientString.begin(), patientString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		patientString.end());

	tests.push_back(sortieAttenduePatient == patientString);

	// Tester l'operateur == (dans les deux sens)
	tests.push_back(patientTest == "1000000" && "1000000" == patientTest && !(patientTest == "123456") && !("123456" == patientTest));
#else
	tests.push_back(false);
	tests.push_back(false);
#endif

// Test 2 : tester la classe Medecin
#if true

	// Tester l'affichage du medecin
	std::stringstream medecinStream;
	medecinStream << medecinTest << std::endl;
	std::string medecinString = medecinStream.str();
	std::cout << medecinString << '\n'; 

	std::string sortieAttendueMedecin =
		"Medecin:TamardNumerodelicence:1000000Specialite:CardiologueStatut:ActifAucunpatientn'estsuiviparcemedecin.";

	medecinString.erase(
		std::remove_if(medecinString.begin(), medecinString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		medecinString.end());

	tests.push_back(sortieAttendueMedecin == medecinString);
	
	// Tester l'operateur == (dans les deux sens)
	tests.push_back(medecinTest == "1000000" && "1000000" == medecinTest && !(medecinTest == "123456") && !("123456" == medecinTest));

	// Tester l'operateur += (ajout de patient)
	medecinTest += patientTest;

	medecinStream = std::stringstream();
	medecinStream << medecinTest << std::endl;
	medecinString = medecinStream.str();
	std::cout << medecinString << '\n';

	medecinString.erase(
		std::remove_if(medecinString.begin(), medecinString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		medecinString.end());

	sortieAttendueMedecin =
		"Medecin:TamardNumerodelicence:1000000Specialite:CardiologueStatut:ActifPatientsassocies:"
		"Patient:Simon|Datedenaissance:25/10/92|Numerod'assurancemaladie:1000000";

	tests.push_back(medecinTest.getNombrePatientsAssocies() == 1
		&& medecinTest.getPatientsAssocies().size() == 1
		&& *medecinTest.getPatientsAssocies()[0] == patientTest.getNumeroAssuranceMaladie()
		&& sortieAttendueMedecin == medecinString);

	// Tester l'operateur -= (supression de patient)
	medecinTest -= patientTest.getNumeroAssuranceMaladie();

	medecinStream = std::stringstream();
	medecinStream << medecinTest << std::endl;
	medecinString = medecinStream.str();
	std::cout << medecinString << '\n';

	sortieAttendueMedecin =
		"Medecin:TamardNumerodelicence:1000000Specialite:CardiologueStatut:ActifAucunpatientn'estsuiviparcemedecin.";

	medecinString.erase(
		std::remove_if(medecinString.begin(), medecinString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		medecinString.end());

	tests.push_back(medecinTest.getNombrePatientsAssocies() == 0
		&& medecinTest.getPatientsAssocies().empty()
		&& sortieAttendueMedecin == medecinString);

#else
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
#endif

// Test 3 : tester la classe GestionnairePatients
#if true
	
	// Tester le chargement de fichier
	bool resultatLecturePatients = gestionnairePatients.chargerDepuisFichier("patients.txt") &&
		gestionnairePatients.chargerDepuisFichier("patients.txt");
	tests.push_back(resultatLecturePatients);

	// Tester l 'affichage des patients
	std::stringstream patientsStream;
	patientsStream << gestionnairePatients << std::endl;
	std::string patientsString = patientsStream.str();
	std::cout << patientsString << '\n';
	const std::string sortieAttenduePatients =
		"Patient:JohnLourdes|Datedenaissance:12/12/2001|Numerod'assurancemaladie:louj010304"
		"Patient:GeorgeLucas|Datedenaissance:01/04/1944|Numerod'assurancemaladie:LUCG441212";

	patientsString.erase(
		std::remove_if(patientsString.begin(), patientsString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		patientsString.end());

	tests.push_back(sortieAttenduePatients == patientsString 
		&& gestionnairePatients.getNbPatients() == 2);

	// Tester le constructeur de copie
	GestionnairePatients gestionnairePatientCopieTest1 = GestionnairePatients(gestionnairePatients);
	bool test3Reussi = true;
	for (size_t i = 0; i < gestionnairePatients.getNbPatients(); i++) {
		if (&gestionnairePatients.getPatients()[i] == &gestionnairePatientCopieTest1.getPatients()[i]) {
			test3Reussi = false;
			break;
		}
	}
	tests.push_back(gestionnairePatientCopieTest1.getPatients() != gestionnairePatients.getPatients() 
		&& test3Reussi);
	
	// Tester l'operateur d'affectation
	GestionnairePatients gestionnairePatientCopieTest2;
	gestionnairePatientCopieTest2 = gestionnairePatients;
	bool test4Reussi = true;
	for (size_t i = 0; i < gestionnairePatients.getNbPatients(); i++) {
		if (&gestionnairePatients.getPatients()[i] == &gestionnairePatientCopieTest2.getPatients()[i]) {
			test4Reussi = false;
			break;
		}
	}

	tests.push_back(&gestionnairePatientCopieTest2.getPatients() != &gestionnairePatients.getPatients() && test4Reussi);

	// Tester l'operateur += (ajout de patients)
	bool test5Reussi = true;
	for (auto i = gestionnairePatients.getNbPatients(); i < GestionnairePatients::NB_PATIENT_MAX; i++)
	{
		Patient patient = Patient("Patient" + std::to_string(i), "12/12/2001", "SETT121201" + std::to_string(i));
		bool succes = gestionnairePatients += (patient);
		if (succes == false)
		{
			test5Reussi = false;
			tests.push_back(false);
			break;
		}
	}
	if (test5Reussi == true)
	{
		bool succes = gestionnairePatients += (Patient("", "", ""));
		tests.push_back(!succes);
	}

    // Tester la fonction recherche patient
	Patient* patient = gestionnairePatients.chercherPatient("louj010304");
	Patient* patientInexistant = gestionnairePatients.chercherPatient("qwerty");
	if (patient == nullptr || patientInexistant != nullptr)
		tests.push_back(false);
	else
		tests.push_back(patient->getDateDeNaissance() == "12/12/2001");

#else
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
#endif

// Test 4 : tester la classe GestionnaireMedecins
#if true
	
	// Tester le chargement de fichier
	bool resultatLectureMedecins = gestionnaireMedecins.chargerDepuisFichier("medecins.txt") &&
		gestionnaireMedecins.chargerDepuisFichier("medecins.txt");
	tests.push_back(resultatLectureMedecins);

	// Tester l 'affichage des medecins
	std::stringstream medecinsStream;
	medecinsStream << gestionnaireMedecins << std::endl;
	std::string medecinsString = medecinsStream.str();
	std::cout << medecinsString << '\n';
	const std::string sortieAttendueMedecins =
		"Medecin:LourdesJohnNumerodelicence:tt1234Specialite:CardiologueStatut:ActifAucunpatientn'estsuiviparcemedecin."
		"Medecin:GeorgeLucasNumerodelicence:hhjue2Specialite:DermatologueStatut:ActifAucunpatientn'estsuiviparcemedecin.";

	medecinsString.erase(
		std::remove_if(medecinsString.begin(), medecinsString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		medecinsString.end());

	tests.push_back(sortieAttendueMedecins == medecinsString
		&& gestionnaireMedecins.getNbMedecins() == 2);

	// Tester le constructeur de copie
	GestionnaireMedecins gestionnaireMedecinCopieTest1 = GestionnaireMedecins(gestionnaireMedecins);
	bool test6Reussi = true;
	for (size_t i = 0; i < gestionnaireMedecins.getNbMedecins(); i++) {
		if (&gestionnaireMedecins.getMedecins()[i] == &gestionnaireMedecinCopieTest1.getMedecins()[i]) {
			test6Reussi = false;
			break;
		}
	}
	tests.push_back(gestionnaireMedecinCopieTest1.getMedecins() != gestionnaireMedecins.getMedecins() 
		&& test6Reussi);

	// Tester l'operateur d'affectation
	GestionnaireMedecins gestionnaireMedecinCopieTest2;
	gestionnaireMedecinCopieTest2 = gestionnaireMedecins;
	bool test7Reussi = true;
	for (size_t i = 0; i < gestionnaireMedecins.getNbMedecins(); i++) {
		if (&gestionnaireMedecins.getMedecins()[i] == &gestionnaireMedecinCopieTest2.getMedecins()[i]) {
			test7Reussi = false;
			break;
		}
	}
	tests.push_back(gestionnaireMedecinCopieTest2.getMedecins() != gestionnaireMedecins.getMedecins() 
		&& test7Reussi);

	// Tester l'operateur += (ajout de medecins)
	bool test8Reussi = true;
	for (auto i = 0; i < 4; i++)
	{
		std::size_t tailleAvantAjout = gestionnaireMedecins.getNbMedecins();

		Medecin medecin = Medecin("Medecin" + std::to_string(i), "LOU1258" + std::to_string(i), to_enum<Medecin::Specialite, int>(i % 6));
		gestionnaireMedecins += (medecin);

		std::size_t tailleApresAjout = gestionnaireMedecins.getNbMedecins();

		if (tailleApresAjout != tailleAvantAjout + 1)
		{
			test8Reussi = false;
			break;
		}
	}
	tests.push_back(gestionnaireMedecins.getNbMedecins() == 6 && gestionnaireMedecins.getMedecins().size() == 6 && test8Reussi);

	// Tester l'operateur -= (supprimer medecin)
	bool medecinEstSupprime = gestionnaireMedecins -= ("tt1234");
	bool medecinNonSupprime = gestionnaireMedecins -= ("qwerty");

	if (!medecinEstSupprime || medecinNonSupprime)
		tests.push_back(false);
	else
	{
		Medecin* medecin = gestionnaireMedecins.chercherMedecin("tt1234");
		tests.push_back(medecin != nullptr && !medecin->getEstActif());
	}

	// Tester fonction chercher Medecin
	Medecin* medecinAChercher = gestionnaireMedecins.chercherMedecin("tt1234");
	Medecin* medecinInexistant = gestionnaireMedecins.chercherMedecin("qwerty");
	if (medecinAChercher == nullptr || medecinInexistant != nullptr)
		tests.push_back(false);
	else
		tests.push_back(medecinAChercher->getNom() == "Lourdes John");

#else
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
#endif

// Test 5 : tester la classe Consultation
#if true
	Consultation consultation = Consultation(medecinTest, patientTest, "05/05/2020");
	
	// Tester le constructeur de Consultation
	tests.push_back(medecinTest.chercherPatient(patientTest.getNumeroAssuranceMaladie()) 
		&& *medecinTest.getPatientsAssocies()[0] == patientTest.getNumeroAssuranceMaladie());

	// Tester l 'affichage de la consultation
	std::stringstream consultationStream;
	consultationStream << consultation << std::endl;
	std::string consultationString = consultationStream.str();
	std::cout << consultationString << '\n';
	const std::string sortieAttendueConsultation =
		"Consultation:Medecin:TamardPatient:Simon|Datedenaissance:25/10/92|Numerod'assurancemaladie:1000000Datedeconsultation:05/05/2020";

	consultationString.erase(
		std::remove_if(consultationString.begin(), consultationString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		consultationString.end());

	tests.push_back(sortieAttendueConsultation == consultationString);

#else
	tests.push_back(false);
	tests.push_back(false);
#endif

// Test 6 : tester la classe Hopital
#if true
	Hopital hopital = Hopital("CHUM", "1051 Rue Sanguinet, Montréal, QC H2X 3E4");

	// Tester le chargement de la base de données
	bool resultatLectureBaseDeDonnees = hopital.chargerBaseDeDonnees("medecins.txt", "patients.txt") 
		&& hopital.chargerBaseDeDonnees("medecins.txt", "patients.txt");
	tests.push_back(hopital.getGesionnaireMedecins().getNbMedecins() == 2
		&& hopital.getGestionnairePatients().getNbPatients() == 2 && resultatLectureBaseDeDonnees);

	// Tester l'ajout d'une consultation (operator+=)
	size_t tailleInitialeConsultations = hopital.getConsultations().size();
	Consultation consultationTestEchoue(medecinTest, patientTest, "05/05/2020");
	Medecin* medecinExistant = hopital.getGesionnaireMedecins().chercherMedecin("tt1234");
	Patient* patientExistant = hopital.getGestionnairePatients().chercherPatient("louj010304");
	Consultation consultationTestReussi(*medecinExistant, *patientExistant, "05/05/2020");


	tests.push_back(!(hopital += consultationTestEchoue) && tailleInitialeConsultations == hopital.getConsultations().size()
		&& (hopital += consultationTestReussi) && (tailleInitialeConsultations + 1 == hopital.getConsultations().size()));

	// Tester l'ajout d'un medecin (operator+=)
	size_t tailleInitialeMedecins = hopital.getGesionnaireMedecins().getNbMedecins();
	medecinExistant = hopital.getGesionnaireMedecins().chercherMedecin("tt1234");
	tests.push_back(!(hopital += *medecinExistant) && tailleInitialeMedecins == hopital.getGesionnaireMedecins().getNbMedecins()
		&& (hopital += medecinTest) && (tailleInitialeMedecins + 1 == hopital.getGesionnaireMedecins().getNbMedecins()));

	// Tester l'ajout d'un patient (operator+=)
	size_t tailleInitialePatients = hopital.getGestionnairePatients().getNbPatients();
	patientExistant = hopital.getGestionnairePatients().chercherPatient("louj010304");
	tests.push_back(!(hopital += *patientExistant) && tailleInitialePatients == hopital.getGestionnairePatients().getNbPatients()
		&& (hopital += patientTest) && (tailleInitialePatients + 1 == hopital.getGestionnairePatients().getNbPatients()));
	
#else
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
	tests.push_back(false);
#endif

	std::vector<float> ponderationTests = { 0.25, 1,								// Patient
											0.25, 1, 0.5, 0.5,						// Medecin
											0.25, 0.25, 0.5, 0.5, 0.5, 0.25,		// GestionnairePatients
											0.25, 0.25, 0.5, 0.5, 0.5, 0.5, 0.25,	// GestionnaireMedecins
											0.25, 0.25,								// Consultation
											0.25, 0.25, 0.25, 0.25					// Hopital
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

	// */
	
}
