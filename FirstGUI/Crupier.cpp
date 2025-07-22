/**
 * @file Crupier.cpp
 * @brief Implementación de la clase Crupier para el juego Blackjack
 * 
 * Este archivo implementa la clase Crupier que hereda de Persona y representa
 * al dealer del casino en el juego de Blackjack. El crupier tiene un nombre
 * aleatorio generado automáticamente y sigue las reglas estándar del casino:
 * debe pedir cartas hasta tener al menos 17 puntos.
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "Crupier.h"
#include "Jugador.h"
#include <algorithm>
#include <random>
#include <stdexcept>

Crupier::Crupier() : Persona(generarNombreAleatorio()) {}

std::string Crupier::generarNombreAleatorio() {
    const std::string nombres[] = { "Ignacio", "Samuel", "Camilo", "Juan Manuel" };
    int numNombres = sizeof(nombres) / sizeof(nombres[0]);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numNombres - 1);

    return nombres[dis(gen)]; // Retorna el nombre seleccionado
}


void Crupier::repartirCartasIniciales(Jugador& jugador, Mazo& mazo) {
    jugador.recibirCarta(mazo.repartirCarta());
    jugador.recibirCarta(mazo.repartirCarta());
    recibirCarta(mazo.repartirCarta());
    recibirCarta(mazo.repartirCarta());
}

void Crupier::mostrar(bool) const {}

std::string Crupier::getTipo() const { return "Crupier"; }

void Crupier::saludar(){
    saludo = "Bienvenido a la mesa de Blackjack. Soy " + getNombre() + ", su crupier para esta partida.\n";
}

std::string Crupier::getsaludo() const{
    return saludo;
}

bool Crupier::debeTomarCarta() const {
    return getValorMano() < 17;
}
