#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QColor>
#include <QPoint>
#include <vector>
#include <experimental/any>

enum DrawMode {
    Line,
    Circle,
    Polygon,
};

enum Algorithms {
    Midpoint_line,
    Bresenham_line,
    Midpoint_circle,
    Midpoint_oval,
    plusminus_arc,
};

class Object {
public:
    DrawMode mode_;
    QColor color_;
    std::vector<QPoint> vertexes_;
    std::vector<QPoint> points_;
    Algorithms Algorithm_;
    int thickness_;
    bool is_selected_;
    int id_;
};

class Line : public Object {

};

class Circle : public Object {

};

struct Drawing {
    DrawMode mode;
    QColor color;
    std::vector<QPoint> vertexes; // 添加 vertexes 以存储绘制的顶点
    std::vector<QPoint> points; // 添加 points 以存储绘制的点
    Algorithms Algorithm;  // 添加 lineAlgorithm 以区分直线生成算法
    int thickness;  // 添加 thickness 以存储线条粗细
    bool is_selected;  // 添加 is_selected 以标记是否被选中
    int id;  // 添加 id 以标记图形的编号
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
    Drawing tempDrawing;  // 添加 tempDrawing 以存储当前绘制的图形
    QColor color;
    QColor backgroundColor;
    DrawMode drawMode;
    Algorithms Algorithm;
    std::vector<QPoint> vertexes; // 添加 vertexes 以存储绘制的顶点
    int thickness;
    bool is_selecting;  // 添加 is_selecting 以标记是否正在选择
    int id;
    QPoint startPoint;
    QPoint endPoint;
    std::vector<Drawing> drawings;     // 添加 drawings 以存储绘制的图形
    std::vector<QPoint> currentPoints; // 添加 currentPoints 以存储当前绘制的点

    std::vector<std::experimental::any> objects;
};

#endif // CANVAS_H
