#ifndef PUBLICCONFIG_H
#define PUBLICCONFIG_H


// 版本设定
enum SCreen_Size
{
    SCREEN_SMALL = 0, // 小于1024 x 800
    SCREEN_MIDDLE = 1,// 正常
    SCREEN_BIG = 2,// 大于1920 x 1080
};
static int g_iSCreenSize;

class PublicConfig
{
public:
    PublicConfig();
};

#endif // PUBLICCONFIG_H
