#ifndef DEBOGAGEMEMOIRE_H
#define DEBOGAGEMEMOIRE_H

//! Ce fichier permet d'avoir un rapport des fuites de mémoires dans la fenêtre de "sortie" de
//! Visual Studio, lorsque le programme termine son exécution en mode débogage.  Il n'y a pas
//! actuellement de rapport fait si utilisé avec un autre compilateur (i.e. gcc ou clang), mais ce
//! fichier va tout de même compiler et ne rien faire. Il faut appeler "initDebogageMemoire()" au
//! début de l'exécution du programme (début du "main").
//! \note   Ce fichier doit être inclus dans
//! chaque fichier source qui utilise "new", pour avoir les numéros de lignes où se trouvent les
//! "new" qui n'ont pas de "delete" qui correspond.  Il ne fonctionne pas si vous utilisez le
//! "placement new".
//! \author Francois-R.Boyer@PolyMtl.ca
//! \since  2015-04
#ifdef _MSC_VER
// Pour avoir un rapport de fuites incluant les numéros de lignes où l'allocation a été faite.
// (source http://msdn.microsoft.com/en-us/library/x98tx3cf%28v=vs.100%29.aspx)
#define _CRTDBG_MAP_ALLOC ///< Utilise les allocations avec débogage.
#include <crtdbg.h>
#include <stdlib.h>
#define new \
    new (_NORMAL_BLOCK, __FILE__, __LINE__) ///< Ajoute le numéro de ligne au rapport de fuites.

inline void initDebogageMemoire()
{
    _CrtSetDbgFlag(
        0 | _CRTDBG_ALLOC_MEM_DF // Débogage d'allocation mémoire.
        | _CRTDBG_LEAK_CHECK_DF // Rapport de fuites à la sortie du programme.  Noter que le rapport
                                // de fuites sera affiché dans la fenêtre "Sortie" de Visual Studio.
        | _CRTDBG_CHECK_ALWAYS_DF // Vérifie la corruption à chaque new/delete (lent).
    );
}
#else
inline void initDebogageMemoire()
{
    // On a actuellement le débogage mémoire seulement sur MSVC.
}
#endif

#endif