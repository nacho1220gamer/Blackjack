@echo off 
title Prueba de Dependencias - Blackjack 
echo Verificando dependencias... 
echo. 
echo Archivos en la carpeta: 
dir /b *.exe *.dll 
echo. 
echo Intentando ejecutar sin mostrar ventana de error... 
Blackjack.exe 2>nul || echo ERROR: Faltan dependencias 
pause 
