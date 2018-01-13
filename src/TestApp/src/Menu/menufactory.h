#ifndef MENUFACTORY_H
#define MENUFACTORY_H
#include "menu.h"
#include <list>

class MenuFactory
{
public:
    MenuFactory() = delete;

    static Menu* createMainMenu(MenuHandler handler, int prev = -1);
    static Menu* createCommandsMenu(MenuHandler handler, int prev = -1);
    static Menu* createSettingsMenu(MenuHandler handler, int prev = -1);
    static Menu* createFunctionsListMenu(MenuHandler handler, StringList& functionsList, int prev = -1);
    static Menu* createCmdListMenu(MenuHandler handler, int prev = -1);
};

#endif // MENUFACTORY_H
