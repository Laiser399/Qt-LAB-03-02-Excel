#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEBUG

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    SetWidgets();
    SetMenu();

#ifdef DEBUG
    FN_GroupSchedule = "C:\\Users\\Сергей\\Desktop\\Normal Handling\\расписание.xlsx";
    FN_List = "C:\\Users\\Сергей\\Desktop\\Normal Handling\\список.xlsx";
    DN_Results = "C:\\Users\\Сергей\\Desktop\\Normal Handling\\results";

    DP_GroupSchedule = "C:\\Users\\Сергей\\Desktop\\Package Handling\\schedules";
    DP_List = "C:\\Users\\Сергей\\Desktop\\Package Handling\\lists";
    DP_Result = "C:\\Users\\Сергей\\Desktop\\Package Handling\\result";
#endif


}

MainWindow::~MainWindow()
{
    delete ui;
}
//цвет текста
//цвет фона


//расположение по вертикали
//расположение по горизонтали
//4 границы
//
//
//
//

void MainWindow::SetWidgets() {



    QWidget *w = new QWidget;
        QVBoxLayout * pvLayout = new QVBoxLayout;
            QTabWidget * pTabWidget = new QTabWidget;
                //tabs
                QWidget * pwTabFont = new QWidget;
                    QGridLayout *plTabFont = new QGridLayout;
                        QHBoxLayout * phBoxLayFont = new QHBoxLayout;
                            pFontName = new QComboBox;
                            pFontSize = new QSpinBox;
                        QGroupBox * pGroupFont = new QGroupBox;
                            QVBoxLayout * pvBoxLayFont_ = new QVBoxLayout;
                                pFontBold = new QCheckBox("Жирный");
                                pFontItalics = new QCheckBox("Курсив");
                                pFontUnderline = new QCheckBox("Подчеркнутый");
                QWidget *pwTabCell = new QWidget;
                    QHBoxLayout *phBoxLayCell = new QHBoxLayout;
                        QGroupBox *pgbAlignment = new QGroupBox("Выравнивание");
                            QGridLayout *pglAlignment = new QGridLayout;
                                //label1
                                pVertAlign = new QComboBox;
                                //label2
                                pHorAlign = new QComboBox;
                        QGroupBox *pgbBorder = new QGroupBox("Границы");
                            QGridLayout *pglBorder = new QGridLayout;
                                pLeftBorder = new QCheckBox();
                                pTopBorder = new QCheckBox();
                                pRightBorder = new QCheckBox();
                                pBottomBorder = new QCheckBox();
                        QVBoxLayout * pvblFontCol = new QVBoxLayout;
                            pbFontCol = new QPushButton("Цвет текста");
                            pbBackgroundCol = new QPushButton("Цвет фона");
            pTable = new TableView;
                pTableModel = new TableModel();
            //QPushButton * pButton = new QPushButton("Click for test");

    //plTabFont->addWidget(pFontName, 0, 0);
    //plTabFont->addWidget(pFontSize, 0, 1);
    //plTabFont->addWidget(p_Check_Box, 1, 0);

    setCentralWidget(w);
        w->setLayout(pvLayout);
            pvLayout->addWidget(pTabWidget);
                //tabs
                pTabWidget->addTab(pwTabFont, "Шрифт");
                    pwTabFont->setLayout(plTabFont);
                        plTabFont->addLayout(phBoxLayFont, 0, 0);
                            phBoxLayFont->addWidget(pFontName);
                            phBoxLayFont->addWidget(pFontSize);
                        plTabFont->addWidget(pGroupFont, 1, 0);
                            pGroupFont->setLayout(pvBoxLayFont_);
                                pvBoxLayFont_->addWidget(pFontBold);
                                pvBoxLayFont_->addWidget(pFontItalics);
                                pvBoxLayFont_->addWidget(pFontUnderline);
                pTabWidget->addTab(pwTabCell, "Ячейка");
                    pwTabCell->setLayout(phBoxLayCell);
                        phBoxLayCell->addWidget(pgbAlignment);
                            pgbAlignment->setLayout(pglAlignment);
                                pglAlignment->addWidget(new QLabel("По верт."), 0, 0);
                                pglAlignment->addWidget(pVertAlign, 0, 1);
                                pglAlignment->addWidget(new QLabel("По гор."), 1, 0);
                                pglAlignment->addWidget(pHorAlign, 1, 1);
                        phBoxLayCell->addWidget(pgbBorder);
                            pgbBorder->setLayout(pglBorder);
                                pglBorder->addWidget(pLeftBorder, 1, 0);
                                pglBorder->addWidget(pTopBorder, 0, 1);
                                pglBorder->addWidget(pRightBorder, 1, 2);
                                pglBorder->addWidget(pBottomBorder, 2, 1);
                        phBoxLayCell->addLayout(pvblFontCol);
                            pvblFontCol->addWidget(pbFontCol);
                            pvblFontCol->addWidget(pbBackgroundCol);
            pvLayout->addWidget(pTable);
                pTable->setModel(pTableModel);
            //pvLayout->addWidget(pButton);

    pvLayout->setContentsMargins(0, 0, 0, 0);

    pTabWidget->setMinimumHeight(160);
    pTabWidget->setMaximumHeight(160);

    pgbAlignment->setMinimumWidth(150);
    pgbAlignment->setMaximumWidth(150);

    pgbBorder->setMinimumWidth(110);
    pgbBorder->setMaximumWidth(110);

    //TAB1
    pFontName->setEditable(true);
    //pFontName->addItem("");
    pFontName->addItems(QFontDatabase().families());
    pFontSize->setRange(1, 200);
    pFontSize->setValue(11);
    //TAB2
    //pVertAlign->addItem("");
    pVertAlign->addItem("Сверху");
    pVertAlign->addItem("По центру");
    pVertAlign->addItem("Снизу");
    //pHorAlign->addItem("");
    pHorAlign->addItem("Слева");
    pHorAlign->addItem("По центру");
    pHorAlign->addItem("Справа");

    pTable->setItemDelegate(new CellDelegate);

    //pTabWidget->setMinimumHeight(100);
    //pTabWidget->setMaximumHeight(100);

    //test
    //Q_ASSERT(connect(pButton, SIGNAL(clicked()), SLOT(ClickTest())));


    QSignalMapper *pSigMap = new QSignalMapper(this);
    connect(pSigMap, SIGNAL(mapped(int)), SLOT(TabParamChanged(int)));

    //TAB1
    connect(pFontName, SIGNAL(currentIndexChanged(int)), pSigMap, SLOT(map()));
    connect(pFontSize, SIGNAL(valueChanged(int)), pSigMap, SLOT(map()));
    connect(pFontBold, SIGNAL(clicked(bool)), pSigMap, SLOT(map()));
    connect(pFontItalics, SIGNAL(clicked(bool)), pSigMap, SLOT(map()));
    connect(pFontUnderline, SIGNAL(clicked(bool)), pSigMap, SLOT(map()));
    pSigMap->setMapping(pFontName, idFontName);
    pSigMap->setMapping(pFontSize, idFontSize);
    pSigMap->setMapping(pFontBold, idBold);
    pSigMap->setMapping(pFontItalics, idItalics);
    pSigMap->setMapping(pFontUnderline, idUnderline);
    //TAB2
    connect(pVertAlign, SIGNAL(currentIndexChanged(int)), pSigMap, SLOT(map()));
    connect(pHorAlign, SIGNAL(currentIndexChanged(int)), pSigMap, SLOT(map()));
    connect(pLeftBorder, SIGNAL(clicked(bool)), pSigMap, SLOT(map()));
    connect(pTopBorder, SIGNAL(clicked(bool)), pSigMap, SLOT(map()));
    connect(pRightBorder, SIGNAL(clicked(bool)), pSigMap, SLOT(map()));
    connect(pBottomBorder, SIGNAL(clicked(bool)), pSigMap, SLOT(map()));
    connect(pbFontCol, SIGNAL(clicked()), pSigMap, SLOT(map()));
    connect(pbBackgroundCol, SIGNAL(clicked()), pSigMap, SLOT(map()));
    pSigMap->setMapping(pVertAlign, idVAlign);
    pSigMap->setMapping(pHorAlign, idHAlign);
    pSigMap->setMapping(pLeftBorder, idBLeft);
    pSigMap->setMapping(pTopBorder, idBTop);
    pSigMap->setMapping(pRightBorder, idBRight);
    pSigMap->setMapping(pBottomBorder, idBBottom);
    pSigMap->setMapping(pbFontCol, idFontCol);
    pSigMap->setMapping(pbBackgroundCol, idBgCol);


}

void MainWindow::SetMenu() {
    QMenu * pmFile = new QMenu("&Файл");
    pmFile->addAction("&Открыть", this, SLOT(DlgOpen()), Qt::CTRL + Qt::Key_O);
    pmFile->addAction("&Сохранить", this, SLOT(DlgSave()), Qt::CTRL + Qt::Key_S);
    pmFile->addAction("&Сохранить как...", this, SLOT(DlgSaveAs()));
    pmFile->addSeparator();
    pmFile->addAction("&Выход", this, SLOT(close()));

    QMenu * pmNormalHandling = new QMenu("Обычная обработка");
    pmNormalHandling->addAction("Выбрать файл с расписанием групп",
                                this, SLOT(DlgNH_GroupSchedule()));
    pmNormalHandling->addAction("Выбрать файл со списком \"Преп. - дисцип.\"",
                                this, SLOT(DlgNH_List()));
    pmNormalHandling->addAction("Выбрать директорию сохранения",
                                this, SLOT(DlgNH_SaveDir()));
    pmNormalHandling->addAction("Преобразовать",
                                this, SLOT(DlgNH_Execute()));

    QMenu * pmPackageHandling = new QMenu("Пакетная обработка");
    pmPackageHandling->addAction("Выбрать директорию с расписаниями групп",
                                 this, SLOT(DlgPH_GroupSchedule()));
    pmPackageHandling->addAction("Выбрать директорию со списками \"Преп. - дисцип.\"",
                                 this, SLOT(DlgPH_List()));
    pmPackageHandling->addAction("Выбрать директорию сохранения",
                                 this, SLOT(DlgPH_SaveDir()));
    pmPackageHandling->addAction("Преобразовать",
                                 this, SLOT(DlgPH_Execute()));

    QMenu * pmHelp = new QMenu("&?");
    pmHelp->addAction("&Помощь", this, SLOT(DlgHelp()), Qt::Key_F1);
    pmHelp->addAction("&О программе", this, SLOT(DlgAbout()));

    ui->menuBar->addMenu(pmFile);
    ui->menuBar->addMenu(pmNormalHandling);
    ui->menuBar->addMenu(pmPackageHandling);
    ui->menuBar->addMenu(pmHelp);
}

#define DAY_AT_WEEK 6
#define LESSONS_AT_DAY 7
void MainWindow::ReadSchedule(QXlsx::Document &doc, Schedule &schedule) {

    //чтение расписания
    int curr_col = 4;
    while (true) {
        QXlsx::Cell *cell = doc.cellAt(1, curr_col);



        //нет ячейки или пустая строка
        if (!cell || cell->value().toString().simplified().isEmpty())
            break;
        int id_last_gr;
        if ((id_last_gr = schedule.AppendGroup(cell->value().toString())) == -1) {
            curr_col++;
            continue;
        }


        int l_count = schedule.getCountLessons();
        int days_count = schedule.getDaysInWeek();

        QRegExp pair("(.*),(.*)");
        //первая неделя
        for (int irow = 2; irow <= l_count * days_count * 2; irow += 2) {
            QXlsx::Cell * cellPair = doc.cellAt(irow, curr_col);
            if (!cellPair)
                continue;
            // (irow / 2 - 1) / 7
            // (irow / 2 - 1) % 7
            if (pair.indexIn(cellPair->value().toString()) == -1)
                continue;
            schedule.SetLesson(0, id_last_gr, (irow / 2 - 1) / l_count,
                               (irow / 2 - 1) % l_count, pair.cap(1), pair.cap(2));
        }
        //вторая неделя
        for (int irow = 3; irow <= schedule.getCountLessons() * schedule.getDaysInWeek() * 2 + 1; irow += 2) {
            QXlsx::Cell * cellPair = doc.cellAt(irow, curr_col);
            if (!cellPair)
                continue;
            if (pair.indexIn(cellPair->value().toString()) == -1)
                continue;
            schedule.SetLesson(1, id_last_gr, ((irow - 1) / 2 - 1) / l_count,
                               ((irow - 1) / 2 - 1) % l_count, pair.cap(1), pair.cap(2));
        }
        curr_col++;
    }
}

void MainWindow::ReadTeachersList(QXlsx::Document &doc, TeachersList &t_list) {
    //чтение списка
    int curr_row = 2;
    while (true) {
        QXlsx::Cell * cell_teacher = doc.cellAt(curr_row, 2);
        if (!cell_teacher || cell_teacher->value().toString().simplified().isEmpty())
            break;
        QXlsx::Cell * cell_gr = doc.cellAt(curr_row, 3);
        QXlsx::Cell * cell_lesson = doc.cellAt(curr_row, 4);
        if (!cell_gr || !cell_lesson ||
                cell_gr->value().toString().simplified().isEmpty() ||
                cell_lesson->value().toString().simplified().isEmpty())
        {
            curr_row++;
            continue;
        }

        t_list.insert(cell_teacher->value().toString(),
                      cell_gr->value().toString(),
                      cell_lesson->value().toString());

        curr_row++;
    }
}

//------------------------|
//                        |
//      private slots     |
//                        |
//------------------------|

void MainWindow::TabParamChanged(int id) {
    switch (id) {
    case idFontName:
        pTable->SetFontName(pFontName->currentText());
        break;
    case idFontSize:
        pTable->SetFontSize(pFontSize->value());
        break;
    case idBold:
        if (pFontBold->checkState() == Qt::Checked)
            pTable->SetBold(true);
        else
            pTable->SetBold(false);
        break;
    case idItalics:
        if (pFontItalics->checkState() == Qt::Checked)
            pTable->SetItalics(true);
        else
            pTable->SetItalics(false);
        break;
    case idUnderline:
        if (pFontUnderline->checkState() == Qt::Checked)
            pTable->SetUnderline(true);
        else
            pTable->SetUnderline(false);
        break;
    case idVAlign:
        switch (pVertAlign->currentIndex()) {
        case 0:
            pTable->SetVAlign(Qt::AlignTop); break;
        case 1:
            pTable->SetVAlign(Qt::AlignVCenter); break;
        case 2:
            pTable->SetVAlign(Qt::AlignBottom); break;
        }
        break;
    case idHAlign:
        switch (pHorAlign->currentIndex()) {
        case 0:
            pTable->SetHAlign(Qt::AlignLeft); break;
        case 1:
            pTable->SetHAlign(Qt::AlignHCenter); break;
        case 2:
            pTable->SetHAlign(Qt::AlignRight); break;
        }
        break;
    case idBLeft:
        if (pLeftBorder->checkState() == Qt::Checked)
            pTable->SetBorderLeft(true);
        else
            pTable->SetBorderLeft(false);
        break;
    case idBTop:
        if (pTopBorder->checkState() == Qt::Checked)
            pTable->SetBorderTop(true);
        else
            pTable->SetBorderTop(false);
        break;
    case idBRight:
        if (pRightBorder->checkState() == Qt::Checked)
            pTable->SetBorderRight(true);
        else
            pTable->SetBorderRight(false);
        break;
    case idBBottom:
        if (pBottomBorder->checkState() == Qt::Checked)
            pTable->SetBorderBottom(true);
        else
            pTable->SetBorderBottom(false);
        break;
    case idFontCol: {
        QColorDialog colDlg;
        QColor col = colDlg.getColor(FontCol, 0, "Цвет текста");
        if (col.isValid()) {
            FontCol = col;
            pTable->SetFontCol(col);
        }
        break;
    }
    case idBgCol: {
        QColorDialog colDlg;
        QColor col = colDlg.getColor(CellColor, 0, "Цвет фона");
        if (col.isValid()) {
            CellColor = col;
            pTable->SetBackgroundCol(col);
        }
        break;
    }
    }

}



//----------------|
// Common options |
//----------------|
void MainWindow::DlgOpen() {
    QFileDialog dlg;
    QString filename = dlg.getOpenFileName(0, "Выберите файл", QString(), "*.xlsx");
    if (!filename.isEmpty()) {
        QXlsx::Document doc(filename);
        QXlsx::CellRange c_range = doc.dimension();
        if (!c_range.isValid()) {
            QMessageBox::warning(0, "Ошибка", "Ошибка чтения документа!");
            return;
        }
        //очистка пред данных
        pTableModel->SetRowCount(0);
        pTableModel->SetRowCount(c_range.bottomRight().row());
        pTableModel->SetColCount(c_range.bottomRight().column());
        //проход по .xlsx
        for (int irow = 0,
             iLastRow = c_range.bottomLeft().row();
             irow < iLastRow; irow++)
        {
            for (int icol = 0,
                 iLastCol = c_range.topRight().column();
                 icol < iLastCol; icol++)
            {
                if (doc.cellAt(irow + 1, icol + 1)) {
                    pTableModel->SetExistingCell(irow, icol,
                                                    doc.cellAt(irow + 1, icol + 1)->value().toString(),
                                                    doc.cellAt(irow + 1, icol + 1)->format());
                }
                else {
                    pTableModel->SetExistingCell(irow, icol, "", QXlsx::Format());
                }
            }
        }
        pathCurrFile = filename;
    }
}

void MainWindow::DlgSave() {
    if (pathCurrFile.isEmpty())
        return;
    if (!pTableModel->SaveToFile(pathCurrFile)) {
        QMessageBox::information(0, "Ошибка", "Ошибка сохранения документа!");
    }
}

void MainWindow::DlgSaveAs() {
    QFileDialog dlg;
    QString filename = dlg.getSaveFileName(0, "Введите имя файла", "", "*.xlsx");
    if (filename.isEmpty())
        return;
    if (filename.indexOf(".xlsx", 0, Qt::CaseInsensitive) == -1) {
        filename += ".xlsx";
    }
    if (!pTableModel->SaveToFile(filename)) {
        QMessageBox::information(0, "Ошибка", "Ошибка сохранения документа!");
    }
}

//-------------------------|
// Normal handling options |
//-------------------------|
void MainWindow::DlgNH_GroupSchedule() {
    QFileDialog dlg;
    QString filename = dlg.getOpenFileName(0, "Выберите файл", "", "*.xlsx");
    if (!filename.isEmpty())
        FN_GroupSchedule = filename;
}

void MainWindow::DlgNH_List() {
    QFileDialog dlg;
    QString filename = dlg.getOpenFileName(0, "Выберите файл", "", "*.xlsx");
    if (!filename.isEmpty())
        FN_List = filename;
}

void MainWindow::DlgNH_SaveDir() {
    QFileDialog dlg;
    QString dir = dlg.getExistingDirectory(0, "Выберите место сохранения");
    if (!dir.isEmpty())
        DN_Results = dir;
}

void MainWindow::DlgNH_Execute() {
    if (FN_GroupSchedule.isEmpty() || FN_List.isEmpty()) {
        QMessageBox::information(0, "Ошибка", "Не заданы файлы для обработки!");
        return;
    }

    QXlsx::Document doc_schedule(FN_GroupSchedule), doc_list(FN_List);
    if (!doc_schedule.dimension().isValid()) {
        QMessageBox::information(0, "Ошибка", "Ошибка чтения файла с расписанием!");
        return;
    }
    else if (!doc_list.dimension().isValid()) {
        QMessageBox::information(0, "Ошибка", "Ошибка чтения файла со списком \"Преп. - дисцип.\"!");
        return;
    }

    //чтение расписания
    Schedule schedule;
    schedule.SetDimension(DAY_AT_WEEK, LESSONS_AT_DAY);
    ReadSchedule(doc_schedule, schedule);

    //чтение списка
    TeachersList t_list;
    ReadTeachersList(doc_list, t_list);

    if (DN_Results.isEmpty()) {
        QDir dir(FN_List);
        dir.cdUp();
        DN_Results = dir.absolutePath();
    }
    if (!t_list.NormalHandling(schedule, DN_Results)) {
        QMessageBox::information(0, "Ошибка", "Во время выполнения произошла ошибка!");
    }
}

//--------------------------|
// Package handling options |
//--------------------------|
void MainWindow::DlgPH_GroupSchedule() {
    QFileDialog dlg;
    QString dir = dlg.getExistingDirectory(0, "Выберите место сохранения");
    if (!dir.isEmpty())
        DP_GroupSchedule = dir;
}

void MainWindow::DlgPH_List() {
    QFileDialog dlg;
    QString dir = dlg.getExistingDirectory(0, "Выберите место сохранения");
    if (!dir.isEmpty())
        DP_List = dir;
}

void MainWindow::DlgPH_SaveDir() {
    QFileDialog dlg;
    QString dir = dlg.getExistingDirectory(0, "Выберите место сохранения");
    if (!dir.isEmpty())
        DP_Result = dir;
}

void MainWindow::DlgPH_Execute() {
    if (DP_GroupSchedule.isEmpty() || DP_List.isEmpty() || DP_Result.isEmpty()) {
        QMessageBox::information(0, "Ошибка", "Не заданы директории!");
        return;
    }

    QDir dir_schedule(DP_GroupSchedule), dir_list(DP_List);
    QStringList filesSchedules, filesLists;
    filesSchedules = dir_schedule.entryList(QDir::Files | QDir::NoDotAndDotDot);
    filesLists = dir_list.entryList(QDir::Files | QDir::NoDotAndDotDot);

    if (filesSchedules.size() == 0) {
        QMessageBox::information(0, "Ошибка", "Не найдены файлы расписания!");
        return;
    }
    else if (filesLists.size() == 0) {
        QMessageBox::information(0, "Ошибка", "Не найдены файлы списков!");
        return;
    }

    Schedule schedule;
    schedule.SetDimension(DAY_AT_WEEK, LESSONS_AT_DAY);
    TeachersList t_list;

    //чтение файлов расписаний
    for (int i = 0; i < filesSchedules.size(); i++) {
        if (filesSchedules[i].indexOf(".xlsx", 0, Qt::CaseInsensitive) == -1)
            continue;
        QXlsx::Document doc(dir_schedule.absolutePath() + '/' + filesSchedules[i]);
        if (!doc.dimension().isValid())
            continue;

        QStringList Sheets = doc.sheetNames();
        //проходим по вкладкам в каждом файле
        for (int i_sh = 0; i_sh < Sheets.size(); i_sh++) {
            doc.selectSheet(Sheets[i_sh]);
            ReadSchedule(doc, schedule);

        }
    }

    //чтение файлов списков
    for (int i = 0; i < filesLists.size(); i++) {
        if (filesLists[i].indexOf(".xlsx", 0, Qt::CaseInsensitive) == -1)
            continue;
        QXlsx::Document doc(dir_list.absolutePath() + '/' + filesLists[i]);
        if (!doc.dimension().isValid())
            continue;

        QStringList Sheets = doc.sheetNames();
        //проходим по вкладкам в каждом файле
        for (int i_sh = 0; i_sh < Sheets.size(); i_sh++) {
            doc.selectSheet(Sheets[i_sh]);
            ReadTeachersList(doc, t_list);
        }
    }

    //TODO exec
    Q_ASSERT(DP_Result[DP_Result.size() - 1] != '\\');
    QString filename = DP_Result + "\\result.xlsx";

    //schedule.test_out();
    //qDebug() << schedule.getCountGroups();
    //t_list.test_out();

    if (!t_list.PackageHandling(schedule, filename)) {
        QMessageBox::information(0, "Ошибка", "Во время выполнения произошла ошибка!");
    }
}

void MainWindow::DlgHelp() {
    QMessageBox::information(0, "Помощь", "   Открытие, сохранение файлов происходит из меню \"Файл\".\n"
                             "   Для создания расписания преподавателей в меню присутствуют пункты \"Обычная обработка\", \"Пакетная обработка\".\n"
                             "   \"Обычная обработка\" считывает данные из указанных файлов (только с первых вкладок) и сохраняет результаты в указанную директорию.\n"
                             "   \"Пакетная обработка\" проходит по всем файлам, в каждом файле - по всем вкладкам, и сохраняет результат в указанную директорию.");
}

void MainWindow::DlgAbout() {
    QMessageBox::information(0, "О программе", "Автор: студент МАИ\n"
                             "Группа: М8О-213Б-17\n"
                             "ФИО: Семенов Сергей Дмитриевич\n"
                             "Программа редактирует \".xlsx\" файлы, составляет расписание для преподавателей по данным расписанию студентов и списку преподавателей.");

}










//test slot
void MainWindow::ClickTest() {
    //pTable->print_selected_cells();
}

















