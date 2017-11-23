// events.h

#ifndef EVENTS_H
#define EVENTS_H

#include <vector>

#include <irrlicht.h>

class EventReceiver : public irr::IEventReceiver
{
  bool button_pressed;
  int  old_x, old_y;

  bool keyboard(const irr::SEvent &event);
  bool mouse(const irr::SEvent &event);
public:
  EventReceiver();
  bool OnEvent(const irr::SEvent &event);
  bool is_mouse_pressed(int &x, int &y);
};

#endif
