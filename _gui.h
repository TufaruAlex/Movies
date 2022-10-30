#include "qwidget.h"
#include "qboxlayout.h"
#include "qformlayout.h"
#include "qpushbutton.h"
#include "qlabel.h"
#include "qtabwidget.h"
#include "qlineedit.h"
#include "qlistwidget.h"
#include "Service.h"
#include "Movie.h"

class Gui:public QWidget{
private:
    QOBJECT_H
    std::vector<Movie> vector;

    QListWidget* movieList;
    QListWidget* filteredObjects;
    QLineEdit* filterBox;
    QPushButton* filter;

    QListWidget* watchlist;
    QListWidget* current_movie;

public:
    Gui(std::vector<Movie> &other,QWidget *parent = 0);

    void initGui();
    void populateGui();
    void connectRelations();
    void filterGui();
};

