#include "SVGElements.hpp"

// Novas Bibliotecas
#include"Point.hpp"
#include <iostream>
#include <sstream>
#include <vector>
using std::vector;

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    // @todo provide the implementation of SVGElement derived classes
    // HERE -->
    // void SVGElement::draw(PNGImage &img) const = 0{


    // Ellipse

    Point Ellipse::translate(const Point &t) const{
        return center.translate(t);
    }

    Point Ellipse::rotate(const Point &origin, int degrees) const{
        return center.rotate(origin, degrees);
    }

    Point Ellipse::scale(const Point &origin, int v) const{
        return center.scale(origin,v);
    }

    // Circle

    Circle::Circle(const Color &fill, const Point &center, const int &radius): Ellipse(fill, center, {radius, radius}){}

    void Circle::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    
    Point Circle::translate(const Point &t) const{
        return Ellipse::translate(t);
    }
    Point Circle::rotate(const Point &origin, int degrees) const{
        return Ellipse::rotate(origin, degrees);
    }

    Point Circle::scale(const Point &origin, int v) const{
        return Ellipse::scale(origin,v);
    }

    // Polyline

    Polyline::Polyline(const vector<Point> &points,const Color &stroke): points(points), stroke(stroke){}

    void Polyline::draw(PNGImage &img) const
    {
        for (size_t i=1; i<points.size(); i++){
            img.draw_line(points[i-1], points[i], stroke);
        }
    }

    Point Polyline::translate(const Point &t) const{}

    Point Polyline::rotate(const Point &origin, int degrees) const{}

    Point Polyline::scale(const Point &origin, int v) const{}

    // Line


    Line::Line(int x1, int y1, int x2, int y2, const Color &stroke): Polyline({{x1,y1},{x2,y2}}, stroke){}

    void Line::draw(PNGImage &img) const
    {
        img.draw_line({x1,y1},{x2,y2}, stroke);
    }

    Point Line::translate(const Point &t) const{} // RECURSIVIDADE !!

    Point Line::rotate(const Point &origin, int degrees) const{}

    Point Line::scale(const Point &origin, int v) const{}

    // Polygon


    Polygon::Polygon(const vector<Point> &points, Color &fill): points(points), fill(fill){}

    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }

    Point Polygon::translate(const Point &t) const{}

    Point Polygon::rotate(const Point &origin, int degrees) const{}

    Point Polygon::scale(const Point &origin, int v) const{}


    // Rect 


    Rect::Rect(int x, int y, int width, int height, Color &fill): Polygon({{x,y},{x+width,y},{x+width,y-height},{x,y+height},{x,y}}, fill), x(x), y(y), width(width), height(height){}

    void Rect::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }

    Point Rect::translate(const Point &t) const{}

    Point Rect::rotate(const Point &origin, int degrees) const{}

    Point Rect::scale(const Point &origin, int v) const{}
}
