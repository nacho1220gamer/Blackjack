
/**
 * @file Mano.cpp
 * @brief Implementación de la clase Mano para el juego Blackjack
 * 
 * Este archivo implementa la clase Mano que representa el conjunto de cartas
 * que tiene un jugador o crupier. Maneja el cálculo automático del valor total
 * considerando las reglas especiales del As (puede valer 1 u 11), y determina
 * si la mano se pasó de 21 o si tiene Blackjack (21 con exactamente 2 cartas).
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "Mano.h"

Mano::Mano() : valor(0) {}

int Mano::getValor() const { return valor; }
std::vector<Carta> Mano::getCartas() const { return cartas; }

void Mano::agregar(Carta carta) {
    cartas.push_back(carta);
    valor = calcular();
}

int Mano::calcular() const {
    int total = 0, ases = 0;
    for (auto &c : cartas) {
        total += c.getValor();
        if (c.getTipo() == "A") ases++;
    }
    while (total > 21 && ases > 0) {
        total -= 10;
        ases--;
    }
    return total;
}

bool Mano::sePaso() const { return valor > 21; }
void Mano::mostrar() const {}
void Mano::clear() { cartas.clear(); valor = 0; }
bool Mano::esBlackjack() const { return cartas.size() == 2 && valor == 21; }