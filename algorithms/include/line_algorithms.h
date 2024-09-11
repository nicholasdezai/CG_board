//
// Created by jin on 24-9-6.
//

#ifndef LINE_ALGORITHMS_H
#define LINE_ALGORITHMS_H

#include <vector>
#include <QPoint>

// 中点算法绘制直线
std::vector<QPoint> midpointLine(int x0, int y0, int x1, int y1);

// Bresenham算法绘制直线
std::vector<QPoint> bresenhamLine(int x0, int y0, int x1, int y1);

#endif // LINE_ALGORITHMS_H
