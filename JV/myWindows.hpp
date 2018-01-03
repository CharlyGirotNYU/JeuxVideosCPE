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


    void create_window(int win_num);

    void create_menu();

    void create_window_begin();

    void create_escape_menu();

    void create_window_room_1();

    void create_window_room_2();




    /** Get Active Windows */
    bool active_windows() const;
    /** Set Active_window */
    void active_windows(bool b);
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

    /** List of active windows */
    bool active_window;






};

#endif
