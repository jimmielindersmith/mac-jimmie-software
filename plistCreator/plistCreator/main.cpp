//
//  main.cpp
//  plistCreator
//
//  Created by Jimmie Lindersmith on 6/30/13.
//  Copyright (c) 2013 Jimmie Lindersmith. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

std::map<std::string, std::string> splitAt(std::string inputString, char delimiter, std::string strArray[]);
int countChar(std::string inputString, char searchChar);
std::string removePrefix(std::string inputStr, std::string prefix);
std::string removeSuffix(std::string inputStr, std::string suffix);
std::string removeDatePageSuffix(std::string inputStr);
std::string removePageSuffix(std::string inputStr);
int makePlistFile(std::vector<std::map<std::string, std::string>> content, std::string outFile);

int main(int argc, const char * argv[])
{
    /* Process the command line argument which should be a file path. */
	std::string line; // A temporary string to hold a line from the file.
	std::vector<std::map<std::string, std::string>> lines; // A vector of maps to hold all data values.
	std::ifstream fileContent; // A file stream for the file access.
    std::string keyStrings[3] = {"path", "filename", "code"};
	if (argc > 1)
    { //Item 0 is the command source.
		fileContent.open (argv[1], std::ifstream::in); //Open the input file.
		if (fileContent.is_open())
		{
			while (fileContent.good())
			{
				getline(fileContent,line);
				lines.push_back(splitAt(line, '\t', keyStrings)); //Push this line into the vector.
			}
			fileContent.close();
            
            /* Step through the lines vector and add a parent element to each map */
            for (int i = 1; i < lines.size(); i++)
            {
                lines[i]["parent"] = removePrefix(removeDatePageSuffix(lines[i]["code"]), "PRQ_");
            }
            /***************************************************************************************
             * At this point the lines vector contains a memory representation of our plist file,  *
             * We just need to map this to a plist string and export to a file to complete this.   *
             *                                                                                     *
             ***************************************************************************************/
            if (makePlistFile(lines, argv[2]) != 0)
            {   // If we cannot write the plist file generate an error.
                return -1;
            }
		}
		else
		{ // An error opening the file indicated on the command line.
			std::cout << "Unable to open file" << std::endl << std::endl;
		}
    }
    return 0;
}

int makePlistFile(std::vector<std::map<std::string, std::string>> content, std::string outFile)
{
    enum tagNames {xml, doc, plist, plistEnd, dict, dictEnd, key, keyEnd, str, strEnd};
    std::string tags[10] = {"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
                            "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">",
                            "<plist version=\"1.0\">", "</plist>", "<dict>", "</dict>", "<key>", "</key>", "<string>", "</string>"};
    typedef std::map<std::string, std::vector<std::map<std::string, std::string>>> plistMap;
    std::stringstream outFileData;
    plistMap plistData;
    for (int i = 1; i < content.size(); i++)
    {
        plistData[content[i]["parent"]].push_back(content[i]);
    }
    // Now use this structure to build the plist file...
    outFileData << tags[xml] << std::endl << tags[doc] << std::endl
                << tags[plist] << std::endl << tags[dict] << std::endl;
    for (plistMap::iterator iterator = plistData.begin(); iterator != plistData.end(); iterator++)
    {
        outFileData << tags[key] << iterator->first << tags[keyEnd] << std::endl
                    << tags[dict] << std::endl;
        for (int i = 0; i < iterator->second.size(); i++)
        {
            outFileData << tags[key] << removePageSuffix(iterator->second[i]["code"])
                        << tags[keyEnd] << std::endl << tags[dict] << std::endl
                        << tags[key] << "Path" << tags[keyEnd] << std::endl
                        << tags[str] << iterator->second[i]["path"] << tags[strEnd] << std::endl
                        << tags[key] << "Filename" << tags[keyEnd] << std::endl
                        << tags[str] << iterator->second[i]["filename"] << tags[strEnd] << std::endl
                        << tags[key] << "Code" << tags[keyEnd] << std::endl
                        << tags[str] << iterator->second[i]["code"] << tags[strEnd] << std::endl
                        << tags[dictEnd] << std::endl;
        }
        outFileData << tags[dictEnd] << std::endl;
    }
    outFileData << tags[dictEnd] << std::endl << tags[plistEnd];
    // Write the plist string to a file...
    std::ofstream outFileStream;
    outFileStream.open (outFile);
    if (outFileStream.is_open())
    {
        outFileStream << outFileData.str();
        outFileStream.close();
        return 0;
    }
    else
    {
        return -1;
    }
}

std::map<std::string, std::string> splitAt(std::string inputString, char delimiter, std::string strArray[])
{
    /* This is a snippit for splitting a standard string
     by using the getline function of an istringstream
     and setting the line delimiter to a char other than
     newline (\n) */
    std::map<std::string, std::string> returnValue;
    if (countChar(inputString, delimiter) == strArray->length())
    {
        std::istringstream f(inputString);
        std::string s;
        int i = 0;
        while (std::getline(f, s, delimiter)) {
            returnValue[strArray[i++]] = s;
        }
    }
    else
    {
        for (int i = 0; i < strArray->length(); i++)
        {
            returnValue[strArray[i]] = "";
        }
    }
    return returnValue;
}

int countChar(std::string inputString, char searchChar)
{
    std::istringstream f(inputString);
    std::string s;
    int i = 0;
    while (std::getline(f, s, searchChar)) {
        i++;
    }
    return i + 1;
}

std::string removePrefix(std::string inputStr, std::string prefix)
{
    unsigned long prefixLen = prefix.length();
    unsigned long pos = inputStr.find(prefix);
    if(pos == 0)
    {
        return inputStr.substr(prefixLen);
    }
    else if(pos > 0 && pos != std::string::npos)
    {
        return inputStr.substr(0, pos) + inputStr.substr(pos + prefixLen);
    }
    return inputStr;
}

std::string removeSuffix(std::string inputStr, std::string suffix)
{
    unsigned long suffixLen = suffix.length();
    unsigned long pos = inputStr.rfind(suffix);
    if(pos == inputStr.length() - suffixLen)
    {
        return inputStr.substr(0, pos);
    }
    else if(pos < inputStr.length() - suffixLen && pos != std::string::npos)
    {
        return inputStr.substr(0, pos) + inputStr.substr(pos + suffixLen);
    }
    return inputStr;
}

std::string removeDatePageSuffix(std::string inputStr)
{
    std::string testValues = "0123456789";
    std::string returnStr = inputStr.substr(0);
    unsigned long limit = inputStr.rfind('_');
    
    for(int i = 0; i < 10; i++)
    {
        while (returnStr.rfind(testValues[i]) != std::string::npos && returnStr.rfind(testValues[i]) > limit)
        {
            if (returnStr.rfind(testValues[i]) < returnStr.length())
            {
                returnStr = returnStr.substr(0, returnStr.rfind(testValues[i]));
            }
        }
    }
    return returnStr.substr(0, limit);
}

std::string removePageSuffix(std::string inputStr)
{
    std::string testValues = "0123456789";
    std::string returnStr = inputStr.substr(0);
    unsigned long limit = inputStr.rfind('-');
    
    for(int i = 0; i < 10; i++)
    {
        while (returnStr.rfind(testValues[i]) != std::string::npos && returnStr.rfind(testValues[i]) > limit)
        {
            if (returnStr.rfind(testValues[i]) < returnStr.length())
            {
                returnStr = returnStr.substr(0, returnStr.rfind(testValues[i]));
            }
        }
    }
    return returnStr.substr(0, limit);
}