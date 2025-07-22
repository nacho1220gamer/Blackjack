/**
 * @file blackjackgameframe.cpp
 * @brief Ventana principal del juego Blackjack
 * 
 * Este archivo implementa la clase blackjackgameframe que maneja toda la lógica
 * de la interfaz gráfica del juego de Blackjack. Incluye la presentación de reglas,
 * saludos de los personajes, el gameplay principal con cartas visuales,
 * manejo de apuestas, determinación de ganadores y estadísticas finales.
 * Es el corazón de la experiencia de juego del usuario.
 * 
 * @author [Ignacio Henao, Juan Camilo Ramos, Samuel Saldaña, Juan Manuel Muñoz]
 * @mail [ignacio.henao@correounivalle.edu.co, juan.ramos.hoyos@correounivalle.edu.co, saldana.samuel@correounivalle.edu.co, juan.munoz.delgado@correounivalle.edu.co]
 */

#include "blackjackgameframe.h"
#include "MainFrame.h"
#include "Estilos.h"

blackjackgameframe::blackjackgameframe(const wxString& title, const std::string& nombreJugador, int dineroInicial, int apuestaInicial) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(900, 600)),juego(nombreJugador, dineroInicial), mazo() {
    
    panelFinal = nullptr;
    
    if (!juego.nuevaRonda(apuestaInicial)) {
        wxMessageBox("No se pudo iniciar la ronda. Verifica que tengas suficiente dinero para apostar.", "Error", wxICON_ERROR);
        Close(); // Cierra la ventana si la ronda no se puede iniciar
        return;
    }

    //panel reglas
    panelreglas = new wxPanel(this);
    panelreglas->SetBackgroundColour(wxColour(139, 0, 0));
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mainSizer);
    mainSizer->Add(panelreglas, 1, wxEXPAND);
    wxBoxSizer* sizerpanel = new wxBoxSizer(wxVERTICAL);
    panelreglas->SetSizer(sizerpanel);

    wxStaticText* statictextreglas = new wxStaticText(panelreglas, wxID_ANY,
        "Reglas del juego:\n\n"
        "1. El objetivo es obtener una mano con valor m�s cercano a 21 que el crupier sin pasarse.\n"
        "2. Las cartas num�ricas (2-10) valen su valor num�rico.\n"
        "3. Las figuras (J, Q, K) valen 10 puntos.\n"
        "4. El As puede valer 11 o 1 (se ajusta autom�ticamente).\n"
        "5. Blackjack (As + carta de 10) paga 3:2.\n"
        "6. El crupier debe pedir cartas hasta tener al menos 17.\n"
        "7. Si te pasas de 21, pierdes autom�ticamente.\n",
        wxPoint(25, 100));
    sizerpanel->Add(statictextreglas, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 100); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloparrafo(statictextreglas);

    //boton de continuar 1
    wxButton* nextbutton = new wxButton(panelreglas, wxID_ANY, "Entendido", wxDefaultPosition, wxSize(200, 50));
    nextbutton->Bind(wxEVT_BUTTON, &blackjackgameframe::Oncontinuar, this);
    sizerpanel->Add(nextbutton, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 0); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloBoton(nextbutton);

    //panel saludo
    panelsaludo = new wxPanel(this);
    panelsaludo->SetBackgroundColour(wxColour(139, 0, 0));
    panelsaludo->Hide();
    mainSizer->Add(panelsaludo, 1, wxEXPAND);
    wxBoxSizer* sizersaludo = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizerhorizontal1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizerhorizontal2 = new wxBoxSizer(wxHORIZONTAL);
    panelsaludo->SetSizer(sizersaludo);
    sizersaludo->Add(sizerhorizontal1, 1, wxEXPAND | wxALL, 10);
    sizersaludo->Add(sizerhorizontal2, 1, wxEXPAND | wxALL, 10);

    sizerhorizontal1->AddStretchSpacer(1); //empuja a la derecha

    //saludo crupier
    juego.getCrupier().saludar();
    saludocrupier = new wxStaticText(panelsaludo, wxID_ANY, juego.getCrupier().getsaludo(), wxPoint(25, 100));
    sizerhorizontal1->Add(saludocrupier, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT | wxTOP, 30);//ajusta el contenido al tama�o de pantalla
    saludocrupier->Wrap(200);
    Estilos::AplicarEstiloTexto(saludocrupier);
    
    cargarperfiles(panelsaludo, sizerhorizontal1, juego.getCrupier().getNombre());

    wxImage perfilImg("perfiles/Jugador.png", wxBITMAP_TYPE_PNG);
    wxBitmap perfilBitmap(perfilImg.Scale(200, 200)); // escala
    wxStaticBitmap* perfil = new wxStaticBitmap(panelsaludo, wxID_ANY, perfilBitmap, wxPoint(700, 25), wxSize(200, 200));
    sizerhorizontal2->Add(perfil, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

    //saludo jugador
    juego.getJugador().saludar();
    saludojugador = new wxStaticText(panelsaludo, wxID_ANY, juego.getJugador().getsaludo(), wxPoint(25, 100));
    sizerhorizontal2->Add(saludojugador, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10); //ajusta el contenido al tama�o de pantalla
    saludojugador->Wrap(200);
    Estilos::AplicarEstiloTexto(saludojugador);

    //boton de continuar 2
    wxButton* nextbutton2 = new wxButton(panelsaludo, wxID_ANY, "Continuar", wxDefaultPosition, wxSize(200, 50));
    nextbutton2->Bind(wxEVT_BUTTON, &blackjackgameframe::MostrarJuego, this);
    sizersaludo->Add(nextbutton2, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 30); //ajusta el contenido al tama�o de pantalla
    Estilos::AplicarEstiloBoton(nextbutton2);

    //panel juego
    paneljuego = new wxPanel(this);
    paneljuego->SetBackgroundColour(wxColour(139, 0, 0));
    paneljuego->Hide();
    mainSizer->Add(paneljuego, 1, wxEXPAND);
    wxBoxSizer* sizerJuego = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    paneljuego->SetSizer(sizerJuego);
    sizerJuego->Add(topSizer, 0, wxEXPAND | wxALL, 25);
    topSizer->AddStretchSpacer(1); //empuja a la derecha

    //panel de cartas del jugador
    panelCartasJugador = new wxPanel(paneljuego);
    panelCartasJugador->SetBackgroundColour(wxColour(139, 0, 0));
    panelCartasJugador->SetSize(wxRect(0, 300, 900, 200));

    //panel de cartas del crupier
    panelCartasCrupier = new wxPanel(paneljuego);
    panelCartasCrupier->SetBackgroundColour(wxColour(139, 0, 0));
    panelCartasCrupier->SetSize(wxRect(0, 100, 900, 160));

    //boton de volver
    wxButton* backbutton = new wxButton(paneljuego, wxID_ANY, "VOLVER AL MEN�", wxPoint(25, 25), wxSize(150, 50));
    backbutton->Bind(wxEVT_BUTTON, &blackjackgameframe::OnVolver, this);
    Estilos::AplicarEstiloBotonpeque�o(backbutton);

    //boton de pedir carta
    botonPedirCarta = new wxButton(paneljuego, wxID_ANY, "Pedir carta", wxPoint(200, 25), wxSize(150, 50));
    botonPedirCarta->Bind(wxEVT_BUTTON, &blackjackgameframe::OnPedirCarta, this);
    topSizer->Add(botonPedirCarta, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 20);
    Estilos::AplicarEstiloBoton(botonPedirCarta);

    //boton de plantarse
    botonPlantarse = new wxButton(paneljuego, wxID_ANY, "Plantarse", wxPoint(400, 25), wxSize(150, 50));
    botonPlantarse->Bind(wxEVT_BUTTON, &blackjackgameframe::OnPlantarse, this);
    topSizer->Add(botonPlantarse, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 100);
    Estilos::AplicarEstiloBoton(botonPlantarse);

    //moneda
    wxImage monedaImg("moneda.png", wxBITMAP_TYPE_PNG);
    wxBitmap monedaBitmap(monedaImg.Scale(50, 50)); // escala
    wxStaticBitmap* moneda = new wxStaticBitmap(paneljuego, wxID_ANY, monedaBitmap, wxPoint(700, 25), wxSize(50, 50));
    topSizer->Add(moneda, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

    //dinero
    dineroInicialJugador = dineroInicial;
    int dineroActual = juego.getJugador().getDinero();
    statictextdinero = new wxStaticText(paneljuego, wxID_ANY, std::to_string(dineroActual), wxPoint(750, 25));
    topSizer->Add(statictextdinero, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    Estilos::AplicarEstiloTexto(statictextdinero);

    //cerrar juego
    Bind(wxEVT_CLOSE_WINDOW, &blackjackgameframe::OnClose, this);

    mazo.barajar();
}

//funcion boton de continuar 1

void blackjackgameframe::Oncontinuar(wxCommandEvent& evt) {
    panelreglas->Hide();
    panelsaludo->Show();
    actualizarInterfaz();
    Layout();
}

//funcion boton de continuar 2
void blackjackgameframe::MostrarJuego(wxCommandEvent& evt) {
    panelsaludo->Hide();
    paneljuego->Show();
    actualizarInterfaz();
    Layout();
}

//funcion boton de volver
void blackjackgameframe::OnVolver(wxCommandEvent& evt) {
    MainFrame* lobby = new MainFrame("Men�");
    lobby->SetClientSize(900, 600);
    lobby->Center();
    lobby->Show();
    this->Hide();
}

void blackjackgameframe::cargarperfiles(wxPanel* panel, wxSizer* sizer, const std::string& nombreCrupier) {
    std::string rutaImagen = "perfiles/" + nombreCrupier + ".png";
    wxString rutaWx = wxString::FromUTF8(rutaImagen);

    wxStaticBitmap* crupier = nullptr;

    if (wxFileExists(rutaWx)) {
        wxImage img(rutaWx, wxBITMAP_TYPE_PNG);
        if (img.IsOk()) {
            wxBitmap bitmap(img.Scale(200, 200));
            crupier = new wxStaticBitmap(panel, wxID_ANY, bitmap,
                wxPoint(700, 25), wxSize(200, 200));
        }
    }

    sizer->Add(crupier, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

}

void blackjackgameframe::OnPedirCarta(wxCommandEvent& event) {
    Carta carta = mazo.repartirCarta();
    juego.getJugador().recibirCarta(carta);
    actualizarInterfaz();

    if (juego.getJugador().sePaso()) {
        wxMessageBox("Te pasaste de 21. Pierdes.");
        terminarTurnoJugador();
    }
    else if (juego.getJugador().tieneBlackjack()) {
        wxMessageBox("�Blackjack!");
        terminarTurnoJugador();
    }
}

void blackjackgameframe::OnPlantarse(wxCommandEvent& event) {
    terminarTurnoJugador();
}

void blackjackgameframe::terminarTurnoJugador() {
    mostrarCartaOcultaCrupier = false;
    turnoCrupier();
    determinarGanador();
}

void blackjackgameframe::turnoCrupier() {
    while (juego.getCrupier().getValorMano() < 17) {
        juego.getCrupier().recibirCarta(mazo.repartirCarta());
    }
    actualizarInterfaz(); // mostrar todas las cartas del crupier
}

void blackjackgameframe::determinarGanador() {
    juego.determinarResultado();
   // Mostrar resultado
    wxMessageBox(juego.getResultado());
    entregardinero();
}

void blackjackgameframe::entregardinero() {
    // Actualizar visualmente el texto del dinero
    statictextdinero->SetLabel(std::to_string(juego.getJugador().getDinero()));
    paneljuego->Refresh();
    if (juego.getJugador().getDinero() <= 0) {
        MostrarPanelFinal();
        return;
    }
    this->abrirpanelnuevaronda();
}

wxBitmap blackjackgameframe::cargarImagenCarta(const Carta& carta) {
    std::string archivo = "cartas/" + carta.getTipo() + carta.getPalo() + ".png";
    wxImage img(archivo, wxBITMAP_TYPE_PNG);
    if (!img.IsOk()) {
        wxLogError("No se pudo cargar la imagen: %s", archivo);
        return wxBitmap(120, 160);  // Imagen vac�a si falla
    }
    return wxBitmap(img.Scale(120, 160));
}

wxBitmap blackjackgameframe::cargarImagenReverso() {
    std::string archivo = "cartas/reverso.png";
    wxImage img(archivo, wxBITMAP_TYPE_PNG);
    if (!img.IsOk()) {
        wxLogError("No se pudo cargar el reverso: %s", archivo);
        return wxBitmap(120, 160);
    }
    return wxBitmap(img.Scale(120, 160));
}

void blackjackgameframe::actualizarInterfaz() {
    // Limpiar panel de cartas del jugador
    panelCartasJugador->DestroyChildren();

    // Redibujar cartas del jugador
    const std::vector<Carta>& cartasJugador = juego.getJugador().getMano().getCartas();
    int xJugador = 100;
    for (const auto& carta : cartasJugador) {
        std::string archivo = "cartas/" + carta.getTipo() + carta.getPalo() + ".png";
        wxImage img(archivo, wxBITMAP_TYPE_PNG);
        wxBitmap bmp(img.Scale(120, 160));
        new wxStaticBitmap(panelCartasJugador, wxID_ANY, bmp, wxPoint(xJugador, 0));
        xJugador += 120;
    }

    panelCartasJugador->Layout();
    panelCartasJugador->Refresh();


    // Mostrar cartas del crupier
    panelCartasCrupier->DestroyChildren();

    const std::vector<Carta>& cartasCrupier = juego.getCrupier().getMano().getCartas();
    int xCrupier = 100;
    for (size_t i = 0; i < cartasCrupier.size(); ++i) {
        wxBitmap bmp;
        if (i == 0 && mostrarCartaOcultaCrupier) {
            wxImage img("cartas/reverso.png", wxBITMAP_TYPE_PNG);
            bmp = wxBitmap(img.Scale(120, 160));
        }
        else {
            std::string archivo = "cartas/" + cartasCrupier[i].getTipo() + cartasCrupier[i].getPalo() + ".png";
            wxImage img(archivo, wxBITMAP_TYPE_PNG);
            bmp = wxBitmap(img.Scale(120, 160));
        }

        new wxStaticBitmap(panelCartasCrupier, wxID_ANY, bmp, wxPoint(xCrupier, 0));
        xCrupier += 120;
    }
    panelCartasCrupier->Layout();
    panelCartasCrupier->Refresh();
    }

void blackjackgameframe::abrirpanelnuevaronda() {
wxDialog* dialogo = new wxDialog(this, wxID_ANY, "Nueva ronda", wxDefaultPosition, wxSize(400, 320), wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP);
    dialogo->SetBackgroundColour(wxColour(120, 0, 0));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* texto = new wxStaticText(dialogo, wxID_ANY, "�Deseas jugar otra ronda?");
    sizer->Add(texto, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);
    Estilos::AplicarEstiloparrafo(texto);

    wxBoxSizer* botonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* btnNuevaRonda = new wxButton(dialogo, wxID_ANY, "Nueva Ronda");
    wxButton* btnSalir = new wxButton(dialogo, wxID_CANCEL, "Terminar juego");

    Estilos::AplicarEstiloBotonpeque�o(btnNuevaRonda);
    Estilos::AplicarEstiloBotonpeque�o(btnSalir);

    botonSizer->Add(btnNuevaRonda, 0, wxALL, 10);
    botonSizer->Add(btnSalir, 0, wxALL, 10);
    sizer->Add(botonSizer, 0, wxALIGN_CENTER);

    // Elementos para la nueva apuesta (inicialmente ocultos)
    wxStaticText* lblApuesta = new wxStaticText(dialogo, wxID_ANY, "Nueva apuesta:");
    Estilos::AplicarEstiloparrafo(lblApuesta);
    wxTextCtrl* txtApuesta = new wxTextCtrl(dialogo, wxID_ANY, "", wxDefaultPosition, wxSize(100, -1));
    Estilos::AplicarEstiloTextCtrl(txtApuesta);
    wxButton* btnConfirmar = new wxButton(dialogo, wxID_OK, "Confirmar");
    Estilos::AplicarEstiloBotonpeque�o(btnConfirmar);

    lblApuesta->Hide();
    txtApuesta->Hide();
    btnConfirmar->Hide();

    sizer->AddSpacer(15);
    sizer->Add(lblApuesta, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    sizer->Add(txtApuesta, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    sizer->Add(btnConfirmar, 0, wxALIGN_CENTER);

    dialogo->SetSizer(sizer);
    dialogo->Layout();
    dialogo->CentreOnParent();

    // Evento para mostrar campo de apuesta y bot�n Confirmar
    btnNuevaRonda->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
        lblApuesta->Show();
        txtApuesta->Show();
        btnConfirmar->Show();
        dialogo->Layout();
    });

    // Evento al confirmar
    btnConfirmar->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
        wxString nuevaapuestaStr = txtApuesta->GetValue();
        long nuevaapuesta;  // usamos 'long' porque wxString::ToLong devuelve un long
        if (nuevaapuestaStr.ToLong(&nuevaapuesta) && nuevaapuesta > 0) {
            if (juego.nuevaRonda(static_cast<int>(nuevaapuesta))) {
                mostrarCartaOcultaCrupier = true;
                actualizarInterfaz();
                statictextdinero->SetLabel(std::to_string(juego.getJugador().getDinero())); // actualiza dinero visible
                mazo.barajar();
                dialogo->EndModal(wxID_OK);
            }
            else {
                wxMessageBox("No tienes suficiente dinero para esa apuesta.", "Error", wxICON_ERROR);
            }
        }
        else {
            wxMessageBox("Por favor ingresa una apuesta v�lida (n�mero mayor que 0).", "Error", wxICON_ERROR);
            txtApuesta->SetFocus();
            txtApuesta->Refresh();
        }
    });

    int resultado = dialogo->ShowModal();

    if (resultado == wxID_OK) {
       
       

        
    }

    if (resultado == wxID_CANCEL) {
        MostrarPanelFinal();
    }

    dialogo->Destroy();
}

void blackjackgameframe::MostrarPanelFinal() {
    // Oculta el panel de juego actual
    if (paneljuego) paneljuego->Hide();

    //muestra el panel final
    if (!panelFinal) {
        panelFinal = new wxPanel(this);
        panelFinal->SetBackgroundColour(wxColour(139, 0, 0));

        wxBoxSizer* sizerPanel = new wxBoxSizer(wxVERTICAL);

        wxStaticText* titulo = new wxStaticText(panelFinal, wxID_ANY, "�Fin del juego!", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
        sizerPanel->Add(titulo, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);
        Estilos::AplicarEstiloTexto(titulo);

        juego.MostrarEstadisticasFinales(juego.getJugador().getNombre(), dineroInicialJugador, juego.getJugador().getDinero());

        wxStaticText* estadisticas = new wxStaticText(panelFinal, wxID_ANY, juego.getEstadistica(), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
        sizerPanel->Add(estadisticas, 0, wxALIGN_CENTER | wxBOTTOM, 20);
        Estilos::AplicarEstiloparrafo(estadisticas);

        wxStaticText* statictextcreditos = new wxStaticText(panelFinal, wxID_ANY,
            "�Gracias por jugar Blackjack!\n"
            "Desarrollado por : \n"
            "- Ignacio Henao\n"
            "- Samuel Salda�a\n"
            "- Juan Camilo Ramos\n"
            "- Juan Manuel Mu�oz\n"
            "Universidad del Valle - FPOO\n",
            wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
        sizerPanel->Add(statictextcreditos, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);
        Estilos::AplicarEstiloparrafo(statictextcreditos);

        wxButton* volverBtn = new wxButton(panelFinal, wxID_ANY, "Volver al men�");
        sizerPanel->Add(volverBtn, 0, wxALIGN_CENTER | wxALL, 10);
        volverBtn->Bind(wxEVT_BUTTON, &blackjackgameframe::OnVolver, this);
        Estilos::AplicarEstiloBoton(volverBtn);

        panelFinal->SetSizer(sizerPanel);
    }

    // Sizer del frame principal
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(panelFinal, 1, wxEXPAND | wxALL, 0);
    this->SetSizer(mainSizer);
    this->Layout();

    panelFinal->Show();
}

//funcion de salir del juego
void blackjackgameframe::OnClose(wxCloseEvent& evt)
{
    wxTheApp->ExitMainLoop();  // cerrar toda la app
    evt.Skip();
}
