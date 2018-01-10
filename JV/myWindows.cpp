
#include "myWindows.hpp"
#include<iostream> //debug

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
//namespace is = irr::scene;
//namespace iv = irr::video;

myWindows::myWindows(){}

myWindows::myWindows(ig::IGUIEnvironment *g,  irr::IrrlichtDevice *d):
    gui(g), device(d){

    font = gui->getFont("data/font_a/myfont.xml");
    init_window_parameters();
}
myWindows::~myWindows()
{}


void myWindows::create_window_begin()
{

    irr::video::IVideoDriver *driver = device->getVideoDriver();

    //    std::cout << device->dimension2D().Height; // How can we get the size of the window/device
    ig::IGUIWindow *window_begin = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Welcome To Our World");

    irr::gui::IGUIStaticText *texte =  gui->addStaticText(L"Vous n'auriez jamais du pénétrer notre monde. Vous en êtes maintenant le prisonnier. Laissez moi vous expliquer. Il y a bien longtemps, dans le temps du CPE antique"
                                                          "une momie se retrouva prise au piège de cette ville qui de plus n'était pas très jolie, ayant perdu beaucoup de décorations sur les facades de ces batiments. "
                                                          "Vous avez été appelé à l'aide pour aider MOMIE (et non pas MAMIE bien au chaud dans son canapé sous son plaid) à s'échapper. "
                                                          "Pour cela il vous faudra résoudre les énigmes qui vous seront proposées par la suite. Chaque énigme vous ménéra à la salle suivante par le biais des nains téléporteurs. "
                                                          "Des informations spécifiques vous seront données ultérieurement. "
                                                          "Pour démarrer, veuillez trouver le nain de jardin vous permettant de vous rendre à la salle de la première énigme ", ic::rect<s32>(10,50,x2-50,y2-200), false,true,window_begin);


    texte->setOverrideFont(font);                               // utilisation de la police

    irr::video::ITexture* command = driver->getTexture("data/info/commandes.png") ;
    gui->addImage(command,ic::position2d< s32 >(x1,y2-300),true,window_begin);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window_begin, UNDERSTOOD_BUTTON, L"A la recherche du nain de jardin");
    active_window = true;
}

void myWindows::create_escape_menu()
{
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    const irr::core::dimension2du& screenSize = driver->getScreenSize();
    int w = screenSize.Width;
    int h = screenSize.Height;

    ig::IGUIWindow *window_escape = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"MENU ESCAPE");

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
    irr::video::IVideoDriver *driver = device->getVideoDriver();

    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Welcome To The Jungle . ");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L" Bien Joué ! Vous avez réussi à accéder à la Jungle."
                                                         " Il vous est ici demandé de trouver le coffre du redoutable pirate GIROT."
                                                         " Paraitrait-il que ce coffre est plutot énorme et que vous le trouverez ... rapidement ... "
                                                         "néanmoins il vous faudra résoudre son énigme pour pouvoir accéder à son contenu"
                                                         "\n"
                                                         "\n"
                                                         "Vous disposez d'un indice pour le localiser : "
                                                         , ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);                               // utilisation de la police

    irr::video::ITexture* command = driver->getTexture("data/info/indice.png") ;
    gui->addImage(command,ic::position2d< s32 >(x1+50,y1+200),true,window);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, UNDERSTOOD_BUTTON, L"UNDERSTOOD!");
    active_window = true;
}

void myWindows::create_window_room_2()
{
    irr::video::IVideoDriver *driver = device->getVideoDriver();

    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Welcome To The Club . ");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L" Bienvenue dans le Club CPE Baila Baila Baila \n"
                                                         "Vous trouverez sur les murs de ce club, une combinaison de chiffres. Assurez vous de trouver "
                                                         "la bonne combinaison pour pouvoir dévérouiller votre nain de jardin de téléportation suivant \n"
                                                         "Fonctionnement des Digits sur les murs : \n"
                                                         "    -Sélectionnez le digit souhaité à l'aide d'un clic gauche de la souris en pointant bien précisemment le digit voulu. \n "
                                                         "    -Modifiez sa valeur en utilisant la molette de votre souris.  ",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);                               // utilisation de la police

    irr::video::ITexture* command = driver->getTexture("data/info/commandes_2.png") ;
    gui->addImage(command,ic::position2d< s32 >(x1+50,y1+200),true,window);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, UNDERSTOOD_BUTTON, L"UNDERSTOOD!");
    active_window = true;
}


void myWindows::create_window_enigm_1()
{


    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Welcome To Our World");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"Pour ouvrir ce coffre vous devez trouver la date de naissance de ... Maxime Di Folco le Terrible (célèbre pour ses shots à 3 poissons)"
                                                         "Vous pouvez retourner sur l'ile ou faire des essais (illimités) de date. \n "
                                                         "Voici quelques indices pour la trouver : \n "
                                                         " - son jour de naissance est le premier nombre premier à 2 chiffres \n"
                                                         " -  l'été commence pendant son mois de naissance \n"
                                                         " - il va avoir 23 ans cette année.",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);                               // utilisation de la police

    texte = gui->addStaticText(L"Jour : \n", ic::rect<s32>(40,190,160,200), false,true,window);
//     texte->setOverrideFont(font);
    gui->addSpinBox(L"14", ic::rect<s32>(40,200, 160,220), true, window, DAY_SPIN);
    texte = gui->addStaticText(L"Mois : \n",ic::rect<s32>(40,230, 160,240), false,true,window);
//     texte->setOverrideFont(font);
    gui->addSpinBox(L"12", ic::rect<s32>(40,240, 160,260), true, window, MONTH_SPIN);
    texte = gui->addStaticText(L"Année : \n",  ic::rect<s32>(40,270, 160,280), false,true,window);
//     texte->setOverrideFont(font);
    gui->addSpinBox(L"1994", ic::rect<s32>(40,280, 160,300), true, window, YEAR_SPIN);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, TRY_BUTTON_1, L"Essai");
    gui->addButton(ic::rect<s32>(x1+160,y2-60, x1+160+150,y2-20), window, ClOSE_BUTTON_ENIGM_1, L"Retourner sur l'ile");

    active_window = true;
}

void myWindows::create_window_answer_enigm_1()
{


    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Answer");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"Félicitation, vous avez déverouiller le coffre et ainsi dévérouillez l'accès à la prochaine salle qui vous proposera l'énigme suivante."
                                                         " Le Nain de jardin qui vous y emmenera se trouve non loin de vous, proche de votre lieu d'arrivée,\n"
                                                         "Bon Courage et à très vite",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);
    texte->setOverrideFont(font);                               // utilisation de la police

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, ClOSE_BUTTON_ENIGM_1, L"Close Informations");

    active_window = true;
}

void myWindows::create_window_enigm_2()
{

}

/** ANswer enigm window 2 : Club */
void myWindows::create_window_answer_enigm_2()
{



    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"SUCCESS ROOM 2");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"Bravo ! Tu as réussi la deuxième enigme. Trouve le prochain téléporteur maintenant.",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,false,window);

    texte->setOverrideFont(font);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, UNDERSTOOD_BUTTON, L"Close Informations");

    answer_2=true;
    active_window = true;
}
void myWindows::create_windows_back_room_0()
{

    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Retour dans la ville");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L" De retour au point de départ ? Non, pas du tout ! Une nouvelle arche est apparu et tu as besoin de l'a trouver pour t'en sortir."
                                                         "   Mais attention, elle est difficile à trouver !",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);
    irr::gui::IGUIFont *font = gui->getFont("data/font_a/myfont.xml");  // chargement de la police
    texte->setOverrideFont(font);                               // utilisation de la police

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, ClOSE_BUTTON_ENIGM_1, L"UNDERSTOOD!");
    active_window = true;
}

void myWindows::create_window_enigm_final()
{



    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Enigme Finale");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"Tu as réussi à atteindre la dernière enigme ! \n Mais pour échapper de ce monde magique tu vas devoir "
                                                         "utiliser toutes tes méninges.\n"
                                                         "Quelle est le nombre suivant de cette suite logique  2, 10 ,12 ,17 ,18 ,19, ...? ",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,false,window);

    texte->setOverrideFont(font);

    gui->addSpinBox(L"19", ic::rect<s32>(40,280, 160,300), true, window, FINAL_SPIN);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, TRY_BUTTON_FINAL, L"Essai");
    gui->addButton(ic::rect<s32>(x1+160,y2-60, x1+160+150,y2-20), window, CLOSE_BUTTON_ENIGM_FINAL, L"Retournez dans la ville");

    active_window = true;
}

void myWindows::create_window_enigm_final_solution()
{


    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Enigme Finale");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"VICTOIRE !!!!!!! Clique sur Finish Game pour finir le jeu",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,false,window);


    texte->setOverrideFont(font);

    gui->addButton(ic::rect<s32>(x1+160,y2-60, x1+160+150,y2-20), window, CLOSE_GAME,L"Finish Game");

    active_window = true;
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
        if(!answer_2)
            create_window_enigm_2();
    case WINDOW_ANSWER_ENIGM_2:
        create_window_answer_enigm_2();
        break;
    case WINDOW_ENIGM_FINAL:
        create_window_enigm_final();
        break;
    case WINDOW_BACK_ROOM_0:
        create_windows_back_room_0();
        break;
    case END_GAME:
        create_window_enigm_final_solution();
        break;
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
/** Set Answer_2 */
void myWindows::setAnswer_2(bool b)
{
    answer_2=b;
}

/** Get Answer_2 */
bool myWindows::getAnswer_2() const
{
    return answer_2;
}
/** Get Answer_Final */
bool myWindows::getAnswer_Final() const
{
    return win_game;
}
/** Set Answer_Final */
void myWindows::setAnswer_Final(bool b)
{
    win_game=b;
}
/** Get the bool which show or not the window WINDOW_BACK_ROOM_0 */
bool myWindows::getBack_0_show() const
{
    return back_0;
}
/** Set the bool which show or not the window WINDOW_BACK_ROOM_0 */
void myWindows::setBack_0(bool b)
{
    back_0=b;
}
void myWindows::init_window_parameters()
{
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    const irr::core::dimension2du& screenSize = driver->getScreenSize();
    int w = screenSize.Width;
    int h = screenSize.Height;
    x1 = 10;
    x2 = w-10;
    y1 = 10;
    y2 = h-10;
}


