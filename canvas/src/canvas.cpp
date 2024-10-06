#include "canvas.h"
#include "line_algorithms.h"
#include "circle_algorithms.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), color(Qt::black), backgroundColor(Qt::white), drawMode(Line), Algorithm(Bresenham_line),
      thickness(1), is_selecting(false), id(-1) {
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
        QPen pen(drawing.color, drawing.thickness);
        painter.setPen(pen);

        if (!drawing.points.empty()) {
            painter.drawPoints(drawing.points.data(), drawing.points.size());
            // 打印顶点信息
            for (const auto &vertex: drawing.vertexes) {
                painter.drawText(vertex, QString("(%1, %2)").arg(vertex.x()).arg(vertex.y()));
            }
        }
    }

    if (!currentPoints.empty()) {
        QPen pen(color, thickness);
        painter.setPen(pen);
        painter.drawPoints(currentPoints.data(), currentPoints.size());
    }
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    startPoint = event->pos();
    currentPoints.clear();
    if (drawMode != Polygon) {
        vertexes.clear();
    }

    vertexes.push_back(startPoint);
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (drawMode == Polygon) return;

    endPoint = event->pos();
    currentPoints.clear();
    if (drawMode == Line) {
        if (Algorithm == Bresenham_line) {
            currentPoints = bresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        } else if (Algorithm == Midpoint_line) {
            currentPoints = midpointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        }
    } else if (drawMode == Circle) {
        if (Algorithm == Midpoint_circle) {
            currentPoints = midpointCircle(startPoint.x(), startPoint.y(),
                                           qSqrt(qPow(endPoint.x() - startPoint.x(), 2) + qPow(
                                                     endPoint.y() - startPoint.y(), 2)));
        } else if (Algorithm == Midpoint_oval) {
            currentPoints = midpointOval(startPoint.x(), startPoint.y(), qAbs(endPoint.x() - startPoint.x()),
                                         qAbs(endPoint.y() - startPoint.y()));
        } else if (Algorithm == plusminus_arc) {
            currentPoints = plusminusArc(startPoint.x(), startPoint.y(),
                                         qSqrt(qPow(endPoint.x() - startPoint.x(), 2) + qPow(
                                                   endPoint.y() - startPoint.y(), 2)),
                                         0, 120);
        }
    }
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    endPoint = event->pos();
    vertexes.push_back(endPoint);


    if (drawMode == Line) {
        if (Algorithm == Bresenham_line) {
            currentPoints = bresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        } else if (Algorithm == Midpoint_line) {
            currentPoints = midpointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        }
    } else if (drawMode == Circle) {
        if (Algorithm == Midpoint_circle) {
            currentPoints = midpointCircle(startPoint.x(), startPoint.y(),
                                           qSqrt(qPow(endPoint.x() - startPoint.x(), 2) + qPow(
                                                     endPoint.y() - startPoint.y(), 2)));
        } else if (Algorithm == Midpoint_oval) {
            currentPoints = midpointOval(startPoint.x(), startPoint.y(), qAbs(endPoint.x() - startPoint.x()),
                                         qAbs(endPoint.y() - startPoint.y()));
        } else if (Algorithm == plusminus_arc) {
            currentPoints = plusminusArc(startPoint.x(), startPoint.y(),
                                         qSqrt(qPow(endPoint.x() - startPoint.x(), 2) + qPow(
                                                   endPoint.y() - startPoint.y(), 2)),
                                         0, 120);
        }
    } else if (drawMode == Polygon) {
        vertexes.pop_back();
        if (event->button() == Qt::LeftButton) {
            if (vertexes.size() > 1) {
                std::vector<QPoint> temp = bresenhamLine(vertexes[vertexes.size() - 2].x(),
                                                         vertexes[vertexes.size() - 2].y(),
                                                         vertexes[vertexes.size() - 1].x(),
                                                         vertexes[vertexes.size() - 1].y());
                currentPoints.insert(currentPoints.end(), temp.begin(), temp.end());
            }
        } else {
            std::vector<QPoint> temp = bresenhamLine(vertexes[0].x(),
                                                     vertexes[0].y(),
                                                     vertexes[vertexes.size() - 2].x(),
                                                     vertexes[vertexes.size() - 2].y());
            currentPoints.insert(currentPoints.end(), temp.begin(), temp.end());
            tempDrawing.vertexes = vertexes;
            vertexes.clear();
        }
    }


    tempDrawing.mode = drawMode;
    tempDrawing.color = color;
    tempDrawing.points = currentPoints;
    tempDrawing.Algorithm = Algorithm;
    tempDrawing.thickness = thickness;
    tempDrawing.is_selected = is_selecting;
    tempDrawing.vertexes = vertexes;
    if (is_selecting) {
        tempDrawing.id = id;
    } else {
        tempDrawing.id = drawings.size();
    }

    drawings.push_back(tempDrawing);
    update();
}

// 双击选中图案
void Canvas::mouseDoubleClickEvent(QMouseEvent *event) {
}
