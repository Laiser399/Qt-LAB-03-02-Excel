#include "tablemodel.h"



//-----------------------------------------|
//                                         |
//               CellDelegate              |
//                                         |
//-----------------------------------------|
#define W_BORDER 1
void CellDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);

    CellInfo * info = static_cast<CellInfo*>(index.internalPointer());
    painter->setBrush(QBrush(QColor(0, 0, 0)));
    if (!info->format.isValid())
        return;
    //option.state & QStyle::State_Active

    QRect rect = option.rect;


    if ((index.row() == 0) && (index.column() == 0)) {
//        qDebug() << info->format.leftBorderStyle();
//        qDebug() << info->format.topBorderStyle();
//        qDebug() << info->format.rightBorderStyle();
//        qDebug() << info->format.bottomBorderStyle();
//        qDebug() << "";
    }
    if (info->format.leftBorderStyle() & QXlsx::Format::BorderThin) {
        painter->drawRect(rect.x(), rect.y(), W_BORDER - 1, rect.height());
    }
    if (info->format.topBorderStyle() & QXlsx::Format::BorderThin) {
        painter->drawRect(rect.x(), rect.y(), rect.width(), W_BORDER - 1);
    }
    if (info->format.rightBorderStyle() & QXlsx::Format::BorderThin) {
        painter->drawRect(rect.x() + rect.width() - W_BORDER, rect.y(), W_BORDER, rect.height());
    }
    if (info->format.bottomBorderStyle() & QXlsx::Format::BorderThin) {
        painter->drawRect(rect.x(), rect.y() + rect.height() - W_BORDER, rect.width(), W_BORDER);
    }

}

//-----------------------------------------|
//                                         |
//            GroupScheduleModel           |
//                                         |
//-----------------------------------------|
TableModel::TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    //SetCell(4, 4, "");
    SetRowCount(5);
    SetColCount(5);
}

TableModel::~TableModel() {
    for (int row = 0; row < table.size(); row++) {
        for (int col = 0; col < table[row].size(); col++) {
            if (table[row][col])
                delete table[row][col];
        }
    }
}

// 0+ 0+
bool TableModel::SetCell(int row, int col, QString data) {
    if ((row < 0) || (col < 0))
        return false;

    if (row >= table.size()) {
        emit beginInsertRows(QModelIndex(), table.size(), row);
        int prev_row_count = table.size();
        int prev_col_count = table.size() == 0 ? 0 : table[0].size();
        //ресайз кол-ва строк
        table.resize(row + 1);
        for (int irow = prev_row_count; irow < table.size(); irow++) {
            //ресайз самих строк в конце
            table[irow].resize(prev_col_count);
            for (int icol = 0; icol < prev_col_count; icol++) {
                if (!table[irow][icol])
                    table[irow][icol] = new CellInfo();
            }
        }
        emit endInsertRows();
    }

    if (col >= table[0].size()) {
        emit beginInsertColumns(QModelIndex(), table[0].size(), col);
        for (int irow = 0; irow < table.size(); irow++) {
            int prev_col_count = table[irow].size();
            table[irow].resize(col + 1);
            for (int icol = prev_col_count; icol < table[irow].size(); icol++) {
                if (!table[irow][icol])
                    table[irow][icol] = new CellInfo();
            }
        }
        emit endInsertColumns();
    }

    Q_ASSERT(table[row][col]);
    //изменение данных
    table[row][col]->data = data;

    QModelIndex indexChange = createIndex(row, col, table[row][col]);
    emit dataChanged(indexChange, indexChange);
    return true;
}

bool TableModel::SetExistingCell(int row, int col, QString data) {
    if ((row < 0) || (col < 0) || (row >= table.size()) || (col >= table[0].size()))
        return false;

    table[row][col]->data = data;
    QModelIndex index = createIndex(row, col, table[row][col]);
    emit dataChanged(index, index);
    return true;
}

bool TableModel::SetExistingCell(int row, int col, QString data, QXlsx::Format format) {
    if ((row < 0) || (col < 0) || (row >= table.size()) || (col >= table[0].size()))
        return false;

    table[row][col]->data = data;
    table[row][col]->format = format;
    QModelIndex index = createIndex(row, col, table[row][col]);
    emit dataChanged(index, index);
    return true;
}

bool TableModel::SetExistingCellFormat(int row, int col, QXlsx::Format format) {
    if ((row < 0) || (col < 0) || (row >= table.size()) || (col >= table[0].size()))
        return false;

    table[row][col]->format = format;
    QModelIndex index = createIndex(row, col, table[row][col]);
    emit dataChanged(index, index);

    return true;
}

bool TableModel::SetRowCount(int value) {
    if (value <= 0)
        return false;

    if (value < table.size()) {
        emit beginRemoveRows(QModelIndex(), value, table.size() - 1);
        for (int irow = value; irow < table.size(); irow++) {
            for (int icol = 0; icol < table[0].size(); icol++) {
                delete table[irow][icol];
            }
        }
        table.resize(value);
        emit endRemoveRows();
    }
    else if (value > table.size()) {
        emit beginInsertRows(QModelIndex(), table.size(), value - 1);
        int prev_row_count = table.size();
        table.resize(value);
        for (int irow = prev_row_count; irow < table.size(); irow++) {
            table[irow].resize(table[0].size());
            for (int icol = 0; icol < table[0].size(); icol++) {
                table[irow][icol] = new CellInfo;
            }
        }
        emit endInsertRows();
    }

    return true;
}

bool TableModel::SetColCount(int value) {
    if ((table.size() <= 0) || (value <= 0))
        return false;


    if (value < table[0].size()) {
        emit beginRemoveColumns(QModelIndex(), value, table[0].size() - 1);
        for (int irow = 0; irow < table.size(); irow++) {
            for (int icol = value; icol < table[irow].size(); icol++) {
                delete table[irow][icol];
            }
            table[irow].resize(value);
        }
        emit endRemoveColumns();
    }
    else if (value > table[0].size()) {
        emit beginInsertColumns(QModelIndex(), table[0].size(), value - 1);
        int prev_col_count = table[0].size();
        for (int irow = 0; irow < table.size(); irow++) {
            table[irow].resize(value);
            for (int icol = prev_col_count; icol < value; icol++) {
                table[irow][icol] = new CellInfo;
            }
        }
        emit endInsertColumns();
    }

    return true;

}

bool TableModel::SaveToFile(QString &filename) {
    QXlsx::Document doc;
    for (int irow = 0; irow < table.size(); irow++) {
        for (int icol = 0; icol < table[irow].size(); icol++) {
            if (!table[irow][icol]->data.isEmpty()) {
                doc.write(irow + 1, icol + 1, table[irow][icol]->data, table[irow][icol]->format);
            }
        }
    }
    return doc.saveAs(filename);
}


//------------------------------|
//                              |
// QAbstractItemModel interface |
//                              |
//------------------------------|
QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    if ((row < 0) || (column < 0))
        return QModelIndex();

    if ((row >= table.size()) || (column >= table[row].size())
            || (row < 0) || (column < 0))
        return QModelIndex();


    return createIndex(row, column, table[row][column]);

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return table.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() || (table.size() <= 0))
        return 0;
    return table[0].size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    CellInfo *cellInfo = static_cast<CellInfo*>(index.internalPointer());

    //cellInfo->format.bor

    int res = 0;
    switch (role) {
    case Qt::DisplayRole: case Qt::EditRole:
        return cellInfo->data;
    case Qt::TextAlignmentRole:
        switch (cellInfo->format.verticalAlignment()) {
        case QXlsx::Format::AlignVCenter:
            res |= Qt::AlignVCenter;
            break;
        case QXlsx::Format::AlignTop:
            res |= Qt::AlignTop;
            break;
        case QXlsx::Format::AlignBottom:
            res |= Qt::AlignBottom;
            break;
        }

        switch (cellInfo->format.horizontalAlignment()) {
        case QXlsx::Format::AlignHCenter:
            return res | Qt::AlignHCenter;
        case QXlsx::Format::AlignLeft:
            return res | Qt::AlignLeft;
        case QXlsx::Format::AlignRight:
            return res | Qt::AlignRight;
        default:
            return res;
        }
    case Qt::FontRole:
        return cellInfo->format.font();
    case Qt::BackgroundRole:
        if (cellInfo->format.patternBackgroundColor().isValid()) {
            return QBrush(cellInfo->format.patternBackgroundColor());
        }
        else {
            return QBrush(QColor(Qt::white));
        }
    case Qt::ForegroundRole:
        return cellInfo->format.fontColor();
    case Qt::SizeHintRole:
        //return QSize(200, 200);
    default:
        return QVariant();
    }
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() &&
            ((role == Qt::EditRole) || (role == Qt::DisplayRole)))
    {
        CellInfo * cellInfo = static_cast<CellInfo*>(index.internalPointer());

        cellInfo->data = value.toString();
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section < 0)
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return QVariant(section + 1);
    case Qt::SizeHintRole:
        return QSize(40, 30);
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    default:
        return QVariant();
    }
    //return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModel::hasChildren(const QModelIndex &parent) const
{
    return false;
}







