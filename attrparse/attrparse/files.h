//
//  files.h
//  attrparse
//
//  Created by Jimmie Lindersmith on 5/18/14.
//  Copyright (c) 2014 Jimmie Lindersmith. All rights reserved.
/*
 This is a file collection class, for storing files.
 These are stored in a string vector with a set of
 simple functions to step through the stored files in an
 orderly manner.
 The addFiles method return a boolean that indicates if any
 files were stored.
 */

#ifndef __attrparse__files__
#define __attrparse__files__

#include <iostream>
#include <dirent.h>
#include <string>
#include <vector>

class files {
public:
    files();
    unsigned long getfileCount();
    void resetFileInterator();
    bool addFiles(std::string path, std::string ext);
    std::string getFileAt(unsigned long num);
    std::string getNextFile();

private:
    std::vector<std::string> fileCollection;
    unsigned long fileIterator;
    DIR *d;
    struct dirent *dir;
};

#endif /* defined(__attrparse__files__) */
