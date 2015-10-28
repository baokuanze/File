#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
    void tesTUserDefault();
    void testXmlParse();
    void testJsonParse();
    void copyFileToPath(std::string fileName);
    tinyxml2::XMLElement *tempElement;
    
};

#endif // __HELLOWORLD_SCENE_H__
