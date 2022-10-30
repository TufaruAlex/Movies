//
// Created by tufar on 29.05.2022.
//

#include "gui.h"
#include "Validator.h"

Gui::Gui(std::vector<Movie> &other, QWidget *parent) : movies{other}, QWidget{parent} {
    service = Service();
    this->init_gui();
    this->populate_gui();
    this->connect_relations();
}

void Gui::init_gui() {
    auto *main_layout = new QHBoxLayout(this);
    auto *tabs = new QTabWidget();

    auto *admin = new QWidget();
    auto *admin_layout = new QHBoxLayout(admin);

    auto *admin_functions_layout = new QVBoxLayout();

    auto *movie_list_layout = new QGridLayout();
    auto *real_time_filter_label = new QLabel("Real-time filter:");
    real_time_filter_line = new QLineEdit();
    real_time_filter_label->setBuddy(real_time_filter_line);

    auto *list_label = new QLabel("Movies");
    movie_list_widget = new QListWidget();
    movie_list_widget->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0 x2: 0, y2: 1, stop: 0 #00CD00 , stop: 0.2 #0AC92B stop: 1 #00FF33 );");
    movie_list_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    list_label->setBuddy(movie_list_widget);

    movie_list_layout->addWidget(real_time_filter_label, 0, 0);
    movie_list_layout->addWidget(real_time_filter_line, 0, 1);
    movie_list_layout->addWidget(list_label, 1, 0);
    movie_list_layout->addWidget(movie_list_widget, 2, 0, 1, 3);

    admin_functions_layout->addLayout(movie_list_layout);

    auto *edits_layout = new QGridLayout();

    auto *title = new QLabel("Title:");
    auto *new_title = new QLabel("New title:");
    auto *genre = new QLabel("Genre:");
    auto *release_year = new QLabel("Release year:");
    auto *likes = new QLabel("Likes:");
    auto *trailer = new QLabel("Trailer:");

    title_line = new QLineEdit();
    new_title_line = new QLineEdit();
    genre_line = new QLineEdit();
    release_year_line = new QLineEdit();
    likes_line = new QLineEdit();
    trailer_line = new QLineEdit();

    title->setBuddy(title_line);
    new_title->setBuddy(new_title_line);
    genre->setBuddy(genre_line);
    release_year->setBuddy(release_year_line);
    likes->setBuddy(likes_line);
    trailer->setBuddy(trailer_line);

    edits_layout->addWidget(title, 0, 0);
    edits_layout->addWidget(title_line, 0, 1, 1, 2);
    edits_layout->addWidget(new_title, 1, 0);
    edits_layout->addWidget(new_title_line, 1, 1, 1, 2);
    edits_layout->addWidget(genre, 2, 0);
    edits_layout->addWidget(genre_line, 2, 1, 1, 2);
    edits_layout->addWidget(release_year, 3, 0);
    edits_layout->addWidget(release_year_line, 3, 1, 1, 2);
    edits_layout->addWidget(likes, 4, 0);
    edits_layout->addWidget(likes_line, 4, 1, 1, 2);
    edits_layout->addWidget(trailer, 5, 0);
    edits_layout->addWidget(trailer_line, 5, 1, 1, 2);

    admin_functions_layout->addLayout(edits_layout);

    auto *buttons_layout = new QGridLayout();

    add_button = new QPushButton("Add");
    remove_button = new QPushButton("Delete");
    update_button = new QPushButton("Update");
    filter_button = new QPushButton("Filter");
    undo_button = new QPushButton("Undo");
    redo_button = new QPushButton("Redo");
    undo_key = new QShortcut(QKeySequence(tr("Ctrl+z")), this);
    redo_key = new QShortcut(QKeySequence(tr("Ctrl+y")), this);

    buttons_layout->addWidget(add_button, 0, 0);
    buttons_layout->addWidget(remove_button, 0, 1);
    buttons_layout->addWidget(update_button, 0, 2);
    buttons_layout->addWidget(undo_button, 1, 0);
    buttons_layout->addWidget(filter_button, 1, 1);
    buttons_layout->addWidget(redo_button, 1, 2);

    admin_functions_layout->addLayout(buttons_layout);

    auto *activity_layout = new QFormLayout();
    auto *filtered_box_label = new QLabel("Filtered movies:");
    filter_line = new QLineEdit();
    filtered_movies_widget = new QListWidget();
    filtered_box_label->setBuddy(filtered_movies_widget);
    auto *filter_label = new QLabel("Search:");
    filter_label->setBuddy(filter_line);

    activity_layout->addRow(filter_label);
    activity_layout->addRow(filter_line);
    activity_layout->addRow(filtered_box_label);
    activity_layout->addRow(filtered_movies_widget);

    admin_layout->addLayout(admin_functions_layout);
    admin_layout->addLayout(activity_layout);

    auto *user = new QWidget();
    auto *user_layout = new QVBoxLayout(user);

    auto *watchlist_setup_layout = new QGridLayout();
    auto *file_type_label = new QLabel("File type:");
    file_type_line = new QLineEdit();
    file_type_label->setBuddy(file_type_line);

    auto *genre_filter_label = new QLabel("Genre:");
    genre_filter_line = new QLineEdit();
    genre_filter_label->setBuddy(genre_filter_line);

    watchlist_setup_layout->addWidget(file_type_label, 0, 0);
    watchlist_setup_layout->addWidget(file_type_line, 0, 1, 1, 4);
    watchlist_setup_layout->addWidget(genre_filter_label, 1, 0);
    watchlist_setup_layout->addWidget(genre_filter_line, 1, 1, 1, 4);

    user_layout->addLayout(watchlist_setup_layout);

    auto *watchlist_layout = new QFormLayout();
    auto *watchlist_label = new QLabel("Watchlist");
    watchlist_widget = new QListWidget();
    watchlist_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    watchlist_label->setBuddy(watchlist_widget);

    watchlist_layout->addWidget(watchlist_label);
    watchlist_layout->addWidget(watchlist_widget);

    user_layout->addLayout(watchlist_layout);

    auto *user_functions_layout = new QGridLayout();
    auto *current_movie_label = new QLabel("Current movie");
    current_movie_widget = new QListWidget();
    current_movie_widget->setAutoFillBackground(true);
    current_movie_label->setBuddy(current_movie_label);

    filter_user_button = new QPushButton("Filter");
    next_movie_button = new QPushButton("Next");
    stop_button = new QPushButton("Stop");
    auto *wl_title = new QLabel("Title:");
    title_user_line = new QLineEdit();
    wl_title->setBuddy(title_user_line);
    add_to_watchlist_button = new QPushButton("Add");
    remove_watchlist_button = new QPushButton("Delete");
    create_file_button = new QPushButton("Create file");
    open_watchlist_button = new QPushButton("Open watchlist");
    watchlist_window_button = new QPushButton("Open watchlist window");

    user_functions_layout->addWidget(current_movie_label, 0, 0);
    user_functions_layout->addWidget(current_movie_widget, 1, 0, 1, 5);
    user_functions_layout->addWidget(filter_user_button, 2, 0);
    user_functions_layout->addWidget(next_movie_button, 2, 1);
    user_functions_layout->addWidget(stop_button, 2, 2);
    user_functions_layout->addWidget(wl_title, 4, 0);
    user_functions_layout->addWidget(title_user_line, 4, 1, 1, 4);
    user_functions_layout->addWidget(remove_watchlist_button, 2, 4);
    user_functions_layout->addWidget(create_file_button, 3, 1);
    user_functions_layout->addWidget(watchlist_window_button, 3, 2);
    user_functions_layout->addWidget(open_watchlist_button, 3, 3);
    user_functions_layout->addWidget(add_to_watchlist_button, 2, 3);

    user_layout->addLayout(user_functions_layout);

    tabs->addTab(admin, "Admin");
    tabs->addTab(user, "User");

    main_layout->addWidget(tabs);
}

void Gui::populate_gui() {
    movie_list_widget->clear();
    for (const auto &movie: service.get_movie_list()) {
        QString movie_qstr = QString::fromStdString(movie.to_string());
        auto *item = new QListWidgetItem(movie_qstr);
        movie_list_widget->addItem(item);
    }
}

void Gui::connect_relations() {
    QObject::connect(filter_button, &QPushButton::clicked, this, &Gui::filter_gui);
    QObject::connect(add_button, &QPushButton::clicked, this, &Gui::add_gui);
    QObject::connect(remove_button, &QPushButton::clicked, this, &Gui::remove_gui);
    QObject::connect(update_button, &QPushButton::clicked, this, &Gui::update_gui);
    QObject::connect(create_file_button, &QPushButton::clicked, this, &Gui::create_watchlist);
    QObject::connect(filter_user_button, &QPushButton::clicked, this, &Gui::filter_user);
    QObject::connect(next_movie_button, &QPushButton::clicked, this, &Gui::show_movie);
    QObject::connect(add_to_watchlist_button, &QPushButton::clicked, this, &Gui::add_to_watchlist);
    QObject::connect(remove_watchlist_button, &QPushButton::clicked, this, &Gui::remove_from_watchlist);
    QObject::connect(open_watchlist_button, &QPushButton::clicked, this, &Gui::open_watchlist_file);
    QObject::connect(stop_button, &QPushButton::clicked, this, &Gui::stop_movie_iteration);
    QObject::connect(real_time_filter_line, &QLineEdit::textChanged, this, &Gui::real_time_filter);
    QObject::connect(undo_button, &QPushButton::clicked, this, &Gui::undo);
    QObject::connect(redo_button, &QPushButton::clicked, this, &Gui::redo);
    QObject::connect(undo_key, &QShortcut::activated, this, &Gui::undo);
    QObject::connect(redo_key, &QShortcut::activated, this, &Gui::redo);
    QObject::connect(watchlist_window_button, &QPushButton::clicked, this, &Gui::open_watchlist_window);
}

void Gui::filter_gui() {
    filtered_movies_widget->clear();
    QString filter_data = filter_line->text();
    std::string filter_data_str = filter_data.toStdString();
    for (const auto &movie: movies) {
        if (movie.get_title().find(filter_data_str) != -1) {
            QString movie_qstr = QString::fromStdString(movie.to_string());
            auto *item = new QListWidgetItem(movie_qstr);
            filtered_movies_widget->addItem(item);
        }
    }
}

void Gui::add_gui() {
    QString title = title_line->text();
    std::string title_str = title.toStdString();
    QString genre = genre_line->text();
    std::string genre_str = genre.toStdString();
    QString year = release_year_line->text();
    std::string year_str = year.toStdString();
    QString likes = likes_line->text();
    std::string likes_str = likes.toStdString();
    QString trailer = trailer_line->text();
    std::string trailer_str = trailer.toStdString();
    try {
        service.add_movie(title_str, genre_str, year_str, likes_str, trailer_str);
    }
    catch (Validation_exception &ve) {
        auto *error = new QErrorMessage();
        QString error_message = "Following errors occurred: " + QString::fromStdString(ve.get_message());
        error->showMessage(error_message);
    }
    populate_gui();
}

void Gui::remove_gui() {
    QString title = title_line->text();
    std::string title_str = title.toStdString();
    try {
        service.remove_movie(title_str);
    }
    catch (Validation_exception &ve) {
        auto *error = new QErrorMessage();
        QString error_message = "Following errors occurred: " + QString::fromStdString(ve.get_message());
        error->showMessage(error_message);
    }
    populate_gui();
}

void Gui::update_gui() {
    QString title = title_line->text();
    std::string title_str = title.toStdString();
    QString new_title = title_line->text();
    std::string new_title_str = new_title.toStdString();
    QString genre = genre_line->text();
    std::string genre_str = genre.toStdString();
    QString year = release_year_line->text();
    std::string year_str = year.toStdString();
    QString likes = likes_line->text();
    std::string likes_str = likes.toStdString();
    QString trailer = trailer_line->text();
    std::string trailer_str = trailer.toStdString();
    try {
        service.update_movie(title_str, new_title_str, genre_str, year_str, likes_str, trailer_str);
    }
    catch (Validation_exception &ve) {
        auto *error = new QErrorMessage();
        QString error_message = "Following errors occurred: " + QString::fromStdString(ve.get_message());
        error->showMessage(error_message);
    }
    populate_gui();
}

void Gui::create_watchlist() {
    QString file_type = file_type_line->text();
    std::string file_type_str = file_type.toStdString();
    Watchlist *watchlist;
    if (file_type_str == "CSV" || file_type_str == "csv") {
        watchlist = new Watchlist_csv(R"(C:\Users\tufar\Desktop\Faculty\Year 1\Semester 2\OOP\a11\watchlist.csv)");
        service.change_watchlist(watchlist);
    } else if (file_type_str == "HTML" || file_type_str == "html") {
        watchlist = new Watchlist_html(R"(C:\Users\tufar\Desktop\Faculty\Year 1\Semester 2\OOP\a11\watchlist.html)");
        service.change_watchlist(watchlist);
    } else {
        auto *error = new QErrorMessage();
        QString error_message = "Invalid file type";
        error->showMessage(error_message);
    }
}

void Gui::filter_user() {
    QString genre = genre_filter_line->text();
    std::string genre_str = genre.toStdString();
    filtered_movies = service.filter_by_genre(genre_str);
    index = 0;
    show_movie();
}

void Gui::show_movie() {
    if (index == filtered_movies.size()) {
        auto *error = new QErrorMessage();
        QString error_message = "No movies to show";
        error->showMessage(error_message);
    } else {
        current_movie_widget->clear();
        QString movie = QString::fromStdString(filtered_movies[index].to_string());
        auto *item = new QListWidgetItem{movie};
        current_movie_widget->addItem(item);
        index++;
    }
}

void Gui::add_to_watchlist() {
    if (filtered_movies.empty()) {
        auto *error = new QErrorMessage();
        QString error_message = "No movie to add";
        error->showMessage(error_message);
        return;
    }
    try {
        service.add_movie_to_watch_list(filtered_movies[index - 1]);
    }
    catch (Validation_exception &ve) {
        auto *error = new QErrorMessage();
        QString error_message = "Following errors occurred: " + QString::fromStdString(ve.get_message());
        error->showMessage(error_message);
    }
    watchlist_widget->clear();
    for (const auto &movie: service.get_watch_list()) {
        QString itemInList = QString::fromStdString(movie.to_string());
        auto *item = new QListWidgetItem{itemInList};
        watchlist_widget->addItem(item);
    }
}

void Gui::remove_from_watchlist() {
    if (service.get_watch_list().empty()) {
        auto *error = new QErrorMessage();
        QString error_message = "No movie to remove";
        error->showMessage(error_message);
        return;
    }
    QString title = title_user_line->text();
    std::string title_str = title.toStdString();
    try {
        service.remove_movie_from_watch_list(title_str);
    }
    catch (Validation_exception &ve) {
        auto *error = new QErrorMessage();
        QString error_message = "Following errors occurred: " + QString::fromStdString(ve.get_message());
        error->showMessage(error_message);
    }
    watchlist_widget->clear();
    for (const auto &movie: service.get_watch_list()) {
        QString itemInList = QString::fromStdString(movie.to_string());
        auto *item = new QListWidgetItem{itemInList};
        watchlist_widget->addItem(item);
    }
}

void Gui::open_watchlist_file() {
    service.write_watch_list_to_file();
    service.show_watch_list_from_file();
}

void Gui::stop_movie_iteration() {
    current_movie_widget->clear();
    index = 0;
}

void Gui::real_time_filter() {
    movie_list_widget->clear();
    std::string filter_string = real_time_filter_line->text().toStdString();
    std::vector<Movie> partial_match = service.partial_match(filter_string);
    for (auto &movie: partial_match){
        QString movie_qstr = QString::fromStdString(movie.to_string());
        auto *item = new QListWidgetItem(movie_qstr);
        movie_list_widget->addItem(item);
    }
}

void Gui::undo() {
    try{
        service.undo();
    }
    catch (Validation_exception &ve){
        auto *error = new QErrorMessage();
        QString error_message = QString::fromStdString(ve.get_message());
        error->showMessage(error_message);
    }
    populate_gui();
}

void Gui::redo() {
    try{
        service.redo();
    }
    catch (Validation_exception &ve){
        auto *error = new QErrorMessage();
        QString error_message = QString::fromStdString(ve.get_message());
        error->showMessage(error_message);
    }
    populate_gui();
}

void Gui::open_watchlist_window() {
    watchlist_window = new MyTableModel(service);
    QTableView *table_view = new QTableView;
    table_view->setModel(watchlist_window);
    table_view->show();
}
