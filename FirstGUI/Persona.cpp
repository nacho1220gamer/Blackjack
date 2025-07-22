/**
 * @file Persona.cpp
 * @brief Clase base abstracta Persona para el juego Blackjack
 * 
 * Este archivo implementa la clase Persona que sirve como clase base para
 * Jugador y Crupier. Proporciona funcionalidad común como el manejo de cartas,
 * cálculo del valor de la mano, detección de Blackjack y bust (pasarse de 21).
 * También incluye métodos virtuales para saludos personalizados.
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "Persona.h"

Persona::Persona(const std::string& nombre) : nombre(nombre) {}
void Persona::recibirCarta(const Carta& carta) { mano.agregar(carta); }
std::string Persona::getNombre() const { return nombre; }
int Persona::getValorMano() const { return mano.getValor(); }
Mano& Persona::getMano() { return mano; }
const Mano& Persona::getMano() const { return mano; }
bool Persona::sePaso() const { return mano.sePaso(); }
bool Persona::tieneBlackjack() const { return mano.esBlackjack(); }
void Persona::clear() { mano.clear(); }
void Persona::saludar() {}
std::string Persona::getsaludo() {
	return saludo;
}