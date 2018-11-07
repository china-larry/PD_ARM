#ifndef MANUALSETDIALOG_H
#define MANUALSETDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include "CommonDataWidget/CLabelCommoBoxWidget.h"
#include <QSqlDatabase>
#include <QMultiMap>

namespace Ui {
class ManualSetDialog;
}

class ManualSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManualSetDialog(QWidget *parent = 0);
    ~ManualSetDialog();

signals:
    void SignalMenualSetProject(QString strCupType,QString strProject);

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_CupTypecomboBox_currentTextChanged(const QString &arg1);

    void on_ItemCombinationcomboBox_currentIndexChanged(const QString &arg1);

protected:
    void showEvent(QShowEvent *);
private:
    void _InitWidget();
    void _AddItemCombination();
    void _UpdateView(QString strSelect);
    bool _ConnectDataBase(const QString &strName);
    void _LoadQss();
    void _InitLayout();
    void _InitDataBase();
    void _ReadConfigFile();
private:
    Ui::ManualSetDialog *ui;
    CLabelCommoBoxWidget *m_pCItemCommoBoxWidget;
    QString strCupType;
    QString strFilter;
    QString m_strDatabaseName;
    QString strProjectName;
    //QTableWidget *m_pDataTableWidget;// 历史数据表控件
    QSqlDatabase db2;

    QStringList strItemList;
    QStringList strCupTypeList;

    QStringList strReadCupList;

    QMultiMap<QString,QString> qMultiMapCup;
};

#endif // MANUALSETDIALOG_H
