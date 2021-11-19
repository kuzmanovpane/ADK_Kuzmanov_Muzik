#include "load.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

//#include <stdio.h>

//using namespace std;

Load::Load()
{

}

std::vector<QPolygon> Load::load_file(std::string &filename)
{
    //Vector to save the results
    std::vector<QPolygon> result;

    std::string line, coords;
    std::ifstream file;

    file.open(filename);

    //Iterates through each line of the file
    while(file.good())
    {
        //Reading csv file line by line
        while(getline(file, line))
        {

            QPolygon polygon;

            //Stores polygon coordinates
            std::stringstream sline(line);

            //Iterates through each point
            while(getline(sline, coords, ','))
            {
                double x, y;
                std::stringstream coord(coords);
                std::string scoord;
                int i = 0;

                //Defines x, y from coordinate pairs
                while(coord>>scoord)
                {
                    if (i == 0)
                        x = (stod(scoord) - 641500);
                    else if (i == 1)
                        y = (stod(scoord) - 1111000)-600;
                    i++;
                }
                //Point added to polygon
                QPoint p(x, y);
                polygon << p;
            }
            //Polygon added to results
            result.push_back(polygon);
        }
    }

    file.close();

    return result;
}
