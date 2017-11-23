// events.cpp

#include <irrlicht.h>

#include "events.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;

/**************************************************************************\
 * EventReceiver::EventReceiver                                           *
\**************************************************************************/
EventReceiver::EventReceiver()
  : button_pressed(false)
{
}

/*------------------------------------------------------------------------*\
 * EventReceiver::keyboard                                                *
\*------------------------------------------------------------------------*/
bool EventReceiver::keyboard(const SEvent &event)
{
  if (event.KeyInput.PressedDown)
  {
    switch (event.KeyInput.Key)
    {
      case KEY_ESCAPE:
        exit(0);
      case KEY_KEY_Z: // Avance
        break;
      case KEY_KEY_S: // Recule
        break;
      case KEY_KEY_D: // Tourne à droite
        break;
      case KEY_KEY_Q: // Tourne à gauche
        break;
      default:;
    }
  }

  return false;
}

/*------------------------------------------------------------------------*\
 * EventReceiver::mouse                                                   *
\*------------------------------------------------------------------------*/
bool EventReceiver::mouse(const SEvent &event)
{
  switch(event.MouseInput.Event)
  {
    case EMIE_LMOUSE_PRESSED_DOWN:
      button_pressed = true;
      old_x = event.MouseInput.X;
      old_y = event.MouseInput.Y;
      break;
    case EMIE_LMOUSE_LEFT_UP:
      button_pressed = false;
      break;
    case EMIE_MOUSE_MOVED:
      if (button_pressed)
      {
        old_x = event.MouseInput.X;
        old_y = event.MouseInput.Y;
      }
      break;
    case EMIE_MOUSE_WHEEL:
      break;
    default:
      ;
  }

  return false;
}

/**************************************************************************\
 * EventReceiver::OnEvent                                                 *
\**************************************************************************/
bool EventReceiver::OnEvent(const SEvent &event)
{
  switch (event.EventType)
  {
    case EET_KEY_INPUT_EVENT:
      return keyboard(event);
    case EET_MOUSE_INPUT_EVENT:
      return mouse(event);
    default:;
  }

  return false;
}

/**************************************************************************\
 * EventReceiver::is_mouse_pressed                                        *
\**************************************************************************/
bool EventReceiver::is_mouse_pressed(int &x, int &y)
{
  if (button_pressed)
  {
    x = old_x;
    y = old_y;
    return true;
  }
  return false;
}
