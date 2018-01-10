// events.h

#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include "myWindows.hpp"
#include <irrlicht.h>


using namespace irr;

class EventReceiver : public irr::IEventReceiver
{
    /** Pointer to gui of the program */
    irr::gui::IGUIEnvironment *gui;
    /** Pointer to the node linked to the event receiver */
    irr::scene::ISceneNode *node;
    /** Pointer to the node corresponding to the digits of the enigm 2 */
    std::vector<irr::scene::IMeshSceneNode*> node_digits;
    /** Pointer to the device of the program */
    irr::IrrlichtDevice *device;
    /** State of the buttons of the mouse */
    bool button_pressed;
    /** Store position of the cursor */ // Is it useful ?
    int  old_x, old_y;
    /** Store the textures of the digits for enigm 2 */
    std::vector<irr::video::ITexture*> textures_digits;
    /** Store the active digit */ // not useful
    int active_digit;
    /** Store the current digits to display */
    int digit_0=0, digit_1=0, digit_2=0;
    /** Pointer to the `windows` created */
    myWindows *windows;

    /** Handling events of the keyboard */
    bool keyboard_handler(const irr::SEvent &event);
    /** Handling events of the mouse */
    bool mouse_handler(const irr::SEvent &event);
    /** Handling events of the gui */
    bool gui_handler(const irr::SEvent &event);

    /** Manage animation : node is moving */
    bool isMoving;
    /** Manage animation : node animation is `run` */
    bool animrun;
    /** store the current state of each key */
      bool KeyIsDown[KEY_KEY_CODES_COUNT];
public:
      /** Constructor */
    EventReceiver();
    /** Called on each iteration of the scene */
    bool OnEvent(const irr::SEvent &event);

    /** Set Gui */
    void set_gui(irr::gui::IGUIEnvironment *gui);
    /** Set current node handled by the EventReceiver */
    void set_node(irr::scene::ISceneNode *node);
    /** Set the digits nodes to handle */
    void set_node_digits(std::vector<irr::scene::IMeshSceneNode*> n);
    //  void set_node_digits(irr::scene::IMeshSceneNode* n);
    /** Set the device */
    void set_device(irr::IrrlichtDevice *d);
    /** Set textures of the digits */
    void set_textures_digits(const std::vector<irr::video::ITexture *> &tex){textures_digits=tex;}
    /** Set window of the gui */
    void set_windows(myWindows *w);
    /** Set state of the mouse buttons */
    bool is_mouse_pressed(int &x, int &y);
    /** Set active digits (enigm2) : the one that is clicked */
    void set_active_digit(int i);

    void init_boolean_animation();
    /** Get active digit */
    const std::vector<int> get_active_digit() const;
    /** Check status of a key */
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;

    /** EventReceiver::set_isMoving */
    void set_isMoving(bool b);
    /** EventReceiver::set_animrun */
    void set_animrun(bool b);
    /** EventReceiver::get_isMoving */
    bool get_isMoving() const;
    /** EventReceiver::get_animrun */
    bool get_animrun() const;
};

#endif
