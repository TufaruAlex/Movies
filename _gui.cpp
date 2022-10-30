#include "_gui.h"

Gui::Gui(std::vector<Movie> &other, QWidget *parent): vector{other}, QWidget{parent}{
    this->initGui();
    this->populateGui();
    this->connectRelations();
}

void Gui::initGui() {

    ///main

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QTabWidget* tabs = new QTabWidget();

    ///admin

    QWidget* admin = new QWidget();

    QHBoxLayout* adminLayout = new QHBoxLayout(admin);

        ///main functions layout

    QVBoxLayout* adminFunctionsLayout = new QVBoxLayout();

            ///movie list layout

    QFormLayout* movieListLayout = new QFormLayout();

    QLabel* listLabel = new QLabel("Movies");
    movieList = new QListWidget();
    movieList->setSelectionMode(QAbstractItemView::SingleSelection);
    listLabel->setBuddy(movieList);

    movieListLayout->addWidget(listLabel);
    movieListLayout->addWidget(movieList);

    adminFunctionsLayout->addLayout(movieListLayout);

            ///attributes layout

    QGridLayout* editsLayout = new QGridLayout();

    QLabel* title = new QLabel("Title: ");
    QLabel* genre = new QLabel("Genre: ");
    QLabel* release_year = new QLabel("Release year: ");
    QLabel* likes = new QLabel("Likes: ");
    QLabel* trailer = new QLabel("Trailer: ");

    QLineEdit* title_line = new QLineEdit();
    QLineEdit* genre_line = new QLineEdit();
    QLineEdit* release_year_line = new QLineEdit();
    QLineEdit* likes_line = new QLineEdit();
    QLineEdit* trailer_line = new QLineEdit();

    title->setBuddy(title_line);
    genre->setBuddy(genre_line);
    release_year->setBuddy(release_year_line);
    likes->setBuddy(likes_line);
    trailer->setBuddy(trailer_line);

    editsLayout->addWidget(title, 0, 0);
    editsLayout->addWidget(title_line, 0, 1, 1, 2);
    editsLayout->addWidget(genre, 1, 0);
    editsLayout->addWidget(genre_line, 1, 1, 1, 2);
    editsLayout->addWidget(release_year, 2, 0);
    editsLayout->addWidget(release_year_line, 2, 1, 1, 2);
    editsLayout->addWidget(likes, 3, 0);
    editsLayout->addWidget(likes_line, 3, 1, 1, 2);
    editsLayout->addWidget(trailer,4, 0);
    editsLayout->addWidget(trailer_line, 4, 1, 1 , 2);

    adminFunctionsLayout->addLayout(editsLayout);

            ///buttons layout

    QGridLayout* buttonsLayout = new QGridLayout();

    QPushButton* add = new QPushButton("Add");
    QPushButton* del = new QPushButton("Delete");
    QPushButton* update = new QPushButton("Update");
    filter = new QPushButton("Filter");

    buttonsLayout->addWidget(add,0,0);
    buttonsLayout->addWidget(del,0,1);
    buttonsLayout->addWidget(update,0,2);
    buttonsLayout->addWidget(filter,1,1);

    adminFunctionsLayout->addLayout(buttonsLayout);

            ///activity layout

    QFormLayout* activityLayout = new QFormLayout();

    QLabel* filteredBoxLabel = new QLabel("Objects filtered: ");
    filterBox = new QLineEdit();
    filteredObjects = new QListWidget();
    filteredBoxLabel->setBuddy(filteredObjects);
    QLabel* filterLabel = new QLabel("Input filter (for title): ");
    filterLabel->setBuddy(filterBox);

    activityLayout->addRow(filterLabel);
    activityLayout->addRow(filterBox);
    activityLayout->addRow(filteredBoxLabel);
    activityLayout->addRow(filteredObjects);

    ///adding layout to admin

    adminLayout->addLayout(adminFunctionsLayout);
    adminLayout->addLayout(activityLayout);

    ///user

    QWidget* user =  new QWidget();

    QVBoxLayout* userLayout = new  QVBoxLayout(user);

        ///watchlist layout

    QFormLayout* watchlistLayout = new QFormLayout();

    QLabel* watchlistLabel = new QLabel("Watchlist");
    watchlist = new QListWidget();
    watchlist->setSelectionMode(QAbstractItemView::SingleSelection);
    watchlistLabel->setBuddy(watchlist);

    watchlistLayout->addWidget(watchlistLabel);
    watchlistLayout->addWidget(watchlist);

    userLayout->addLayout(watchlistLayout);

        ///current movies layout

    QGridLayout* currentMovieLayout = new QGridLayout();

    QLabel* currentMovieLabel = new QLabel("Current movie");
    current_movie = new QListWidget();
    current_movie->setAutoFillBackground(true);
    currentMovieLabel->setBuddy(currentMovieLabel);

    QPushButton* next = new QPushButton("Next");
    QPushButton* add_to_wl = new QPushButton("Add");
    QPushButton* stop = new QPushButton("Stop");

    currentMovieLayout->addWidget(currentMovieLabel,0,0);
    currentMovieLayout->addWidget(current_movie,1,0,1,3);
    currentMovieLayout->addWidget(next,2,0);
    currentMovieLayout->addWidget(add_to_wl,2,1);
    currentMovieLayout->addWidget(stop,2,2);

    userLayout->addLayout(currentMovieLayout);

        ///user functions layout

    QGridLayout* userFunctionsLayout = new QGridLayout();

    QLabel*  wl_title = new QLabel("Title: ");
    QLineEdit* wl_title_line = new QLineEdit();
    wl_title->setBuddy(wl_title_line);

    QPushButton* wl_del = new QPushButton("Delete");

    userFunctionsLayout->addWidget(wl_title, 0, 0);
    userFunctionsLayout->addWidget(wl_title_line, 0, 1, 1, 2);
    userFunctionsLayout->addWidget(wl_del,1, 0, 1, 3);

    userLayout->addLayout(userFunctionsLayout);

    ///adding tabs to main

    tabs->addTab(admin,"Admin");
    tabs->addTab(user,"User");

    mainLayout->addWidget(tabs);
}

void Gui::populateGui(){
    movieList->clear();
    for(auto o : vector){
        QString itemInList = QString::fromStdString(o.to_string());
        QListWidgetItem* item = new QListWidgetItem{itemInList};
        movieList->addItem(item);
    }
}

void Gui::connectRelations() {
    QObject::connect(filter,&QPushButton::clicked,this,&Gui::filterFunc);
}

void Gui::filterGui() {
    filteredObjects->clear();
    QString filterData = filterBox->text();
    std::string filterDataString = filterData.toStdString();
    for (auto o: vector) {
        if (o.get_title().find(filterDataString) != -1) {
            QString itemInList = QString::fromStdString(o.to_string());
            QListWidgetItem *item = new QListWidgetItem{itemInList};
            filteredObjects->addItem(item);
        }
    }
}



