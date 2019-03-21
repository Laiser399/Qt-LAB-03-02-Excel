#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QMessageBox>
#include <QModelIndex>
#include <QModelIndexList>
#include <QFileDialog>
#include <QRegExp>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QColorDialog>

#include <QSignalMapper>

#include "tablemodel.h"
#include "schedule.h"
#include "TeachersList.h"
#include "tableview.h"

#include <QtXlsx>

#include <QFontDatabase>

#include <QDebug>

enum {
    idFontName,
    idFontSize,
    idBold, idItalics, idUnderline,
    idVAlign, idHAlign,
    idBLeft, idBTop, idBRight, idBBottom,
    idFontCol, idBgCol
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

    TableView * pTable;
    TableModel *pTableModel;
    //changing by DlgOpen
    QString pathCurrFile;


    //normal handling
    QString FN_GroupSchedule, FN_List, DN_Results;
    //package handling
    QString DP_GroupSchedule, DP_List, DP_Result;

    //TAB WIDGETS
    //TAB1
    QComboBox *pFontName;
    QSpinBox *pFontSize;
    QCheckBox *pFontBold, *pFontItalics, *pFontUnderline;
    //TAB2
    //align
    QComboBox *pVertAlign, *pHorAlign;
    //borders
    QCheckBox *pLeftBorder, *pTopBorder, *pRightBorder, *pBottomBorder;
    //colors
    QPushButton *pbFontCol, *pbBackgroundCol;
    QColor FontCol, CellColor;

    void SetWidgets();
    void SetMenu();

    void ReadSchedule(QXlsx::Document &doc, Schedule &schedule);
    void ReadTeachersList(QXlsx::Document &doc, TeachersList &t_list);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void TabParamChanged(int id);

    //common
    void DlgOpen();
    void DlgSave();
    void DlgSaveAs();
    //normal handling
    void DlgNH_GroupSchedule();
    void DlgNH_List();
    void DlgNH_SaveDir();
    void DlgNH_Execute();
    //package handling
    void DlgPH_GroupSchedule();
    void DlgPH_List();
    void DlgPH_SaveDir();
    void DlgPH_Execute();

    void DlgHelp();
    void DlgAbout();


    void ClickTest();

};

#endif // MAINWINDOW_H
