#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QSpinBox>
#include <QLabel>
#include "canvas.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void changeCanvasColor();

    void changeCanvasBackgroundColor();

    void setLineMode();

    void setCircleMode();

    void setPolygonMode();

    void setSelectMode();

    void setMidpointAlgorithm();

    void setBresenhamAlgorithm();

    void setMidpointCircleAlgorithm();

    void setMidpointOvalAlgorithm();

    void setplusminusArcAlgorithm();

    void changeThickness(int thickness);

private:
    Canvas *canvas;
    QSpinBox *thicknessSpinBox;
};

#endif // MAINWINDOW_H
