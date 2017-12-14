
#include "myWindows.hpp"
#include<iostream> //debug

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
//namespace is = irr::scene;
//namespace iv = irr::video;
myWindows::myWindows(ig::IGUIEnvironment *g, const irr::IrrlichtDevice *d):
    gui(g), device(d){}
myWindows::~myWindows()
{}


void myWindows::create_window_begin()
{
//    std::cout << device->dimension2D().Height; // How can we get the size of the window/device
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(10,10, 620,460), false, L"Welcome To Our World");

    gui->addStaticText(L"You are going to discover this worls, your goal is to ... ", ic::rect<s32>(150,20,350,200), true,window);
}

void myWindows::create_window()
{
    // La fenêtre
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(420,25, 620,460), false, L"Settings");

    // Une zone d'édition de texte, précédée d'un label
    gui->addStaticText(L"Value", ic::rect<s32>(22,48, 65,66), false, false, window);
    gui->addEditBox(L"1.0", ic::rect<s32>(65,46, 160,66), true, window, WINDOW_VALUE);

    // Un bouton à clicker
    gui->addButton(ic::rect<s32>(40,74, 140,92), window, WINDOW_BUTTON, L"Click me!");

    // Une case à cocher
    gui->addCheckBox(true, ic::rect<s32>(40,100, 140,118), window, WINDOW_CHECK_BOX, L"Select me!");

    // Une boite combo (une liste déroulante)
    gui->addStaticText(L"Choose one: ", ic::rect<s32>(22,126, 100,142), false, false, window);
    ig::IGUIComboBox *cbox = gui->addComboBox(ic::rect<s32>(100,126, 180,142), window, WINDOW_COMBO_BOX);
    cbox->addItem(L"Choice 1", WINDOW_COMBO_CHOICE_1);
    cbox->addItem(L"Choice 2", WINDOW_COMBO_CHOICE_2);
    cbox->addItem(L"Choice 3", WINDOW_COMBO_CHOICE_3);

    // Une liste déroulée
    gui->addStaticText(L"List:", ic::rect<s32>(22,150, 65,168), false, false, window);
    ig::IGUIListBox *lbox = gui->addListBox(ic::rect<s32>(40,170, 160,242), window, WINDOW_LIST_BOX, true);
    lbox->addItem(L"First Entry");
    lbox->addItem(L"Second Entry");
    lbox->addItem(L"Third Entry");

    // Une barre de défilement
    gui->addScrollBar(true, ic::rect<s32>(22,250, 160,268), window, WINDOW_SCROLLBAR);

    // Une spin box
    gui->addSpinBox(L"18.0", ic::rect<s32>(40,280, 160,298), true, window, WINDOW_SPIN_BOX);
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
