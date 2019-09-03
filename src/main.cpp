#include "Application.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Application app(SCR_WIDTH, SCR_HEIGHT);
    
    app.runLoop();
    
    return 0;
}
