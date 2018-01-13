#include "menu.h"
#include <cstring>
#include <stdio.h>
#include <iostream>

#ifdef _WIN32
    #include <conio.h>
    int Menu::getKey()
    {
        return getch();
    }

    void Menu::clearScreen()
    {
        system("cls");
    }
#else
    #include <termios.h>
    #include <unistd.h>

    int Menu::getKey()
    {
        struct termios oldt, newt;
        int ch;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
    }

    void Menu::clearScreen()
    {
        std::system("clear");
    }
#endif


Menu::Menu(const char *title, MenuHandler handler, int prev) : activeItemId(0), size(0)
{
    this->prev = prev;
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
    this->handler = handler;
}

Menu::~Menu()
{
    if (title != nullptr)
    {
        delete[] title;
    }

    for (auto it = items.begin(); it != items.end(); it++)
    {
        MenuItem* itemPtr = *it;
        if (itemPtr != nullptr)
            delete itemPtr;
    }
}

void Menu::pushItem(const char *name, const bool isDisabled)
{
    items.push_back(new MenuItem(size, name, isDisabled));
    size++;
}

char* Menu::getTitle()
{
    return title;
}

int Menu::getPrev()
{
    return prev;
}

void Menu::setPrev(int prev)
{
    this->prev = prev;
}

size_t Menu::getSize()
{
    return size;
}

MenuItem *Menu::getItem(size_t id)
{
    auto it = items.begin();
    for (size_t i = 0; it != items.end() && i < id; it++, i++);
    return *it;
}

size_t Menu::getActiveItemId()
{
    return activeItemId;
}

void Menu::resetActiveItem()
{
    activeItemId = 0;
    if (getItem(activeItemId)->getDisabled())
        doStepDown();
}

bool Menu::processStep(int keyCode)
{
    bool result = true;
    if (keyCode == 0 || keyCode == 224 || (keyCode == 27 && getKey() == 91))
    {
        int input = getKey();
        if (input == 72 || input == 65)
        {
            doStepUp();
        }
        else if (input == 80 || input == 66)
        {
            doStepDown();
        }
    }
    else if (keyCode == 13 || keyCode == 10)
    {
        handler(getItem(activeItemId));
    }
    else
    {
        result = false;
    }

    return result;

}

void Menu::doStepUp()
{
    activeItemId = activeItemId == 0 ? size - 1 : activeItemId - 1;
    if (getItem(activeItemId)->getDisabled())
        doStepUp();
}

void Menu::doStepDown()
{
    activeItemId = activeItemId == size - 1 ? 0 : activeItemId + 1;
    if (getItem(activeItemId)->getDisabled())
        doStepDown();

}
