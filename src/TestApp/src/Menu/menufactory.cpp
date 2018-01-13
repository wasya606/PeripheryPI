#include "menufactory.h"

Menu* MenuFactory::createMainMenu(MenuHandler handler, int prev)
{
    Menu* menu = new Menu("****** MAIN MENU ******", handler, prev);
    menu->pushItem("Commands");
    menu->pushItem("Settings");
    menu->pushItem("About");
    menu->pushItem("Exit");
    return menu;
}

Menu* MenuFactory::createCommandsMenu(MenuHandler handler, int prev)
{
    Menu* menu = new Menu("****** COMMANDS ******", handler, prev);
    menu->pushItem("Register command");
    menu->pushItem("Unregister command");
    menu->pushItem("Run command");
    menu->pushItem("Show registered commands");
    menu->pushItem("Show avaliable functions");
    menu->pushItem("Run scenario from file");
    menu->pushItem("Run demo");
    menu->pushItem("Back");
    return menu;
}

Menu* MenuFactory::createSettingsMenu(MenuHandler handler, int prev)
{
    Menu* menu = new Menu("****** SETTINGS ******", handler, prev);
    menu->pushItem("Show/Edit settings");
    menu->pushItem("Load settings from file");
    menu->pushItem("Save settings to file");
    menu->pushItem("Reset all to default");
    menu->pushItem("Back");
    return menu;
}

Menu* MenuFactory::createFunctionsListMenu(MenuHandler handler, StringList& functionsList, int prev)
{
    Menu* menu = new Menu("****** AVALIABLE FUNCTIONS ******", handler, prev);

    for (size_t i = 0; i < functionsList.getSize(); i++)
    {
        menu->pushItem(functionsList[i]);
    }

    menu->pushItem("Back");
    return menu;
}

Menu *MenuFactory::createCmdListMenu(MenuHandler handler, int prev)
{
    Menu* menu = new Menu("****** TEST MENU ******", handler, prev);
    menu->pushItem("Test 1");
    menu->pushItem("Test 2");
    menu->pushItem("Test 3");
    menu->pushItem("Test 4");
    menu->pushItem("Back");
    return menu;
}
