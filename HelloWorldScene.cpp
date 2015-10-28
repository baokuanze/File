#include "HelloWorldScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
using namespace rapidjson;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
  //  tesTUserDefault();
   // std::string std="achievement.xml";
   // copyFileToPath(std);
    testJsonParse();
    //testXmlParse();
    
}

void HelloWorld:: tesTUserDefault(){
    //获取单例对象 //就像一个小的数据库
    UserDefault *de=UserDefault::getInstance();
    //获取一个可读可写的路径
    std::string path=FileUtils::getInstance()->getWritablePath();
    log("path=%s",path.c_str());
    de->setStringForKey("NAME", "张三");
    de->setStringForKey("PWD", "121212");
    //将修改写入文件保存生效
    de->flush();
    std::string name=de->getStringForKey("NAME","defaultname");
    log("name=%s",name.c_str());
}

void HelloWorld:: testXmlParse(){
    log("XMLParse");
    //获取可以写的路径
    std::string path=FileUtils::getInstance()->getWritablePath();

    std::string xmlPath=path+std::string("achievement.xml");
    log("xmlPath=%s",xmlPath.c_str());
    //加载文档
    XMLDocument *mydocument=new XMLDocument();
    XMLError errorId=mydocument->LoadFile(xmlPath.c_str());
    //判断是否解析错误
    if(errorId!=0 ){
        log("Parse Error");
        return;
    }
    //获取根节点
    //第一层
   // XMLElement *rootElement=mydocument->RootElement();
    //CCLOG("RootKey=%s",rootElement->Value());//获取建
   // log("RootValue=%s",rootElement->GetText());//获取值
    //第二层
   // XMLElement *chapterElement=rootElement->FirstChildElement();
   // log("chapterKeyElement=%s",chapterElement->Value());
    //log("chapterValueElement=%s",chapterElement->GetText());
    // 第三层 第一排
    
    if ( XMLElement *rootElement=mydocument->RootElement()) {
        XMLElement *element=rootElement->FirstChildElement();
        tempElement=element;
      }
    int i=0;
    do
    {  if(i++)
        tempElement=tempElement->NextSiblingElement();
        XMLElement *nameElement=tempElement->FirstChildElement();
        log("nameElement=%s",nameElement->Value());
        log("nameElement=%s",nameElement->GetText());
        //第二排
        XMLElement *numElement=nameElement->NextSiblingElement();
        log("num=%s",numElement->Value());//获取建
        int a=atoi(numElement->GetText());
        log("numValue=%d",a);//这里是获取值。
        //第三排
        XMLElement *lockElement=numElement->NextSiblingElement();
        log("locked=%s",lockElement->Value());
        log("locked=%d",atoi(lockElement->GetText()));
    }while (tempElement->NextSiblingElement());
    
//    //下一个Chapter
//    XMLElement *element=chapterElement->NextSiblingElement();
//    log("2chapterElement=%s",element->GetText());
//    log("2chapterElement=%s",element->Value());
//     //下一个的第一排
//    XMLElement *nameElement1=element->FirstChildElement();
//    log("nameElemt1=%s",nameElement1->Value());
//    log("nameElemt1=%s",nameElement1->GetText());
    

    //将字符串转为数字。
   
    //修改节点
/*    XMLNode *oldNode=numElement->FirstChild();
    log("oldNodeValue=%s",oldNode->Value());
    oldNode->SetValue("xiugaileaaaao");
    mydocument->SaveFile(xmlPath.c_str());//这个将修改保存到文件
    //添加节点。需要使用其父节点调用，若使用同等级的子节点，则会作为其子节点添加
    XMLElement *broadcast_Pid=mydocument->NewElement("AGE");//<AGE></AGE>
    XMLText *text1=mydocument->NewText("44444442");
    broadcast_Pid->SetAttribute("info", "the pid");
    broadcast_Pid->LinkEndChild(text1);//<AGE info=the pid> 3333</AGE>
    chapterElement->LinkEndChild(broadcast_Pid);//最后把这个节点加上了
    mydocument->SaveFile(xmlPath.c_str());
  */
  /*  //移除节点
    XMLElement *nameNode=chapterElement->FirstChildElement();
    chapterElement->DeleteChild(nameNode);
    mydocument->SaveFile(xmlPath.c_str());
    
 */
    
    
}
void HelloWorld:: testJsonParse(){
  //DOW,SAX
    FileUtils *fu=FileUtils::getInstance();
    std::string wrpath=fu->getWritablePath();
    //创建rapidjson::doucument类，用于操作json代码
    wrpath+="aa.json";//chushihua luji
    rapidjson::Document doc;
    std::string data=fu->getStringFromFile(wrpath);
     //乱码的问题解决; 
    std::string clearData(data);
   //拿到最后}的位置 。只是从反向查找
    size_t pos=clearData.rfind("}");
    //截取从0开始到“}”之后的字符串
    clearData=clearData.substr(0,pos+1);
             //模式
    doc.Parse<kParseDefaultFlags>(clearData.c_str());
    //判断解析是否出错
    if(doc.HasParseError()){
        log("GetParaseErro %s\n",doc.GetParseError());
    }
    //获取建对应的值
    rapidjson::Value &array=doc["Tollgate"]; //对应的是一个数组[]
    
    for (int i=0; i<array.Size();i++) {
        rapidjson::Value & first=array[i];//{}
        rapidjson::Value & type=first["Type2"]; //取出建对应的值
        rapidjson::Value & time=type["RefreshTime"]; //取出建对应的值
        printf("%d   ,%d次数----",time.GetInt(),i);
    }
    if (array.IsArray()) {
        int i=1;
        rapidjson::Value &first=array[i];
        rapidjson::Value &type=first["Type2"];
        rapidjson::Value &time=type["refreshTime"];
        time.SetInt(50);//修改内容
      //  printf("%d",time.GetInt());
    }
    //修改json内容之后重新写入
    StringBuffer buffer;//初始化缓存区
    rapidjson::Writer<StringBuffer>writer(buffer);//初始化写入器
    doc.Accept(writer);  //将doc内容放到write里面的buffer
    FILE *file=fopen(wrpath.c_str(), "wb");
    if (file) {
        fputs(buffer.GetString(), file);
        fclose(file);
    }
}

void HelloWorld:: copyFileToPath(std::string fileName){
    //拷贝文本  不能拷贝图片；
    //获取文件复制的原路径和目录路径
    FileUtils *fu=FileUtils::getInstance();
    std::string wrpath=fu->getWritablePath();
     wrpath+=fileName;
    log("%s",wrpath.c_str());
    if (!fu->isFileExist(wrpath)) {
        //获取app里面的路径
        std::string datapath=fu->fullPathForFilename(fileName.c_str());
        log("datapath=%s",datapath.c_str());
        //根据这个路径来获取到文件
        std::string pFileContent=fu->getStringFromFile(datapath);
       // CCLOG("%s",pFileContent.c_str());
        //将文件内容读出，写入到沙盒中
        FILE *file=fopen(wrpath.c_str(), "w");
        if (file) {
            fputs(pFileContent.c_str(), file);
            fclose(file);
        }
    }
}






