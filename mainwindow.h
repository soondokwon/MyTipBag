#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "highlighter.h"
#include "codeeditor.h"
#include "categorydialog.h"
#include "addnewitemdialog.h"

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QSettings>
#include <QFileInfo>
#include <QStandardItemModel>
#include <QFontDialog>
#include <QScrollBar>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void closeEvent( QCloseEvent * event );
    bool fileExists(QString path);
    void openFile();
    void showSelectedList( const QString & strCategoryID );
    void showContent( const QString & strListID );
    QString getTitle( const QString & strID );
    void updateCategoryNameAndLangType( const QString & strID );
    void insertAddedItem();

public:
    inline QSqlDatabase * getTipBagDb() {
        return &_myTipBagDb;
    }

    inline QStringList * getLangType() {
        return &_strlstLangType;
    }

    inline QString * getCurCategoryID() {
        return &_strCurCategoryID;
    }

private slots:
    void on_actionExit_triggered();
    void on_action_New_Bag_triggered();
    void on__tbtnAddCategory_clicked();
    void on__tbtnUpdateCategory_clicked();
    void on__tbtnDeleteCategory_clicked();
    void on__tbtnNewDoc_clicked();
    void on__tbtnSaveDoc_clicked();
    void on__tbtnDelDoc_clicked();
    void on__tvCategory_clicked(const QModelIndex &index);
    void on__tvCategory_activated(const QModelIndex &index);
    void on__tvList_clicked(const QModelIndex &index);
    void on__tvList_activated(const QModelIndex &index);
    void on__tvSearchResult_clicked(const QModelIndex &index);
    void on__tbtnUpdateTitle_clicked();
    void on_action_Font_triggered();
    void on_actionFind_All_triggered();
    void on__btnFind_clicked();

    void on__tvSearchResult_activated(const QModelIndex &index);

private:
    void setupEditor();
    void setupTvCategory();
    void setupTvList();
    void setupTvFindList();

    void readAppIni();
    void writeDbIni( const QString & strDbFile );
    void writeFontIni( const QString & strFontName, const int iFontSize );

private:
    Ui::MainWindow *ui;
    Highlighter * _pHighlighter;
    CodeEditor * _pEditor;
    QStandardItemModel * _pModelCategoryList;
    QStandardItemModel * _pModelSelectedList;
    QStandardItemModel * _pModelFindList;
    QString _strDefaultDb;
    QString _strFontName;
    int _iFontSize;
    QString _strCurCategoryID;
    QString _strCurstrListID;

    QSqlDatabase _myTipBagDb;
    QStringList _strlstLangType;

};

#endif // MAINWINDOW_H

