#include <stdio.h>
#include "App.h"

int main(int argc, char* argv[])
{

    App* app = new App;
    app->Init();
    app->Run();
   
    return 0;
}
