#pragma once

#include "Movie.h"
#include <vector>
#include <iostream>
#include <fstream>

class Repo {
private:
    std::vector<Movie> movies;
    std::vector<Movie> deleted_movies;

public:
    Repo();

    std::vector<Movie> get_movie_list() const;

    std::vector<Movie> get_movie_list_deleted() const;

    void add_movie(Movie &new_movie);

    void remove_movie(const std::string &title);

    void update_movie(const std::string &title, Movie &new_movie);

    void add_like_to_movie(const std::string &title);

    void write_movie_list_to_file();

    void write_deleted_list_to_file();

    ~Repo();
};
