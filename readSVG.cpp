
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

// Novas Bibliotecas
#include<sstream>
#include<map>

using namespace std;
using namespace tinyxml2;

// declaração de novas funções
svg::Point Recolher(string s);
int Recolher_rs(string s);
string funcao(string s);
string dados (string s);

namespace svg
{ 
    SVGElement* parse_element(XMLElement* elemento);

    map<string, XMLElement*> element_map;

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

        element_map.clear();

        for (XMLElement* elemento = xml_elem->FirstChildElement(); elemento != nullptr; elemento = elemento->NextSiblingElement()){
            SVGElement* elem = parse_element(elemento);
            
            if (elem) svg_elements.push_back(elem);
        }
    }

    SVGElement* parse_element(XMLElement* elemento){
            string name = elemento->Name();
            SVGElement* elem = nullptr;

            const char* id_attr = elemento->Attribute("id");
            if (id_attr) {
                element_map[string(id_attr)] = elemento;
            }
            
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
                    points.push_back(Recolher(ponto));
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
            else if (name == "g"){
                vector<SVGElement*> childs;
                for (XMLElement* child = elemento->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()){
                    SVGElement* child_obj = parse_element(child);
                    if (child_obj) childs.push_back(child_obj);
                }
                elem = new Group(childs);
            }
            else if (name == "use"){
                const char* href_attr = elemento->Attribute("href");
                if (href_attr && href_attr[0] == '#'){
                    string ref_id = string(href_attr + 1);
                    if (element_map.find(ref_id) != element_map.end()) {
                        elem = parse_element(element_map[ref_id]);
                    }
                }
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
                        int a = Recolher_rs(dados(transform));
                        elem->scale(origin, a);
                    }
                }
            }
            return elem;
        }
}

svg::Point Recolher(string s){
    for(auto &c : s) if(c == ',') c = ' ';
    std::istringstream ss(s);
    int x_, y_, x, y;
    while (ss >> x >> y){
        x_ = x;
        y_ = y;
    }
    svg::Point p = {x_, y_};
    return p;

}

int Recolher_rs(string s){
    std::istringstream ss(s);
    int d_, d;
    while (ss >> d){
        d_ = d;
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