/**
 * @file JuegoFrame.cpp
 * @brief Ventana de configuración inicial del juego Blackjack
 * 
 * Este archivo implementa la clase JuegoFrame que proporciona la interfaz gráfica
 * para que el jugador ingrese su nombre, dinero inicial y apuesta antes de comenzar
 * a jugar. Valida los datos ingresados y crea la ventana principal del juego.
 * Utiliza wxWidgets para crear una interfaz intuitiva y atractiva.
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "JuegoFrame.h"
#include "blackjackgameframe.h"
#include "MainFrame.h"
#include "Estilos.h"

JuegoFrame::JuegoFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(900, 600)) {
    //panel
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(139, 0, 0));
    wxBoxSizer* sizerpanel = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizerpanel);
    sizerpanel->AddSpacer(30);

    //boton de volver
    wxButton* backbutton = new wxButton(panel, wxID_ANY, "VOLVER AL MEN�", wxPoint(25, 25), wxSize(150, 50));
    backbutton->Bind(wxEVT_BUTTON, &JuegoFrame::OnVolver, this);
    Estilos::AplicarEstiloBotonpeque�o(backbutton);

    //cerrar juego
    Bind(wxEVT_CLOSE_WINDOW, &JuegoFrame::OnClose, this);


    //nombre
    wxStaticText* statictextnombre= new wxStaticText(panel, wxID_ANY, "Ingrese su nombre", wxDefaultPosition);
    sizerpanel->Add(statictextnombre, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloTexto(statictextnombre);
    nombreCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, 40));
    sizerpanel->Add(nombreCtrl, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloTextCtrl(nombreCtrl);

    //dinero
    wxStaticText* statictextdinero = new wxStaticText(panel, wxID_ANY, "Ingrese su dinero", wxDefaultPosition);
    sizerpanel->Add(statictextdinero, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloTexto(statictextdinero);
    dineroCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, 40));
    sizerpanel->Add(dineroCtrl, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloTextCtrl(dineroCtrl);

    //apuesta
    wxStaticText* statictextapuesta = new wxStaticText(panel, wxID_ANY, "Cantidad de dinero a apostar", wxDefaultPosition);
    sizerpanel->Add(statictextapuesta, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloTexto(statictextapuesta);
    apuestaCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, 40));
    sizerpanel->Add(apuestaCtrl, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloTextCtrl(apuestaCtrl);

    //boton de confirmar
    wxButton* confirmbutton = new wxButton(panel, wxID_ANY, "CONFIRMAR", wxDefaultPosition, wxSize(200, 50));
    confirmbutton->Bind(wxEVT_BUTTON, &JuegoFrame::OnConfirmar, this);
    sizerpanel->Add(confirmbutton, 0, wxALIGN_CENTER | wxTOP, 40); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloBoton(confirmbutton);


}

//funcion boton de volver
void JuegoFrame::OnVolver(wxCommandEvent& evt) {
    MainFrame* lobby = new MainFrame("Men�");
    lobby->SetClientSize(900, 600);
    lobby->Center();
    lobby->Show();
    this->Hide();
}

//funcion boton confirmar
void JuegoFrame::OnConfirmar(wxCommandEvent& evt) {
    wxString nombre = nombreCtrl->GetValue();
    wxString dineroStr = dineroCtrl->GetValue();
    wxString apuestaStr = apuestaCtrl->GetValue();

    long dinero, apuesta;
    if (!dineroStr.ToLong(&dinero) || dinero <= 0) {
        wxMessageBox("El dinero debe ser un n�mero mayor que 0", "Error", wxICON_ERROR);
        return;
    }
    if (!apuestaStr.ToLong(&apuesta) || apuesta <= 0 || apuesta > dinero) {
        wxMessageBox("La apuesta debe ser un n�mero positivo y menor o igual al dinero", "Error", wxICON_ERROR);
        return;
    }

    blackjackgameframe* blackjack = new blackjackgameframe("Blackjack", nombre.ToStdString(), dinero, apuesta);
    blackjack->Center();
    blackjack->Show();
    this->Hide();
}

//funcion de salir del juego
void JuegoFrame::OnClose(wxCloseEvent& evt)
{
    wxTheApp->ExitMainLoop();  // cerrar toda la app
    evt.Skip();
}