/**
 * @file Carta.cpp
 * @brief Implementación de la clase Carta para el juego Blackjack
 * 
 * Este archivo implementa la clase Carta que representa una carta individual
 * en el juego de Blackjack. Cada carta tiene un tipo (A, 2-10, J, Q, K),
 * un palo (Corazones, Diamantes, Tréboles, Picas) y un valor numérico
 * asociado para el cálculo de puntos en el juego.
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "Carta.h"

Carta::Carta(std::string tipo, std::string palo, int valor)
    : tipo(tipo), palo(palo), valor(valor) {}

std::string Carta::getTipo() const { return tipo; }
std::string Carta::getPalo() const { return palo; }
int Carta::getValor() const { return valor; }

std::string Carta::toString() const {
    return tipo + " de " + palo;
}