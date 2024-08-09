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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

const int kTypeSize = 7; // 方块种类个数
const int kBlockNum = 4; // 方块的数量

class HelloWorld : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void UpdatePosition(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
    struct Porint {
        cocos2d::Sprite* sprite;
        int x;
        int y;
    };
    int _figures[kTypeSize][kBlockNum] = {
            1, 3, 5, 7, // I
            4, 6, 8, 7, // J
            3, 5, 7, 8, // L
            5, 7, 6, 8, // O
            3, 5, 6, 8, // S
            3, 5, 7, 6, // T
            4, 6, 5, 7  // Z
    };
    std::list<Porint> _points;
    Porint _current_block[kBlockNum];
    bool _is_left_pressed = false;
    bool _is_right_pressed = false;
    bool _is_up_pressed = false;
    bool _is_down_pressed = false;
};

#endif // __HELLOWORLD_SCENE_H__
