#ifndef __APP_H__
#define __APP_H__

#include <atomic>
#include <memory>
#include <string>
#include <X11/Xlib.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/XKBlib.h>
#include <glad/glad_glx.h>
#include <glm/glm.hpp>

using namespace std;

enum IdentifierType
{
  NAME,
  CLASS,
  WINDOW,
  PID
};

struct Identifier
{
  IdentifierType type;
  string strId;
  Window win;
  int pid;
};

class X11App
// the monster X11 Interface App class!!
{

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
  atomic_bool selected = false;
  X11App(Display* display, int screen);
  int x = 0;
  int y = 0;
  size_t appIndex;

public:
  X11App(X11App&& other) noexcept;
  static X11App* byName(string windowName,
                        Display* display,
                        int screen,
                        int width,
                        int height);
  static X11App* byClass(string windowClass,
                         Display* display,
                         int screen,
                         int width,
                         int height);

  static X11App* byWindow(Window window,
                          Display* display,
                          int screen,
                          int width,
                          int height);

  static X11App* byPID(int pid,
                       Display* display,
                       int screen,
                       int width,
                       int height);

  static bool initAppClass(Display* display, int screen);

  int width = 0;
  int height = 0;
  glm::mat4 heightScalar = glm::mat4(1.0);
  static glm::mat4 recomputeHeightScaler(double width, double height);
  void positionNotify(int x, int y);
  void appTexture();
  void attachTexture(int textureUnit, int textureId, size_t appIndex);
  void focus(Window matrix);
  void takeInputFocus();
  void unfocus(Window matrix);
  void resize(int width, int height);
  void resizeMove(int width, int height, int x, int y);
  bool isFocused();
  bool isAccessory();
  int getPID();
  string getWindowName();
  Window getWindow();
  array<int, 2> getPosition();
  size_t getAppIndex() { return appIndex; }
  void select();
  void deselect();
  bool isSelected();
  void close();
  void larger();
  void smaller();
};

#endif
