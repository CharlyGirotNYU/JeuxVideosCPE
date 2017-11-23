// main.cpp

#include <iostream>

#include <irrlicht.h>

#include "events.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;

const int ENEMY_ID = 42;

int main()
{
  // Le gestionnaire d'événements
  EventReceiver receiver;
  iv::ITexture *base_texture;
  iv::ITexture *wounded_texture;

  // Création de la fenêtre et du système de rendu.
  IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                        ic::dimension2d<u32>(640, 480),
                                        16, false, false, false, &receiver);

  iv::IVideoDriver  *driver = device->getVideoDriver();
  is::ISceneManager *smgr = device->getSceneManager();

  base_texture    = driver->getTexture("data/base.pcx");
  wounded_texture = driver->getTexture("data/red_texture.pcx");

  // Chargement de notre personnage
  is::IAnimatedMesh *mesh = smgr->getMesh("data/tris.md2");

  // Création de plusieurs personnages
  is::IAnimatedMeshSceneNode *node;
  
  for (int i = -100; i <= 100; i += 40)
  {
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node->setMaterialFlag(iv::EMF_LIGHTING, false);
    node->setMD2Animation(is::EMAT_STAND);
    node->setMaterialTexture(0, base_texture);
    node->setPosition(ic::vector3df(i, 0, 0));
    node->setRotation(ic::vector3df(0, 90, 0));

    is::ITriangleSelector *selector = smgr->createTriangleSelector(node);
    node->setTriangleSelector(selector);
    selector->drop();    
  }

  is::ISceneCollisionManager *collision_manager = smgr->getSceneCollisionManager();

  smgr->addCameraSceneNode(nullptr, ic::vector3df(0, 30, -140), ic::vector3df(0, 5, 0));

  while(device->run())
  {
    driver->beginScene(true, true, iv::SColor(0,50,100,255));

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
                    ENEMY_ID); // On ne veut que des noeuds avec cet identifiant

      if (selected_scene_node)
        selected_scene_node->setMaterialTexture(0, wounded_texture);
    }

    // Dessin de la scène :
    smgr->drawAll();
    // 
    driver->endScene();
  }
  device->drop();

  return 0;
}
