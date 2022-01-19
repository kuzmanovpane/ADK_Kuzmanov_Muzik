#ifndef LOAD_H
#define LOAD_H

#include <string>
#include <vector>
#include <QtGui>

class Load
{
public:
    Load();

    static std::vector<QPolygon> load_file(std::string &filename);
};

#endif // LOAD_H
