/**
    Clase: Mazo
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Información CRC:

    Responsabilidades:
        - Crear y gestionar un mazo de cartas.
        - Barajar las cartas para mezclarlas.
        - Repartir cartas del mazo.
        - Proporcionar información sobre las cartas restantes en el mazo.

    Colaboradores:
        - Carta: Utiliza objetos de la clase Carta para almacenar las cartas del mazo.


    @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz ]
    @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co ,
        saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co ]


    Librerías utilizadas:
        - <vector>: Para almacenar y gestionar dinámicamente las cartas del mazo.
        - <string>: Para representar cartas.
*/

#ifndef MAZO_H
#define MAZO_H

#include <vector>
#include "Carta.h"

class Mazo {
private:
    std::vector<Carta> cartas;
public:
    Mazo();
    void barajar();
    Carta repartirCarta();
    int cartasRestantes() const;
};

#endif // MAZO_H