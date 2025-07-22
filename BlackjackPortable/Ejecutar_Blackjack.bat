@echo off 
title Blackjack Game - wxWidgets 
echo. 
echo ================================ 
echo    BLACKJACK GAME - wxWidgets 
echo ================================ 
echo. 
echo Iniciando juego... 
cd /d "%~dp0" 
if exist "Blackjack.exe" ( 
    start "" "Blackjack.exe" 
) else ( 
    echo ERROR: No se encuentra Blackjack.exe 
    pause 
) 
