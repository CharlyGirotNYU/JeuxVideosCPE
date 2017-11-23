// main.cpp

#include <irrlicht.h>
#include<iostream>
#include "events.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

const int ENEMY_ID = 42;

int main()
{
    // Le gestionnaire d'événements
    EventReceiver receiver;
    std::vector<iv::ITexture*> textures;


    // Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d<u32>(640, 480),
                                          16, false, false, false, &receiver);

    iv::IVideoDriver    *driver = device->getVideoDriver();
    is::ISceneManager   *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui  = device->getGUIEnvironment();


    textures.push_back(driver->getTexture("data/base.pcx"));
    textures.push_back(driver->getTexture("data/red_texture.pcx"));
    textures.push_back(driver->getTexture("data/blue_texture.pcx"));
    // Chargement de notre personnage
    is::IAnimatedMesh *mesh = smgr->getMesh("data/tris.md2");

    // Attachement de notre personnage dans la scène
    is::IAnimatedMeshSceneNode *node;

    for (int i = -100; i <= 100; i += 40)
    {
        node = smgr->addAnimatedMeshSceneNode(mesh);
        node->setMaterialFlag(iv::EMF_LIGHTING, false);
        node->setMD2Animation(is::EMAT_STAND);
        node->setMaterialTexture(0, textures[0]);
        node->setPosition(ic::vector3df(i, 0, 0));
        node->setRotation(ic::vector3df(0, 90, 0));

        is::ITriangleSelector *selector = smgr->createTriangleSelector(node);
        node->setTriangleSelector(selector);
        selector->drop();
    }

    smgr->addCameraSceneNode(nullptr, ic::vector3df(0, 30, -40), ic::vector3df(0, 5, 0));

    // Chargement des textures pour les chiffres
    iv::ITexture *digits[10];
    digits[0] = driver->getTexture("data/0.png");
    digits[1] = driver->getTexture("data/1.png");
    digits[2] = driver->getTexture("data/2.png");
    digits[3] = driver->getTexture("data/3.png");
    digits[4] = driver->getTexture("data/4.png");
    digits[5] = driver->getTexture("data/5.png");
    digits[6] = driver->getTexture("data/6.png");
    digits[7] = driver->getTexture("data/7.png");
    digits[8] = driver->getTexture("data/8.png");
    digits[9] = driver->getTexture("data/9.png");

    // Création des places pour les chiffres
    ig::IGUIImage *score_10000 = gui->addImage(ic::rect<s32>(10,10,  50,50)); score_10000->setScaleImage(true);
    ig::IGUIImage *score_1000  = gui->addImage(ic::rect<s32>(50,10,  90,50)); score_1000->setScaleImage(true);
    ig::IGUIImage *score_100   = gui->addImage(ic::rect<s32>(90,10,  130,50)); score_100->setScaleImage(true);
    ig::IGUIImage *score_10    = gui->addImage(ic::rect<s32>(130,10, 170,50)); score_10->setScaleImage(true);
    ig::IGUIImage *score_1     = gui->addImage(ic::rect<s32>(170,10, 210,50)); score_1->setScaleImage(true);

    //Création des billboards
    irr :: scene :: IBillboardSceneNode * billboard ;
    billboard = smgr -> addBillboardSceneNode ( nullptr, ic::dimension2d <f32 >(50 , 80), ic::vector3df (0 , 0, 50));
    billboard -> setMaterialFlag ( iv::EMF_LIGHTING , false );
    billboard -> setMaterialType ( iv::EMT_TRANSPARENT_ALPHA_CHANNEL );
    billboard -> setMaterialTexture (0 , driver -> getTexture ("data/tree.png"));


    //ajout décor
    device->getFileSystem()->addFileArchive("data/map-20kdm2.pk3");
    is::IAnimatedMesh * mesh_decor = smgr->getMesh ("maps/20kdm2.bsp");
    is:: IMeshSceneNode * node_decor = smgr->addOctreeSceneNode (mesh_decor -> getMesh (0));
    node_decor->setPosition(ic::vector3df( -1350 , -130 , -1400));

    // Translation pour que nos personnages soient dans le décor
    //  node->setPosition(core::vector3df(-1300,-104,-1249));

    is :: ITriangleSelector * selector ;
    selector = smgr->createOctreeTriangleSelector(node_decor->getMesh(),node_decor);
    node_decor->setTriangleSelector(selector);

    is :: ITriangleSelector * selector_perso ;
    selector_perso = smgr->createOctreeTriangleSelector(node->getMesh(),node);
    node->setTriangleSelector(selector_perso);

    is :: ICameraSceneNode * camera ;
//    camera = smgr->addCameraSceneNodeFPS ( nullptr , 100 , 0.3 , -1, nullptr , 0, true , 3);
    camera = smgr->addCameraSceneNode();
    camera->setPosition (ic::vector3df (50 , 50 , -60));
    camera->setTarget (ic::vector3df ( -70 , 30 , -60));


    //Gestion de la collision
    is :: ISceneNodeAnimator * anim ;
    anim = smgr -> createCollisionResponseAnimator ( selector , camera ,ic :: vector3df (30 , 50 , 30) ,
                                                     ic :: vector3df (0 , -10 , 0) ,
                                                     ic :: vector3df (0 , 30 , 0));
    camera -> addAnimator ( anim );
    is :: ISceneNodeAnimator * anim_perso ;
    anim_perso = smgr -> createCollisionResponseAnimator ( selector_perso , camera ,ic :: vector3df (15 , 25 , 15) ,
                                                           ic :: vector3df (0 , 0 , 0) ,
                                                           ic :: vector3df (0 , 30 , 0));
    camera -> addAnimator(anim_perso);
    selector -> drop ();
    node->setID( ENEMY_ID );

    is::ISceneCollisionManager *collision_manager = smgr->getSceneCollisionManager();
    int score = 49500;
    std::vector<int> mouse_coord;
    while(device->run())
    {
        driver->beginScene(true, true, iv::SColor(0,50,100,255));


        int mouse_x,mouse_y;
        if(receiver.is_mouse_pressed(mouse_x,mouse_y))
        {
            ic::line3d<f32> ray;
            ray = collision_manager->getRayFromScreenCoordinates(ic::position2d<s32>(mouse_x, mouse_y));
            std::cout << mouse_x << " " << mouse_y<< std::endl;
            ic::vector3df intersection;
            ic::triangle3df hit_triangle;

            is::ISceneNode *selected_scene_node =
                    collision_manager->getSceneNodeAndCollisionPointFromRay(
                        ray,
                        intersection, // On récupère ici les coordonnées 3D de l'intersection
                        hit_triangle, // et le triangle intersecté
                        ENEMY_ID); // On ne veut que des noeuds avec cet identifiant

            if (selected_scene_node)
                selected_scene_node->setMaterialTexture(0, textures[1]);
        }

        // Dessin de la scène :
        smgr->drawAll();

        // Calcul du score :
        score++; if (score == 50000) score = 0;
        // Mise à jour du score :
        score_10000->setImage(digits[(score / 10000) % 10]);
        score_1000->setImage(digits[(score / 1000) % 10]);
        score_100->setImage(digits[(score / 100) % 10]);
        score_10->setImage(digits[(score / 10) % 10]);
        score_1->setImage(digits[(score / 1) % 10]);

        // Dessin de la GUI :
        gui->drawAll();
        driver->endScene();
    }
    device->drop();

    return 0;
}
