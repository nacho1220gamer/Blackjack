
/**
 * @file MainFrame.cpp
 * @brief Ventana principal del menú del juego Blackjack
 * 
 * Este archivo implementa la clase MainFrame que proporciona la interfaz
 * principal del juego, mostrando el logo del Blackjack y los botones para
 * jugar o salir. Es la primera ventana que ve el usuario al iniciar la
 * aplicación y sirve como punto de entrada a todas las funcionalidades.
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "MainFrame.h"
#include "JuegoFrame.h"
#include "Estilos.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
	//panel
	wxPanel* panel = new wxPanel(this);
	panel->SetBackgroundColour(wxColour(139, 0, 0));
	wxBoxSizer* sizerpanel = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(sizerpanel);
	
	//logo
	wxImage logoImg("blackjack.png", wxBITMAP_TYPE_PNG);
	wxBitmap logoBitmap(logoImg.Scale(800, 300)); // escala
	wxStaticBitmap* logo = new wxStaticBitmap(panel, wxID_ANY, logoBitmap, wxPoint(50, 25), wxSize(800, 300));
	sizerpanel->Add(logo, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 30); //ajusta el contenido al tama�o de pantalla
	
	//boton de jugar
	wxButton* playbutton = new wxButton(panel, wxID_ANY, "JUGAR", wxPoint(300, 350), wxSize(300, 75));
	playbutton->Bind(wxEVT_BUTTON, &MainFrame::OnJugar, this);
	sizerpanel->Add(playbutton, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20); //ajusta el contenido al tama�o de pantalla
	Estilos::AplicarEstiloBoton(playbutton); //estilo del boton

	//boton de salir
	wxButton* leavebutton = new wxButton(panel, wxID_ANY, "SALIR", wxPoint(300, 450), wxSize(300, 75));
	leavebutton->Bind(wxEVT_BUTTON, &MainFrame::OnSalir, this);
	sizerpanel->Add(leavebutton, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20); //ajusta el contenido al tama�o de pantalla
	Estilos::AplicarEstiloBoton(leavebutton); //estilo del boton

	//cerrar juego
	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);


}

//funcion boton jugar
void MainFrame::OnJugar(wxCommandEvent& evt) {
	JuegoFrame* Juego = new JuegoFrame("Blackjack");
	Juego->Center();
	Juego->Show();
	this->Hide();
}

//funcion boton salir
void MainFrame::OnSalir(wxCommandEvent& evt) {
	wxTheApp->ExitMainLoop();
}

//funcion de salir del juego
void MainFrame::OnClose(wxCloseEvent& evt)
{
	wxTheApp->ExitMainLoop();  // cerrar toda la app
	evt.Skip();
}