// main.cpp

#include <irrlicht.h>

#include "events.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

int main()
{
    // Le gestionnaire d'événements
    EventReceiver receiver;
    std::vector<iv::ITexture*> textures;

    // Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d<u32>(640, 480),
                                          16, false, false, false, &receiver);

    iv::IVideoDriver  *driver = device->getVideoDriver();
    is::ISceneManager *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui = device->getGUIEnvironment();

    //Création fenetre "Settings"
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(420,25,620,460), false, L"Settings");
    gui->addStaticText(L"Value", ic::rect<s32>(22,48,65,66), false, false, window);
    gui->addButton(ic::rect<s32>(40,74,200,92), window, 1, L"Don't Click me Whatever happen");
    gui->addEditBox(L"1.0", ic::rect<s32>(65,46,160,66), true, window, 0);

    // Ajout de l'archive qui contient entre autres un niveau complet
    device->getFileSystem()->addFileArchive("data/map-20kdm2.pk3");

    // On charge un bsp (un niveau) en particulier :
    is::IAnimatedMesh *decor = smgr->getMesh("maps/20kdm2.bsp");
    is::ISceneNode *node_decor;
    node_decor = smgr->addOctreeSceneNode(decor->getMesh(0), nullptr, -1, 1024);
    // Translation pour que nos personnages soient dans le décor
    node_decor->setPosition(core::vector3df(-1300,-104,-1249));

    // Chargement de notre personnage
    is::IAnimatedMesh *mesh = smgr->getMesh("data/tris.md2");

    // Attachement de notre personnage dans la scène
    is::IAnimatedMeshSceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setMD2Animation(irr::scene::EMAT_STAND);
    textures.push_back(driver->getTexture("data/base.pcx"));
    textures.push_back(driver->getTexture("data/red_texture.pcx"));
    textures.push_back(driver->getTexture("data/blue_texture.pcx"));
    node->setMaterialTexture(0, textures[0]);
    is::ISceneNodeAnimator *anim_cercle =
            smgr->createFlyCircleAnimator(core::vector3df(30,0,0), 20.0f);
    node->addAnimator(anim_cercle);
    receiver.set_node(node);
    receiver.set_textures(textures);

    //    smgr->addCameraSceneNode(node, ic::vector3df(0, 30, -40), ic::vector3df(0, 5, 0));
    is::ICameraSceneNode *camera = smgr->addCameraSceneNodeMaya();

    receiver.set_camera(camera);

    while(device->run())
    {
        driver->beginScene(true, true, iv::SColor(0,50,100,255));

        // Dessin de la scène :
        smgr->drawAll();
        gui->drawAll();
        //
        camera->setTarget(node->getPosition());
        driver->endScene();
    }
    device->drop();

    return 0;
}
