#pragma once
#include "triangle.h"
#include <vector>

class Group;

class ObjParser {
public:
  int vertices_size;
  Vec4 vertices[100000];

  ObjParser();
  ~ObjParser();

  Group *parse_obj_file(std::string filename);
  std::string *parse_line(std::string line);

  void add_vertice(std::string *line);
  Triangle *get_triangle(std::string *line);
  Group *fan_triagulation(Group *g, std::string *line);
};