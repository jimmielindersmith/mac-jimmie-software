//
//  paths.h
//  attrparse
//
//  Created by Jimmie Lindersmith on 5/14/14.
//  Copyright (c) 2014 Jimmie Lindersmith. All rights reserved.
/*
    This is a path collection class, for storing paths.
    These are stored in a string vector with a set of
    simple functions to step through the stored paths in an
    orderly manner.
    The addPath method return a boolean that indicates if the
    path was stored. if the path terminates with a filename
    it will not be stored, this class is just for paths, not files.
 */

#ifndef __attrparse__paths__
#define __attrparse__paths__

#include <iostream>
#include <dirent.h>
#include <string>
#include <vector>

class paths {
public:
    paths();
    unsigned long getPathCount();
    void resetPathInterator();
    bool addPath(std::string path);
    unsigned long addRecursivePaths(std::string path, int num);
    std::string getPathAt(unsigned long num);
    std::string getNextPath();
    unsigned long getPathChildren(std::string path, paths &collection);
    
private:
    std::vector<std::string> pathCollection;
    unsigned long pathIterator;
};

#endif /* defined(__attrparse__paths__) */
