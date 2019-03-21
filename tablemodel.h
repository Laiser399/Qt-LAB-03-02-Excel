#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QString>
#include <QtXlsx>
#include <QStyledItemDelegate>

#include <QDebug>

struct CellInfo {
    QString data;
    QXlsx::Format format;

    CellInfo(const QString & n_data, const QXlsx::Format & n_format = QXlsx::Format()) :
        data(n_data), format(n_format)
    {
    }
};

class CellDelegate : public QStyledItemDelegate
{
public:
    CellDelegate(QObject * pobj = 0) : QStyledItemDelegate(pobj){ }
    // QAbstractItemDelegate interface
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};



class TableModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QVector<QVector<CellInfo*> > table;
public:
    explicit TableModel(QObject *parent = 0);
    ~TableModel();
    // 0+ 0+
    bool SetCell(int row, int col, QString data);
    bool SetExistingCell(int row, int col, QString data);
    bool SetExistingCell(int row, int col, QString data, QXlsx::Format format);
    bool SetExistingCellFormat(int row, int col, QXlsx::Format format);
    bool SetRowCount(int value);
    bool SetColCount(int value);
    bool SaveToFile(QString &filename);

    // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool hasChildren(const QModelIndex &parent) const;

};

#endif // TABLEMODEL_H
