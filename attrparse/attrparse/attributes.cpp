//
//  attributes.cpp
//  attrparse
//
//  Created by Jimmie Lindersmith on 5/20/14.
//  Copyright (c) 2014 Jimmie Lindersmith. All rights reserved.
//

#include "attributes.h"

attributes::attributes() {
    attributes::attributeIterator = 0;
}

void attributes::resetAttributeInterator() {
    attributes::attributeIterator = 0;
}

unsigned long attributes::addAttribute(std::string name, std::string value) {
    unsigned long temp = attributes::findAttributeByName(name);
    if (temp < attributes::attributeCollection.size()) {
        for (unsigned long i = 0; i < attributes::attributeCollection.at(temp).valueCollection.size(); i++) {
            if (attributes::attributeCollection.at(temp).valueCollection.at(i) == value) {
                return temp;
            }
        }
        attributes::attributeCollection.at(temp).valueCollection.push_back(value);
        return temp;
    } else {
        //we are here because no Attribute matches so we need to create one.
        Attribute attrTemp;
        attrTemp.name = name;
        attrTemp.valueCollection.push_back(value);
        attributes::attributeCollection.push_back(attrTemp);
        return attributes::attributeCollection.size();
    }
}

bool attributes::attributeExists(std::string name) {
    for (unsigned long i = 0; i < attributes::attributeCollection.size(); i++) {
        if (attributes::attributeCollection.at(i).name == name) {
            return true;
        }
    }
    return false;
}

unsigned long attributes::getAttributeCount() {
    return attributes::attributeCollection.size();
}

unsigned long attributes::getAttributeValues(std::string name, std::vector<std::string> &values) {
    unsigned long temp = attributes::findAttributeByName(name);
    if (temp < attributes::attributeCollection.size()) {
        for (unsigned long i = 0; i < attributes::attributeCollection.at(temp).valueCollection.size(); i++) {
            values.push_back(attributes::attributeCollection.at(temp).valueCollection.at(i));
        }
        return temp;
    }
    return 0;
}

unsigned long attributes::findAttributeByName(std::string name) {
    for (unsigned long i = 0; i < attributes::attributeCollection.size(); i++) {
        if (attributes::attributeCollection.at(i).name == name) {
            return i;
        }
    }
    return attributes::attributeCollection.size();
}

std::string attributes::getAttributeAt(unsigned long num, std::vector<std::string> &values) {
    if (num < attributes::attributeCollection.size()) {
        for (unsigned long i = 0; i < attributes::attributeCollection.at(num).valueCollection.size(); i++) {
            values.push_back(attributes::attributeCollection.at(num).valueCollection.at(i));
        }
        return attributes::attributeCollection.at(num).name;
    }
    return "";
}

std::string attributes::getNextAttribute(std::vector<std::string> &values) {
    if (attributes::attributeIterator < attributes::attributeCollection.size()) {
        for (unsigned long i = 0; i < attributes::attributeCollection.at(attributes::attributeIterator).valueCollection.size(); i++) {
            values.push_back(attributes::attributeCollection.at(attributes::attributeIterator).valueCollection.at(i));
        }
        return attributes::attributeCollection.at(attributes::attributeIterator++).name;
    }
    return "";
}
