#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include "tablemodel.h"
#include <QtXlsx>

#include <QDebug>

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = 0);

    //TAB 1
    void SetFontName(QString f_name);
    void SetFontSize(int size);
    void SetBold(bool flag);
    void SetItalics(bool flag);
    void SetUnderline(bool flag);
    //TAB 2
    void SetVAlign(Qt::Alignment id);
    void SetHAlign(Qt::Alignment id);
    void SetBorderLeft(bool flag);
    void SetBorderTop(bool flag);
    void SetBorderRight(bool flag);
    void SetBorderBottom(bool flag);
    void SetFontCol(QColor col);
    void SetBackgroundCol(QColor col);

signals:

public slots:

};

#endif // TABLEVIEW_H
