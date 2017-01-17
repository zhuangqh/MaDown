#include <iostream>
#include <fstream>
#include "../src/Madown.h"

using namespace std;

int main() {
  md::IO::FileStream fs("../example.md");

  md::Madown madown;

  string HTML = madown.render(fs);

  std::ofstream out("example.html");

  out << HTML;

  out.close();
}
