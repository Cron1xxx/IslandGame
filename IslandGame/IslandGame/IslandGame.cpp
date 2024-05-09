#include <iostream>
#include <stdlib.h>
#include <windows.h>
using namespace std;


int main() {
  system("cls");

  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

  if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo)) {
      printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
      return 0;
  }

  int x = csbiInfo.dwSize.X;
  int y = csbiInfo.dwSize.Y;

  cout << x << endl;
  cout << y << endl;
  system("pause");
}


