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
    : gui(nullptr), node(nullptr), button_pressed(false), current_texture(0)
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
        //      case KEY_KEY_Z: // Avance
        //        position.X += 1 * cos(rotation.Y * M_PI / 180.0);
        //        position.Z += -1 * sin(rotation.Y * M_PI / 180.0);
        //        break;
        //      case KEY_KEY_S: // Recule
        //        position.X += -1 * cos(rotation.Y * M_PI / 180.0);
        //        position.Z += 1 * sin(rotation.Y * M_PI / 180.0);
        //        break;
        //      case KEY_KEY_D: // Tourne à droite
        //        rotation.Y += 10;
        //        break;
        //      case KEY_KEY_Q: // Tourne à gauche
        //        rotation.Y -= 10;
        //        break;

        case KEY_ESCAPE:
            std::cout<< "ESCAPE PRESSED" << ESCAPE_PRESSED << std::endl;
            if(ESCAPE_PRESSED)
            {
                gui->clear();
                std::cout<<"clear\n";
                ESCAPE_PRESSED = false;
                windows->active_windows(false);
                //TO DO : RESET cursor at center
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
        //    case EMIE_MOUSE_MOVED:
        //      if (button_pressed)
        //      {
        //        ic::vector3df rotation = node->getRotation();
        //        rotation.Y -= (event.MouseInput.X - old_x);
        //        old_x = event.MouseInput.X;
        //        old_y = event.MouseInput.Y;
        //        node->setRotation(rotation);
        //      }
        //      break;
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

        //current_texture = (current_texture + 1) % textures_digits.size();
        //node->setMaterialTexture(0, textures[current_texture]);
        //node_digits->setMaterialTexture(0, textures_digits[current_texture]);
        //std::cout << "current texture " << current_texture << std::endl;
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
    // Gestion des menus de la barre de menu
    case ig::EGET_MENU_ITEM_SELECTED:
    {
        ig::IGUIContextMenu *menu = (ig::IGUIContextMenu*)event.GUIEvent.Caller;
        s32 item = menu->getSelectedItem();
        s32 id = menu->getItemCommandId(item);
        u32 debug_info = node->isDebugDataVisible();

        switch(id)
        {
        case MENU_NEW_GAME:
            // Faire quelque chose ici !
            break;
        case MENU_QUIT:
            exit(0);

        case MENU_BOUNDING_BOX:
            menu->setItemChecked(item, !menu->isItemChecked(item));
            node->setDebugDataVisible(debug_info ^ is::EDS_BBOX);
            break;

        case MENU_NORMALS:
            menu->setItemChecked(item, !menu->isItemChecked(item));
            node->setDebugDataVisible(debug_info ^ is::EDS_NORMALS);
            break;

        case MENU_TRIANGLES:
            menu->setItemChecked(item, !menu->isItemChecked(item));
            node->setDebugDataVisible(debug_info ^ is::EDS_MESH_WIRE_OVERLAY);
            break;

        case MENU_TRANSPARENCY:
            menu->setItemChecked(item, !menu->isItemChecked(item));
            node->setDebugDataVisible(debug_info ^ is::EDS_HALF_TRANSPARENCY);
            break;

        case MENU_ABOUT:
            gui->addMessageBox(L"Boite About", L"Texte présentant ce super jeu\nd'un intérêt incroyable");
            break;
        }
    }
        break;
        // gestion des boites d'édition de texte
    case ig::EGET_EDITBOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_VALUE)
        {
            ic::stringc s = event.GUIEvent.Caller->getText();
            std::cout << "editbox changed:" << s.c_str() << std::endl;
        }
    }
        break;
        // gestion des boutons
    case ig::EGET_BUTTON_CLICKED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_BUTTON)
            std::cout << "Button clicked\n";
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
        }
        if(id == CLOSE_BUTTON_ENIGM_FINAL)
        {
            gui->clear();
            windows->active_windows(false);
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
        }
        if(id == CLOSE_GAME)
            exit(0);
    }
        break;
        // gestion des cases à cocher
    case ig::EGET_CHECKBOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_CHECK_BOX)
        {
            std::cout << "Check box clicked: ";
            bool checked = ((ig::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
            if (!checked) std::cout << "un";
            std::cout << "checked\n";
        }
    }
        break;
        // gestion des combo-box
    case ig::EGET_COMBO_BOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_COMBO_BOX)
        {
            ig::IGUIComboBox *cbox = (ig::IGUIComboBox*)event.GUIEvent.Caller;
            s32 item = cbox->getSelected();
            u32 elem_id = cbox->getItemData(item);
            std::cout << "Combo box changed: item " << item << ", id " << elem_id << std::endl;
        }
    }
        break;
        // Gestion des listes
    case ig::EGET_LISTBOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_LIST_BOX)
        {
            ig::IGUIListBox *lbox = (ig::IGUIListBox*)event.GUIEvent.Caller;
            s32 item = lbox->getSelected();
            std::cout << "List box changed: item " << item << std::endl;
        }
        if(id == WINDOW_ESCAPE_LIST_BOX)
        {
            ig::IGUIListBox *lbox = (ig::IGUIListBox*)event.GUIEvent.Caller;
            s32 item = lbox->getSelected();
            std::cout << item << std::endl;
            switch(item)
            {
            case 0:
                gui->clear();
                ESCAPE_PRESSED = false;
                windows->active_windows(false);
                // TODO reset cursor position
                break;
            case 1:
                std::cout << "No Help at this point of Development" << std::endl;
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
        // Gestion des barres de défilement
    case ig::EGET_SCROLL_BAR_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_SCROLLBAR)
        {
            ig::IGUIScrollBar *scroll = (ig::IGUIScrollBar*)event.GUIEvent.Caller;
            s32 value = scroll->getPos();
            std::cout << "Scrollbar moved: " << value << std::endl;
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
            std::cout << "Spin Box changed: " << value << std::endl;
        }
        if (id == DAY_SPIN)
        {
            ig::IGUISpinBox *spin = (ig::IGUISpinBox*)event.GUIEvent.Caller;
            day = spin->getValue();
            std::cout<< "day" << day << std::endl;
        }
        if (id == MONTH_SPIN)
        {
            ig::IGUISpinBox *spin = (ig::IGUISpinBox*)event.GUIEvent.Caller;
            month = spin->getValue();
            std::cout<< "month" << month << std::endl;
        }
        if (id == YEAR_SPIN)
        {
            ig::IGUISpinBox *spin = (ig::IGUISpinBox*)event.GUIEvent.Caller;
            year = spin->getValue();
            std::cout<< "year" << year << std::endl;
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
        std::cout << "Close button clicked\n";
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

/**************************************************************************\
 * EventReceiver::set_camera                                                 *
\**************************************************************************/
void EventReceiver::set_camera(irr::scene::ICameraSceneNode* c)
{
    camera = c;
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
