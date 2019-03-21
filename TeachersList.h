#ifndef TEACHERSLIST_H
#define TEACHERSLIST_H

#include <QMap>
#include <QVector>
#include <QPair>
#include <QString>
#include <QDir>
#include <algorithm>
#include <QtXlsx>


#include "schedule.h"

#include <QDebug>

QString & NameToNormalForm(QString & name);

class TeachersList
{
public:
    TeachersList();
    bool insert(QString TeacherName, QString sGroup, QString sLesson);
    bool NormalHandling(Schedule & schedule, QString &dirName);
    bool PackageHandling(Schedule & schedule, QString &fileName);


    void test_out();
private:
    typedef QVector<QPair<QString, QString> > PairArr;
    QMap<QString, PairArr> MapTeachers;

    void CreateTemplateXlsx_NH(QXlsx::Document & doc, const QString & TeacherName,
                               int days_at_week, int lessons_at_day);
    void CreateTemplateXlsx_PH(QXlsx::Document & doc, int days_at_week, int lessons_at_day);

};

#endif // TEACHERSLIST_H
