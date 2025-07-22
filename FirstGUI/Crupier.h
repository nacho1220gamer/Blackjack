/**
  Clase: Crupier (Hereda de Persona)
  Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
  Universidad del Valle

  Información CRC:

  Responsabilidades:
   - Heredar comportamientos básicos de Persona.
   - Repartir las cartas iniciales a los jugadores.
   - Implementar comportamiento específico de mostrar mano (con carta oculta).
   - Gestionar las reglas específicas del crupier.

  Colaboradores:
   - Persona: Clase base de la que hereda.
   - Mazo: Fuente de las cartas que reparte el crupier.
   - Jugador: A quien reparte las cartas iniciales.

    @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
    @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co,
           saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
*/

#ifndef CRUPIER_H
#define CRUPIER_H

#include "Persona.h"
#include "Mazo.h"
#include <vector>

class Jugador;

class Crupier : public Persona {
private:
    std::string nombre;

public:
    Crupier();
    std::string generarNombreAleatorio();
    void repartirCartasIniciales(Jugador& jugador, Mazo& mazo);
    void mostrar(bool inicial = false) const override;
    std::string getTipo() const override;
    void saludar();
    bool debeTomarCarta() const;
    std::string getsaludo() const;
};

#endif // CRUPIER_H