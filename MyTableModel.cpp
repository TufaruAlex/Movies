//
// Created by tufar on 03.06.2022.
//

#include "MyTableModel.h"

void MyTableModel::add_to_watchlist(const std::string &title) {
    for (auto &movie: service.get_movie_list()) {
        if (movie.get_title() == title) {
            service.add_movie_to_watch_list(movie);
            insertRows((int) service.get_watch_list().size(), 1);
            return;
        }
    }
}

bool MyTableModel::insertRows(int position, int rows, const QModelIndex &index) {
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    endInsertRows();
    return true;
}

bool MyTableModel::removeRows(int position, int rows, const QModelIndex &index) {
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    endRemoveRows();
    return true;
}

int MyTableModel::rowCount(const QModelIndex &parent) const {
    return (int) service.get_watch_list().size();
}

int MyTableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();

    Movie movie = service.get_watch_list()[row];
    std::string likes = std::to_string(movie.get_likes());
    std::string year = std::to_string(movie.get_release_year());

    if (role == Qt::DisplayRole) {
        switch (column) {
            case 0:
                return QString::fromStdString(movie.get_title());
            case 1:
                return QString::fromStdString(movie.get_genre());
            case 2:
                return QString::fromStdString(year);
            case 3:
                return QString::fromStdString(likes);
            case 4:
                return QString::fromStdString(movie.get_trailer());
            default:
                break;
        }
    }

    return QVariant();
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Title");
                case 1:
                    return QString("Genre");
                case 2:
                    return QString("Year");
                case 3:
                    return QString("Number of Likes");
                case 4:
                    return QString("Trailer");
                default:
                    break;
            }
        }
    }
    return QVariant();
}
