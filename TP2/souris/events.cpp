// events.cpp

#include <irrlicht.h>

#include "events.h"
#include "gui_ids.h"
#include <iostream>
#include <string>
using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

/**************************************************************************\
 * EventReceiver::EventReceiver                                           *
\**************************************************************************/
EventReceiver::EventReceiver()
    : node(nullptr), button_pressed(false), current_texture(0)
{
}

/*------------------------------------------------------------------------*\
 * EventReceiver::keyboard                                                *
\*------------------------------------------------------------------------*/
bool EventReceiver::keyboard(const SEvent &event)
{
    if (event.KeyInput.PressedDown)
    {
        ic::vector3df position = node->getPosition();
        ic::vector3df rotation = node->getRotation();


        switch (event.KeyInput.Key)
        {
        case KEY_ESCAPE:
            exit(0);
        case KEY_KEY_Z: // Avance
            position.X += 1 * cos(rotation.Y * M_PI / 180.0);
            position.Z += -1 * sin(rotation.Y * M_PI / 180.0);
            break;
        case KEY_KEY_S: // Recule
            position.X += -1 * cos(rotation.Y * M_PI / 180.0);
            position.Z += 1 * sin(rotation.Y * M_PI / 180.0);
            break;
        case KEY_KEY_D: // Tourne à droite
            rotation.Y += 10;
            break;
        case KEY_KEY_Q: // Tourne à gauche
            rotation.Y -= 10;
            break;
        default:;
        }
        node->setPosition(position);
        node->setRotation(rotation);
        camera->setTarget(position);
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
            ic::vector3df rotation = node->getRotation();
            rotation.Y -= (event.MouseInput.X - old_x);
            old_x = event.MouseInput.X;
            old_y = event.MouseInput.Y;
            node->setRotation(rotation);
        }
        break;
    case EMIE_MOUSE_WHEEL:
        current_texture = (current_texture + 1) % textures.size();
        node->setMaterialTexture(0, textures[current_texture]);
        break;
    default:
        ;
    }

    return false;
}

/*------------------------------------------------------------------------*\
 * EventReceiver::gui
\*------------------------------------------------------------------------*/
bool EventReceiver::gui(const irr::SEvent &event)
{


    switch(event.GUIEvent.EventType)
    {
    //entrée de menu
    case ig::EGET_MENU_ITEM_SELECTED:
    {
        ig::IGUIContextMenu *menu = (ig::IGUIContextMenu *) event.GUIEvent.Caller ;
        s32 item = menu->getSelectedItem();
        s32 id = menu->getItemCommandId(item);
        switch (id)
        {
        case MENU_NEW_GAME :
            // Faire quelque chose ici !
            //reset
            break;
        case MENU_QUIT :
            exit (0);
        default:
            ;
        }
    }
    case ig::EGET_EDITBOX_CHANGED:
        value_edit_box = event.GUIEvent.Caller->getText();
    case ig::EGET_BUTTON_CLICKED :
    {
        s32 id_button = event.GUIEvent.Caller->getID();
        if (id_button == WINDOW_BUTTON )
        {
            std::cout<< " Button ␣ clicked \n " << value_edit_box.c_str() << std::endl;

        }

        break ;
    }
    default:;
    }


    return false;
}


/**************************************************************************\
 * EventReceiver::OnEvent                                                 *
\**************************************************************************/
bool EventReceiver::OnEvent(const SEvent &event)
{
    if (!node) return false;
    switch (event.EventType)
    {
    case EET_KEY_INPUT_EVENT:
        return keyboard(event);
    case EET_MOUSE_INPUT_EVENT:
        return mouse(event);
    case EET_GUI_EVENT:
        return gui(event);
    default:;
    }

    return false;
}


/**************************************************************************\
 * EventReceiver::set_node                                                *
\**************************************************************************/
void EventReceiver::set_node(irr::scene::ISceneNode *n)
{
    node = n;
}

/**************************************************************************\
 * EventReceiver::set_camera                                               *
\**************************************************************************/
void EventReceiver::set_camera(irr::scene::ICameraSceneNode *n)
{
    camera = n;
}


