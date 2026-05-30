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


    void Ellipse::translate(const Point &t){
        center = center.translate(t);
    }

    void Ellipse::rotate(const Point &origin, int degrees){
        center = center.rotate(origin, degrees);
    }

    void Ellipse::scale(const Point &origin, int v){
        center = center.scale(origin,v);
        radius = radius.scale({0, 0}, v);
    }

    SVGElement* Ellipse::clone() const{
        return new Ellipse(*this);
    }

    // Circle


    Circle::Circle(const Color &fill, const Point &center, const int &radius): Ellipse(fill, center, {radius, radius}){}
    
    void Circle::translate(const Point &t){
        Ellipse::translate(t);
    }
    void Circle::rotate(const Point &origin, int degrees){
        Ellipse::rotate(origin, degrees);
    }

    void Circle::scale(const Point &origin, int v){
        Ellipse::scale(origin,v);
    }

    void Circle::draw(PNGImage &img) const{
        Ellipse::draw(img);
    }

    SVGElement* Circle::clone() const{
        return new Circle(*this);
    }

    // Polyline


    Polyline::Polyline(const vector<Point> &points,const Color &stroke): points(points), stroke(stroke){}

    void Polyline::translate(const Point &t){
        for (Point& p: points){
            p = p.translate(t);
        }
    }

    void Polyline::rotate(const Point &origin, int degrees){
        for (Point& p: points){
            p = p.rotate(origin, degrees);
        }
    }

    void Polyline::scale(const Point &origin, int v){
        for (Point &p : points){
            p = p.scale(origin, v);
        } 
    }

    void Polyline::draw(PNGImage &img) const{
        for (size_t i=1; i<points.size(); i++){
            img.draw_line(points[i-1], points[i], stroke);
        }
    }

    SVGElement* Polyline::clone() const{
        return new Polyline(*this);
    }

    // Line


    Line::Line(int x1, int y1, int x2, int y2, const Color &stroke): Polyline({{x1,y1},{x2,y2}}, stroke){}

    void Line::translate(const Point &t){
        Polyline::translate(t);
    } 

    void Line::rotate(const Point &origin, int degrees){
        Polyline::rotate(origin, degrees);
    }

    void Line::scale(const Point &origin, int v){
        Polyline::scale(origin, v); 
    }

    void Line::draw(PNGImage &img) const{
        Polyline::draw(img);
    }

    SVGElement* Line::clone() const{
        return new Line(*this);
    }

    // Polygon


    Polygon::Polygon(const vector<Point> &points, const Color &fill): points(points), fill(fill){}

    void Polygon::translate(const Point &t){
        for (Point& p: points){
            p = p.translate(t);
        }
    }

    void Polygon::rotate(const Point &origin, int degrees){
        for (Point& p: points){
            p = p.rotate(origin, degrees);
        }
    }

    void Polygon::scale(const Point &origin, int v){
        for (Point &p : points){
            p = p.scale(origin, v);
        } 
    }

    void Polygon::draw(PNGImage &img) const{
        img.draw_polygon(points, fill);
    }

    SVGElement* Polygon::clone() const{
        return new Polygon(*this);
    }

    // Rect 


    Rect::Rect(int x, int y, int width, int height, const Color &fill): Polygon({{x,y},{x+width-1,y},{x+width-1,y+height-1},{x,y+height-1}}, fill), x(x), y(y), width(width), height(height){}

    void Rect::translate(const Point &t){
        Polygon::translate(t);
    } 

    void Rect::rotate(const Point &origin, int degrees){
        Polygon::rotate(origin, degrees);
    }

    void Rect::scale(const Point &origin, int v){
        Polygon::scale(origin, v); 
    }

    void Rect::draw(PNGImage &img) const{
        Polygon::draw(img);
    }

    SVGElement* Rect::clone() const{
        return new Rect(*this);
    }

    // Group

    Group::Group():SVGElement(){}

    Group::Group(vector<SVGElement*> childs): childs(childs){}

    Group::~Group(){
        for (SVGElement* v: childs){
            delete v;
        }
        childs.clear();
    }

    void Group::draw(PNGImage &img) const{
        for (const SVGElement* v: childs){
            v->draw(img);
        }
    }

    void Group::translate(const Point &t){
        for (SVGElement* child : childs) {
            child->translate(t);
        }
    }

    void Group::rotate(const Point &origin, int degrees){
        for (SVGElement* child : childs) {
            child->rotate(origin, degrees);
        }
    }

    void Group::scale(const Point &origin, int v){
        for (SVGElement* child : childs) {
            child->scale(origin, v);
        }
    }

    void Group::add_element(SVGElement* v) {
        if (v != nullptr) {
            childs.push_back(v);
        }
    }

    SVGElement* Group::clone() const{
        Group* g = new Group();
        for (SVGElement* v:childs){
            g->add_element(v->clone());
        }
        return g;
    }
}
