/*
    Clase: Estilos (namespace)
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Información CRC:

    Clase: Estilos
    Responsabilidades:
        - Proporcionar funciones de estilizado consistente para elementos de la interfaz.
        - Aplicar estilos personalizados a controles de texto, botones y etiquetas.
        - Mantener la coherencia visual en toda la aplicación.
        - Centralizar la configuración de colores, fuentes y apariencia.

    Colaboradores:
        - wxTextCtrl: Controles de entrada de texto que reciben estilizado.
        - wxButton: Botones que reciben estilos personalizados.
        - wxStaticText: Etiquetas de texto que reciben formateo.
        - MainFrame, JuegoFrame, blackjackgameframe: Ventanas que utilizan estos estilos.

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

namespace Estilos{

    inline void AplicarEstiloTextCtrl(wxTextCtrl* entrada) {
        // Fondo elegante oscuro
        entrada->SetBackgroundColour(wxColour(30, 30, 30));

        // Texto en dorado
        entrada->SetForegroundColour(wxColour(212, 175, 55));

        // Fuente en cursiva y negrita, tama�o 14
        wxFont font = entrada->GetFont();
        font.SetPointSize(14);
        font.SetStyle(wxFONTSTYLE_ITALIC);
        font.SetWeight(wxFONTWEIGHT_BOLD);
        entrada->SetFont(font);

        // (Opcional) Sin borde 3D cl�sico
        entrada->SetWindowStyle(wxBORDER_NONE);
    }

    inline void AplicarEstiloBoton(wxButton* entrada) {
        wxColour dorado(250, 160, 23); // fondo dorado
        entrada->SetBackgroundColour(dorado);
        entrada->SetForegroundColour(*wxWHITE); // texto blanco
        wxFont font = entrada->GetFont();
        font.SetPointSize(20);
        font.SetWeight(wxFONTWEIGHT_BOLD);
        entrada->SetFont(font);
    }

    inline void AplicarEstiloBotonpeque�o(wxButton* entrada) {
        wxColour dorado(250, 160, 23); // fondo dorado
        entrada->SetBackgroundColour(dorado);
        entrada->SetForegroundColour(*wxWHITE); // texto blanco
        wxFont font = entrada->GetFont();
        font.SetPointSize(10);
        font.SetWeight(wxFONTWEIGHT_BOLD);
        entrada->SetFont(font);
    }

    inline void AplicarEstiloTexto(wxStaticText* entrada) {
        wxFont font = entrada->GetFont();
        font.SetPointSize(25);
        font.SetWeight(wxFONTWEIGHT_BOLD);
        entrada->SetFont(font);
        entrada->SetForegroundColour(*wxWHITE);
    }
    inline void AplicarEstiloparrafo(wxStaticText* entrada) {
        wxFont font = entrada->GetFont();
        font.SetPointSize(15);
        font.SetWeight(wxFONTWEIGHT_BOLD);
        entrada->SetFont(font);
        entrada->SetForegroundColour(*wxWHITE);
    }
}
