/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 公用函数库文件
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#ifndef PUBLICFUNCTION_H
#define PUBLICFUNCTION_H
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QCameraInfo>
#include <QComboBox>
#include <QPainter>
#include <QProxyStyle>
#include "AdjustLight/common.h"
#include "AdjustLight/testing/ThreadTesting.h"
#include <QSqlDatabase>
#include "CommonDataWidget/CLabelCommoBoxWidget.h"
// 版本设定
enum Version_Config
{
    NORMAL_VERSION = 0, // 普通版本
    OTHER_VERSION = 1,//
    ADMIN_VERSION = 2,//
};
const int gk_iVersionConfig = NORMAL_VERSION;
// 测试页所有非结果数据(用户)结构体，便于数据传送
struct DetectorPageUserData
{
    // donor details
    QString strDonorFirstName;
    QString strDonorLastName;
    QDateTime qTestDateTime;
    QDate qBirthDate;
    QString strDonorID;
    QString strTestSite;
    // operator
    QString strOperator;// 操作者身份
    // adulterants
    QString bOxidant = "2";
    QString bSpecificGravity = "2";
    QString bPH = "2";
    QString bNitrite = "2";
    QString bCreatinine = "2";
    // reason
    bool bPreEmployment;
    bool bRandom;
    bool bReasonableSuspicionCause;
    bool bPostAccident;
    bool bReturnToDuty;
    bool bFollowUp;
    bool bOtherReason;
    QString strOtherReasonComments;
    QString strEmail;
    QString strAddress;
    // product details
    bool bTemperatureNormal;
    QString strProductDefinition =  "FiveFace";
    QString strExpriationDate;
    QString strProductLot;
    QString strProductID;
    int iProgramsNumber;//
};

/**
  * @brief 设置控件背景图片
  * @param pWidget:控件，非空
  * @param strImagepath:路径地址
  * @return
  */
void SetWidgetBackImage(QWidget *pWidget, QString strImagePath);
/**
  * @brief 设置控件背景色
  * @param pWidget：控件名称
  * @param qColor: 颜色
  * @return
  */
void SetWidgetBackColor(QWidget *pWidget, QColor qColor);
/**
  * @brief pushbutton背景图片
  * @param pButton:控件
  * @param strImagePath：路径
  * @return
  */
void SetButtonBackImage(QPushButton *pButton, QString strImagePath);
/**
  * @brief 设置Label背景图片
  * @param pLabel：控件
  * @param strImagePath：路径
  * @return
  */
void SetLabelBackImage(QLabel *pLabel, QString strImagePath);
/**
  * @brief 设置Label背景图片,绘制红色提示区域框，只为测试结果使用
  * @param
  * @return
  */
void SetLabelBackImageEx(QLabel *pLabel, QString strImagePath, QRect qRedRect);
/**
  * @brief 设置控件QSS样式
  * @param pWidget：控件
  * @param strQssFilePath：地址
  * @return
  */
void LoadQss(QWidget *pWidget, QString strQssFilePath);
/**
  * @brief 获取图片的base64值(PNG)
  * @param strImagePath：地址
  * @return
  */
QString GetImagePngBase64(QString strImagePath);
/**
  * @brief 连接数据库
  * @param strDBName：数据库路径名称
  * @return
  */
QSqlDatabase ConnectDataBase(const QString &kstrDBName);
/**
  * @brief 向TableWidget添加一行
  * @param pTableWidget：控件
  * @param strContentList：添加行数据的字符串数组
  * @return true：添加成功；false：添加失败
  */
bool InsertOneLine(QTableWidget *pTableWidget, QStringList strContentList);

bool InsertOneLine(QTableWidget *pTableWidget, QStringList strContentList, QComboBox *qComBox);
/**
  * @brief 向TableWidget某行某列添加Item
  * @param iRow：所在行
  * @param iColumn：所在列
  * @param strContent：Item显示的内容
  * @return true：添加成功；false：添加失败
  */
bool InsertOneItem(QTableWidget *pTableWidget, int iRow, int iColumn, QString strContent);
/**
  * @brief 错误类型弹框提示
  * @param eTypeError:错误类型
  * @return
  */
void TipErrorInfomation(EnumTypeErr eTypeError);
void TipErrorInfomation(ENUM_ERR eTestError);

/**
    * @brief 获取摄像头信息
    * @param
    * @param
    * @return
    */
QList<QCameraInfo> GetQCameraInfo();
/**
  * @brief 拼接图片类，当前为内部使用类，处理侧四结果拼接为打印图片，宽高固定
  * @param
  * @return
  */
class CFuseImageThread:public  QThread
{
    Q_OBJECT

public :
    explicit CFuseImageThread();
    virtual ~CFuseImageThread();
protected:
    virtual void run();
signals:
    void SignalFuseOk();// 拼接完成

public:
    void SetImagePaths(QStringList strImagePathList, QString strSaveImagePath,QStringList strResultImagePathList,QString strSaveResultImagePath);// 待拼接的图片
private:
    QStringList m_strImagePathList;
    QStringList m_strResultImagePathList;
    QString m_strSaveImagePath;
    QString m_strSaveResultImagePath;
    QPixmap *m_pPixmap;
    int m_iImageWidth;
    int m_iImageHeigth;
};
/**
  * @brief 删除图片线程，删除测试过程中产生的临时图片
  * @param
  * @return
  */
class CDeleteImageThread:public  QThread
{
    Q_OBJECT

public :
    explicit CDeleteImageThread();
protected:
    virtual void run();
signals:
    void SignalDeleteOk();// 删除完成

public:
    void SetImageDir(QString strImageDir);// 待删除的图片的路径
private:
    bool _RemoveFolderContent();
private:
    QString m_strImageDir;
};
/**
  * @brief 打印报告
  * @param
  * @return
  */
bool PrintToPage(QString strHtml);
/**
  * @brief 保存报告PDF
  * @param strHtml: 待保存的数据流
  * @param pWidget: 保存对话框父类
  * @return
  */
bool PrintToPdf(QString strHtml, QWidget *pWidget);
/**
  * @brief 获取TCube的HTML源文件
  * @param
  * @return
  */
QString GetTCubeHtmlStream();
/**
  * @brief 获取Cup的HTML源文件
  * @param
  * @return
  */
QString GetHtmlStream(QString strHtmlFilePath);
/**
  * @brief 获取本机MAC
  * @param
  * @return
  */
QString GetHostMacAddress();
/**
  * @brief 自定义TabBar
  * @param
  * @return
  */
class CCustomTabStyle : public QProxyStyle
{

public :
    explicit CCustomTabStyle();
    virtual ~CCustomTabStyle();
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const;
    void drawControl(ControlElement element, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const;

};



#endif // PUBLICFUNCTION_H
