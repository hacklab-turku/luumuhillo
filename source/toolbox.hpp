#ifndef _TOOLBOX_HPP_
#define _TOOLBOX_HPP_

#include <string>
#include <vector>
#ifdef WIN32
#include <windows.h>
#endif

class Toolbox
{
private:
public:
    Toolbox();
    
    int timesRandomized;
    
    int giveRandomInt();
    int giveRandomInt(int min, int max);
    
    template<class T>
    typename T::const_iterator findFromVector(T const& c, typename T::value_type const& v);

    template<class T>
    bool isInVector(T const& c, typename T::value_type const& v);

    std::string appendToStringNTimes(std::string in, int numOfTimes);
    std::string charToString(char c);
    std::string intToString(int i);
    std::string resolutionToString(int sizeX, int sizeY);
    int boolToInt(bool b);
    std::vector<int> doubleVectorToIntVector(std::vector<double> in);
    std::string stripString(std::string source, int quantity, std::string mode);
    std::string relativePathToAbsolute(std::string path);
    std::string reverseString(std::string toReverse);
    std::string combineStringAndInt(std::string in1, int in2);
    std::string combineStringAndInts(std::string in1, int in2, int in3);
    std::string combineIntAndString(int i, std::string s);

    std::vector<std::string> splitTextByString(char separator, std::string text);
    std::string splitTextInLines(size_t line_length, std::string text);

    float** giveFloatArray2D(int sizeX, int sizeY);
    float*** giveFloatArray3D(int sizeX, int sizeY, int sizeZ);
    void clearFloatArray2D(float** arr, int sizeX, int sizeY);
    void deleteFloatArray2D(float** arr, int sizeX);
    void clearFloatArray3D(float*** arr, int sizeX, int sizeY, int sizeZ);
    void deleteFloatArray3D(float*** arr, int sizeX, int sizeY);
};

#endif
