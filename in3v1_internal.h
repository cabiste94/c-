#ifndef IN3V1_INTERNAL_H
#define IN3V1_INTERNAL_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QWidget>
#include <vector>

namespace in3v1 {
namespace internal {

class Diagram: public QWidget
{
    struct Point {
        double x, y;
    };

    static const int BORDER;
    static const double INITIAL_WIDTH; // portion of screen size

    double minx, maxx, miny, maxy, scale;
    std::vector<Point> points;

    // coord transforms
    void setScale();
    int tx(double x);
    int ty(double y);

    // Overrides from QWidget
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;

public:
    Diagram(double minx, double maxx, double miny, double maxy);
    ~Diagram();

    void addPoint(double x, double y);

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QVBoxLayout *layout;
    //Diagram *diagram;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Diagram *addDiagram(double minx, double maxx, double miny, double maxy);
};

} // internal
} // in3v1

#endif // IN3V1_INTERNAL_H

