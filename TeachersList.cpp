#include "TeachersList.h"

//-----------------|
//   Common func   |
//-----------------|
QString & NameToNormalForm(QString & name) {
    name = name.simplified();
    for (int i = 0, i2 = name.length(); i < i2; i++) {
        if ((i == 0) || (name[i - 1].isSpace())) {
            name[i] = name[i].toUpper();
        }
        else {
            name[i] = name[i].toLower();
        }
    }
    return name;
}

QString toVertical(QString str) {
    str = str.replace(QRegExp(".{0}"), "\n");
    return str;
}





TeachersList::TeachersList()
{
}

bool TeachersList::insert(QString TeacherName, QString sGroup, QString sLesson) {
    GroupToNormal(sGroup);
    LessonToNormal(sLesson);
    NameToNormalForm(TeacherName);
    if (sGroup.isEmpty() || sLesson.isEmpty() || TeacherName.isEmpty())
        return false;

    QMap<QString, PairArr>::iterator it;
    if ((it = MapTeachers.find(TeacherName)) == MapTeachers.end()) {
        MapTeachers.insert(TeacherName,
                           PairArr(1, QPair<QString, QString>(sGroup, sLesson)));
    }
    else {
        PairArr & arr = it.value();
        for (int i = 0; i < arr.size(); i++) {
            if ((arr[i].first == sGroup) && (arr[i].second == sLesson))
                return false;
        }
        arr.push_back(QPair<QString, QString>(sGroup, sLesson));
    }
    return true;
}

void TeachersList::CreateTemplateXlsx_NH(QXlsx::Document & doc, const QString & TeacherName,
        int days_at_week, int lessons_at_day)
{
    doc.mergeCells(QXlsx::CellRange(1, 1, 1, 9));
    doc.setRowHeight(1, 2, 25);

    QXlsx::Format format;

    format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    format.setFontName("Times New Roman");
    format.setFontSize(16);

    //TODO to vertical string
    for (int irow = 3; irow < days_at_week * 2 + 2; irow += 2) {
        doc.mergeCells(QXlsx::CellRange(irow, 2, irow + 1, 2));
        doc.setRowHeight(irow, 82);
        doc.setRowHeight(irow + 1, 82);

        //заполнение I II
        format.setFontSize(16);
        format.setFontBold(false);
        format.setTextWarp(false);
        doc.write(irow, 1, "I", format);
        doc.write(irow + 1, 1, "II", format);

        format.setFontSize(11);
        format.setFontBold(true);
        format.setTextWarp(true);
        switch ((irow - 3) / 2) {
        case 0:
            doc.write(irow, 2, toVertical(QString("Понедельник")), format); break;
        case 1:
            doc.write(irow, 2, toVertical(QString("Вторник")), format); break;
        case 2:
            doc.write(irow, 2, toVertical(QString("Среда")), format); break;
        case 3:
            doc.write(irow, 2, toVertical(QString("Четверг")), format); break;
        case 4:
            doc.write(irow, 2, toVertical(QString("Пятница")), format); break;
        case 5:
            doc.write(irow, 2, toVertical(QString("Суббота")), format); break;
        case 6:
            doc.write(irow, 2, toVertical(QString("Воскресенье")), format); break;
        }
    }

    format.setFontBold(true);
    format.setFontSize(13);
    for (int icol = 3; icol < lessons_at_day + 3; icol++) {
        doc.write(2, icol, icol - 2, format);
    }
    format.setFontBold(true);
    format.setFontSize(14);
    format.setHorizontalAlignment(QXlsx::Format::AlignLeft);
    doc.write(1, 1, TeacherName, format);
}

void TeachersList::CreateTemplateXlsx_PH(QXlsx::Document & doc, int days_at_week, int lessons_at_day) {
    doc.setRowHeight(1, 25);

    QXlsx::Format format;
    format.setFontName("Times New Roman");
    format.setFontSize(14);
    format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format.setVerticalAlignment(QXlsx::Format::AlignVCenter);

    for (int irow = 2; irow < days_at_week * lessons_at_day * 2 + 1; irow += 2) {
        doc.mergeCells(QXlsx::CellRange(irow, 3, irow + 1, 3));

        doc.write(irow, 1, "I", format);
        doc.write(irow + 1, 1, "II", format);
        doc.write(irow, 3, (irow / 2 - 1) % 7 + 1, format);
    }

    format.setFontBold(true);
    format.setTextWarp(true);
    for (int irow = 2; irow < days_at_week * lessons_at_day * 2 + 1; irow += lessons_at_day * 2) {
        doc.mergeCells(QXlsx::CellRange(irow, 2, irow + lessons_at_day * 2 - 1, 2));

        switch ((irow - 2) / (lessons_at_day * 2)) {
        case 0: doc.write(irow, 2, toVertical(QString("Понедельник")), format); break;
        case 1: doc.write(irow, 2, toVertical(QString("Вторник")), format); break;
        case 2: doc.write(irow, 2, toVertical(QString("Среда")), format); break;
        case 3: doc.write(irow, 2, toVertical(QString("Четверг")), format); break;
        case 4: doc.write(irow, 2, toVertical(QString("Пятница")), format); break;
        case 5: doc.write(irow, 2, toVertical(QString("Суббота")), format); break;
        case 6: doc.write(irow, 2, toVertical(QString("Воскресенье")), format); break;
        }
    }
}

#define COL_WIDTH 40
bool TeachersList::NormalHandling(Schedule & schedule, QString &dirName) {
    QDir dir(dirName);
    if (!dir.exists())
        return false;



    QXlsx::Format format_cell;
    format_cell.setTextWarp(true);
    format_cell.setHorizontalAlignment(QXlsx::Format::AlignLeft);
    format_cell.setVerticalAlignment(QXlsx::Format::AlignTop);

    QMap<QString, PairArr>::iterator it_map;
    //по преподавателям
    for (it_map = MapTeachers.begin(); it_map != MapTeachers.end(); ++it_map) {
        QString tm_path = dir.absolutePath() + '/';
        Q_ASSERT(tm_path[tm_path.length() - 2] != '/');

        QString curr_filename = tm_path + it_map.key() + ".xlsx";

        //по массиву пар "группа - предмет"
        PairArr & p_arr = it_map.value();
        QVector<Schedule::lesson_data> LessonsArr;

        for (int i = 0; i < p_arr.size(); i++) {
            int GroupIndex = schedule.getIndex(p_arr[i].first);
            if (GroupIndex == -1)
                continue;

            QVector<Schedule::lesson_data> tm_arr;

            schedule.FindAllLessons(tm_arr, GroupIndex, p_arr[i].second);

            for (int i_tm = 0; i_tm < tm_arr.size(); i_tm++) {
                LessonsArr.append(tm_arr[i_tm]);
            }
        }


        if (LessonsArr.size() == 0)
            continue;
        //сортировка по времени
        std::sort(LessonsArr.begin(), LessonsArr.end());

        //создание документа
        QXlsx::Document doc_out;
        CreateTemplateXlsx_NH(doc_out, it_map.key(),
            schedule.getDaysInWeek(), schedule.getCountLessons());


        QString cellLesson = LessonsArr[0].Room + ",\n"
                + LessonsArr[0].Lesson + ",\n"
                + LessonsArr[0].Group;

        for (int i_lesson = 1; i_lesson < LessonsArr.size(); i_lesson++) {
            if (LessonsArr[i_lesson - 1] == LessonsArr[i_lesson]) {
                cellLesson += QString(",\n") + LessonsArr[i_lesson].Group;
            }
            else {
                doc_out.setColumnWidth(LessonsArr[i_lesson - 1].NumberLesson + 3, COL_WIDTH);
                doc_out.write(LessonsArr[i_lesson - 1].DayOfWeek * 2 + 3 + LessonsArr[i_lesson - 1].type_week,
                        LessonsArr[i_lesson - 1].NumberLesson + 3, cellLesson, format_cell);
                cellLesson = LessonsArr[i_lesson].Room + ",\n"
                        + LessonsArr[i_lesson].Lesson + ",\n"
                        + LessonsArr[i_lesson].Group;
            }
            if (i_lesson == LessonsArr.size() - 1) {
                doc_out.setColumnWidth(LessonsArr[i_lesson].NumberLesson + 3, COL_WIDTH);
                doc_out.write(LessonsArr[i_lesson].DayOfWeek * 2 + 3 + LessonsArr[i_lesson].type_week,
                        LessonsArr[i_lesson].NumberLesson + 3, cellLesson, format_cell);
            }
        }
        doc_out.saveAs(curr_filename);
    }


    return true;
}

bool TeachersList::PackageHandling(Schedule & schedule, QString &fileName) {
    QXlsx::Document doc;
    CreateTemplateXlsx_PH(doc, schedule.getDaysInWeek(), schedule.getCountLessons());

    QXlsx::Format cell_f, teacher_f;
    cell_f.setVerticalAlignment(QXlsx::Format::AlignTop);
    cell_f.setHorizontalAlignment(QXlsx::Format::AlignLeft);
    cell_f.setTextWarp(true);
    teacher_f.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    teacher_f.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    teacher_f.setFontBold(true);

    //цикл по преподавателям
    QMap<QString, PairArr>::iterator it_map;
    int CurrCol = 0;
    for (it_map = MapTeachers.begin(), CurrCol = 4; it_map != MapTeachers.end(); ++it_map, CurrCol++) {
        doc.write(1, CurrCol, it_map.key(), teacher_f);

        //по массиву пар "группа - предмет"
        PairArr & p_arr = it_map.value();
        QVector<Schedule::lesson_data> LessonsArr;

        for (int i = 0; i < p_arr.size(); i++) {
            //получ индекс группы
            int GroupIndex = schedule.getIndex(p_arr[i].first);
            if (GroupIndex == -1)
                continue;

            QVector<Schedule::lesson_data> tm_arr;

            schedule.FindAllLessons(tm_arr, GroupIndex, p_arr[i].second);

            for (int i_tm = 0; i_tm < tm_arr.size(); i_tm++) {
                LessonsArr.append(tm_arr[i_tm]);
            }
        }

        if (LessonsArr.size() == 0)
            continue;
        doc.setColumnWidth(CurrCol, COL_WIDTH);

        //сортировка по времени
        std::sort(LessonsArr.begin(), LessonsArr.end());

        QString cellLesson = LessonsArr[0].Room + ",\n"
                + LessonsArr[0].Lesson + ",\n"
                + LessonsArr[0].Group;

        for (int i_lesson = 1; i_lesson < LessonsArr.size(); i_lesson++) {
            if (LessonsArr[i_lesson - 1] == LessonsArr[i_lesson]) {
                //добавление групп в конец
                cellLesson += QString(",\n") + LessonsArr[i_lesson].Group;
            }
            else {
                doc.write(LessonsArr[i_lesson - 1].DayOfWeek * schedule.getCountLessons()
                        * 2 + 2 + LessonsArr[i_lesson - 1].NumberLesson * 2
                        + LessonsArr[i_lesson - 1].type_week, CurrCol,
                        cellLesson, cell_f);
                cellLesson = LessonsArr[i_lesson].Room + ",\n"
                        + LessonsArr[i_lesson].Lesson + ",\n"
                        + LessonsArr[i_lesson].Group;
            }
            if (i_lesson == LessonsArr.size() - 1) {
                doc.write(LessonsArr[i_lesson].DayOfWeek * schedule.getCountLessons()
                        * 2 + 2 + LessonsArr[i_lesson].NumberLesson * 2
                        + LessonsArr[i_lesson].type_week, CurrCol,
                        cellLesson, cell_f);
            }
        }
    }

    if (!doc.saveAs(fileName))
        return false;
    return true;
}








void TeachersList::test_out() {
    for (QMap<QString, PairArr>::iterator it = MapTeachers.begin(); it != MapTeachers.end(); ++it) {
        qDebug() << "KEY - " << it.key();
        PairArr & arr = it.value();
        for (int i = 0; i < arr.size(); i++) {
            qDebug() << "   " << arr[i];
        }
    }
}
