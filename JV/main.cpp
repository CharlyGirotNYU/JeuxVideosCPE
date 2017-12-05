// main.cpp

#include <irrlicht.h>

#include "events.h"
#include "gui_ids.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

/*===========================================================================*\
 * create_menu                                                               *
\*===========================================================================*/
static void create_menu(ig::IGUIEnvironment *gui)
{
  ig::IGUIContextMenu *submenu;

  // Les trois entrées principales :
  ig::IGUIContextMenu *menu = gui->addMenu();
  menu->addItem(L"File", -1, true, true);
  menu->addItem(L"Debug", -1, true, true);
  menu->addItem(L"Help", -1, true, true);

  // Le contenu du menu File :
  submenu = menu->getSubMenu(0);
  submenu->addItem(L"New game...", MENU_NEW_GAME);
  submenu->addSeparator();
  submenu->addItem(L"Quit", MENU_QUIT);

  // Le contenu du menu Debug :
  submenu = menu->getSubMenu(1);
  submenu->addItem(L"Bounding Box",   MENU_BOUNDING_BOX);
  submenu->addItem(L"Show Normals",   MENU_NORMALS);
  submenu->addItem(L"Show Triangles", MENU_TRIANGLES);
  submenu->addItem(L"Transparency",   MENU_TRANSPARENCY);

  // Le contenu du menu Help :
  submenu = menu->getSubMenu(2);
  submenu->addItem(L"About...", MENU_ABOUT);
}

/*===========================================================================*\
 * create_window                                                             *
\*===========================================================================*/
static void create_window(ig::IGUIEnvironment *gui)
{
  // La fenêtre
  ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(420,25, 620,460), false, L"Settings");

  // Une zone d'édition de texte, précédée d'un label
  gui->addStaticText(L"Value", ic::rect<s32>(22,48, 65,66), false, false, window);
  gui->addEditBox(L"1.0", ic::rect<s32>(65,46, 160,66), true, window, WINDOW_VALUE);

  // Un bouton à clicker
  gui->addButton(ic::rect<s32>(40,74, 140,92), window, WINDOW_BUTTON, L"Click me!");

  // Une case à cocher
  gui->addCheckBox(true, ic::rect<s32>(40,100, 140,118), window, WINDOW_CHECK_BOX, L"Select me!");

  // Une boite combo (une liste déroulante)
  gui->addStaticText(L"Choose one: ", ic::rect<s32>(22,126, 100,142), false, false, window);
  ig::IGUIComboBox *cbox = gui->addComboBox(ic::rect<s32>(100,126, 180,142), window, WINDOW_COMBO_BOX);
  cbox->addItem(L"Choice 1", WINDOW_COMBO_CHOICE_1);
  cbox->addItem(L"Choice 2", WINDOW_COMBO_CHOICE_2);
  cbox->addItem(L"Choice 3", WINDOW_COMBO_CHOICE_3);

  // Une liste déroulée
  gui->addStaticText(L"List:", ic::rect<s32>(22,150, 65,168), false, false, window);
  ig::IGUIListBox *lbox = gui->addListBox(ic::rect<s32>(40,170, 160,242), window, WINDOW_LIST_BOX, true);
  lbox->addItem(L"First Entry");
  lbox->addItem(L"Second Entry");
  lbox->addItem(L"Third Entry");

  // Une barre de défilement
  gui->addScrollBar(true, ic::rect<s32>(22,250, 160,268), window, WINDOW_SCROLLBAR);

  // Une spin box
  gui->addSpinBox(L"18.0", ic::rect<s32>(40,280, 160,298), true, window, WINDOW_SPIN_BOX);
}  

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
  ig::IGUIEnvironment *gui = device->getGUIEnvironment();

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
  receiver.set_gui(gui);
  receiver.set_node(node);
  receiver.set_textures(textures);

  //Ajout image 2D
  irr :: video :: ITexture * tex = driver -> getTexture ("data/0.png");
  irr :: gui :: IGUIImage * image = gui -> addImage ( irr :: core :: rect <s32 >(10 ,10 , 50 ,50));
  image -> setScaleImage ( true );
  image -> setImage ( tex );
  irr :: video :: ITexture * tex1 = driver -> getTexture ("data/1.png");
  irr :: gui :: IGUIImage * image1 = gui -> addImage ( irr :: core :: rect <s32 >(60 ,10 , 110 ,50));
  image1 -> setScaleImage ( true );
  image1 -> setImage ( tex1 );


  smgr->addCameraSceneNode(nullptr, ic::vector3df(0, 30, -40), ic::vector3df(0, 5, 0));

  // Création de notre Gui
  // Choix de la police de caractères
  ig::IGUISkin* skin = gui->getSkin();
  ig::IGUIFont* font = gui->getFont("data/fontlucida.png");
  skin->setFont(font);

  // La barre de menu
  create_menu(gui);

  // Une fenêtre pour différents réglages
  create_window(gui);

  while(device->run())
  {
    driver->beginScene(true, true, iv::SColor(0,50,100,255));

    // Dessin de la scène :
    smgr->drawAll();
    // Dessin de l'interface utilisateur :
    gui->drawAll();

    driver->endScene();
  }
  device->drop();

  return 0;
}
