#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <list>
#include "UnixReaddir.hpp"

UnixReaddir::UnixReaddir(void) {
}

UnixReaddir::~UnixReaddir(void) {
}

std::list<std::string> UnixReaddir::readFolder(const std::string& folderName) const {
  DIR *dir;
  struct dirent *ent;
  struct stat st;
  std::list<std::string> files;

  if ((dir = opendir(folderName.c_str())) != NULL)
  {
    while ((ent = readdir(dir)) != NULL) {
        const std::string file_name = ent->d_name;
        const std::string full_file_name = folderName + "/" + file_name;

        if (file_name[0] == '.' || stat(full_file_name.c_str(), &st) == -1 || (st.st_mode & S_IFDIR) != 0)
            continue;

        files.push_back(full_file_name);
    }
    closedir(dir);
  }

  return files;
}
