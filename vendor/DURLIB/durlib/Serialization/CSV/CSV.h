#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
//
//#include <stdexcept>
//#include <algorithm>

//#include "Parser.h"

namespace DURLIB
{
  namespace CSV
  {

    enum DATATYPE
    {
      INT = 1,
      DOUBLE = 2,
      CHAR = 3,
      STRING = 4
    };

    class CSV
    {
    private:
      std::string category;
      std::vector<std::string> elements;
      int elementcount = 0;

      int COLUMNDATATYPE = 0;

    public:
      CSV *next;
      // CSV(const std::string &FILEPATH);
      CSV(const std::string &categoryName);
      ~CSV();

      std::map<int, int> elementsINT;
      std::map<int, double> elementsDBL;
      std::map<int, char *> elementsCHAR;
      std::map<int, std::string> elementsSTR;

      const std::string &getCategory() const;

      void setCategory(const std::string &category);

      const std::vector<std::string> &getElements() const;

      void setElements(const std::string &elements);

      int getTotalElements();

      void displayElements();

      void sortElement(const std::string &elements);

      int getCOLUMNDATATYPE() const;

      /*void clearElementsINT();
      void clearElementsDBL();
      void clearElementsCHAR();
      void clearElementsSTR();*/

      /*int getElementsINT1(int key);
      int getElementsINT2(int key);
      int getElementsDBL1(int key);
      double getElementsDBL2(int key);
      int getElementsCHAR1(int key);
      char getElementsCHAR2(int key);
      int getElementsSTR1(int key);
      std::string getElementsSTR2(int key);*/

      std::map<int, int> getElementsINT();
      std::map<int, double> getElementsDBL();
      std::map<int, char *> getElementsCHAR();
      std::map<int, std::string> getElementsSTR();

      void setElementsINT(int key, int value);
      void setElementsDBL(int key, double value);
      void setElementsCHAR(int key, char *value);
      void setElementsSTR(int key, std::string &value);

      void freeMem();
    };

    /*int readCSV(const std::string &FILEPATH, CSV *CSVOBJ);
    void parseCSV(std::fstream &CSVFILE, CSV *CSVOBJ);
    void parseColumns(const std::string &line, CSV *CSVOBJ);
    void parseElements(const std::string &line, CSV *CSVOBJ);*/

  }
}