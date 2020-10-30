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

  Remarque(s) : Les valeurs de verifications d'une annee bissextile ont ete laissees
                en dur dans le code puisqu'elles proviennent d'une formule.

  Compilateur : MinGW-w64
  ---------------------------------------------------------------------------
*/
#include <cstdlib>  // Pour le EXIT_SUCCESS
#include <iostream> // Pour le flux
#include <limits>   // Pour le numeric_limits<streamsize>
#include <iomanip>  // Pour le setw(...)

using namespace std;

#define VIDER_BUFFER cin.ignore(numeric_limits<streamsize>::max(),'\n')

int main() {

   // ----------------------------------------------------------------------------
   // Variables constantes
   const int ESPACE_JOURS      =    2,
             ESPACE_ALIGNEMENT =    3,
             NBRE_COLONNES     =    7,
             ANNEE_MIN         = 1900,
             ANNEE_MAX         = 2100,
             MOIS_DEPART       =    1,
             MOIS_FIN          =   12,
             MOIS_LONG         =   31,
             MOIS_COURT        =   30,
             MOIS_FEVRIER      =   28,
             MOIS_FEVRIER_BIS  =   29;

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
   // Message de bienvenue
   cout << "ce programme ..." << endl;

   // ----------------------------------------------------------------------------
   // Boucle de recommencement selon entree utilisateur
   do{

      // ----------------------------------------------------------------------------
      // Variables utilisées pour gérer l'entree de l'utilisateur
      int  annee;

      bool verifAnnee = true,
           bissextile = true;

      // ----------------------------------------------------------------------------
      // Saisie de l'année par l'utilisateur
      do {
         cout << "entrer une valeur [" << ANNEE_MIN << "-" << ANNEE_MAX << "] : ";
         cin >> annee;

         if (cin.fail()) {
            cin.clear();
         }
			VIDER_BUFFER;

         if (annee >= ANNEE_MIN && annee <= ANNEE_MAX) {
				verifAnnee = false;
         }
         else {
            cout << "/!\\ recommencer" << endl;
         }
      } while (verifAnnee);
      cout << endl;

      // ----------------------------------------------------------------------------
      // Vérification de l'année bissextile
		// Ne pas modifier les valeurs (voir remarques) !
		bissextile = (annee % 400 == 0 || (annee % 4 == 0 && annee % 100 != 0));

      // ----------------------------------------------------------------------------
      // Initalisation de la boucle des calendriers

      // Variable pour revenir sur le bon jour lors du mois suivant
      int bonJour = 0;

      for (int i = MOIS_DEPART; i <= MOIS_FIN; ++i) {
         int nbreJour = 1;

         switch(i) {
            case (int)Mois::JANVIER:   cout << "JANVIER ";
                                       break;
            case (int)Mois::FEVRIER:   cout << "FEVRIER ";
                                       break;
            case (int)Mois::MARS:      cout << "MARS ";
                                       break;
            case (int)Mois::AVRIL:     cout << "AVRIL ";
                                       break;
            case (int)Mois::MAI:       cout << "MAI ";
                                       break;
            case (int)Mois::JUIN:      cout << "JUIN ";
                                       break;
            case (int)Mois::JUILLET:   cout << "JUILLET ";
                                       break;
            case (int)Mois::AOUT:      cout << "AOUT ";
                                       break;
            case (int)Mois::SEPTEMBRE: cout << "SEPTEMBRE ";
                                       break;
            case (int)Mois::OCTOBRE:   cout << "OCTOBRE ";
                                       break;
            case (int)Mois::NOVEMBRE:  cout << "NOVEMBRE ";
                                       break;
            case (int)Mois::DECEMBRE:  cout << "DECEMBRE ";
                                       break;
            default: break;
         }

			// ----------------------------------------------------------------------------
			// Calcul du nombre de jour d'un mois
			// - Les valeurs 2 et 8 correspondent aux expections des mois de Février
			//   et Aout.
			int nbreJoursMois;

			if(i % 2 == 0){
         	if(i == 2){
					if (bissextile) {
						nbreJoursMois = MOIS_FEVRIER_BIS;
					}
					else {
						nbreJoursMois = MOIS_FEVRIER;
					}
         	} else if(i == 8){
					nbreJoursMois = MOIS_LONG;
         	} else {
					nbreJoursMois = MOIS_COURT;
         	}
         } else {
				nbreJoursMois = MOIS_LONG;
         }

			// ----------------------------------------------------------------------------
			// Affichage des colonnes avec gestion des espaces
         cout << annee << endl;
         cout << " L  M  M  J  V  S  D" << endl;

         int sautJours = 0;

         while(bonJour--) {
            cout << setw(ESPACE_ALIGNEMENT) << " ";

            ++sautJours;

            if (sautJours % NBRE_COLONNES == 0) {
               cout << endl;
            }
         }

			// ----------------------------------------------------------------------------
			// Affichage des jours du mois
         while(nbreJour <= nbreJoursMois){
            cout << setw(ESPACE_JOURS) << nbreJour << " ";

            ++nbreJour;
            ++sautJours;

            if (sautJours % NBRE_COLONNES == 0) {
               cout << endl;
            }
         }
         cout << endl;
         bonJour = sautJours % NBRE_COLONNES;

         // On met un saut de ligne s'il n'y en a pas déjà un
         if (bonJour) {
            cout << endl;
         }
      }

		// ----------------------------------------------------------------------------
		// Invitation à recommencer avec gestion de l'entree utilisateur
      do{
			cout << "Voulez-vous recommencer [O/N] ? ";
			cin  >> choixUtilisateur;

			if (cin.fail()) {
				cin.clear();
			}
			VIDER_BUFFER;
		}while(choixUtilisateur != 'N' && choixUtilisateur != 'O');

   } while(choixUtilisateur == 'O');

   return EXIT_SUCCESS;
}