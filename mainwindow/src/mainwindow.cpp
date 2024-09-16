#include "mainwindow.h"
#include "canvas.h"
#include <QColorDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), canvas(new Canvas(this)) {
    setCentralWidget(canvas);

    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu("&File");
    QAction *exitAction = fileMenu->addAction("E&xit");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    QToolBar *toolbar = addToolBar("Tools");
    QAction *changeColorAction = toolbar->addAction("Change Color");
    connect(changeColorAction, &QAction::triggered, this, &MainWindow::changeCanvasColor);

    QAction *changeBackgroundColorAction = toolbar->addAction("Change Background Color");
    connect(changeBackgroundColorAction, &QAction::triggered, this, &MainWindow::changeCanvasBackgroundColor);

    QAction *lineModeAction = toolbar->addAction("Line Mode");
    connect(lineModeAction, &QAction::triggered, this, &MainWindow::setLineMode);

    QAction *circleModeAction = toolbar->addAction("Circle Mode");
    connect(circleModeAction, &QAction::triggered, this, &MainWindow::setCircleMode);

    QAction *pencilAction = toolbar->addAction("Pencil");
    connect(pencilAction, &QAction::triggered, this, &MainWindow::setPencilMode);
    toolbar->addAction(pencilAction);

    QAction *eraserModeAction = toolbar->addAction("Eraser Mode");
    connect(eraserModeAction, &QAction::triggered, this, &MainWindow::setEraserMode);

    QMenu *algorithmMenu = menuBar->addMenu("&Algorithms");
    QAction *midpointAlgorithmAction = algorithmMenu->addAction("Midpoint Line Algorithm");
    connect(midpointAlgorithmAction, &QAction::triggered, this, &MainWindow::setMidpointAlgorithm);

    QAction *bresenhamAlgorithmAction = algorithmMenu->addAction("Bresenham Line Algorithm");
    connect(bresenhamAlgorithmAction, &QAction::triggered, this, &MainWindow::setBresenhamAlgorithm);

    // 添加选择线条粗细的控件
    toolbar->addSeparator();
    toolbar->addWidget(new QLabel("Thickness:"));
    thicknessSpinBox = new QSpinBox();
    thicknessSpinBox->setRange(1, 10);
    thicknessSpinBox->setValue(canvas->getThickness());
    connect(thicknessSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::changeThickness);
    toolbar->addWidget(thicknessSpinBox);
}

MainWindow::~MainWindow() {}

void MainWindow::changeCanvasColor() {
    QColor newColor = QColorDialog::getColor(canvas->getColor(), this, "Choose Canvas Color");
    if (newColor.isValid()) {
        canvas->setColor(newColor);
    }
}

void MainWindow::changeCanvasBackgroundColor() {
    QColor newColor = QColorDialog::getColor(canvas->getBackgroundColor(), this, "Choose Canvas Background Color");
    if (newColor.isValid()) {
        canvas->setBackgroundColor(newColor);
    }
}

void MainWindow::setLineMode() {
    canvas->setDrawMode(Line);
}

void MainWindow::setCircleMode() {
    canvas->setDrawMode(Circle);
}

void MainWindow::setEraserMode() {
    canvas->setDrawMode(Eraser);
}

void MainWindow::setPencilMode() {
    canvas->setDrawMode(Pencil);
}

void MainWindow::setMidpointAlgorithm() {
    canvas->setLineAlgorithm(Midpoint);
}

void MainWindow::setBresenhamAlgorithm() {
    canvas->setLineAlgorithm(Bresenham);
}

void MainWindow::changeThickness(int thickness) {
    canvas->setThickness(thickness);
}
