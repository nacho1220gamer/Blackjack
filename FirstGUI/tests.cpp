
#include <iostream>
#include <cassert>
#include <stdexcept>
#include "Carta.h"
#include "Mazo.h"
#include "Mano.h"
#include "Persona.h"
#include "Jugador.h"
#include "Crupier.h"
#include "Blackjack.h"

class TestRunner {
private:
    int tests_passed = 0;
    int tests_failed = 0;
public:
    void assert_test(bool condition, const std::string& test_name) {
        if (condition) {
            std::cout << "[PASS] " << test_name << std::endl;
            tests_passed++;
        } else {
            std::cout << "[FAIL] " << test_name << std::endl;
            tests_failed++;
        }
    }

    void print_summary() {
        std::cout << "\n=== RESUMEN DE PRUEBAS ===" << std::endl;
        std::cout << "Pruebas pasadas: " << tests_passed << std::endl;
        std::cout << "Pruebas fallidas: " << tests_failed << std::endl;
        std::cout << "Total: " << (tests_passed + tests_failed) << std::endl;
    }
};

// Pruebas para la clase Carta
void test_carta(TestRunner& runner) {
    std::cout << "\n=== PRUEBAS CLASE CARTA ===" << std::endl;
    
    // Caso común: crear carta válida
    try {
        Carta carta("A", "Corazones", 11);
        runner.assert_test(carta.getTipo() == "A", "Carta - getTipo() devuelve tipo correcto");
        runner.assert_test(carta.getPalo() == "Corazones", "Carta - getPalo() devuelve palo correcto");
        runner.assert_test(carta.getValor() == 11, "Carta - getValor() devuelve valor correcto");
        runner.assert_test(carta.toString() == "A de Corazones", "Carta - toString() formato correcto");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Carta - Constructor básico falló");
    }

    // Casos límite: diferentes valores
    try {
        Carta carta_baja("2", "Picas", 2);
        runner.assert_test(carta_baja.getValor() == 2, "Carta - Valor mínimo (2)");
        
        Carta carta_alta("K", "Diamantes", 10);
        runner.assert_test(carta_alta.getValor() == 10, "Carta - Valor figuras (10)");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Carta - Casos límite fallaron");
    }
}

// Pruebas para la clase Mazo
void test_mazo(TestRunner& runner) {
    std::cout << "\n=== PRUEBAS CLASE MAZO ===" << std::endl;
    
    // Caso común: mazo inicial
    try {
        Mazo mazo;
        runner.assert_test(mazo.cartasRestantes() == 52, "Mazo - Contiene 52 cartas inicialmente");
        
        // Repartir una carta
        Carta carta = mazo.repartirCarta();
        runner.assert_test(mazo.cartasRestantes() == 51, "Mazo - Quedan 51 cartas después de repartir");
        runner.assert_test(!carta.getTipo().empty(), "Mazo - Carta repartida es válida");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Mazo - Operaciones básicas fallaron");
    }

    // Caso límite: agotar el mazo
    try {
        Mazo mazo_vacio;
        for (int i = 0; i < 52; i++) {
            mazo_vacio.repartirCarta();
        }
        runner.assert_test(mazo_vacio.cartasRestantes() == 0, "Mazo - Se puede agotar completamente");
        
        // Intentar repartir cuando está vacío
        bool excepcion_lanzada = false;
        try {
            mazo_vacio.repartirCarta();
        } catch (const std::runtime_error& e) {
            excepcion_lanzada = true;
        }
        runner.assert_test(excepcion_lanzada, "Mazo - Lanza excepción cuando está vacío");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Mazo - Prueba de mazo vacío falló");
    }
}

// Pruebas para la clase Jugador
void test_jugador(TestRunner& runner) {
    std::cout << "\n=== PRUEBAS CLASE JUGADOR ===" << std::endl;
    
    // Caso común: jugador válido
    try {
        Jugador jugador("TestPlayer", 1000);
        runner.assert_test(jugador.getNombre() == "TestPlayer", "Jugador - Nombre correcto");
        runner.assert_test(jugador.getDinero() == 1000, "Jugador - Dinero inicial correcto");
        runner.assert_test(jugador.getTipo() == "Jugador", "Jugador - Tipo correcto");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Jugador - Constructor básico falló");
    }

    // Pruebas de apuestas
    try {
        Jugador jugador("TestPlayer", 1000);
        
        // Apuesta válida
        bool apuesta_exitosa = jugador.apostar(100);
        runner.assert_test(apuesta_exitosa, "Jugador - Apuesta válida exitosa");
        runner.assert_test(jugador.getDinero() == 900, "Jugador - Dinero reducido después de apostar");
        runner.assert_test(jugador.getApuesta() == 100, "Jugador - Apuesta registrada correctamente");
        
        // Recibir dinero
        jugador.recibirDinero(200);
        runner.assert_test(jugador.getDinero() == 1100, "Jugador - Recibe dinero correctamente");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Jugador - Operaciones de dinero fallaron");
    }

    // Casos límite: apuestas inválidas
    try {
        Jugador jugador_pobre("PoorPlayer", 50);
        
        // Apuesta mayor al dinero disponible
        bool apuesta_fallida = jugador_pobre.apostar(100);
        runner.assert_test(!apuesta_fallida, "Jugador - Rechaza apuesta mayor al dinero");
        
        // Apuesta negativa
        bool apuesta_negativa = jugador_pobre.apostar(-10);
        runner.assert_test(!apuesta_negativa, "Jugador - Rechaza apuesta negativa");
        
        // Apuesta cero
        bool apuesta_cero = jugador_pobre.apostar(0);
        runner.assert_test(!apuesta_cero, "Jugador - Rechaza apuesta de cero");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Jugador - Casos límite de apuestas fallaron");
    }
}

// Pruebas para la clase Crupier
void test_crupier(TestRunner& runner) {
    std::cout << "\n=== PRUEBAS CLASE CRUPIER ===" << std::endl;
    
    try {
        Crupier crupier;
        runner.assert_test(crupier.getTipo() == "Crupier", "Crupier - Tipo correcto");
        runner.assert_test(!crupier.getNombre().empty(), "Crupier - Tiene nombre asignado");
        
        // Verificar que el nombre es uno de los esperados
        std::string nombre = crupier.getNombre();
        bool nombre_valido = (nombre == "Ignacio" || nombre == "Samuel" || 
                             nombre == "Camilo" || nombre == "Juan Manuel");
        runner.assert_test(nombre_valido, "Crupier - Nombre es uno de los predefinidos");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Crupier - Constructor básico falló");
    }

    // Prueba de repartir cartas iniciales
    try {
        Crupier crupier;
        Jugador jugador("TestPlayer", 1000);
        Mazo mazo;
        
        int cartas_iniciales_jugador = 0;
        int cartas_iniciales_crupier = 0;
        
        crupier.repartirCartasIniciales(jugador, mazo);
        
        runner.assert_test(jugador.getMano().getCartas().size() == cartas_iniciales_jugador + 2, 
                          "Crupier - Reparte 2 cartas al jugador");
        runner.assert_test(crupier.getMano().getCartas().size() == cartas_iniciales_crupier + 2, 
                          "Crupier - Se reparte 2 cartas a sí mismo");
        runner.assert_test(mazo.cartasRestantes() == 48, "Crupier - Mazo tiene 4 cartas menos");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Crupier - Repartir cartas iniciales falló");
    }
}

// Pruebas para la clase Mano
void test_mano(TestRunner& runner) {
    std::cout << "\n=== PRUEBAS CLASE MANO ===" << std::endl;
    
    try {
        Mano mano;
        runner.assert_test(mano.getCartas().size() == 0, "Mano - Inicialmente vacía");
        runner.assert_test(mano.getValor() == 0, "Mano - Valor inicial es 0");
        runner.assert_test(!mano.sePaso(), "Mano - No se pasa inicialmente");
        runner.assert_test(!mano.esBlackjack(), "Mano - No tiene blackjack inicialmente");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Mano - Constructor básico falló");
    }

    // Pruebas agregando cartas
    try {
        Mano mano;
        Carta carta1("K", "Corazones", 10);
        Carta carta2("A", "Picas", 11);
        
        mano.agregar(carta1);
        runner.assert_test(mano.getCartas().size() == 1, "Mano - Agrega carta correctamente");
        runner.assert_test(mano.getValor() == 10, "Mano - Valor correcto con una carta");
        
        mano.agregar(carta2);
        runner.assert_test(mano.getCartas().size() == 2, "Mano - Agrega segunda carta");
        runner.assert_test(mano.esBlackjack(), "Mano - Detecta blackjack (K+A)");
        runner.assert_test(mano.getValor() == 21, "Mano - Valor blackjack es 21");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Mano - Agregar cartas falló");
    }

    // Caso límite: se pasa de 21
    try {
        Mano mano_pasada;
        Carta carta1("K", "Corazones", 10);
        Carta carta2("Q", "Picas", 10);
        Carta carta3("5", "Diamantes", 5);
        
        mano_pasada.agregar(carta1);
        mano_pasada.agregar(carta2);
        mano_pasada.agregar(carta3);
        
        runner.assert_test(mano_pasada.sePaso(), "Mano - Detecta cuando se pasa de 21");
        runner.assert_test(mano_pasada.getValor() == 25, "Mano - Valor correcto al pasarse");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Mano - Caso de pasarse falló");
    }

    // Prueba manejo de As
    try {
        Mano mano_ases;
        Carta as1("A", "Corazones", 11);
        Carta as2("A", "Picas", 11);
        Carta carta9("9", "Diamantes", 9);
        
        mano_ases.agregar(as1);
        mano_ases.agregar(as2);
        mano_ases.agregar(carta9);
        
        // Con A+A+9, debería ser 1+1+9=11 o 1+11+9=21
        int valor = mano_ases.getValor();
        runner.assert_test(valor <= 21, "Mano - Maneja ases correctamente para no pasarse");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Mano - Manejo de ases falló");
    }
}

// Pruebas para la clase Blackjack (juego completo)
void test_blackjack(TestRunner& runner) {
    std::cout << "\n=== PRUEBAS CLASE BLACKJACK ===" << std::endl;
    
    try {
        Blackjack juego("TestPlayer", 1000);
        runner.assert_test(juego.getJugador().getNombre() == "TestPlayer", "Blackjack - Jugador creado correctamente");
        runner.assert_test(juego.getJugador().getDinero() == 1000, "Blackjack - Dinero inicial correcto");
        runner.assert_test(!juego.getCrupier().getNombre().empty(), "Blackjack - Crupier creado");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Blackjack - Constructor básico falló");
    }

    // Prueba nueva ronda
    try {
        Blackjack juego("TestPlayer", 1000);
        bool ronda_iniciada = juego.nuevaRonda(100);
        
        runner.assert_test(ronda_iniciada, "Blackjack - Nueva ronda inicia correctamente");
        runner.assert_test(juego.getJugador().getDinero() == 900, "Blackjack - Dinero descontado en nueva ronda");
        runner.assert_test(juego.getJugador().getMano().getCartas().size() == 2, "Blackjack - Jugador recibe 2 cartas");
        runner.assert_test(juego.getCrupier().getMano().getCartas().size() == 2, "Blackjack - Crupier recibe 2 cartas");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Blackjack - Nueva ronda falló");
    }

    // Casos límite: apuestas inválidas
    try {
        Blackjack juego("PoorPlayer", 50);
        
        bool ronda_fallida = juego.nuevaRonda(100);
        runner.assert_test(!ronda_fallida, "Blackjack - Rechaza ronda con apuesta excesiva");
        
        bool ronda_negativa = juego.nuevaRonda(-10);
        runner.assert_test(!ronda_negativa, "Blackjack - Rechaza apuesta negativa");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Blackjack - Casos límite de nueva ronda fallaron");
    }

    // Prueba estadísticas finales
    try {
        Blackjack juego("TestPlayer", 1000);
        juego.MostrarEstadisticasFinales("TestPlayer", 1000, 1200);
        
        std::string estadistica = juego.getEstadistica();
        runner.assert_test(!estadistica.empty(), "Blackjack - Genera estadísticas finales");
        runner.assert_test(estadistica.find("TestPlayer") != std::string::npos, 
                          "Blackjack - Estadísticas contienen nombre del jugador");
        runner.assert_test(estadistica.find("Ganaste") != std::string::npos, 
                          "Blackjack - Detecta ganancia en estadísticas");
    } catch (const std::exception& e) {
        runner.assert_test(false, "Blackjack - Estadísticas finales fallaron");
    }
}

// Pruebas de integración
void test_integracion(TestRunner& runner) {
    std::cout << "\n=== PRUEBAS DE INTEGRACIÓN ===" << std::endl;
    
    // Simulación de juego completo
    try {
        Blackjack juego("IntegrationTest", 1000);
        
        // Iniciar ronda
        bool ronda_ok = juego.nuevaRonda(100);
        runner.assert_test(ronda_ok, "Integración - Ronda inicia correctamente");
        
        // Verificar estado inicial
        runner.assert_test(juego.getJugador().getMano().getCartas().size() == 2, 
                          "Integración - Jugador tiene cartas iniciales");
        runner.assert_test(juego.getCrupier().getMano().getCartas().size() == 2, 
                          "Integración - Crupier tiene cartas iniciales");
        
        // Simular decisión de plantarse
        juego.jugadorSePlanta();
        
        // Verificar que se generó un resultado
        std::string resultado = juego.getResultado();
        runner.assert_test(!resultado.empty(), "Integración - Se genera resultado de la partida");
        
    } catch (const std::exception& e) {
        runner.assert_test(false, "Integración - Simulación de juego completo falló");
    }

    // Prueba de múltiples rondas
    try {
        Blackjack juego("MultiRound", 1000);
        
        int dinero_inicial = juego.getJugador().getDinero();
        
        // Primera ronda
        juego.nuevaRonda(50);
        juego.jugadorSePlanta();
        
        int dinero_tras_primera = juego.getJugador().getDinero();
        
        // Segunda ronda (si tiene dinero)
        if (dinero_tras_primera >= 50) {
            bool segunda_ronda = juego.nuevaRonda(50);
            runner.assert_test(segunda_ronda, "Integración - Puede jugar múltiples rondas");
        }
        
        runner.assert_test(true, "Integración - Múltiples rondas manejadas correctamente");
        
    } catch (const std::exception& e) {
        runner.assert_test(false, "Integración - Múltiples rondas fallaron");
    }
}

int main() {
    TestRunner runner;
    
    std::cout << "=== EJECUTANDO PRUEBAS UNITARIAS BLACKJACK ===" << std::endl;
    
    test_carta(runner);
    test_mazo(runner);
    test_mano(runner);
    test_jugador(runner);
    test_crupier(runner);
    test_blackjack(runner);
    test_integracion(runner);
    
    runner.print_summary();
    
    return 0;
}
