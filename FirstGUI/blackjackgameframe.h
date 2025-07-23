/*
		Clase: blackjackgameframe
		Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
		Universidad del Valle

		Información CRC:

		Clase: blackjackgameframe
		Responsabilidades:
				- Gestionar la interfaz gráfica principal del juego de Blackjack.
				- Controlar el flujo del juego (repartir cartas, turnos, determinar ganadores).
				- Visualizar las cartas del jugador y crupier mediante imágenes.
				- Manejar la lógica de apuestas y dinero del jugador.
				- Proporcionar controles interactivos (pedir carta, plantarse).
				- Mostrar paneles informativos (reglas, saludo, estado del juego).

		Colaboradores:
				- Blackjack: Clase que contiene la lógica principal del juego.
				- Mazo: Clase que maneja el conjunto de cartas disponibles.
				- Carta: Representa cada carta individual del juego.
				- JuegoFrame: Ventana anterior desde donde se obtienen los datos iniciales.
				- wxFrame: Clase base de wxWidgets para la ventana del juego.
				- wxPanel: Paneles para organizar diferentes secciones de la interfaz.
				- wxStaticBitmap: Para mostrar las imágenes de las cartas.

		Este es un proyecto del curso FPOO de la Universidad del Valle, 
		desarrollado con fines académicos. Puede ser utilizado con fines 
		académicos dando los créditos de la autoría.
		Autor: Victor Bucheli
		Correo: victor.bucheli@correounivalle.edu.co
		@author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz ]
		@mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co , 
		saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co ]
*/

#pragma once
#include <wx/wx.h>
#include "Blackjack.h"

class blackjackgameframe : public wxFrame
{
public:
	blackjackgameframe(const wxString& title, const std::string& nombreJugador, int dineroInicial, int apuestaInicial);
private:
	Blackjack juego;
	Mazo mazo;
	bool mostrarCartaOcultaCrupier = true;
	int dineroInicialJugador;
	wxPanel* panelreglas;
	wxPanel* panelsaludo;
	wxPanel* paneljuego;
	wxPanel* panelCartasJugador;
	wxPanel* panelCartasCrupier;
	wxPanel* panelFinal;
	wxStaticText* saludojugador;
	wxStaticText* saludocrupier;
	wxStaticText* statictextdinero;
	wxButton* botonPedirCarta;
	wxButton* botonPlantarse;
	wxBitmap cargarImagenCarta(const Carta& carta);
	wxBitmap cargarImagenReverso();
	std::vector<wxStaticBitmap*> imagenesCartas;
	void Oncontinuar(wxCommandEvent& evt);
	void cargarperfiles(wxPanel* panel, wxSizer* sizer, const std::string& nombreCrupier);
	void MostrarJuego(wxCommandEvent& evt);
	void OnVolver(wxCommandEvent& evt);
	void OnPedirCarta(wxCommandEvent& event);
	void OnPlantarse(wxCommandEvent& event);
	void turnoCrupier();
	void determinarGanador();
	void entregardinero();
	void abrirpanelnuevaronda();
	void MostrarPanelFinal();
	void actualizarInterfaz();
	void terminarTurnoJugador();
	void OnClose(wxCloseEvent& evt);
};

