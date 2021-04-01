#ifndef __STLBFGS_H__
#define __STLBFGS_H__

#include <functional>
#include <vector>
#include <deque>
#include "linesearch.h"

namespace STLBFGS {
    struct Optimizer {
        typedef std::function<void(const std::vector<double>& x, double &f, std::vector<double>& g)> func_grad_eval;

        Optimizer(size_t nvars, func_grad_eval func) : func_grad(func), invH(nvars) {}
        void run(std::vector<double>& sol);

        const func_grad_eval func_grad;

        struct IHessian {
            IHessian(size_t n) : nvars(n) {}
            void mult(const std::vector<double> &g, std::vector<double> &result);
            void add_correction(const std::vector<double>&s, const std::vector<double>& y);

            const size_t nvars;
            size_t history_depth = 10;
            typedef std::deque<std::vector<double>> history;
            history S = {};
            history Y = {};
            double gamma = 1.;
        } invH;
        size_t maxiter = 100; // Maximum number of function evaluations
        double ftol = 1e-6;   // The iteration stops when (f^k - f^{k+1})/max{|f^k|,|f^{k+1}|,1} <= ftol
        double gtol = 1e-14;  // The iteration will stop when max{|g_i|, i = 1, ..., n} <= gtol
    };
}

#endif //__STLBFGS_H__

