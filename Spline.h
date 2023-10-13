#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>

class FunctionInterpolator
{
public:
    virtual double get_value(const double x) const = 0;
    double operator()(const double x) const
    {
        return get_value(x);
    }
};

class Linear : public FunctionInterpolator
{
private:
    std::vector<double> as_;
    std::vector<double> bs_;
    std::vector<double> xs_;

public:
    Linear(const std::vector<double> &xs, const std::vector<double> &ys) : xs_{xs}, bs_{ys}
    {
        xs_.push_back(1.0);
        bs_.push_back(bs_[0]);
        for (int i = 0; i <= xs_.size() - 2; i++)
        {
            double ai = (bs_[i + 1] - bs_[i]) / (xs_[i + 1] - xs_[i]);
            as_.push_back(ai);
        }
    }
    ~Linear() = default;

    double get_value(const double x) const
    {
        if (x <= 0.0 || x > 1.0)
        {
            return bs_[0];
        }
        std::vector<double>::const_iterator it = xs_.begin();
        while (*it < x)
        {
            it++;
        }

        int i = it - xs_.begin() - 1;
        auto delta_x = x - xs_[i];
        auto y = as_[i] * delta_x + bs_[i];

        return y;
    }
};

class Spline : public FunctionInterpolator
{
private:
    int dim_;
    std::vector<double> as_;
    std::vector<double> bs_;
    std::vector<double> cs_;
    std::vector<double> ds_;
    std::vector<double> xs_;

public:
    Spline(const std::vector<double> &xs, const std::vector<double> &ys) : xs_{xs}, ds_{ys}
    {
        dim_ = xs.size();
        // using same notation as the helper document
        Eigen::MatrixXd m(3 * dim_, 3 * dim_);
        Eigen::VectorXd v(3 * dim_);

        m.setZero();
        v.setZero();

        // value at x = 1.0
        xs_.push_back(1.0);
        ds_.push_back(ds_[0]);

        // fill V and M
        for (int i = 0; i < dim_ - 1; i++)
        {
            double dx = xs_[i + 1] - xs_[i];

            m.block<1, 3>(3 * i, 3 * i) << pow(dx, 3), pow(dx, 2), dx;
            m.block<1, 6>(3 * i + 1, 3 * i) << 3 * pow(dx, 2), 2 * dx, 1, 0, 0, -1;
            m.block<1, 5>(3 * i + 2, 3 * i) << 6 * dx, 2, 0, 0, -2;
            v.block<1, 1>(3 * i, 0) << ds_[i + 1] - ds_[i];
        }

        //Last data point
        double dx = xs_[dim_] - xs_[dim_ - 1];
        v.block<1, 1>(3 * dim_ - 3, 0) << ds_.back() - *(ds_.end() - 2);
        m.block<1, 3>(3 * dim_ - 3, 3 * dim_ - 3) << pow(dx, 3), pow(dx, 2), dx;
        m.block<1, 1>(dim_ * 3 - 2, 2) << 1;
        m.block<1, 3>(3 * dim_ - 1, 3 * dim_ - 3) << 3 * pow(dx, 2), 2 * dx, 1;

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
            auto ni = 3 * i;
            as_.push_back(u[ni + 0]);
            bs_.push_back(u[ni + 1]);
            cs_.push_back(u[ni + 2]);
        }
    }
    ~Spline() = default;

    double get_value(const double x) const
    {
        if (x <= 0.0 || x > 1.0)
        {
            return ds_[0];
        }
        std::vector<double>::const_iterator it = xs_.begin();
        while (*it < x)
        {
            it++;
        }

        int i = it - xs_.begin() - 1;
        auto delta_x = x - xs_[i];
        auto y = as_[i] * delta_x * delta_x * delta_x + bs_[i] * delta_x * delta_x + cs_[i] * delta_x + ds_[i];

        return y;
    }
};
