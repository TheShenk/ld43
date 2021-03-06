/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#include "cocos2d.h"
#include "ActiveObject.h"
#include <vector>
#include <algorithm>

using namespace std;
using namespace cocos2d;

class Game : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    virtual void update(float);
    virtual void setAngle();

    virtual void createCollision();
    virtual bool checkCollision();


    virtual void createActive();
    virtual ActiveObject* checkActiveCollission();

    virtual void checkMove();
    virtual void trainMove();


    vector<Node*> collisionObjects;
    vector<ActiveObject*> activeObjects;

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

private:

    Sprite* sprite;
    Sprite* train;
    Sprite* inventorySprite;


    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};

