#include "SVGElements.hpp"

// Novas Bibliotecas 
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

    Circle::Circle(const Color &fill, const Point &center, const int &radius): Ellipse(fill, center, {radius, radius}){}

    Polyline::Polyline(const vector<Point> &points,const Color &Stroke): points(points), stroke(stroke){}

    Line::Line(int x1, int y1, int x2, int y2, const Color &stroke): Polyline({{x1,y1},{x2,y2}}, stroke){}

    Polygon::Polygon(vector<Point> &points, Color &fill): points(points), fill(fill){}

    Rect::Rect(int &x, int &y, int width, int height, Color &fill): Rect({{x,y},{x+width,y},{x+width,y-height},{x,y-height},{x,y}}, fill){}

    Rect::Rect(vector<Point> vec, Color &fill): Polygon(vec, fill){}

}


int main(){
    std::vector<svg::Point> v = vector<svg::Point>{};
    return 0;
}