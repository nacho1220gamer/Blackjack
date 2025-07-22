/*
    Clase: Carta
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle
    
    Información CRC:
    
    Clase: Carta

    Responsabilidades:
        - Almacenar información básica de una carta.
        - Proporcionar acceso controlado a los atributos mediante métodos get.
        - Representación en texto de la carta mediante toString().
    
    Colaboradores:
        - Mazo: La clase Carta es utilizada por Mazo para crear un conjunto de cartas.
        - Mano: La clase Carta es utilizada por Mano para crear un conjunto de cartas para los
        usuarios.
    
    Este es un proyecto del curso FPOO de la Universidad del Valle, 
    desarrollado con fines académicos. Puede ser utilizado con fines 
    académicos dando los créditos de la autoría.

    Autor: Victor Bucheli
    Correo: victor.bucheli@correounivalle.edu.co
    @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz ]
    @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co , 
    saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co ]

*/

#ifndef CARTA_H
#define CARTA_H

#include <string>

class Carta {
private:
    std::string tipo;
    std::string palo;
    int valor;
public:
    Carta(std::string tipo, std::string palo, int valor);
    std::string getTipo() const;
    std::string getPalo() const;
    int getValor() const;
    std::string toString() const;
};

#endif // CARTA_H