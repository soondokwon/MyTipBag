#ifndef CATEGORYDIALOG_H
#define CATEGORYDIALOG_H

#include "mainwindow.h"
#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class CategoryDialog;
}

class MainWindow;
class CategoryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CategoryDialog(QWidget *parent = 0);
    ~CategoryDialog();
    void setCateName( QString strCateName );
    void setLangType( int iLangType );

public:
    enum CATE_TYPE {
        ADD_CATE = 0,
        UPDATE_CATE
    };

public:
    inline void setCateType( CATE_TYPE cateType ) {
        _cateType = cateType;
    }

    inline void setCurID( QString strID ) {
        _strCurID = strID;
    }

private slots:
    void on__btnSave_clicked();

private:
    Ui::CategoryDialog *ui;
    MainWindow * _pMainWnd;
    CATE_TYPE _cateType;
    QString _strCateName;
    QString _strCurID;
};

#endif // CATEGORYDIALOG_H
