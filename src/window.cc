module;
#include <X11/Xlib.h>
export module xwindow;
import <iostream>;
import <string>;

export class Xwindow {
  Display *d;
  Window w;
  int s;
  int font_height;
  int font_width;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  // Available colours.
  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);
  
  // close the window
  void close();

  // clear the output on the window
  void clearWindow();
  
  // return the font height
  int getHeight();
  // return the font width
  int getWidth();
};

