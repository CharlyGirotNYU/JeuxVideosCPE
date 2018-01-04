#pragma once

#ifndef MY_WINDOWS_HPP
#define MY_WINDOWS_HPP

#include <irrlicht.h>
#include "gui_ids.h"
#include <vector>

namespace ig = irr::gui;

/** Declaration of the Window class */
class myWindows
{

public:

    myWindows();
    myWindows(ig::IGUIEnvironment *g, irr::IrrlichtDevice *d);
    ~myWindows();

    /** Method called to create a window */
    void create_window(int win_num);
    /** menu Bar */
    void create_menu();



    /** Get Active Windows */
    bool active_windows() const;
    /** Set Active_window */
    void active_windows(bool b);

    /** Get Answer_1 */
    bool getAnswer_1() const;
    /** Set Answer_1 */
    void setAnswer_1(bool b);
//private slots:

    /** Quit the application */
//    void action_quit();


private:

    /** Layout for the Window */
    //    Ui::MainWindow *ui;
    /** gui linked to the scene */
    ig::IGUIEnvironment *gui;

    /** Irrlicht device */
     irr::IrrlichtDevice *device;

     /** Answer 1 is OK ? */
     bool answer_1=false;



    /** List of active windows */
    bool active_window;

    /** Create beginning information winddow */
    void create_window_begin();
    /** Window diaplsayed when escape is pressed (RESUME, HELP (if developped), QUIT GAME)*/
    void create_escape_menu();
    /** Information window for room 1 */ //JUNGLE
    void create_window_room_1();
    /** Information window for room 2 */ //CLUB
    void create_window_room_2();
    /** Enigm window 1 : Jungle */
    void create_window_enigm_1();
    /** ANswer enigm window 1 : Jungle */
    void create_window_answer_enigm_1();
    /** Engim window 2 : Club */
    void create_window_enigm_2();





};

#endif
