#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QColor>
#include <QPoint>
#include <vector>

enum DrawMode {
    Line,
    Circle,
    Eraser,
    Pencil
};

enum Algorithms {
    Midpoint_line,
    Bresenham_line,
    Midpoint_circle,
    Midpoint_oval,
    plusminus_arc,
};

struct Drawing {
    DrawMode mode;
    QColor color;
    std::vector<QPoint> points; // 添加 points 以存储绘制的点
    Algorithms Algorithm;  // 添加 lineAlgorithm 以区分直线生成算法
    int thickness;  // 添加 thickness 以存储线条粗细
};

class Canvas : public QWidget {
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);

    QColor getColor() const;
    void setColor(const QColor &color);
    QColor getBackgroundColor() const;
    void setBackgroundColor(const QColor &color);
    void setDrawMode(DrawMode mode);
    void setAlgorithm(Algorithms algorithm);
    int getThickness() const;
    void setThickness(int thickness);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QColor color;
    QColor backgroundColor;
    DrawMode drawMode;
    Algorithms Algorithm;
    int thickness;
    QPoint startPoint;
    QPoint endPoint;
    std::vector<Drawing> drawings;     // 添加 drawings 以存储绘制的图形
    std::vector<QPoint> currentPoints; // 添加 currentPoints 以存储当前绘制的点
    std::vector<QPoint> previewPoints; // 添加用于存储预览点的变量
};

#endif // CANVAS_H
