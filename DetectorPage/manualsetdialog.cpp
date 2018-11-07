#include "manualsetdialog.h"
#include "ui_manualsetdialog.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QDebug>
#include <QHeaderView>
#include <QSqlQuery>
#include <QtSql>
#include "PublicFunction.h"

ManualSetDialog::ManualSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualSetDialog)
{

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);  //关闭时自动销毁内存

    this->setAutoFillBackground(true);  //自动填充背景

    SetWidgetBackColor(ui->label, QColor(0x00, 0x68, 0xB8));
    _InitWidget();

    _ReadConfigFile();
    _InitDataBase();

    _InitLayout();
    ui->ItemCombinationcomboBox->setCurrentIndex(0);

}

ManualSetDialog::~ManualSetDialog()
{
    delete ui;
}

void ManualSetDialog::_InitDataBase()
{


    //m_strDatabaseName = "\\drug.db";
    QString strDatabaseName = QCoreApplication::applicationDirPath() + "/SampleCupTyle.db";
    //if (ConnectDataBase(strDatabaseName))

        //QSqlDatabase db2;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
        {
            db2 = QSqlDatabase::database("qt_sql_default_connection");
        }
        else
        {
            db2 = QSqlDatabase::addDatabase("QSQLITE");
        }

        //QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE");
        //QString strDatabaseName = QCoreApplication::applicationDirPath() + "/SampleCupTyle.db";
        db2.setDatabaseName(strDatabaseName);
        if (!db2.open())
        {
            qDebug()<<"open falsed!";
        }
        else
        {
            qDebug()<<"open success!";

//            QString strCreateTable  = "CREATE TABLE ProjectPortfolioTable ("
//                                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
//                                      "CupType VARCHAR,"
//                                      "ProjectPortfolio VARCHAR,"
//                                      "ProjectCount VARCHAR,"
//                                      "ProjectName VARCHAR)";
//            QSqlQuery qSqlQuery(db2);
//            // 创建
//            if (!qSqlQuery.exec(strCreateTable))
//            {
//                qDebug() << " database error: " << qSqlQuery.lastError().text();
//                //return;
//            }

//            QString ProjectName = "MOP,300;MET,1000;KET,1000;BZO,300;COC,300;MDMA,500;AMP,1000;BAR,300;TCA,1000;OXY,100;BUP,10;THC,50";

//            // 数据库插入
//            qSqlQuery.prepare("INSERT INTO ProjectPortfolioTable (CupType,ProjectPortfolio,ProjectCount,ProjectName) "
//                              "VALUES (?,?, ?,?)");
//            qSqlQuery.addBindValue("TCup");
//            qSqlQuery.addBindValue("J12");
//            qSqlQuery.addBindValue("12");
//            qSqlQuery.addBindValue(ProjectName);
//            //
//            if (!qSqlQuery.exec())
//            {
//                qDebug() << qSqlQuery.lastError();
//                QMessageBox::warning(0, QObject::tr("Database Error"),
//                                      qSqlQuery.lastError().text());
//            }
        }

        qMultiMapCup.clear();
        QString strSelect = "SELECT * FROM ProjectPortfolioTable";
        qDebug() << "strSelect = " << strSelect;
        QSqlQuery qSqlQuery(db2);//
        bool isValid =  qSqlQuery.exec(strSelect);
        qDebug() << "isValid = " << isValid;

        if(isValid == false)
        {
            return;
        }

        strCupTypeList.clear();
        strItemList.clear();

        while(qSqlQuery.next())
        {
            QString strCupType = qSqlQuery.value(1).toString();
            qDebug() << "strCupType = " << strCupType;
            if(strReadCupList.contains(strCupType))
            {
                if(strCupTypeList.contains(strCupType) == false)
                {
                    strCupTypeList.append(strCupType);
                }

                QString strProjectPortfolio = qSqlQuery.value(2).toString();
                qDebug() << "strProjectPortfolio = " << strProjectPortfolio;
                //strItemList.append(strProjectPortfolio);

                qMultiMapCup.insert(strCupType,strProjectPortfolio);
            }

        }

        ui->CupTypecomboBox->insertItems(0,strCupTypeList);
        strItemList = qMultiMapCup.values(ui->CupTypecomboBox->currentText());
        //ui->ItemCombinationcomboBox->insertItems(0,strItemList);
}

/**
* @brief _InitWidget
* @param
* @param
* @return
*/
void ManualSetDialog::_InitWidget()
{
    this->setObjectName("ManualSetDialog");
    ui->qCupTypelabel->setObjectName("Label1");
    ui->qCupTypeNameLabel->setObjectName("Label3");
    ui->qProjectCountlabel->setObjectName("Label1");
    ui->qProjectCountNamelabel->setObjectName("Label3");
    ui->qProjectProtfoliolabel->setObjectName("Label1");
    ui->qProjectProtfolioNameLabel->setObjectName("Label3");

    ui->qCupTypelabel_2->setObjectName(("Label2"));
    ui->qItemCombinationlabel->setObjectName(("Label2"));
    _LoadQss();
    strCupType = "TCup";

    // table
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    int m_iTableColumnCount = 2;
    // 设置列数量
    ui->tableWidget->setColumnCount(m_iTableColumnCount);
    //m_pDataTableWidget->setColumnHidden(0, true);// 首列为ID数据，隐藏不显示

    ui->tableWidget->setRowCount(16);

    // 不显示行号
    QHeaderView *pVerticalHeader = ui->tableWidget->verticalHeader();
    pVerticalHeader->setHidden(true);
    pVerticalHeader->setHighlightSections(false);
    // 表单样式
    QHeaderView *pHeaderView = ui->tableWidget->horizontalHeader();
    pHeaderView->setDefaultSectionSize(110);
    pHeaderView->resizeSection(0, 138);
    pHeaderView->resizeSection(1, 200);
    pHeaderView->setHighlightSections(false);
    pHeaderView->setDisabled(true);
    // 充满表格
    pHeaderView->setStretchLastSection(true);
    // 多选
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // 每次选择一行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //m_pHistoryDataTableWidget->setStyleSheet("border-radius:5; color:#94f3dc; font: 18px ;selection-background-color: #d9f4fe;selection-color: black");
    // 设置表头内容
    QStringList qstrHeaderList;
    qstrHeaderList << tr("ProjectName") << tr("");
    //
    ui->tableWidget->setHorizontalHeaderLabels(qstrHeaderList);
    // 显示格子线
    ui->tableWidget->setShowGrid(true);

    on_ItemCombinationcomboBox_currentIndexChanged("");

}

void ManualSetDialog::_InitLayout()
{
//    QVBoxLayout *pLayout = new QVBoxLayout;
//    //
//    pLayout->addLayout(ui->horizontalLayout);
//    //
//    //
//    pLayout->addWidget(m_pDataTableWidget);
//    this->setLayout(pLayout);
}

void ManualSetDialog::_LoadQss()
{
    LoadQss(this, ":/qss/DetectorPage/ManualSetDialog.qss");
}

void ManualSetDialog::_AddItemCombination()
{

}

void ManualSetDialog::_UpdateView(QString strSelect)
{

}

void ManualSetDialog::on_okButton_clicked()
{
    this->close();
    if(strProjectName.isEmpty() == false)
    {
        SignalMenualSetProject(strCupType,strProjectName);
    }

}

void ManualSetDialog::on_cancelButton_clicked()
{
    this->close();
}

void ManualSetDialog::showEvent(QShowEvent *)
{

}

void ManualSetDialog::on_CupTypecomboBox_currentTextChanged(const QString &arg1)
{
    qDebug() << arg1;
    strCupType = arg1;

    strItemList.clear();
    strItemList = qMultiMapCup.values(ui->CupTypecomboBox->currentText());
    //qDebug() << "ui->ItemCombinationcomboBox->count() = " << ui->ItemCombinationcomboBox->count();
    ui->ItemCombinationcomboBox->clear();
    //qDebug() << "strItemList = " << strItemList;
    ui->ItemCombinationcomboBox->insertItems(0,strItemList);
    //qDebug() << "ui->ItemCombinationcomboBox->count() = " << ui->ItemCombinationcomboBox->count();

    for(int i = 0;i < ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(""));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(""));

    }
    QString strSelect = QString("SELECT * FROM ProjectPortfolioTable WHERE CupType = '")
            + arg1  + "'" + " AND ProjectPortfolio = " + "'" +  ui->ItemCombinationcomboBox->currentText() + "'";
    //qDebug() << "strSelect = " << strSelect;
    QSqlQuery qSqlQuery(db2);//
    qSqlQuery.exec(strSelect);

    QString strProjectPortfolio;
    QString strProjectCount;
    strProjectName = "";
    if(qSqlQuery.next())
    {

        strProjectPortfolio = qSqlQuery.value(2).toString();
        //qDebug() << "strProjectPortfolio = " << strProjectPortfolio;
        strProjectCount = qSqlQuery.value(3).toString();
        //qDebug() << "strProjectCount = " << strProjectCount;
        strProjectName = qSqlQuery.value(4).toString();
        //qDebug() << "strProjectName = " << strProjectName;

        ui->qCupTypeNameLabel->setText(strCupType);
        ui->qProjectProtfolioNameLabel->setText(strProjectPortfolio);
        ui->qProjectCountNamelabel->setText(strProjectCount);
    }
    QStringList strProjectNameGroupList = strProjectName.split(";");
    if(strProjectName.isEmpty())
    {
        return;
    }
    QStringList strProjectNameList;
    QList<QString> ProjectName;
    QList<QString> ProjectCutOff;
    for(int i = 0;i < strProjectNameGroupList.count();i++)
    {
        QString strProjectNameGroup = strProjectNameGroupList.at(i);
        strProjectNameList = strProjectNameGroup.split(",");
        ProjectName.append(strProjectNameList.at(0));
        ProjectCutOff.append(strProjectNameList.at(1));
    }

    for(int i = 0;i < ProjectName.count();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(ProjectName.at(i)));
        ui->tableWidget->item(i,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(ProjectCutOff.at(i)));
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);
    }

}

void ManualSetDialog::on_ItemCombinationcomboBox_currentIndexChanged(const QString &arg1)
{

    for(int i = 0;i < ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(""));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(""));
    }
//    QString strSelect = QString("SELECT * FROM ProjectPortfolioTable WHERE ProjectPortfolio = '")
//            + arg1 + "'";
    QString strSelect = QString("SELECT * FROM ProjectPortfolioTable WHERE CupType = '")
            + ui->CupTypecomboBox->currentText() +"'" + " AND ProjectPortfolio = " + "'" + arg1 + "'";
    //qDebug() << "strSelect = " << strSelect;

    QSqlQuery qSqlQuery(db2);//
    qSqlQuery.exec(strSelect);
    QString strCupType;
    QString strProjectPortfolio;
    QString strProjectCount;
    strProjectName = "";
    if(qSqlQuery.next())
    {
        strCupType = qSqlQuery.value(1).toString();
        strProjectPortfolio = qSqlQuery.value(2).toString();
        //qDebug() << "strProjectPortfolio = " << strProjectPortfolio;
        strProjectCount = qSqlQuery.value(3).toString();
        //qDebug() << "strProjectCount = " << strProjectCount;
        strProjectName = qSqlQuery.value(4).toString();
        //qDebug() << "strProjectName = " << strProjectName;

        ui->qCupTypeNameLabel->setText(strCupType);
        ui->qProjectProtfolioNameLabel->setText(strProjectPortfolio);
        ui->qProjectCountNamelabel->setText(strProjectCount);
    }

    if(strProjectName.isEmpty())
    {
        return;
    }
    QStringList strProjectNameGroupList = strProjectName.split(";");
    QStringList strProjectNameList;
    QList<QString> ProjectName;
    QList<QString> ProjectCutOff;
    for(int i = 0;i < strProjectNameGroupList.count();i++)
    {
        QString strProjectNameGroup = strProjectNameGroupList.at(i);
        strProjectNameList = strProjectNameGroup.split(",");
        ProjectName.append(strProjectNameList.at(0));
        ProjectCutOff.append(strProjectNameList.at(1));
    }

    for(int i = 0;i < ProjectName.count();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(ProjectName.at(i)));
        ui->tableWidget->item(i,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(ProjectCutOff.at(i)));
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);
    }

}

/**
  * @brief 读取配置文件
  * @param
  * @return
  */
void ManualSetDialog::_ReadConfigFile()
{
    strReadCupList.clear();
    QFile qFile(QApplication::applicationDirPath() + "/Resources/config.json");
    if(!qFile.open(QFile::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Critical Data lost"));
        return;
    }
    QByteArray qFileByte = qFile.readAll();
    QString strFile = QString::fromLocal8Bit(qFileByte.data());
    QJsonParseError *pError=new QJsonParseError;
    QJsonDocument qJsonDoc=QJsonDocument::fromJson(strFile.toStdString().data(), pError);
    if(pError->error == QJsonParseError::NoError)
    {
        if(qJsonDoc.isObject())
        {
            QJsonObject qJsonObject = qJsonDoc.object();//取得最外层这个大对象
                //这里放代码，对json数据进行取值
            QJsonArray qCupArray = qJsonObject["cup_type"].toArray();

            foreach(QJsonValue qJsonValue, qCupArray)
            {
                strReadCupList.push_back(qJsonValue.toString());
            }
            qDebug() << " cup type " << strReadCupList;
            // 设置控件
        }
        else
        {
            qDebug() << pError->errorString();
        }
    }
    if(pError != NULL)
    {
        delete pError;
    }
    qFile.close();
}
