//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
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

    private:
        Color fill;
        Point center;
        Point radius;
    };

    // New Classes & Declarations

    class Circle: public Ellipse{
        public:
            Circle(const Color &fill, const Point &center, const int &radius);
    };

    class Polyline{
        public:
        Polyline(const vector<Point> &points,const Color &Stroke);
        
        private:
        vector<Point> points;
        Color stroke;
    };

    class Line: public Polyline{
        public:
        Line(int x1, int y1, int x2, int y2, const Color &stroke);

        private:
        int x1,x2,y1,y2;
        Color stroke;
    };

    class Polygon{
        public:
        Polygon(vector<Point> &points, Color &fill);

        private:
        vector<Point> points;
        Color fill;
    };

    class Rect: public Polygon{
        public:
        Rect(int &x, int &y, int width, int height, Color &fill);
        Rect(vector<Point> vec, Color& fill);

        private:
        int x, y, width, height;
    };
}
#endif
