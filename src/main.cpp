#include "app/app.h"



// Main code
int main(int, char**)
{
    try {
        std::unique_ptr<App> app = std::make_unique<App>();
        app->execute();
    } catch (std::exception& error) {
        std::cout<<error.what()<<std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}