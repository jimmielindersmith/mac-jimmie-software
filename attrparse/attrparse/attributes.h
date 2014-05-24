//
//  attributes.h
//  attrparse
//
//  Created by Jimmie Lindersmith on 5/20/14.
//  Copyright (c) 2014 Jimmie Lindersmith. All rights reserved.
//

#ifndef __attrparse__attributes__
#define __attrparse__attributes__

#include <iostream>
#include <string>
#include <vector>

struct Attribute {
    std::string name;
    std::vector<std::string> valueCollection;
};

class attributes {
public:
    attributes();
    void resetAttributeInterator();
    unsigned long addAttribute(std::string name, std::string value);
    bool attributeExists(std::string name);
    unsigned long getAttributeCount();
    unsigned long getAttributeValues(std::string name, std::vector<std::string> &values);
    unsigned long findAttributeByName(std::string name);
    std::string getAttributeAt(unsigned long num, std::vector<std::string> &values);
    std::string getNextAttribute(std::vector<std::string> &values);
    
private:
    std::vector<Attribute> attributeCollection;
    unsigned long attributeIterator;
    
};

#endif /* defined(__attrparse__attributes__) */
