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

    myWindows(ig::IGUIEnvironment *g);
    ~myWindows();


    void create_window();

    void create_menu();


//private slots:

    /** Quit the application */
//    void action_quit();


private:

    /** Layout for the Window */
    //    Ui::MainWindow *ui;
    /** gui linked to the scene */
    ig::IGUIEnvironment *gui;






};

#endif
