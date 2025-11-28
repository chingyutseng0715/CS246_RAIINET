module Graphics;

import <string>;
import <sstream>;
import <vector>;

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

const int window_width = 600;
const int window_height = 1000;
const int border_width = 2;
enum {White = 0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

Graphics::Graphics()
{

    // This opens the connection between your computer and the Linux's XLib server
    display = XOpenDisplay(nullptr);

    if (display == nullptr)
    {
        throw std::runtime_error("Cannot connect to X server");
    }

    // DefaultScreen return a int and seems like Xlib can support showing differenct screens, default is 1 screen
    screen = DefaultScreen(display); // Check Xlib tutorial, not sure it's XDefaultScreen or DefaultScreen

    // Your screen width, so compiler know your screen properties
    int screen_width = DisplayWidth(display, screen);
    // Your screen height, so compiler know your screen properties
    int screen_height = DisplayHeight(display, screen);

    // initiate positions where player1 and player2's window might be
    int x_p1 = (screen_width - 2 * window_width - 50) / 2;
    int y_p1 = (screen_height - window_height) / 2;

    int x_p2 = x_p1 + window_width + 50;
    int y_p2 = (screen_height - window_height) / 2;

    // Creates a window for Player 1, may also use XCreateWindow for more customizable window
    window_p1 = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        x_p1,
        y_p1,
        window_width,
        window_height,
        border_width,
        WhitePixel(display, screen), // This is the colour of the border, the return type is unsigned long pixel
        BlackPixel(display, screen)  // This is the colour of the background
    );

    // Creates a window for Player 2
    window_p2 = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        x_p2,
        y_p2,
        window_width,
        window_height,
        border_width,
        WhitePixel(display, screen), // This is the colour of the border, the return type is unsigned long pixel
        BlackPixel(display, screen)  // This is the colour of the background
    );

    // conver strings to XTextProperty which is the only type that XSetWMProperties receive - p1
    XTextProperty window_name_p1, icon_name_p1;
    char window_name_str_p1[] = "Player 1";
    char icon_name_str_p1[] = "Player 1";
    char *wp1 = window_name_str_p1;
    char *ip1 = icon_name_str_p1;

    XStringListToTextProperty(&wp1, 1, &window_name_p1);
    XStringListToTextProperty(&ip1, 1, &icon_name_p1);
    // Set some properties of the window, so it will show title and icon
    XSetWMProperties(display, window_p1, &window_name_p1, &icon_name_p1,
                     nullptr, 0, nullptr, nullptr, nullptr);

    // conver strings to XTextProperty which is the only type that XSetWMProperties receive - p2
    XTextProperty window_name_p2, icon_name_p2;
    char window_name_str_p2[] = "Player 2";
    char icon_name_str_p2[] = "Player 2";
    char *wp2 = window_name_str_p2;
    char *ip2 = icon_name_str_p2;

    XStringListToTextProperty(&wp2, 1, &window_name_p2);
    XStringListToTextProperty(&ip2, 1, &icon_name_p2);
    XSetWMProperties(display, window_p2, &window_name_p2, &icon_name_p2,
                     nullptr, 0, nullptr, nullptr, nullptr);

    gc = XCreateGC(display, window_p1, 0, nullptr);

    XColor xcolour;
    Colormap cmap;
    char color_vals[10][10] = {"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

    cmap = DefaultColormap(display, DefaultScreen(display));
    for (int i = 0; i < 10; ++i)
    {
        XParseColor(display, cmap, color_vals[i], &xcolour);
        XAllocColor(display, cmap, &xcolour);
        colours[i] = xcolour.pixel;
    }

    XSetForeground(display, gc, colours[Black]);
    XSetBackground(display, gc, colours[White]);

    // This functions tells what event the windows should react to
    XSelectInput(display, window_p1, ExposureMask | KeyPressMask | StructureNotifyMask);
    XSelectInput(display, window_p2, ExposureMask | KeyPressMask | StructureNotifyMask);

    // This is the function, that will actually shows the window
    XMapWindow(display, window_p1);
    XMapWindow(display, window_p2);

    // This checks if the two windows are opened properly
    XEvent event;
    int mapped_count = 0;
    while (mapped_count < 2)
    {
        XNextEvent(display, &event); // this fetchs the next event
        if (event.type == MapNotify)
        { // MapNotify is a special type that happens when a window maps
            mapped_count++;
        }
        else
        {
            throw std::runtime_error("2 windows did not open properly");
        }
    }

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = hints.min_height = hints.max_height = window_height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = window_width;
    XSetNormalHints(display, window_p1, &hints);
    XSetNormalHints(display, window_p2, &hints);

    XSynchronize(display, True);

    usleep(1000);

    // Special function for X11, frees X type's thing, so we have 4 XTextProperty
    XFree(window_name_p1.value);
    XFree(icon_name_p1.value);
    XFree(window_name_p2.value);
    XFree(icon_name_p2.value);
    // The reason we only need to free this but no XEvent is because XStringListToTextProperty will automatically allocate this four XTextProperty to heap but event will not
}

Graphics::~Graphics()
{
    if (display)
    {

        // Destroying things
        XCloseDisplay(display);
        XDestroyWindow(display, window_p1);
        XDestroyWindow(display, window_p2);
    }
}

void Graphics::drawWindow(Window window, const std::string &board_output, const std::string &title, bool is_player1)
{
    XClearWindow(display, window);

    // Draw title
    drawString(window, 10, 20, title);

    std::istringstream stream(board_output);
    std::string line;
    std::vector<std::string> board_lines;

    while (std::getline(stream, line))
    {
        // Check if line is part of board
        if (!line.empty())
        {
            bool is_board_line = true;
            for (char c : line)
            {
                if (c != '=' && c != '.' && c != ' ' && c != 'S' && c != '#' &&
                    !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') &&
                    c != 'x' && c != 'y' && c != 'z' && c != 'w')
                {
                    is_board_line = false;
                    break;
                }
            }

            if (is_board_line && (line[0] == '=' || line[0] == '.' ||
                                  (line[0] >= 'a' && line[0] <= 'z') || (line[0] >= 'A' && line[0] <= 'Z')))
            {
                board_lines.emplace_back(line);
            }
        }
    }

    for (int row = 0; row < static_cast<int>(board_lines.size()); ++row)
    {

        std::string &line = board_lines[row];

        for (int col = 0; col < static_cast<int>(line.length()); ++col)
        {

            char cell = line[col];
            int x = 20 + col * 50;
            int y = 30 + 20 + row * 50;

            int color = white;

            if (cell == '=')
            {
                color = cyan;
            }
            else if (cell >= 'a' && cell <= 'h')
            {
                color = is_player1 ? Green : Red;
            }
            else if (cell >= 'A' && cell <= 'H')
            {
                color = is_player1 ? Red : Green;
            }
            else if (cell == 'd' || cell == 'e' || cell == 'D' || cell == 'E')
            {
                color = Orange;
            }
            else if (cell == 'S')
            {
                color = DarkGray;
            }
            else if (cell == '#')
            {
                color = Gray;
            }
            else if (cell == 'x' || cell == 'y' || cell == 'z' || cell == 'w')
            {
                color = Pink;
            }
            else if (cell >= 'i' && cell <= 'p')
            {
                color = Orange;
            }
            else if (cell >= 'I' && cell <= 'P')
            {
                color = Yellow;
            }

            if (cell != '.')
            {
                fillRectangle(x, y, 50, 50, color);
            }

            XDrawRectangle(display, window, gc, x, y, 50, 50);

            if (cell != '.' && cell != '=' && cell != ' ')
            {
                XSetForeground(display, gc, colours[White]);
                drawString(x + 25 - 4, y + 25 + 4, std::string(1, cell));
                XSetForeground(display, gc, colours[Black]);
            }
        }
    }
}
void Graphics::updatePlayer1Window(const std::string &board_output) {
    drawWindow(window_p1, board_output, "Player 1 View", true);
    XFlush(display);
}

void Graphics::updatePlayer2Window(const std::string &board_output) {
    drawWindow(window_p2, board_output, "Player 2 View", false);
    XFlush(display);
}

void Graphics::fillRectangle(int x, int y, int width, int height, int colour)
{
    XSetForeground(display, gc, colours[colour]);
    XFillRectangle(display, window, gc, x, y, width, height);
    XSetForeground(display, gc, colours[Black]);
}

void Graphics::drawString(int x, int y, std::string &msg)
{
    XDrawString(display, window, DefaultGC(display, screen), x, y, msg.c_str(), msg.length());
}
