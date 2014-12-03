#include <dirent.h>
#include <iostream>
#include <string>
#include <list>
#include "UnixReaddir.hpp"

UnixReaddir::UnixReaddir(void) {
}

UnixReaddir::~UnixReaddir(void) {
}

std::list<std::string> UnixReaddir::readFolder(std::string pathFolder){
  DIR *dir;
  struct dirent *ent;
  std::list<std::string> files;
 
  if ((dir = opendir (pathFolder)) != NULL)
    {
      while ((ent = readdir(dir)) != NULL)
        if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
          files.push_back(ent->d_name);
      closedir (dir);
    }
  return files;
}
