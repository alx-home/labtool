/******************************************************************************
* Coherent Point Drift
* Copyright (C) 2014 Pete Gadomski <pete.gadomski@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
******************************************************************************/

#include <gflags/gflags.h>

#include <cpd/nonrigid.hpp>
#include <cpd/nonrigid_lowrank.hpp>
#include <cpd/rigid.hpp>


using namespace cpd;


DEFINE_string(method, "nonrigid_lowrank", "Registration method");
DEFINE_double(tol, DefaultTolerance, "Tolerance ctriterium");
DEFINE_int32(max_it, DefaultMaxIterations, "Maximum number of iterations");
DEFINE_double(outliers, DefaultOutliers, "The weight of noise and outliers");
DEFINE_bool(fgt, DefaultFgt, "Use a Fast Gauss Transform");
DEFINE_double(epsilon, DefaultEpsilon,
              "The tolerance of the Fast Gauss Transform");
DEFINE_double(beta, DefaultBeta, "Std of Gaussian filter");
DEFINE_double(lambda, DefaultLambda, "Regularization weight");
DEFINE_double(numeig, DefaultNumeig, "Number of the largest eigenvectors to "
                                     "use, try NumPoints^(1/2). If zero, will "
                                     "be auto-calculated.");
DEFINE_bool(include_deltas, true, "Include change vectors for each point.");
DEFINE_double(z_exaggeration, DefaultZExaggeration,
              "Z-dimension exaggeration, use for flat datasets");


int main(int argc, char** argv) {
    gflags::SetUsageMessage("usage: cpd file1.txt file2.txt");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    if (argc == 1) {
        gflags::ShowUsageWithFlags("cpd");
        return 0;
    }
    if (argc != 3) {
        std::cerr << "ERROR: cpd requires two input files" << std::endl;
        gflags::ShowUsageWithFlags("cpd");
        return 1;
    }
    std::string fileX = argv[1];
    std::string fileY = argv[2];
    arma::mat X, Y;
    if (!X.load(fileX)) {
        std::cerr << "ERROR: unable to open file '" << fileX << "'"
                  << std::endl;
        return 1;
    }
    if (!Y.load(fileY)) {
        std::cerr << "ERROR: unable to open file '" << fileY << "'"
                  << std::endl;
        return 1;
    }

    std::unique_ptr<cpd::Registration> reg;
    if (FLAGS_method == "nonrigid_lowrank") {
        reg = std::unique_ptr<cpd::Registration>(new cpd::NonrigidLowrank(
            FLAGS_tol, FLAGS_max_it, FLAGS_outliers, FLAGS_fgt, FLAGS_epsilon,
            FLAGS_beta, FLAGS_lambda, FLAGS_numeig));
    } else if (FLAGS_method == "nonrigid") {
        reg = std::unique_ptr<cpd::Registration>(new cpd::Nonrigid(
            FLAGS_tol, FLAGS_max_it, FLAGS_outliers, FLAGS_fgt, FLAGS_epsilon,
            FLAGS_beta, FLAGS_lambda));
    } else if (FLAGS_method == "rigid") {
        reg = std::unique_ptr<cpd::Registration>(new cpd::Rigid(
            FLAGS_tol, FLAGS_max_it, FLAGS_outliers, FLAGS_fgt, FLAGS_epsilon));
    } else {
        std::cerr << "ERROR: unsuppored registration method '" << FLAGS_method
                  << "'" << std::endl;
        return 1;
    }

    reg->set_z_exaggeration(FLAGS_z_exaggeration);
    cpd::Registration::ResultPtr result = reg->run(X, Y);

    arma::mat output(result->Y);
    if (FLAGS_include_deltas) {
        output.insert_cols(output.n_cols, Y - output);
    }

    output.save(std::cout, arma::csv_ascii);

    return 0;
}
