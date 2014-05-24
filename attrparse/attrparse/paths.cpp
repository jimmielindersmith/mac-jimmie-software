//
//  paths.cpp
//  attrparse
//
//  Created by Jimmie Lindersmith on 5/14/14.
//  Copyright (c) 2014 Jimmie Lindersmith. All rights reserved.
//

#include "paths.h"

paths::paths(){
    paths::pathIterator = 0;
}

unsigned long paths::getPathCount() {
    return paths::pathCollection.size();
}

void paths::resetPathInterator() {
    paths::pathIterator = 0;
}

bool paths::addPath(std::string path) {
    DIR *d;
    d = opendir(path.c_str());
    if (d) {
        pathCollection.push_back(path);
        closedir(d);
    } else {
        return false;
    }
    return true;
}

unsigned long paths::addRecursivePaths(std::string path, int num) {
    DIR *d;
    struct dirent *dir;
    d = opendir(path.c_str());
    if (d) {
        if (!num++) {
            pathCollection.push_back(path);
        }
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] != '.') {
                unsigned long preValue = pathCollection.size();
                addPath(path + "/" + dir->d_name);
                if (preValue < pathCollection.size()) {
                    addRecursivePaths(pathCollection.at(preValue), num);
                }
            }
        }
        closedir(d);
    }
    
    return num;
}

std::string paths::getPathAt(unsigned long num) {
    if (num < paths::pathCollection.size()) {
        return  paths::pathCollection.at(num);
    }
    return  "";
}

std::string paths::getNextPath() {
    if (paths::pathIterator < paths::pathCollection.size()) {
        return paths::pathCollection.at(paths::pathIterator++);
    }
    return "";
}

unsigned long paths::getPathChildren(std::string path, paths &collection) {
    DIR *d;
    struct dirent *dir;
    d = opendir(path.c_str());
    if (d) {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] != '.') {
                collection.addPath(path + "/" + dir->d_name);
            }
        }
        closedir(d);
    }
    return collection.getPathCount();
}