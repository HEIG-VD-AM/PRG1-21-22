/*
Nom du fichier : Uint.hpp
But : Fichier header de la classe Uint
Nom : Alexis Martins
Date : 15.12.2021
No. Laboratoire : 31
*/
#ifndef UINT_HPP
#define UINT_HPP

#include <vector>
#include <string>

const uint64_t BASE = 10;   //Base dans laquelle sont exprimées les nombres
const uint64_t ZERO = 48;   //Code du caractère ASCII '0'

class Uint
{
    //MUD = Membre Uint de droite
    //MUG = Membre Uint de gauche

    std::vector<uint64_t> nombre;    //Nombre représenté par le Uint

    /// <summary>
    /// Gère le report de la retenu de la case actuelle à la case suivante
    /// </summary>
    void report();

    /// <summary>
    /// Permet de supprimer les éventuelles zéros en trop, notamment lors
    /// des entrées utilisateurs et des opérations (soustraction)
    /// </summary>
    void enleverZeros();

    /// <summary>
    /// Vérifie si le nombre Uint est un zéro
    /// </summary>
    /// <returns>Vrai si le Uint est égal à 0</returns>
    bool egalZero();

    /// <summary>
    /// Vérifie si lors d'opération telle que la division 
    /// le diviseur n'est pas égal à 0
    /// Surcharge prenant un Uint en paramètres
    /// </summary>
    void verifierZero(Uint diviseur);

    /// <summary>
    /// Vérifie si lors d'opération telle que la division 
    /// le diviseur n'est pas égal à 0
    /// Surcharge prenant un uint64_t en paramètres
    /// </summary>
    void verifierZero(uint64_t diviseur);

    /// <summary>
    /// Méthode retournant le résultat d'une division, ainsi que son reste
    /// Voir pseudo-code laboratoire 30 pour plus d'informations
    /// </summary>
    /// <param name="dividende">Uint utilisé comme dividende</param>
    /// <param name="diviseur">Uint utilisé commme diviseur</param>
    /// <param name="reste">Reste de la division</param>
    /// <returns></returns>
    Uint divisionReste(const Uint& dividende, const Uint& diviseur, 
                       Uint& reste);

    /// <summary>
    /// Permet de comparer la valeurs de deux Uint (Plus petit, grand ou égal)
    /// </summary>
    /// <param name="mug">Première valeur de comparaison</param>
    /// <param name="mud">Seconde valeur de comparaison</param>
    /// <returns>-1 si A < B, 0 si A = B et 1 si A > B</returns>
    friend int comp(const Uint& mug, const Uint& mud);

    /// <summary>
    /// Surcharge de l'opérateur '+', en réutilisant 
    /// l'opérateur '+=' pour deux Uints
    /// </summary>
    /// <param name="mug">Premier nombre de l'opération</param>
    /// <param name="mud">Second nombre de l'opération</param>
    /// <returns>Addition des deux Uints</returns>
    friend Uint operator+(Uint mug, const Uint& mud);

    /// <summary>
    /// Surcharge de l'opérateur '-', en réutilisant 
    /// l'opérateur '-=' pour deux Uints
    /// </summary>
    /// <param name="mug">Premier nombre de l'opération</param>
    /// <param name="mud">Second nombre de l'opération</param>
    /// <returns>Soustraction des deux Uints</returns>
    friend Uint operator-(Uint mug, const Uint& mud);

    /// <summary>
    /// Surcharge de l'opérateur '*', en réutilisant 
    /// l'opérateur '*=' pour deux Uints
    /// </summary>
    /// <param name="mug">Premier nombre de l'opération</param>
    /// <param name="mud">Second nombre de l'opération</param>
    /// <returns>Multiplication des deux Uints</returns>
    friend Uint operator*(Uint mug, const Uint& mud);

    /// <summary>
    /// Surcharge de l'opérateur '*', en réutilisant 
    /// l'opérateur '*=' pour un Uint et un scalaire
    /// </summary>
    /// <param name="mug">Premier nombre de l'opération</param>
    /// <param name="multiple">Scalaire</param>
    /// <returns>Multiplications de l'Uint et du scalaire</returns>
    friend Uint operator*(Uint mug, const uint64_t& multiple);

    /// <summary>
    /// Surcharge de l'opérateur '*', en réutilisant 
    /// l'opérateur '*=' pour un Uint et un scalaire (autre sens)
    /// </summary>
    /// <param name="multiple">Scalaire</param>
    /// <param name="mug">Premier nombre de l'opération</param>
    /// <returns>Multiplications de l'Uint et du scalaire</returns>
    friend Uint operator*(const uint64_t& multiple, Uint mug);

    /// <summary>
    /// Surcharge de l'opérateur '/', en réutilisant 
    /// l'opérateur '/=' pour deux Uint
    /// </summary>
    /// <param name="mug">Premier nombre de l'opération</param>
    /// <param name="diviseur">Second nombre Uint</param>
    /// <returns>Divison de l'Uint par le second</returns>
    friend Uint operator/(Uint mug, const uint64_t& diviseur);

    /// <summary>
    /// Surcharge de l'opérateur '%', en réutilisant 
    /// l'opérateur '%=' pour deux Uint
    /// </summary>
    /// <param name="mug">Premier nombre de l'opération</param>
    /// <param name="diviseur"Second nombre Uint</param>
    /// <returns>Reste de la division</returns>
    friend Uint operator%(Uint mug, const uint64_t& diviseur);

    /// <summary>
    /// Surcharge de l'opérateur '/', en réutilisant 
    /// l'opérateur '%='avec un scalaire
    /// </summary>
    /// <param name="mug">Premier nombre de l'opération</param>
    /// <param name="diviseur">Nombre diviseur de notre Uint</param>
    /// <returns>Divison de l'Uint par un nombre entier</returns>
    friend Uint operator/(Uint mug, const Uint& diviseur);

    /// <summary>
    /// Surcharge de l'opérateur '%', en réutilisant 
    /// l'opérateur '%=' avec un scalaire
    /// </summary>
    /// <param name="mug">Premier nombre de l'opération</param>
    /// <param name="diviseur">Nombre diviseur de notre Uint</param>
    /// <returns>Reste de la division</returns>
    friend Uint operator%(Uint mug, const Uint& diviseur);

    /// <summary>
    /// Permet d'afficher les informations de nos Uints
    /// </summary>
    /// <param name="flux">Référence au flux de sortie</param>
    /// <param name="mug">Uint à afficher</param>
    /// <returns>Nouveau flux</returns>
    friend std::ostream& operator<<(std::ostream& lhs, const Uint& mug);

    /// <summary>
    /// Permet de d'écrire depuis un flux dans un Uint
    /// </summary>
    /// <param name="is">Référence au flux d'entrée</param>
    /// <param name="mug">Uint vers lequel est dirigé le flux</param>
    /// <returns>Nouveau flux</returns>
    friend std::istream& operator>>(std::istream& lhs, Uint& mug);

    /// <summary>
    /// Calcul de l'exponentiation modulaire. 
    /// Voir le pseudo-code labo. 15 pour plus d'informations
    /// Nom en snake casee, car le programme rsa.cpp utilisait 
    /// l'expMod avec le nom mod_pow. Je me suis adapté au rsa.cpp
    /// </summary>
    /// <param name="base">Première valeur représentant la base 
    /// du calcul</param>
    /// <param name="exposant">Seconde valeur repésentant l'exposant</param>
    /// <param name="modulo">Modulo utilisé pour le calcul</param>
    /// <returns>Entier contenant le résultat de l'exponentiation</returns>
    friend Uint mod_pow(Uint base, Uint exposant, const Uint& modulo);

    /// <summary>
    /// Classe Sint
    /// </summary>
    friend class Sint;

public:

    /// <summary>
    /// Constructeur vide de la classe Uint
    /// </summary>
    Uint() {};

    /// <summary>
    /// Constructeur de la classe Uint à partir d'une string
    /// </summary>
    /// <param name="texte">Nombre à stocker dans dans l'Uint</param>
    Uint(const std::string& texte);

    /// <summary>
    /// Constructeur de la classe Uint à partir d'un uint64_t
    /// </summary>
    /// <param name="nombre">uint64_t</param>
    Uint(const uint64_t& nombre) { *this = std::to_string(nombre); };

    /// <summary>
    /// Permet d'obtenir le nombre de chiffres d'un Uint
    /// </summary>
    /// <returns>Nombre de chiffres</returns>
    size_t getterTaille() const;

    /// <summary>
    /// Défini si un Uint est pair ou non
    /// </summary>
    /// <returns>vrai si pair, sinon faux</returns>
    bool estPair() const;

    /// <summary>
    /// Surcharge de l'opérateur '+=' entre deux Uints.
    /// Additionne le second Uint au premier
    /// </summary>
    /// <param name="mud">Second nombre de l'opération</param>
    /// <returns>Retourne le premier nombre contenant l'addition</returns>
    Uint& operator+=(const Uint& mud);

    /// <summary>
    /// Surcharge de l'opérateur '-=' entre deux Uints.
    /// Soustrait le second Uint au premier si c'est possible
    /// </summary>
    /// <param name="mud">Second nombre de l'opération</param>
    /// <returns>Retourne le premier nombre contenant la soustraction</returns>
    Uint& operator-=(const Uint& mud);

    /// <summary>
    /// Surcharge de l'opérateur '*=' entre deux Uints.
    /// </summary>
    /// <param name="mud">Second nombre de l'opération</param>
    /// <returns>Retourne le premier nombre contenant 
    /// la multiplication</returns>
    Uint& operator*=(const Uint& mud);

    /// <summary>
    /// Surcharge de l'opérateur '*=' entre un Uint et un multiple
    /// </summary>
    /// <param name="multiple">Scalaire</param>
    /// <returns>Retourne le premier nombre contenant la multiplication 
    /// avec le scalaire</returns>
    Uint& operator*=(const uint64_t& multiple);

    /// <summary>
    /// Surcharge de l'opérateur '/=' entre deux Uint
    /// </summary>
    /// <param name="diviseur">Nombre diviseur</param>
    /// <returns>Premier nombre avec le résultat de la divison</returns>
    Uint& operator/=(const Uint& diviseur);

    /// <summary>
    /// Surcharge de l'opérateur '/=' entre deux Uint
    /// </summary>
    /// <param name="diviseur">Nombre diviseur</param>
    /// <returns>Premier nombre avec le reste de la division</returns>
    Uint& operator%=(const Uint& diviseur);

    /// <summary>
    /// Surcharge de l'opérateur '/=' entre un Uint et un diviseur (nombre)
    /// </summary>
    /// <param name="diviseur">Nombre diviseur de notre Uint</param>
    /// <returns>Retourne le premier nombre contenant la divison</returns>
    Uint& operator/=(const uint64_t& diviseur);

    /// <summary>
    /// Surcharge de l'opérateur '%=' entre un Uint et un diviseur (nombre)
    /// </summary>
    /// <param name="diviseur">diviseur">Nombre diviseur de notre Uint</param>
    /// <returns>Retourne le premier nombre contenant 
    /// le reste de la divison</returns>
    Uint& operator%=(const uint64_t& diviseur);

    /// <summary>
    /// Opérateur de cast d'un Uint en uint64_t
    /// </summary>
    explicit operator uint64_t() const;

    /// <summary>
    /// Surcharge de l'opérateur '++' préfixé
    /// </summary>
    /// <returns>Retourne le nombre incrémenté de 1</returns>
    Uint& operator++();

    /// <summary>
    /// Surcharge de l'opérateur '++' postfixé
    /// </summary>
    /// <param name="">Int permettant de différencier postfixé 
    /// et préfixé</param>
    /// <returns>Retourne le nombre (non-incrémenté), 
    /// puis l'incrémente de 1</returns>
    Uint operator++(int);


    /// <summary>
    /// Surcharge de l'opérateur '--' préfixé
    /// </summary>
    /// <returns>Retourne le nombre décrémenté de 1</returns>
    Uint& operator--();

    /// <summary>
    /// Surcharge de l'opérateur '--' postfixé
    /// </summary>
    /// <param name="">Int permettant de différencier postfixé 
    /// et préfixé</param>
    /// <returns>Retourne le nombre (non-décrémenté), 
    /// puis l'décrémente de 1</returns>
    Uint operator--(int);

    /// <summary>
    /// Surcharge de l'opérateur '>', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est plus grand que 
    /// le second</returns>
    bool operator>(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'opérateur '<', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est plus petit que 
    /// le second</returns>
    bool operator<(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'opérateur '>=', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est plus grand
    ///  ou égal au second</returns>
    bool operator>=(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'opérateur '<=', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est plus petit
    ///  ou égal au second</returns>
    bool operator<=(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'opérateur '==', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est égal au second</returns>
    bool operator==(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'opérateur '!=', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est différent du second</returns>
    bool operator!=(const Uint& mud) const;
};

#endif
