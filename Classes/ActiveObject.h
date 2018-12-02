//
// Created by shenk on 02.12.18.
//

#ifndef LD43_ACTIVEOBJECT_H
#define LD43_ACTIVEOBJECT_H

#include "cocos2d.h"

typedef void (*func)();

using namespace cocos2d;

class ActiveObject{

public:

    virtual void activate();
    std::function<void()> actFunc;
    Node* node;


};

#endif //LD43_ACTIVEOBJECT_H
