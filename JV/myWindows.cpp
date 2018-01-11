
#include "myWindows.hpp"
#include<iostream> //debug
#include <sstream>

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
//namespace is = irr::scene;
//namespace iv = irr::video;

myWindows::myWindows(){}

myWindows::myWindows(ig::IGUIEnvironment *g,  irr::IrrlichtDevice *d):
    gui(g), device(d),driver(device->getVideoDriver()),screenSize(driver->getScreenSize()),
    w(screenSize.Width),h(screenSize.Height),x1(10),x2(w-10),y1(10),y2(h-10),font(gui->getFont("data/font_a/myfont.xml"))
{
}

myWindows::~myWindows()
{
}


void myWindows::create_window_begin()
{
    ig::IGUIWindow *window_begin = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Welcome To Our World");

    irr::gui::IGUIStaticText *texte =  gui->addStaticText(L"Vous n'auriez jamais du pénétrer notre monde. Vous en êtes maintenant le prisonnier. Laissez moi vous expliquer. Il y a bien longtemps, dans le temps du CPE antique "
                                                          "une momie se retrouva prise au piège de cette ville qui de plus n'était pas très jolie, ayant perdu beaucoup de décorations sur les facades de ses batiments. "
                                                          "Vous avez été appelé à l'aide pour aider MOMIE (et non pas MAMIE bien au chaud dans son canapé sous son plaid) à s'échapper. "
                                                          "Pour cela, il vous faudra résoudre les énigmes qui vous seront proposées par la suite. Chaque énigme vous mènera à la salle suivante par le biais des nains téléporteurs. "
                                                          "Des informations spécifiques vous seront données ultérieurement. "
                                                          "Pour démarrer, veuillez trouver le nain de jardin vous permettant de vous rendre à la salle de la première énigme \n"
                                                          "N'oubliez pas qu'à tout instant vous pouvez accéder aux informations d'aide : ESCAPE -> HELP "
                                                          , ic::rect<s32>(10,50,x2-50,y2-200), false,true,window_begin);

    texte->setOverrideFont(font);                               // utilisation de la police

    irr::video::ITexture* command = driver->getTexture("data/info/commandes.png") ;
    gui->addImage(command,ic::position2d< s32 >(x1,y2-300),true,window_begin);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window_begin, UNDERSTOOD_BUTTON, L"A la recherche du nain de jardin");
    active_window = true;
    last_active_window = WINDOW_BEGIN;
}

void myWindows::create_escape_menu()
{

    ig::IGUIWindow *window_escape = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"MENU ESCAPE");

    // Une liste déroulée
    ig::IGUIListBox *lbox = gui->addListBox(ic::rect<s32>(w/2-w/3, h/2-h/3, w/2+w/3, h/2+h/3), window_escape, WINDOW_ESCAPE_LIST_BOX, true);
    lbox->setItemHeight(h/5);
    lbox->addItem(L"RESUME");
    lbox->addItem(L"HELP");
    lbox->addItem(L"EXIT");

    lbox->setSelected(0);
    active_window = true;
}

void myWindows::create_window_room_1()
{
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Welcome To The Jungle . ");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L" Bien Joué ! Vous avez réussi à accéder à la Jungle."
                                                         " Il vous est ici demandé de trouver le coffre du redoutable pirate GIROT."
                                                         " Paraitrait-il que ce coffre est plutot énorme et que vous le trouverez ... rapidement ... "
                                                         "néanmoins il vous faudra résoudre son énigme pour pouvoir accéder à son contenu"
                                                         "\n"
                                                         "\n"
                                                         "Vous disposez d'un indice pour le localiser : (oui c'est bien la photo de l'énorme coffre) "
                                                         , ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);                               // utilisation de la police

    irr::video::ITexture* command = driver->getTexture("data/info/indice.png") ;
    gui->addImage(command,ic::position2d< s32 >(x1+50,y1+200),true,window);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, UNDERSTOOD_BUTTON, L"UNDERSTOOD!");
    active_window = true;
    last_active_window = WINDOW_ROOM_1;
}

void myWindows::create_window_room_2()
{
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Welcome To The Club . ");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L" Bienvenue dans le Club CPE Baila Baila Baila \n"
                                                         "Vous trouverez sur les murs de ce club, une combinaison de chiffres. Assurez vous de trouver "
                                                         "la bonne combinaison pour pouvoir dévérouiller votre nain de jardin de téléportation suivant \n"
                                                         "Fonctionnement des Digits sur les murs (Assurez vous de bien les comprendre, vous pouvez revenir ici à tout instant en utilisant ESCAPE->HELP: \n"
                                                         "    -Sélectionnez le digit souhaité à l'aide d'un clic gauche de la souris en pointant bien précisemment le digit voulu. \n "
                                                         "    -Modifiez sa valeur en utilisant la molette de votre souris.  ",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);                               // utilisation de la police

    irr::video::ITexture* command = driver->getTexture("data/info/commandes_2.png") ;
    gui->addImage(command,ic::position2d< s32 >(x1+50,y1+200),true,window);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, UNDERSTOOD_BUTTON, L"UNDERSTOOD!");
    active_window = true;
    last_active_window = WINDOW_ROOM_2;
}


void myWindows::create_window_enigm_1()
{
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Welcome To Our World");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"Pour ouvrir ce coffre vous devez trouver la date de naissance de ... Maxime Di Folco le Terrible (célèbre pour ses shots à 3 poissons)"
                                                         "Vous pouvez retourner sur l'ile ou faire des essais (illimités) de date. \n "
                                                         "Voici quelques indices pour trouver la date : \n "
                                                         " - son jour de naissance est le premier nombre premier à 2 chiffres \n"
                                                         " - l'été commence pendant son mois de naissance \n"
                                                         " - il va avoir 23 ans cette année 2018.",

                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);                               // utilisation de la police

    texte = gui->addStaticText(L"Jour : \n", ic::rect<s32>(40,190,160,200), false,true,window);
    gui->addSpinBox(L"14", ic::rect<s32>(40,200, 160,220), true, window, DAY_SPIN);
    texte = gui->addStaticText(L"Mois : \n",ic::rect<s32>(40,230, 160,240), false,true,window);
    gui->addSpinBox(L"12", ic::rect<s32>(40,240, 160,260), true, window, MONTH_SPIN);
    texte = gui->addStaticText(L"Année : \n",  ic::rect<s32>(40,270, 160,280), false,true,window);
    gui->addSpinBox(L"1994", ic::rect<s32>(40,280, 160,300), true, window, YEAR_SPIN);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, TRY_BUTTON_1, L"Essai");
    gui->addButton(ic::rect<s32>(x1+160,y2-60, x1+160+150,y2-20), window, ClOSE_BUTTON_ENIGM_1, L"Retourner sur l'ile");

    active_window = true;
}

void myWindows::create_window_answer_enigm_1()
{
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Answer");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"Félicitation, vous avez déverouillé le coffre et ainsi dévérouillé l'accès à la prochaine salle qui vous proposera l'énigme suivante."
                                                         " Le Nain de jardin qui vous y emmenera se trouve non loin de vous, proche de votre lieu d'arrivée,\n"
                                                         "Bon Courage et à très vite",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);                               // utilisation de la police

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, ClOSE_BUTTON_ENIGM_1, L"Close Informations");

    active_window = true;
    last_active_window = WINDOW_ANSWER_ENIGM_1;
}


/** ANswer enigm window 2 : Club */
void myWindows::create_window_answer_enigm_2()
{

    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"SUCCESS ROOM 2");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"Bravo ! Tu as réussi la deuxième enigme. Trouve le prochain Nain Téléporteur maintenant.",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, UNDERSTOOD_BUTTON, L"Close Informations");

    answer_2=true;
    active_window = true;
    last_active_window = WINDOW_ANSWER_ENIGM_2;
}
void myWindows::create_windows_back_room_0()
{

    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Retour dans la ville");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L" De retour au point de départ ? Non, pas du tout ! Un nouveau Nain Téléporteur est apparu et tu as besoin de la trouver pour t'en sortir."
                                                         "   Mais attention, elle est difficile à trouver !",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);
    irr::gui::IGUIFont *font = gui->getFont("data/font_a/myfont.xml");  // chargement de la police
    texte->setOverrideFont(font);                               // utilisation de la police

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, CLOSE_BUTTON_BACK_ROOM_0, L"UNDERSTOOD!");
    back_0=true;
    active_window = true;
    last_active_window = WINDOW_BACK_ROOM_0;
}

void myWindows::create_window_enigm_final()
{
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Enigme Finale");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"Tu as réussi à atteindre la dernière enigme ! \n Mais pour échapper de ce monde magique tu vas devoir "
                                                         "utiliser toutes tes méninges.\n"
                                                         "Quelle est le nombre suivant de cette suite logique  2, dix ,12 ,17 ,18 ,19, ...? ",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);

    gui->addSpinBox(L"19", ic::rect<s32>(40,280, 160,300), true, window, FINAL_SPIN);

    gui->addButton(ic::rect<s32>(x1,y2-60, x1+150,y2-20), window, TRY_BUTTON_FINAL, L"Essai");
    gui->addButton(ic::rect<s32>(x1+160,y2-60, x1+160+150,y2-20), window, CLOSE_BUTTON_ENIGM_FINAL, L"Retournez dans la ville");

    active_window = true;
    last_active_window = WINDOW_ENIGM_FINAL;
}

void myWindows::create_window_enigm_final_solution()
{
    time_end = device->getTimer()->getTime();
    int time = (time_end - time_begin ) / 1000;

    int minutes = (time)/60;
    int secondes = (time - 60*minutes);

    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(x1,y1, x2,y2), false, L"Enigme Finale");

    irr::gui::IGUIStaticText *texte = gui->addStaticText(L"VICTOIRE !!!!!!! Clique sur Finish Game pour finir le jeu: ",
                                                         ic::rect<s32>(10,50,x2-50,y2-200), false,true,window);

    irr::core::stringw a = L"VICTOIRE !!!!!!! Tu as mis : " ;
    irr::core::stringw d = irr::core::stringw(minutes).c_str();
    irr::core::stringw e = L" Minutes ";
    irr::core::stringw f = irr::core::stringw(secondes).c_str();
    irr::core::stringw g= L" secondes (attention : facile de confondre Zéro 0 et Huit 8) \nClique sur Finish Game pour finir le jeu ";

    irr::core::stringw str = a+d+e+f+g;
    irr::gui::IGUIStaticText *texte2 = gui->addStaticText(str.c_str(),
                                                          ic::rect<s32>(10,100,x2-50,y2-200), false,true,window);

    texte->setOverrideFont(font);
    texte2->setOverrideFont(font);

    gui->addButton(ic::rect<s32>(x1+160,y2-60, x1+160+150,y2-20), window, CLOSE_GAME,L"Finish Game");

    active_window = true;
    last_active_window = END_GAME;
}


void myWindows::create_window(int win_num)
{
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
        if(!active_windows()) //TODO : Should be replaced by a boolean proper to this windows or could create conflict or bug in windows display
            create_window_enigm_1();
        break;
    case WINDOW_ANSWER_ENIGM_1:
        create_window_answer_enigm_1();
        break;
//    case WINDOW_ENIGM_2:
//        if(!answer_2)
//            create_window_enigm_2();
//        break;
    case WINDOW_ANSWER_ENIGM_2:
        create_window_answer_enigm_2();
        break;
    case WINDOW_ENIGM_FINAL:
        create_window_enigm_final();
        break;
    case WINDOW_BACK_ROOM_0:
        if(!back_0)
            create_windows_back_room_0();
        break;
    case END_GAME:
        if(!active_windows())
            create_window_enigm_final_solution();
        break;
    default:
        break;
    }
}


bool myWindows::active_windows() const
{
    return active_window;
}

void myWindows::active_windows(bool b)
{
    active_window=b;
}

bool myWindows::getAnswer_1() const
{
    return answer_1;
}

void myWindows::setAnswer_1(bool b)
{
    answer_1=b;
}

void myWindows::setAnswer_2(bool b)
{
    answer_2=b;
}

bool myWindows::getAnswer_2() const
{
    return answer_2;
}

bool myWindows::getAnswer_Final() const
{
    return win_game;
}

void myWindows::setAnswer_Final(bool b)
{
    win_game=b;
}

bool myWindows::getBack_0_show() const
{
    return back_0;
}

void myWindows::setBack_0(bool b)
{
    back_0=b;
}

int myWindows::get_last_displayed_window()
{
    return last_active_window;
}

void myWindows::set_last_displayed_window(int w)
{
    last_active_window = w;
}

void myWindows::set_begin_time(float t)
{
    time_begin =t;
}
