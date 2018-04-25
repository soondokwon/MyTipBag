#include "addnewitemdialog.h"
#include "ui_addnewitemdialog.h"

AddNewItemDialog::AddNewItemDialog(QWidget *parent) :
    QDialog(parent),
    _pMainWnd(NULL),
    _popupType(ADD_TITLE),
    _strCurID(""),
    ui(new Ui::AddNewItemDialog)
{
    ui->setupUi(this);
    _pMainWnd = reinterpret_cast<MainWindow*>(parent);
}

AddNewItemDialog::~AddNewItemDialog()
{
    delete ui;
}

void AddNewItemDialog::on__btnSave_clicked()
{
    qDebug() << "AddNewItemDialog::on__btnSave_clicked() -> _pMainWnd->getCurCategoryID()" << _pMainWnd->getCurCategoryID();

    if ( !_pMainWnd->getTipBagDb()->isOpen() ) {
        qDebug() << "AddNewItemDialog::on__btnSave_clicked() -> Failed to open the database";
        return;
    }

    QString strTitle = ui->_edTitle->text();
    if ( strTitle.length() <= 0 ) {
        qDebug() << "AddNewItemDialog::on__btnSave_clicked() -> require strTitle";
        return;
    }

    QSqlQuery sql;
    //QString strSQL("");

    switch( _popupType ) {
    case ADD_TITLE:
        //strSQL = "insert into Tip(category_id, title, content) values("+ *(_pMainWnd->getCurCategoryID()) +", '" + strTitle+"', '')";
        sql.prepare( "insert into Tip(category_id, title) values(:category_id, :title)" );
        sql.bindValue( ":category_id", *(_pMainWnd->getCurCategoryID()) );
        sql.bindValue( ":title", ui->_edTitle->text() );
        break;

    case UPDATE_TITLE:
        sql.prepare( "update tip set title=:title "
                     "where id=" + _strCurID );
        sql.bindValue( ":title", ui->_edTitle->text() );

        break;
    }
    //qDebug() << strSQL;

    if ( sql.exec() ) {
        qDebug() << "SQL succeeded...";
        this->accept();
        close(); // 현재 창 닫기
    }
}

void AddNewItemDialog::setTitle( QString strTitle ) {
    ui->_edTitle->setText(strTitle);
}

