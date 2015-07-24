#include <iostream> // debugging

#include <sstream>
#include <algorithm>

#include "voronoi.hpp"

#ifndef EPS
#define EPS 1e-6
#endif

namespace voronoi {

point::operator std::string() const {
    std::ostringstream s;
    s << "(" << m_x << "," << m_y << ")";
    return s.str();
}

bool half_plane::is_inside(const point &pt) const {
    return (m_b - m_a).cross(pt - m_a) <= EPS;
}

double triangle_area(const point &a, const point &b, const point &c) {
    return a.cross(b) + b.cross(c) + c.cross(a);
}

bool compute_line_intersection(const point &a1, const point &b1,
    const point &a2, const point &b2, point &in) {

    if(std::fabs((b1-a1).cross(b2-a2)) <= EPS) return false;
    in = a1 + ((a2-a1).cross(b2-a2) / (b1-a1).cross(b2-a2)) * (b1-a1);
    return true;
}

void compute_convex_hull(std::vector<point> &points) {
    std::sort(points.begin(), points.end());

    points.erase(std::unique(points.begin(), points.end()), points.end());

    std::vector<point> up, down; // Upper and lower hulls
    for(unsigned i = 0; i < points.size(); i ++) {
        while(up.size() > 1
            && triangle_area(up[up.size()-2], up.back(), points[i]) >= -EPS)
                up.pop_back();
        while(down.size() > 1
            && triangle_area(down[down.size()-2], down.back(), points[i]) <= EPS)
                down.pop_back();
        up.push_back(points[i]);
        down.push_back(points[i]);
    }

    points = down;
    for(int i = (int)up.size() - 2; i >= 1; i --) points.push_back(up[i]);
}

std::vector<point> compute_half_plane_intersection(
    const std::vector<half_plane> &planes) {

    std::vector<point> line_a(planes.size()), line_b(planes.size());
    for(unsigned i = 0; i < planes.size(); i ++) {
        planes[i].get_defining_line(line_a[i], line_b[i]);
    }

    std::vector<point> intersections;
    point in;
    for(unsigned i = 0; i < planes.size(); i ++) {
        for(unsigned j = i+1; j < planes.size(); j ++) {
            if(compute_line_intersection(line_a[i], line_b[i],
                line_a[j], line_b[j], in)) {
                
                bool valid = true;
                int which = -1;
                for(unsigned k = 0; k < planes.size(); k ++) {
                    valid = valid && planes[k].is_inside(in);
                    if(!valid) { which = k; break; }
                }
                if(valid) intersections.push_back(in);
            }
        }
    }

    /*std::cout << "Computing convex hull of:";
    for(auto pt : intersections) {
        std::cout << " " << pt.to_string();
    }
    std::cout << std::endl;*/
    compute_convex_hull(intersections);

    return intersections;
}

std::vector<std::vector<point>> compute_voronoi(
    const std::vector<point> &points, const std::vector<double> &weights,
    double x_pad, double y_pad) {

    std::vector<std::vector<point>> results;

    double min_x = points.front().x();
    double max_x = min_x;
    double min_y = points.front().y();
    double max_y = min_y;

    for(unsigned i = 0; i < points.size(); i ++) {
        min_x = std::min(min_x, points[i].x());
        min_y = std::min(min_y, points[i].y());
        max_x = std::max(max_x, points[i].x());
        max_y = std::max(max_y, points[i].y());
    }

    min_x -= x_pad;
    min_y -= y_pad;
    max_x += x_pad;
    max_y += y_pad;

    for(unsigned i = 0; i < points.size(); i ++) {
        std::vector<half_plane> planes;

        planes.push_back(half_plane(point(min_x, min_y), point(min_x, max_y)));
        planes.push_back(half_plane(point(min_x, max_y), point(max_x, max_y)));
        planes.push_back(half_plane(point(max_x, max_y), point(max_x, min_y)));
        planes.push_back(half_plane(point(max_x, min_y), point(min_x, min_y)));

        for(unsigned j = 0; j < points.size(); j ++) {
            if(i == j) continue;

            point a = (weights[i] * points[i] + weights[j] * points[j])
                / ((weights[i]+weights[j]));

            point d = (a-points[i]);
            point d_rot(d.y(), -d.x());
            point b = a + d_rot;

            planes.push_back(half_plane(a, b));
        }

        results.push_back(compute_half_plane_intersection(planes));
    }
    
    return results;
}

} // namespace voronoi
