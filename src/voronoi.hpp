#ifndef VORONOI_HPP
#define VORONOI_HPP

#include <vector>
#include <string>

namespace voronoi {

class point {
private:
    double m_x, m_y;
public:
    point(double x = 0, double y = 0) : m_x(x), m_y(y) {}

    double x() const { return m_x; }
    double y() const { return m_y; }

    point &operator+=(const point &pt) {
        m_x += pt.m_x;
        m_y += pt.m_y;
        return *this;
    }
    point &operator-=(const point &pt) {
        m_x -= pt.m_x;
        m_y -= pt.m_y;
        return *this;
    }
    point &operator*=(double c) {
        m_x *= c;
        m_y *= c;
        return *this;
    }
    point &operator/=(double c) {
        m_x /= c;
        m_y /= c;
        return *this;
    }

    double dot(const point &pt) const {
        return pt.m_x*m_x + pt.m_y*m_y;
    }

    double cross(const point &pt) const {
        return m_x*pt.m_y - m_y*pt.m_x;
    }

    bool operator<(const point &pt) const {
        if(m_x < pt.m_x) return true;
        if(m_x == pt.m_x) return m_y < pt.m_y;
        return false;
    }

    bool operator==(const point &pt) const {
        return m_x == pt.m_x && m_y == pt.m_y;
    }

    operator std::string() const;
    std::string to_string() const { return this->operator std::string(); }
};

class half_plane {
private:
    point m_a, m_b;
public:
    half_plane(const point &a, const point &b) : m_a(a), m_b(b) {}

    bool is_inside(const point &pt) const;
    void get_defining_line(point &a, point &b) const { a = m_a, b = m_b; }
};

double triangle_area(const point &a, const point &b, const point &c);
bool compute_line_intersection(const point &a1, const point &b1,
    const point &a2, const point &b2, point &in);
void compute_convex_hull(std::vector<point> &points);
std::vector<point> compute_half_plane_intersection(
    const std::vector<half_plane> &planes);

std::vector<std::vector<point>> compute_voronoi(
    const std::vector<point> &points, const std::vector<double> &weights,
    double x_pad = 1, double y_pad = 1);

} // namespace voronoi

inline voronoi::point operator+(const voronoi::point &pt1,
    const voronoi::point &pt2) {

    return voronoi::point(pt1.x() + pt2.x(), pt1.y() + pt2.y());
}

inline voronoi::point operator-(const voronoi::point &pt1,
    const voronoi::point &pt2) {

    return voronoi::point(pt1.x() - pt2.x(), pt1.y() - pt2.y());
}

inline voronoi::point operator*(const voronoi::point &pt1, double c) {
    return voronoi::point(pt1.x() * c, pt1.y() * c);
}

inline voronoi::point operator*(double c, const voronoi::point &pt1) {
    return voronoi::point(pt1.x() * c, pt1.y() * c);
}

inline voronoi::point operator/(const voronoi::point &pt1, double c) {
    return voronoi::point(pt1.x() / c, pt1.y() / c);
}

#endif
