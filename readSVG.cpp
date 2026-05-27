
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

// Novas Bibliotecas
#include<sstream>

using namespace std;
using namespace tinyxml2;

// declaração de novas funções
svg::Point Recolher(string s){}

namespace svg
{
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        // TODO complete code -->

        //criar func que retorna pontos

        XMLElement *g = xml_elem->FirstChildElement();
        for (XMLElement *elemento = g->FirstChildElement(); elemento != nullptr; elemento = elemento->NextSiblingElement()){
            string name = elemento->Name();
            
            if (name == "ellipse"){
                int cx = elemento->IntAttribute("cx");
                int cy = elemento->IntAttribute("cy");
                const Point center = {cx, cy};
                int rx = elemento->IntAttribute("rx");
                int ry = elemento->IntAttribute("ry");
                const Point radius = {rx, ry};
                const char* fill = elemento->Attribute("fill");
                Color cor = parse_color(fill ? fill : "black");
                svg_elements.push_back(new Ellipse(cor,center,radius));
            }
            
            else if (name == "circle"){
                int cx = elemento->IntAttribute("cx");
                int cy = elemento->IntAttribute("cy");
                const Point center = {cx, cy};
                int r = elemento->IntAttribute("r");
                const char* fill = elemento->Attribute("fill");
                Color cor = parse_color(fill ? fill : "black");
                svg_elements.push_back(new Circle(cor,center,r));
            }

            else if (name == "polyline"){
                std::istringstream pontos(elemento-> Attribute("points"));
                string ponto, func, dados;
                vector<Point> points;
                string trans = elemento->Attribute("transform");
                std::istringstream t(trans);
                char b1 = '(', b2 = ')';
                while (pontos >> ponto){
                    Point p =Recolher(ponto);
                        if (!trans.empty()){
                            while (t >> func >> b1 >> dados >> b2){
                                if (func == "translate"){
                                    std::istringstream d(dados);
                                    Point t;
                                    string x1, y1;
                                    while (d >> x1 >> y1){
                                        int x_1 = std::stoi(x1);
                                        int y_1 = std::stoi(y1);
                                        t = {x_1, y_1};
                                    }
                                    p.translate(t);
                                }
                                else if (func == "rotate"){
                                    int degree = std::stoi(dados);
                                    string trans_or = elemento->Attribute("transform-origin");
                                    Point o = Recolher(trans_or);
                                    p.rotate(o, degree);
                                }
                            }
                        }   
                    points.push_back(p);
                }
                const char* stroke = elemento->Attribute("stroke");
                Color cor = parse_color(stroke ? stroke : "black");
                svg_elements.push_back(new Polyline(points, cor));
                
            }

            else if (name == "line"){
                int x1 = elemento->IntAttribute("x1");
                int y1 = elemento->IntAttribute("y1");
                int x2 = elemento->IntAttribute("x2");
                int y2 = elemento->IntAttribute("y2");
                string func, dados;
                vector<Point> points;
                string trans = elemento->Attribute("transform");
                std::istringstream t(trans);
                char b1 = '(', b2 = ')';
                while (t >> func >> b1 >> dados >> b2){
                    if (!trans.empty()){
                        Point p1 = {x1, y1};
                        Point p2 = {x2, y2};
                        if (trans ==  "translate"){
                            p1.translate(Recolher(dados));
                            p2.translate(Recolher(dados));
                        }
                        if (trans == "rotate"){
                            int degree = std::stoi(dados);
                            string trans_or = elemento->Attribute("transform-origin");
                            Point o = Recolher(trans_or);
                            p1.rotate(o, degree);
                            p2.rotate(o, degree);
                        }
                    }
                }
                const char* stroke = elemento->Attribute("stroke");
                Color cor = parse_color(stroke ? stroke : "black");
                svg_elements.push_back(new Line(x1, y1, x2, y2, cor));
            }

            else if (name == "polygon"){
                std::istringstream pontos(elemento-> Attribute("points"));
                string ponto;
                vector<Point> points;
                while (pontos >> ponto){
                    char v=',';
                    string x, y;
                    std::istringstream point(ponto);
                    while (point >> x >> v >> y){
                        int x_ = std::stoi(x);
                        int y_ = std::stoi(y);
                        points.push_back({x_,y_});
                    }
                }
                const char* fill = elemento->Attribute("fill");
                Color cor = parse_color(fill ? fill : "black");
                svg_elements.push_back(new Polygon(points, cor));
            }

            else if (name == "rect"){
                int x = elemento->IntAttribute("x");
                int y = elemento->IntAttribute("y");
                int width = elemento->IntAttribute("width");
                int height = elemento->IntAttribute("height");
                const char* fill = elemento->Attribute("fill");
                Color cor = parse_color(fill ? fill : "black");
                svg_elements.push_back(new Rect(x, y, width, height, cor));
            }
        }
    }   
}

svg::Point Recolher(string s){
    std::istringstream ss(s);
    string x,y;
    char sep;
    int x_, y_;
    while (ss >> x >> sep >> y){
        x_ = std::stoi(x);
        y_ = std::stoi(y);
    }
    svg::Point p = {x_, y_};
    return p;

}