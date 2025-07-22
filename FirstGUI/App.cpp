/**
 * @file App.cpp
 * @brief Punto de entrada principal de la aplicación Blackjack
 * 
 * Este archivo contiene la clase App que hereda de wxApp y maneja la inicialización
 * de la aplicación GUI del juego Blackjack. Se encarga de crear la ventana principal
 * y configurar los manejadores de imágenes necesarios para el juego.
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "App.h"
#include "MainFrame.h"
#include "JuegoFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	wxInitAllImageHandlers();
	MainFrame* mainFrame = new MainFrame("Menu BlackJack");
	mainFrame->SetClientSize(900, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}