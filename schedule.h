#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QVector>
#include <QPair>
#include <QString>

#include <QDebug>

QString & RoomToNormal(QString & str);
QString & LessonToNormal(QString & str);
QString & GroupToNormal(QString & str);

class Schedule
{
public:
    //typedefs
    //аудитория - предмет
    typedef QPair<QString, QString> Lesson;
    typedef QVector<Lesson> DayOfWeek;
    typedef QVector<DayOfWeek> WeekSchedule;
    //[group_index][day_of_week][номер_пары]
    typedef QVector<WeekSchedule> arrWeekSchedule;

    //methods
    explicit Schedule();

    bool SetDimension(int DaysInWeek, int CountLessons);
    //возвращает индекс добавленной группы из GroupNames, ошибка - -1
    int AppendGroup(QString GroupName);
    bool SetLesson(int numWeek, int indexGroup, int numDay,
                   int numLesson, QString room, QString nameLesson);
    Lesson GetLesson(int numWeek, int indexGroup,
                     int numDay, int numLesson);
    int getCountGroups();
    int getDaysInWeek();
    int getCountLessons();
    int getIndex(QString group);



    void test_out();


    //struct
    struct lesson_data {
        lesson_data(int n_type_week, int n_DayOfWeek,
                    int n_NumberLesson, QString & n_Room,
                    QString &n_Group, QString &n_Lesson);
        lesson_data();
        lesson_data(const lesson_data & another);
        bool operator < (const lesson_data & another) const;
        bool operator == (lesson_data & another);
        lesson_data & operator =(const lesson_data & another);

        int type_week, DayOfWeek, NumberLesson;
        QString Room, Group, Lesson;
    };

    void FindAllLessons(QVector<lesson_data> & res, int GroupIndex, QString sLesson);

private:
    QVector<QString> GroupNames;
    //[group_index][day_of_week][номер_пары]
    arrWeekSchedule FirstWeek, SecondWeek;
    int DaysInWeek, CountLessons;
};

#endif // SCHEDULE_H
