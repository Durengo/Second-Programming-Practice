#pragma once

#include <iostream>
#include <vector>
#include <queue>

namespace CSV{
class CSVLL;
}

namespace CSV{
class CSV;
}

namespace ALGO {

enum AXIS { ROW=0, COLUMN=1 };

enum ALGOFUNC {LSEARCH=0, LSEARCH2=1, BSEARCH=2, ISORT=3, INVERT=4};

class CSVQUEUE{
 private:

  std::vector<std::pair<int, std::string>> STORAGE;
  int count;
  CSV::CSVLL *LOCALLIST;
  //std::vector<int> STORAGE;

  //BACK>---------FRONT>

 public:
  CSVQUEUE(CSV::CSVLL *LIST);
  ~CSVQUEUE();
  int size();
  int *front();
  int *back();
  int *at(int index);
  void queue(ALGOFUNC arr, const std::string &argument);
  void queue(ALGOFUNC arr, const std::string &argument, ALGO::AXIS axis, int index);
  void queue(ALGOFUNC arr, bool lowtohigh, int index);
  //void dequeue(ALGOFUNC);
  void pop();
  void execute();
};

/*class ALGO{
 private:
  CSV::CSVLL *LIST;
 public:
  ALGO(CSV::CSVLL *LIST);
};*/

/*void LSearch(std::string argument, std::vector<CSV::CSV> &searchList);
void LSearch(std::string argument, int column, std::vector<CSV::CSV> &searchList);

void BSearch(std::string argument, std::vector<CSV::CSV> &searchList);
void BSearch(std::string argument, int column, std::vector<CSV::CSV> &searchList);

void ISort(bool lowtohigh, std::vector<CSV::CSV> &searchList);*/

void LSearch(std::string argument, CSV::CSVLL *LIST);
void LSearch(std::string argument, ALGO::AXIS axis, int index, CSV::CSVLL *LIST);

void BSearch(std::string argument, CSV::CSVLL *LIST);

std::vector<std::string> BSortINT(std::string argument, CSV::CSV* temp);
std::vector<std::string> BSortDBL(std::string argument, CSV::CSV* temp);
std::vector<std::string> BSortCHAR(std::string argument, CSV::CSV* temp);
std::vector<std::string> BSortSTR(std::string argument, CSV::CSV* temp);
int BSearchSPEC(std::vector<std::string> arr, const std::string &argument, CSV::CSV* temp);

void ISort(bool lowtohigh, CSV::CSVLL *LIST, int index);
void INTMAPTOVEC(bool lowtohigh, CSV::CSV *temp, int index);
void DOUBLEMAPTOVEC(bool lowtohigh, CSV::CSV *temp, int index);
void CHARMAPTOVEC(bool lowtohigh, CSV::CSV *temp, int index);
void STRINGMAPTOVEC(bool lowtohigh, CSV::CSV *temp, int index);

void REVERSE(bool colorrow, CSV::CSVLL *LIST, int index);

void RRange(int key, int count, CSV::CSVLL *LIST);

}