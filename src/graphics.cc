export module Graphics;

import <string>;

#include <X11/Xlib.h>

export class Graphics {

    Display *display;
    Window window_p1;
    Window window_p2;
    int screen;
    void drawWindow(Window window, const std::string &output, bool is_player1);
public:
    Graphics();
    ~Graphics();
    void updatePlayer1Window(const std::string &player1_output);
    void updatePlayer2Window(const std::string &player2_output);
      
};