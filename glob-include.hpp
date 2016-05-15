#ifndef GLOB_INCLUDE_HPP
#define GLOB_INCLUDE_HPP

#include "glob.hpp"

namespace glob {

  void globInclude(std::string path) {
    Glob files(path);
    while (files) {
      include("./"+files.GetFileName()); //jyt meta function
      files.Next();
    }
  }
}

#endif
