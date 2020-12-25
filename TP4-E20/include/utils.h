//! Foncteur variés utilisés pour les algorithmes.
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 2020-06-04

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <ctime>

//! Convertir une date string en struct tm
//! \param date    La date en chaine à convertir.
//! \return        La chaine de la date converti en struct tm
static tm convertirStringDate(const std::string& date) {

	const int anneeOrigine = 1900;
	struct tm tm = { 0 };
	int annee;
	int mois;
	int jour;

	sscanf_s(date.c_str(), "%4d-%02d-%02d", &annee, &mois, &jour);

	tm.tm_year = annee - anneeOrigine;
	tm.tm_mon = mois - 1;
	tm.tm_mday = jour;

	return tm;
};

//! Comparer deux dates tm
//! \param1     La premiere date à comparer.
//! \param2     La deuxiéme date à comparer.
//! \return     true si t1 >= t2 false sinon
static bool comparerDate(tm& date1, tm& date2)
{
	time_t t1 = mktime(&date1);
	time_t t2 = mktime(&date2);

	return difftime(t1, t2) > 0;
};

static tm getDateCourante() {
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(now);
	struct tm buf;
	localtime_s(&buf, &start_time);

	return buf;
};


#endif