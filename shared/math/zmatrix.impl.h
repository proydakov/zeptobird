template<class T>
std::vector<T> zortho_matrix(T left, T right, T bottom, T top, T near, T far)
{
    std::vector<T> matrix(16, 0);

    T r_l = right - left;
    T t_b = top - bottom;
    T f_n = far - near;
    T tx = - (right + left) / (right - left);
    T ty = - (top + bottom) / (top - bottom);
    T tz = - (far + near) / (far - near);

    matrix[0] = 2.0f / r_l;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = tx;

    matrix[4] = 0.0f;
    matrix[5] = 2.0f / t_b;
    matrix[6] = 0.0f;
    matrix[7] = ty;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 2.0f / f_n;
    matrix[11] = tz;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;

    return matrix;
}

template<class T>
std::vector<T> zrotate_around_z_matrix(T radians)
{
    std::vector<T> matrix(16, 0);

    matrix[0] = std::cos(radians);
    matrix[1] = std::sin(radians);
    matrix[2] = 0.0f;

    matrix[4] = -std::sin(radians);
    matrix[5] = +std::cos(radians);
    matrix[6] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;

    matrix[15] = 1.0f;

    return matrix;
}

template<class T>
std::vector<T> zidentity_matrix()
{
    std::vector<T> matrix(16, 0);

    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;

    matrix[15] = 1.0f;

    return matrix;
}
