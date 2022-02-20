#pragma once
#include "Manager.h"
#include "Button.h"
class ButtonManager
{
public:
    bool onClick(Button* button);
    void onHover(Button* button, const char* idle, const char* hover);
};