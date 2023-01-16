#include <stdio.h>
#include "App.h"

int main(int argc, char* argv[])
{

    App app;
    app.Init(1920, 1080);
    app.Update();
   
    return 0;
}
