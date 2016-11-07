#include <iostream>
#include <iomanip>
#include <in3v1.h>

using namespace std;

int main(int argc, char *argv[])
{
    FILE *datei ;
    int h = 10;
    double b[100] , m[15] , gleitender[15];
    char filename[] = "//PATH//data.txt";

    datei = fopen(filename, "r");
    in3v1::openDiagram(argc, argv, 0, 15, 0, 15);

           for (int i = 0; i < 100; i++)
           {
              fscanf(datei, "%lf\n", &b[i]);
              std::cout<< i << "." << setprecision(12) << b[i] << '\n';
           }


           int c=89;
           for (int d = 0; d < 10; d++)
           {
               c+=1;
               m[d]=b[c];
           }

           std::cout<< '\n' ;
           for(int e = 1 ; e < h-1 ; e++)
           {

              for(int f =e-1 ; f <= h-1 ; f++)
              {
                 gleitender[e] = gleitender[e] + m[f];
              }

              gleitender[e]=gleitender[e]/10;
              std::cout<< e << "." << gleitender[e] << '\n';
              in3v1::addPoint(e,gleitender[e]);
            }

            in3v1::run();
            fclose(datei);

    return 0;
}
