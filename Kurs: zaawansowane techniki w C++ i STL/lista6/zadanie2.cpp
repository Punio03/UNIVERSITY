//
// Created by Jakub Malczak on 21/11/2023.
//
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

class Point {
public:
    double x, y;
    int r, g, b;
    string name;

    Point(double x, double y, int r, int g, int b, std::string name)
            : x(x), y(y), r(r), g(g), b(b), name(std::move(name)) {}

    [[nodiscard]] double luminance() const { return 0.3 * r + 0.59 * g + 0.11 * b; }

    friend ostream& operator<<(ostream& os, const Point& point) {
        os << "Point: " << point.name << " [" << point.x << ", " << point.y << "], "
           << "Color: (" << point.r << ", " << point.g << ", " << point.b << "), "
           << "Luminance: " << point.luminance();
        return os;
    }
};

ostream& operator<<(ostream& os, const list<Point>& points) {
    for (const auto& point : points) {
        os << point << endl;
    }
    return os;
}

//a
void removeLongNamedPoints(list<Point>& points) {
    points.remove_if([](const Point& p) { return p.name.length() > 5; });

    cout << points;
}

//b
void countPointsInQuadrants(const list<Point>& points) {
    int count[4] = {0, 0, 0, 0};

    count[0] = count_if(points.begin(), points.end(), [](const Point& p) {
        return p.x > 0 && p.y > 0;
    });

    count[1] = count_if(points.begin(), points.end(), [](const Point& p) {
        return p.x < 0 && p.y > 0;
    });

    count[2] = count_if(points.begin(), points.end(), [](const Point& p) {
        return p.x < 0 && p.y < 0;
    });

    count[3] = count_if(points.begin(), points.end(), [](const Point& p) {
        return p.x > 0 && p.y < 0;
    });

    cout << "Points in I: " << count[0] << ", II: " << count[1]
         << ", III: " << count[2] << ", IV: " << count[3] << endl;
}

//c
void sortByLuminance(list<Point>& points) {
    points.sort([](const Point& a, const Point& b) {
        return a.luminance() < b.luminance();
    });

    cout << points;
}

//d
void separateAndPrintDarkPoints(list<Point>& points) {
    list<Point> darkPoints;
    copy_if(points.begin(), points.end(), back_inserter(darkPoints),
            [](const Point& p) { return p.luminance() < 64; });

    cout << "Dark Points: " << darkPoints.size() << endl;
    cout << darkPoints;
}

int main() {
    list<Point> points;

    points.emplace_back(24, 33, 162, 111, 17, "fok");
    points.emplace_back(-48, 20, 219, 50, 223, "FXoGg");
    points.emplace_back(-70, -79, 81, 10, 100, "jL");
    points.emplace_back(-10, -79, 167, 163, 19, "VaU");
    points.emplace_back(-65, -49, 74, 3, 194, "FZm");
    points.emplace_back(63, 50, 176, 24, 10, "cmWEfjd");
    points.emplace_back(-42, -8, 55, 51, 59, "fUEPSX");
    points.emplace_back(7, 23, 42, 168, 151, "SQWF");
    points.emplace_back(-21, 84, 65, 23, 254, "rPJ");
    points.emplace_back(-75, 88, 205, 158, 20, "TjQeUes");
    points.emplace_back(61, -97, 70, 49, 129, "PACKMMWmk");
    points.emplace_back(-3, -33, 15, 134, 22, "yIPIJBfJ");
    points.emplace_back(70, 57, 209, 54, 231, "WXAbtmYNY");
    points.emplace_back(-24, -30, 178, 72, 8, "IEXRHMe");
    points.emplace_back(95, -7, 57, 60, 251, "a");
    points.emplace_back(-92, -17, 234, 162, 38, "GUNAKxtJ");
    points.emplace_back(-53, -100, 163, 55, 28, "Tele");
    points.emplace_back(23, -65, 229, 10, 86, "QwF");
    points.emplace_back(-100, -4, 34, 242, 172, "MzTwsH");
    points.emplace_back(87, 51, 153, 162, 94, "kygPJHefB");
    points.emplace_back(76, -18, 232, 244, 180, "xfHIR");
    points.emplace_back(-62, -79, 149, 76, 37, "YRPJL");
    points.emplace_back(-34, 20, 165, 75, 202, "kuZQEyXdsk");

    cout << "A:" << endl;
    removeLongNamedPoints(points);
    cout << endl;

    cout << "B:" << endl;
    countPointsInQuadrants(points);
    cout << endl;

    cout << "C:" << endl;
    sortByLuminance(points);
    cout << endl;

    cout << "D:" << endl;
    separateAndPrintDarkPoints(points);
    cout << endl;
}