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

#pragma once

#include <armadillo>

namespace cpd {

double find_P(const arma::mat& X, const arma::mat& Y, double sigma2,
		float outliers, arma::vec& P1, arma::vec& Pt1, arma::mat& PX,
		arma::mat& P, bool use_fgt, const float epsilon);
}
