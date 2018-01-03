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



/************************\
 * Load Decors
/************************/
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

/************************\
 * Load Personnages
 * **********************/

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

/************************\
 * Load Arches
 * ***********************/
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

/************************\
 * Create lights for arches
 * **********************/
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

/************************\
 * Update the triangle selector for collision
 * *************************/
void update_selector(is::ISceneManager* &smgr, std::vector<is::IMeshSceneNode*> &nodes_decors,scene::ITriangleSelector* &selector, const int visible_node_decor )
{
    selector = smgr->createOctreeTriangleSelector(nodes_decors[visible_node_decor]->getMesh(), nodes_decors[visible_node_decor]);
    nodes_decors[visible_node_decor]->setTriangleSelector(selector);
}

/************************\
 * Update arches (when decors change
 * ***********************/
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

/************************\
 * update position of perso relative to camera
 * ***********************/
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

/************************\
 * Update cam position quand décor change
 * *********************/
void update_cam_position(scene::ICameraSceneNode* &camera)
{
    camera->setPosition(ic::vector3df(0,0,0));
}

/************************\
 * update all elements of the scene
 * **********************/
void update_scene(std::vector<is::IMeshSceneNode*> &nodes_decors,
                  std::vector<is::IMeshSceneNode*> &nodes_arches,
                  std::vector<is::IAnimatedMeshSceneNode*> &nodes_persos,
                  scene::ICameraSceneNode* &camera,
                  int &visible_node_decor,
                  is::ISceneManager* &smgr,
                  scene::ITriangleSelector* &selector,
                  scene::ISceneNodeAnimator* &anim,
                  myWindows* &windows)
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
                                                         ic::vector3df(0, -100, 0),  // gravité
                                                         ic::vector3df(0,10,0));  // décalage du centre
            camera->addAnimator(anim);
            update_cam_position(camera);

            std::cout << "after" << std::endl;
            std::cout << position.X << " " <<position.Y<<" "<< position.Z <<  std::endl;
            //TO DO : Change arches position funciton of the decor
            //Une arche d'un décor dans lequel on veut pas retourner -> en dehors de la map (c'est pas beau mais ca marche)
            //On place l'arche souhaité au bonne endroit
            //EST CE QUE C'est toujours utile depuis l'utilisation de setVisible et de la désasctivation de l'animateur : THINK NO (Charly)

            //TODO : Display GUI to inform player about what to do in this map.
            //switch case for each map
            switch(i)
            {
            case 0:
                windows->create_window_room_1();
                break;
            default:;
            }

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

    //Create FPS Camera
    scene::ICameraSceneNode* camera_FPS =
            smgr->addCameraSceneNodeFPS(nullptr,
                                        100,         // Vitesse de rotation
                                        .2,          // Vitesse de déplacement
                                        -1,          // Identifiant
                                        nullptr, 0,  // Table de changement de touches
                                        true,        // Pas de possibilité de voler
                                        10);          // Vitesse saut


    //Création GUI Caméra
    scene::ICameraSceneNode* camera_gui = smgr->addCameraSceneNode();
    bool enabled = camera_gui->isInputReceiverEnabled();
    camera_gui->setInputReceiverEnabled(!enabled);
    device->getCursorControl()->setVisible(enabled);

     device->getCursorControl()->setVisible(true);

    // Création du triangle selector
    scene::ITriangleSelector *selector;
    selector = smgr->createOctreeTriangleSelector(nodes_decors[0]->getMesh(), nodes_decors[0]);
    nodes_decors[0]->setTriangleSelector(selector);

    // Création animateur collisionneur initiale avec le décor de départ
    scene::ISceneNodeAnimator *anim;
    anim = smgr->createCollisionResponseAnimator(selector,
                                                 camera_FPS,  // Le noeud que l'on veut gérer
                                                 ic::vector3df(1,15,10), // "rayons" de la caméra
                                                 ic::vector3df(0, -100, 0),  // gravité
                                                 ic::vector3df(0,10,0));  // décalage du centre
    camera_FPS->addAnimator(anim);

    //Création Lumière
    f32 const lightRadius = 6000.f; // Enough to reach the far side of each 'zone'
    create_lights(smgr,nodes_arches,lightRadius,driver);

    CMyLightManager * myLightManager = new CMyLightManager(smgr);
    smgr->setLightManager(myLightManager); // This is the default: we won't do light management until told to do it.
    //device->setEventReceiver(myLightManager); //What is it ?


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

    receiver.set_node(nodes_persos[0]);
    receiver.set_gui(gui);
    myWindows * windows = new myWindows(gui,device);
    receiver.set_device(device);
    receiver.set_windows(windows);
    windows->create_window(WINDOW_BEGIN);



    scene::ICameraSceneNode* camera;
    camera = camera_FPS;
    bool previous_gui_state = windows->active_windows();
   // std::cout << "previous gui state " << previous_gui_state << std::endl;
    while(device->run())
    {



        driver->beginScene(true, true, iv::SColor(0,50,100,255));

        // Dessin de la scène :
        smgr->drawAll();

        // Dessin de l'interface utilisateur :
        gui->drawAll();

        if(previous_gui_state == true && windows->active_windows() == false)
        {

            smgr->setActiveCamera(camera_FPS);
            previous_gui_state = windows->active_windows();
        }
        else if (previous_gui_state == false && windows->active_windows() == true)
        {
           smgr->setActiveCamera(camera_gui);
           previous_gui_state = windows->active_windows();
        }

        //When we change decors
        update_scene(nodes_decors, nodes_arches, nodes_persos, camera, visible_node_decor,smgr,selector, anim, windows);

        driver->endScene();
    }
    device->drop();

    return 0;
}



