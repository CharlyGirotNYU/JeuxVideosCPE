// events.cpp

#include <iostream>

#include <irrlicht.h>

#include "events.h"
#include "gui_ids.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


bool ESCAPE_PRESSED = false;

int day=0;
int month=0;
int year=0;
int final_solution =0;

/**************************************************************************\
 * EventReceiver::EventReceiver                                           *
\**************************************************************************/
EventReceiver::EventReceiver()
    : gui(nullptr), node(nullptr), button_pressed(false)
{
}

/*------------------------------------------------------------------------*\
 * EventReceiver::IsKeyDown                                        *
\*------------------------------------------------------------------------*/
// This is used to check whether a key is being held down
bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

/*------------------------------------------------------------------------*\
 * EventReceiver::keyboard_handler                                        *
\*------------------------------------------------------------------------*/
bool EventReceiver::keyboard_handler(const SEvent &event)
{

    if (event.KeyInput.PressedDown)
    {
        ic::vector3df position = node->getPosition();
        ic::vector3df rotation = node->getRotation();
        switch (event.KeyInput.Key)
        {
        case KEY_ESCAPE:
            if(ESCAPE_PRESSED)
            {
                gui->clear();
                ESCAPE_PRESSED = false;
                windows->active_windows(false);
            }
            else
            {
                windows->create_window(WINDOW_ESCAPE);
                ESCAPE_PRESSED = true;
            }
            break;
        default:;
        }
        node->setPosition(position);
        node->setRotation(rotation);
    }

    return false;
}

/*------------------------------------------------------------------------*\
 * EventReceiver::mouse_handler                                           *
\*------------------------------------------------------------------------*/
bool EventReceiver::mouse_handler(const SEvent &event)
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

    case EMIE_MOUSE_WHEEL:

        switch(active_digit)
        {
        case 0:
            digit_0 = (digit_0 + 1) % textures_digits.size();
            node_digits[0]->setMaterialTexture(0, textures_digits[digit_0]);
            break;
        case 1:
            digit_1 = (digit_1 + 1) % textures_digits.size();
            node_digits[1]->setMaterialTexture(0, textures_digits[digit_1]);
            break;
        case 2:
            digit_2 = (digit_2 + 1) % textures_digits.size();
            node_digits[2]->setMaterialTexture(0, textures_digits[digit_2]);
            break;
        default:;
        }
        break;
    default:
        ;
    }

    return false;
}


/*------------------------------------------------------------------------*\
 * EventReceiver::gui_handler                                             *
\*------------------------------------------------------------------------*/
bool EventReceiver::gui_handler(const SEvent &event)
{
    if (!node) return false;
    switch(event.GUIEvent.EventType)
    {
        // gestion des boutons
    case ig::EGET_BUTTON_CLICKED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if(id == UNDERSTOOD_BUTTON)
        {
            gui->clear();
            windows->active_windows(false);
            break;
        }
        if(id == ClOSE_BUTTON_ENIGM_1)
        {
            gui->clear();
            windows->active_windows(false);
            node->setPosition(node->getPosition() + ic::vector3df(-50.0,0.0f,-50.0f));
            break;
        }

        if(id==TRY_BUTTON_1)
        {
            if(day == 11 && month == 6 && year == 1995 )
            {
                gui->clear();
                windows->active_windows(false);
                windows->create_window(WINDOW_ANSWER_ENIGM_1);
                windows->setAnswer_1(true);
                node->setPosition(node->getPosition() + ic::vector3df(-50.0,0.0f,-50.0f));
            }
            break;
        }
        if(id == CLOSE_BUTTON_ENIGM_FINAL)
        {
            gui->clear();
            windows->active_windows(false);
            node->setPosition(node->getPosition() + ic::vector3df(-50.0,0.0f,-50.0f));
            break;
        }
        if(id == TRY_BUTTON_FINAL)
        {
            if( final_solution == 200)
            {
                gui->clear();
                windows->active_windows(false);
                windows->create_window(END_GAME);
                windows->setAnswer_Final(true);
            }
            break;
        }
        if(id == CLOSE_BUTTON_BACK_ROOM_0)
        {
            gui->clear();
            windows->active_windows(false);
            windows->setBack_0(false);
            break;
        }
        if(id == CLOSE_GAME)
            exit(0);
    }
        break;

        // Gestion des listes
    case ig::EGET_LISTBOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if(id == WINDOW_ESCAPE_LIST_BOX)
        {
            ig::IGUIListBox *lbox = (ig::IGUIListBox*)event.GUIEvent.Caller;
            s32 item = lbox->getSelected();
            switch(item)
            {
            case 0:
                gui->clear();
                ESCAPE_PRESSED = false;
                windows->active_windows(false);
                break;
            case 1:
                gui->clear();
                ESCAPE_PRESSED = false; //Quit the menu so escape reseted
                std::cout << "last displayed window : "  << windows->get_last_displayed_window() << std::endl;
                windows->create_window(windows->get_last_displayed_window());
                //windows->active_windows(false);
                break;
            case 2:
                std::cout << "Partie quitté en cours de Jeu" << std::endl;
                exit(0);
            default:
                break;
            }
        }
    }
        break;

        // Gestion des spinbox
    case ig::EGET_SPINBOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_SPIN_BOX)
        {
            ig::IGUISpinBox *spin = (ig::IGUISpinBox*)event.GUIEvent.Caller;
            f32 value = spin->getValue();
        }
        if (id == DAY_SPIN)
        {
            ig::IGUISpinBox *spin = (ig::IGUISpinBox*)event.GUIEvent.Caller;
            day = spin->getValue();
        }
        if (id == MONTH_SPIN)
        {
            ig::IGUISpinBox *spin = (ig::IGUISpinBox*)event.GUIEvent.Caller;
            month = spin->getValue();
        }
        if (id == YEAR_SPIN)
        {
            ig::IGUISpinBox *spin = (ig::IGUISpinBox*)event.GUIEvent.Caller;
            year = spin->getValue();
        }
        if(id == FINAL_SPIN)
        {
            ig::IGUISpinBox *spin = (ig::IGUISpinBox*)event.GUIEvent.Caller;
            final_solution = spin->getValue();
        }

    }
        break;
        //gestion des close button
    case ig::EGET_ELEMENT_CLOSED:
    {
        windows->active_windows(false);
    }
        break;

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
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return keyboard_handler(event);
    case EET_MOUSE_INPUT_EVENT:
        return mouse_handler(event);
    case EET_GUI_EVENT:
        return gui_handler(event);
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
 * EventReceiver::set_gui                                                 *
\**************************************************************************/
void EventReceiver::set_gui(irr::gui::IGUIEnvironment *g)
{
    gui = g;
}


/**************************************************************************\
 * EventReceiver::set_device                                                 *
\**************************************************************************/
void EventReceiver::set_device(irr::IrrlichtDevice *d)
{
    device = d ;
}

/**************************************************************************\
 * EventReceiver::set_window                                                 *
\**************************************************************************/
void EventReceiver::set_windows(myWindows *w)
{
    windows = w;
}

void EventReceiver::set_node_digits(std::vector<irr::scene::IMeshSceneNode*> n)
{
    node_digits = n;
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


/**************************************************************************\
 * EventReceiver::set_isMoving                                        *
\**************************************************************************/
void EventReceiver::set_isMoving(bool b)
{
    isMoving = b;
}


/**************************************************************************\
 * EventReceiver::set_animrun                                       *
\**************************************************************************/
void EventReceiver::set_animrun(bool b)
{
    animrun = b;
}

/** EventReceiver::get_isMoving */
bool EventReceiver::get_isMoving() const
{
    return isMoving;
}

/** EventReceiver::get_animrun */
bool EventReceiver::get_animrun() const
{
    return animrun;
}

void EventReceiver::set_active_digit(int i)
{
    active_digit = i;
}

const std::vector<int> EventReceiver::get_active_digit() const
{
    std::vector<int> v;
    v.push_back(digit_0);
    v.push_back(digit_1);
    v.push_back(digit_2);
    return v;
}
void EventReceiver::init_boolean_animation()
{
    isMoving =false; animrun =false;
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;

}
