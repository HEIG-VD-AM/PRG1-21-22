/*
Nom du fichier : Sint.cpp
But : Implantation d'une classe Sint permettant d'effectuer des opérations
	  sur des entiers positifs et négatifs aribtrairement longs
Nom : Alexis Martins
Date : 15.01.2022
No. Laboratoire : 31
*/
#include "Sint.hpp"
#include <iostream>

//MSD = Membre Sint de droite
//MSG = Membre Sint de gauche

//////////////////////////////// CONSTRUCTEURS ////////////////////////////////

Sint::Sint(const std::string& texte)
{
	/* 
	Si le premier carctère est un + ou un nombre, alors c'est un nombre positif
	si c'est un -, il est négatif. Autrement c'est une erreur.	
	*/ 
	if (texte.at(0) == '+' || isdigit(texte.at(0)))
	{
		signe = 0;
	}
	else if (texte.at(0) == '-')
	{
		signe = 1;
	}
	else
	{
		std::cerr << "Le caractère devant le nombre est incorrect."
					 " Le signe a été initialisé à zéro.";
		signe = 0;
	}
		
	std::string temp = texte;

	//Élimine les signes pour créer un Uint
	while (!isdigit(temp.at(0)))
	{
		temp = temp.substr(1);
	} 

	nombre = temp;
}

////////////////////////////// GESTION DU SIGNE ///////////////////////////////

Sint& Sint::gererSigne(const Sint& msd)
{
	//XOR entre les deux signes pour savoir s'il faut l'inverser
	signe = signe ^ msd.signe;

	//Le nombre 0 est forcément positif
	if (nombre.egalZero())
	{
		signe = false;
	}

	return *this;
}

////////////////////////// OPERATEURS ARITHMETIQUES ///////////////////////////

Sint& Sint::operator+=(const Sint& msd)
{
	/*
	S'ils ont le même signe, on fait une addition normale
	Autrement, on fait des soustraction selon le nombre plus grand des deux
	*/
	if (signe == msd.signe)
	{
		nombre += msd.nombre;
	}
	else if (nombre > msd.nombre)
	{
		nombre -= msd.nombre;
	}
	else
	{
		nombre = msd.nombre - nombre;
		-*this;
	}

	if (nombre.egalZero())
	{
		signe = false;
	}
	return *this;
}

///////////////////////////// OPERATEURS DE FLUX //////////////////////////////

std::ostream& operator<<(std::ostream& flux, const Sint& msg)
{
	//Affiche le signe si le nombre est négatif
	if (msg.signe)
	{
		flux << '-';
	}

	//Appelle l'affichage de la classe Uint 
	flux << msg.nombre;

	return flux;
}

////////////////////////// FONCTIONS AUTRES ///////////////////////////

int compare(const Sint& msg, const Sint& msd)
{
	/*
	Si A est négatif et B positif (A < B)
	Si A est positif et B négatif (A > B)
	Si A est positif et B positif (On appelle comp de Uint)
	Si A est négatif et B négatif (On appelle comp de Uint et
	on inverse le résultat)
	*/
	if (msg.signe && !msd.signe)
	{
		return -1;
	}
	else if (msg.signe && msd.signe)
	{
		return comp(msd.nombre, msg.nombre);
	}
	else if (!msg.signe && !msd.signe)
	{
		return comp(msg.nombre, msd.nombre);
	}
	else
	{
		return 1;
	}
}