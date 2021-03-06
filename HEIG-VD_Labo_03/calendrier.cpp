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

                Source pour calcul du jour du 1er Janvier :
                https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html

                Source pour calcul du nombre de jours dans 1 mois :
                http://www.dispersiondesign.com/articles/time/number_of_days_in_a_month

  Compilateur : MinGW-w64
  ---------------------------------------------------------------------------
*/
#include <cstdlib>  // Pour le EXIT_SUCCESS
#include <iostream> // Pour le flux
#include <limits>   // Pour le numeric_limits<streamsize>
#include <iomanip>  // Pour le setw(...)
#include <cmath>	  // Pour le calcul du jour du 1er Janvier -> fonction floor()

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
             MOIS_FIN          =   12;

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

		// Formule pour calculer le jour de la semaine pour le 1er janvier
		// ----------------------------------------------------------------------------
		int anneeSiecle = (annee % 100) - 1 ; // les deux derniers chiffres de l'annee
		int siecle 	    =  annee / 100;  	  // les deux premiers chiffres de l'annee
		int jourSemaine =
			+ (int)floor((2.6 * 11)  - 0.2)
			+ (int)floor(anneeSiecle / 4)
			+ (int)floor(siecle 		 / 4)
			- 2 * siecle + anneeSiecle
			+ 1 ;

		// Un decalage s'opere sur le 1er Janvier puisque le resultat du calcul precedent
		// se base sur une semaine commencant un dimanche
		int jourDepart =
			(jourSemaine % 7) == 0 ?
			(jourSemaine % 7)  + 6 :
			(jourSemaine % 7)  - 1;

		// ----------------------------------------------------------------------------
		// Initalisation de la boucle des calendriers
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
			// On remarque un pattern qui se répète tous les 7 mois, dans lequel se trouve
			// un deuxième pattern se repetant tous les 2 mois. Il ne reste plus qu'a gerer
			// le mois de fevrier et les annees bissextiles. Cela donne le calcul suivant
			int nbreJoursMois = (i == 2) ? (28 + bissextile) : 31 - (i - 1) % 7 % 2;


			// ----------------------------------------------------------------------------
			// Affichage des colonnes avec gestion des espaces
         cout << annee << endl;
         cout << " L  M  M  J  V  S  D" << endl;

         int sautJours = 0;

         while(jourDepart--) {
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

         // On recalcule le jour de départ pour le mois suivant
			jourDepart = sautJours % NBRE_COLONNES;

         // On met un saut de ligne s'il n'y en a pas déjà un
         if (jourDepart) {
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