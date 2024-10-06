//
// Created by jin on 24-9-20.
//

#include "polygon_algorithms.h"

std::vector<QPoint> polygon_algorithms::createPolygon(QPoint x) {
    if (!prePoint_.empty()) {
        vertex_.push_back(x);
    } else {
        
    }
    return vertex_;
}

void polygon_algorithms::resetPrePoint() {
    prePoint_.clear();
}
