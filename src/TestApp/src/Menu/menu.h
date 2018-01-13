#ifndef __MENU_H__VDYKYY__
#define __MENU_H__VDYKYY__
#include "menuitem.h"
#include <functional>
#include <list>

using MenuHandler = std::function<void(MenuItem*)>;

class Menu
{
public:
    static int getKey();
    static void clearScreen();

public:
    Menu(const char* title, MenuHandler handler, int prev = -1);
    ~Menu();

    void pushItem(const char* name, const bool isDisabled = false);
    char* getTitle();
    int getPrev();
    void setPrev(int prev = -1);
    size_t getSize();
    MenuItem* getItem(size_t id);
    size_t getActiveItemId();
    void resetActiveItem();
    bool processStep(int keyCode);

private:
    void doStepUp();
    void doStepDown();

private:
    char *title;
    std::list<MenuItem*> items;
    size_t activeItemId;

    size_t size;
    int prev;

    MenuHandler handler;
};

#endif // __MENU_H__VDYKYY__
