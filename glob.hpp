#ifndef GLOB_HPP
#define GLOB_HPP

#include <fnmatch.h>
#include <dirent.h>
#include <string>
#include <cassert>
//https://bitbucket.org/szx/glob/src

namespace glob {

static std::pair<std::string, std::string> SplitPath(const std::string &path) {
  std::string::size_type last_sep = path.find_last_of("/");
  if (last_sep != std::string::npos) {
    return std::make_pair(std::string(path.begin(), path.begin() + last_sep),
                          std::string(path.begin() + last_sep + 1, path.end()));
  }
  return std::make_pair(".", path);
}

struct Glob {
  Glob(const std::string &pattern)
   : dir_(0),
     dir_entry_(0)
  {
    std::pair<std::string, std::string> dir_and_mask = SplitPath(pattern);

    dir_ = opendir(dir_and_mask.first.c_str());
    path = dir_and_mask.first;
    pattern_ = dir_and_mask.second;

    if (dir_ != 0) {
      Next();
    }
  }

  ~Glob() {
    if (dir_ != 0) {
      closedir(dir_);
    }
  }

  std::string GetFileName() const {
    assert(dir_entry_ != 0);
    return  path+"/"+dir_entry_->d_name;
  }

  operator bool() const {
    return dir_entry_ != 0;
  }



  bool Next() {
    while ((dir_entry_ = readdir(dir_)) != 0) {
      if (!fnmatch(pattern_.c_str(), dir_entry_->d_name,
                   FNM_CASEFOLD | FNM_NOESCAPE | FNM_PERIOD)) {
        return true;
      }
    }
    return false;
  }

 private:
  std::string pattern_;
  DIR *dir_;
  struct dirent *dir_entry_;
  std::string path;

};

} // namespace glob

#endif
