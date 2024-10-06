//
// Created by jin on 24-9-20.
//

#ifndef POLYGON_ALGORITHMS_H
#define POLYGON_ALGORITHMS_H

#include <QPoint>
#include <vector>
#include "line_algorithms.h"


class polygon_algorithms {
public:
    std::vector<QPoint> createPolygon(QPoint x);
    void resetPrePoint();
private:
    std::vector<QPoint> prePoint_;
    std::vector<QPoint> vertex_;
};



#endif //POLYGON_ALGORITHMS_H
