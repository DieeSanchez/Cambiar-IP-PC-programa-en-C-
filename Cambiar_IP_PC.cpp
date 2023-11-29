#include <windows.h>
#include <tchar.h>
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>


using namespace std;

int main() {
	// Ejecuta el script VBScript y guarda la salida en un archivo
	system("cscript //nologo script.vbs > output.txt");
	
	// Abre el archivo de salida y lee la IP libre
	ifstream file("output.txt");
	string free_ip;
	if (file.is_open()) {
		getline(file, free_ip);
		file.close();
	}
	
	// Borra el archivo de salida
	remove("output.txt");
	
	//Asigna la IP libre en el panel de control
	cout<<"By Diego Sanchez 2023";
	string command1 = "netsh interface ip set address \"Ethernet\" static " + free_ip + " 255.255.255.0 192.168.11.250 1";
	string command2 = "netsh interface ip add dns \"Ethernet\" 8.8.8.8";
	string command3 = "netsh interface ip add dns \"Ethernet\" 8.8.4.4 index=2";
	string commands = "/C " + command1 + " && " + command2 + " && " + command3;
	
	SHELLEXECUTEINFO sei = { sizeof(sei) };
	sei.lpVerb = _T("runas");
	sei.lpFile = _T("cmd.exe");
	sei.lpParameters = _T(commands.c_str());
	sei.hwnd = NULL;
	sei.nShow = SW_NORMAL;
	
	if (!ShellExecuteEx(&sei)) {
		DWORD dwError = GetLastError();
		if (dwError == ERROR_CANCELLED) {
			// El usuario se negó a permitir privilegios de administrador
			return 1;
		}
	}
	return 0;
	
	
}
