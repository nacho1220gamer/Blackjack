/**
 * @file Jugador.cpp
 * @brief Implementación de la clase Jugador para el juego Blackjack
 * 
 * Este archivo implementa la clase Jugador que hereda de Persona y representa
 * al jugador humano en el juego de Blackjack. El jugador tiene dinero para apostar,
 * puede realizar apuestas y recibir ganancias según el resultado de cada mano.
 * También maneja la lógica de apuestas y el saludo personalizado del jugador.
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "Jugador.h"

Jugador::Jugador(const std::string &nombre, int dinero)
    : Persona(nombre), dinero(dinero), apuesta(0) {}

bool Jugador::apostar(int nuevaApuesta) {
    if (nuevaApuesta <= 0 || nuevaApuesta > dinero) return false;
    apuesta = nuevaApuesta;
    dinero -= nuevaApuesta;
    return true;
}

int Jugador::getDinero() const { return dinero; }
int Jugador::getApuesta() const { return apuesta; }
void Jugador::recibirDinero(int cantidad) { if (cantidad > 0) dinero += cantidad; }
void Jugador::resetearApuesta() { apuesta = 0; }

void Jugador::mostrar(bool) const {}
std::string Jugador::getTipo() const { return "Jugador"; }
void Jugador::saludar(){
    saludo = "Hola! Soy " + nombre + ", tengo $" + std::to_string(dinero) + " para apostar. �Vamos a jugar!\n";
}
std::string Jugador::getsaludo() {
    return saludo;
}