// main.cpp

#include <irrlicht.h>

#include<iostream> //debug
#include "events.h"
#include "gui_ids.h"
#include <cmath>
#include "CMyLightManager.h"

#include "myWindows.hpp"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

/*===========================================================================*\
 * create_menu                                                               *
\*===========================================================================*/
//static void create_menu(ig::IGUIEnvironment *gui)
//{
//    ig::IGUIContextMenu *submenu;

//    // Les trois entrées principales :
//    ig::IGUIContextMenu *menu = gui->addMenu();
//    menu->addItem(L"File", -1, true, true);
//    menu->addItem(L"Debug", -1, true, true);
//    menu->addItem(L"Help", -1, true, true);

//    // Le contenu du menu File :
//    submenu = menu->getSubMenu(0);
//    submenu->addItem(L"New game...", MENU_NEW_GAME);
//    submenu->addSeparator();
//    submenu->addItem(L"Quit", MENU_QUIT);

//    // Le contenu du menu Debug :
//    submenu = menu->getSubMenu(1);
//    submenu->addItem(L"Bounding Box",   MENU_BOUNDING_BOX);
//    submenu->addItem(L"Show Normals",   MENU_NORMALS);
//    submenu->addItem(L"Show Triangles", MENU_TRIANGLES);
//    submenu->addItem(L"Transparency",   MENU_TRANSPARENCY);

//    // Le contenu du menu Help :
//    submenu = menu->getSubMenu(2);
//    submenu->addItem(L"About...", MENU_ABOUT);
//}

/*===========================================================================*\
 * create_window                                                             *
\*===========================================================================*/
//static void create_window(ig::IGUIEnvironment *gui)
//{
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
//}


/*
 * Load Decors
 */

static void load_decors(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
                        std::vector<is::IMeshSceneNode*> &nodes, iv::IVideoDriver* &driver)
{
    // Ajout de l'archive qui contient entre autres un niveau complet

    //Street
    meshes.push_back(smgr->getMesh("data/Street/Street_environment_V01.obj"));
    nodes.push_back(smgr->addOctreeSceneNode(meshes[0]->getMesh(0), nullptr, -1, 1024));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[0]->setScale(ic::vector3df(30.0f));
    nodes[0]->setPosition(ic::vector3df(0.0f,-50.0f,0.0f));

    //Island
    meshes.push_back(smgr->getMesh("data/ISLAND/island.obj"));
    nodes.push_back(smgr->addOctreeSceneNode(meshes[1]->getMesh(0), nullptr, -1, 1024));
    nodes[1]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[1]->setMaterialFlag(iv::EMF_GOURAUD_SHADING , false);
    nodes[1]->setPosition(ic::vector3df(0.0f,100.0f,0.0f));
    nodes[1]->setScale(ic::vector3df(50.0f));
    //nodes[1]->setRotation(ic::vector3df(90,0,0));

    meshes.push_back(smgr->getMesh("data/room2/Club.3DS"));
    nodes.push_back(smgr->addOctreeSceneNode(meshes[2]->getMesh(0), nullptr, -1, 1024));
    nodes[2]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[2]->setMaterialFlag(iv::EMF_GOURAUD_SHADING , true);
    nodes[2]->setPosition(ic::vector3df(0.0f,-50.0f,0.0f));
    nodes[2]->setScale(ic::vector3df(1.0f));
    //    nodes[2]->setMaterialTexture(0, driver->getTexture("data/bathroom/obj/BathroomOBJ.mtl"));
}

static void load_persos(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
                        std::vector<is::IAnimatedMeshSceneNode*> &nodes,iv::IVideoDriver* &driver)
{
    // Ajout de l'archive qui contient entre autres un niveau complet


    meshes.push_back(smgr->getMesh("data/base/tris.md2"));
    nodes.push_back(smgr->addAnimatedMeshSceneNode(meshes[0]));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[0]->setMD2Animation(is::EMAT_STAND);
    nodes[0]->setMaterialTexture(0, driver->getTexture("data/base/blue_texture.pcx"));

}

static void load_arches(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
                        std::vector<is::IMeshSceneNode*> &nodes,iv::IVideoDriver* &driver)
{
    meshes.push_back(smgr->getMesh("data/arbre1/Dwarf_2_Low.obj"));
    nodes.push_back(smgr->addOctreeSceneNode(meshes[0]->getMesh(0), nullptr, -1, 1024));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, true);
    nodes[0]->setScale(ic::vector3df(30.0f));
    nodes[0]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    nodes[0]->setPosition(ic::vector3df(800.0f,-40.0f,-400));

    nodes.push_back(smgr->addOctreeSceneNode(meshes[0]->getMesh(0), nullptr, -1, 1024));
    nodes[1]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[1]->setScale(ic::vector3df(30.0f));
    nodes[1]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    nodes[1]->setPosition(ic::vector3df(-800.0f,-40.0f,-400));
}

void create_lights(is::ISceneManager* &smgr,std::vector<is::IMeshSceneNode*> &nodes, f32 const lightRadius, iv::IVideoDriver* &driver)
{
    // And each cube has three lights attached to it.  The lights are attached to billboards so
    // that we can see where they are.  The billboards are attached to the cube, so that the
    // lights are indirect descendents of the same empty scene node as the cube.
    for( auto &node: nodes)
    {
        scene::IBillboardSceneNode * billboard = smgr->addBillboardSceneNode(node);
        billboard->setPosition(vector3df(0, -0.14, 0.30));
        billboard->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
        billboard->setMaterialTexture(0, driver->getTexture("data/lights/particle.bmp"));
        billboard->setMaterialFlag(video::EMF_LIGHTING, false);
        smgr->addLightSceneNode(billboard, vector3df(0, 0, 0), video::SColorf(1, 0, 0), lightRadius);

        billboard = smgr->addBillboardSceneNode(node);
        billboard->setPosition(vector3df(-0.21, -0.14, -0.21));
        billboard->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
        billboard->setMaterialTexture(0, driver->getTexture("data/lights/particlegreen.jpg"));
        billboard->setMaterialFlag(video::EMF_LIGHTING, false);
        smgr->addLightSceneNode(billboard, vector3df(0, 0, 0), video::SColorf(0, 1, 0), lightRadius);

        billboard = smgr->addBillboardSceneNode(node);
        billboard->setPosition(vector3df(0.21, -0.14, -0.21));
        billboard->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
        billboard->setMaterialTexture(0, driver->getTexture("data/lights/particlewhite.bmp"));
        billboard->setMaterialFlag(video::EMF_LIGHTING, false);
        smgr->addLightSceneNode(billboard, vector3df(0, 0, 0), video::SColorf(0, 0, 1), lightRadius);
    }
}

void update_selector(is::ISceneManager* &smgr, std::vector<is::IMeshSceneNode*> &nodes_decors,scene::ITriangleSelector* &selector, const int visible_node_decor )
{
    selector = smgr->createOctreeTriangleSelector(nodes_decors[visible_node_decor]->getMesh(), nodes_decors[visible_node_decor]);
    nodes_decors[visible_node_decor]->setTriangleSelector(selector);
}

void update_arches(std::vector<is::IMeshSceneNode*> &nodes_arches, int visible_node_decor)
{
    ic::vector3df pos0, pos1;
    switch(visible_node_decor)
    {
    case 0:
        pos0 = ic::vector3df(800.0f,-40.0f,-400);
        pos1 = ic::vector3df(-800.0f,-40.0f,-400);
    case 1:
        pos0 = ic::vector3df(100.0f,-40.0f,0);
        pos1 = ic::vector3df(-100.0f,-40.0f,-0);
    case 2:
        pos0 = ic::vector3df(100.0f,-40.0f,-00);
        pos1 = ic::vector3df(-100.0f,-40.0f,-00);
    }
    nodes_arches[0]->setPosition(pos0);
    nodes_arches[1]->setPosition(pos1);
//    nodes_arches[visible_node_decor-1]->setVisible(false);
    for(unsigned int i=0; i<nodes_arches.size(); i++)
    {
        nodes_arches[i]->setVisible(true);
        if(i == visible_node_decor-1)
            nodes_arches[i]->setVisible(false);
    }
}

void update_perso_1(scene::ICameraSceneNode* camera,is::IAnimatedMeshSceneNode* node_perso)
{
    ic::vector3df cam_pos = camera->getPosition();
    ic::vector3df cam_rot = camera->getRotation();
    ic::vector3df decalage = ic::vector3df(0.0f,0.0f,-50.0f);
    node_perso->setRotation(ic::vector3df(.0f,
                                          cam_rot.Y-90,
                                          0.0f));
    node_perso->setPosition(cam_pos-decalage);
}

void update_cam_position(scene::ICameraSceneNode* &camera)
{
    camera->setPosition(ic::vector3df(0,0,0));
}

void update_scene(std::vector<is::IMeshSceneNode*> &nodes_decors,
                   std::vector<is::IMeshSceneNode*> &nodes_arches,
                  std::vector<is::IAnimatedMeshSceneNode*> &nodes_persos,
                   scene::ICameraSceneNode* &camera,
                   int &visible_node_decor,
                   is::ISceneManager* &smgr,
                   scene::ITriangleSelector* &selector,
                   scene::ISceneNodeAnimator* &anim)
{
    for(unsigned int i=0; i< nodes_decors.size(); i++)
    {
        if(i == (unsigned int) visible_node_decor )
            nodes_decors[i]->setVisible(true);
        else
            nodes_decors[i]->setVisible(false);
    }
    bool colli = false;
    for(unsigned int i=0; i<nodes_arches.size(); i++)
    {
        //Changement couleur fonciton de la distance a l'arche

        //Entrée dans une salle si on passe dans l'arche
        ic::vector3df position = camera->getPosition();

        //Si on est sur l'arche et que ce décor n'est pas encore activé (on désactive l'arche une fois qu'on est dedans)
        if(position.getDistanceFrom(nodes_arches[i]->getPosition()) < 30.0f && !nodes_decors[i+1]->isVisible() )
        {

            colli = true;
            std::cout << position.X << " " <<position.Y<<" "<< position.Z <<  std::endl;
            visible_node_decor = i+1;
            update_selector(smgr, nodes_decors,selector,visible_node_decor);
            camera->removeAnimator(anim);
            anim = smgr->createCollisionResponseAnimator(selector,
                                                         camera,  // Le noeud que l'on veut gérer
                                                         ic::vector3df(10,10,10), // "rayons" de la caméra
                                                         ic::vector3df(0, -9, 0),  // gravité
                                                         ic::vector3df(0,10,0));  // décalage du centre
            camera->addAnimator(anim);
            update_cam_position(camera);

            std::cout << "after" << std::endl;
            std::cout << position.X << " " <<position.Y<<" "<< position.Z <<  std::endl;
            //TO DO : Change arches position funciton of the decor
            //Une arche d'un décor dans lequel on veut pas retourner -> en dehors de la map (c'est pas beau mais ca marche)
            //On place l'arche souhaité au bonne endroit

        }
    }
   if(colli) update_arches(nodes_arches,visible_node_decor);
    update_perso_1(camera,nodes_persos[0]);
}





int main()
{
    // Le gestionnaire d'événements
    EventReceiver receiver;
    int visible_node_decor = 0;

    // Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d<u32>(640, 480),
                                          16, false, false, false, &receiver);

    iv::IVideoDriver    *driver = device->getVideoDriver();
    is::ISceneManager   *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui = device->getGUIEnvironment();

    // Load Decors
    std::vector<is::IAnimatedMesh*> meshes_decors;
    std::vector<is::IMeshSceneNode*> nodes_decors;
    load_decors(smgr,meshes_decors,nodes_decors,driver);

    // Load Personnages
    std::vector<is::IAnimatedMesh*> meshes_persos;
    std::vector<is::IAnimatedMeshSceneNode*> nodes_persos;
    load_persos(smgr,meshes_persos,nodes_persos,driver);

    // Load Arches
    std::vector<is::IAnimatedMesh*> meshes_arches;
    std::vector<is::IMeshSceneNode*> nodes_arches;
    load_arches(smgr,meshes_arches,nodes_arches,driver);


    scene::ICameraSceneNode* camera =
            smgr->addCameraSceneNodeFPS(nullptr,
                                        100,         // Vitesse de rotation
                                        .2,          // Vitesse de déplacement
                                        -1,          // Identifiant
                                        nullptr, 0,  // Table de changement de touches
                                        true,        // Pas de possibilité de voler
                                        10);          // Vitesse saut


    // Création du triangle selector
    scene::ITriangleSelector *selector;
    selector = smgr->createOctreeTriangleSelector(nodes_decors[0]->getMesh(), nodes_decors[0]);
    nodes_decors[0]->setTriangleSelector(selector);


    // Création animateur collisionneur initiale avec le décor de départ
    scene::ISceneNodeAnimator *anim;
    anim = smgr->createCollisionResponseAnimator(selector,
                                                 camera,  // Le noeud que l'on veut gérer
                                                 ic::vector3df(1,15,10), // "rayons" de la caméra
                                                 ic::vector3df(0, -9, 0),  // gravité
                                                 ic::vector3df(0,10,0));  // décalage du centre
    camera->addAnimator(anim);

    //Création Lumière
    f32 const lightRadius = 6000.f; // Enough to reach the far side of each 'zone'

    create_lights(smgr,nodes_arches,lightRadius,driver);


    CMyLightManager * myLightManager = new CMyLightManager(smgr);
    smgr->setLightManager(myLightManager); // This is the default: we won't do light management until told to do it.
    device->setEventReceiver(myLightManager);

    // add a nice skybox

    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

    smgr->addSkyBoxSceneNode(
                driver->getTexture("data/media/irrlicht2_up.jpg"),
                driver->getTexture("data/media/irrlicht2_dn.jpg"),
                driver->getTexture("data/media/irrlicht2_lf.jpg"),
                driver->getTexture("data/media/irrlicht2_rt.jpg"),
                driver->getTexture("data/media/irrlicht2_ft.jpg"),
                driver->getTexture("data/media/irrlicht2_bk.jpg"));

    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

//    create_window(gui);

    myWindows windows(gui);
    windows.create_window();
    while(device->run())
    {
        driver->beginScene(true, true, iv::SColor(0,50,100,255));

        // Dessin de la scène :
        smgr->drawAll();
        // Dessin de l'interface utilisateur :
        gui->drawAll();

        //When we change decors
        update_scene(nodes_decors, nodes_arches, nodes_persos, camera, visible_node_decor,smgr,selector, anim);
//        update_perso_1(camera,nodes_persos[0]);

        driver->endScene();
    }
    device->drop();

    return 0;
}



