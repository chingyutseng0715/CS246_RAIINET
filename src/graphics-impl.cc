module Graphics;

import <string>;
import <sstream>;

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

const int window_width = 600;
const int window_height = 1000;
const int border_width = 2;

Graphics::Graphics()
{

    // This opens the connection between your computer and the Linux's XLib server
    display = XOpenDisplay(nullptr);

    if (display == nullptr)
    {
        throw std::runtime_error("Cannot connect to X server");
    }

    // DefaultScreen return a int and seems like Xlib can support showing differenct screens, default is 1 screen
    screen = DefaultScreen(display) // Check Xlib tutorial, not sure it's XDefaultScreen or DefaultScreen

        // Your screen width, so compiler know your screen properties
        int screen_width = DisplayWidth(display, screen);
    // Your screen height, so compiler know your screen properties
    int screen_height = DosplayHeight(display, screen);

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
        x_p1,
        y_p1,
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
    
    // This functions tells what event the windows should react to
    XSelectInput(display, window_p1, ExposureMask | KeyPressMask | StructureNotifyMask);
    XSelectInput(display, window_p2, ExposureMask | KeyPressMask | StructureNotifyMask);
    
    // This is the function, that will actually shows the window
    XMapWindow(display, window_p1);
    XMapWindow(display, window_p2);
    
    // This checks if the two windows are opened properly
    XEvent event;
    int mapped_count = 0;
    while (mapped_count < 2) {
        XNextEvent(display, &event); // this fetchs the next event
        if (event.type == MapNotify) { //MapNotify is a special type that happens when a window maps
            mapped_count++;
        } else {
            throw std::runtime_error("2 windows did not open properly");
        }
    }


    // Special function for X11, frees X type's thing, so we have 4 XTextProperty
    XFree(window_name_p1.value);
    XFree(icon_name_p1.value);
    XFree(window_name_p2.value);
    XFree(icon_name_p2.value);
    // The reason we only need to free this but no XEvent is because XStringListToTextProperty will automatically allocate this four XTextProperty to heap but event will not

}

Graphics::~Graphics() {
    if (display) {

        // Destroying things
        XCloseDisplay(display);
        XDestroyWindow(display, window_p1);
        XDestroyWindow(display, window_p2);
        
    }
}
