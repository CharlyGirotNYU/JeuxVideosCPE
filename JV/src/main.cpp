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
*  Load scenes
*  ***********************/
static void load_scenes(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
                        std::vector<is::IMeshSceneNode*> &nodes, iv::IVideoDriver* &driver)
{
    //Street
    meshes.push_back(smgr->getMesh("../data/Street/Street_environment_V01.obj"));
    nodes.push_back(smgr->addOctreeSceneNode(meshes[0]->getMesh(0), nullptr, -1, 1024));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[0]->setScale(ic::vector3df(30.0f));
    nodes[0]->setPosition(ic::vector3df(0.0f,-50.0f,0.0f));

    //Island
    meshes.push_back(smgr->getMesh("../data/ISLAND/island.obj"));
    nodes.push_back(smgr->addOctreeSceneNode(meshes[1]->getMesh(0), nullptr, -1, 1024));
    nodes[1]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[1]->setMaterialFlag(iv::EMF_GOURAUD_SHADING , false);
    nodes[1]->setPosition(ic::vector3df(0.0f,100.0f,0.0f));
    nodes[1]->setScale(ic::vector3df(50.0f));

    meshes.push_back(smgr->getMesh("../data/room2/Club.3DS"));
    nodes.push_back(smgr->addOctreeSceneNode(meshes[2]->getMesh(0), nullptr, -1, 1024));
    nodes[2]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[2]->setMaterialFlag(iv::EMF_GOURAUD_SHADING , true);
    nodes[2]->setPosition(ic::vector3df(0.0f,-50.0f,0.0f));
    nodes[2]->setScale(ic::vector3df(1.0f));
}

/************************\
 * Load Personnages
 * **********************/
static void load_persos(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
                        std::vector<is::IAnimatedMeshSceneNode*> &nodes,iv::IVideoDriver* &driver)
{
    //Squellette
    meshes.push_back(smgr->getMesh("../data/base/tris.md2"));
    nodes.push_back(smgr->addAnimatedMeshSceneNode(meshes[0]));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[0]->setMD2Animation(is::EMAT_STAND);
    nodes[0]->setMaterialTexture(0, driver->getTexture("../data/base/blue_texture.pcx"));
    nodes[0]->setPosition(ic::vector3df(nodes[0]->getPosition().X,-30.0f,nodes[0]->getPosition().Z));
    nodes[0]->setRotation(ic::vector3df(0.0,-90.0,0.0));
}

/************************\
 * Load Arches
 * ***********************/
static void load_arches(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
                        std::vector<is::IMeshSceneNode*> &nodes,iv::IVideoDriver* &driver)
{
    //Chargement du Nain
    meshes.push_back(smgr->getMesh("../data/dwarf/Dwarf_2_Low.obj"));
    nodes.push_back(smgr->addMeshSceneNode(meshes[0]->getMesh(0), nullptr, -1));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, true);
    nodes[0]->setScale(ic::vector3df(30.0f));
    nodes[0]->setMaterialTexture(0, driver->getTexture("../data/dwarf/dwarf_2_1K_color.jpg"));
    nodes[0]->setPosition(ic::vector3df(800.0f,-40.0f,-400));
    nodes[0]->setVisible(false);

    nodes.push_back(smgr->addMeshSceneNode(meshes[0]->getMesh(0), nullptr, -1));
    nodes[1]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[1]->setScale(ic::vector3df(30.0f));
    nodes[1]->setMaterialTexture(0, driver->getTexture("../data/dwarf/dwarf_2_1K_color.jpg"));
    nodes[1]->setPosition(ic::vector3df(-800.0f,-40.0f,-400));
    nodes[1]->setVisible(false);

    nodes.push_back(smgr->addMeshSceneNode(meshes[0]->getMesh(0), nullptr, -1));
    nodes[2]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[2]->setScale(ic::vector3df(30.0f));
    nodes[2]->setMaterialTexture(0, driver->getTexture("../data/dwarf/dwarf_2_1K_color.jpg"));
    nodes[2]->setPosition(ic::vector3df(170.0f,30.0f,20));
    nodes[2]->setVisible(false);

    nodes.push_back(smgr->addMeshSceneNode(meshes[0]->getMesh(0), nullptr, -1));
    nodes[3]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[3]->setScale(ic::vector3df(30.0f));
    nodes[3]->setMaterialTexture(0, driver->getTexture("../data/dwarf/dwarf_2_1K_color.jpg"));
    nodes[3]->setPosition(ic::vector3df(1166.7,-24.9925,958.817));
    nodes[3]->setVisible(false);
}


static void load_decors(is::ISceneManager* &smgr, std::vector<is::IAnimatedMesh*> &meshes,
                        std::vector<is::IMeshSceneNode*> &nodes,iv::IVideoDriver* &driver)
{
    meshes.push_back(smgr->getMesh("../data/ISLAND/Chest.3DS"));
    nodes.push_back(smgr->addMeshSceneNode(meshes[0]->getMesh(0), nullptr, -1));
    nodes[0]->setMaterialFlag(iv::EMF_LIGHTING, false);
    nodes[0]->setScale(ic::vector3df(2.0f));
    nodes[0]->setPosition(ic::vector3df(789.74-300, -25.9285, -377.781));
    nodes[0]->setVisible(false);
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

static void load_paintings(is::ISceneManager* &smgr, std::vector<is::IMeshSceneNode*> &nodes, iv::ITexture *paintings[3] ,iv::IVideoDriver* &driver)
{
    std::vector<ic::vector3df> paintings_positions;
    paintings_positions.push_back(ic::vector3df(-106.5,20,-210));
    paintings_positions.push_back(ic::vector3df(-70,20,-236.2));
    paintings_positions.push_back(ic::vector3df(24.5,20,-236.5));
    //La premiere paintings a besoin d"une rotation
    ic::vector3df rotation = ic ::vector3df(0,90,0);

    for (int i =0 ; i <3 ; ++i)
    {
        nodes.push_back(smgr->addCubeSceneNode(3.0f,0,-1,paintings_positions[i],rotation,ic::vector3df(5.0,7.0,0.01)));
        nodes[i]->setVisible(true);

        nodes[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        nodes[i]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        nodes[i]->setMaterialTexture(0, paintings[i]);
        nodes[i]->setVisible(false);
        //On met la rotation pour les 2 autres paintings
        rotation = ic::vector3df(0,0,0);

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
        billboard->setMaterialTexture(0, driver->getTexture("../data/lights/particle.bmp"));
        billboard->setMaterialFlag(video::EMF_LIGHTING, false);
        smgr->addLightSceneNode(billboard, vector3df(0, 0, 0), video::SColorf(1, 0, 0), lightRadius);

        billboard = smgr->addBillboardSceneNode(node);
        billboard->setPosition(vector3df(-0.21, -0.14, -0.21));
        billboard->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
        billboard->setMaterialTexture(0, driver->getTexture("../data/lights/particlegreen.jpg"));
        billboard->setMaterialFlag(video::EMF_LIGHTING, false);
        smgr->addLightSceneNode(billboard, vector3df(0, 0, 0), video::SColorf(0, 1, 0), lightRadius);

        billboard = smgr->addBillboardSceneNode(node);
        billboard->setPosition(vector3df(0.21, -0.14, -0.21));
        billboard->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
        billboard->setMaterialTexture(0, driver->getTexture("../data/lights/particlewhite.bmp"));
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
    //TO DO : Pas utile d'afficher deux arches en meme temps, set leur position une seule fois dans le switch
    // en meme temps que set Visible dans le update_scene serait suffisant
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
}

/************************\
 * update position of perso relative to camera
 * ***********************/
void update_perso_1(scene::ICameraSceneNode* camera,is::IAnimatedMeshSceneNode* node_perso,EventReceiver &receiver)
{
    ic::vector3df position;
    ic::vector3df rotation;
    position = node_perso->getPosition();
    rotation = node_perso->getRotation();

    //Avance
    if(receiver.IsKeyDown(KEY_UP))
    {
        position.X += 4 * cos(rotation.Y * M_PI / 180.0) ;
        position.Z += -4 * sin(rotation.Y * M_PI / 180.0);
        receiver.set_isMoving(true);
    }
    //Recule
    if(receiver.IsKeyDown(KEY_DOWN))
    {
        position.X += -4 * cos(rotation.Y * M_PI / 180.0) ;
        position.Z += 4 * sin(rotation.Y * M_PI / 180.0) ;
        receiver.set_isMoving(true);
    }

    //Droite
    if(receiver.IsKeyDown(KEY_RIGHT))
        rotation.Y += 5 ;
    receiver.set_isMoving(true);

    //Gauche
    if(receiver.IsKeyDown(KEY_LEFT))
        rotation.Y -= 5 ;
    receiver.set_isMoving(true);

    if(camera != nullptr)
        camera->setTarget(node_perso->getPosition());

    node_perso->setPosition(position);
    node_perso->setRotation(rotation);

    if(receiver.IsKeyDown(KEY_UP) == false && receiver.IsKeyDown(KEY_DOWN)==false && receiver.IsKeyDown(KEY_RIGHT)==false && receiver.IsKeyDown(KEY_LEFT)==false)
        receiver.set_isMoving(false);

    if(receiver.get_isMoving() == true  && receiver.get_animrun() == false)    //Si le pointeur vers le mesh est ok , si l'on bouge et si l'on n'a pas encore mis à jour l'animation ...
    {
        node_perso->setMD2Animation(is::EMAT_RUN);//on passe à l'animation "courir"
        receiver.set_animrun(true);//on declare que l'animation courir est bien en trainde se derouler
    }
    if( receiver.get_isMoving() == false && receiver.get_animrun() ==true)    //Si le pointeur vers le mesh est ok , si l'on ne bouge plus et si l'on n'a pas encore mis à jour l'animation ...
    {
        node_perso->setMD2Animation(is::EMAT_STAND);//on passe à l'animation "rester en place"
        receiver.set_animrun(false);//et on declare que l'animation courir ne se deroule plus , du coup
    }


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
                  myWindows* &windows,
                  EventReceiver &receiver)
{
    //Afficher le décor dans lequel on se trouve
    for(unsigned int i=0; i< nodes_decors.size(); i++)
    {
        if(i == (unsigned int) visible_node_decor )
            nodes_decors[i]->setVisible(true);
        else
            nodes_decors[i]->setVisible(false);
    }

    //Gestion de l'histoire
    ic::vector3df position = nodes_persos[0]->getPosition();
    // Solution enigme 2
    std::vector<int> solution;
    solution = {9,0,7};

    switch(visible_node_decor)
    {
    case 0: // Decor ville
        nodes_arches[1]->setVisible(false);
        nodes_arches[2]->setVisible(false);
        nodes_enigmes[0]->setVisible(false);

        if(!windows->getAnswer_2())
            nodes_arches[0]->setVisible(true);
        else
            nodes_arches[3]->setVisible(true);

        for(auto& node : nodes_cube)
            node->setVisible(false);
        for(auto& node : nodes_paintings)
            node->setVisible(false);

        if(windows->getAnswer_Final())
        {
            windows->create_window(END_GAME);
        }
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
        if(windows->getAnswer_1())
            nodes_arches[1]->setVisible(true); // Enigme résole -> affichage arches pour aller dans la salle suivante
        break;

    case 2: //Decor Club
        nodes_arches[0]->setVisible(false);
        nodes_arches[1]->setVisible(false);
        nodes_persos[0]->setScale(ic::vector3df(0.5f,0.5f,0.5f));
        if(!windows->getAnswer_2()) nodes_arches[2]->setVisible(false);
        for(auto& node : nodes_cube)
            node->setVisible(true);

        for(auto& node : nodes_paintings)
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


    //test collision arches / Perso
    bool colli = false;
    for(unsigned int i=0; i<nodes_arches.size(); i++)
    {
        //TODO : Changement couleur fonciton de la distance a l'arche
        if(position.getDistanceFrom(nodes_arches[i]->getPosition()) < 25.0f && nodes_arches[i]->isVisible())
        {
            colli = true;
            if(i < 2)
                visible_node_decor = i+1;
            else
                visible_node_decor = 0;
            //Update le gestionnaire de collision en fonction du décor
            //TODO : peut etre vérifier qu'on est dans le bon décor avant de faire les changements suivant histoire d'être sur
            update_selector(smgr, nodes_decors,selector,visible_node_decor);
            nodes_persos[0]->removeAnimator(anim);
            anim = smgr->createCollisionResponseAnimator(selector,
                                                         nodes_persos[0],  // Le noeud que l'on veut gérer
                                                         ic::vector3df(10,8,10), // "rayons" de la caméra
                                                         ic::vector3df(0, -10, 0),  // gravité
                                                         ic::vector3df(-4,0,0));  // décalage du centre

            nodes_persos[0]->addAnimator(anim);

            //Reset le personnage au centre du nouveau décor
            //TO DO : sauf si collision avec arches de back 0 ??
            //if(windows->get_last_displayed_window() != WINDOW_ENIGM_FINAL)
            nodes_persos[0]->setPosition(ic::vector3df(0.0f,0.0f,0.0f));

            switch(i)
            {
            case 0:
                windows->create_window(WINDOW_ROOM_1);
                break;
            case 1:
                windows->create_window(WINDOW_ROOM_2);
                break;
            case 2:
                windows->create_window(WINDOW_BACK_ROOM_0);
                break;
            case 3:
                windows->create_window(WINDOW_ENIGM_FINAL);
                break;
            default:
                break;
            }

        }
    }
    //si il y a eu collision perso/arche changer l'arche visible
    //NB : Ne devrait plus être fait que dans update_scene , vu qu'une seule arche est affiché en même temps,
    // cetteupdate_arches devient obsolete
    if(colli) update_arches(nodes_arches,visible_node_decor);
    //gestion des animations et des déplacements du personnage (fortement lié a EventReceiver)
    update_perso_1(camera,nodes_persos[0],receiver);

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

    //Load digit textures for enigm 2
    digits.push_back (driver->getTexture("../data/digits/0.png"));
    digits.push_back (driver->getTexture("../data/digits/1.png"));
    digits.push_back (driver->getTexture("../data/digits/2.png"));
    digits.push_back (driver->getTexture("../data/digits/3.png"));
    digits.push_back (driver->getTexture("../data/digits/4.png"));
    digits.push_back (driver->getTexture("../data/digits/5.png"));
    digits.push_back (driver->getTexture("../data/digits/6.png"));
    digits.push_back (driver->getTexture("../data/digits/7.png"));
    digits.push_back (driver->getTexture("../data/digits/8.png"));
    digits.push_back (driver->getTexture("../data/digits/9.png"));
    load_cubes(smgr,nodes_cube, digits,driver);

    //Load paintings for digits for enigm 2
    std::vector<is::IMeshSceneNode*> nodes_painting;
    iv::ITexture *paintings[3];
    paintings[0] = driver->getTexture("../data/room2/enigme_9.jpg");
    paintings[1] = driver->getTexture("../data/room2/enigme_0.png");
    paintings[2] = driver->getTexture("../data/room2/enigme_7.jpg");
    load_paintings(smgr,nodes_painting, paintings,driver);

    //Create Gaming Camera
    scene::ICameraSceneNode *camera_FPS; //TODO : ce n'est plus une caméra FPS -> NOM à changer
    //nodes_persos[0]->setPosition(ic::vector3df(0,-30,0));
    ic::vector3df position_perso = nodes_persos[0]->getPosition();
    position_perso.X -=70;
    position_perso.Y +=100;

    camera_FPS = smgr->addCameraSceneNode(nodes_persos[0],position_perso-ic::vector3df(0.0f,40.0f,0.0f));
    camera_FPS->setTarget(position_perso);

    //Création GUI Caméra
    scene::ICameraSceneNode* camera_gui = smgr->addCameraSceneNode();
    device->getCursorControl()->setVisible(true);

    // Création du triangle selector
    scene::ITriangleSelector *selector;
    selector = smgr->createOctreeTriangleSelector(nodes_decors[visible_node_decor]->getMesh(), nodes_decors[visible_node_decor]);
    nodes_decors[visible_node_decor]->setTriangleSelector(selector);

    // Création animateur collisionneur initiale avec le décor de départ
    scene::ISceneNodeAnimator *anim;
    anim = smgr->createCollisionResponseAnimator(selector,
                                                 nodes_persos[0],  // Le noeud que l'on veut gérer
                                                 ic::vector3df(10,8,10), // "rayons" de la caméra
                                                 ic::vector3df(0, -10, 0),  // gravité
                                                 ic::vector3df(-4,0,0));  // décalage du centre

    nodes_persos[0]->addAnimator(anim);

    //Création Lumière pour les nains
    f32 const lightRadius = 6000.f; // Enough to reach the far side of each 'zone'
    create_lights(smgr,nodes_arches,lightRadius,driver);

    CMyLightManager * myLightManager = new CMyLightManager(smgr);
    smgr->setLightManager(myLightManager); // This is the default: we won't do light management until told to do it.

    // add a nice skybox
    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
    smgr->addSkyBoxSceneNode(
                driver->getTexture("../data/Skybox/irrlicht2_up.jpg"),
                driver->getTexture("../data/Skybox/irrlicht2_dn.jpg"),
                driver->getTexture("../data/Skybox/irrlicht2_lf.jpg"),
                driver->getTexture("../data/Skybox/irrlicht2_rt.jpg"),
                driver->getTexture("../data/Skybox/irrlicht2_ft.jpg"),
                driver->getTexture("../data/Skybox/irrlicht2_bk.jpg"));

    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);


    myWindows * windows = new myWindows(gui,device);
    windows->create_window(WINDOW_BEGIN);

    receiver.set_node(nodes_persos[0]);
    receiver.set_gui(gui);
    receiver.set_device(device);
    receiver.set_windows(windows);
    receiver.set_node_digits(nodes_cube); //default
    receiver.set_textures_digits(digits);
    receiver.init_boolean_animation();

    scene::ICameraSceneNode* camera;
    camera = camera_FPS;
    bool previous_gui_state = windows->active_windows();

    windows->set_begin_time(device->getTimer()->getTime());

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
        }

        //When we change decors
        update_scene(nodes_decors, nodes_arches, nodes_persos, nodes_enigmes, nodes_cube,  nodes_painting,
                     camera, visible_node_decor,smgr,selector, anim, windows,receiver);
        driver->endScene();
    }
    device->drop();

    return 0;
}



