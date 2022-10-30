#include "Movie.h"

#include <utility>
#include <sstream>

Movie::Movie(std::string title, std::string genre, int release_year, int likes, std::string trailer) {
    this->title = std::move(title);
    this->genre = std::move(genre);
    this->year_of_release = release_year;
    this->number_of_likes = likes;
    this->trailer = std::move(trailer);
}

std::string Movie::get_title() const {
    return title;
}

std::string Movie::get_genre() const {
    return genre;
}

int Movie::get_release_year() const {
    return year_of_release;
}

int Movie::get_likes() const {
    return number_of_likes;
}

std::string Movie::get_trailer() const {
    return trailer;
}

void Movie::set_title(std::string new_title) {
    this->title = std::move(new_title);
}

void Movie::set_genre(std::string new_genre) {
    this->genre = std::move(new_genre);
}

void Movie::set_release_year(int new_release_year) {
    this->year_of_release = new_release_year;
}

void Movie::set_likes(int new_likes) {
    this->number_of_likes = new_likes;
}

void Movie::set_trailer(std::string new_trailer) {
    this->trailer = std::move(new_trailer);
}

Movie::~Movie() = default;

std::string Movie::to_string() const {
    return "Title: " + this->title + ", genre: " + this->genre + ", year_of_release: " +
           std::to_string(this->year_of_release) + ", number of likes: " + std::to_string(this->number_of_likes) +
           ", trailer link: " + this->trailer;
}

void Movie::play_trailer() const {
    ShellExecuteA(nullptr, nullptr, nullptr, this->trailer.c_str(), "opera.exe", SW_SHOWMAXIMIZED);
}

std::ofstream &operator<<(std::ofstream &file, Movie &movie) {
    std::string movie_str = movie.title + '|' + movie.genre + '|' + std::to_string(movie.year_of_release) + '|' +
                        std::to_string(movie.number_of_likes) + '|' + movie.trailer + '\n';
    file << movie_str;
    return file;
}

std::ifstream &operator>>(std::ifstream &file, Movie &movie) {
    std::string movie_str, token;
    std::getline(file, movie_str);
    if (movie_str.empty()) {
        movie.number_of_likes = -1;
        return file;
    }
    std::istringstream iss(movie_str);
    std::getline(iss, token, '|');
    movie.title = token;
    std::getline(iss, token, '|');
    movie.genre = token;
    std::getline(iss, token, '|');
    char *remaining;
    movie.year_of_release = strtol(token.c_str(), &remaining, 10);
    std::getline(iss, token, '|');
    movie.number_of_likes = strtol(token.c_str(), &remaining, 10);
    std::getline(iss, token, '|');
    movie.trailer = token;
    return file;
}
