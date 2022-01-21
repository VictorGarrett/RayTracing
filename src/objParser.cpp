#include "objParser.h"
#include "group.h"

ObjParser::ObjParser() { this->vertices_size = 0; }

ObjParser::~ObjParser() {}

Group *ObjParser::parse_obj_file(std::string filename) {
  using namespace std;

  Group *g = new Group();
  string line;
  ifstream obj_file(filename);

  while (getline(obj_file, line)) {
    string *words = this->parse_line(line);
    // for (int k = 0; k < 6; k++)
    //   cout << words[k];
    // cout << endl;
    if (!words)
      continue;

    if (words[0] == "v")
      this->add_vertice(words);

    if (words[0] == "f") {
      if (words[5] == "")
        g->add_child(this->get_triangle(words));

      else
        g = this->fan_triagulation(g, words);
    }

    delete[] words;
  }
  obj_file.close();
  return g;
}

std::string *ObjParser::parse_line(std::string line) {
  using namespace std;
  string *words = new string[6]{"-"};

  size_t pos = 0;
  size_t i = 0;
  while ((pos = line.find(" ")) != string::npos) {
    words[i] = line.substr(0, pos);
    line.erase(0, pos + 1);
    i++;
  }
  words[i] = line;

  return words;
}

void ObjParser::add_vertice(std::string *line) {
  using namespace std;
  Vec4 p = point(stof(line[1]), stof(line[2]), stof(line[3]));
  this->vertices[++this->vertices_size] = p;
}

Triangle *ObjParser::get_triangle(std::string *line) {
  using namespace std;
  int i1 = stoi(line[1]);
  int i2 = stoi(line[2]);
  int i3 = stoi(line[3]);
  return new Triangle(this->vertices[i1], this->vertices[i2],
                      this->vertices[i3]);
}

Group *ObjParser::fan_triagulation(Group *g, std::string *line) {
  for (int i = 0; i <= 2; i++) {
    g->add_child(new Triangle(this->vertices[stoi(line[1])],
                              this->vertices[stoi(line[2 + i])],
                              this->vertices[stoi(line[3 + i])]));
  }
  return g;
}