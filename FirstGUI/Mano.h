/**
    Clase: Mano
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Información CRC:

    Responsabilidades:
        - Gestionar las cartas que un jugador tiene en su mano.
        - Calcular el valor total de la mano según las reglas del juego.
        - Verificar si la mano se ha pasado de 21 (en juegos como Blackjack).
        - Mostrar las cartas de la mano.
        - Limpiar la mano para una nueva ronda.
        - Verificar si la mano es un Blackjack.

    Colaboradores:
        Carta: Utiliza objetos de la clase Carta para representar las cartas en la mano.


    @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz ]
    @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co ,
        saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co ]


    Librerías utilizadas:
        <vector>: Para almacenar y manipular las cartas de la mano.
        <string>: Para posibles operaciones de representación/texto (ej: mostrar cartas).
*/

#ifndef MANO_H
#define MANO_H

#include <vector>
#include "Carta.h"

class Mano {
private:
    std::vector<Carta> cartas;
    int valor;
public:
    Mano();
    int getValor() const;
    std::vector<Carta> getCartas() const;
    void agregar(Carta carta);
    int calcular() const;
    bool sePaso() const;
    void mostrar() const;
    void clear();
    bool esBlackjack() const;
};

#endif // MANO_H