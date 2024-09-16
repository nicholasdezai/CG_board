#include "canvas.h"
#include "line_algorithms.h"
#include "circle_algorithms.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), color(Qt::black), backgroundColor(Qt::white), drawMode(Line), lineAlgorithm(Bresenham), thickness(1) {}

QColor Canvas::getColor() const {
    return color;
}

void Canvas::setColor(const QColor &newColor) {
    color = newColor;
}

QColor Canvas::getBackgroundColor() const {
    return backgroundColor;
}

void Canvas::setBackgroundColor(const QColor &newColor) {
    backgroundColor = newColor;
    update();
}

void Canvas::setDrawMode(DrawMode mode) {
    drawMode = mode;
}

void Canvas::setLineAlgorithm(LineAlgorithm algorithm) {
    lineAlgorithm = algorithm;
}

int Canvas::getThickness() const {
    return thickness;
}

void Canvas::setThickness(int newThickness) {
    thickness = newThickness;
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this); // 创建一个 QPainter 对象
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    painter.fillRect(rect(), backgroundColor);  // 填充背景色

    for (const auto &drawing : drawings) {
        QPen pen(drawing.mode == Eraser ? Qt::white : drawing.color, drawing.thickness);
        painter.setPen(pen);
        if (!drawing.points.empty()) {
            if (drawing.mode == Line || drawing.mode == Eraser || drawing.mode == Pencil) {
                painter.drawPoints(drawing.points.data(), drawing.points.size());
            } else if (drawing.mode == Circle) {
                QRect boundingRect(drawing.points[0], drawing.points[1]);
                painter.drawEllipse(boundingRect);
            }
        }
    }

    if (!currentPoints.empty()) {
        QPen pen(drawMode == Eraser ? backgroundColor : color, thickness);
        painter.setPen(pen);
        if (drawMode == Line || drawMode == Eraser) {
            painter.drawPoints(currentPoints.data(), currentPoints.size());
        } else if (drawMode == Circle) {
            QRect boundingRect(currentPoints[0], currentPoints[1]);
            painter.drawEllipse(boundingRect);
        }
    }

    if (!previewPoints.empty()) {
        QPen pen(color, thickness, Qt::DashLine);
        painter.setPen(pen);
        if (drawMode == Line) {
            for (size_t i = 1; i < previewPoints.size(); ++i) {
                painter.drawLine(previewPoints[i - 1], previewPoints[i]);
            }
        } else if (drawMode == Circle) {
            QRect boundingRect(previewPoints[0], previewPoints[1]);
            painter.drawEllipse(boundingRect);
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    startPoint = event->pos();
    currentPoints.clear();
    previewPoints.clear();
    if (drawMode == Eraser || drawMode == Pencil) {
        currentPoints.push_back(startPoint);
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (drawMode == Eraser || drawMode == Pencil) {
        currentPoints.push_back(event->pos());
        drawings.push_back({drawMode, color, currentPoints, lineAlgorithm, thickness});
    } else {
        endPoint = event->pos();
        previewPoints.clear();
        if (drawMode == Line) {
            if (lineAlgorithm == Bresenham) {
                previewPoints = bresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
            } else if (lineAlgorithm == Midpoint) {
                previewPoints = midpointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
            }
        } else if (drawMode == Circle) {
            previewPoints.push_back(startPoint);
            previewPoints.push_back(endPoint);
        }
    }
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    endPoint = event->pos();

    if (drawMode == Line) {
        if (lineAlgorithm == Bresenham) {
            currentPoints = bresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        } else if (lineAlgorithm == Midpoint) {
            currentPoints = midpointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        }
    } else if (drawMode == Circle) {
        currentPoints.push_back(startPoint);
        currentPoints.push_back(endPoint);
    } else if (drawMode == Eraser) {
        currentPoints.push_back(endPoint);
    }

    drawings.push_back({drawMode, color, currentPoints, lineAlgorithm, thickness});
    update();
}
