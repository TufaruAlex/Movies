//
// Created by tufar on 03.06.2022.
//

#include "QAbstractTableModel"
#include "Service.h"
#include "Watchlist.h"

#ifndef A11_MYLISTTABLE_H
#define A11_MYLISTTABLE_H
class MyTableModel : public QAbstractTableModel{
private:
    Service &service;
public:
    explicit MyTableModel(Service &service, QObject *parent = nullptr) : service(service){};

    void add_to_watchlist(const std::string& title);

    bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;

    bool removeRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
#endif //A11_MYLISTTABLE_H
