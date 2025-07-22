/**
   Clase: Jugador (Hereda de Persona)
   Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
   Universidad del Valle

  Información CRC:

  Responsabilidades:
   - Heredar comportamientos básicos de Persona.
   - Gestionar dinero y apuestas específicas del jugador.
   - Implementar comportamiento específico de mostrar mano.
   - Proporcionar funcionalidades específicas del jugador.

  Colaboradores:
   - Persona: Clase base de la que hereda.
   - Mano: Heredado de Persona para gestionar cartas.

    @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
    @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co,
           saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
*/

#ifndef JUGADOR_H
#define JUGADOR_H

#include "Persona.h"

class Jugador : public Persona {
private:
    int apuesta;
    int dinero;

public:
    Jugador(const std::string& nombre, int dinero);
    bool apostar(int apuesta);
    int getDinero() const;
    int getApuesta() const;
    void recibirDinero(int cantidad);
    void resetearApuesta();
    void mostrar(bool inicial = false) const override;
    std::string getTipo() const override;
    void saludar();
    std::string getsaludo();
};

#endif // JUGADOR_H