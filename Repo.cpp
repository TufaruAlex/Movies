#include "Repo.h"

Repo::Repo() {
    Movie movie, deleted_movie;
    std::ifstream file;
    file.open(R"(C:\Users\tufar\Desktop\Faculty\Year 1\Semester 2\OOP\a11\movielist.txt)");
    while (!file.eof()) {
        file >> movie;
        if (movie.get_likes() != -1)
            movies.push_back(movie);
    }
    file.close();
    file.open(R"(C:\Users\tufar\Desktop\Faculty\Year 1\Semester 2\OOP\a11\deletedlist.txt)");
    while (!file.eof()) {
        file >> deleted_movie;
        if (movie.get_likes() != -1)
            deleted_movies.push_back(deleted_movie);
    }
    file.close();
}

std::vector<Movie> Repo::get_movie_list() const {
    return movies;
}

void Repo::add_movie(Movie &new_movie) {
    movies.push_back(new_movie);
}

void Repo::remove_movie(const std::string &title) {
    for (int i = 0; i < movies.size(); i++)
        if (movies[i].get_title() == title) {
            deleted_movies.push_back(movies[i]);
            movies.erase(movies.begin() + i);
            break;
        }
}

void Repo::update_movie(const std::string &title, Movie &new_movie) {
    for (auto &movie: movies)
        if (movie.get_title() == title) {
            movie = new_movie;
            break;
        }
}

void Repo::add_like_to_movie(const std::string &title) {
    for (auto &movie: movies)
        if (movie.get_title() == title) {
            movie.set_likes(movie.get_likes() + 1);
            return;
        }
}

std::vector<Movie> Repo::get_movie_list_deleted() const {
    return deleted_movies;
}

void Repo::write_movie_list_to_file() {
    std::ofstream file;
    file.open(R"(C:\Users\tufar\Desktop\Faculty\Year 1\Semester 2\OOP\a11\movielist.txt)");
    for (auto &movie: movies)
        file << movie;
    file.close();
}

void Repo::write_deleted_list_to_file() {
    std::ofstream file;
    file.open(R"(C:\Users\tufar\Desktop\Faculty\Year 1\Semester 2\OOP\a11\deletedlist.txt)");
    for (auto &movie: deleted_movies)
        file << movie;
    file.close();
}


Repo::~Repo() = default;
