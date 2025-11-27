export module Graphics;

import <string>;

#include <X11/Xlib.h>

export class Graphics {

    Display *display;
    Window window_p1;
    Window window_p2;
    int screen;
public:
    Graphics();
    ~Graphics();
    void drawWindow(Window window, const std::string &output);
    void updateWindows(const std::string &player1_output, const std::string &player2_output);
      
};