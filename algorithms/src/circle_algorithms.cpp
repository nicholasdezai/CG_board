//
// Created by jin on 24-9-6.
//
#include "circle_algorithms.h"

std::vector<QPoint> midpointCircle(int xc, int yc, int r) {
    std::vector<QPoint> points;
    int x = r, y = 0;
    int P = 1 - r;

    if (r > 0) {
        points.push_back(QPoint(xc - r, yc));
        points.push_back(QPoint(xc + r, yc));
        points.push_back(QPoint(xc, yc - r));
        points.push_back(QPoint(xc, yc + r));
    }

    while (x > y) {
        y++;
        if (P <= 0) {
            P = P + 2*y + 1;
        } else {
            x--;
            P = P + 2*y - 2*x + 1;
        }
        if (x < y) break;

        points.push_back(QPoint(xc + x, yc + y));
        points.push_back(QPoint(xc - x, yc + y));
        points.push_back(QPoint(xc + x, yc - y));
        points.push_back(QPoint(xc - x, yc - y));

        if (x != y) {
            points.push_back(QPoint(xc + y, yc + x));
            points.push_back(QPoint(xc - y, yc + x));
            points.push_back(QPoint(xc + y, yc - x));
            points.push_back(QPoint(xc - y, yc - x));
        }
    }
    return points;
}

std::vector<QPoint> midpointOval(int xc, int yc, int rx, int ry) {
    std::vector<QPoint> points;
    // TODO: Implement the midpoint algorithm to draw an oval

    return points;
}

std::vector<QPoint> plusminusArc(int xc, int yc, int r, int startAngle, int endAngle) {
    std::vector<QPoint> points;
    // TODO: Implement the plus-minus algorithm to draw an arc

    return points;
}