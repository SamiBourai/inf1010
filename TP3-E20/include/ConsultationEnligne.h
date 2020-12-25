#ifndef CONSULTATIONENLIGNE_H
#define CONSULTATIONENLIGNE_H

#include <string>
#include "Consultation.h"
#include"PatientEtudiant.h"

class ConsultationEnligne : public Consultation
{
	
public:
	
	ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date);


	
	const double calculerPrix() const override;
	const double TAUX_RABAIS_CONSULTATION_ENLIGNE = 0.5;

	
	const std::string& getDiagnostique() const;
	double getRabaisConsultationEnligne() const;


	
private:
	std::string diagnostique__;
	double rabaisConsultationEnLigne__;
};
#endif // CONSULTATIONENLIGNE_H