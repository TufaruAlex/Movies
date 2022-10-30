#include "Validator.h"
#include <regex>
#include <utility>

Validation_exception::Validation_exception(std::string _message) {
    this->message = std::move(_message);
}

std::string Validation_exception::get_message() const {
    return this->message;
}

std::string validate_number(const std::string &_str_number, const std::string &type) {
    std::string error;
    char *remaining;
    if (strcmp(_str_number.c_str(), "0") == 0)
        return error;
    int number = strtol(_str_number.c_str(), &remaining, 10);
    if (number == 0) {
        if (type == "likes")
            error += "Invalid likes\n";
        else
            error += "Invalid release year\n";
    }
    return error;
}

std::string validate_link(const std::string &link) {
    std::string error;
    const std::regex pattern(
            R"(((http|https)://)(www.)?[a-zA-Z0-9@:%._\+~#?&//=]{2,256}\.[a-z]{2,6}\b([-a-zA-Z0-9@:%._\+~#?&//=]*))");
    if (!std::regex_match(link, pattern))
        error += "Invalid link\n";
    return error;
}

void Validator::validate_add(const Repo &r, std::string &title, std::string &release_year, std::string &likes,
                             std::string &trailer) {
    std::string error;
    error += validate_number(release_year, "release year") + validate_number(likes, "likes") + validate_link(trailer);
    std::vector<Movie> movies = r.get_movie_list();
    for (auto &movie: movies)
        if (movie.get_title() == title) {
            error += "Movie already in database\n";
            break;
        }

    if (!error.empty())
        throw Validation_exception(error);

}

void Validator::validate_delete(const Repo &r, std::string &title) {
    std::string error;
    std::vector<Movie> arr = r.get_movie_list();
    bool movie_exists = false;
    for (auto &movie: arr)
        if (movie.get_title() == title) {
            movie_exists = true;
            break;
        }
    if (!movie_exists)
        throw Validation_exception("Movie not in database\n");
}

void
Validator::validate_update(const Repo &r, std::string &title, std::string &new_release_year, std::string &new_likes,
                           std::string &new_trailer) {
    std::string error;
    error += validate_number(new_release_year, "release year") + validate_number(new_likes, "likes") +
             validate_link(new_trailer);
    std::vector<Movie> movies = r.get_movie_list();
    bool movie_exists = false;
    for (auto &movie: movies)
        if (movie.get_title() == title) {
            movie_exists = true;
            break;
        }
    if (!movie_exists)
        error += "Movie not in database\n";

    if (!error.empty())
        throw Validation_exception(error);
}

void Validator::validate_add_to_watchlist(const Watchlist &ur, const std::string &title) {
    std::vector<Movie> movies;
    movies = ur.get_watch_list();
    for (auto &movie: movies)
        if (movie.get_title() == title)
            throw Validation_exception("Movie already in watchlist_widget\n");
}

void Validator::validate_remove_from_watchlist(const Watchlist &ur, const std::string &title) {
    std::vector<Movie> movies = ur.get_watch_list();
    bool movie_exists = false;
    for (auto &movie: movies)
        if (movie.get_title() == title) {
            movie_exists = true;
            break;
        }
    if (!movie_exists)
        throw Validation_exception("Movie not in watchlist_widget\n");
}

