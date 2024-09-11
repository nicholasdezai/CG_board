//
// Created by jin on 24-9-6.
//
#include "line_algorithms.h"

// 中点算法绘制直线
std::vector<QPoint> midpointLine(int x0, int y0, int x1, int y1) {
    std::vector<QPoint> points;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int d = dy - (dx / 2);
    int x = x0, y = y0;

    points.push_back(QPoint(x, y));

    while (x < x1) {
        x++;
        if (d < 0) {
            d = d + dy;
        } else {
            d += (dy - dx);
            y++;
        }
        points.push_back(QPoint(x, y));
    }
    return points;
}

// Bresenham算法绘制直线
std::vector<QPoint> bresenhamLine(int x0, int y0, int x1, int y1) {
    std::vector<QPoint> points;
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (true) {
        points.push_back(QPoint(x0, y0));
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
    return points;
}
