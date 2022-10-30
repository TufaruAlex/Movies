//
// Created by tufar on 29.05.2022.
//

#include "qwidget.h"
#include "qboxlayout.h"
#include "qformlayout.h"
#include "qpushbutton.h"
#include "qlabel.h"
#include "qtabwidget.h"
#include "qlineedit.h"
#include "qlistwidget.h"
#include "QErrorMessage"
#include "QLinearGradient"
#include "QShortcut"
#include "Service.h"
#include "Movie.h"
#include "MyTableModel.h"
#include "QTableView"

class Gui : public QWidget {
private:
    QOBJECT_H
    Service service;
    std::vector<Movie> movies;
    std::vector<Movie> filtered_movies;
    QListWidget *movie_list_widget;
    QListWidget *filtered_movies_widget;
    QLineEdit *filter_line;
    QPushButton *filter_button;
    QPushButton *add_button;
    QPushButton *remove_button;
    QPushButton *update_button;
    QListWidget *watchlist_widget;
    QListWidget *current_movie_widget;
    QLineEdit *title_line;
    QLineEdit *new_title_line;
    QLineEdit *genre_line;
    QLineEdit *release_year_line;
    QLineEdit *likes_line;
    QLineEdit *trailer_line;
    QPushButton *filter_user_button;
    QPushButton *next_movie_button;
    QPushButton *add_to_watchlist_button;
    QPushButton *stop_button;
    QLineEdit *file_type_line;
    QLineEdit *genre_filter_line;
    QPushButton *create_file_button;
    QPushButton *remove_watchlist_button;
    QPushButton *open_watchlist_button;
    QLineEdit *title_user_line;
    QLineEdit *real_time_filter_line;
    QPushButton *undo_button;
    QPushButton *redo_button;
    QShortcut *undo_key;
    QShortcut *redo_key;
    MyTableModel *watchlist_window;
    QPushButton *watchlist_window_button;
    int index;

public:
    explicit Gui(std::vector<Movie> &other, QWidget *parent = nullptr);

    void init_gui();

    void populate_gui();

    void connect_relations();

    void filter_gui();

    void add_gui();

    void remove_gui();

    void update_gui();

    void create_watchlist();

    void filter_user();

    void show_movie();

    void add_to_watchlist();

    void remove_from_watchlist();

    void open_watchlist_file();

    void stop_movie_iteration();

    void real_time_filter();

    void undo();

    void redo();

    void open_watchlist_window();
};

