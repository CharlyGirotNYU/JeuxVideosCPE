#pragma once

#ifndef MY_WINDOWS_HPP
#define MY_WINDOWS_HPP

#include <irrlicht.h>
#include "gui_ids.h"

namespace ig = irr::gui;

/** Declaration of the Window class */
class myWindows
{

public:

    myWindows(ig::IGUIEnvironment *g, const irr::IrrlichtDevice *d);
    ~myWindows();


    void create_window();

    void create_menu();

    void create_window_begin();




//private slots:

    /** Quit the application */
//    void action_quit();


private:

    /** Layout for the Window */
    //    Ui::MainWindow *ui;
    /** gui linked to the scene */
    ig::IGUIEnvironment *gui;

    /** Irrlicht device */
    const irr::IrrlichtDevice *device;






};

#endif
