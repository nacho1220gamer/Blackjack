@echo off
:: Script para crear versión portable del juego Blackjack
:: Para proyecto FirstGUI en Visual Studio con wxWidgets

echo ============================================
echo  EXPORTADOR DE JUEGO BLACKJACK - wxWidgets
echo ============================================
echo.

:: Verificar que estamos en el directorio correcto
if not exist "FirstGUI.sln" (
    echo ERROR: No se encuentra FirstGUI.sln en este directorio
    echo.
    echo Asegurate de ejecutar este script en la carpeta donde esta FirstGUI.sln
    echo.
    pause
    exit /b 1
)

echo Proyecto encontrado: FirstGUI.sln
echo.

:: Crear carpeta de distribución
if exist "BlackjackPortable" rmdir /s /q "BlackjackPortable"
mkdir "BlackjackPortable"

echo Buscando ejecutable compilado...

:: Buscar el ejecutable en diferentes configuraciones
set FOUND_EXE=0
set SOURCE_DIR=""

:: Buscar en Release x64 (preferido)
if exist "x64\Release\FirstGUI.exe" (
    copy "x64\Release\FirstGUI.exe" "BlackjackPortable\Blackjack.exe" >nul
    echo [✓] Encontrado: x64\Release\FirstGUI.exe
    set FOUND_EXE=1
    set SOURCE_DIR=x64\Release
    goto :found_exe
)

:: Buscar en Release x64 sin extensión (Windows a veces no la muestra)
if exist "x64\Release\FirstGUI" (
    copy "x64\Release\FirstGUI" "BlackjackPortable\Blackjack.exe" >nul
    echo [✓] Encontrado: x64\Release\FirstGUI
    set FOUND_EXE=1
    set SOURCE_DIR=x64\Release
    goto :found_exe
)

:: Buscar en ruta con FirstGUI\
if exist "FirstGUI\x64\Release\FirstGUI.exe" (
    copy "FirstGUI\x64\Release\FirstGUI.exe" "BlackjackPortable\Blackjack.exe" >nul
    echo [✓] Encontrado: FirstGUI\x64\Release\FirstGUI.exe
    set FOUND_EXE=1
    set SOURCE_DIR=FirstGUI\x64\Release
    goto :found_exe
)

:: Buscar en Release Win32
if exist "FirstGUI\Release\FirstGUI.exe" (
    copy "FirstGUI\Release\FirstGUI.exe" "BlackjackPortable\Blackjack.exe" >nul
    echo [✓] Encontrado: FirstGUI\Release\FirstGUI.exe
    set FOUND_EXE=1
    set SOURCE_DIR=FirstGUI\Release
    goto :found_exe
)

:: Buscar en Debug x64
if exist "FirstGUI\x64\Debug\FirstGUI.exe" (
    copy "FirstGUI\x64\Debug\FirstGUI.exe" "BlackjackPortable\Blackjack.exe" >nul
    echo [⚠] Encontrado (Debug): FirstGUI\x64\Debug\FirstGUI.exe
    set FOUND_EXE=1
    set SOURCE_DIR=FirstGUI\x64\Debug
    goto :found_exe
)

:: Buscar en Debug Win32
if exist "FirstGUI\Debug\FirstGUI.exe" (
    copy "FirstGUI\Debug\FirstGUI.exe" "BlackjackPortable\Blackjack.exe" >nul
    echo [⚠] Encontrado (Debug): FirstGUI\Debug\FirstGUI.exe
    set FOUND_EXE=1
    set SOURCE_DIR=FirstGUI\Debug
    goto :found_exe
)

:: Si no se encontró el ejecutable
echo.
echo [✗] ERROR: No se encontró FirstGUI.exe
echo.
echo SOLUCION:
echo 1. Abre Visual Studio
echo 2. Abre FirstGUI.sln
echo 3. Cambia a modo "Release" (arriba donde dice Debug/Release)
echo 4. Ve a Build ^> Build Solution (o presiona F7)
echo 5. Ejecuta este script nuevamente
echo.
echo El ejecutable debería crearse en una de estas ubicaciones:
echo - FirstGUI\Release\FirstGUI.exe
echo - FirstGUI\x64\Release\FirstGUI.exe
echo.
pause
exit /b 1

:found_exe
echo.
echo Copiando dependencias desde: %SOURCE_DIR%
echo.

:: Copiar DLLs que estén junto al ejecutable
echo Buscando DLLs en directorio del ejecutable...
set DLL_COUNT=0
for %%f in ("%SOURCE_DIR%\*.dll") do (
    copy "%%f" "BlackjackPortable\" >nul 2>&1
    if exist "BlackjackPortable\%%~nxf" (
        echo   [✓] %%~nxf
        set /a DLL_COUNT+=1
    )
)

if %DLL_COUNT%==0 (
    echo   [i] No se encontraron DLLs en el directorio del ejecutable
)

:: Buscar wxWidgets DLLs en ubicaciones comunes
echo.
echo Buscando wxWidgets DLLs...
set WX_FOUND=0

:: Buscar en vcpkg
for /d %%d in ("C:\vcpkg\installed\x64-windows\bin" "C:\vcpkg\installed\x86-windows\bin") do (
    if exist "%%d" (
        for %%f in ("%%d\wxmsw*.dll" "%%d\wxbase*.dll") do (
            if exist "%%f" (
                copy "%%f" "BlackjackPortable\" >nul 2>&1
                if exist "BlackjackPortable\%%~nxf" (
                    echo   [✓] %%~nxf (vcpkg)
                    set WX_FOUND=1
                )
            )
        )
    )
)

:: Buscar en instalaciones de wxWidgets
for /d %%d in ("C:\wxWidgets*\lib\vc_*dll" "C:\wxWidgets*\lib\vc*_dll") do (
    if exist "%%d" (
        for %%f in ("%%d\wxmsw*.dll" "%%d\wxbase*.dll") do (
            if exist "%%f" (
                copy "%%f" "BlackjackPortable\" >nul 2>&1
                if exist "BlackjackPortable\%%~nxf" (
                    echo   [✓] %%~nxf (wxWidgets)
                    set WX_FOUND=1
                )
            )
        )
    )
)

if %WX_FOUND%==0 (
    echo   [⚠] No se encontraron DLLs de wxWidgets automáticamente
    echo   [i] Es posible que estén enlazadas estáticamente o en otra ubicación
)

:: Buscar Visual C++ Runtime
echo.
echo Buscando Visual C++ Runtime...
set VCRT_FOUND=0

:: Primero buscar en el directorio del ejecutable
for %%f in ("%SOURCE_DIR%\msvcp*.dll" "%SOURCE_DIR%\vcruntime*.dll" "%SOURCE_DIR%\concrt*.dll") do (
    if exist "%%f" (
        copy "%%f" "BlackjackPortable\" >nul 2>&1
        if exist "BlackjackPortable\%%~nxf" (
            echo   [✓] %%~nxf
            set VCRT_FOUND=1
        )
    )
)

:: Buscar en system32 si no se encontró
if %VCRT_FOUND%==0 (
    for %%f in ("C:\Windows\System32\msvcp*.dll" "C:\Windows\System32\vcruntime*.dll") do (
        if exist "%%f" (
            copy "%%f" "BlackjackPortable\" >nul 2>&1 && (
                echo   [✓] %%~nxf (system)
                set VCRT_FOUND=1
            )
        )
    )
)

:: Crear launcher batch
echo.
echo Creando launcher...
echo @echo off > "BlackjackPortable\Ejecutar_Blackjack.bat"
echo title Blackjack Game - wxWidgets >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo echo. >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo echo ================================ >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo echo    BLACKJACK GAME - wxWidgets >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo echo ================================ >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo echo. >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo echo Iniciando juego... >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo cd /d "%%~dp0" >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo if exist "Blackjack.exe" ( >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo     start "" "Blackjack.exe" >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo ^) else ( >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo     echo ERROR: No se encuentra Blackjack.exe >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo     pause >> "BlackjackPortable\Ejecutar_Blackjack.bat"
echo ^) >> "BlackjackPortable\Ejecutar_Blackjack.bat"

:: Crear README detallado
:: Copiar recursos específicos del juego
echo.
echo Copiando recursos del juego...
set RESOURCES_COPIED=0

:: Copiar carpeta de cartas
if exist "cartas" (
    echo   [✓] Copiando carpeta: cartas\
    xcopy "cartas" "BlackjackPortable\cartas\" /E /I /Q >nul 2>&1
    set RESOURCES_COPIED=1
) else if exist "FirstGUI\cartas" (
    echo   [✓] Copiando carpeta: FirstGUI\cartas\
    xcopy "FirstGUI\cartas" "BlackjackPortable\cartas\" /E /I /Q >nul 2>&1
    set RESOURCES_COPIED=1
)

:: Copiar carpeta de perfiles
if exist "Perfiles" (
    echo   [✓] Copiando carpeta: Perfiles\
    xcopy "Perfiles" "BlackjackPortable\Perfiles\" /E /I /Q >nul 2>&1
    set RESOURCES_COPIED=1
) else if exist "FirstGUI\Perfiles" (
    echo   [✓] Copiando carpeta: FirstGUI\Perfiles\
    xcopy "FirstGUI\Perfiles" "BlackjackPortable\Perfiles\" /E /I /Q >nul 2>&1
    set RESOURCES_COPIED=1
)

:: Copiar imágenes específicas del juego
for %%f in ("blackjack.png" "moneda.png") do (
    if exist "%%f" (
        copy "%%f" "BlackjackPortable\" >nul 2>&1
        echo   [✓] Imagen específica: %%f
        set RESOURCES_COPIED=1
    ) else if exist "FirstGUI\%%f" (
        copy "FirstGUI\%%f" "BlackjackPortable\" >nul 2>&1
        echo   [✓] Imagen específica: %%f (desde FirstGUI\)
        set RESOURCES_COPIED=1
    )
)

:: Copiar cualquier otra imagen PNG/JPG suelta
for %%f in (*.png *.jpg *.jpeg *.bmp *.gif *.ico) do (
    if exist "%%f" (
        copy "%%f" "BlackjackPortable\" >nul 2>&1
        echo   [✓] Imagen adicional: %%f
        set RESOURCES_COPIED=1
    )
)

:: Copiar imágenes desde carpeta FirstGUI
for %%f in ("FirstGUI\*.png" "FirstGUI\*.jpg" "FirstGUI\*.jpeg" "FirstGUI\*.bmp") do (
    if exist "%%f" (
        copy "%%f" "BlackjackPortable\" >nul 2>&1
        echo   [✓] Imagen: %%~nxf (desde FirstGUI\)
        set RESOURCES_COPIED=1
    )
)

:: Buscar otras carpetas de recursos comunes
for %%d in ("images" "assets" "res" "resources" "img" "pics" "sprites") do (
    if exist "%%d" (
        echo   [✓] Copiando carpeta adicional: %%d
        xcopy "%%d" "BlackjackPortable\%%d\" /E /I /Q >nul 2>&1
        set RESOURCES_COPIED=1
    )
    if exist "FirstGUI\%%d" (
        echo   [✓] Copiando carpeta adicional: FirstGUI\%%d
        xcopy "FirstGUI\%%d" "BlackjackPortable\%%d\" /E /I /Q >nul 2>&1
        set RESOURCES_COPIED=1
    )
)

:: Verificar y mostrar lo que se copió
if %RESOURCES_COPIED%==1 (
    echo.
    echo   Recursos copiados. Contenido de BlackjackPortable:
    dir "BlackjackPortable" /b 2>nul | findstr /i "\.png \.jpg cartas" || echo   [i] Ejecuta el script para ver todos los archivos
) else (
    echo   [⚠] No se encontraron recursos automáticamente
    echo   [i] Revisa que las imágenes estén en las ubicaciones esperadas
)

echo Creando documentación...
echo # Blackjack Game - Versión Portable > "BlackjackPortable\README.txt"
echo ================================== >> "BlackjackPortable\README.txt"
echo. >> "BlackjackPortable\README.txt"
echo Juego de Blackjack desarrollado en C++ con wxWidgets >> "BlackjackPortable\README.txt"
echo Compilado desde Visual Studio >> "BlackjackPortable\README.txt"
echo. >> "BlackjackPortable\README.txt"
echo ## COMO EJECUTAR: >> "BlackjackPortable\README.txt"
echo ================== >> "BlackjackPortable\README.txt"
echo 1. Doble clic en "Ejecutar_Blackjack.bat" (recomendado) >> "BlackjackPortable\README.txt"
echo 2. O directamente en "Blackjack.exe" >> "BlackjackPortable\README.txt"
echo. >> "BlackjackPortable\README.txt"
echo ## REQUISITOS DEL SISTEMA: >> "BlackjackPortable\README.txt"
echo ========================== >> "BlackjackPortable\README.txt"
echo - Windows 10 o superior >> "BlackjackPortable\README.txt"
echo - Arquitectura x64 o x86 >> "BlackjackPortable\README.txt"
echo - Visual C++ Redistributable (si no funciona) >> "BlackjackPortable\README.txt"
echo. >> "BlackjackPortable\README.txt"
echo ## SOLUCION DE PROBLEMAS: >> "BlackjackPortable\README.txt"
echo ========================= >> "BlackjackPortable\README.txt"
echo Si el juego no inicia, descarga e instala: >> "BlackjackPortable\README.txt"
echo Visual C++ Redistributable 2019-2022 >> "BlackjackPortable\README.txt"
echo Link: https://aka.ms/vs/17/release/vc_redist.x64.exe >> "BlackjackPortable\README.txt"
echo. >> "BlackjackPortable\README.txt"
echo Creado por: [Tu nombre] >> "BlackjackPortable\README.txt"
echo Fecha: %date% >> "BlackjackPortable\README.txt"

:: Crear script de prueba
echo @echo off > "BlackjackPortable\Probar_Dependencias.bat"
echo title Prueba de Dependencias - Blackjack >> "BlackjackPortable\Probar_Dependencias.bat"
echo echo Verificando dependencias... >> "BlackjackPortable\Probar_Dependencias.bat"
echo echo. >> "BlackjackPortable\Probar_Dependencias.bat"
echo echo Archivos en la carpeta: >> "BlackjackPortable\Probar_Dependencias.bat"
echo dir /b *.exe *.dll >> "BlackjackPortable\Probar_Dependencias.bat"
echo echo. >> "BlackjackPortable\Probar_Dependencias.bat"
echo echo Intentando ejecutar sin mostrar ventana de error... >> "BlackjackPortable\Probar_Dependencias.bat"
echo Blackjack.exe 2^>nul ^|^| echo ERROR: Faltan dependencias >> "BlackjackPortable\Probar_Dependencias.bat"
echo pause >> "BlackjackPortable\Probar_Dependencias.bat"

:: Mostrar resultados
echo.
echo ============================================
echo           EXPORTACION COMPLETADA
echo ============================================
echo.
echo [✓] Ejecutable copiado como: Blackjack.exe
echo [✓] Launcher creado: Ejecutar_Blackjack.bat
echo [✓] Documentación: README.txt
echo [✓] Herramientas de prueba incluidas
echo.
echo Contenido de BlackjackPortable:
echo ================================
dir "BlackjackPortable" 
echo.
echo SIGUIENTE PASO:
echo Ve a la carpeta "BlackjackPortable" y ejecuta "Ejecutar_Blackjack.bat"
echo.
echo Si no funciona, ejecuta "Probar_Dependencias.bat" para diagnosticar
echo.
echo ============================================
echo.
pause