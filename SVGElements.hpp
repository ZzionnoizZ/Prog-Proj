//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

//Novas Bibliotecas
#include<vector>
using std::vector;

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;

        // NEW declarations
        virtual Point translate(const Point &t) const = 0;
        virtual Point rotate(const Point &origin, int degrees) const = 0;
        virtual Point scale(const Point &origin, int v) const = 0;
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
        Point translate(const Point &t) const override;
        Point rotate(const Point &origin, int degrees) const override;
        Point scale(const Point &origin, int v) const override; 

    private:
        Color fill;
        Point center;
        Point radius;
    };

    // New Classes & Declarations

    class Circle: public Ellipse{
        public:
            Circle(const Color &fill, const Point &center, const int &radius);
            void draw(PNGImage &img) const override;
            Point translate(const Point &t) const override;
            Point rotate(const Point &origin, int degrees) const override;
            Point scale(const Point &origin, int v) const override;
    };

    class Polyline: public SVGElement{
        public:
        Polyline(const vector<Point> &points,const Color &Stroke);
        void draw(PNGImage &img) const override;
        Point translate(const Point &t) const override;
        Point rotate(const Point &origin, int degrees) const override;
        Point scale(const Point &origin, int v) const override;
        
        private:
        vector<Point> points;
        Color stroke;
    };

    class Line: public Polyline{
        public:
        Line(int x1, int y1, int x2, int y2, const Color &stroke);
        void draw(PNGImage &img) const override;
        Point translate(const Point &t) const override;
        Point rotate(const Point &origin, int degrees) const override;
        Point scale(const Point &origin, int v) const override;

        private:
        int x1,x2,y1,y2;
        Color stroke;
    };

    class Polygon: public SVGElement{
        public:
        Polygon(const vector<Point> &points, Color &fill);
        void draw(PNGImage &img) const override;
        Point translate(const Point &t) const override;
        Point rotate(const Point &origin, int degrees) const override;
        Point scale(const Point &origin, int v) const override;

        private:
        vector<Point> points;
        Color fill;
    };

    class Rect: public Polygon{
        public:
        Rect(int x, int y, int width, int height, Color &fill);        
        void draw(PNGImage &img) const override;
        Point translate(const Point &t) const override;
        Point rotate(const Point &origin, int degrees) const override;
        Point scale(const Point &origin, int v) const override;

        private:
        int x, y, width, height;
        Color fill;
    };
};

#endif
