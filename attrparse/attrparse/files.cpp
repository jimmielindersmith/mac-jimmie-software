//
//  files.cpp
//  attrparse
//
//  Created by Jimmie Lindersmith on 5/18/14.
//  Copyright (c) 2014 Jimmie Lindersmith. All rights reserved.
//

#include "files.h"

files::files() {
    files::fileIterator = 0;
}

unsigned long files::getfileCount() {
    return files::fileCollection.size();
}

void files::resetFileInterator() {
    files::fileIterator = 0;
}

bool files::addFiles(std::string path, std::string ext) {
    std::string filenameTemp = "";
    if((d  = opendir(path.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << path << std::endl;
        return false;
    }
    while ((dir = readdir(d)) != NULL) {
        filenameTemp = std::string(dir->d_name);
        if (filenameTemp.length() > ext.length()) {
            if (filenameTemp.substr(filenameTemp.length() - ext.length(),ext.length()) == ext) {
                files::fileCollection.push_back(path + "/" + filenameTemp);
            }
        }
    }
    closedir(d);
    return true;
}

std::string files::getFileAt(unsigned long num) {
    if (num < files::fileCollection.size()) {
        return  files::fileCollection.at(num);
    }
    return  "";
}

std::string files::getNextFile() {
    if (files::fileIterator < files::fileCollection.size()) {
        return files::fileCollection.at(files::fileIterator++);
    }
    return "";
}
