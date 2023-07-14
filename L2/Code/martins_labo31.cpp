/*
Nom du fichier : Sint.cpp
But : Main du programme qui permet de générer des clés RSA.
      Ces deux clés sont générés à partir des nombres P, Q et E 
      dont l'utilisateur choisi la longueur.
      Utilisation de la classe Uint et Sint pour avoir des entiers longs.
Nom : Alexis Martins
Date : 15.01.2022
No. Laboratoire : 31
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <functional>
#include <limits>
#include "Sint.hpp"
#include "Uint.hpp"
using namespace std;

const uint64_t VALEUR_MIN = 1;
const uint64_t VALEUR_MAX = std::numeric_limits<uint64_t>::max();
auto genInt = std::bind(std::uniform_int_distribution<uint64_t>
    (VALEUR_MIN, VALEUR_MAX), std::mt19937(987));

/// <summary>
/// Algoritme d'Euclide étendu permettant de calculer le modulo inverse
/// de deux termes. Ce paramètre est passé par référence pour le récupérer
/// dans la suite du code 
/// Ainsi que leur PGDC qui est donné dans le retour pour 
/// pouvoir utiliser la méthode dans une condition directement
/// Voir le pseudo-code du labo. 16 pour plus d'informations sur l'algorithme
/// </summary>
/// <param name="termeA">Premier terme</param>
/// <param name="termeB">Second terme</param>
/// <param name="moduloInverse">Modulo inverse des 
/// deux termes en parametres</param>
/// <returns>Retourne le PGDC des deux nombres</returns>
Uint euclideEtendu(const Uint& termeA, const Uint& termeB, Uint& moduloInverse)
{
    Sint r = termeA;
    Sint rPrime = termeB;
    Sint d = 0;
    Sint dPrime = 1;
    Sint q;
    Sint rs;
    Sint ds;

    while (rPrime != 0)
    {
        q = r / rPrime;
        rs = r;
        ds = d;
        r = rPrime;
        d = dPrime;
        rPrime = rs - q * rPrime;
        dPrime = ds - q * dPrime;
    }

    if (d < 0)
    {
        d += termeA;
    }

    //Modulo inverse retourné ici par référence
    moduloInverse = d.abs();

    //PGDC retourné ici en tant que retour de la fonction
    return r.abs();
}

/// <summary>
/// Génération d'une nombre aléatoire avec un nombre de chiffres donnés
/// </summary>
/// <param name="nbreChiffres">Nombre de chiffres du nombre</param>
/// <returns>Nombre aléatoire au format Uint</returns>
Uint generationAleatoire(const uint64_t& nbreChiffres)
{
    std::string nombre;
    uint64_t nombreAleatoire;

    //Génére un chiffre aléatoire par case du nombre à générer
    for (size_t i = 0; i < nbreChiffres; i++)
    {
        //On vérifie que le premier nombre soit différent de 0
        do
        {
            nombreAleatoire = genInt() % BASE;
        } while (i == 0 && nombreAleatoire == 0);
        nombre += std::to_string(nombreAleatoire);
    }

    return nombre;
}

/// <summary>
/// Test de primalité, afin de vérifier si un nombre est probablement premier.
/// Voir le pseudo-code du labo. 16 pour plus d'informations sur ce test.
/// </summary>
/// <param name="nombrePremier">Nombre testé par le test de primalité</param>
/// <returns>Retourne vrai, si le nombre entré est premier. 
/// Sinon retourne faux</returns>
bool estPremier(const Uint& nombrePremier)
{
    //Si le nombre est plus petit que 2, il n'est pas premier
    if (nombrePremier < 2 || nombrePremier.estPair())
    {
        return false;
    }

    //Si le nombre est égal à 2, il est forcément premier
    if (nombrePremier == 2)
    {
        return true;
    }

    Uint nombreAleatoire;

    for (int i = 0; i < 10; i++)
    {
        //Génération du nombre aléatoire entre 2 et le nombre premier testé
        nombreAleatoire = (generationAleatoire((uint64_t)nombrePremier.getterTaille()) 
                          % nombrePremier) + 1;

        if (mod_pow(nombreAleatoire, nombrePremier - 1, nombrePremier) != 1)
        {
            return false;
        }

        Uint expModQ = 1;
        Uint exposantU = nombrePremier - 1;

        while (exposantU.estPair() && expModQ == 1)
        {
            exposantU /= 2;
            expModQ = mod_pow(nombreAleatoire, exposantU, nombrePremier);

            if (expModQ != 1 && expModQ != nombrePremier - 1)
            {
                return false;
            }
        }
    }

    return true;
}

/// <summary>
/// Génère des Uint premiers et aléatoires
/// </summary>
/// <param name="nbreChiffres">Nombre de chiffres voulus dans le Uint</param>
/// <returns>Uint aléatoire et premier/returns>
Uint GenererNombrePremier(const uint64_t& nbreChiffres)
{
    Uint p;
    do
    {
        p = generationAleatoire(nbreChiffres); // Vérification gen_random
    } while (!estPremier(p));  // Vérification exponentiation modulaire, prime

    return p;
}

/// <summary>
/// Vérifie que l'entrée utilisateur soit une entier
/// </summary>
/// <param name="entreeAVerifier">Entrée de l'utilisateur</param>
void verificationEntreeNumerique(uint64_t& entreeAVerifier)
{
    if (!(cin >> entreeAVerifier)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main()
{
    Uint nombrePremierP;
    Uint nombrePremierQ;
    uint64_t nbreChiffres;

    //Vérifie que l'utilisateur rentre un nombre correct (> 0)
    do
    {
        cout << "Entrez le nombre de chiffres qu'auront vos nombres"
            " P et Q (> 0) : ";
        verificationEntreeNumerique(nbreChiffres);

        if (nbreChiffres <= 0)
        {
            cout << "Saisie incorrecte : Entrez un nombre strictement"
                " positif et non nul" << endl;
        }
    } while (nbreChiffres <= 0);

    /*
    L'utilisateur entre deux nombres premiers P et Q.
    Vérification que ceux-ci sont premiers et qu'ils ne sont pas trop grands
    */
    do
    {
        nombrePremierP = GenererNombrePremier(nbreChiffres);

        nombrePremierQ = GenererNombrePremier(nbreChiffres);

        /*
        Utilisation d'une division pour éviter le dépassement des int
        lorsqu'on vérifie que p*q < 2^31  - 1
        */
    } while (nombrePremierP == nombrePremierQ || nombrePremierP < VALEUR_MIN
        || nombrePremierQ < VALEUR_MIN);

    //Calcul de phi qui permettra de calculer la clé secrète
    Uint phi = (nombrePremierP - 1) * (nombrePremierQ - 1);
    Uint clePubliqueE;
    Uint clePriveeD;

    /*
    L'utilisateur entre un nombre E qui est une partie de la clé publique,
    on vérifie que la valeur est première avec P et Q (PGDC = 1)
    et qu'elle n'est pas trop grande
    */
    do
    {
        clePubliqueE = GenererNombrePremier(nbreChiffres);

    } while (clePubliqueE >= phi || clePubliqueE < VALEUR_MIN
        || euclideEtendu(phi, clePubliqueE, clePriveeD) != 1);

    //Calcul de la seconde partie de la clé publique.
    Uint clePubliqueN = nombrePremierP * nombrePremierQ;

    //Affichage de la paire E et N formant la clé publique d'Alice
    cout << endl << "Cle publique d'Alice : e = " << clePubliqueE << " n = "
        << clePubliqueN << endl;

    //On affiche la clé privée d'Alice calculée dans Euclide etendu
    cout << "Cle secrete : " << clePriveeD << endl << endl;
}

