//
// Created by tufar on 03.06.2022.
//

#include "Movie.h"
#include "Repo.h"

#ifndef A11_UNDO_H
#define A11_UNDO_H

class UndoRedo {
public:
    virtual void undo() = 0;

    virtual void redo() = 0;
};

class UndoRedoAdd : public UndoRedo {
private:
    Movie movie;
    Repo *repo;
public:
    UndoRedoAdd(Repo *repo, const Movie &movie);

    void undo() override;

    void redo() override;
};

class UndoRedoRemove : public UndoRedo {
private:
    Movie movie;
    Repo *repo;
public:
    UndoRedoRemove(Repo *repo, const Movie& movie);

    void undo() override;
    void redo() override;
};

class UndoRedoUpdate : public UndoRedo{
private:
    Movie old_movie;
    Movie new_movie;
    Repo *repo;
public:
    UndoRedoUpdate(Repo *repo, const Movie& old_movie, const Movie& new_movie);

    void undo() override;

    void redo() override;
};

#endif //A11_UNDO_H
