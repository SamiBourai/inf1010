//! namespace Tests
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "Tests.h"
#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include "Foncteurs.h"
#include "GestionnairePatients.h"
#include "GestionnairePersonnels.h"
#include "Hopital.h"
#include "ConsultationEnligne.h"
#include "ConsultationPhysique.h"
#include "utils.h"
#include <chrono>

namespace
{
    /// Affiche un header pour chaque section de tests à l'écran.
    /// \param nomSectionTest   Le nom de la section de tests.
    void afficherHeaderTest(const std::string& nomSectionTest)
    {
        std::cout << "\nTests pour " + nomSectionTest + ":\n--------\n";
    }

    /// Affiche un footer avec les points pour chaque section de tests à l'écran.
    /// \param totalPoints  Le nombre de points obtenus à la section de tests.
    /// \param maxPoints    Le nombre de points maximal alloués à la section de tests.
    void afficherFooterTest(double totalPoints, double maxPoints)
    {
        std::cout << "--------\nTotal pour la section: " << totalPoints << "/" << maxPoints << '\n';
    }

    /// Affiche le nom d'un test ainsi que son état de passage à l'écran.
    /// \param index        L'index du test.
    /// \param nom          Le nom du test.
    /// \param estReussi    L'état de passage du test.
    void afficherResultatTest(int index, const std::string& nom, bool estReussi)
    {
        static constexpr int largeurNumeroTest = 2;
        static constexpr int largeurNomTest = 50;
        std::cout << "Test " << std::right << std::setw(largeurNumeroTest) << index << ": " << std::left
                  << std::setw(largeurNomTest) << nom << ": " << (estReussi ? "OK" : "FAILED") << '\n';
    }
} // namespace

namespace Tests
{
    /// Appelle tous les tests et affiche la somme de ceux-ci à l'écran.
    void testAll()
    {
        static constexpr double maxPointsAll = 8.0;

        double totalPointsAll = 0.0;
        totalPointsAll += testGestionnairePatients();
        totalPointsAll += testGestionnairePersonnels();
        totalPointsAll += testHopital();

        std::cout << "\nTotal pour tous les tests: " << totalPointsAll << '/' << maxPointsAll << '\n';

        afficherQuestionBonus();
    }

    /// Teste la classe GestionnairePatients.
    /// \return Le nombre de points obtenus aux tests.
    double testGestionnairePatients()
    {
        afficherHeaderTest("GestionnairePatients");
        static constexpr double maxPointsSection = 2;

#if TEST_GESTIONNAIRE_PATIENTS_ACTIF
        std::vector<bool> tests;

        GestionnairePatients gestionnairePatients;

        // Test 1
        gestionnairePatients.chargerDepuisFichier("patients.txt");
        Patient* patientChercheExistant = gestionnairePatients.chercherPatient("P001");
        Patient* patientChercheInExistant = gestionnairePatients.chercherPatient("None");
        tests.push_back(patientChercheExistant && !patientChercheInExistant);
        afficherResultatTest(1, "GestionnairePatients::chercherPatient", tests.back());

        // Test 2
        gestionnairePatients.chargerDepuisFichier("patients.txt");
        size_t nbPatientsInitial1 = gestionnairePatients.getPatients().size();
        Patient patientExistant = Patient("Patient Existant", "2017-20-10", "P001", convertirStringDate("2017-20-10"));
        Patient patientInExistant = Patient("Patient Inexistant", "2017-20-10", "Patient Inexistant ID", convertirStringDate("2017-20-10"));
        PatientEtudiant patientEtudiant = PatientEtudiant("Patient Etudiant", "2017-20-10", "Patient Etudiant Test ID", convertirStringDate("2017-20-10"), "Matricule Test", "Etablissament Test");
        bool ajoutPatientExistant = gestionnairePatients.ajouterPatient<Patient>(patientExistant);
        bool ajoutPatientInexistant = gestionnairePatients.ajouterPatient<Patient>(patientInExistant);
        bool ajoutPatientEtudiantInexistant = gestionnairePatients.ajouterPatient<PatientEtudiant>(patientEtudiant);
        tests.push_back(!ajoutPatientExistant && ajoutPatientInexistant && ajoutPatientEtudiantInexistant && (gestionnairePatients.getPatients().size() == nbPatientsInitial1+2));
        afficherResultatTest(2, "GestionnairePatients::ajouterPatient", tests.back());

        // Test 3
        gestionnairePatients.chargerDepuisFichier("patients.txt");
        size_t nbPatientsInitial2 = gestionnairePatients.getPatients().size();
        bool supprimerPatientExistant = gestionnairePatients.supprimerPatient("P001");
        bool supprimerPatientInExistant = gestionnairePatients.supprimerPatient("None");
        bool supprimerPatientEtudiantExistant = gestionnairePatients.supprimerPatient("PE001");
        tests.push_back((nbPatientsInitial2 - 2 == gestionnairePatients.getPatients().size()) && (supprimerPatientExistant && !supprimerPatientInExistant && supprimerPatientEtudiantExistant));
        afficherResultatTest(3, "GestionnairePatients::supprimerPatient", tests.back());

        // Test 4
        gestionnairePatients.chargerDepuisFichier("patients.txt");
        std::vector<std::shared_ptr<Patient>> patientsEtudiants = gestionnairePatients.getPatientsEtudiants();
        size_t nbPatientsEtudiant = 0;
        for (const auto& patient : gestionnairePatients.getPatients()) {
            if (dynamic_cast<PatientEtudiant*>(patient.get())) {
                nbPatientsEtudiant ++;
            }
        }

        bool sontTousDesPatientsEtudiants = true;
        for (const auto& patient : patientsEtudiants) {
            if (!dynamic_cast<PatientEtudiant*>(patient.get())) {
                sontTousDesPatientsEtudiants = false;
                break;
            }
        }
        tests.push_back(sontTousDesPatientsEtudiants && nbPatientsEtudiant==patientsEtudiants.size());
        afficherResultatTest(4, "GestionnairePatients::getPatientsEtudiants", tests.back());

        int nombreTestsReussis = static_cast<int>(std::count(tests.begin(), tests.end(), true));
        double totalPointsSection =
            static_cast<double>(nombreTestsReussis) / static_cast<double>(tests.size()) * maxPointsSection;
#else
        std::cout << "[Tests désactivés]\n";
        double totalPointsSection = 0.0;
#endif
        afficherFooterTest(totalPointsSection, maxPointsSection);
        return totalPointsSection;
    }

    /// Teste la classe GestionnairePersonnels.
    /// \return Le nombre de points obtenus aux tests.
    double testGestionnairePersonnels()
    {
        afficherHeaderTest("GestionnairePersonnels");
        static constexpr double maxPointsSection = 3;

#if TEST_GESTIONNAIRE_PERSONNELS_ACTIF
        std::vector<bool> tests;

        GestionnairePersonnels gestionnairePersonnels;

        // Test 1
        gestionnairePersonnels.chargerDepuisFichier("personnels.txt");
        Personnel* personnelChercheExistant = gestionnairePersonnels.chercherPersonnel("M001");
        Personnel* personnelChercheInExistant = gestionnairePersonnels.chercherPersonnel("None");
        tests.push_back(personnelChercheExistant && !personnelChercheInExistant);
        afficherResultatTest(1, "GestionnairePersonnels::chercherPersonnel", tests.back());

        // Test 2
        gestionnairePersonnels.chargerDepuisFichier("personnels.txt");
        size_t nbPersonnelsInitial1 = gestionnairePersonnels.getPersonnels().size();
        Medecin medecinExistant = Medecin("Medecin Existant", "M001", Medecin::Specialite::Cardiologue, convertirStringDate("2017-20-10"));
        Medecin medecinInExistant = Medecin("Medecin Inexistant", "Personnel Inexistant ID", Medecin::Specialite::Cardiologue, convertirStringDate("2017-20-10"));
        MedecinResident medecinResident = MedecinResident("Medecin Resident", "2017-20-10", "Matricule", "Etablissament Test", "ID TEST", Medecin::Specialite::Cardiologue, convertirStringDate("2017-20-10"));
        bool ajoutMedecinExistant = gestionnairePersonnels.ajouterPersonnel<Medecin>(medecinExistant);
        bool ajoutMedecinInexistant = gestionnairePersonnels.ajouterPersonnel<Medecin>(medecinInExistant);
        bool ajoutMedecinResidentInexistant = gestionnairePersonnels.ajouterPersonnel<MedecinResident>(medecinResident);
        tests.push_back(!ajoutMedecinExistant && ajoutMedecinInexistant && ajoutMedecinResidentInexistant && (gestionnairePersonnels.getPersonnels().size() == nbPersonnelsInitial1 + 2));
        afficherResultatTest(2, "GestionnairePersonnels::ajouterPersonnel", tests.back());

        // Test 3-4-5
        gestionnairePersonnels.chargerDepuisFichier("personnels.txt");
        std::unordered_map<std::string, Medecin*> personnelsDeTypeMedecin = gestionnairePersonnels.getPersonnelsAvecType<Medecin>();
        std::unordered_map<std::string, MedecinResident*> personnelsDeTypeMedecinResident = gestionnairePersonnels.getPersonnelsAvecType<MedecinResident>();

        size_t nbPersonnelsdeTypeMedecin = 0, nbPersonnelsDeTypeMedecinResident = 0;
        for (const auto& personnel : gestionnairePersonnels.getPersonnels()) {
            if (dynamic_cast<Medecin*>(personnel.second.get())) {
                nbPersonnelsdeTypeMedecin++;
            }
            if (dynamic_cast<MedecinResident*>(personnel.second.get())) {
                nbPersonnelsDeTypeMedecinResident++;
            }
        }

        bool sontTousDesMedecins = true;
        for (const auto& personnel : personnelsDeTypeMedecin) {
            if (!dynamic_cast<Medecin*>(personnel.second)) {
                sontTousDesMedecins = false;
                break;
            }
        }

        bool sontTousDesMedecinsResidents = true;
        for (const auto& personnel : personnelsDeTypeMedecinResident) {
            if (!dynamic_cast<MedecinResident*>(personnel.second)) {
                sontTousDesMedecinsResidents = false;
                break;
            }
        }

        tests.push_back(nbPersonnelsdeTypeMedecin== personnelsDeTypeMedecin.size()
                        && nbPersonnelsDeTypeMedecinResident==personnelsDeTypeMedecinResident.size()
                        && sontTousDesMedecins
                        && sontTousDesMedecinsResidents
                        );
        afficherResultatTest(3, "GestionnairePersonnels::getPersonnelsAvecType", tests.back());
        tests.push_back(gestionnairePersonnels.getNbMedecins() == nbPersonnelsdeTypeMedecin);
        afficherResultatTest(4, "GestionnairePersonnels::getNbMedecins", tests.back());
        tests.push_back(gestionnairePersonnels.getNbMedecinsResidents() == nbPersonnelsDeTypeMedecinResident);
        afficherResultatTest(5, "GestionnairePersonnels::getNbMedecinsResidents", tests.back());

        // Test 6
        gestionnairePersonnels.chargerDepuisFichier("personnels.txt");
        std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> personnelsTries = gestionnairePersonnels.getPersonnelsTriesSuivantSalaireAnnuel();
        bool sontOrdonnes = true;
        for (size_t i = 0; i < personnelsTries.size() - 2; i++) {
            for (size_t j = i + 1; j < personnelsTries.size() - 1; j++) {
                if (personnelsTries[i].second->getSalaireAnnuel() > personnelsTries[j].second->getSalaireAnnuel()) {
                    sontOrdonnes = false;
                    break;
                }
            }
        }
        tests.push_back(sontOrdonnes);
        afficherResultatTest(6, "GestionnairePersonnels::getPersonnelsTriesSuivantSalaireAnnuel", tests.back());

        int nombreTestsReussis = static_cast<int>(std::count(tests.begin(), tests.end(), true));
        double totalPointsSection =
            static_cast<double>(nombreTestsReussis) / static_cast<double>(tests.size()) * maxPointsSection;
#else
        std::cout << "[Tests désactivés]\n";
        double totalPointsSection = 0.0;
#endif
        afficherFooterTest(totalPointsSection, maxPointsSection);
        return totalPointsSection;
    }

    /// Teste la classe Hopital.
    /// \return Le nombre de points obtenus aux tests.
    double testHopital()
    {
        afficherHeaderTest("Hopital");
        static constexpr double maxPointsSection = 3.0;

#if TEST_HOPITAL_ACTIF
        std::vector<bool> tests;
        Hopital hopital = Hopital("CHUM", "1051 Rue Sanguinet, Montréal, QC H2X 3E4");

        // Test 1
        bool resultatLectureBaseDeDonnees = hopital.chargerBaseDeDonnees("personnels.txt", "patients.txt", "consultations.txt")
            && hopital.chargerBaseDeDonnees("personnels.txt", "patients.txt", "consultations.txt");

        tests.push_back(hopital.getGestionnairePersonnels().getNbMedecins() == 50
                        && hopital.getGestionnairePersonnels().getNbMedecinsResidents() == 30
                        && hopital.getGestionnairePatients().getNbPatients() == 50
                        && hopital.getGestionnairePatients().getNbPatientsEtudiants() == 20
                        && hopital.getConsultations().size() == 120
                        && resultatLectureBaseDeDonnees);
        afficherResultatTest(1, "Hopital::chargerBaseDeDonnees", tests.back());

        // Test 2
        hopital.chargerBaseDeDonnees("personnels.txt", "patients.txt", "consultations.txt");
        size_t nbPersonnelsInitial1 = hopital.getGestionnairePersonnels().getPersonnels().size();
        size_t nbMedecinsInitial1 = hopital.getGestionnairePersonnels().getNbMedecins();
        size_t nbMedecinsResidentsInitial1 = hopital.getGestionnairePersonnels().getNbMedecinsResidents();
        Medecin medecinInExistant = Medecin("Medecin Inexistant", "Personnel Inexistant ID", Medecin::Specialite::Cardiologue, convertirStringDate("2017-20-10"));
        MedecinResident medecinResidentInExisant = MedecinResident("Medecin Resident", "2017-20-10", "Matricule", "Etablissament Test", "ID TEST", Medecin::Specialite::Cardiologue, convertirStringDate("2017-20-10"));
       bool ajoutMedecinInExistant = hopital.ajouterPersonnel<Medecin>(medecinInExistant);
        bool ajoutMedecinResidentInExistant = hopital.ajouterPersonnel<MedecinResident>(medecinResidentInExisant);
        bool ajoutMedecinExistant = hopital.ajouterPersonnel<Medecin>(medecinInExistant);
        tests.push_back(ajoutMedecinInExistant && ajoutMedecinResidentInExistant && !ajoutMedecinExistant
                        && (hopital.getGestionnairePersonnels().getPersonnels().size() == nbPersonnelsInitial1 + 2)
                        && (hopital.getGestionnairePersonnels().getNbMedecins()) == nbMedecinsInitial1 + 2
                        && (hopital.getGestionnairePersonnels().getNbMedecinsResidents()) == nbMedecinsResidentsInitial1 + 1);
        afficherResultatTest(2, "Hopital::ajouterPersonnel", tests.back());

        // Test 3
        hopital.chargerBaseDeDonnees("personnels.txt", "patients.txt", "consultations.txt");
        size_t nbPatients1 = hopital.getGestionnairePatients().getPatients().size();
        size_t nbPatientsEtudiants1 = hopital.getGestionnairePatients().getNbPatientsEtudiants();
        Patient patientInExistant = Patient("Patient Inexistant", "2017-20-10", "Patient Inexistant ID", convertirStringDate("2017-20-10"));
        PatientEtudiant patientEtudiantInExistant = PatientEtudiant("Patient Etudiant", "2017-20-10", "Patient Etudiant Test ID", convertirStringDate("2017-20-10"), "Matricule Test", "Etablissament Test");
        bool ajoutPatientInexistant = hopital.ajouterPatient<Patient>(patientInExistant);
        bool ajoutPatientEtudiantInexistant = hopital.ajouterPatient<PatientEtudiant>(patientEtudiantInExistant);
        bool ajoutPatientExistant = hopital.ajouterPatient<Patient>(patientInExistant);
        tests.push_back(ajoutPatientInexistant && ajoutPatientEtudiantInexistant && !ajoutPatientExistant
                        && (hopital.getGestionnairePatients().getPatients().size() == nbPatients1 + 2)
                        && hopital.getGestionnairePatients().getNbPatientsEtudiants() == nbPatientsEtudiants1 + 1);
        afficherResultatTest(3, "Hopital::ajouterPatient", tests.back());

        //Test 4
        hopital.chargerBaseDeDonnees("personnels.txt", "patients.txt", "consultations.txt");
        size_t nbConsultations = hopital.getConsultations().size();
        Patient patient = Patient("Patient", "2017-20-10", "P001", convertirStringDate("2017-20-10"));
        Medecin medecin = Medecin("Medecin", "M001", Medecin::Specialite::Cardiologue, convertirStringDate("2017-20-10"));
        ConsultationEnligne consultationEnligneValide = ConsultationEnligne(medecin, patient, "2020-05-02");
        ConsultationPhysique consultationPhysiqueValide = ConsultationPhysique(medecin, patient, "2020-05-03");
        bool ajoutConsultationEnligneValide = hopital.ajouterConsultation<ConsultationEnligne>(consultationEnligneValide);
        bool ajoutConsultationPhysiqueValide = hopital.ajouterConsultation<ConsultationPhysique>(consultationPhysiqueValide);
        tests.push_back(ajoutConsultationEnligneValide && ajoutConsultationPhysiqueValide
            && (hopital.getConsultations().size() == nbConsultations + 2));
        afficherResultatTest(4, "Hopital::ajouterConsultation", tests.back());

        // Test 5
        hopital.chargerBaseDeDonnees("personnels.txt", "patients.txt", "consultations.txt");
        double periodeMoyennePersonnel = hopital.getAncienneteMoyenneDesPersonnels();

        double periodeMoyenneAttendue = 0;
        for (const auto& personnel : hopital.getGestionnairePersonnels().getPersonnels()) {
            periodeMoyenneAttendue += static_cast<double>(static_cast<double>(getDateCourante().tm_year) - static_cast<double>(personnel.second->getDateAdhesion().tm_year));
        }

        periodeMoyenneAttendue /= static_cast<double>(hopital.getGestionnairePersonnels().getPersonnels().size());

        tests.push_back(periodeMoyenneAttendue == periodeMoyennePersonnel);
        afficherResultatTest(5, "Hopital::getAncienneteMoyenneDesPersonnels", tests.back());

        // Test 6
        hopital.chargerBaseDeDonnees("personnels.txt", "patients.txt", "consultations.txt");
        tm dateInferieure = convertirStringDate("2019-10-01");
        tm dateSuperieure = convertirStringDate("2020-01-30");
        std::vector<std::shared_ptr<Consultation>> consultationsEntreDates = hopital.getCosultationsEntreDates(dateInferieure, dateSuperieure);

        bool sontToutesDansIntervalles = true;
        for (const auto& consultation : consultationsEntreDates) {
            tm dateConsutation = convertirStringDate(consultation->getDate());
            if (!(comparerDate(dateConsutation, dateInferieure) && comparerDate(dateSuperieure, dateConsutation))) {
                sontToutesDansIntervalles = false;
                break;
            }
        }
        tests.push_back(sontToutesDansIntervalles);
        afficherResultatTest(6, "Hopital::getCosultationsEntreDates", tests.back());

        int nombreTestsReussis = static_cast<int>(std::count(tests.begin(), tests.end(), true));
        double totalPointsSection =
            static_cast<double>(nombreTestsReussis) / static_cast<double>(tests.size()) * maxPointsSection;
#else
        std::cout << "[Tests désactivés]\n";
        double totalPointsSection = 0.0;
#endif
        afficherFooterTest(totalPointsSection, maxPointsSection);
        return totalPointsSection;
    }

    /// Affihcher les interpretations pour la question Bonus
    void afficherQuestionBonus()
    {

#if AFFICHER_QUESTION_BONUS
        std::cout << "\n----------------\nQuestion Bonus:\n----------------\n" << std::endl
            << "Expliquez pourquoi il y a une différence remarquable entre la recherche" << std::endl 
            << "de Patient dans GestionnairePatients et la recherche de Personnel dans GestionnairePersonnels" << std::endl 
            << "pourtant les deux ont le même npmbres d'élements = 50 elements" << std::endl
            << "Remarquez bien que dans le test ci-dessous, on est entrain de faire le pire cas: " << std::endl 
            << "la recherche d'un element inexistant donc un parcours de tout le conteneur." << std::endl
            << "Repondez à cette question dans un fichier txt nommé bonus.txt que vous remetteriez avec vos autres fichiers\n" << std::endl;

        GestionnairePersonnels gPersonnels;
        gPersonnels.chargerDepuisFichier("personnels.txt");
        auto startRecherchePersonnel = std::chrono::steady_clock::now();
        gPersonnels.chercherPersonnel("NoNe");
        auto endRecherchePersonnel = std::chrono::steady_clock::now();
        auto diffRecherchePersonnel = endRecherchePersonnel - startRecherchePersonnel;
        std::cout << "La recherche d'un personnel inexistant a durée : " <<std::chrono::duration <double, std::milli>(diffRecherchePersonnel).count() << " ms" << std::endl;

        GestionnairePatients gPatients;
        gPatients.chargerDepuisFichier("patients.txt");
        auto startRecherchePatient = std::chrono::steady_clock::now();
        gPatients.chercherPatient("NoNe");
        auto endRecherchePatient = std::chrono::steady_clock::now();
        auto diffRecherchePatient = endRecherchePatient - startRecherchePatient;
        std::cout << "La recherche d'un patient inexistant a durée : " << std::chrono::duration <double, std::milli>(diffRecherchePatient).count() << " ms" << std::endl;

#endif
    }
} // namespace Tests
