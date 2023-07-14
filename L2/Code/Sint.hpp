/*
Nom du fichier : Sint.hpp
But : Fichier header de la classe Sint
Nom : Alexis Martins
Date : 15.01.2022
No. Laboratoire : 31
*/
#ifndef SINT_HPP
#define SINT_HPP

#include <string>
#include "Uint.hpp"

class Sint
{
    //MSD = Membre Sint de droite
    //MSG = Membre Sint de gauche

    bool signe; // 0 = positif, 1 = négatif
    Uint nombre;

    /// <summary>
    /// Surcharge de l'opérateur '+', en réutilisant 
    /// l'opérateur '+=' pour deux Sints
    /// </summary>
    /// <param name="msg">Premier nombre de l'opération</param>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Addition des deux Sints</returns>
    friend Sint operator+(Sint msg, const Sint& msd) 
    { return msg += msd; };

    /// <summary>
    /// Surcharge de l'opérateur '-', en réutilisant 
    /// l'opérateur '-=' pour deux Sints
    /// </summary>
    /// <param name="msg">Premier nombre de l'opération</param>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Soustraction des deux Sints</returns>
    friend Sint operator-(Sint msg, const Sint& msd) { return msg -= msd; };

    /// <summary>
    /// Surcharge de l'opérateur '*', en réutilisant 
    /// l'opérateur '*=' pour deux Sints
    /// </summary>
    /// <param name="msg">Premier nombre de l'opération</param>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Multiplication des deux Sints</returns>
    friend Sint operator*(Sint msg, const Sint& msd) { return msg *= msd; };

    /// <summary>
    /// Surcharge de l'opérateur '/', en réutilisant 
    /// l'opérateur '/=' pour deux Sints
    /// </summary>
    /// <param name="msg">Premier nombre de l'opération</param>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Division des deux Sints</returns>
    friend Sint operator/(Sint msg, const Sint& msd) { return msg /= msd; };

    /// <summary>
    /// Surcharge de l'opérateur '%', en réutilisant 
    /// l'opérateur '%=' pour deux Sints
    /// </summary>
    /// <param name="msg">Premier nombre de l'opération</param>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Reste de la division de des deux Sints</returns>
    friend Sint operator%(Sint msg, const Sint& msd) { return msg %= msd; };

    /// <summary>
    /// Permet de comparer la valeurs de deux Sint (Plus petit, grand ou égal)
    /// </summary>
    /// <param name="msg">Première valeur de comparaison</param>
    /// <param name="msd">Seconde valeur de comparaison</param>
    /// <returns>-1 si A < B, 0 si A = B et 1 si A > B</returns>
    friend int compare(const Sint& msg, const Sint& msd);

    /// <summary>
    /// Permet d'afficher les informations de nos Sints
    /// </summary>
    /// <param name="flux">Référence au flux de sortie</param>
    /// <param name="msg">Sint à afficher</param>
    /// <returns>Nouveau flux</returns>
    friend std::ostream& operator<<(std::ostream& flux, const Sint& msg);

    /// <summary>
    /// Gestion du signe dans les opérations de multiplication et division
    /// </summary>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Sint avec le signe potentiellement inversé</returns>
    Sint& gererSigne(const Sint& msd);

public:
    
    /// <summary>
    /// Constructeur vide de la classe Sint
    /// </summary>
    Sint() {};

    /// <summary>
    /// Constructeur de la classe Sint à partir d'une string
    /// </summary>
    /// <param name="texte">Nombre à stocker dans dans l'Sint</param>
    Sint(const std::string& texte);

    /// <summary>
    /// Constructeur de la classe Sint à partir d'un Uint
    /// </summary>
    /// <param name="nombre">Uint</param>
    Sint(const Uint& nombre) { this->nombre = nombre; signe = 0; };

    /// <summary>
    /// Constructeur de la classe Sint à partir d'un int64_t
    /// </summary>
    /// <param name="nombre">int64_t</param>
    Sint(const int64_t& nombre) { *this = std::to_string(nombre); };

    /// <summary>
    /// Surcharge de l'opérateur '+=' entre deux Sints.
    /// Additionne le second Sint au premier
    /// </summary>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Le premier nombre contenant l'addition</returns>
    Sint& operator+=(const Sint& msd);

    /// <summary>
    /// Surcharge de l'opérateur '-=' entre deux Sints.
    /// Soustrait le second Sint au premier
    /// </summary>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Le premier nombre contenant la soustraction</returns>
    Sint& operator-=(Sint msd) { return *this += -msd; };

    /// <summary>
    /// Surcharge de l'opérateur '*=' entre deux Sints.
    /// Multiplie le second Sint au premier
    /// </summary>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Le premier nombre contenant la multiplication</returns>
    Sint& operator*=(const Sint& msd) { nombre *= msd.nombre; return gererSigne(msd); };

    /// <summary>
    /// Surcharge de l'opérateur '/=' entre deux Sints.
    /// Multiplie le second Sint au premier
    /// </summary>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Le premier nombre contenant la division</returns>
    Sint& operator/=(const Sint& msd) { nombre /= msd.nombre; return gererSigne(msd); };

    /// <summary>
    /// Surcharge de l'opérateur '%=' entre deux Sints.
    /// Reste de la division le second Sint au premier
    /// </summary>
    /// <param name="msd">Second nombre de l'opération</param>
    /// <returns>Le premier nombre contenant le reste</returns>
    Sint& operator%=(const Sint& msd) { nombre %= msd.nombre; return *this; };

    /// <summary>
    /// Surcharge de l'opérateur '-' qui permet d'inverser le signe
    /// </summary>
    /// <returns>Le Sint avec le signe inverse</returns>
    Sint& operator-() { signe = !signe; return *this; };

    /// <summary>
    /// Surcharge de l'opérateur '>', entre deux Sints
    /// </summary>
    /// <param name="msd">Second nombre de la comparaison</param>
    /// <returns>Vrai si le premier est plus grand que le second</returns>
    bool operator>(const Sint& msd) const { return compare(*this, msd) == 1; };

    /// <summary>
    /// Surcharge de l'opérateur '<', entre deux Sints
    /// </summary>
    /// <param name="msd">Second nombre de la comparaison</param>
    /// <returns>Vrai si le premier est plus petit que le second</returns>
    bool operator<(const Sint& msd) const { return compare(*this, msd) == -1; };

    /// <summary>
    /// Surcharge de l'opérateur '>=', entre deux Sints
    /// </summary>
    /// <param name="msd">Second nombre de la comparaison</param>
    /// <returns>Vrai si le premier est plus grand ou égal au second</returns>
    bool operator>=(const Sint& msd) const { return compare(*this, msd) != -1; };

    /// <summary>
    /// Surcharge de l'opérateur '<=', entre deux Sints
    /// </summary>
    /// <param name="msd">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est plus petit
    ///  ou égal au second</returns>
    bool operator<=(const Sint& msd) const { return compare(*this, msd) != 1; };

    /// <summary>
    /// Surcharge de l'opérateur '==', entre deux Sints
    /// </summary>
    /// <param name="msd">Second nombre de la comparaison</param>
    /// <returns>Vrai si le premier est égal au second</returns>
    bool operator==(const Sint& msd) const { return compare(*this, msd) == 0; };

    /// <summary>
    /// Surcharge de l'opérateur '!=', entre deux Uints
    /// </summary>
    /// <param name="msd">Second nombre de la comparaison</param>
    /// <returns>Vrai si le premier est différent du second</returns>
    bool operator!=(const Sint& msd) const { return compare(*this, msd) != 0; };

    /// <summary>
    /// Retourne le Uint stocké dans le Sint (représeente la valeur absolue)
    /// </summary>
    /// <returns>Le Uint stocké en tant que membre privé</returns>
    Uint abs() const { return nombre; };
};

#endif
