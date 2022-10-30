#pragma once

#include "Movie.h"
#include <vector>

class Watchlist {
private:
    std::vector<Movie> watch_list;

public:
    void add_movie_to_watch_list(const Movie &movie);

    void remove_movie_from_watch_list(const std::string &title);

    std::vector<Movie> get_watch_list() const;

    ~Watchlist();

    virtual void write_watch_list_to_file() const = 0;

    virtual void show_watch_list_from_file() const = 0;
};