#pragma once

#include "Repo.h"
#include "Watchlist.h"

class Validation_exception {
private:
    std::string message;
public:
    explicit Validation_exception(std::string _message);

    std::string get_message() const;

};

class Validator {
public:
    static void validate_add(const Repo &r, std::string &title, std::string &release_year, std::string &likes,
                             std::string &trailer);

    static void validate_delete(const Repo &r, std::string &title);

    static void
    validate_update(const Repo &r, std::string &title, std::string &new_release_year, std::string &new_likes,
                    std::string &new_trailer);

    static void validate_add_to_watchlist(const Watchlist &ur, const std::string& title);

    static void validate_remove_from_watchlist(const Watchlist &ur, const std::string& title);
};


