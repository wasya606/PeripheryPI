#ifndef __MENUITEM_H__VDYKYY__
#define __MENUITEM_H__VDYKYY__
#include <functional>

class MenuItem
{
public:
    MenuItem(const size_t id, const char *name, const bool isDisabled = false);
    ~MenuItem();

    char* getName();
    size_t getId();

    bool getDisabled();
    void setDisabled(const bool isDisabled);

private:
    size_t id;
    char *name;
    bool isDisabled;
};

#endif // __MENUITEM_H__VDYKYY__
