//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

//Novas Bibliotecas
#include<vector>
using std::vector;
#include<string>
using std::string;

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;

        // NEW declarations
        virtual void translate(const Point &t) = 0;
        virtual void rotate(const Point &origin, int degrees) = 0;
        virtual void scale(const Point &origin, int v) = 0;
        virtual SVGElement* clone() const = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;
        void translate(const Point &t) override;
        void rotate(const Point &origin, int degrees) override;
        void scale(const Point &origin, int v) override;
        SVGElement* clone() const override;
        

    protected: // private -> protected
        Color fill;
        Point center;
        Point radius;
    };

    // New Classes & Declarations

    class Circle: public Ellipse{
        public:
        Circle(const Color &fill, const Point &center, const int &radius);
        void draw(PNGImage &img) const override;
        void translate(const Point &t) override;
        void rotate(const Point &origin, int degrees) override;
        void scale(const Point &origin, int v) override;
        SVGElement* clone() const override;
    };

    class Polyline: public SVGElement{
        public:
        Polyline(const vector<Point> &points,const Color &stroke);
        void draw(PNGImage &img) const override;
        void translate(const Point &t) override;
        void rotate(const Point &origin, int degrees) override;
        void scale(const Point &origin, int v) override;
        SVGElement* clone() const override;
        
        protected:
        vector<Point> points;
        Color stroke;
    };

    class Line: public Polyline{
        public:
        Line(int x1, int y1, int x2, int y2, const Color &stroke);
        void draw(PNGImage &img) const override;
        void translate(const Point &t) override;
        void rotate(const Point &origin, int degrees) override;
        void scale(const Point &origin, int v) override;
        SVGElement* clone() const override;

        private:
        int x1,x2,y1,y2;
    };

    class Polygon: public SVGElement{
        public:
        Polygon(const vector<Point> &points, const Color &fill);
        void draw(PNGImage &img) const override;
        void translate(const Point &t) override;
        void rotate(const Point &origin, int degrees) override;
        void scale(const Point &origin, int v) override;
        SVGElement* clone() const override;

        protected:
        vector<Point> points;
        Color fill;
    };

    class Rect: public Polygon{
        public:
        Rect(int x, int y, int width, int height, const Color &fill);        
        void draw(PNGImage &img) const override;
        void translate(const Point &t) override;
        void rotate(const Point &origin, int degrees) override;
        void scale(const Point &origin, int v) override;
        SVGElement* clone() const override;

        private:
        int x, y, width, height;
    };
    class Group: public SVGElement{
        public:
        Group();
        Group(vector<SVGElement*> childs);
        ~Group();
        void draw(PNGImage &img) const override;
        void translate(const Point &t) override;
        void rotate(const Point &origin, int degrees) override;
        void scale(const Point &origin, int v) override; 
        void add_element(SVGElement* elem);
        SVGElement* clone() const override;

        protected:
        vector<SVGElement*> childs;
    };
};

#endif
