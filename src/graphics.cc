export module Graphics;

import <string>;

#include <X11/Xlib.h>

export class Graphics {

    Display *display;
    Window window_p1;
    Window window_p2;
    int screen;
    void drawWindow(Window window, const std::string &board_output, const std::string &title, bool is_player1);
    void fillRectangle(Window window, int x, int y, int width, int height, int colour);
    void drawString(Window window, int x, int y, const std::string &msg);
public:
    Graphics();
    ~Graphics();
    void updatePlayer1Window(const std::string &player1_output);
    void updatePlayer2Window(const std::string &player2_output);
      
};