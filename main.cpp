/*
  ---------------------------------------------------------------------------
  Fichier     : calendrier.cpp
  Nom du labo : Laboratoire 03
  Auteur(s)   : Flavio Sovilla, Nicolas Benitez
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
   // Variables constantes
   const int ESPACE = 3;

   // ----------------------------------------------------------------------------
   // Variables générales
   enum class Mois {
      JANVIER = 1,
      FEVRIER,
      MARS,
      AVRIL,
      MAI,
      JUIN,
      JUILLET,
      AOUT,
      SEPTEMBRE,
      OCTOBRE,
      NOVEMBRE,
      DECEMBRE
   };

   char choixUtilisateur;

   // ----------------------------------------------------------------------------
   //Message de bienvenue
   cout << "ce programme ..." << endl;

   // ----------------------------------------------------------------------------
   //Boucle de recommencement selon entree utilisateur
   do{

      // ----------------------------------------------------------------------------
      // Variable utilisée pour la vérification de l'utilisateur
      int  annee;

      bool verification = true,
           bissextile;

      // ----------------------------------------------------------------------------
      // Saisie de l'utilisateur
      do {
         cout << "entrer une valeur [1900-2100] : ";
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
      cout << endl;

      // ----------------------------------------------------------------------------
      // Vérification de l'année bissextile

      if (annee % 400 == 0 || (annee % 4 == 0 && annee % 100 != 0)) {
         bissextile = true;
      }
      else {
         bissextile = false;
      }

      // ----------------------------------------------------------------------------
      //Initalisation de la boucle des calendriers

      // Variable pour revenir sur le bon jour lors du mois suivant
      int bonJour = 0;

      for (int i = 1; i <= 12; ++i) {
         int nbreJour = 1;
         int nbreJoursMois;

         //TODO: Trop de redondance pour nbreJourMois ???
         switch(i) {
            case (int)Mois::JANVIER:   cout << "Janvier ";
                                       nbreJoursMois = 31;
                                       break;
            case (int)Mois::FEVRIER:   cout << "Fevrier ";
                                       if (bissextile) {
                                          nbreJoursMois = 29;
                                       }
                                       else {
                                          nbreJoursMois = 28;
                                       }
                                       break;
            case (int)Mois::MARS:      cout << "Mars ";
                                       nbreJoursMois = 31;
                                       break;
            case (int)Mois::AVRIL:     cout << "Avril ";
                                       nbreJoursMois = 30;
                                       break;
            case (int)Mois::MAI:       cout << "Mai ";
                                       nbreJoursMois = 31;
                                       break;
            case (int)Mois::JUIN:      cout << "Juin ";
                                       nbreJoursMois = 30;
                                       break;
            case (int)Mois::JUILLET:   cout << "Juillet ";
                                       nbreJoursMois = 31;
                                       break;
            case (int)Mois::AOUT:      cout << "Aout ";
                                       nbreJoursMois = 31;
                                       break;
            case (int)Mois::SEPTEMBRE: cout << "Septembre ";
                                       nbreJoursMois = 30;
                                       break;
            case (int)Mois::OCTOBRE:   cout << "Octobre ";
                                       nbreJoursMois = 31;
                                       break;
            case (int)Mois::NOVEMBRE:  cout << "Novembre ";
                                       nbreJoursMois = 30;
                                       break;
            case (int)Mois::DECEMBRE:  cout << "Decembre ";
                                       nbreJoursMois = 31;
                                       break;
            default: break;
         }

         cout << annee << endl;
         cout << "  L  M  M  J  V  S  D" << endl;
         int sautJours = 0;
         while(bonJour--) {
            cout << setw(ESPACE) << " ";
            ++sautJours;
            if (sautJours % 7 == 0) {
               cout << endl;
            }
         }
         while(nbreJour <= nbreJoursMois){
            cout << setw(ESPACE) << nbreJour;
            ++nbreJour;
            ++sautJours;
            if (sautJours % 7 == 0) {
               cout << endl;
            }
         }
         cout << endl;
         bonJour = sautJours % 7;
         // On met un saut de ligne s'il n'y en a pas déjà un
         if (bonJour) {
            cout << endl;
         }
      }

      //TODO: Mieux gérer la saisie ?
      cout << "Voulez-vous recommencer [O/N] ? ";
      cin  >> choixUtilisateur;

      if (cin.fail()) {
         cin.clear();
         VIDER_BUFFER;
      }

   } while(choixUtilisateur == 'O');

   return EXIT_SUCCESS;
}