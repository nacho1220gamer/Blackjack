/**
		Clase: App 
		Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
		Universidad del Valle

		Información CRC:

		Clase: App

		Responsabilidades:
			- Gestiona el inicio de la interfaz gráfica del juego.

		Colaboradores:
				- MainFrame: Clase que representa la ventana principal del juego.
				- JuegoFrame: Clase que representa la ventana del juego.
				- wxApp: Clase base de wxWidgets para la aplicación.
				- wxFrame: Clase base de wxWidgets para la ventana principal.

		@author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
		@mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co,
					 saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
*/

#pragma once
#include <wx/wx.h>
class App : public wxApp
{
public:
	bool OnInit();
};

