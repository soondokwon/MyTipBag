#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _strDefaultDb(""),
    _strFontName("Fixedsys"),
    _iFontSize(10),
    _strCurCategoryID(""),
    _strCurstrListID(""),
    _pModelCategoryList(NULL),
    _pModelSelectedList(NULL),
    _pModelFindList(NULL),
    _pEditor(NULL),
    _pHighlighter(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _strlstLangType << "C" << "C++" << "Java" << "C#" << "Go Lang"
                    << "Java Script" << "PHP" << "HTML" << "TEXT"
                    << "SQL" << "Python" << "Ruby";
    ui->_dckWidSearchResult->setVisible( false );

    readAppIni();
    setupEditor();
    setupTvCategory();
    setupTvList();
    setupTvFindList();
}

MainWindow::~MainWindow() {
    //----------------------------------------
    // db close
    if ( _myTipBagDb.isOpen() ) {
        _myTipBagDb.close();
        qDebug() << "database closed...";
    }

    delete ui;
}

void MainWindow::on_actionExit_triggered() {
    close();
}

void MainWindow::closeEvent( QCloseEvent * event ) {

    QMessageBox::StandardButton dialog;

    dialog = QMessageBox::warning( this, "Confirm Exit", "Do you really want to exit now?",
                                   QMessageBox::Ok | QMessageBox::Cancel );
    if ( dialog == QMessageBox::Ok) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::setupEditor() {
    QFont font;

    //font.setFamily("Courier");
    font.setFamily( _strFontName );
    font.setFixedPitch(true);
    font.setPointSize( _iFontSize );

    _pEditor = new CodeEditor;
    _pEditor->setFont(font);
    setCentralWidget( _pEditor );

    //-----------------------------------------------------
    // tab 문자의 칸 수를 설정한다.
    const int tabStop = 4;  // 4 characters
    QFontMetrics metrics(font);
    _pEditor->setTabStopWidth(tabStop * metrics.width(' '));

    _pHighlighter = new Highlighter( _pEditor->document(), 1 );
}

void MainWindow::setupTvCategory() {
    QStringList lstCategoryHeader;

    lstCategoryHeader << "ID" << "Category Name" << "Lang Type"; // 숨겨질 열은 보이지 않는다.
    _pModelCategoryList = new QStandardItemModel();
    _pModelCategoryList->setHorizontalHeaderLabels( lstCategoryHeader );
    ui->_tvCategory->setSelectionMode( QAbstractItemView::SingleSelection );// 한줄만 선택
    ui->_tvCategory->setModel( _pModelCategoryList );

    ui->_tvCategory->setColumnHidden( 0, true ); // 0번 열 숨기기
    ui->_tvCategory->setSelectionBehavior( QAbstractItemView::SelectRows );

    ui->_tvCategory->setColumnWidth( 1, 160 );
    ui->_tvCategory->setColumnWidth( 2, 78 );

    //-------------------------------------------------------
    // db 데이터 로드
    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::setupTvCategory() -> Failed to open the database";
        return;
    }

    QSqlQuery sql;
    QString strSQL( "select id, langtype, name from Category" );
    qDebug() << strSQL;

    if ( !sql.exec(strSQL) ) {
        qDebug() << "MainWindow::setupTvCategory() -> failed select SQL...";
        return;
    }

    int iRow = 0;
    QStandardItem * pNewItem = NULL;
    while ( sql.next() ) {
        QString strId = sql.value(sql.record().indexOf("id")).toString();
        int iLangType = sql.value( sql.record().indexOf("langtype")).toInt();
        QString strName = sql.value(sql.record().indexOf("name")).toString();

        qDebug() << "strId=" << strId
                 << ", iLangType=" << iLangType
                 << ", strName=" << strName;

        //--------------------------------------------------------
        pNewItem = new QStandardItem( strId );
        _pModelCategoryList->setItem( iRow, 0, pNewItem );

        pNewItem = new QStandardItem( strName );
        _pModelCategoryList->setItem( iRow, 1, pNewItem );

        pNewItem = new QStandardItem( _strlstLangType.at(iLangType) );
        pNewItem->setTextAlignment( Qt::AlignCenter );
        _pModelCategoryList->setItem( iRow, 2, pNewItem );

        ++iRow;
    }

    ui->_tvCategory->selectRow( 0 );
}

void MainWindow::setupTvList() {
    QStringList lstSelectedListHeader;

    lstSelectedListHeader << "ID" << "Title" << "Size";
    _pModelSelectedList = new QStandardItemModel();
    _pModelSelectedList->setHorizontalHeaderLabels( lstSelectedListHeader );
    ui->_tvList->setSelectionMode( QAbstractItemView::SingleSelection );// 한줄만 선택
    ui->_tvList->setModel( _pModelSelectedList );

    ui->_tvList->setColumnHidden( 0, true ); // 0번 열 숨기기
    ui->_tvList->setSelectionBehavior( QAbstractItemView::SelectRows );

    ui->_tvList->setColumnWidth( 1, 160 );
    ui->_tvList->setColumnWidth( 2, 78 );

    if ( ui->_tvCategory->model()->rowCount() <= 0 )
        return;

    _strCurCategoryID = ui->_tvCategory->model()->index(0,0).data().toString();
    showSelectedList( _strCurCategoryID );

    ui->_tvList->selectRow( 0 );

    //---------------------------------------------
    _strCurstrListID = ui->_tvList->model()->index(0,0).data().toString();
    showContent( _strCurstrListID );
}

void MainWindow::setupTvFindList() {
    //----------------------------------------------------------------
    QStringList lstFindHeader;

    lstFindHeader << "TIP_ID" << "Category Name" << "Lang Type" << "Title" << "Content"; // 숨겨질 열은 보이지 않는다.
    _pModelFindList = new QStandardItemModel();
    _pModelFindList->setHorizontalHeaderLabels( lstFindHeader );
    ui->_tvSearchResult->setSelectionMode( QAbstractItemView::SingleSelection );// 한줄만 선택
    ui->_tvSearchResult->setModel( _pModelFindList );

    ui->_tvSearchResult->setColumnHidden( 0, true ); // 0번 열 숨기기
    ui->_tvSearchResult->setSelectionBehavior( QAbstractItemView::SelectRows );

    ui->_tvSearchResult->setColumnWidth( 1, 150 );
    ui->_tvSearchResult->setColumnWidth( 2, 78 );
    ui->_tvSearchResult->setColumnWidth( 3, 200 );
    ui->_tvSearchResult->setColumnWidth( 4, 300 );
}

void MainWindow::showSelectedList(const QString & strCategoryID) {
    //-------------------------------------------------------
    // db 데이터 로드
    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::showSelectedList() -> Failed to open the database";
        return;
    }

    QSqlQuery sql;
    QString strSQL(
                    "select id, title, length(content) as content_len from Tip "
                    "where category_id=" + strCategoryID + " order by id desc"
                );
    qDebug() << strSQL;

    if ( !sql.exec(strSQL) ) {
        qDebug() << "MainWindow::showSelectedList() -> failed select SQL...";
        return;
    }

    int iRow = 0;
    QStandardItem * pNewItem = NULL;
    while ( sql.next() ) {
        QString strId = sql.value(sql.record().indexOf("id")).toString();
        QString strTitle = sql.value(sql.record().indexOf("title")).toString();
        int iLength = sql.value( sql.record().indexOf("content_len")).toInt();

        qDebug() << "strTitle=" << strTitle
                 << ", iLength=" << iLength;

        //--------------------------------------------------------
        pNewItem = new QStandardItem( strId );
        _pModelSelectedList->setItem( iRow, 0, pNewItem );

        pNewItem = new QStandardItem( strTitle );
        _pModelSelectedList->setItem( iRow, 1, pNewItem );

        pNewItem = new QStandardItem( QString::number(iLength) );
        pNewItem->setTextAlignment( Qt::AlignCenter );
        _pModelSelectedList->setItem( iRow, 2, pNewItem );

        ++iRow;
    }
}

void MainWindow::showContent( const QString & strListID ) {
    //-------------------------------------------------------
    // db 데이터 로드
    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::showContent() -> Failed to open the database";
        return;
    }

    QSqlQuery sql;
    QString strSQL(
                    "SELECT content FROM Tip "
                    "WHERE id=" + strListID
                );
    qDebug() << strSQL;

    if ( !sql.exec(strSQL) ) {
        qDebug() << "MainWindow::showContent() -> failed select SQL...";
        return;
    }

    while ( sql.next() ) {
        QString strContent = sql.value(sql.record().indexOf("content")).toString();
        _pEditor->setPlainText( strContent );
    }
}

void MainWindow::openFile()
{
    QString fileName;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "C++ Files (*.cpp *.h)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            _pEditor->setPlainText(file.readAll());
    }
}

void MainWindow::on_action_New_Bag_triggered()
{
    QString strFile = QFileDialog::getSaveFileName( this, "Save database file", "./", "SQLite Files (*.db);;All Files (*)" );

    if ( strFile.isEmpty() ) {
        qDebug() << "on_action_New_Bag_triggered() -> Save database failed...";
        return;
    }

    // 경로를 구하면...
    qDebug() << strFile;

    //QString strPath = QApplication::applicationDirPath() + "/db/test.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName( strFile );
    if ( !db.open() ) {
        qDebug() << "on_action_New_Bag_triggered() -> Failed to open the database.";
    }
    else {
        qDebug() << "on_action_New_Bag_triggered() -> succeed to open the db.";
    }

    QSqlQuery query;
    bool bResult = false;

    bResult = query.exec(
        "create table Category "
        "(id integer primary key, "
        "langtype integer, "
        "name varchar(128))"
    );

    bResult = query.exec(
        "create table Tip "
        "(id integer primary key, "
        "category_id integer, "
        "title varchar(128), "
        "content text)"
    );

    if ( db.isOpen() ) {
           db.close();
           qDebug() << "on_action_New_Bag_triggered() -> database closed...";
    }

    if ( bResult ) {
        writeDbIni( strFile );
        readAppIni();
    }
}

bool MainWindow::fileExists(QString path) {
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if ( checkFile.exists() && checkFile.isFile() ) {
        return true;
    }
    else {
        return false;
    }
}

/*
[Setting]
DefaultDb=c:/test.db
*/
void MainWindow::readAppIni() {
    QString strIniFile = QApplication::applicationDirPath() + "/MyTipBag.ini";

    QString strKey("Setting/");
    QSettings * pSettings = NULL;
    pSettings = new QSettings( strIniFile, QSettings::IniFormat );

    _strDefaultDb = pSettings->value( strKey + "DefaultDb" ).toString();
    qDebug() << "MainWindow::readAppIni() -> _strDefaultDb=" << _strDefaultDb;

    QString strFontName = pSettings->value( strKey + "FontName" ).toString();
    if ( strFontName.length() > 0 )
        _strFontName = strFontName;

    int iFontSize = pSettings->value( strKey + "FontSize" ).toInt();
    if ( iFontSize > 0 )
        _iFontSize = iFontSize;

    pSettings->deleteLater();

    if ( fileExists(_strDefaultDb) ) {
        _myTipBagDb = QSqlDatabase::addDatabase( "QSQLITE" );
        _myTipBagDb.setDatabaseName( _strDefaultDb );

        if ( !_myTipBagDb.open() ) {
            qDebug() << "Failed to open the database";
        }
        else {
            qDebug() << "Connected...";
        }
    }
    else {
        qDebug() << "No exist file=" << _strDefaultDb;
    }
}

void MainWindow::writeDbIni( const QString & strDbFile ) {
    QString strIniFile = QApplication::applicationDirPath() + "/MyTipBag.ini";

    QString strKey("Setting/");
    QSettings * pSettings = NULL;
    pSettings = new QSettings( strIniFile, QSettings::IniFormat );
    pSettings->setValue(strKey+"DefaultDb", strDbFile);

    pSettings->deleteLater();
}

void MainWindow::writeFontIni( const QString & strFontName, const int iFontSize ) {
    QString strIniFile = QApplication::applicationDirPath() + "/MyTipBag.ini";

    QString strKey("Setting/");
    QSettings * pSettings = NULL;
    pSettings = new QSettings( strIniFile, QSettings::IniFormat );
    pSettings->setValue(strKey+"FontName", strFontName);
    pSettings->setValue(strKey+"FontSize", QString::number(iFontSize));

    pSettings->deleteLater();
}

void MainWindow::on__tvCategory_clicked(const QModelIndex &index) {
    _strCurCategoryID = index.sibling(index.row(), 0).data().toString();
    qDebug() << "MainWindow::on__tvCategory_clicked() -> strCategoryID=" << _strCurCategoryID;

    _pEditor->setPlainText("");
    // tableView 모두 지우기
    while ( _pModelSelectedList->rowCount() > 0 ) {
        _pModelSelectedList->removeRow( 0 );
    }

    //---------------------------------------------
    // Editor를 언어에 맞게 새로 생성한다.
    if ( _pHighlighter != NULL ) {
        delete _pHighlighter;
        _pHighlighter = NULL;
    }
    QString strLangType = index.sibling(index.row(), 2).data().toString();
    _pHighlighter = new Highlighter( _pEditor->document(), _strlstLangType.indexOf(strLangType) );

    //---------------------------------------------
    showSelectedList( _strCurCategoryID );
    ui->_tvList->selectRow( 0 );

    //---------------------------------------------
    _strCurstrListID = ui->_tvList->model()->index(0,0).data().toString();
    showContent( _strCurstrListID );
}

void MainWindow::on__tvCategory_activated(const QModelIndex &index) {
    on__tvCategory_clicked(index);
}

void MainWindow::on__tvList_clicked(const QModelIndex &index) {
    _strCurstrListID = index.sibling(index.row(), 0).data().toString();
    showContent( _strCurstrListID );
}

void MainWindow::on__tvList_activated(const QModelIndex &index)
{
    on__tvList_clicked( index );
}

void MainWindow::on__tbtnAddCategory_clicked() {
    CategoryDialog dlg( this );
    dlg.setWindowTitle( "Add Category" );

    int iResult = dlg.exec();

    qDebug() << "MainWindow::on__tbtnAddCategory_clicked() -> iResult=" << iResult;
    if ( iResult == 1 ) { // 정상적으로 insert됬으면, ... QTableView에 마지막에 하나를 추가한다.
        insertAddedItem();
    }
}

void MainWindow::insertAddedItem() {
    // SELECT id, langtype, name FROM Category ORDER BY id DESC LIMIT 1; // 마지막에 입력한 행을 구하는 SQL
    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::insertAddedItem() -> Failed to open the database";
        return;
    }

    QSqlQuery sql;
    QString strSQL( "SELECT id, langtype, name FROM Category ORDER BY id DESC LIMIT 1" );
    qDebug() << strSQL;

    if ( !sql.exec(strSQL) ) {
        qDebug() << "MainWindow::insertAddedItem() -> failed select SQL...";
        return;
    }

    if ( sql.next() ) {
        QStandardItem * pNewItem = NULL;
        int iRow = _pModelCategoryList->rowCount();

        QString strId = sql.value(sql.record().indexOf("id")).toString();
        int iLangType = sql.value(sql.record().indexOf("langtype")).toInt();
        QString strName = sql.value(sql.record().indexOf("name")).toString();

        pNewItem = new QStandardItem( strId );
        _pModelCategoryList->setItem( iRow, 0, pNewItem );

        pNewItem = new QStandardItem( strName );
        _pModelCategoryList->setItem( iRow, 1, pNewItem );

        pNewItem = new QStandardItem( _strlstLangType.at(iLangType) );
        pNewItem->setTextAlignment( Qt::AlignCenter );
        _pModelCategoryList->setItem( iRow, 2, pNewItem );
    }
}

void MainWindow::on__tbtnUpdateCategory_clicked() {
    CategoryDialog dlg( this );
    dlg.setWindowTitle( "Update Category" );
    dlg.setCateType( CategoryDialog::UPDATE_CATE );

    QModelIndexList indexes = ui->_tvCategory->selectionModel()->selectedRows();
    QString strCurID = ui->_tvCategory->model()->index(indexes.last().row(), 0).data().toString(); // id
    dlg.setCurID( strCurID );
    dlg.setCateName( ui->_tvCategory->model()->index(indexes.last().row(), 1).data().toString() ); // CategoryName
    dlg.setLangType( _strlstLangType.indexOf( ui->_tvCategory->model()->index(indexes.last().row(), 2).data().toString() ) ); // langtype

    int iResult = dlg.exec();
    qDebug() << "MainWindow::on__tbtnUpdateCategory_clicked() -> iResult=" << iResult;

    if ( iResult == 1 ) { // 정상적으로 update 처리 했으면... QTableView에 CategoryName, langtype을 update
        updateCategoryNameAndLangType( strCurID );
    }
}

void MainWindow::updateCategoryNameAndLangType( const QString & strID ) {
    //-------------------------------------------------------
    // db 데이터 로드
    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::updateCategoryNameAndLangType() -> Failed to open the database";
        return;
    }

    QSqlQuery sql;
    QString strSQL(
                    "select langtype, name from Category "
                    "where id=" + strID
                  );
    qDebug() << strSQL;

    if ( !sql.exec(strSQL) ) {
        qDebug() << "MainWindow::updateCategoryNameAndLangType() -> failed select SQL...";
        return;
    }

    if ( sql.next() ) {
        QString strName = sql.value(sql.record().indexOf("name")).toString();
        int iLangType = sql.value(sql.record().indexOf("langtype")).toInt();

        QModelIndexList indexes = ui->_tvCategory->selectionModel()->selectedRows();
        if ( !indexes.isEmpty() ) {
            ui->_tvCategory->model()->setData( ui->_tvCategory->model()->index(indexes.last().row(), 1), strName );
            ui->_tvCategory->model()->setData( ui->_tvCategory->model()->index(indexes.last().row(), 2), _strlstLangType.at(iLangType) );
        }
    }
}

void MainWindow::on__tbtnDeleteCategory_clicked() {
    qDebug() << "MainWindow::on__tbtnDeleteCategory_clicked()";

    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning( this, "Confirm Delete", "Do you really want to delete this item?",
                                   QMessageBox::Ok | QMessageBox::Cancel );
    if ( dialog != QMessageBox::Ok) {
        return;
    }

    QModelIndexList indexes = ui->_tvCategory->selectionModel()->selectedRows();
    QString strCurCategoryID = ui->_tvCategory->model()->index(indexes.last().row(), 0).data().toString(); // id

    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::on__tbtnDeleteCategory_clicked() -> Failed to open the database";
        return;
    }

    // SELECT count(*) AS tip_count FROM Tip WHERE category_id=2
    QSqlQuery sql;
    QString strSQL(
                    "SELECT count(*) AS tip_count FROM Tip "
                    "WHERE category_id=" + strCurCategoryID
                  );
    qDebug() << strSQL;

    if ( !sql.exec(strSQL) ) {
        qDebug() << "MainWindow::on__tbtnDeleteCategory_clicked() -> failed select SQL...";
        return;
    }

    int iTipCount = 0;
    if ( sql.next() ) {
        iTipCount = sql.value(sql.record().indexOf("tip_count")).toInt();
    }

    if ( iTipCount > 0 ) { // 예외 처리
        QMessageBox::information( this, "Confirm", "Already using this category at tip lists!!!" );
        return;
    }

    //-----------------------------------------------------
    // 문제가 없으면, 삭제 하겠다.
    // DELETE FROM employee WHERE id = 1007
    QString strDeleteSQL(
                "DELETE FROM Category "
                "WHERE id=" + strCurCategoryID
    );
    qDebug() << strDeleteSQL;

    int iResult = sql.exec( strDeleteSQL );
    qDebug() << "MainWindow::on__tbtnDeleteCategory_clicked() -> iResult=" << iResult;

    if ( iResult == 1 ) { // 지워 졌으면, QTableView도 정리를 한다.
        QModelIndexList indexes = ui->_tvCategory->selectionModel()->selectedRows();
        while ( !indexes.isEmpty() ) {
            _pModelCategoryList->removeRows( indexes.last().row(), 1 );
            indexes.removeLast();
        }
    }
}

void MainWindow::on__tbtnNewDoc_clicked() {
    AddNewItemDialog dlg( this );
    dlg.setWindowTitle( "Add Title" );

    int iResult = dlg.exec();

    qDebug() << "MainWindow::on__tbtnNewDoc_clicked() -> iResult=" << iResult;

    //-------------------------------------------------------
    // tableView 모두 지우기
    while ( _pModelSelectedList->rowCount() > 0 ) {
        _pModelSelectedList->removeRow( 0 );
    }

    // 새로 읽어오기
    showSelectedList( _strCurCategoryID );
    ui->_tvList->selectRow( 0 );

    //---------------------------------------------
    _strCurstrListID = ui->_tvList->model()->index(0,0).data().toString();
    showContent( _strCurstrListID );
}

void MainWindow::on__tbtnUpdateTitle_clicked()
{
    qDebug() << "MainWindow::on__tbtnUpdateTitle_clicked()";
    AddNewItemDialog dlg( this );
    dlg.setWindowTitle( "Update Title" );
    dlg.setPopupType( AddNewItemDialog::UPDATE_TITLE );
    QModelIndexList indexes = ui->_tvList->selectionModel()->selectedRows();
    QString strCurID = ui->_tvList->model()->index(indexes.last().row(), 0).data().toString();
    dlg.setCurID( strCurID );
    dlg.setTitle( ui->_tvList->model()->index(indexes.last().row(), 1).data().toString() );

    int iResult = dlg.exec();
    qDebug() << "MainWindow::on__tbtnUpdateTitle_clicked() -> dlg finished... iResult=" << iResult;

    if ( iResult == 1 ) { // Save를 눌렀을때... 그리고, 성공 했을때...
        QString strNewTitle = getTitle(strCurID);
        qDebug() << strNewTitle;

        QModelIndexList indexes = ui->_tvList->selectionModel()->selectedRows();
        if ( !indexes.isEmpty() ) {
            ui->_tvList->model()->setData( ui->_tvList->model()->index(indexes.last().row(),1),
                                            strNewTitle );
        }
    }
}

QString MainWindow::getTitle( const QString & strID ) {
    QString strResult("");

    //-------------------------------------------------------
    // db 데이터 로드
    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::getTitle() -> Failed to open the database";
        return "";
    }

    QSqlQuery sql;
    QString strSQL(
                    "select title from Tip "
                    "where id=" + strID
                );
    qDebug() << strSQL;

    if ( !sql.exec(strSQL) ) {
        qDebug() << "MainWindow::getTitle() -> failed select SQL...";
        return "";
    }

    while ( sql.next() ) {
        strResult = sql.value(sql.record().indexOf("title")).toString();
    }

    return strResult;
}

void MainWindow::on__tbtnSaveDoc_clicked() {
    qDebug() << "MainWindow::on__tbtnSaveDoc_clicked()";

    if ( _pModelSelectedList->rowCount() <= 0 ) {
        qDebug() << "MainWindow::on__tbtnSaveDoc_clicked() -> 선택된 항목이 없습니다.";
        return;
    }

    if ( _strCurstrListID.length() <= 0 ) {
        qDebug() << "MainWindow::on__tbtnSaveDoc_clicked() -> 선택된 ListID가 없습니다.";
        return;
    }

    //-------------------------------------------------------
    // db 데이터 로드
    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::on__tbtnSaveDoc_clicked() -> Failed to open the database";
        return;
    }

    //update tip set content=''
    //WHERE id=3;

    QSqlQuery sql;
    sql.prepare(
                "update tip set content=:content "
                "where id=" + _strCurstrListID
    );

#if 1
    int iCurrentLine = _pEditor->textCursor().blockNumber(); // 현재 줄 번호 저장
    qDebug() << "MainWindow::on__tbtnSaveDoc_clicked() -> iCurrentLine=" << iCurrentLine;
    int iCurrentScrollValue = _pEditor->verticalScrollBar()->value();

    _pEditor->setPlainText( _pEditor->toPlainText().replace("\t", "    ") ); // tab -> "    "

    //------------------------------------------------------------------------------
    // 현재 작업 중인 위치로 커서 이동
    QTextCursor cursor(_pEditor->document()->findBlockByLineNumber(iCurrentLine));
    _pEditor->setTextCursor( cursor );
    _pEditor->verticalScrollBar()->setValue( iCurrentScrollValue );
#endif


    sql.bindValue( ":content", _pEditor->toPlainText() );
    int iResult = sql.exec();
    qDebug() << "MainWindow::on__tbtnSaveDoc_clicked() -> iResult=" << iResult;

    if ( iResult == 1 ) { // 크기 정보를 QTableView에 Update 처리한다.

        QModelIndexList indexes = ui->_tvList->selectionModel()->selectedRows();
        if ( !indexes.isEmpty()
             && _strCurstrListID == ui->_tvList->model()->index(indexes.last().row(), 0).data().toString() ) {
            ui->_tvList->model()->setData( ui->_tvList->model()->index(indexes.last().row(),2),
                                            QString::number(_pEditor->toPlainText().length()) );
        }
    }
}

void MainWindow::on__tbtnDelDoc_clicked() {
    QMessageBox::StandardButton dialog;

    dialog = QMessageBox::warning( this, "Confirm Delete", "Do you really want to delete this item?",
                                   QMessageBox::Ok | QMessageBox::Cancel );
    if ( dialog != QMessageBox::Ok) {
        return;
    }

    qDebug() << "MainWindow::on__tbtnDelDoc_clicked()";

    if ( _pModelSelectedList->rowCount() <= 0 ) {
        qDebug() << "MainWindow::on__tbtnDelDoc_clicked() -> 선택된 항목이 없습니다.";
        return;
    }

    if ( _strCurstrListID.length() <= 0 ) {
        qDebug() << "MainWindow::on__tbtnDelDoc_clicked() -> 선택된 ListID가 없습니다.";
        return;
    }

    //-------------------------------------------------------
    // db 데이터 로드
    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::on__tbtnDelDoc_clicked() -> Failed to open the database";
        return;
    }

    // DELETE FROM employee WHERE id = 1007

    QSqlQuery sql;
    QString strSQL(
                "delete from Tip "
                "where id=" + _strCurstrListID
    );
    qDebug() << strSQL;

    int iResult = sql.exec( strSQL );
    qDebug() << "MainWindow::on__tbtnDelDoc_clicked() -> iResult=" << iResult;

    if ( iResult == 1 ) { // 지워 졌으면, QTableView도 정리를 한다.
        _pEditor->setPlainText("");

        QModelIndexList indexes = ui->_tvList->selectionModel()->selectedRows();
        while ( !indexes.isEmpty() ) {
            _pModelSelectedList->removeRows( indexes.last().row(), 1 );
            indexes.removeLast();
        }
    }
}

void MainWindow::on_action_Font_triggered() {
    qDebug() << "on_action_Font_triggered() called...";

    bool bOk = false;
    QFont font = QFontDialog::getFont( &bOk, QFont("Courier", 10), this );

    if ( bOk ) {
        qDebug() << "FontName=" << font.family() << "FontSize=" << font.pointSize();
        writeFontIni( font.family(), font.pointSize() );

        font.setFixedPitch( true );
        _pEditor->setFont( font );
    }
    else {

    }
}

void MainWindow::on_actionFind_All_triggered() {
    qDebug() << "on_actionFind_All_triggered() called...";

    ui->_edFindText->setFocus();

    if ( ui->_cmbCategoryForSearch->count() > 0 ) {
        ui->_cmbCategoryForSearch->clear();
    }

    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::on_actionFind_All_triggered() -> Failed to open the database";
        return;
    }

    // SELECT count(*) AS tip_count FROM Tip WHERE category_id=2
    QSqlQuery sql;
    QString strSQL( "SELECT id, name FROM category" );
    qDebug() << strSQL;

    if ( !sql.exec(strSQL) ) {
        qDebug() << "MainWindow::on_actionFind_All_triggered() -> failed select SQL...";
        return;
    }

    ui->_cmbCategoryForSearch->addItem( "All", QString("-1") ); // 전체

    while ( sql.next() ) {
        int iId = sql.value(sql.record().indexOf("id")).toInt();
        QString strName = sql.value(sql.record().indexOf("name")).toString();

        ui->_cmbCategoryForSearch->addItem( strName, iId );
    }

    ui->_dckWidSearchResult->setVisible( true );
}

void MainWindow::on__btnFind_clicked() {
    qDebug() << "on__btnFind_clicked() called...";

    if ( ui->_edFindText->text().length() <= 0 ) {
        qDebug() << "empty search key words.";
        return;
    }

    if ( ui->_chkTitle->isChecked() == false
         && ui->_chkContent->isChecked() == false ) {
        qDebug() << "You have to select title or content first.";
        return;
    }

    //-----------------------------------------------------------------
    // tableView 모두 지우기
    while ( _pModelFindList->rowCount() > 0 ) {
        _pModelFindList->removeRow( 0 );
    }

    //-----------------------------------------------------------------
    int iCurCateID = ui->_cmbCategoryForSearch->itemData( ui->_cmbCategoryForSearch->currentIndex() ).toInt();
    //qDebug() << iCurCateID;
    int iCheck = 0;
    QString strWhere = " WHERE ";

    QString strCategory_id("");
    QString strTitle("");
    QString strContent("");
    if ( iCurCateID != -1 ) { // 전체가 아니면...
        strCategory_id = " category_id=" + QString::number(iCurCateID);
        iCheck += 1;
    }

    if ( ui->_chkTitle->isChecked()
         && ui->_edFindText->text().length() > 0 ) {
        strTitle = " title LIKE '%" + ui->_edFindText->text() + "%' ";
        iCheck += 2;
    }

    if ( ui->_chkContent->isChecked()
         && ui->_edFindText->text().length() > 0 ) {
        strContent += " content LIKE '%" + ui->_edFindText->text() + "%' ";
        iCheck += 4;
    }

    //-------------------------------------------------------
    switch( iCheck ) {
    case 0:
        strWhere = "";
        break;
    case 1: // category_id
        strWhere += strCategory_id;
        break;
    case 2: // title
        strWhere += strTitle;
        break;
    case 4: // content
        strWhere += strContent;
        break;
    case 3: // category_id, title
        strWhere += strCategory_id + " AND " + strTitle;
        break;
    case 5: // category_id, content
        strWhere += strCategory_id + " AND " + strContent;
        break;
    case 6: // title, content
        strWhere += strTitle + " OR " + strContent;
        break;
    case 7: // category_id, title, content
        strWhere += strCategory_id + " AND (" + strTitle + " OR " + strContent + ")";
        break;
    }

    qDebug() << strWhere;

    //-----------------------------------------------------------------
    //SELECT name, langtype, title FROM Category
    //INNER JOIN Tip ON Category.id=Tip.category_id;

    if ( !_myTipBagDb.isOpen() ) {
        qDebug() << "MainWindow::on__btnFind_clicked() -> Failed to open the database";
        return;
    }

    // SELECT count(*) AS tip_count FROM Tip WHERE category_id=2
    QSqlQuery sql;
    QString strSQL(
                    "SELECT Tip.id AS tip_id, name, langtype, title, substr(content,1,60) AS content FROM Category "
                    "INNER JOIN Tip ON Category.id=Tip.category_id " + strWhere
                  );
    qDebug() << strSQL;

    if ( !sql.exec(strSQL) ) {
        qDebug() << "MainWindow::on__btnFind_clicked() -> failed select SQL...";
        return;
    }

    int iRow = 0;
    QStandardItem * pNewItem = NULL;
    while ( sql.next() ) {
        QString strTipId = sql.value(sql.record().indexOf("tip_id")).toString();
        QString strName = sql.value(sql.record().indexOf("name")).toString();
        int iLangType = sql.value(sql.record().indexOf("langtype")).toInt();
        QString strTitle = sql.value(sql.record().indexOf("title")).toString();
        QString strContent = sql.value(sql.record().indexOf("content")).toString();

        qDebug() << strTipId << strName << iLangType << strTitle;

        pNewItem = new QStandardItem( strTipId );
        _pModelFindList->setItem( iRow, 0, pNewItem );

        pNewItem = new QStandardItem( strName );
        _pModelFindList->setItem( iRow, 1, pNewItem );

        pNewItem = new QStandardItem( _strlstLangType.at(iLangType) );
        pNewItem->setTextAlignment( Qt::AlignCenter );
        _pModelFindList->setItem( iRow, 2, pNewItem );

        pNewItem = new QStandardItem( strTitle );
        _pModelFindList->setItem( iRow, 3, pNewItem );

        pNewItem = new QStandardItem( strContent );
        _pModelFindList->setItem( iRow, 4, pNewItem );

        ++iRow;
    }
}

void MainWindow::on__tvSearchResult_clicked(const QModelIndex &index) {
    _strCurstrListID = index.sibling(index.row(), 0).data().toString();
    showContent( _strCurstrListID );
}

void MainWindow::on__tvSearchResult_activated(const QModelIndex &index) {
    on__tvSearchResult_clicked(index);
}
