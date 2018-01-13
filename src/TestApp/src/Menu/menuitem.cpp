#include "menuitem.h"
#include <cstring>

MenuItem::MenuItem(const size_t id, const char *name, const bool isDisabled) : id(id), isDisabled(isDisabled)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

MenuItem::~MenuItem()
{
    if (name != nullptr)
    {
        delete[] name;
    }
}

char* MenuItem::getName()
{
    return name;
}

size_t MenuItem::getId()
{
    return id;
}

bool MenuItem::getDisabled()
{
    return isDisabled;
}

void MenuItem::setDisabled(const bool isDisabled)
{
    this->isDisabled = isDisabled;
}
