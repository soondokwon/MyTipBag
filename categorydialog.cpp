#include "categorydialog.h"
#include "ui_categorydialog.h"

CategoryDialog::CategoryDialog(QWidget *parent) :
    QDialog(parent),
    _pMainWnd(NULL),
    _cateType(ADD_CATE),
    _strCateName(""),
    ui(new Ui::CategoryDialog)
{
    ui->setupUi(this);
    _pMainWnd = reinterpret_cast<MainWindow*>(parent);

    ui->_cmbLangFormat->addItems( *_pMainWnd->getLangType() );
}

CategoryDialog::~CategoryDialog() {
    delete ui;
}

void CategoryDialog::on__btnSave_clicked()
{
    if ( !_pMainWnd->getTipBagDb()->isOpen() ) {
        qDebug() << "CategoryDialog::on__btnSave_clicked() -> Failed to open the database";
        return;
    }

    QString strCatName = ui->_edCatName->text();
    if ( strCatName.length() <= 0 ) {
        qDebug() << "CategoryDialog::on__btnSave_clicked() -> require strCatName";
        return;
    }

    QSqlQuery sql;

    switch( _cateType ) {
    case ADD_CATE:
        sql.prepare( "insert into Category(langtype, name) values(:langtype, :name)" );
        sql.bindValue( ":langtype", ui->_cmbLangFormat->currentIndex() );
        sql.bindValue( ":name", strCatName );

        break;

    case UPDATE_CATE:
        sql.prepare("update Category set langtype=:langtype, name=:name "
                    "where id=" + _strCurID );
        sql.bindValue( ":langtype", ui->_cmbLangFormat->currentIndex() );
        sql.bindValue( ":name", strCatName );

        break;
    }

    if ( sql.exec() ) {
        qDebug() << "SQL succeeded...";
        accept();
        close(); // 현재 창 닫기
    }
}

void CategoryDialog::setCateName( QString strCateName ) {
    ui->_edCatName->setText( strCateName );
}

void CategoryDialog::setLangType( int iLangType ) {
    ui->_cmbLangFormat->setCurrentIndex( iLangType );
}
