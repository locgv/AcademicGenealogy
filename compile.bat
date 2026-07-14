@echo off
echo =======================================================
echo Dang bien dich Academic Genealogy Project...
echo =======================================================
gcc -Wall -o main.exe AcademicGenealogy.c main.c
if %errorlevel% neq 0 (
    echo [ERROR] Bien dich that bai! Vui long kiem tra lai gcc.
    pause
    exit /b %errorlevel%
)
echo [SUCCESS] Bien dich thanh cong! Dang chay chuong trinh...
echo -------------------------------------------------------
main.exe
echo -------------------------------------------------------
echo Nhan phim bat ky de thoat.
pause
