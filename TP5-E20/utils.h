//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 2020-06-04

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <ctime>
#include "Medecin.h"
#include <QMetaEnum>
#include <QRegularExpression>

/*
 * Utiliser un namespace nommé utils pour regrouper toutes les fonctions de ce fichier
 * N'oublier pas de changer l'appel de ces fonctions là ou elles sont appelées
*/

namespace utils{

//! Convertir une date string en struct tm
//! \param date    La date en chaine à convertir.
//! \return        La chaine de la date converti en struct tm
inline tm convertirStringDate(const std::string& date) {

    const int anneeOrigine = 1900;
    struct tm tm = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int annee;
    int mois;
    int jour;

    sscanf_s(date.c_str(), "%4d-%02d-%02d", &annee, &mois, &jour);

    tm.tm_year = annee - anneeOrigine;
    tm.tm_mon = mois - 1;
    tm.tm_mday = jour;

    return tm;
};

//! Convertir une date tm en string
//! \param date    La date en tm à convertir.
//! \return        La date convertie en string
inline std::string convertirTmString(const tm& date) {

    const int anneeOrigine = 1900;
    int annee;
    int mois;
    int jour;

    annee = date.tm_year + anneeOrigine ;
    mois = date.tm_mon + 1;
    jour = date.tm_mday;

    std::string stringDate = std::to_string(annee) + "-" + std::to_string(mois) + "-" + std::to_string(jour);

    return stringDate;
};

inline bool validerDate(const std::string& date) {
    QRegularExpression reg("^\\d{4}-(((0)[0-9])|((1)[0-2]))-([0-2][0-9]|(3)[0-1])$");

    QRegularExpressionMatch match = reg.match(QString::fromStdString(date));

    return  match.hasMatch();
};
}
#endif
