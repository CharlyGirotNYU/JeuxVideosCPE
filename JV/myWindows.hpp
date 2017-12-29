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

    myWindows(ig::IGUIEnvironment *g, const irr::IrrlichtDevice *d);
    ~myWindows();


    void create_window();

    void create_menu();

    void create_window_begin();




    /** Get Active Windows */
    const std::vector<int> active_windows() const;
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

    /** List of active windows */
    std::vector<int> active_windows_data;






};

#endif
