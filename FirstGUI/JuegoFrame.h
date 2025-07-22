/*
		Clase: JuegoFrame
		Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
		Universidad del Valle

		Información CRC:

		Clase: JuegoFrame
		Responsabilidades:
				- Gestionar la ventana de configuración del juego.
				- Capturar información del jugador (nombre, dinero inicial, apuesta).
				- Validar datos de entrada antes de iniciar el juego.
				- Proporcionar navegación de regreso a la ventana principal.

		Colaboradores:
				- MainFrame: Ventana principal desde donde se accede a esta clase.
				- blackjackgameframe: Ventana del juego que se abre tras confirmar los datos.
				- wxFrame: Clase base de wxWidgets para ventanas.
				- wxTextCtrl: Controles de entrada de texto para datos del usuario.

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

class JuegoFrame : public wxFrame
{
public:
	JuegoFrame(const wxString& title);
private:
	wxTextCtrl* nombreCtrl;
	wxTextCtrl* dineroCtrl;
	wxTextCtrl* apuestaCtrl;
	void OnVolver(wxCommandEvent& evt);
	void OnClose(wxCloseEvent& evt);
	void OnConfirmar(wxCommandEvent& evt);
};

