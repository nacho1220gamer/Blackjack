/*
		Clase: MainFrame
		Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
		Universidad del Valle

		Información CRC:

		Clase: MainFrame
		Responsabilidades:
				- Gestionar la ventana principal de la aplicación.
				- Proporcionar la interfaz de entrada al juego.
				- Manejar eventos de navegación y cierre de la aplicación.

		Colaboradores:
				- JuegoFrame: Clase que representa la ventana del juego donde el usuario ingresa datos.
				- wxFrame: Clase base de wxWidgets para ventanas principales.
				- wxCommandEvent: Para manejo de eventos de botones y menús.

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
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void OnJugar(wxCommandEvent& evt);
	void OnSalir(wxCommandEvent& evt);
	void OnClose(wxCloseEvent& evt);
};

