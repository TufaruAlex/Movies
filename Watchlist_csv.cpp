#include "Watchlist_csv.h"

#include <utility>

Watchlist_csv::Watchlist_csv(std::string file) {
    this->file = std::move(file);
}

void Watchlist_csv::write_watch_list_to_file() const {
    std::ofstream f(file);
    if (!f.is_open())
        return;
    for (auto movie: this->get_watch_list())
        f << movie;
    f.close();
}

void Watchlist_csv::show_watch_list_from_file() const {
    ShellExecuteA(nullptr, "open", file.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}
