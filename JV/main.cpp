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

const int DIGITS_ID = 42;


/************************\
 * Load scenes
/************************/
static void load_scenes(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
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

    //TODO : add objects relative to history
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
    nodes.push_back(smgr->addMeshSceneNode(meshes[0]->getMesh(0), nullptr, -1));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, true);
    nodes[0]->setScale(ic::vector3df(30.0f));
    nodes[0]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    nodes[0]->setPosition(ic::vector3df(800.0f,-40.0f,-400));
    nodes[0]->setVisible(false);

    nodes.push_back(smgr->addMeshSceneNode(meshes[0]->getMesh(0), nullptr, -1));
    nodes[1]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[1]->setScale(ic::vector3df(30.0f));
    nodes[1]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    nodes[1]->setPosition(ic::vector3df(-800.0f,-40.0f,-400));
    nodes[1]->setVisible(false);

    nodes.push_back(smgr->addMeshSceneNode(meshes[0]->getMesh(0), nullptr, -1));
    nodes[2]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[2]->setScale(ic::vector3df(30.0f));
    nodes[2]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //nodeS[0]->setScale(ic::vector3df(1.0f)); //Not working
    nodes[2]->setPosition(ic::vector3df(170.0f,30.0f,20));
    nodes[2]->setVisible(false);
}


static void load_decors(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
                        std::vector<is::IMeshSceneNode*> &nodes,iv::IVideoDriver* &driver)
{
    meshes.push_back(smgr->getMesh("data/ISLAND/Chest.3DS"));
    nodes.push_back(smgr->addMeshSceneNode(meshes[0]->getMesh(0), nullptr, -1));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[0]->setScale(ic::vector3df(2.0f));
    //nodes[0]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    nodes[0]->setPosition(ic::vector3df(789.74-300, -25.9285, -377.781));
    nodes[0]->setVisible(false);

    //    nodes.push_back(smgr->addOctreeSceneNode(meshes[0]->getMesh(0), nullptr, -1, 1024));
    //    nodes[1]->setMaterialFlag(iv::EMF_LIGHTING, false);
    //    nodes[1]->setScale(ic::vector3df(30.0f));
    //    nodes[1]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    //    nodes[1]->setPosition(ic::vector3df(-800.0f,-40.0f,-400));
}


static void load_cubes(is::ISceneManager* &smgr, std::vector<is::IMeshSceneNode*> &nodes, std::vector<iv::ITexture *>digits ,iv::IVideoDriver* &driver)
{
    int z = -50;
    for (int i =0 ; i <3 ; ++i)
    {
        nodes.push_back(smgr->addCubeSceneNode(3.0f,0,DIGITS_ID,ic::vector3df(z,-20,111),ic::vector3df(0,0,0),ic::vector3df(3.0,3.0,0.01)));
        nodes[i]->setVisible(false);

        nodes[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        nodes[i]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        nodes[i]->setMaterialTexture(0, digits[0]);
        z+=50;
        is::ITriangleSelector *selector = smgr->createTriangleSelectorFromBoundingBox(nodes[i]);
        nodes[i]->setTriangleSelector(selector);
        selector->drop();
    }
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
    //    for(unsigned int i=0; i<nodes_arches.size(); i++)
    //    {
    //        nodes_arches[i]->setVisible(true);
    //        if(i == visible_node_decor-1)
    //            nodes_arches[i]->setVisible(false);
    //    }
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
                  std::vector<is::IMeshSceneNode*> &nodes_enigmes,
                  std::vector<is::IMeshSceneNode*> &nodes_cube,
                  scene::ICameraSceneNode* &camera,
                  int &visible_node_decor,
                  is::ISceneManager* &smgr,
                  scene::ITriangleSelector* &selector,
                  scene::ISceneNodeAnimator* &anim,
                  myWindows* &windows,
                  const EventReceiver receiver)
{

    ic::vector3df position = camera->getPosition();


    //Afficher le décor dans lequel on se trouve
    for(unsigned int i=0; i< nodes_decors.size(); i++)
    {
        if(i == (unsigned int) visible_node_decor )
            nodes_decors[i]->setVisible(true);
        else
            nodes_decors[i]->setVisible(false);
    }

    //Gestion de l'histoire
    std::vector<int> solution;
    solution = {9,0,7};
    switch(visible_node_decor)
    {
    case 0: // Decor ville
        if(!windows->getAnswer_2()) nodes_arches[0]->setVisible(true);
        nodes_arches[1]->setVisible(false);
        nodes_arches[2]->setVisible(false);
        nodes_enigmes[0]->setVisible(false);
        for(auto& node : nodes_cube)
            node->setVisible(false);
        break;

    case 1: //Decor island
        nodes_enigmes[0]->setVisible(true); // Coffre
        nodes_arches[0]->setVisible(false);
        nodes_arches[1]->setVisible(false);
        nodes_arches[2]->setVisible(false);
        for(auto& node : nodes_cube)
            node->setVisible(false);
        if(position.getDistanceFrom(nodes_enigmes[0]->getPosition()) < 60.0f)
        {
            if(!windows->getAnswer_1())
                windows->create_window(WINDOW_ENIGM_1);
            else
                windows->create_window(WINDOW_ANSWER_ENIGM_1);
        }

        std::cout << "Main answer 1 : "<< windows->getAnswer_1()<<std::endl;
        if(windows->getAnswer_1())
        {
            std::cout << "afficahge de l'arche"<<std::endl;
            nodes_arches[1]->setVisible(true); // Enigme résole -> affichage arches pour aller dans la salle suivante
        }
        break;

    case 2: //Decor Club
        nodes_arches[0]->setVisible(false);
        nodes_arches[1]->setVisible(false);
        if(!windows->getAnswer_2()) nodes_arches[2]->setVisible(false);
        for(auto& node : nodes_cube)
            node->setVisible(true);
        if(receiver.get_active_digit()[0] == solution[0] &&
                receiver.get_active_digit()[1] == solution[1] &&
                receiver.get_active_digit()[2] == solution[2] &&
                windows->getAnswer_2() == false)
        {
            windows->setAnswer_2(true);
            nodes_arches[2]->setVisible(true);
            windows->create_window(WINDOW_ANSWER_ENIGM_2);// On ne doit le faire qu'une fois ...
        }
        break;
    }


    bool colli = false;
    for(unsigned int i=0; i<nodes_arches.size(); i++)
    {
        //Changement couleur fonciton de la distance a l'arche

        //Entrée dans une salle si on passe dans l'arche

        //Si on est sur l'arche et que ce décor n'est pas encore activé (on désactive l'arche une fois qu'on est dedans)
        //        int idx_decor_suivant;
        //        if(i!=2)
        //            idx_decor_suivant = i+1;
        //        else
        //            idx_decor_suivant=0;
        if(position.getDistanceFrom(nodes_arches[i]->getPosition()) < 30.0f && !nodes_decors[(i+1)%3]->isVisible() && nodes_arches[i]->isVisible())
        {

            colli = true;
            //            std::cout << position.X << " " <<position.Y<<" "<< position.Z <<  std::endl;
            if(i != 2)
                visible_node_decor = i+1;
            else
                visible_node_decor = 0;

            update_selector(smgr, nodes_decors,selector,visible_node_decor);
            camera->removeAnimator(anim);
            anim = smgr->createCollisionResponseAnimator(selector,
                                                         camera,  // Le noeud que l'on veut gérer
                                                         ic::vector3df(10,10,10), // "rayons" de la caméra
                                                         ic::vector3df(0, -100, 0),  // gravité
                                                         ic::vector3df(0,10,0));  // décalage du centre
            camera->addAnimator(anim);
            update_cam_position(camera);

            switch(i)
            {
            case 0:
                windows->create_window(WINDOW_ROOM_1);
                break;
            case 1:
                windows->create_window(WINDOW_ROOM_2);
                break;
            default:
                break;
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
                                          ic::dimension2d<u32>(1024, 768),
                                          16, false, false, false, &receiver);

    iv::IVideoDriver    *driver = device->getVideoDriver();
    is::ISceneManager   *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui = device->getGUIEnvironment();

    // Load Scenes
    std::vector<is::IAnimatedMesh*> meshes_decors;
    std::vector<is::IMeshSceneNode*> nodes_decors;
    load_scenes(smgr,meshes_decors,nodes_decors,driver);

    // Load Personnages
    std::vector<is::IAnimatedMesh*> meshes_persos;
    std::vector<is::IAnimatedMeshSceneNode*> nodes_persos;
    load_persos(smgr,meshes_persos,nodes_persos,driver);

    // Load Arches
    std::vector<is::IAnimatedMesh*> meshes_arches;
    std::vector<is::IMeshSceneNode*> nodes_arches;
    load_arches(smgr,meshes_arches,nodes_arches,driver);

    //Load decors
    std::vector<is::IAnimatedMesh*> meshes_enigmes;
    std::vector<is::IMeshSceneNode*> nodes_enigmes;
    load_decors(smgr,meshes_enigmes,nodes_enigmes,driver);

    //Load cube for digits for enigm 2
    std::vector<is::IMeshSceneNode*> nodes_cube;
    std::vector<irr::video::ITexture *> digits;

    digits.push_back (driver->getTexture("data/digits/0.png"));
    digits.push_back (driver->getTexture("data/digits/1.png"));
    digits.push_back (driver->getTexture("data/digits/2.png"));
    digits.push_back (driver->getTexture("data/digits/3.png"));
    digits.push_back (driver->getTexture("data/digits/4.png"));
    digits.push_back (driver->getTexture("data/digits/5.png"));
    digits.push_back (driver->getTexture("data/digits/6.png"));
    digits.push_back (driver->getTexture("data/digits/7.png"));
    digits.push_back (driver->getTexture("data/digits/8.png"));
    digits.push_back (driver->getTexture("data/digits/9.png"));
    load_cubes(smgr,nodes_cube, digits,driver);


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
    //    bool enabled = camera_gui->isInputReceiverEnabled();
    //    camera_gui->setInputReceiverEnabled(!enabled);
    //    device->getCursorControl()->setVisible(enabled);

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
    receiver.set_node_digits(nodes_cube); //default
    receiver.set_textures_digits(digits);

    windows->create_window(WINDOW_BEGIN);



    scene::ICameraSceneNode* camera;
    camera = camera_FPS;
    receiver.set_camera(camera);
    bool previous_gui_state = windows->active_windows();
    // std::cout << "previous gui state " << previous_gui_state << std::endl;

    is::ISceneCollisionManager *collision_manager = smgr->getSceneCollisionManager();

    while(device->run())
    {



        driver->beginScene(true, true, iv::SColor(0,50,100,255));

        // Dessin de la scène :
        smgr->drawAll();

        // Dessin de l'interface utilisateur :
        gui->drawAll();



        if(previous_gui_state == true && windows->active_windows() == false)
        {
            camera_FPS->setInputReceiverEnabled(true);
            smgr->setActiveCamera(camera_FPS);
            camera = camera_FPS;
            previous_gui_state = windows->active_windows();
        }
        else if (previous_gui_state == false && windows->active_windows() == true)
        {
            camera_FPS->setInputReceiverEnabled(false);
            smgr->setActiveCamera(camera_gui);
            camera=camera_gui;
            previous_gui_state = windows->active_windows();
        }

        //Select digit to change during enigm 2
        int mouse_x, mouse_y;
        if (receiver.is_mouse_pressed(mouse_x, mouse_y))
        {
            ic::line3d<f32> ray;
            ray = collision_manager->getRayFromScreenCoordinates(ic::position2d<s32>(mouse_x, mouse_y));
            ic::vector3df intersection;
            ic::triangle3df hit_triangle;

            is::ISceneNode *selected_scene_node =
                    collision_manager->getSceneNodeAndCollisionPointFromRay(
                        ray,
                        intersection, // On récupère ici les coordonnées 3D de l'intersection
                        hit_triangle, // et le triangle intersecté
                        DIGITS_ID); // On ne veut que des noeuds avec cet identifiant
            for(int i=0; i<3; i++)
                if(selected_scene_node == nodes_cube[i])
                    receiver.set_active_digit(i);

            //              for (auto& no : nodes_cube)
            //                  if(selected_scene_node == no)
            //                          receiver.set_node_digits(no);
        }

        //When we change decors
        update_scene(nodes_decors, nodes_arches, nodes_persos, nodes_enigmes, nodes_cube,
                     camera, visible_node_decor,smgr,selector, anim, windows,receiver);


        //std::cout << "Camera position : " << camera->getPosition().X << " " << camera->getPosition().Y << " " << camera->getPosition().Z << std::endl;
        driver->endScene();
    }
    device->drop();

    return 0;
}



