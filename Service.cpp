#include "Service.h"
#include "Validator.h"
#include <regex>

Service::Service() = default;

Service::Service(const Service &s) {
    this->repo = s.repo;
    this->watchlist = s.watchlist;
}

Service::Service(Repo *repo, Watchlist *watchlist) {
    this->repo = repo;
    this->watchlist = watchlist;
}

std::vector<Movie> Service::get_movie_list() const {
    return this->repo->get_movie_list();
}

void
Service::add_movie(std::string &title, std::string &genre, std::string &year_of_release, std::string &number_of_likes,
                   std::string &trailer) {
    Validator::validate_add(*this->repo, title, year_of_release, number_of_likes, trailer);
    int release_year_nr = std::stoi(year_of_release);
    int likes_nr = std::stoi(number_of_likes);
    Movie movie(title, genre, release_year_nr, likes_nr, trailer);
    std::shared_ptr<UndoRedo> action = std::make_shared<UndoRedoAdd>(repo, movie);
    undo_actions.push_back(action);
    this->repo->add_movie(movie);
}

void Service::remove_movie(std::string &title) {
    Validator::validate_delete(*this->repo, title);
    Movie movie = get_movie_from_title(title);
    std::shared_ptr<UndoRedo> action = std::make_shared<UndoRedoRemove>(repo, movie);
    undo_actions.push_back(action);
    this->repo->remove_movie(title);
}

void Service::update_movie(std::string &title, std::string &new_title, std::string &new_genre,
                           std::string &new_year_of_release, std::string &new_number_of_likes,
                           std::string &new_trailer) {
    Validator::validate_update(*this->repo, title, new_year_of_release, new_number_of_likes, new_trailer);
    int new_release_year_nr = std::stoi(new_year_of_release);
    int new_likes_nr = std::stoi(new_number_of_likes);
    Movie movie(new_title, new_genre, new_release_year_nr, new_likes_nr, new_trailer);
    Movie old_movie = get_movie_from_title(title);
    std::shared_ptr<UndoRedo> action = std::make_shared<UndoRedoUpdate>(repo, old_movie, movie);
    undo_actions.push_back(action);
    this->repo->update_movie(title, movie);
}

std::vector<Movie> Service::filter_by_genre(std::string &genre) const {
    if (!genre.empty()) {
        std::vector<Movie> initial_movie_list = get_movie_list();
        int size = 0;
        for (auto &movie: get_movie_list()) {
            if (movie.get_genre() == genre)
                size++;
        }
        std::vector<Movie> movie_list(size);
        std::copy_if(initial_movie_list.begin(), initial_movie_list.end(),
                     movie_list.begin(), [&genre](const Movie &movie) { return movie.get_genre() == genre; });
        return movie_list;
    }
    return get_movie_list();
}

std::vector<Movie> Service::get_watch_list() const {
    return watchlist->get_watch_list();
}

void Service::add_movie_to_watch_list(const Movie &movie) {
    Validator::validate_add_to_watchlist(*this->watchlist, movie.get_title());
    watchlist->add_movie_to_watch_list(movie);
}

void Service::remove_movie_from_watch_list(const std::string &title) {
    Validator::validate_remove_from_watchlist(*this->watchlist, title);
    watchlist->remove_movie_from_watch_list(title);
}

void Service::add_like_to_movie(const std::string &title) {
    repo->add_like_to_movie(title);
}

std::vector<Movie> Service::get_movie_list_deleted() const {
    return repo->get_movie_list_deleted();
}

void Service::write_repo_to_file() {
    repo->write_movie_list_to_file();
    repo->write_deleted_list_to_file();
}

void Service::write_watch_list_to_file() {
    watchlist->write_watch_list_to_file();
}

void Service::show_watch_list_from_file() {
    watchlist->show_watch_list_from_file();
}

void Service::change_watchlist(Watchlist *new_watchlist) {
    watchlist = new_watchlist;
}

std::vector<Movie> Service::partial_match(const std::string &string_to_match) {
    std::vector<Movie> result;
    for (auto &movie: repo->get_movie_list()) {
        if (movie.to_string().find(string_to_match) != std::string::npos) {
            result.push_back(movie);
        }
    }
    return result;
}

void Service::undo() {
    if (undo_actions.empty())
        throw Validation_exception("There's no operation to undo");
    undo_actions[undo_actions.size() - 1]->undo();
    redo_actions.push_back(std::move(undo_actions[undo_actions.size() - 1]));
    undo_actions.pop_back();
}

void Service::redo() {
    if(redo_actions.empty())
        throw Validation_exception("There's no operation to redo");
    redo_actions[redo_actions.size() - 1]->redo();
    undo_actions.push_back(std::move(redo_actions[redo_actions.size() - 1]));
    redo_actions.pop_back();
}

Movie Service::get_movie_from_title(const std::string& title) {
    if (repo->get_movie_list().empty())
        throw Validation_exception("Empty list");
    for (int i = 0; i < repo->get_movie_list().size(); ++i) {
        if (repo->get_movie_list()[i].get_title() == title)
            return repo->get_movie_list()[i];
    }
    throw Validation_exception("A movie with this title is not in the database");
}

Service::~Service() = default;
