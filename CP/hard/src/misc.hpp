#ifndef MISC_HPP
#define MISC_HPP

#include <cmath>
#include <cstdio>
#include <vector>

const double STOP_DATA = 11235813;
const size_t GEODATA_SIZE = sizeof(uint32_t) + 2 * sizeof(double);

struct node_t {
    uint32_t id;
    double lon;
    double lat;
};

bool operator < (const node_t & lhs, const node_t & rhs) {
    return lhs.id < rhs.id;
}

const double SPHERE_RADIUS = 6371e3;
const double MAX_ANGLE = 180.0;
const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-6;

double radians(double angle) {
    return angle * PI / MAX_ANGLE;
}

double geo_dist(const node_t & lhs, const node_t & rhs) {
    double phi_a = radians(lhs.lon);
    double phi_b = radians(rhs.lon);
    double delta = radians(lhs.lat - rhs.lat);
    double cos_d = std::sin(phi_a) * std::sin(phi_b) + std::cos(phi_a) * std::cos(phi_b) * std::cos(delta);
    double d = std::acos(cos_d);
    return std::isnan(d) ? 0 : SPHERE_RADIUS * d;
}

struct edge_t {
    uint32_t id_from;
    uint32_t id_to;
};

bool operator < (const edge_t & lhs, const edge_t & rhs) {
    if (lhs.id_from != rhs.id_from) {
        return lhs.id_from < rhs.id_from;
    } else {
        return lhs.id_to < rhs.id_to;
    }
}

struct euristic_t {
    uint32_t id;
    double distance;
    double path;

    euristic_t(const uint32_t & u_id, const node_t & u, const node_t & v, const double & path_to) {
        id = u_id;
        distance = geo_dist(u, v);
        path = path_to;
    }
};

bool operator < (const euristic_t & lhs, const euristic_t & rhs) {
    if (std::abs((lhs.path + lhs.distance) - (rhs.path + rhs.distance)) > EPS) {
        return lhs.path + lhs.distance > rhs.path + rhs.distance;
    } else if (std::abs(lhs.path - rhs.path) > EPS) {
        return lhs.path > rhs.path;
    } else {
        return lhs.id < rhs.id;
    }
}

#endif /* MISC_HPP */
