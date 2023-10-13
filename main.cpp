#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include "Spline.h"
#include <Eigen/Dense>

int main(int argc, char *argv[])
{
    //
    // Important only N points are given, the point N+1 is implicitly defined
    // see section 1.1.1 on boundary condition
    //
    std::vector<double> xs{0., 0.16, 0.42, 0.6425, 0.8575};
    std::vector<double> ys{100., 183., 235., 40., 15.};
    Spline spline(xs, ys);
    Linear linear(xs, ys);
    std::cout << std::setw(17) << "X value" << std::setw(6) << ":("<<std::setw(10)<<"Spline," << std::setw(10)
              << "Linear)" << std::endl;
    for (double x = -0.125; x <= 1.125; x += 0.0625)
    {
        std::cout << "Value for " <<std::setw(7)<< x << " is :(" <<std::setw(9)<< spline(x) << "," <<std::setw(9)<< linear(x) << ")" << std::endl;
    }
    std::cout<< std::endl << "Writing to file spline.csv with 0.00001 definition" << std::endl;
    std::ofstream file("spline.csv");
    for (double x = 0; x < 1.125; x += 0.00001)
    {
        file << x << "," << spline.get_value(x) << "," << linear.get_value(x) << std::endl;
    }
    file.close();
    std::cout << "Done. Goodbye!" << std::endl;
    return 0;
}
