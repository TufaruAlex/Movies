#pragma once

#include "Repo.h"
#include "Watchlist.h"
#include "Watchlist_html.h"
#include "Watchlist_csv.h"
#include "undo.h"
#include "memory"

class Service {
private:
    std::vector<std::shared_ptr<UndoRedo>> undo_actions;
    std::vector<std::shared_ptr<UndoRedo>> redo_actions;
    Repo *repo;
    Watchlist *watchlist;
public:
    Service();

    Service(Repo *repo, Watchlist *watchlist);

    Service(const Service &s);

    void add_movie(std::string &title, std::string &genre, std::string &year_of_release, std::string &number_of_likes,
                   std::string &trailer);

    void remove_movie(std::string &title);

    void update_movie(std::string &title, std::string &new_title, std::string &new_genre, std::string &new_year_of_release,
                      std::string &new_number_of_likes, std::string &new_trailer);

    void add_movie_to_watch_list(const Movie &movie);

    void remove_movie_from_watch_list(const std::string &title);

    std::vector<Movie> get_movie_list() const;

    std::vector<Movie> get_movie_list_deleted() const;

    std::vector<Movie> get_watch_list() const;

    std::vector<Movie> filter_by_genre(std::string &genre) const;

    void add_like_to_movie(const std::string &title);

    void write_repo_to_file();

    void write_watch_list_to_file();

    void show_watch_list_from_file();

    void change_watchlist(Watchlist *new_watchlist);

    std::vector<Movie> partial_match(const std::string& string_to_match);

    Movie get_movie_from_title(const std::string& title);

    void undo();

    void redo();

    ~Service();
};
