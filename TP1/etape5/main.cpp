#include <irrlicht.h>

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;

struct MyEventReceiver : IEventReceiver
{
  bool OnEvent(const SEvent &event)
  {
    // Si l'événement est de type clavier (KEY_INPUT)
    // et du genre pressage de touche
    // et que la touche est escape, on sort du programme
    if (event.EventType == EET_KEY_INPUT_EVENT &&
        event.KeyInput.PressedDown)
    {
      ic::vector3df position = node->getPosition();
      ic::vector3df rotation = node->getRotation();
      switch (event.KeyInput.Key)
      {
        case KEY_ESCAPE:
          exit(0);
        case KEY_KEY_Z: // Avance
          position.X += 1 * cos(rotation.Y * M_PI / 180.0);
          position.Z += -1 * sin(rotation.Y * M_PI / 180.0);
          break;
        case KEY_KEY_S: // Recule
          position.X += -1 * cos(rotation.Y * M_PI / 180.0);
          position.Z += 1 * sin(rotation.Y * M_PI / 180.0);
          break;
        case KEY_KEY_D: // Tourne à droite
          rotation.Y += 10;
          break;
        case KEY_KEY_Q: // Tourne à gauche
          rotation.Y -= 10;
          break;
        default:;
      }
      node->setPosition(position);
      node->setRotation(rotation);
    }
    return false;
  }
  is::IAnimatedMeshSceneNode *node;
};

int main()
{
  // Le gestionnaire d'événements
  MyEventReceiver receiver;
  // Création de la fenêtre et du système de rendu.
  IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                        ic::dimension2d<u32>(640, 480),
                                        16, false, false, false, &receiver);

  iv::IVideoDriver  *driver = device->getVideoDriver();
  is::ISceneManager *smgr = device->getSceneManager();

  // Ajout de l'archive qui contient entre autres un niveau complet
  device->getFileSystem()->addFileArchive("data/map-20kdm2.pk3");

  // On charge un bsp (un niveau) en particulier :
  is::IAnimatedMesh *mesh = smgr->getMesh("20kdm2.bsp");
  is::ISceneNode *node;
  node = smgr->addOctreeSceneNode(mesh->getMesh(0), nullptr, -1, 1024);
  // Translation pour que nos personnages soient dans le décor
  node->setPosition(core::vector3df(-1300,-104,-1249));

  // Chargement de notre personnage (réutilisé plusieurs fois)
  is::IAnimatedMesh *mesh_perso = smgr->getMesh("data/tris.md2");

  // Attachement de notre personnage dans la scène
  is::IAnimatedMeshSceneNode *perso = smgr->addAnimatedMeshSceneNode(mesh_perso);
  receiver.node = perso;
  perso->setMaterialFlag(iv::EMF_LIGHTING, false);
  perso->setMD2Animation(is::EMAT_STAND);
  perso->setMaterialTexture(0, driver->getTexture("data/blue_texture.pcx"));

  // Un deuxième personnage, en rouge et qui cours entre deux points
  is::IAnimatedMeshSceneNode *perso_cours = smgr->addAnimatedMeshSceneNode(mesh_perso);
  perso_cours->setMaterialFlag(iv::EMF_LIGHTING, false);
  perso_cours->setMD2Animation(is::EMAT_RUN);
  perso_cours->setMaterialTexture(0, driver->getTexture("data/red_texture.pcx"));
  is::ISceneNodeAnimator *anim =
            smgr->createFlyStraightAnimator(ic::vector3df(-100,0,60),
            ic::vector3df(100,0,60), 3500, true);
  perso_cours->addAnimator(anim);

  // Un troisième personnage, qui saute en rond
  is::IAnimatedMeshSceneNode *perso_cercle = smgr->addAnimatedMeshSceneNode(mesh_perso);
  perso_cercle->setMaterialFlag(iv::EMF_LIGHTING, false);
  perso_cercle->setMD2Animation(is::EMAT_JUMP);
  perso_cercle->setMaterialTexture(0, driver->getTexture("data/red_texture.pcx"));
  is::ISceneNodeAnimator *anim_cercle =
            smgr->createFlyCircleAnimator(core::vector3df(30,0,0), 20.0f);
  perso_cercle->addAnimator(anim_cercle);

  // Camera fixe
  //smgr->addCameraSceneNode(nullptr, ic::vector3df(0, 30, -70), ic::vector3df(0, 5, 0));
  // Ou une caméra "jeu video à la première personne"
//  smgr->addCameraSceneNodeFPS();

  // Ou une caméra type modelleur
  smgr->addCameraSceneNodeMaya();

  is::ICameraSceneNode *camera = smgr->getActiveCamera();
  while(device->run())
  {
    driver->beginScene(true, true, iv::SColor(100,150,200,255));

    // Dessin de la scène :
    smgr->drawAll();
    // 
    //Ajout caméra qui suit un personnage (on suit perso_cours)
    camera->setTarget(perso_cercle->getPosition());
    driver->endScene();
  }
  device->drop();

  return 0;
}
