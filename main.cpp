/*
  ---------------------------------------------------------------------------
  Fichier     : calendrier.cpp
  Nom du labo : Laboratoire 03
  Auteur(s)   : Flavio Sovilla
  Date        : 26.10.2020
  But         : Permettre à l'utilisateur d'entrer une date entre 1900
  					 et 2100. Le programme va par la suite ressortir le
  					 calendrier de l'année avec tous les mois et les dates
  					 des différents jours.

  Remarque(s) :

  Compilateur : MinGW-w64
  ---------------------------------------------------------------------------
*/
#include <cstdlib>  // Pour le EXIT_SUCCESS
#include <iostream> // Pour le flux
#include <limits>   // Pour le numeric_limits<streamsize>
#include <iomanip>  // Pour le setw(...) et setprecision(...)

using namespace std;

#define VIDER_BUFFER cin.ignore(numeric_limits<streamsize>::max(),'\n')

int main() {
   // ----------------------------------------------------------------------------
   // Variable utilisée pour la vérification de l'utilisateur

   int  annee;

   bool verification = true,
        bissextile;

   // ----------------------------------------------------------------------------
   // Saisie de l'utilisateur

   cout << "ce programme ..." << endl;
   do {
      cout << "entrer une valeur [1900-2100] :";
      cin >> annee;
      if (cin.fail()) {
         cin.clear();
         VIDER_BUFFER;
      }
      if (annee >= 1900 && annee <= 2100) {
         verification = false;
      }
      else {
         cout << "/!\\ recommencer" << endl;
      }
   } while (verification);

   // ----------------------------------------------------------------------------
   // Vérification de l'année bissextile

   if (annee % 400 == 0 && annee % 4 && annee % 100 != 0) {
      bissextile = true;
   }
   else {
      bissextile = false;
   }

   return EXIT_SUCCESS;
}