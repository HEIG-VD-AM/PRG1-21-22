/*
Nom du fichier : Sint.cpp
But : Implantation d'une classe Sint permettant d'effectuer des op�rations
	  sur des entiers positifs et n�gatifs aribtrairement longs
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
	Si le premier carct�re est un + ou un nombre, alors c'est un nombre positif
	si c'est un -, il est n�gatif. Autrement c'est une erreur.	
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
		std::cerr << "Le caract�re devant le nombre est incorrect."
					 " Le signe a �t� initialis� � z�ro.";
		signe = 0;
	}
		
	std::string temp = texte;

	//�limine les signes pour cr�er un Uint
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

	//Le nombre 0 est forc�ment positif
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
	S'ils ont le m�me signe, on fait une addition normale
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
	//Affiche le signe si le nombre est n�gatif
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
	Si A est n�gatif et B positif (A < B)
	Si A est positif et B n�gatif (A > B)
	Si A est positif et B positif (On appelle comp de Uint)
	Si A est n�gatif et B n�gatif (On appelle comp de Uint et
	on inverse le r�sultat)
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