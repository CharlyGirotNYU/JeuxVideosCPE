#include <irrlicht.h>

using namespace irr;
namespace iv = irr::video;
namespace is = irr::scene;
namespace ic = irr::core;


struct MyEventReceiver : IEventReceiver
{
    is::IAnimatedMeshSceneNode *node;

    bool OnEvent(const SEvent &event)
    {
        //Si l'événement est de type clavier (KEY_INPUT)
        // et du genre pressage de touche
        // et que la touche est excape, on sort du programme
        if(event.EventType == EET_KEY_INPUT_EVENT &&
                event.KeyInput.PressedDown)
        {
            if(event.KeyInput.Key == KEY_ESCAPE)
                exit(0);
            if(event.KeyInput.Key == KEY_LEFT)
                node->setPosition(  node->getPosition() + ic::vector3df(-1,0,0) );
            if(event.KeyInput.Key == KEY_RIGHT)
                node->setPosition(  node->getPosition() + ic::vector3df(1,0,0) );
            if(event.KeyInput.Key == KEY_UP)
                node->setPosition(  node->getPosition() + ic::vector3df(0,0,1) );
            if(event.KeyInput.Key == KEY_DOWN)
                node->setPosition(  node->getPosition() + ic::vector3df(0,0,-1) );
        }

        return false;
    }
};





int main()
{
    //Le gestionnaire d'événement
    MyEventReceiver receiver;
    //Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d<u32>(640,480),
                                          16, false, false, false, &receiver);
    iv::IVideoDriver  *driver = device->getVideoDriver();
    is::ISceneManager *smgr = device->getSceneManager();

    //Chargement D'un personnage
    is::IAnimatedMesh *mesh = smgr->getMesh("data/tris.md2");
    receiver.node = smgr->addAnimatedMeshSceneNode(mesh);
    receiver.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    receiver.node->setMD2Animation(irr::scene::EMAT_SALUTE);
    receiver.node->setMaterialTexture(0,driver->getTexture("data/blue_texture.pcx"));

    is::IAnimatedMeshSceneNode *perso_cours =smgr->addAnimatedMeshSceneNode(mesh);;
    //is::ISceneNodeAnimator *anim = smgr->createFlyStraightAnimator(ic::vector3df(-100,0,60),ic::vector3df(100,0,60)
    //                                                               ,3500,true);
    is::ISceneNodeAnimator *anim = smgr->createFlyCircleAnimator(	receiver.node->getPosition(),100.f,0.001f,ic::vector3df(0.f, 1.f, 0.f),
                                                                    0.f,0.f
                                                                    );
    perso_cours->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    perso_cours->setMaterialTexture(0,driver->getTexture("data/red_texture.pcx"));
    perso_cours->addAnimator(anim);

    // Ajout de l’archive qui contient entre autres un niveau complet
    device->getFileSystem()->addFileArchive("data/map-20kdm2.pk3");
    // On charge un bsp (un niveau ) en particulier :
    is :: IAnimatedMesh *decor = smgr->getMesh("maps/20kdm2.bsp");
    is :: ISceneNode * node_decor ;
    node_decor = smgr->addOctreeSceneNode (decor->getMesh (0) , nullptr , -1 , 1024);
    // Translation pour que nos personnages soient dans le dé cor
    node_decor -> setPosition ( ic :: vector3df ( -1300 , -104 , -1249));

    //Définition d'une caméra (pour que notre personnage soit visible

    SKeyMap keyMap[4];
    keyMap[0].Action = EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = KEY_KEY_Z;

    keyMap[1].Action = EKA_MOVE_BACKWARD;
    keyMap[1].KeyCode = KEY_KEY_S;

    keyMap[2].Action = EKA_STRAFE_LEFT;
    keyMap[2].KeyCode = KEY_KEY_Q;

    keyMap[3].Action = EKA_STRAFE_RIGHT;
    keyMap[3].KeyCode = KEY_KEY_D;

//    smgr->addCameraSceneNode(nullptr, ic::vector3df(0,30,-40), ic::vector3df(0,5,0));
//      smgr->addCameraSceneNodeFPS(nullptr, 100.0f, 0.5f,-1, keyMap,4,false,0.f,false,true);
    smgr->addCameraSceneNodeMaya();
    smgr->getActiveCamera()->setTarget(receiver.node)

    while(device->run())
    {
        driver->beginScene(true, true, iv::SColor(100,150,200,255));

        // Dessin de la scène :
        smgr->drawAll();
        //
        driver->endScene();
    }
    device->drop();

    return 0;
}
