#include "schedule.h"

//-----------------|
//   common func   |
//-----------------|
QString & RoomToNormal(QString & str) {
    str = str.simplified();
    return str;
}

QString & LessonToNormal(QString & str) {
    str = str.simplified();
    if (str.length() > 0) {
        str[0] = str[0].toUpper();
        for (int i = 1; i < str.length(); i++) {
            str[i] = str[i].toLower();
        }
    }
    return str;
}

QString & GroupToNormal(QString & str) {
    str = str.simplified().toUpper();
    return str;
}

//------------------------|
//   struct lesson_data   |
//------------------------|
Schedule::lesson_data::lesson_data(int n_type_week, int n_DayOfWeek,
            int n_NumberLesson, QString & n_Room,
            QString &n_Group, QString &n_Lesson)
{
    type_week = n_type_week;
    DayOfWeek = n_DayOfWeek;
    NumberLesson = n_NumberLesson;
    Room = n_Room;
    Group = n_Group;
    Lesson = n_Lesson;
}

Schedule::lesson_data::lesson_data(const Schedule::lesson_data & another) {
    this->type_week = another.type_week;
    this->DayOfWeek = another.DayOfWeek;
    this->NumberLesson = another.NumberLesson;
    this->Room = another.Room;
    this->Group = another.Group;
    this->Lesson = another.Lesson;
}

Schedule::lesson_data::lesson_data() :
    type_week(), DayOfWeek(0), NumberLesson(0) {}

bool Schedule::lesson_data::operator < (const Schedule::lesson_data & another) const {
    if (type_week == another.type_week) {
        if (DayOfWeek == another.DayOfWeek) {
            return NumberLesson < another.NumberLesson;
        }
        else return DayOfWeek < another.DayOfWeek;
    }
    else
        return type_week < another.type_week;
}

bool Schedule::lesson_data::operator == (Schedule::lesson_data & another) {
    return (type_week == another.type_week)
            && (DayOfWeek == another.DayOfWeek)
            && (NumberLesson == another.NumberLesson);
}

Schedule::lesson_data & Schedule::lesson_data::operator = (const Schedule::lesson_data & another) {
    this->type_week = another.type_week;
    this->DayOfWeek = another.DayOfWeek;
    this->NumberLesson = another.NumberLesson;
    this->Room = another.Room;
    this->Group = another.Group;
    this->Lesson = another.Lesson;
}


//--------------|
//   schedule   |
//--------------|
Schedule::Schedule() : DaysInWeek(0), CountLessons(0)
{
}

bool Schedule::SetDimension(int DaysInWeek, int CountLessons) {
    if ((DaysInWeek < 1) || (DaysInWeek > 7) ||
            (CountLessons <= 0)) {
        return false;
    }
    this->DaysInWeek = DaysInWeek;
    this->CountLessons = CountLessons;
    return true;
}

int Schedule::AppendGroup(QString GroupName) {
    GroupToNormal(GroupName);
    for (int i = 0; i < GroupNames.size(); i++) {
        if (GroupNames[i] == GroupName)
            return -1;
    }

    GroupNames.push_back(GroupName);
    FirstWeek.push_back(WeekSchedule(DaysInWeek, DayOfWeek(CountLessons, Lesson())));
    SecondWeek.push_back(WeekSchedule(DaysInWeek, DayOfWeek(CountLessons, Lesson())));
    return GroupNames.size() - 1;
    //TODO add WeekSchedule
}

//все переменные с 0
bool Schedule::SetLesson(int numWeek, int indexGroup, int numDay,
               int numLesson, QString room, QString nameLesson)
{
    if ((numWeek < 0) || (numWeek > 1) || (indexGroup < 0)
            || (indexGroup >= GroupNames.size())
            || (numDay < 0) || (numDay >= DaysInWeek)
            || (numLesson < 0) || (numLesson >= CountLessons))
        return false;

    if (numWeek == 0) {
        FirstWeek[indexGroup][numDay][numLesson]
                = Lesson(RoomToNormal(room), LessonToNormal(nameLesson));
    }
    else {
        SecondWeek[indexGroup][numDay][numLesson]
                = Lesson(RoomToNormal(room), LessonToNormal(nameLesson));
    }
    return true;
}

Schedule::Lesson Schedule::GetLesson(int numWeek, int indexGroup,
                 int numDay, int numLesson)
{
    if ((numWeek < 0) || (numWeek > 1) || (indexGroup < 0)
            || (indexGroup >= GroupNames.size())
            || (numDay < 0) || (numDay >= DaysInWeek)
            || (numLesson < 0) || (numLesson >= CountLessons))
        throw QString("Schedule: GetLesson: Out of range!");

    if (numWeek == 0) {
        return FirstWeek[indexGroup][numDay][numLesson];
    }
    else {
        return SecondWeek[indexGroup][numDay][numLesson];
    }
}

int Schedule::getCountGroups() {
    return GroupNames.size();
}

int Schedule::getDaysInWeek() {
    return DaysInWeek;
}

int Schedule::getCountLessons() {
    return CountLessons;
}

int Schedule::getIndex(QString group) {
    GroupToNormal(group);
    for (int i = 0; i < GroupNames.size(); i++) {
        if (GroupNames[i] == group) {
            return i;
        }
    }
    return -1;
}

//по указ группе, занятию вернуть список соотв времен
//return тип недели, день недели, номер пары, аудиторию
void Schedule::FindAllLessons(QVector<lesson_data> & res,
        int GroupIndex, QString sLesson)
{
    Q_ASSERT(GroupIndex >= 0);
    Q_ASSERT(GroupIndex < GroupNames.size());

    //по первой неделе
    for (int day = 0; day < DaysInWeek; day++) {
        for (int lesson = 0; lesson < CountLessons; lesson++) {
            if (FirstWeek[GroupIndex][day][lesson].second == sLesson) {
                res.append(Schedule::lesson_data(0, day, lesson,
                     FirstWeek[GroupIndex][day][lesson].first,
                     GroupNames[GroupIndex], sLesson));
            }
        }
    }
    //по второй неделе
    for (int day = 0; day < DaysInWeek; day++) {
        for (int lesson = 0; lesson < CountLessons; lesson++) {
            if (SecondWeek[GroupIndex][day][lesson].second == sLesson) {
                res.append(Schedule::lesson_data(1, day, lesson,
                    SecondWeek[GroupIndex][day][lesson].first,
                    GroupNames[GroupIndex], sLesson));
            }
        }
    }
}


void Schedule::test_out() {
    for (int iGr = 0; iGr < GroupNames.size(); iGr++) {
        qDebug() << GroupNames[iGr];
        qDebug() << "   FIRST WEEK";
        for (int day = 0; day < DaysInWeek; day++) {
            qDebug() << QString("      %1 day").arg(day + 1);
            for (int lesson = 0; lesson < CountLessons; lesson++) {
                if ((FirstWeek[iGr][day][lesson].first.length() > 0)
                        || (FirstWeek[iGr][day][lesson].second.length() > 0))
                {
                    qDebug() << QString("         lesson #%1: %2, %3").arg(
                        lesson + 1).arg(
                        FirstWeek[iGr][day][lesson].first).arg(
                        FirstWeek[iGr][day][lesson].second);
                }
            }
        }


        qDebug() << "   SECOND WEEK";
        for (int day = 0; day < DaysInWeek; day++) {
            qDebug() << QString("      %1 day").arg(day + 1);
            for (int lesson = 0; lesson < CountLessons; lesson++) {
                if ((SecondWeek[iGr][day][lesson].first.length() > 0)
                        || (SecondWeek[iGr][day][lesson].second.length() > 0))
                {
                    qDebug() << QString("         lesson #%1: %2, %3").arg(
                        lesson + 1).arg(
                        SecondWeek[iGr][day][lesson].first).arg(
                        SecondWeek[iGr][day][lesson].second);
                }
            }
        }
    }
}









