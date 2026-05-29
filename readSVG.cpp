
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

// Novas Bibliotecas
#include<sstream>

using namespace std;
using namespace tinyxml2;

// declaração de novas funções
svg::Point Recolher(string s);
int Recolher_rs(string s);
string funcao(string s);
string dados (string s);
void processar(XMLElement* elemento, vector<svg::SVGElement*>& svg_elements);

namespace svg
{   void processar(XMLElement* elemento, vector<SVGElement*>& svg_elements);
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
        for (XMLElement* elemento = xml_elem->FirstChildElement(); elemento != nullptr; elemento = elemento->NextSiblingElement()){
            processar(elemento, svg_elements);
        }
    }

    void processar(XMLElement* elemento, vector<SVGElement*>& svg_elements){
        if (!elemento){return;}
        string name = elemento->Name();
        SVGElement* elem = nullptr;
            
        if (name == "ellipse"){
            int cx = elemento->IntAttribute("cx");
            int cy = elemento->IntAttribute("cy");
            const Point center = {cx, cy};
            int rx = elemento->IntAttribute("rx");
            int ry = elemento->IntAttribute("ry");
            const Point radius = {rx, ry};
            const char* fill = elemento->Attribute("fill");
            Color cor = parse_color(fill);
            elem = (new Ellipse(cor,center,radius));
        }
        
        else if (name == "circle"){
            int cx = elemento->IntAttribute("cx");
            int cy = elemento->IntAttribute("cy");
            const Point center = {cx, cy};
            int r = elemento->IntAttribute("r");
            const char* fill = elemento->Attribute("fill");
            Color cor = parse_color(fill);
            elem = (new Circle(cor,center,r));
        }
        else if (name == "polyline"){
            std::istringstream pontos(elemento-> Attribute("points"));
            string ponto, func, dados;
            vector<Point> points;
            while (pontos >> ponto){
                Point p =Recolher(ponto);  
                points.push_back(p);
            }
            const char* stroke = elemento->Attribute("stroke");
            Color cor = parse_color(stroke);
            elem = (new Polyline(points, cor));
            
        }
        else if (name == "line"){
            int x1 = elemento->IntAttribute("x1");
              int y1 = elemento->IntAttribute("y1");
            int x2 = elemento->IntAttribute("x2");
            int y2 = elemento->IntAttribute("y2");
            string func, dados;
            vector<Point> points;
            const char* stroke = elemento->Attribute("stroke");
            Color cor = parse_color(stroke);
            elem = (new Line(x1, y1, x2, y2, cor));
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
                Color cor = parse_color(fill);
                elem = (new Polygon(points, cor));
            }
        else if (name == "rect"){
            int x = elemento->IntAttribute("x");
            int y = elemento->IntAttribute("y");
            int width = elemento->IntAttribute("width");
            int height = elemento->IntAttribute("height");
            const char* fill = elemento->Attribute("fill");
            Color cor = parse_color(fill);
            elem = (new Rect(x, y, width, height, cor));
        }
        if (elem!=nullptr){
            const char* transform = elemento->Attribute("transform");
            Point origin = {0, 0};
            const char* transform_or = elemento->Attribute("transform-origin");
            if (transform_or) {
                origin = Recolher(transform_or); 
            }
            if (transform){
                string nome = funcao(transform);
                if (nome == "translate"){
                    Point t = Recolher(dados(transform));
                    elem->translate(t);
                }
                if (nome == "rotate"){
                    int a = Recolher_rs(dados(transform));
                    elem->rotate(origin, a);
                }
                else if (nome == "scale"){
                    int a = Recolher_rs(transform);
                    elem->scale(origin, a);
                }
            }
            svg_elements.push_back(elem);
        }
        for (XMLElement* child = elemento->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
            processar(child, svg_elements);
        }
    }
}

svg::Point Recolher(string s){
    for(auto &c : s) if(c == ',') c = ' ';
    std::istringstream ss(s);
    string x,y;
    int x_, y_;
    while (ss >> x >> y){
        x_ = std::stoi(x);
        y_ = std::stoi(y);
    }
    svg::Point p = {x_, y_};
    return p;

}

int Recolher_rs(string s){
    std::istringstream ss(s);
    string d;
    int d_;
    while (ss >> d){
        d_ = std::stoi(d);
    }
    return d_;
}

string funcao(string s){
    int idx = s.find('(');
    return s.substr(0,idx);
}

string dados(string s){
    int idx_i = s.find('(');
    int idx_f = s.find(')');
    return s.substr(idx_i+1,idx_f-idx_i-1);
}