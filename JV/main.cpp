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
    nodes.push_back(smgr->addOctreeSceneNode(meshes[0]->getMesh(0), nullptr, -1, 1024));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, true);
    nodes[0]->setScale(ic::vector3df(30.0f));
    nodes[0]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    nodes[0]->setPosition(ic::vector3df(800.0f,-40.0f,-400));
    nodes[0]->setVisible(false);

    nodes.push_back(smgr->addOctreeSceneNode(meshes[0]->getMesh(0), nullptr, -1, 1024));
    nodes[1]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[1]->setScale(ic::vector3df(30.0f));
    nodes[1]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    nodes[1]->setPosition(ic::vector3df(-800.0f,-40.0f,-400));
    nodes[1]->setVisible(false);
}


static void load_decors(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
                        std::vector<is::IMeshSceneNode*> &nodes,iv::IVideoDriver* &driver)
{
    meshes.push_back(smgr->getMesh("data/ISLAND/Chest.3DS"));
    nodes.push_back(smgr->addOctreeSceneNode(meshes[0]->getMesh(0), nullptr, -1, 1024));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[0]->setScale(ic::vector3df(2.0f));
    //nodes[0]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    nodes[0]->setPosition(ic::vector3df(789.74-300, -40.9285, -377.781));
    nodes[0]->setVisible(false);

    //    nodes.push_back(smgr->addOctreeSceneNode(meshes[0]->getMesh(0), nullptr, -1, 1024));
    //    nodes[1]->setMaterialFlag(iv::EMF_LIGHTING, false);
    //    nodes[1]->setScale(ic::vector3df(30.0f));
    //    nodes[1]->setMaterialTexture(0, driver->getTexture("data/arbre1/dwarf_2_1K_color.jpg"));
    //    //nodes[0]->setScale(ic::vector3df(1.0f)); //Not working
    //    nodes[1]->setPosition(ic::vector3df(-800.0f,-40.0f,-400));
}


static void load_cubes(is::ISceneManager* &smgr, std::vector<is::IMeshSceneNode*> &nodes, iv::ITexture *digits[10] ,iv::IVideoDriver* &driver)
{
    int z = -50;
    for (int i =0 ; i <3 ; ++i)
    {
        nodes.push_back(smgr->addCubeSceneNode(3.0f,0,-1,ic::vector3df(z,-20,100),ic::vector3df(0,0,0),ic::vector3df(3.0,3.0,0.01)));
        nodes[i]->setVisible(true);

        nodes[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        nodes[i]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        nodes[i]->setMaterialTexture(0, digits[0]);
        z+=50;
    }


}

static void load_paintings(is::ISceneManager* &smgr, std::vector<is::IMeshSceneNode*> &nodes, iv::ITexture *paintings[3] ,iv::IVideoDriver* &driver)
{
    std::vector<ic::vector3df> paintings_positions;
    paintings_positions.push_back(ic::vector3df(-97,14,-208));
    paintings_positions.push_back(ic::vector3df(-70,20,-236));
    paintings_positions.push_back(ic::vector3df(28,20,-236)); //AJuster le X

    for (int i =0 ; i <3 ; ++i)
    {
        nodes.push_back(smgr->addCubeSceneNode(3.0f,0,-1,paintings_positions[i],ic::vector3df(0,0,0),ic::vector3df(5.0,7.0,0.01)));
        nodes[i]->setVisible(true);

        nodes[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        nodes[i]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        nodes[i]->setMaterialTexture(0, paintings[i]);
        nodes[i]->setVisible(false);

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
                  std::vector<is::IMeshSceneNode*> &nodes_enigmes,
                  std::vector<is::IMeshSceneNode*> &nodes_cube,
                  std::vector<is::IMeshSceneNode*> &nodes_paintings,
                  scene::ICameraSceneNode* &camera,
                  int &visible_node_decor,
                  is::ISceneManager* &smgr,
                  scene::ITriangleSelector* &selector,
                  scene::ISceneNodeAnimator* &anim,
                  myWindows* &windows)
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
    switch(visible_node_decor)
    {
    case 0: // Decor ville
        nodes_arches[0]->setVisible(true);
        nodes_arches[1]->setVisible(true);

        break;
    case 1: //Decor island
        nodes_enigmes[0]->setVisible(true); // Coffre
        nodes_arches[0]->setVisible(false);
        nodes_arches[1]->setVisible(false);
        if(position.getDistanceFrom(nodes_enigmes[0]->getPosition()) < 60.0f)
            windows->create_window(WINDOW_ENIGM_1);

        std::cout << "Main answer 1 : "<< windows->getAnswer_1()<<std::endl;
        if(windows->getAnswer_1())
        {
            std::cout << "afficahge de l'arche"<<std::endl;
            nodes_arches[1]->setVisible(true); // Enigme résole -> affichage arches pour aller dans la salle suivante
        }
        break;
    case 2: //Decor Club
        for(auto& node : nodes_cube)
            node->setVisible(true);
        for(auto& node : nodes_paintings)
            node->setVisible(true);
        break;
    default:;



    }


    //Si sur l'ile afficher le trésor


    //    bool colli_coffre = false;
    //    for(unsigned int i=0; i<nodes_enigmes.size(); i++)
    //    {
    //        if( visible_node_decor == 1)
    //        {
    //            nodes_enigmes[0]->setVisible(true);

    //            if(position.getDistanceFrom(nodes_enigmes[i]->getPosition()) < 60.0f)
    //            {
    //                windows->create_window(WINDOW_ENIGM_1);
    //                camera->setPosition(camera->getPosition() + ic::vector3df(-50.0,0.0f,-50.0f));

    //                if(windows->getAnswer_1())
    //                    nodes_arches[1]->setVisible(true);
    //                else
    //                    nodes_arches[1]->setVisible(false);
    //            }
    //        }
    //        else
    //            nodes_enigmes[0]->setVisible(false);

    //    }

    bool colli = false;
    for(unsigned int i=0; i<nodes_arches.size(); i++)
    {
        //Changement couleur fonciton de la distance a l'arche

        //Entrée dans une salle si on passe dans l'arche

        //Si on est sur l'arche et que ce décor n'est pas encore activé (on désactive l'arche une fois qu'on est dedans)
        if(position.getDistanceFrom(nodes_arches[i]->getPosition()) < 30.0f && !nodes_decors[i+1]->isVisible() )
        {

            colli = true;
            //            std::cout << position.X << " " <<position.Y<<" "<< position.Z <<  std::endl;
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

            //            std::cout << "after" << std::endl;
            //            std::cout << position.X << " " <<position.Y<<" "<< position.Z <<  std::endl;
            //TO DO : Change arches position funciton of the decor
            //Une arche d'un décor dans lequel on veut pas retourner -> en dehors de la map (c'est pas beau mais ca marche)
            //On place l'arche souhaité au bonne endroit
            //EST CE QUE C'est toujours utile depuis l'utilisation de setVisible et de la désasctivation de l'animateur : THINK NO (Charly)

            //TODO : Display GUI to inform player about what to do in this map.
            //switch case for each map
            switch(i)
            {
            case 0:
                windows->create_window(WINDOW_ROOM_1);
                break;
            case 1:
                windows->create_window(WINDOW_ROOM_2);
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
    iv::ITexture *digits[10];
    digits[0] = driver->getTexture("data/digits/0.png");
    digits[1] = driver->getTexture("data/digits/1.png");
    digits[2] = driver->getTexture("data/digits/2.png");
    digits[3] = driver->getTexture("data/digits/3.png");
    digits[4] = driver->getTexture("data/digits/4.png");
    digits[5] = driver->getTexture("data/digits/5.png");
    digits[6] = driver->getTexture("data/digits/6.png");
    digits[7] = driver->getTexture("data/digits/7.png");
    digits[8] = driver->getTexture("data/digits/8.png");
    digits[9] = driver->getTexture("data/digits/9.png");
    load_cubes(smgr,nodes_cube, digits,driver);


    //Load paintings for digits for enigm 2
    std::vector<is::IMeshSceneNode*> nodes_painting;
    iv::ITexture *paintings[3];
    paintings[0] = driver->getTexture("data/room2/enigme_9.jpg");
    paintings[1] = driver->getTexture("data/room2/enigme_0.png");
    paintings[2] = driver->getTexture("data/room2/enigme_7.jpg");

    load_paintings(smgr,nodes_painting, paintings,driver);




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

    windows->create_window(WINDOW_BEGIN);



    scene::ICameraSceneNode* camera;
    camera = camera_FPS;
    receiver.set_camera(camera);
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

        //When we change decors
        update_scene(nodes_decors, nodes_arches, nodes_persos, nodes_enigmes, nodes_cube, nodes_painting,
                     camera, visible_node_decor,smgr,selector, anim, windows);


        std::cout << "Camera position : " << camera->getPosition().X << " " << camera->getPosition().Y << " " << camera->getPosition().Z << std::endl;
        driver->endScene();
    }
    device->drop();

    return 0;
}



