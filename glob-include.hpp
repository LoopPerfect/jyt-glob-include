#ifndef GLOB_INCLUDE_HPP
#define GLOB_INCLUDE_HPP

#include <jyt/runtime.hpp>
#include "glob.hpp"

namespace glob {

  void globInclude(std::string path) {
    Glob files(path);
    while (files) {
      jyt.include("./"+files.GetFileName()); //jyt meta function
      files.Next();
    }
  }
}

#endif
