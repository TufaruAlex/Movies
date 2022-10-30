#include "Watchlist_html.h"

#include <utility>

Watchlist_html::Watchlist_html(std::string file) {
    this->file = std::move(file);
}

void Watchlist_html::write_watch_list_to_file() const {
    std::ofstream f(file);
    if (!f.is_open())
        return;
    f
            << "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>Watchlist</title>\n\t</head>\n\t<body>\n\t\t<table border=\"\">\n";
    f
            << "\t\t<tr>\n\t\t\t<td>Title</td>\n\t\t\t<td>Genre</td>\n\t\t\t<td>Release year</td>\n\t\t\t<td>Likes</td>\n\t\t\t<td>Trailer</td>\n\t\t</tr>\n";
    for (const auto &movie: this->get_watch_list()) {
        f << "\t\t<tr>\n";
        f << "\t\t\t<td>" << movie.get_title() << "</td>\n";
        f << "\t\t\t<td>" << movie.get_genre() << "</td>\n";
        f << "\t\t\t<td>" << movie.get_release_year() << " </td>\n";
        f << "\t\t\t<td>" << movie.get_likes() << "</td>\n";
        f << "\t\t\t<td><a href = \"" << movie.get_trailer() << "\">Link</a></td>\n";
        f << "\t\t</tr>\n";
    }
    f << "\t\t</table>\n\t</body>\n</html>\n";
    f.close();

}

void Watchlist_html::show_watch_list_from_file() const {
    ShellExecuteA(nullptr, "open", file.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}
