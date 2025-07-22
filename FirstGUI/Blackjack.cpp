/**
 * @file Blackjack.cpp
 * @brief Implementación de la clase Blackjack - Motor principal del juego
 * 
 * Este archivo contiene la implementación de todos los métodos de la clase Blackjack,
 * que maneja la lógica principal del juego de casino. Incluye el control de rondas,
 * manejo de cartas, determinación de resultados y cálculo de ganancias/pérdidas
 * según las reglas estándar del Blackjack.
 * 
 * Funcionalidades principales:
 * - Gestión de rondas de juego y apuestas
 * - Control del flujo entre jugador y crupier
 * - Determinación automática de resultados
 * - Cálculo de pagos (incluido Blackjack 3:2)
 * - Estadísticas finales de sesiónes
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "Blackjack.h"

Blackjack::Blackjack(const std::string& nombreJugador, int dineroInicial)
    : jugador(nombreJugador, dineroInicial), crupier()
{
    participantes.push_back(&jugador);
    participantes.push_back(&crupier);
}

bool Blackjack::nuevaRonda(int apuesta)
{
    if (jugador.getDinero() < apuesta || apuesta <= 0)
        return false;

    for (auto p : participantes) p->clear();
    if (mazo.cartasRestantes() < 17) mazo = Mazo();
    if (!jugador.apostar(apuesta)) return false;

    crupier.repartirCartasIniciales(jugador, mazo);
    resultado.clear();
    return true;
}

bool Blackjack::jugadorPideCarta()
{
    jugador.recibirCarta(mazo.repartirCarta());
    if (jugador.sePaso())
    {
        determinarResultado();
        return false;
    }
    return true;
}

void Blackjack::jugadorSePlanta()
{
    turnoCrupier();
    determinarResultado();
}

void Blackjack::turnoCrupier()
{
    while (crupier.debeTomarCarta())
    {
        crupier.recibirCarta(mazo.repartirCarta());
        if (crupier.sePaso())
            break;
    }
}

void Blackjack::determinarResultado()
{
    int valorJugador = jugador.getValorMano();
    int valorCrupier = crupier.getValorMano();
    int apuesta = jugador.getApuesta();

    if (jugador.sePaso())
        resultado = "Perdiste: Te pasaste de 21.";
    else if (crupier.sePaso())
    {
        resultado = "¡Ganaste! El crupier se pasó.";
        jugador.recibirDinero(apuesta * 2);
    }
    else if (jugador.tieneBlackjack() && !crupier.tieneBlackjack())
    {
        int ganancia = static_cast<int>(apuesta * 1.5);
        jugador.recibirDinero(apuesta + ganancia);
        resultado = "¡Blackjack! Ganaste.";
    }
    else if (valorJugador > valorCrupier)
    {
        jugador.recibirDinero(apuesta * 2);
        resultado = "¡Ganaste! Tienes más puntos.";
    }
    else if (valorJugador == valorCrupier)
    {
        jugador.recibirDinero(apuesta);
        resultado = "Empate. Recuperas tu apuesta.";
    }
    else
        resultado = "Perdiste. El crupier gana.";

}

void Blackjack::MostrarEstadisticasFinales(const std::string& nombre, int dineroInicial, int dineroFinal)
{
    int diferencia = dineroFinal - dineroInicial;

    std::string resultado = "Jugador: " + nombre + "\n";
    resultado += "Dinero inicial: $" + std::to_string(dineroInicial) + "\n";
    resultado += "Dinero final: $" + std::to_string(dineroFinal) + "\n";

    if (diferencia > 0) {
        resultado += "¡Felicidades! Ganaste $" + std::to_string(diferencia);
    }
    else if (diferencia < 0) {
        resultado += "Perdiste $" + std::to_string(abs(diferencia));
    }
    else {
        resultado += "Terminaste con el mismo dinero que empezaste.";
    }

    estadistica = resultado;
}

Jugador& Blackjack::getJugador() { return jugador; }
Crupier& Blackjack::getCrupier() { return crupier; }
const Jugador& Blackjack::getJugador() const{ return jugador; }
const Crupier& Blackjack::getCrupier() const{ return crupier; }
std::string Blackjack::getResultado() const { return resultado; }
std::string Blackjack::getEstadistica() const { return estadistica; }
bool Blackjack::jugadorSePaso() const { return jugador.sePaso(); }
bool Blackjack::crupierSePaso() const { return crupier.sePaso(); }
bool Blackjack::jugadorTieneBlackjack() const { return jugador.tieneBlackjack(); }
bool Blackjack::crupierTieneBlackjack() const { return crupier.tieneBlackjack(); }
int Blackjack::cartasRestantes() const { return mazo.cartasRestantes(); }