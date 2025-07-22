/**
    Clase: Persona (Clase base abstracta)
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Información CRC:

    Responsabilidades:
        - Definir la interfaz común para todos los participantes del juego.
        - Gestionar operaciones básicas con cartas (recibir, mostrar mano).
        - Proporcionar métodos virtuales puros para comportamientos específicos.
        - Mantener estado común (nombre, mano).

    Colaboradores:
        - Mano: Para gestionar las cartas que tiene cada persona.
        - Carta: Para recibir cartas individuales.

    @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
    @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co,
           saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
*/

#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "Mano.h"
#include "Carta.h"

class Persona {
protected:
    std::string nombre;
    Mano mano;
    std::string saludo;
public:
    Persona(const std::string& nombre);
    virtual ~Persona() = default;
    void recibirCarta(const Carta& carta);
    std::string getNombre() const;
    int getValorMano() const;
    Mano& getMano();
    const Mano& getMano() const;
    bool sePaso() const;
    bool tieneBlackjack() const;
    void clear();
    virtual void mostrar(bool inicial = false) const = 0;
    virtual std::string getTipo() const = 0;
    virtual void saludar();
    virtual std::string getsaludo();
};

#endif // PERSONA_H