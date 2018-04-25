#ifndef ADDNEWITEMDIALOG_H
#define ADDNEWITEMDIALOG_H

#include "mainwindow.h"
#include <QDialog>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class AddNewItemDialog;
}

class MainWindow;
class AddNewItemDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddNewItemDialog(QWidget *parent = 0);
    ~AddNewItemDialog();

public:
    enum POPUP_TYPE {
        ADD_TITLE = 0,
        UPDATE_TITLE
    };

    inline void setPopupType( POPUP_TYPE type = ADD_TITLE ) {
        _popupType = type;
    };
    inline void setCurID( QString strID ) {
        _strCurID = strID;
    }

    void setTitle( QString strTitle );

private slots:
    void on__btnSave_clicked();

private:
    Ui::AddNewItemDialog *ui;
    MainWindow * _pMainWnd;
    POPUP_TYPE _popupType;
    QString _strCurID;
};

#endif // ADDNEWITEMDIALOG_H
