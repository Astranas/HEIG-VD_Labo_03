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
	// Variables générales
	enum class Mois {JANVIER, FEVRIER, MARS, AVRIL, MAI, JUIN, JUILLET, AOUT, SEPTEMBRE,
		NOVEMBRE, DECEMBRE};

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

		// ----------------------------------------------------------------------------
		// Vérification de l'année bissextile

		if (annee % 400 == 0 || (annee % 4 == 0 && annee % 100 != 0)) {
			bissextile = true;
		}
		else {
			bissextile = false;
		}

		int nbreJour = 1;
		int mois     = 1;

		//TODO: affecter le nombre de jours du mois en fonction du mois
		int nbreJoursMois;

		//TODO: boucler et afficher calendrier
		/*
		while(nbreJour < nbreJoursMois){

		 nbreJour++;
		}
		*/

		cout << "Voulez-vous recommencer [O/N] ? ";
		cin  >> choixUtilisateur;

		if (cin.fail()) {
			cin.clear();
			VIDER_BUFFER;
		}

	} while(choixUtilisateur == 'O');

	return EXIT_SUCCESS;
}