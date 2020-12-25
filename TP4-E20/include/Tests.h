//! namespace Tests
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef TESTS_H
#define TESTS_H

#define TEST_GESTIONNAIRE_PATIENTS_ACTIF true
#define TEST_GESTIONNAIRE_PERSONNELS_ACTIF true
#define TEST_HOPITAL_ACTIF true
#define AFFICHER_QUESTION_BONUS true

namespace Tests
{
    void testAll();
    double testGestionnairePatients();
    double testGestionnairePersonnels();
    double testHopital();
    void afficherQuestionBonus();
} // namespace Tests

#endif // TESTS_H
