//
// Created by jin on 24-9-6.
//

#ifndef CIRCLE_ALGORITHMS_H
#define CIRCLE_ALGORITHMS_H

#include <vector>
#include <QPoint>

// 中点算法绘制圆
std::vector<QPoint> midpointCircle(int xc, int yc, int r);
std::vector<QPoint> midpointOval(int xc, int yc, int rx, int ry);
std::vector<QPoint> plusminusArc(int xc, int yc, int r, int startAngle, int endAngle);

#endif // CIRCLE_ALGORITHMS_H

