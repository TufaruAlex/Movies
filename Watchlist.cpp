#include "Watchlist.h"

void Watchlist::add_movie_to_watch_list(const Movie &movie) {
    watch_list.push_back(movie);
}

void Watchlist::remove_movie_from_watch_list(const std::string &title) {
    for (int i = 0; i < watch_list.size(); i++)
        if (watch_list[i].get_title() == title) {
            watch_list.erase(watch_list.begin() + i);
            break;
        }
}

std::vector<Movie> Watchlist::get_watch_list() const {
    return watch_list;
}

Watchlist::~Watchlist() = default;


