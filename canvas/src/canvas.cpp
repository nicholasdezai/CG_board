#include "canvas.h"
#include "line_algorithms.h"
#include "circle_algorithms.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), color(Qt::black), backgroundColor(Qt::white), drawMode(Line), Algorithm(Bresenham_line),
      thickness(1) {
}

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

void Canvas::setAlgorithm(Algorithms algorithm) {
    Algorithm = algorithm;
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
    painter.fillRect(rect(), backgroundColor); // 填充背景色

    for (const auto &drawing: drawings) {
        QPen pen(drawing.mode == Eraser ? Qt::white : drawing.color, drawing.thickness);
        painter.setPen(pen);
        if (!drawing.points.empty()) {
            painter.drawPoints(drawing.points.data(), drawing.points.size());
        }
    }

    if (!currentPoints.empty()) {
        QPen pen(drawMode == Eraser ? backgroundColor : color, thickness);
        painter.setPen(pen);
        painter.drawPoints(currentPoints.data(), currentPoints.size());
    }

    if (!previewPoints.empty()) {
        QPen pen(color, thickness, Qt::DashLine);
        painter.setPen(pen);
        for (size_t i = 1; i < previewPoints.size(); ++i) {
            painter.drawPoints(previewPoints.data(), previewPoints.size());
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
        drawings.push_back({drawMode, color, currentPoints, Algorithm, thickness});
    } else {
        endPoint = event->pos();
        previewPoints.clear();
        if (drawMode == Line) {
            if (Algorithm == Bresenham_line) {
                previewPoints = bresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
            } else if (Algorithm == Midpoint_line) {
                previewPoints = midpointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
            }
        } else if (drawMode == Circle) {
            if (Algorithm == Midpoint_circle) {
                previewPoints = midpointCircle(startPoint.x(), startPoint.y(),
                                               qSqrt(qPow(endPoint.x() - startPoint.x(), 2) + qPow(endPoint.y() - startPoint.y(), 2)));
            } else if (Algorithm == Midpoint_oval) {
                previewPoints = midpointOval(startPoint.x(), startPoint.y(), qAbs(endPoint.x() - startPoint.x()),
                                             qAbs(endPoint.y() - startPoint.y()));
            } else if (Algorithm == plusminus_arc) {
                previewPoints = plusminusArc(startPoint.x(), startPoint.y(),
                                             qSqrt(qPow(endPoint.x() - startPoint.x(), 2) + qPow(endPoint.y() - startPoint.y(), 2)),
                                             0, 120);
            }
        }
    }
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    endPoint = event->pos();

    if (drawMode == Line) {
        if (Algorithm == Bresenham_line) {
            currentPoints = bresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        } else if (Algorithm == Midpoint_line) {
            currentPoints = midpointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        }
    } else if (drawMode == Circle) {
        if (Algorithm == Midpoint_circle) {
            currentPoints = midpointCircle(startPoint.x(), startPoint.y(),
                                           qSqrt(qPow(endPoint.x() - startPoint.x(), 2) + qPow(endPoint.y() - startPoint.y(), 2)));
        } else if (Algorithm == Midpoint_oval) {
            currentPoints = midpointOval(startPoint.x(), startPoint.y(), qAbs(endPoint.x() - startPoint.x()),
                                         qAbs(endPoint.y() - startPoint.y()));
        } else if (Algorithm == plusminus_arc) {
            currentPoints = plusminusArc(startPoint.x(), startPoint.y(),
                                         qSqrt(qPow(endPoint.x() - startPoint.x(), 2) + qPow(endPoint.y() - startPoint.y(), 2)),
                                         0, 120);
        }
    } else if (drawMode == Eraser) {
        currentPoints.push_back(endPoint);
    }

    drawings.push_back({drawMode, color, currentPoints, Algorithm, thickness});
    update();
}

// 双击选中图案
void Canvas::mouseDoubleClickEvent(QMouseEvent *event) {
}
