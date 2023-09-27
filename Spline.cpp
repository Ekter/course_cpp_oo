#include <iostream>
#include <vector>

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
    for (double x = -0.125; x <= 1.125; x += 0.0625)
    {
        std::cout << "Value for " << x << " is " << spline.get_value(x) << std::endl;
    }
}
