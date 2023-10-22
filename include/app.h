#ifndef __APP_H__
#define __APP_H__

#include <atomic>
#include <memory>
#include <string>
#include <X11/Xlib.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/XKBlib.h>
#include <glad/glad_glx.h>

using namespace std;

enum IdentifierType {
  NAME,
  CLASS,
  WINDOW
};

struct Identifier {
  IdentifierType type;
  string strId;
  Window win;
};

class X11App {
  Display* display;
  int screen;
  Window appWindow;
  XWindowAttributes attrs;
  GLXFBConfig* fbConfigs;
  int fbConfigCount;
  void fetchInfo(Identifier identifier);
  int textureUnit = -1;
  int textureId = -1;
  atomic_bool focused = false;
  X11App(Display *display, int screen);

public:
  static X11App *byName(string windowName, Display *display, int screen,
                        int width, int height);
  static X11App *byClass(string windowClass, Display *display, int screen,
                         int width, int height);

  static X11App *byWindow(Window window, Display *display, int screen, int width, int height);

  static bool initAppClass(Display * display, int screen);

  int width;
  int height;
  void appTexture();
  void attachTexture(int textureUnit, int textureId);
  void click(int x, int y);
  void focus(Window matrix);
  void takeInputFocus();
  void unfocus(Window matrix);
  void resize(int width, int height);
  bool isFocused();
  Window getWindow();
};

#endif
