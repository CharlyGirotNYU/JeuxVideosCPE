// events.h

#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include "myWindows.hpp"
#include <irrlicht.h>


using namespace irr;

class EventReceiver : public irr::IEventReceiver
{

    irr::gui::IGUIEnvironment *gui;
    irr::scene::ISceneNode *node;
    std::vector<irr::scene::IMeshSceneNode*> node_digits;
    //  irr::scene::IMeshSceneNode* node_digits;
    irr::IrrlichtDevice *device;
    bool button_pressed;
    int  old_x, old_y;
    std::vector<irr::video::ITexture*> textures;
    std::vector<irr::video::ITexture*> textures_digits;
    int current_texture;
    int active_digit;
    int digit_0=0, digit_1=0, digit_2=0;
    myWindows *windows;
    irr::scene::ICameraSceneNode *camera;


    bool keyboard_handler(const irr::SEvent &event);
    bool mouse_handler(const irr::SEvent &event);
    bool gui_handler(const irr::SEvent &event);

    bool isMoving;
    bool animrun;
    // We use this array to store the current state of each key
      bool KeyIsDown[KEY_KEY_CODES_COUNT];
public:
    EventReceiver();
    bool OnEvent(const irr::SEvent &event);
    void set_gui(irr::gui::IGUIEnvironment *gui);
    void set_node(irr::scene::ISceneNode *node);
    void set_node_digits(std::vector<irr::scene::IMeshSceneNode*> n);
    //  void set_node_digits(irr::scene::IMeshSceneNode* n);
    void set_device(irr::IrrlichtDevice *d);
    void set_textures(const std::vector<irr::video::ITexture *> &tex){textures=tex;}
    void set_textures_digits(const std::vector<irr::video::ITexture *> &tex){textures_digits=tex;}
    void set_windows(myWindows *w);
    void set_camera(irr::scene::ICameraSceneNode* c);
    bool is_mouse_pressed(int &x, int &y);
    void set_active_digit(int i);
    void init_boolean_animation();
    const std::vector<int> get_active_digit() const;

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
