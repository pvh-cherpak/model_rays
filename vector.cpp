#include "vector.h"

vector_t::vector_t(double x, double y)
{
    this->x = x;
    this->y = y;
}

vector_t::~vector_t() {}

void vector_t::normalization()
{
    double modul = sqrt(x * x + y * y);
    x /= modul;
    y /= modul;
}
double vector_t::operator*(const vector_t &v2)
{
    return this->x * v2.x + this->y * y;
}

vector_t vector_t::operator*(const double &number)
{
    return vector_t(this->x * number, this->y * number);
}

vector_t vector_t::operator/(const double &number)
{
    return vector_t(this->x / number, this->y / number);
}

vector_t vector_t::operator+(const vector_t &v2)
{
    return vector_t(this->x + v2.x, this->y + v2.y);
}

vector_t vector_t::operator-(const vector_t &v2)
{
    return vector_t(this->x - v2.x, this->y - v2.y);
}

