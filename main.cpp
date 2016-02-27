#include "graphics.h"

#define HELP "This is the help string\n"
#define WELCOME "Welcome!\n"
#define PROMPT ">> "

int main(int argc, char *argv[]) {
    Canvas screen;
    screen.clear_screen();

    color c0;

    edge_set es;

    float master[4][4], current[4][4];
    gen_identity_matrix_4(master);

    std::string command;
    float a, b, c, d, e, f;

    std::cout << WELCOME;
    std::cout << PROMPT;

    while (std::cin >> command) {

        if (!command.compare("exit")) { 
            break;
        }

        else if (!command.compare("help")) {
            std::cout << HELP;
        }

        else if (!command.compare("add")) {
            std::cin >> command; // secondary command
            
            if (!command.compare("edge")) {
                std::cin >> a >> b >> c >> d >> e >> f; // x_0 y_0 z_0, x_1 y_1 z_1
                ADD_TO_EDGE_SET(es, EDGE(PT(a, b, c), PT(d, e, f)));
            }

            else if (!command.compare("point")){ // FIXME idk what the hw is asking
                std::cin >> a >> b >> c; // x_0 y_0 z_0
                ADD_TO_EDGE_SET(es, EDGE(PT(a, b, c), PT(a, b, c)));
            }
        }

        else if (!command.compare("transform")) {
            std::cin >> command; // secondary command
            // TODO
        }

        else if (!command.compare("clear")) {
            std::cin >> command; // secondary

            if (!command.compare("all")) {
                screen.clear_screen(); // clear screen
                es.clear(); // clear edges
                gen_identity_matrix_4(master); // clear transformations
                std::cout << "All drawings, edges and transformations have been removed.\n";
            }

            else if (!command.compare("screen")) {
                screen.clear_screen();
                std::cout << "The screen has been cleared, but the edge and transformation matrices are still in-tact. To remove them, run 'clear edges' and 'clear transformations' respectively.\n";
            }

            else if (!command.compare("edges")) {
                es.clear();
                std::cout << "All the edges have been removed. But the canvas and transformation matrices are still in-tact. To remove them, run 'clear screen' and 'clear transformations' respectively.\n";
            }

            else if (!command.compare("transformations")) {
                gen_identity_matrix_4(master);
                std::cout << "The transformation matrix has been wiped. But the canvas and the edge-set are still in-tact. To remove them, run 'clear screen' and 'clear edges' respectively.\n";
            }
        }

        else if (!command.compare("draw")) {
            std::cin >> c0.r >> c0.g >> c0.b;
            screen.draw_edge_set(c0, es);
            std::cout << "";
        }

        else if (!command.compare("save")) {
            std::cin >> command; // technically filename
            screen.save_ppm(command.c_str());
            std::cout << "Image saved at '" << command << "'\n";
        }

        std::cout << PROMPT;

    }

    return 0;
}
