#include <iostream>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

void SetCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, pos);
}

void ClearScreen() {
    system("cls"); 
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, SOMAXCONN);
    cout << "Server is waiting for connection..." << endl;

    SOCKET client = accept(server, 0, 0);
    cout << "Client connected." << endl;

    char coords[10];
    int oldX = -1, oldY = -1;

    while (true) {
        int bytes = recv(client, coords, sizeof(coords), 0);
        if (bytes <= 0) break;

        int x, y;
        sscanf_s(coords, "%d %d", &x, &y);

        if (oldX != -1 && oldY != -1) {
            SetCursorPosition(oldX, oldY);
            cout << " ";
        }

        SetCursorPosition(x, y);
        cout << ":)";

        oldX = x;
        oldY = y;
    }

    closesocket(client);
    closesocket(server);
    WSACleanup();
    return 0;
}