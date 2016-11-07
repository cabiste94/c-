#include <vector>
#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <in3v1.h>
#include <in3v1_internal.h>

namespace in3v1 {

/**************** Diagram implementation **************************/

namespace internal {
const int Diagram::BORDER = 10;
const double Diagram::INITIAL_WIDTH = 0.5;

Diagram::Diagram(double minx, double maxx, double miny, double maxy)
{
    /* make sure that the cartesian origin is always in the diagram */
    if (minx > 0)
        minx = 0;
    if (maxx < 0)
        maxx = 0;
    if (miny > 0)
        miny = 0;
    if (maxy < 0)
        maxy = 0;
    this->minx = minx;
    this->maxx = maxx;
    this->miny = miny;
    this->maxy = maxy;
    setMinimumWidth(2*BORDER+10);
    setMinimumHeight(2*BORDER+10);
}

void Diagram::setScale()
{
    /* Compute aspect ratio and scaling,
     * to always fit all points onto screen
     */
    double deltax = maxx-minx;
    double deltay = maxy-miny;
    double ratio = deltay/deltax;

    int w = width() - 2*BORDER;
    int h = height() - 2*BORDER;

    double qratio = 1.0*h/w;
    if(ratio > qratio) {
        // the diagram is taller than the window
        scale = h / deltay;
    } else {
        // the diagram is wider than the window
        scale = w / deltax;
    }
}

int Diagram::tx(double x)
{
    return (x-minx)*scale + BORDER;
}

int Diagram::ty(double y)
{
    return height() - BORDER - (y-miny)*scale;
}

Diagram::~Diagram()
{
}

void Diagram::addPoint(double x, double y)
{
    Point p;
    p.x = x;
    p.y = y;
    points.push_back(p);
}

void Diagram::paintEvent(QPaintEvent *)
{
    setScale();
    QPainter painter(this);

    // X axis
    painter.drawLine(tx(minx), ty(0), tx(maxx), ty(0));
    painter.drawLine(tx(maxx)-10, ty(0)-3, tx(maxx), ty(0));
    painter.drawLine(tx(maxx)-10, ty(0)+3, tx(maxx), ty(0));
    // Y axis
    painter.drawLine(tx(0), ty(miny), tx(0), ty(maxy));
    painter.drawLine(tx(0)-3, ty(maxy)+10, tx(0), ty(maxy));
    painter.drawLine(tx(0)+3, ty(maxy)+10, tx(0), ty(maxy));

    // points
    for (std::vector<Point>::iterator it = points.begin(); it != points.end(); it++)
    {
        int x = tx(it->x);
        int y = ty(it->y);
        painter.drawLine(x-2, y, x+2, y);
        painter.drawLine(x, y-2, x, y+2);
    }
}

QSize Diagram::sizeHint() const
{
    QRect r = QApplication::desktop()->screenGeometry();
    double ratio = (maxy-miny)/(maxx-minx);
    int desired_width = INITIAL_WIDTH* r.width();
    QSize result(desired_width+2*BORDER, ratio*desired_width+2*BORDER);
    return result;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *main = new QWidget();
    layout = new QVBoxLayout;
    main->setLayout(layout);
    setCentralWidget(main);
}

MainWindow::~MainWindow()
{
}

Diagram *MainWindow::addDiagram(double minx, double maxx, double miny, double maxy)
{
    Diagram *result = new Diagram(minx, maxx, miny, maxy);
    layout->addWidget(result);
    return result;
}
} // internal

/*********************** in3v1 API *************************/

QApplication *app;
internal::MainWindow *root;
internal::Diagram *dia;

void openDiagram(int argc, char* argv[], double minx, double maxx, double miny, double maxy)
{
    app = new QApplication(argc, argv);
    root = new internal::MainWindow();
    dia = root->addDiagram(minx, maxx, miny, maxy);
    root->show();
}

void addPoint(double x, double y)
{
    dia->addPoint(x, y);
}

void run()
{
    app->exec();
}

} // in3v1
