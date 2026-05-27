
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
        }
    }   
