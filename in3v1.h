#ifndef IN3V1_H
#define IN3V1_H

/* Public API for in3v1 */

namespace in3v1 {
    void openDiagram(int argc, char* argv[], double minx, double maxx, double miny, double maxy);
    void addPoint(double x, double y);
    void run();
}

#endif // IN3V1_H

