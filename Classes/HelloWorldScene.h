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
    // 以pos为中心顺时针旋转90度
    void RotatePoint90(int pos);

    // 以pos为中心逆时针旋转90度
    void RotatePointNeg90(int pos);

    // 旋转方块
    void Rotate();

    // 移动方块
    void Move(int dx, int dy);

    bool IsValidPosition();

    void Drop(float dt);

    void GetNewBlock();

    void FixBlock();
    
    void ClearLines();

    struct Point {
        cocos2d::Sprite* sprite;
        int x;
        int y;
    };

    void SetPosition(Point& point);

    int _figures[kTypeSize][kBlockNum] = {
            1, 3, 5, 7, // I
            1, 2, 4, 6, // J
            1, 2, 3, 5, // L
            1, 2, 3, 4, // O
            2, 3, 4, 5, // S
            1, 3, 4, 5, // T
            1, 3, 4, 6  // Z
    };
    enum BlockType { I = 0, J, L, O, S, T, Z };
    
    std::list<Point> _points;
    Point _current_block[kBlockNum];
    Point _previous_block[kBlockNum];
    BlockType _type;
    std::mt19937 _random_engine;
    bool _is_left_pressed = false;
    bool _is_right_pressed = false;
    bool _is_up_pressed = false;
    bool _is_down_pressed = false;

};

#endif // __HELLOWORLD_SCENE_H__
