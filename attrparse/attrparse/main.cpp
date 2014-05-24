//
//  main.cpp
//  attrparse
//
//  Created by Jimmie Lindersmith on 5/14/14.
//  Copyright (c) 2014 Jimmie Lindersmith. All rights reserved.
/*
    For now this app only reads the attribute lines from xml files
    and displays a countdown at the console.
    For the next part we need to develope a class to store the
    resulting data found in a memory structure that is searchable
    and reusable. 
    (will write the data out in a file structure of some sort.)
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "unistd.h"
#include "paths.h"
#include "files.h"
#include "attributes.h"

using namespace std;


int main(int argc, const char * argv[])
{
    ifstream inStream;
    string myStr;
    paths *myPaths = new paths();
    files *myFiles = new files();
    attributes *myAttributes = new attributes();
    unsigned long attrCount = 0;
    
    if (argc > 1) {
        for (int p = 1; p < argc; p++) {
            myPaths->addRecursivePaths(argv[p], 0);
            for (unsigned long x = 0; x < myPaths->getPathCount(); x++) {
                myFiles->addFiles(myPaths->getNextPath(), "xml");
            }
            cout << "Paths: " << myPaths->getPathCount() << ", Files: " << myFiles->getfileCount() << endl;
            for (unsigned long i = 0; i < myFiles->getfileCount(); i++) {
                inStream.open(myFiles->getNextFile());
                
                if (inStream.fail()) {
                    cout << "Input file (" << i << ") opening failed.\n";
                    exit(1);
                } else if(inStream.good()) {
                    while (inStream.good()) {
                        getline(inStream, myStr);
                        if (myStr.find("<XMLAttribute") < myStr.length()) {
                            unsigned long nameOffset = myStr.find(" Name=\"") + 7;
                            unsigned long valueOffset = myStr.find(" Value=\"") + 8; //may need to account for stored returns
                            unsigned long trailing =  myStr.length() - myStr.find_last_of("\"");
                            unsigned long nameLength = (valueOffset - 9) - nameOffset;
                            unsigned long valueLength = (myStr.length() - trailing) - valueOffset;
                            attrCount = myAttributes->addAttribute(myStr.substr(nameOffset, nameLength), myStr.substr(valueOffset, valueLength));
                        }
                    }
                }
                inStream.close();
            }
            for (unsigned long i = 0; i < myAttributes->getAttributeCount(); i++) {
                vector<string> temp;
                cout << "Name: " << myAttributes->getNextAttribute(temp) << " Values: ";
                for( string v : temp ) cout << v << ", ";
                cout << endl;
            }
        }
    }
    return 0;
}
