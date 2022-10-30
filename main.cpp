#include <QApplication>
#include <QFont>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFont font("Comic Sans MS");
    int font_size = font.pointSize();
    font.setPointSize(font_size - 3);
    QApplication::setFont(font);
    Repo repo;
    std::vector<Movie> vector=repo.get_movie_list();
    Gui gui{vector};
    gui.show();
    return QApplication::exec();
}
