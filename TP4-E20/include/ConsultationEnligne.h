//! Class ConsultationEnligne
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef CONSULTATIONENLIGNE_H
#define CONSULTATIONENLIGNE_H

#include <string>
#include "Medecin.h"
#include "Patient.h"
#include "Consultation.h"

class ConsultationEnligne : public Consultation
{
public:
    ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date);

    const double calculerPrix() const override;

    const std::string& getDiagnostique() const;
    double getRabaisConsultationEnLigne() const;

    void setRabaisConsultationEnLigne(double tauxRabais);
    void setDiagnostique(const std::string diagnostique);
    static constexpr double TAUX_RABAIS_CONSULTATION_ENLIGNE = 0.5;

private:
    std::string diagnostique_;
    double rabaisConsultationEnLigne_;
};

#endif // CONSULTATIONENLIGNE_H