#pragma once

#include <cmath>
#include <vector>

template<class T>
std::vector<T> zortho_matrix(T left, T right, T bottom, T top, T near, T far);

template<class T>
std::vector<T> zrotate_around_z_matrix(T radians);

template<class T>
std::vector<T> zidentity_matrix();

// impl

#include <math/zmatrix.impl.h>
