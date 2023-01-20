#include <stdio.h>
#include "App.h"

int main(int argc, char* argv[])
{

    App* app = new App;
    app->Init(1920, 1080);
    app->Run();
   
    return 0;
}
