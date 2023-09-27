#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>

struct Spline1
{
    std::vector<double> as_;
    std::vector<double> bs_;
    std::vector<double> xs_;

    Spline1(const std::vector<double> &xs, const std::vector<double> &ys) : xs_{xs}, bs_{ys}
    {
        xs_.push_back(1.0);
        bs_.push_back(bs_[0]);
        // std::cout << "xs_ size: " << xs_.size() << std::endl;

        // 7 lines
        for (int i = 0; i <= xs_.size() - 2; i++)
        {
            double ai = (bs_[i + 1] - bs_[i]) / (xs_[i + 1] - xs_[i]);
            as_.push_back(ai);
            // std::cout << "ai: " << ai << std::endl;
            // std::cout << "bs_[i]: " << bs_[i] << std::endl;
            // std::cout << "xs_[i]: " << xs_[i] << std::endl;
            // std::cout << "bs_[i + 1]: " << bs_[i + 1] << std::endl;
            // std::cout << "xs[i + 1]: " << xs[i + 1] << std::endl;
        }
        // std::cout << "as_ size: " << as_.size() << std::endl;
        // std::cout << "bs_ size: " << bs_.size() << std::endl;
        // std::cout << "xs_: " << std::endl;
        // for (auto a : xs_)
        // {
        //     printf("%f\n", a);
        // }
    }

    double get_value(const double x) const
    {
        if (x <= 0.0 || x > 1.0)
        {
            return bs_[0];
        }
        // 5 lines of code

        std::vector<double>::const_iterator it = xs_.begin();
        while (*it < x)
        {
            it++;
        }

        int i = it - xs_.begin() - 1;
        // std::cout << "i: " << i << std::endl;

        auto delta_x = x - xs_[i];
        auto y = as_[i] * delta_x + bs_[i];

        return y;
    }
};

struct Spline
{
    int dim_;
    std::vector<double> as_;
    std::vector<double> bs_;
    std::vector<double> cs_;
    std::vector<double> ds_;
    std::vector<double> xs_;

    Spline(const std::vector<double> &xs, const std::vector<double> &ys) : xs_{xs}, ds_{ys}
    {
        dim_ = xs.size();
        // using same notation as the helper document
        Eigen::MatrixXd m(3 * dim_, 3 * dim_);
        Eigen::VectorXd v(3 * dim_);

        m.setZero();
        v.setZero();

        // value at x = 1.0
        auto xN = 1.0;
        xs_.push_back(xN);
        ds_.push_back(ds_[0]);

        // about 25 lines of code here

        // fill V
        // for (int i = 0; i < dim_; i++)
        // {
        //     v.block<1, 1>(3 * i, 0) << ds_[i+1]-ds_[i];
        //     // double dx = xs_[i + 1] - xs_[i];
        //     // v.block<1, 1>(3 * i, 0) << (ds_[i + 1] - ds_[i]) / dx - (ds_[i] - xs_[i]);
        // }

    
        // fill M

        for (int i = 0; i < dim_ - 1; i++)
        {
            double dx = xs_[i + 1] - xs_[i];

            m.block<1, 3>(3 * i, 3 * i) << pow(dx, 3), pow(dx, 2), dx;
            m.block<1, 6>(3 * i + 1, 3 * i) << 3 * pow(dx, 2), 2 * dx, 1, 0, 0, -1;
            m.block<1, 5>(3 * i + 2, 3 * i) << 6 * dx, 2, 0, 0, -2;
            v.block<1, 1>(3 * i, 0) << ds_[i+1]-ds_[i];
        }
        v.block<1, 1>(3 * dim_-3, 0) << ds_.back()-*(ds_.end()-2);

        // print m and v
        std::cout << "m: " << std::endl;
        std::cout << m << std::endl;
        std::cout << "v: " << std::endl;
        std::cout << v << std::endl;

        // Solve M.U=V =>  U = M^{-1}.V
        Eigen::VectorXd u = m.fullPivHouseholderQr().solve(v);

        // Fill in the ai, bi and ci

        for (size_t i = 0; i < dim_; ++i)
        {
            auto bi = 3 * i;
            as_.push_back(u[bi + 0]);
            bs_.push_back(u[bi + 1]);
            cs_.push_back(u[bi + 2]);
        }
    }

    double get_value(const double x) const
    {
        if (x <= 0.0 || x > 1.0)
        {
            return ds_[0];
        }
        // 5 lines of code

        std::vector<double>::const_iterator it = xs_.begin();
        while (*it < x)
        {
            it++;
        }

        int i = it - xs_.begin() - 1;
        // std::cout << "i: " << i << std::endl;

        auto delta_x = x - xs_[i];
        auto y = as_[i] * delta_x * delta_x * delta_x + bs_[i] * delta_x * delta_x + cs_[i] * delta_x + ds_[i];

        return y;
    }
};