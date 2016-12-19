#include <iostream>
#include "renderer.h"
#include "main.h"

#include "linuxplatform.h"

using namespace std;

int main(int argc, char *argv[])
{
    int width = 1024;
    int height = 768;

    LinuxPlatform platform;
    platform.Init();
    platform.CreateWindow(width, height, "TT2D");
    platform.Run();

    return 0;
}
