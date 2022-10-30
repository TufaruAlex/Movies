#pragma once

#include "Watchlist.h"

class Watchlist_csv: public Watchlist{
private:
    std::string file;

public:
    explicit Watchlist_csv(std::string file);

    void write_watch_list_to_file() const override;

    void show_watch_list_from_file() const override;
};