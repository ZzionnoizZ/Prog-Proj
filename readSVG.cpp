
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

// Novas Bibliotecas
#include<sstream>

using namespace std;
using namespace tinyxml2;

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
                const char* stroke = elemento->Attribute("stroke");
                Color cor = parse_color(stroke ? stroke : "black");
                svg_elements.push_back(new Polyline(points, cor));
            }

            else if (name == "line"){
                int x1 = elemento->IntAttribute("x1");
                int y1 = elemento->IntAttribute("y1");
                int x2 = elemento->IntAttribute("x2");
                int y2 = elemento->IntAttribute("y2");
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