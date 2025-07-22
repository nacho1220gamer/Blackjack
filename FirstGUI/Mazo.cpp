/**
 * @file Mazo.cpp
 * @brief Implementación de la clase Mazo para el juego Blackjack
 * 
 * Este archivo implementa la clase Mazo que representa una baraja completa
 * de 52 cartas. Incluye la creación automática de todas las cartas con sus
 * respectivos valores, la funcionalidad de barajado aleatorio y el reparto
 * de cartas. Maneja los cuatro palos y los 13 tipos de cartas según las
 * reglas estándar del Blackjack.
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "Mazo.h"
#include <algorithm>
#include <random>
#include <stdexcept>

Mazo::Mazo() {
    const std::string palos[] = { "Corazones", "Diamantes", "Treboles", "Picas" };
    const std::string tipos[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    const int valores[] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
    for (const auto& palo : palos) {
        for (int j = 0; j < 13; ++j)
            cartas.emplace_back(tipos[j], palo, valores[j]);
    }
    barajar();
}

void Mazo::barajar() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartas.begin(), cartas.end(), g);
}

Carta Mazo::repartirCarta() {
    if (cartas.empty()) throw std::runtime_error("No hay cartas en el mazo");
    Carta carta = cartas.back();
    cartas.pop_back();
    return carta;
}

int Mazo::cartasRestantes() const { return cartas.size(); }