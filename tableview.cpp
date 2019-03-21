#include "tableview.h"


TableView::TableView(QWidget *parent) :
    QTableView(parent)
{

}




void TableView::SetFontName(QString f_name) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        info->format.setFontName(f_name);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }

    //updateEditorData();
}

void TableView::SetFontSize(int size) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        info->format.setFontSize(size);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }

}

void TableView::SetBold(bool flag) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        info->format.setFontBold(flag);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }
}

void TableView::SetItalics(bool flag) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        info->format.setFontItalic(flag);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }
}

void TableView::SetUnderline(bool flag) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        if (flag)
            info->format.setFontUnderline(QXlsx::Format::FontUnderlineSingle);
        else
            info->format.setFontUnderline(QXlsx::Format::FontUnderlineNone);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }
}

void TableView::SetVAlign(Qt::Alignment id) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        switch (id) {
        case Qt::AlignTop:
            info->format.setVerticalAlignment(QXlsx::Format::AlignTop);
            break;
        case Qt::AlignVCenter:
            info->format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
            break;
        case Qt::AlignBottom:
            info->format.setVerticalAlignment(QXlsx::Format::AlignBottom);
            break;
        }
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }
}

void TableView::SetHAlign(Qt::Alignment id) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        switch (id) {
        case Qt::AlignLeft:
            info->format.setHorizontalAlignment(QXlsx::Format::AlignLeft);
            break;
        case Qt::AlignHCenter:
            info->format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            break;
        case Qt::AlignRight:
            info->format.setHorizontalAlignment(QXlsx::Format::AlignRight);
            break;
        }
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }
}

//QXlsx::Format::BorderThin
void TableView::SetBorderLeft(bool flag) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        if (flag)
            info->format.setLeftBorderStyle(QXlsx::Format::BorderThin);
        else
            info->format.setLeftBorderStyle(QXlsx::Format::BorderNone);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }
}

void TableView::SetBorderTop(bool flag) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        if (flag)
            info->format.setTopBorderStyle(QXlsx::Format::BorderThin);
        else
            info->format.setTopBorderStyle(QXlsx::Format::BorderNone);
        emit dataChanged(list_indexes[i], list_indexes[i]);

        //qDebug() << info->format.topBorderStyle();
    }
}

void TableView::SetBorderRight(bool flag) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        if (flag)
            info->format.setRightBorderStyle(QXlsx::Format::BorderThin);
        else
            info->format.setRightBorderStyle(QXlsx::Format::BorderNone);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }

}

void TableView::SetBorderBottom(bool flag) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        if (flag)
            info->format.setBottomBorderStyle(QXlsx::Format::BorderThin);
        else
            info->format.setBottomBorderStyle(QXlsx::Format::BorderNone);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }
}

void TableView::SetFontCol(QColor col) {
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        info->format.setFontColor(col);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }
}

void TableView::SetBackgroundCol(QColor col){
    QModelIndexList list_indexes = QTableView::selectedIndexes();
    for (int i = 0; i < list_indexes.size(); i++) {
        CellInfo * info = static_cast<CellInfo*>(list_indexes[i].internalPointer());
        info->format.setPatternBackgroundColor(col);
        emit dataChanged(list_indexes[i], list_indexes[i]);
    }
}
