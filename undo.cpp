//
// Created by tufar on 03.06.2022.
//

#include "undo.h"

UndoRedoAdd::UndoRedoAdd(Repo *repo, const Movie& movie) {
    this->repo = repo;
    this->movie = movie;
}

void UndoRedoAdd::undo() {
    repo->remove_movie(movie.get_title());
}

void UndoRedoAdd::redo() {
    repo->add_movie(movie);
}


UndoRedoRemove::UndoRedoRemove(Repo *repo, const Movie& movie) {
    this->repo = repo;
    this->movie = movie;
}

void UndoRedoRemove::undo() {
    repo->add_movie(movie);
}

void UndoRedoRemove::redo() {
    repo->remove_movie(movie.get_title());
}

UndoRedoUpdate::UndoRedoUpdate(Repo *repo, const Movie& old_movie, const Movie& new_movie) {
    this->repo = repo;
    this->old_movie = old_movie;
    this->new_movie = new_movie;
}

void UndoRedoUpdate::undo() {
    repo->update_movie(new_movie.get_title(), old_movie);
}

void UndoRedoUpdate::redo() {
    repo->update_movie(old_movie.get_title(), new_movie);
}
