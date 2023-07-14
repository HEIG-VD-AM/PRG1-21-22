/*
Nom du fichier : martins_labo16
But : Implémentation de la méthode de chiffrement asymétrique RSA
Nom : Alexis Martins
Date : 07.11.2021
No. Laboratoire : 16
*/
#include <iostream>
#include <random>
#include <functional>
#include <limits>

using namespace std;

const int32_t VALEUR_MIN = 1; ///Valeur minimum des chiffres entrés
const int32_t VALEUR_MAX = numeric_limits<int32_t>::max(); //Valeur max 2^31 -1
const int32_t NBRE_MESSAGES = 10; //Nombres de messages de tests aléatoires
auto genInt = std::bind(std::uniform_int_distribution<int32_t> //Tirage aléatoire
    (1, VALEUR_MAX), std::mt19937(987));


/// <summary>
/// Génération d'un entier aléatoire entre 2 et la limite des int. 
/// Puis, on applique un modulo de la limite maximum voulue pour avoir
/// un nombre compris dans la plage voulue.
/// </summary>
/// <param name="limiteMax">Limite maximum que peut avoir l'entier</param>
/// <returns>Entier aléatoire généré entre 2 et la limite fournie</returns>
int32_t generationAleatoire(int32_t limiteMax)
{
    /*
    On effectue le modulo ce qui nous donne un chiffre entre 0 et limiteMax - 1
    Puis on y additionne 1 pour que la plage soit entre 1 et limiteMax.
    */
    int32_t nombreAleatoire = genInt() % (limiteMax) + 1;

    return nombreAleatoire;
}

/// <summary>
/// Calcul de l'exponentiation modulaire. 
/// Voir le pseudo-code labo. 15 pour plus d'informations
/// </summary>
/// <param name="base">Première valeur représentant la base du calcul</param>
/// <param name="exposant">Seconde valeur repésentant l'exposant</param>
/// <param name="modulo">Modulo utilisé pour le calcul</param>
/// <returns>Entier contenant le résultat de l'exponentiation</returns>
int32_t expMod(int64_t base, int32_t exposant, int32_t modulo)
{
    //Resultat en 64_t, car il y'a des risques de dépassement pendant le calcul
    int64_t resultat = 1;
   
    while (exposant > 0)
    {     
        if (exposant % 2 == 0)
        {
            base = (base * base) % modulo;
            exposant /= 2;
        }
        else
        {
            resultat = (resultat * base) % modulo;
            exposant--;
        }
    }
    //On le convertit en 32_t, le résultat final ne dépassera pas cette valeur
    return (int32_t) resultat;
}

/// <summary>
/// Test de primalité, afin de vérifier si un nombre est probablement premier.
/// Voir le pseudo-code du labo. 16 pour plus d'informations sur ce test.
/// </summary>
/// <param name="nombrePremier">Nombre testé par le test de primalité</param>
/// <returns>Retourne vrai, si le nombre entré est premier. 
/// Sinon retourne faux</returns>
bool estPremier(int32_t nombrePremier)
{
    //Si le nombre est plus petit que 2, il n'est pas premier
    if (nombrePremier < 2)
    {
        return false;
    }

    //Si le nombre est égal à 2, il est forcément premier
    if (nombrePremier == 2)
    {
        return true;
    }

    int32_t nombreAleatoire;

    for (int i = 0; i < 10; i++)
    {
        //Génération du nombre aléatoire entre 2 et le nombre premier testé
        nombreAleatoire = generationAleatoire(nombrePremier - 1);

        /*
        On vérifie que a^(p - 1) mod p soit différent de 1, si
        c'est le cas il n'est pas premier.
        */
        if (expMod(nombreAleatoire, nombrePremier - 1, nombrePremier) != 1)
        {
            return false;
        }

        int32_t expModQ = 1;
        int32_t exposantU = nombrePremier - 1;

        while (exposantU % 2 == 0 && expModQ == 1)
        {
            exposantU /= 2;
            expModQ = expMod(nombreAleatoire, exposantU, nombrePremier);

            if (expModQ != 1 && expModQ != nombrePremier - 1)
            {
                return false;
            }
        }
    }

    /*
    Si aucune des vérifications ci-dessus n'a abouti,
    le nombre est potentiellement premier
    */
    return true;
}

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
int32_t euclideEtendu(int32_t termeA, int32_t termeB, int32_t& moduloInverse)
{
    int32_t r = termeA;
    int32_t rPrime = termeB;
    int32_t d = 0;
    int32_t dPrime = 1;
    int32_t q;
    int32_t rs;
    int32_t ds;

    while (rPrime != 0)
    {
        q = (int32_t) floor(r / rPrime);
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
    moduloInverse = d;

    //PGDC retourné ici en tant que retour de la fonction
    return r;
}

/// <summary>
/// Méthode qui permet de faire toutes les étapes du chiffrements 
/// au déchiffrement des messages (calculs et affichages),
/// et vérifie que le message initial soit équivalent au message decrypté
/// </summary>
/// <param name="message">Message que l'on souhait (dé)chiffré</param>
/// <param name="clePubliqueE">Première partie de la clé publique</param>
/// <param name="clePubliqueN">Seconde partie de la clé publique</param>
/// <param name="clePriveeD">Clé privée pour le déchiffrement</param>
void chiffrementEtDechiffremenet(int32_t message, int32_t clePubliqueE, int32_t clePubliqueN, int32_t clePriveeD)
{
    //Chiffrement du message de Bob avec la clé publique d'Alice
    int32_t messageCrypte = expMod(message, clePubliqueE, clePubliqueN);
    cout << "Message crypte : " << messageCrypte << endl;

    //Déchiffrement du message avec la clé privée d'Alice
    int32_t messageDecrypte = expMod(messageCrypte, clePriveeD, clePubliqueN);
    cout << "Message decrypte : " << messageDecrypte << endl;


    //Vérifie que le message entrée est équivalent au message decrypté
    if (message == messageDecrypte)
    {
        cout << "Test reussi !" << endl << endl;
    }
    else
    {
        cout << "Test echoue !" << endl << endl;
    }
}

/// <summary>
/// Fonction qui génère 10 messages aléatoirement afin de 
/// tester le fonctionnement du chiffrement
/// </summary>
/// <param name="clePubliqueE">Première partie de la clé publique</param>
/// <param name="clePubliqueN">Deuxième partie de la clé publique</param>
/// <param name="clePriveeD">Clé privée servant au déchiffrement</param>
void messagesTest(int32_t clePubliqueE, int32_t clePubliqueN, int32_t clePriveeD)
{
    int32_t message;

    cout << "Generation des messages aleatoires : " << endl;

    for (int i = 1; i <= NBRE_MESSAGES; i++)
    {
        cout << "TEST " << i << endl;

        //Génération du message
        message = generationAleatoire(clePubliqueN - 1);
        cout << "Message de Bob : " << message << endl;

        chiffrementEtDechiffremenet(message, clePubliqueE, clePubliqueN, 
        clePriveeD);
    }
}

/// <summary>
/// Vérifie que l'entrée utilisateur soit une entier
/// </summary>
/// <param name="entreeAVerifier">Entrée de l'utilisateur</param>
void verificationEntreeNumerique(int32_t& entreeAVerifier)
{
    if (!(cin >> entreeAVerifier)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main()
{
    int32_t nombrePremierP;
    int32_t nombrePremierQ;

    /*
    L'utilisateur entre deux nombres premiers P et Q.
    Vérification que ceux-ci sont premiers et qu'ils ne sont pas trop grands
    */
    do
    {
        cout << "Entrer un nombre premier P : ";
        verificationEntreeNumerique(nombrePremierP);

        cout << "Entrer un nombre premier Q different de P : ";
        verificationEntreeNumerique(nombrePremierQ);

    /*
    Utilisation d'une division pour éviter le dépassement des int 
    lorsqu'on vérifie que p*q < 2^31  - 1
    */
    } while (nombrePremierP == nombrePremierQ || nombrePremierP < VALEUR_MIN 
             || nombrePremierQ < VALEUR_MIN 
             || nombrePremierP >= VALEUR_MAX / nombrePremierQ 
             || !estPremier(nombrePremierP) || !estPremier(nombrePremierQ));

    //Calcul de phi qui permettra de calculer la clé secrète
    int32_t phi = (nombrePremierP - 1) * (nombrePremierQ - 1);
    int32_t clePubliqueE;
    int32_t clePriveeD;

    /*
    L'utilisateur entre un nombre E qui est une partie de la clé publique, 
    on vérifie que la valeur est première avec P et Q (PGDC = 1) 
    et qu'elle n'est pas trop grande
    */
    do
    {
        cout << "Entrer un nombre qui est premier avec " << phi << " et "
             << "plus petit que cette meme valeur : ";

        verificationEntreeNumerique(clePubliqueE);

    } while (clePubliqueE >= phi || clePubliqueE < VALEUR_MIN 
             || clePubliqueE >= VALEUR_MAX 
             || euclideEtendu(phi, clePubliqueE, clePriveeD) != 1);

    //Calcul de la seconde partie de la clé publique.
    int32_t clePubliqueN = nombrePremierP * nombrePremierQ;

    //Affichage de la paire E et N formant la clé publique d'Alice
    cout << endl << "Cle publique d'Alice : e = " << clePubliqueE << " n = " 
         << clePubliqueN << endl;
     
    //On affiche la clé privée d'Alice calculée dans Euclide etendu
    cout << "Cle secrete : " << clePriveeD << endl << endl;

    int32_t messageManuel;
    
    //Entrée d'un message manuellement par l'utilisateur entre 1 et N - 1
    do
    {
        cout << "Message de Bob plus petit que " << clePubliqueN << " : ";
        verificationEntreeNumerique(messageManuel);

    } while (messageManuel < VALEUR_MIN || messageManuel > clePubliqueN - 1);


    chiffrementEtDechiffremenet(messageManuel, clePubliqueE, clePubliqueN, 
    clePriveeD);

    //Génération automatique des messages exemples pour faire une vérification
    messagesTest(clePubliqueE, clePubliqueN, clePriveeD);
}