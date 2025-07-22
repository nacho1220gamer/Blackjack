/**
    Clase: Blackjack (Refactorizada con polimorfismo)
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Información CRC:

    Clase: Blackjack

    Responsabilidades:
        - Gestiona el flujo principal del juego de blackjack usando polimorfismo.
        - Controla el inicio de cada ronda de juego.
        - Determina el resultado de cada ronda usando referencias polimórficas.
        - Proporciona la interfaz necesaria para que el usuario pueda jugar.
        - Demuestra el uso de herencia y polimorfismo con Persona.

    Colaboradores:
        - Persona: Clase base que permite polimorfismo.
        - Jugador: Clase derivada que representa al jugador.
        - Crupier: Clase derivada que representa al crupier.
        - Mazo: Proporciona las cartas necesarias para el juego.

    @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
    @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co,
           saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
*/


#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <string>
#include <vector>
#include <cmath>
#include "Persona.h"
#include "Jugador.h"
#include "Crupier.h"
#include "Mazo.h"

class Blackjack
{
private:
    Jugador jugador;
    Crupier crupier;
    Mazo mazo;
    std::vector<Persona*> participantes;
    std::string resultado;
    std::string estadistica;

public:
    Blackjack(const std::string& nombreJugador, int dineroInicial);

    // Inicializa una nueva ronda
    bool nuevaRonda(int apuesta);

    // Acciones del jugador
    bool jugadorPideCarta();
    void jugadorSePlanta();

    // Acciones del crupier
    void turnoCrupier();

    // Determina resultado de la ronda
    void determinarResultado();

    void MostrarEstadisticasFinales(const std::string& nombre, int dineroInicial, int dineroFinal);

    // Acceso a estado del juego
    Jugador& getJugador();
    Crupier& getCrupier();
    const Jugador& getJugador() const;
    const Crupier& getCrupier() const;
    std::string getResultado() const;
    std::string getEstadistica() const;
    bool jugadorSePaso() const;
    bool crupierSePaso() const;
    bool jugadorTieneBlackjack() const;
    bool crupierTieneBlackjack() const;
    int cartasRestantes() const;
};

#endif // BLACKJACK_H