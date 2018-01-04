
#include "myWindows.hpp"
#include<iostream> //debug

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
//namespace is = irr::scene;
//namespace iv = irr::video;

myWindows::myWindows(){}

myWindows::myWindows(ig::IGUIEnvironment *g,  irr::IrrlichtDevice *d):
    gui(g), device(d){}
myWindows::~myWindows()
{}


void myWindows::create_window_begin()
{
    irr::video::IVideoDriver    *driver = device->getVideoDriver();
    const irr::core::dimension2du& screenSize = driver->getScreenSize();
    int w = screenSize.Width;
    int h = screenSize.Height;

    //    std::cout << device->dimension2D().Height; // How can we get the size of the window/device
    ig::IGUIWindow *window_begin = gui->addWindow(ic::rect<s32>(10,20, w-10,h-20), false, L"Welcome To Our World");

    gui->addStaticText(L"You are going to discover this worls, your goal is to ... ", ic::rect<s32>(150,20,350,200), false,false,window_begin);
    gui->addButton(ic::rect<s32>(40,74, 140,92), window_begin, UNDERSTOOD_BUTTON, L"Close Informations");
    active_window = true;
    gui->addSpinBox(L"18.0", ic::rect<s32>(40,280, 160,298), true, window_begin, WINDOW_SPIN_BOX);
}

void myWindows::create_escape_menu()
{
    irr::video::IVideoDriver    *driver = device->getVideoDriver();
    const irr::core::dimension2du& screenSize = driver->getScreenSize();
    int w = screenSize.Width;
    int h = screenSize.Height;

    ig::IGUIWindow *window_escape = gui->addWindow(ic::rect<s32>(0,0, w, h), false, L"MENU ESCAPE");

    // Une liste déroulée
    ig::IGUIListBox *lbox = gui->addListBox(ic::rect<s32>(w/2-w/3, h/2-h/3, w/2+w/3, h/2+h/3), window_escape, WINDOW_ESCAPE_LIST_BOX, true);
    lbox->setItemHeight(h/5);
    //lbox->setDrawBackground(true);
    lbox->addItem(L"RESUME");
    lbox->addItem(L"HELP ? NOTHING CAN HELP YOU RIGHT NOW");
    lbox->addItem(L"EXIT");

    active_window = true;
    lbox->setSelected(0);
}

void myWindows::create_window_room_1()
{
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(10,10, 620,460), false, L"Welcome To The Jungle . ");

    gui->addStaticText(L" .. BLABLABLA you have to find THIS ... ", ic::rect<s32>(150,20,350,200), false,false,window);
    gui->addButton(ic::rect<s32>(40,74, 140,92), window, UNDERSTOOD_BUTTON, L"UNDERSTOOD!");
    active_window = true;
}

void myWindows::create_window_room_2()
{
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(10,10, 620,460), false, L"Welcome To The Club . ");

    gui->addStaticText(L" .. BLABLABLA you have to find THIS ... ", ic::rect<s32>(150,20,350,200), false,false,window);
    gui->addButton(ic::rect<s32>(40,74, 140,92), window, UNDERSTOOD_BUTTON, L"UNDERSTOOD!");
    active_window = true;
}


void myWindows::create_window_enigm_1()
{
    active_window = true;

    irr::video::IVideoDriver    *driver = device->getVideoDriver();
    const irr::core::dimension2du& screenSize = driver->getScreenSize();
    int w = screenSize.Width;
    int h = screenSize.Height;

    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(w/2-w/3, h/2-h/3, w/2+w/3, h/2+h/3), false, L"Welcome To Our World");

    gui->addStaticText(L"This Box contains your next destination to find your friend back in the city. You must unlock it. To do so, please type the birth date of Maxime Di Folco", ic::rect<s32>(180,20,250,200), false,false,window);

    gui->addSpinBox(L"14", ic::rect<s32>(40,200, 160,220), true, window, DAY_SPIN);
    gui->addSpinBox(L"12", ic::rect<s32>(40,240, 160,260), true, window, MONTH_SPIN);
    gui->addSpinBox(L"1994", ic::rect<s32>(40,280, 160,300), true, window, YEAR_SPIN);

    gui->addButton(ic::rect<s32>(40,74, 140,92), window, TRY_BUTTON_1, L"TRY DATE");
    gui->addButton(ic::rect<s32>(150,74, 250,92), window, ClOSE_BUTTON_ENIGM_1, L"Close Informations");
}

void myWindows::create_window_answer_enigm_1()
{
    active_window = true;

    irr::video::IVideoDriver    *driver = device->getVideoDriver();
    const irr::core::dimension2du& screenSize = driver->getScreenSize();
    int w = screenSize.Width;
    int h = screenSize.Height;

    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(w/2-w/3, h/2-h/3, w/2+w/3, h/2+h/3), false, L"Answer");

    gui->addStaticText(L"This Box contains your next destination to find your friend back in the city. You must unlock it. To do so, please type the birth date of Maxime Di Folco", ic::rect<s32>(180,20,250,200), false,false,window);

    gui->addButton(ic::rect<s32>(150,74, 250,92), window, ClOSE_BUTTON_ENIGM_1, L"Close Informations");
}

void myWindows::create_window_enigm_2()
{

}

void myWindows::create_window(int win_num)
{
    std::cout << win_num << std::endl ;
    switch(win_num)
    {
    case WINDOW_BEGIN:
        create_window_begin();
        break;
    case WINDOW_ESCAPE:
        create_escape_menu();
        break;
    case WINDOW_ROOM_1:
        create_window_room_1();
        break;
    case WINDOW_ROOM_2:
        create_window_room_2();
        break;
    case WINDOW_ENIGM_1:
        create_window_enigm_1();
        break;
       case WINDOW_ANSWER_ENIGM_1:
        create_window_answer_enigm_1();
        break;
    case WINDOW_ENIGM_2:
        create_window_enigm_2();
    default:
        break;
    }



    //    // La fenêtre
    //    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(420,25, 620,460), false, L"Settings");

    //    // Une zone d'édition de texte, précédée d'un label
    //    gui->addStaticText(L"Value", ic::rect<s32>(22,48, 65,66), false, false, window);
    //    gui->addEditBox(L"1.0", ic::rect<s32>(65,46, 160,66), true, window, WINDOW_VALUE);

    //    // Un bouton à clicker
    //    gui->addButton(ic::rect<s32>(40,74, 140,92), window, WINDOW_BUTTON, L"Click me!");

    //    // Une case à cocher
    //    gui->addCheckBox(true, ic::rect<s32>(40,100, 140,118), window, WINDOW_CHECK_BOX, L"Select me!");

    //    // Une boite combo (une liste déroulante)
    //    gui->addStaticText(L"Choose one: ", ic::rect<s32>(22,126, 100,142), false, false, window);
    //    ig::IGUIComboBox *cbox = gui->addComboBox(ic::rect<s32>(100,126, 180,142), window, WINDOW_COMBO_BOX);
    //    cbox->addItem(L"Choice 1", WINDOW_COMBO_CHOICE_1);
    //    cbox->addItem(L"Choice 2", WINDOW_COMBO_CHOICE_2);
    //    cbox->addItem(L"Choice 3", WINDOW_COMBO_CHOICE_3);

    //    // Une liste déroulée
    //    gui->addStaticText(L"List:", ic::rect<s32>(22,150, 65,168), false, false, window);
    //    ig::IGUIListBox *lbox = gui->addListBox(ic::rect<s32>(40,170, 160,242), window, WINDOW_LIST_BOX, true);
    //    lbox->addItem(L"First Entry");
    //    lbox->addItem(L"Second Entry");
    //    lbox->addItem(L"Third Entry");

    //    // Une barre de défilement
    //    gui->addScrollBar(true, ic::rect<s32>(22,250, 160,268), window, WINDOW_SCROLLBAR);

    //    // Une spin box
    //    gui->addSpinBox(L"18.0", ic::rect<s32>(40,280, 160,298), true, window, WINDOW_SPIN_BOX);
}

/*===========================================================================*\
 * create_menu                                                               *
\*===========================================================================*/
void myWindows::create_menu()
{
    ig::IGUIContextMenu *submenu;

    // Les trois entrées principales :
    ig::IGUIContextMenu *menu = gui->addMenu();
    menu->addItem(L"File", -1, true, true);
    menu->addItem(L"Debug", -1, true, true);
    menu->addItem(L"Help", -1, true, true);

    // Le contenu du menu File :
    submenu = menu->getSubMenu(0);
    submenu->addItem(L"New game...", MENU_NEW_GAME);
    submenu->addSeparator();
    submenu->addItem(L"Quit", MENU_QUIT);

    // Le contenu du menu Debug :
    submenu = menu->getSubMenu(1);
    submenu->addItem(L"Bounding Box",   MENU_BOUNDING_BOX);
    submenu->addItem(L"Show Normals",   MENU_NORMALS);
    submenu->addItem(L"Show Triangles", MENU_TRIANGLES);
    submenu->addItem(L"Transparency",   MENU_TRANSPARENCY);

    // Le contenu du menu Help :
    submenu = menu->getSubMenu(2);
    submenu->addItem(L"About...", MENU_ABOUT);
}


bool myWindows::active_windows() const
{
    return active_window;
}

void myWindows::active_windows(bool b)
{
    active_window=b;
}
/** Get Answer_1 */
bool myWindows::getAnswer_1() const
{
    return answer_1;
}
/** Set Answer_1 */
void myWindows::setAnswer_1(bool b)
{
    answer_1=b;
}



