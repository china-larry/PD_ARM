/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 登陆页面Widget，用户登陆操作
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CLoginInWidget.h"
#include <QBoxLayout>
#include <QFont>
#include <QPixmap>
#include <QBitmap>
#include <QPalette>
#include <QMouseEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include <QApplication>
#include "PublicFunction.h"
#include "AdjustLight/CHidCmdThread.h"

CLoginInWidget::CLoginInWidget(QWidget *parent) : QWidget(parent)
{
    //
    this->setFixedSize(1024, 600);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    // 设置b背景图片
    if(gk_iVersionConfig == PIS_VERSION)
    {
        SetWidgetBackImage(this, ":/image/ico/login/PIS_login_bgr.png");
    }
    else if(gk_iVersionConfig == MD_VERSION)
    {
        SetWidgetBackImage(this, ":/image/ico/login/MD_login_bgr.png");
    }
    else
    {
        SetWidgetBackImage(this, ":/image/ico/login/wondfo_login_bgr.png");
    }
    //
    LoadQss(this, ":/qss/LoginPage/LoginPage.qss");
    //
    _InitWidget();
    _InitLayout();
    // 数据库
    m_strDatabaseName = "\\drug.db";
    m_iUserPower = 2;//
    m_strAdminUserName = "admin";
    m_strAdminPassWord = "123";
    m_strModifyUserName = "wfip201";
    m_strModifyPassWord = "3688";
    // 焦点定位
    m_pUserNameLineEdit->setFocus();
    //
    m_bLeftButtonCheck = false;
}


void CLoginInWidget::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton)
    {
        m_iPressPoint = event->globalPos();
        m_bLeftButtonCheck = true;
    }
    event->ignore();//表示继续向下传递事件，其他的控件还可以去获取
}

void CLoginInWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
    {
        m_bLeftButtonCheck = false;
    }
    event->ignore();
}

void CLoginInWidget::mouseMoveEvent(QMouseEvent *event)
{
    if( m_bLeftButtonCheck )
    {
        m_iMovePoint = event->globalPos();
        this->move( this->pos() + m_iMovePoint - m_iPressPoint );
        m_iPressPoint = m_iMovePoint;
    }
    event->ignore();
}

void CLoginInWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        // 检查用户名及权限
        qDebug() << __FUNCTION__ << __LINE__;

        m_iUserPower = 2;//_CheckUserPower();
        if(m_iUserPower >= 0)
        {//
            emit SigShowMainWindow(m_iUserPower,m_pUserNameLineEdit->text());

            qDebug() << "SigShowMainWindow";
            this->hide();

            if(HIDOpertaionUtility::GetInstance()->IsReadDevParames() == false)
            {
                for(int iPos = 0;iPos < 3;iPos++)
                {
                    QTime qOldTime = QTime::currentTime();
                    CHidCmdThread::GetInstance()->AddReadDevParamsCmd();
                    while(1)
                    {
                        int iSeconds = qOldTime.secsTo(QTime::currentTime());
                        if(iSeconds > 10)
                        {
                            break;
                        }
                        QApplication::processEvents();
                    }
                    if(HIDOpertaionUtility::GetInstance()->IsReadDevParames() == true)
                    {
                        break;
                    }
                }
                if(HIDOpertaionUtility::GetInstance()->IsReadDevParames() == false)
                {
                    QMessageBox::warning(this, "warning", tr("Read Device Params error,please reboot the SoftWare!"), QMessageBox::Ok, QMessageBox::Ok);
                }
            }
        }
        qDebug() << __FUNCTION__ << __LINE__;
    }
}

void CLoginInWidget::_SlotCheckMinButton()
{
    this->showMinimized();
}

void CLoginInWidget::_SlotCheckCloseButton()
{
    if(QMessageBox::warning(NULL, "Warning", "Are you sure to quit?",
                            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {
        this->close();
    }
}

void CLoginInWidget::_SlotCheckHideButton()
{

}

void CLoginInWidget::_SlotCheckLoginButton()
{
    // 检查用户名及权限
    qDebug() << __FUNCTION__ << __LINE__;

    m_iUserPower = 2;//_CheckUserPower();
    if(m_iUserPower >= 0)
    {//
        emit SigShowMainWindow(m_iUserPower,m_pUserNameLineEdit->text());

        qDebug() << "SigShowMainWindow";
        this->hide();

        if(HIDOpertaionUtility::GetInstance()->IsReadDevParames() == false)
        {
            for(int iPos = 0;iPos < 3;iPos++)
            {
                QTime qOldTime = QTime::currentTime();
                CHidCmdThread::GetInstance()->AddReadDevParamsCmd();
                while(1)
                {
                    int iSeconds = qOldTime.secsTo(QTime::currentTime());
                    if(iSeconds > 10)
                    {
                        break;
                    }
                    QApplication::processEvents();
                }
                if(HIDOpertaionUtility::GetInstance()->IsReadDevParames() == true)
                {
                    break;
                }
            }
            if(HIDOpertaionUtility::GetInstance()->IsReadDevParames() == false)
            {
                QMessageBox::warning(this, "warning", tr("Read Device Params error,please reboot the SoftWare!"), QMessageBox::Ok, QMessageBox::Ok);
            }
        }
    }
    qDebug() << __FUNCTION__ << __LINE__;
}

void CLoginInWidget::_SlotPasswordChange()
{
    this->setFocusPolicy(Qt::StrongFocus);
}

int CLoginInWidget::GetUserPower()
{
    return m_iUserPower;
}

/**
  * @brief 初始化控件
  * @param
  * @return
  */
void CLoginInWidget::_InitWidget()
{
    //
    m_pMinButton = new QPushButton(this);
    m_pMinButton->setFixedSize(60, 50);
    SetButtonBackImage(m_pMinButton, ":/image/ico/login/login_zoomout_pressed.jpg");
    connect(m_pMinButton, SIGNAL(clicked(bool)), this, SLOT(_SlotCheckMinButton()));

    //
    m_pCloseButton = new QPushButton(this);
    m_pCloseButton->setFixedSize(60, 50);
    SetButtonBackImage(m_pCloseButton, ":/image/ico/login/login_close_pressed.jpg");
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(_SlotCheckCloseButton()));
    //
//    m_pLoginLabel = new QLabel("Login", this);
//    m_pLoginLabel->setObjectName("m_pLoginLabel");
    // user
    m_pUserNameLabel = new QLabel("Username: ", this);
    //m_pUserNameLabel->setFixedSize(100, 50);
   // m_pUserNameLabel->setObjectName("m_pUserNameLabel");
    m_pUserNameLineEdit = new QLineEdit(this);
    m_pUserNameLineEdit->setFixedSize(280, 35);
    // pass
    m_pPasswordLabel = new QLabel("Password:  ", this);
   // m_pPasswordLabel->setObjectName("m_pUserNameLabel");
    m_pPasswordLineEdit = new QLineEdit(this);
    m_pPasswordLineEdit->setEchoMode(QLineEdit::Password);
    m_pPasswordLineEdit->setFixedSize(280, 35);
    connect(m_pPasswordLineEdit, &QLineEdit::textChanged, this, &CLoginInWidget::_SlotPasswordChange);
    m_pPasswordHidButton = new QPushButton("Hide", this);
    m_pPasswordHidButton->setFixedSize(60, 35);
    connect(m_pPasswordHidButton, &QPushButton::clicked, this, &CLoginInWidget::_SlotCheckHideButton);
    //
    m_pLoginButton = new QPushButton("Login", this);
    m_pLoginButton->setFixedSize(160, 35);
    m_pLoginButton->setObjectName("m_pLoginButton");

    connect(m_pLoginButton, SIGNAL(clicked(bool)), this, SLOT(_SlotCheckLoginButton()));
}
/**
  * @brief 布局
  * @param
  * @return
  */
void CLoginInWidget::_InitLayout()
{
    int iLeftSize = 625;
    QHBoxLayout *pTitleLayout = new QHBoxLayout;
    pTitleLayout->setMargin(0);
    pTitleLayout->addStretch(100);
    pTitleLayout->addWidget(m_pMinButton);
    pTitleLayout->addWidget(m_pCloseButton);
    // username
    QHBoxLayout *pUserNameLableHLayout = new QHBoxLayout;
    pUserNameLableHLayout->addSpacing(iLeftSize);
    pUserNameLableHLayout->addWidget(m_pUserNameLabel);
    pUserNameLableHLayout->addStretch(100);
    //
    QHBoxLayout *pUserNameLineHLayout = new QHBoxLayout;
    pUserNameLineHLayout->addSpacing(iLeftSize);
    pUserNameLineHLayout->addWidget(m_pUserNameLineEdit);
    pUserNameLineHLayout->addStretch(100);
    // password
    QHBoxLayout *pPasswordLableHLayout = new QHBoxLayout;
    pPasswordLableHLayout->addSpacing(iLeftSize);
    pPasswordLableHLayout->addWidget(m_pPasswordLabel);
    pPasswordLableHLayout->addStretch(100);
    //
    QHBoxLayout *pPasswordLineHLayout = new QHBoxLayout;
    pPasswordLineHLayout->addSpacing(iLeftSize);
    pPasswordLineHLayout->addWidget(m_pPasswordLineEdit);
    pPasswordLineHLayout->addSpacing(10);
    pPasswordLineHLayout->addWidget(m_pPasswordHidButton);
    pPasswordLineHLayout->addStretch(100);
    //
    //
    QHBoxLayout *pLoadInHLayout = new QHBoxLayout;
    pLoadInHLayout->addSpacing(iLeftSize+60);
    pLoadInHLayout->addWidget(m_pLoginButton);
    pLoadInHLayout->addStretch(100);
    //

    QVBoxLayout *pVLayout = new QVBoxLayout;
    pVLayout->setMargin(0);
    pVLayout->addLayout(pTitleLayout);
    pVLayout->addStretch(100);
    pVLayout->addLayout(pUserNameLableHLayout);
    pVLayout->addSpacing(10);
    pVLayout->addLayout(pUserNameLineHLayout);
    pVLayout->addSpacing(10);
    pVLayout->addLayout(pPasswordLableHLayout);
    pVLayout->addSpacing(10);
    pVLayout->addLayout(pPasswordLineHLayout);
    pVLayout->addSpacing(50);
    pVLayout->addLayout(pLoadInHLayout);
    pVLayout->addStretch(100);
    //
    this->setLayout(pVLayout);
}
/**
  * @brief 验证用户和权限
  * @param
  * @return -1：无效用户，0：普通用户，1：管理员，2：维护人员
  */
int CLoginInWidget::_CheckUserPower()
{
    qDebug() << __FUNCTION__ << __LINE__;
    QString strUserName = m_pUserNameLineEdit->text();
    QString strPassWord = m_pPasswordLineEdit->text();
    QString strDataPassWord = "";// 数据库中存储密码
    if(strUserName.isEmpty() || strPassWord.isEmpty())
    {
        QMessageBox::critical(0, QObject::tr("Error!"),
                         QObject::tr("Please input Username and Password!"));
        return -1;
    }

    qDebug() << __FUNCTION__ << __LINE__;
    if(strUserName == m_strAdminUserName)
    {
        if(strPassWord == m_strAdminPassWord)
        {
            qDebug() << "admin user";
            return 1;
        }
        else
        {
            // 密码错误
            QMessageBox::critical(0, QObject::tr("Error!"),
                             QObject::tr("Incorrect Password!"));
            return -1;
        }
    }
    else if(strUserName == m_strModifyUserName)
    {
        if(strPassWord == m_strModifyPassWord)
        {
            qDebug() << "modify user";
            return 2;
        }
        else
        {
            // 密码错误
            QMessageBox::critical(0, QObject::tr("Error!"),
                             QObject::tr("Incorrect Password!"));
            return -1;
        }

    }

    qDebug() << __FUNCTION__ << __LINE__;
    // 数据库查询
    QSqlDatabase qSqldb = ConnectDataBase(QCoreApplication::applicationDirPath() + m_strDatabaseName);
    if(qSqldb.isOpen() == false)
    {
        qSqldb.open();
    }
    if(qSqldb.isOpen())
    {
        QString strSelect = QString("SELECT * FROM userdata WHERE username = '")
                + strUserName + "'";
        QSqlQuery qSqlQuery(qSqldb);//
        qSqlQuery.exec(strSelect);
        qDebug() << __FUNCTION__ << __LINE__;
        if(qSqlQuery.next())
        {
            strDataPassWord = qSqlQuery.value(2).toString();
            qDebug() << "find the pase" << strDataPassWord;
            if(strPassWord == strDataPassWord)
            {// 密码校验正确
                if(strUserName == m_strAdminUserName && strPassWord == m_strAdminPassWord)
                {
                    qDebug() << "admin user";
                    return 1;
                }
                else if(strUserName == m_strModifyUserName && strPassWord == m_strModifyPassWord)
                {
                    qDebug() << "modify user";
                    return 2;
                }
                else
                {
                    qDebug() <<"normal user";
                    return 0;
                }
            }
            else
            {// 密码错误
                QMessageBox::critical(0, QObject::tr("Error!"),
                                 QObject::tr("Incorrect Password!"));
                return -1;
            }
        }
        else
        {
            QMessageBox::critical(0, QObject::tr("Error!"),
                             QObject::tr("Incorrect UserName!"));
            return -1;
        }
    }
    qDebug() << __FUNCTION__ << __LINE__;
//    else
//    {
//        QMessageBox::critical(0, QObject::tr("Data base error!"),
//                         QObject::tr("Critical Data lostr!"));
//        return -1;
//    }
    return -1;
}
