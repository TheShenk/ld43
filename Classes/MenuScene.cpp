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

#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "globals.h"

USING_NS_CC;

Scene* GameMenu::createScene()
{
    return GameMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameMenu::init()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    MenuItemFont::setFontSize(20);
    auto menuItemFirst = MenuItemFont::create("Start the Game", CC_CALLBACK_1(GameMenu::firstMenuButtonTapped, this));
    auto menuItemSecond = MenuItemFont::create("Options", CC_CALLBACK_1(GameMenu::secondMenuButtonTapped, this));

    auto menuCenter = Menu::create(menuItemFirst, menuItemSecond, NULL);
    menuCenter->setPosition(Vec2(visibleSize.width/2.0, visibleSize.height/2.0));
    menuCenter->setColor(Color3B(255.0f, 255.0f, 255.0f));

    menuCenter->alignItemsVerticallyWithPadding(20.0f);

    this->addChild(menuCenter, 3);


    return true;
}

void GameMenu::firstMenuButtonTapped(Ref* pSender)
{
    auto nextScene = Game::createScene();
    auto director = Director::getInstance();
    director->pushScene(nextScene);
}

void GameMenu::secondMenuButtonTapped(Ref* pSender)
{
    log("Second menu tapped");
}
