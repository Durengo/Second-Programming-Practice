#include "ALGO.h"
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <stack>

#include "durlib/Serialization/CSV/CSVLL.h"

namespace ALGO {
//CLASS--------------

CSVQUEUE::CSVQUEUE(CSV::CSVLL *LIST)
	: count(0), LOCALLIST(LIST) {

}

CSVQUEUE::~CSVQUEUE() {

}

int CSVQUEUE::size() {
  return STORAGE.size();
  STORAGE[0].first;
}

int *CSVQUEUE::front() {
  return &STORAGE[0].first;
}

int *CSVQUEUE::back() {
  return &STORAGE[STORAGE.size() - 1].first;
}

int *CSVQUEUE::at(int index) {
  if (index >= STORAGE.size() || index < 0) {
	std::cout << "\nINDEX OUT OF BOUNDS\n";
	return nullptr;
  } else {
	return &STORAGE[index].first;
  }
}

void CSVQUEUE::queue(ALGOFUNC arr, const std::string &argument) {
  if (arr == ALGOFUNC::LSEARCH2 || arr == ALGOFUNC::ISORT || arr == ALGOFUNC::INVERT) {
	std::cout << "\nINVALID ARR FOR THIS FUNCTION\n";
	return;
  }
  switch (arr) {
	case ALGOFUNC::LSEARCH:
	  STORAGE.emplace_back(ALGOFUNC::LSEARCH, argument);
	  count++;
	  return;
	case ALGOFUNC::BSEARCH:
	  STORAGE.emplace_back(ALGOFUNC::BSEARCH, argument);
	  count++;
	  return;
  }
}

void CSVQUEUE::queue(ALGOFUNC arr, const std::string &argument, ALGO::AXIS axis, int index) {
  if (arr == ALGOFUNC::LSEARCH || arr == ALGOFUNC::BSEARCH || arr == ALGOFUNC::ISORT || arr == ALGOFUNC::INVERT) {
	std::cout << "\nINVALID ARR FOR THIS FUNCTION\n";
	return;
  }
  std::string comb = "";
  comb.append(argument + "," + std::to_string(axis) + "," + std::to_string(index));
  STORAGE.emplace_back(ALGOFUNC::LSEARCH2, comb);
  count++;
}

void CSVQUEUE::queue(ALGOFUNC arr, bool lowtohigh, int index) {
  if (arr == ALGOFUNC::LSEARCH || arr == ALGOFUNC::BSEARCH || arr == ALGOFUNC::LSEARCH2) {
	std::cout << "\nINVALID ARR FOR THIS FUNCTION\n";
	return;
  }
  std::string comb = "";
  switch(arr){
	case ALGOFUNC::ISORT:
	  comb.append(std::to_string(lowtohigh) + "," + std::to_string(index));
	  STORAGE.emplace_back(ALGOFUNC::ISORT, comb);
	  count++;
	  return;
	case ALGOFUNC::INVERT:
	  comb.append(std::to_string(lowtohigh) + "," + std::to_string(index));
	  STORAGE.emplace_back(ALGOFUNC::INVERT, comb);
	  count++;
	  return;
  }
}

void CSVQUEUE::pop() {
  STORAGE.pop_back();
  count--;
}

void CSVQUEUE::execute() {

  for (int i = 0; i < STORAGE.size(); i++) {
	std::string temparg = "";
	std::string tempstr = "";
	ALGO::AXIS tempbool;
	int tempint = 0;
	bool tempbool2 = false;
	switch (STORAGE[i].first) {
	  case ALGOFUNC::LSEARCH:
		LSearch(STORAGE[i].second, LOCALLIST);
		//std::cout << STORAGE[i].first << ":" << STORAGE[i].second << "\n";
		break;
	  case ALGOFUNC::LSEARCH2:
		tempstr = STORAGE[i].second;
		temparg = tempstr.substr(0, tempstr.find(','));
		tempstr = tempstr.substr(tempstr.find(',') + 1, tempstr.length());
		tempbool = static_cast<AXIS>(std::stoi(tempstr.substr(0, tempstr.find(','))));
		tempstr = tempstr.substr(tempstr.find(',') + 1, tempstr.length());
		tempint = std::stoi(tempstr.substr(0, tempstr.length()));
		LSearch(temparg, tempbool, tempint, LOCALLIST);
		//std::cout << STORAGE[i].first << ":" << STORAGE[i].second << "\n";
		break;
	  case ALGOFUNC::BSEARCH:
		BSearch(STORAGE[i].second, LOCALLIST);
		//std::cout << STORAGE[i].first << ":" << STORAGE[i].second << "\n";
		break;
	  case ALGOFUNC::ISORT:
		tempstr = STORAGE[i].second;
		/*std::cout << "TEMPSTR: " << tempstr << "\n";
		std::cout << "TEMPSTR: " << tempstr.substr(0, tempstr.find(',')) << "\n";
		std::cout << "TEMPSTR: " << tempstr.substr(tempstr.find(',') + 1, tempstr.length()) << "\n";*/
		tempbool2 = std::stoi(tempstr.substr(0, tempstr.find(',')));
		tempint = std::stoi(tempstr.substr(tempstr.find(',') + 1, tempstr.length()));

		ISort(tempbool2, LOCALLIST, tempint);

		//std::cout << STORAGE[i].first << ":" << STORAGE[i].second << "\n";
		break;
	  case ALGOFUNC::INVERT:
		tempstr = STORAGE[i].second;
		/*std::cout << "TEMPSTR: " << tempstr << "\n";
		std::cout << "TEMPSTR: " << tempstr.substr(0, tempstr.find(',')) << "\n";
		std::cout << "TEMPSTR: " << tempstr.substr(tempstr.find(',') + 1, tempstr.length()) << "\n";*/
		tempbool2 = std::stoi(tempstr.substr(0, tempstr.find(',')));
		tempint = std::stoi(tempstr.substr(tempstr.find(',') + 1, tempstr.length()));

		REVERSE(tempbool2, LOCALLIST, tempint);
		break;
	}
  }

  //delete(this);
}

//CLASS--------------

void LSearch(std::string argument, CSV::CSVLL *LIST) {
  if (argument.length() < 2) {
	return;
  }
  std::string foundArguments = "";
  int count = 0;

  CSV::CSV *temp = LIST->getHead();

  while (temp != nullptr) {
	for (int i = 0; i < temp->getTotalElements(); i++) {
	  if (temp->getElements()[i].find(argument) != std::string::npos) {
		int previous = count + 1;
		std::string current = std::to_string(previous);
		foundArguments.append(current + ". " + temp->getCategory() + ": " + temp->getElements()[i] + "\n");
		count++;
	  }
	}
	temp = temp->next;
  }

  /*for (int i = 0; i < searchList.size(); i++) {
	for (int j = 0; j < searchList[i].getTotalElements(); j++) {
	  if (searchList[i].getElements()[j].find(argument) != std::string::npos) {
		foundArguments.append(searchList[i].getCategory() + ": " + searchList[i].getElements()[j] + "\n");
		count++;
	  }
	}
  }*/

  if (foundArguments.length() == 0) {
	std::cout << "Keyword does not exist.\n";
	return;
  } else {
	std::cout << "KEYWORD \"" << argument << "\"" << " FOUND IN " << count << " SEARCHES:\n";
	std::cout << foundArguments;
  }
}

void LSearch(std::string argument, ALGO::AXIS axis, int index, CSV::CSVLL *LIST) {
  if (argument.length() < 2) {
	return;
  }
  std::string foundArguments = "";
  int count = 0;
  int columnCount[LIST->length()];
  switch (axis) {
	case ALGO::AXIS::ROW:
	  if (index > LIST->getHead()->getTotalElements() - 1 || index < 0) {
		std::cout << "\nINDEX OUT OF BOUNDS\n";
		return;
	  } else {
		for (int i = 0; i < LIST->length(); i++) {
		  if (LIST->getPTR(i)->getElements()[index].find(argument) != std::string::npos) {
			int previous = count + 1;
			std::string current = std::to_string(previous);
			foundArguments.append(current + "." + LIST->getPTR(i)->getCategory() + " : " + LIST->getPTR(i)->getElements()[index] + "\n");
			count++;
		  }
		}
	  }
	  if (foundArguments.length() == 0) {
		std::cout << "Keyword does not exist.\n";
		return;
	  } else {
		std::cout << "KEYWORD \"" << argument << "\"" << " IN ROW " << "\'" << index << "\' FOUND " << count << " SEARCHES:\n";
		std::cout << foundArguments;
	  }
	  return;
	case ALGO::AXIS::COLUMN:
	  if (index > LIST->length() - 1 || index < 0) {
		std::cout << "\nINDEX OUT OF BOUNDS\n";
		return;
	  } else {
		for (int i = 0; i < LIST->getPTR(index)->getTotalElements(); i++) {
		  if (LIST->getPTR(index)->getElements()[i].find(argument) != std::string::npos) {
			int previous = count + 1;
			std::string current = std::to_string(previous);
			foundArguments.append(current + ". " + LIST->getPTR(index)->getElements()[i] + "\n");
			count++;
		  }
		}
	  }
	  if (foundArguments.length() == 0) {
		std::cout << "Keyword does not exist.\n";
		return;
	  } else {
		std::cout << "KEYWORD \"" << argument << "\"" << " IN COLUMN " << "\'" << LIST->getPTR(index)->getCategory() << "\' FOUND " << count << " SEARCHES:\n";
		std::cout << foundArguments;
	  }
	  return;
  }
}

void BSearch(std::string argument, CSV::CSVLL *LIST) {
  if (argument.length() < 2) {
	return;
  }
  //DO SORT
  CSV::CSV *temp = LIST->getHead();
  while (temp != nullptr) {
	int count = 0;
	switch (temp->getCOLUMNDATATYPE()) {
	  case CSV::DATATYPE::INT:
		count = BSearchSPEC(BSortINT(argument, temp), argument, temp);
		if (count <= -1) {
		  std::cout << "NOTHING FOUND IN " << temp->getCategory() << "\n";
		} else {
		  //std::cout << "\'" << argument << "\' FOUND IN " << temp->getCategory() << " AT ROW: " << count << "\n";
		  std::cout << "\'" << argument << "\' FOUND IN " << temp->getCategory() << "\n";
		}
		break;
	  case CSV::DATATYPE::DOUBLE:
		count = BSearchSPEC(BSortDBL(argument, temp), argument, temp);
		if (count <= -1) {
		  std::cout << "NOTHING FOUND IN " << temp->getCategory() << "\n";
		} else {
		  std::cout << "\'" << argument << "\' FOUND IN " << temp->getCategory() << "\n";
		}
		break;
	  case CSV::DATATYPE::CHAR:
		count = BSearchSPEC(BSortCHAR(argument, temp), argument, temp);
		if (count <= -1) {
		  std::cout << "NOTHING FOUND IN " << temp->getCategory() << "\n";
		} else {
		  std::cout << "\'" << argument << "\' FOUND IN " << temp->getCategory() << "\n";
		}
		break;
	  case CSV::DATATYPE::STRING:
		count = BSearchSPEC(BSortSTR(argument, temp), argument, temp);
		if (count <= -1) {
		  std::cout << "NOTHING FOUND IN " << temp->getCategory() << "\n";
		} else {
		  std::cout << "\'" << argument << "\' FOUND IN " << temp->getCategory() << "\n";
		}
		break;
	  default:
		std::cout << "CRITICAL ERROR\n";
		return;
	}
	temp = temp->next;
  }
}

std::vector<std::string> BSortINT(std::string argument, CSV::CSV *temp) {
  int count = 0;
  int totalelements = temp->getTotalElements();
  std::vector<std::pair<int, int>> arr;
  std::vector<std::string> rval;
  //std::vector<std::string> rval;
  int oldValues[totalelements];
  int oldKeys[totalelements];
  int newValues[totalelements];
  int newKeys[totalelements];

  for (auto &item : temp->getElementsINT()) {
	arr.emplace_back(item);
  }
  for (auto &[key, value] : arr) {
	oldKeys[count] = key;
	oldValues[count] = value;
	count++;
  }
  count = 0;

  std::sort(arr.begin(), arr.end(), [](auto &x, auto &y) { return x.second < y.second; });

  for (auto &[key, value] : arr) {
	/*for(int i = 0; i < totalelements - 1; i++){
	  if(oldValues[i] == value){
		rval[i] = std::to_string(value);
	  }
	}*/
	rval.push_back(std::to_string(value));
	count++;
  }

  return rval;
}

std::vector<std::string> BSortDBL(std::string argument, CSV::CSV *temp) {
  int count = 0;
  int totalelements = temp->getTotalElements();
  std::vector<std::pair<int, double>> arr;
  std::vector<std::string> rval;
  double newValues[totalelements];

  for (auto &item : temp->getElementsDBL()) {
	arr.emplace_back(item);
  }

  count = 0;

  std::sort(arr.begin(), arr.end(), [](auto &x, auto &y) { return x.second < y.second; });

  for (auto &[key, value] : arr) {
	//newKeys[count] = key;
	//newValues[count] = value;
	rval.push_back(std::to_string(value));
	count++;
  }

  return rval;
}

std::vector<std::string> BSortCHAR(std::string argument, CSV::CSV *temp) {
  int count = 0;
  int totalelements = temp->getTotalElements();
  std::vector<std::pair<int, char *>> arr;
  std::vector<std::string> rval;
  int newValues[totalelements];

  for (auto &item : temp->getElementsCHAR()) {
	arr.emplace_back(item);
  }
  count = 0;

  std::sort(arr.begin(), arr.end(), [](auto &x, auto &y) { return x.second < y.second; });

  for (auto &[key, value] : arr) {
	//newKeys[count] = key;
	//newValues[count] = value;
	rval.emplace_back(value);
	count++;
  }

  return rval;
}

std::vector<std::string> BSortSTR(std::string argument, CSV::CSV *temp) {
  int count = 0;
  int totalelements = temp->getTotalElements();
  std::vector<std::pair<int, std::string>> arr;
  std::vector<std::string> rval;
  int newValues[totalelements];

  for (auto &item : temp->getElementsSTR()) {
	arr.emplace_back(item);
  }
  count = 0;

  std::sort(arr.begin(), arr.end(), [](auto &x, auto &y) { return x.second < y.second; });

  for (auto &[key, value] : arr) {
	//newKeys[count] = key;
	//newValues[count] = value;
	rval.push_back(value);
	count++;
  }

  return rval;
}

int BSearchSPEC(std::vector<std::string> arr, const std::string &argument, CSV::CSV *temp) {
  int lower = 0;
  int upper = arr.size() - 1;
  while (lower <= upper) {
	int mid = lower + (upper - lower) / 2;
	int res;
	//|| arr[mid].find(argument)
	if (argument == (arr[mid])) {
	  //std::cout << "\n1. ARGUMENT = " << argument << " | arr[mid] = " << arr[mid] << "\n";
	  res = 0;
	  //return 1;
	}
	if (res == 0) {
	  //std::cout << "\n2. RES = 0\n";
	  return mid;
	}
	if (argument > (arr[mid])) {
	  //std::cout << "\n3. ARGUMENT = " << argument << " | arr[mid] = " << arr[mid] << "\n";
	  lower = mid + 1;
	  //return 2;
	} else {
	  upper = mid - 1;
	}
  }
  //std::cout << "\nARGUMENT NOT FOUND\n";
  return -1;
}

void ISort(bool lowtohigh, CSV::CSVLL *LIST, int index) {
  CSV::CSV *temp = LIST->getPTR(index);

  switch (temp->getCOLUMNDATATYPE()) {
	case CSV::DATATYPE::INT:
	  /*std::cout << "BEFORE: \n";
	  temp->displayElements();
	  std::cout << "AFTER: \n";*/
	  INTMAPTOVEC(lowtohigh, temp, index);
	  //searchList[index].displayElements();
	  break;
	case CSV::DATATYPE::DOUBLE:
	  DOUBLEMAPTOVEC(lowtohigh, temp, index);
	  break;
	case CSV::DATATYPE::CHAR:
	  CHARMAPTOVEC(lowtohigh, temp, index);
	  break;
	case CSV::DATATYPE::STRING:
	  STRINGMAPTOVEC(lowtohigh, temp, index);
	  break;
	default:
	  std::cout << "CRITICAL ERROR\n";
	  return;
  }
}

void INTMAPTOVEC(bool lowtohigh, CSV::CSV *temp, int index) {
  int count = 0;
  int totalelements = temp->getTotalElements();
  std::vector<std::pair<int, int>> arr;
  /*std::vector<std::pair<int, double>> arrDBL;
  std::vector<std::pair<int, char*>> arrCHAR;
  std::vector<std::pair<int, std::string>> arrSTR;*/
  int oldKeys[totalelements];
  int oldValues[totalelements];
  int newKeys[totalelements];
  int newValues[totalelements];

  /*double newValuesDBL[totalelements];
  char *newValuesCHAR[totalelements];
  std::string newValuesSTR[totalelements];*/

  /*for (int i = 0; i < LIST->length(); i++) {
	switch (current->getCOLUMNDATATYPE()) {
	  case CSV::DATATYPE::INT:
		for (auto &item : temp->getElementsINT()) {
		  arr.emplace_back(item);
		}
		break;
	  case CSV::DATATYPE::DOUBLE:
		for (auto &item : temp->getElementsDBL()) {
		  arrDBL.emplace_back(item);
		}
		break;
	  case CSV::DATATYPE::CHAR:
		for (auto &item : temp->getElementsCHAR()) {
		  arrCHAR.emplace_back(item);
		}
		break;
	  case CSV::DATATYPE::STRING:
		for (auto &item : temp->getElementsSTR()) {
		  arrSTR.emplace_back(item);
		}
		break;
	}
  }*/

  /* for (int i = 0; i < LIST->length(); i++) {
	 switch (current->getCOLUMNDATATYPE()) {
	   case CSV::DATATYPE::INT:
		 for (auto &[key, value] : arr) {
		   oldKeys[count] = key;
		   oldValues[count] = value;
		   count++;
		 }
		 count = 0;
		 break;
	   case CSV::DATATYPE::DOUBLE:
		 for (auto &[key, value] : arrDBL) {
		   oldKeys[count] = key;
		   oldValuesDB[count] = value;
		   count++;
		 }
		 count = 0;
		 break;
	   case CSV::DATATYPE::CHAR:
		 for (auto &[key, value] : arr) {
		   oldKeys[count] = key;
		   oldValues[count] = value;
		   count++;
		 }
		 count = 0;
		 break;
	   case CSV::DATATYPE::STRING:
		 for (auto &[key, value] : arr) {
		   oldKeys[count] = key;
		   oldValues[count] = value;
		   count++;
		 }
		 count = 0;
		 break;
	 }
   }*/

  for (auto &item : temp->getElementsINT()) {
	arr.emplace_back(item);
  }

  for (auto &[key, value] : arr) {
	oldKeys[count] = key;
	oldValues[count] = value;
	count++;
  }
  count = 0;

  std::sort(arr.begin(), arr.end(), [](auto &x, auto &y) { return x.second < y.second; });

  if (!lowtohigh) {
	std::reverse(arr.begin(), arr.end());
  }

  for (auto &[key, value] : arr) {
	newKeys[count] = key;
	newValues[count] = value;
	count++;
  }
  count = 0;
  std::cout << "OLD:\n";
  for (int i = 0; i < totalelements; i++) {
	//std::cout << "OLD - KEY: " << oldKeys[i] << " | VALUE: " << oldValues[i] << "\n";
	std::cout << oldValues[i] << "\n";
  }
  std::cout << "\n";
  std::cout << "NEW:\n";
  for (int i = 0; i < totalelements; i++) {
	//std::cout << "NEW - KEY: " << newKeys[i] << " | VALUE: " << newValues[i] << "\n";
	std::cout << newValues[i] << "\n";
  }

  /*for (int i = 0; i < LIST->length(); i++) {
	std::map<int,int>::iterator itr;
	switch (current->getCOLUMNDATATYPE()) {
	  count = 0;
	  case CSV::DATATYPE::INT:
		int previous;
		for (itr=current->elementsINT.begin(); itr!=current->elementsINT.end(); itr++){
		  previous = itr->second;
		  itr->second = current->elementsINT[newKeys[count]];
		  current->elementsINT[newKeys[count]] = previous;
		  std::cout << "\nSAVE-------->" << previous << " <--------\n";
		  std::cout << "\nNEW-------->" << itr->second << " <--------\n";
		  std::cout << "\nOLD-------->" << current->elementsINT[newKeys[count]] << " <--------\n";
		  count++;
		}
		*//*for (int j = 0; j < current->getTotalElements(); j++){
		  previous = current->elementsINT[j];
		  //std::cout << "\nSAVE-------->" << previous << " <--------\n";
		  //std::cout << "\nNEW-------->" << current->elementsINT[newKeys[j]] << " <--------\n";
		  //std::cout << "\nOLD-------->" << current->elementsINT[j] << " <--------\n";
		  current->elementsINT[j] = current->elementsINT[newKeys[j]];
		  current->elementsINT[newKeys[j]] = previous;
		  std::cout << "\nNEW2.0-------->" << current->elementsINT[newKeys[j]] << " <--------\n";
		  *//**//*if(newKeys[j] != j) {
		  }*//**//*
		}*//*
		current = current->next;
		break;
		*//*current->elementsINT.clear();
		for (int j = 0; j < current->getTotalElements(); j++){
		  current->elementsINT[j] = newValues[j];
		}
		current = current->next;
		break;*//*
	  case CSV::DATATYPE::DOUBLE:
		double previous1;
		for (int j = 0; j < current->getTotalElements(); j++){
		  previous1 = current->elementsDBL[j];
		  current->elementsDBL[j] = current->elementsDBL[newKeys[j]];
		  if(newKeys[j] != j) {
			current->elementsDBL[newKeys[j]] = previous1;
		  }
		}
		current = current->next;
		break;
	  case CSV::DATATYPE::CHAR:
		char *previous2;
		for (int j = 0; j < current->getTotalElements(); j++){
		  previous2 = current->elementsCHAR[j];
		  current->elementsCHAR[j] = current->elementsCHAR[newKeys[j]];
		  if(newKeys[j] != j) {
			current->elementsCHAR[newKeys[j]] = previous2;
		  }
		}
		current = current->next;
		break;
	  case CSV::DATATYPE::STRING:
		std::string previous3;
		for (int j = 0; j < current->getTotalElements(); j++){
		  previous3 = current->elementsSTR[j];
		  current->elementsSTR[j] = current->elementsSTR[newKeys[j]];
		  if(newKeys[j] != j){
			current->elementsSTR[newKeys[j]] = previous3;
		  }
		}
		current = current->next;
		break;
	}
  }*/

  /*for (auto & [key, value] : arr) {
	//std::cout << count << ". KEY:" << key << " : " << value << "\n";
	searchList[index].setElementsINT(count, value);
	count++;
  }*/
}

void DOUBLEMAPTOVEC(bool lowtohigh, CSV::CSV *temp, int index) {
  int count = 0;
  int totalelements = temp->getTotalElements();
  std::vector<std::pair<int, double>> arr;
  /*std::vector<std::pair<int, double>> arrDBL;
  std::vector<std::pair<int, char*>> arrCHAR;
  std::vector<std::pair<int, std::string>> arrSTR;*/
  int oldKeys[totalelements];
  double oldValues[totalelements];
  int newKeys[totalelements];
  double newValues[totalelements];

  for (auto &item : temp->getElementsDBL()) {
	arr.emplace_back(item);
  }

  for (auto &[key, value] : arr) {
	oldKeys[count] = key;
	oldValues[count] = value;
	count++;
  }
  count = 0;

  std::sort(arr.begin(), arr.end(), [](auto &x, auto &y) { return x.second < y.second; });

  if (!lowtohigh) {
	std::reverse(arr.begin(), arr.end());
  }

  for (auto &[key, value] : arr) {
	newKeys[count] = key;
	newValues[count] = value;
	count++;
  }
  count = 0;
  std::cout << "OLD:\n";
  for (int i = 0; i < totalelements; i++) {
	//std::cout << "OLD - KEY: " << oldKeys[i] << " | VALUE: " << oldValues[i] << "\n";
	std::cout << oldValues[i] << "\n";
  }
  std::cout << "\n";
  std::cout << "NEW:\n";
  for (int i = 0; i < totalelements; i++) {
	//std::cout << "NEW - KEY: " << newKeys[i] << " | VALUE: " << newValues[i] << "\n";
	std::cout << newValues[i] << "\n";
  }
}

void CHARMAPTOVEC(bool lowtohigh, CSV::CSV *temp, int index) {
//  std::regex pattern("^(?=.*[A-Z]).+$");
//  std::regex pattern2("^(?=.*[a-z]).+$");
//  std::regex pattern3("^(?=.*[0-9]).+$");
  int count = 0;
  int totalelements = temp->getTotalElements();
  std::vector<std::pair<int, char *>> arr;
  /*std::vector<std::pair<int, double>> arrDBL;
  std::vector<std::pair<int, char*>> arrCHAR;
  std::vector<std::pair<int, std::string>> arrSTR;*/
  int oldKeys[totalelements];
  char *oldValues[totalelements];
  int newKeys[totalelements];
  char *newValues[totalelements];

  for (auto &item : temp->getElementsCHAR()) {
	arr.emplace_back(item);
  }

  /*char previous = *item.second;
  std::string current = std::to_string(previous);
  current = current.at(0);
  if (std::regex_match(current, pattern) || std::regex_match(current, pattern2)){

  }
  else if(std::regex_match(current, pattern3)){

  }*/

  for (auto &[key, value] : arr) {
	oldKeys[count] = key;
	oldValues[count] = value;
	count++;
  }
  count = 0;

  std::sort(arr.begin(), arr.end(), [](auto &x, auto &y) { return x.second < y.second; });

  if (!lowtohigh) {
	std::reverse(arr.begin(), arr.end());
  }

  for (auto &[key, value] : arr) {
	newKeys[count] = key;
	newValues[count] = value;
	count++;
  }
  count = 0;
  std::cout << "OLD:\n";
  for (int i = 0; i < totalelements; i++) {
	//std::cout << "OLD - KEY: " << oldKeys[i] << " | VALUE: " << oldValues[i] << "\n";
	std::cout << oldValues[i] << "\n";
  }
  std::cout << "\n";
  std::cout << "NEW:\n";
  for (int i = 0; i < totalelements; i++) {
	//std::cout << "NEW - KEY: " << newKeys[i] << " | VALUE: " << newValues[i] << "\n";
	std::cout << newValues[i] << "\n";
  }
}

void STRINGMAPTOVEC(bool lowtohigh, CSV::CSV *temp, int index) {
//  std::regex pattern("^(?=.*[A-Z]).+$");
//  std::regex pattern2("^(?=.*[a-z]).+$");
//  std::regex pattern3("^(?=.*[0-9]).+$");
  int count = 0;
  int totalelements = temp->getTotalElements();
  std::vector<std::pair<int, std::string>> arr;
  /*std::vector<std::pair<int, double>> arrDBL;
  std::vector<std::pair<int, char*>> arrCHAR;
  std::vector<std::pair<int, std::string>> arrSTR;*/
  int oldKeys[totalelements];
  std::string oldValues[totalelements];
  int newKeys[totalelements];
  std::string newValues[totalelements];

  for (auto &item : temp->getElementsSTR()) {
	arr.emplace_back(item);
  }

  /*char previous = *item.second;
  std::string current = std::to_string(previous);
  current = current.at(0);
  if (std::regex_match(current, pattern) || std::regex_match(current, pattern2)){

  }
  else if(std::regex_match(current, pattern3)){

  }*/

  for (auto &[key, value] : arr) {
	oldKeys[count] = key;
	oldValues[count] = value;
	count++;
  }
  count = 0;

  std::sort(arr.begin(), arr.end(), [](auto &x, auto &y) { return x.second < y.second; });

  if (!lowtohigh) {
	std::reverse(arr.begin(), arr.end());
  }

  for (auto &[key, value] : arr) {
	newKeys[count] = key;
	newValues[count] = value;
	count++;
  }
  count = 0;
  std::cout << "OLD:\n";
  for (int i = 0; i < totalelements; i++) {
	//std::cout << "OLD - KEY: " << oldKeys[i] << " | VALUE: " << oldValues[i] << "\n";
	std::cout << oldValues[i] << "\n";
  }
  std::cout << "\n";
  std::cout << "NEW:\n";
  for (int i = 0; i < totalelements; i++) {
	//std::cout << "NEW - KEY: " << newKeys[i] << " | VALUE: " << newValues[i] << "\n";
	std::cout << newValues[i] << "\n";
  }
}

/*void RRange(int key, int count, CSV::CSVLL *LIST){

  for(int i = 0; i < searchList.size(); i++){
	for(int j = 0; j < searchList[i].getTotalElements(); j++){
	  switch(searchList[i].getCOLUMNDATATYPE()){
		case DATATYPE::INT:
		  int previousK;
		  int previousV;
		  int currentK;
		  int currentV;
		  //previousK = ;

		  break;
		case DATATYPE::DOUBLE:
		  break;
		case DATATYPE::CHAR:
		  break;
		case DATATYPE::STRING:
		  break;
	  }
	}
  }

}*/

/*
int Console::Get_Input_By_INT() //Function can return any integer.
{
  std::string input; //Crate a variable where the user can input anything.

  int converted; //Create a variable that will output only an integer.
  while (true) {
	std::cin >> input; //Request input from user.
	try {
	  converted = std::stoi(input); //If conversion from string to integer is successful then break the loop.
	  break;
	}
	catch (std::invalid_argument &i) { //If user entered a char or a char array throw an exception.
	  PTC(i.what());
	  PTC("\n!EXCEPTION!\n");
	  LogHook->PTF("\n!EXCEPTION!\n !STOI INVALID ARGUMENT!: ", input, "\n");
	}
	catch (std::out_of_range &i) { //If user went out of bounds of string throw an exception.
	  PTC(i.what());
	  PTC("\n!EXCEPTION!\n");
	  LogHook->PTF("\n!EXCEPTION!\n !STOI OUT OF RANGE!: ", input, "\n");
	}
  }
  return converted;
}*/

void REVERSE(bool colorrow, CSV::CSVLL *LIST, int index) {
  if (colorrow) {
	if (index >= LIST->length() || index < 0) {
	  std::cout << "\nINDEX OUT OF BOUNDS\n";
	  return;
	}
	CSV::CSV *temp = LIST->getPTR(index);
	CSV::DATATYPE dtype = static_cast<CSV::DATATYPE>(temp->getCOLUMNDATATYPE());
	std::stack<std::string> column;

	for (int i = 0; i < temp->getTotalElements(); i++) {
		switch(dtype){
		  case CSV::DATATYPE::INT:
			column.push(std::to_string(temp->getElementsINT()[i]));
			break;
		  case CSV::DATATYPE::DOUBLE:
			column.push(std::to_string(temp->getElementsDBL()[i]));
			break;
		  case CSV::DATATYPE::CHAR:
			column.push(temp->getElementsCHAR()[i]);
			break;
		  case CSV::DATATYPE::STRING:
			column.push(temp->getElementsSTR()[i]);
			break;
		}
	}

	while (!column.empty()) {
		std::cout << column.top() << std::endl;
		column.pop();
	}

  } else {
	if (index >= LIST->getHead()->getTotalElements() || index < 0) {
	  std::cout << "\nINDEX OUT OF BOUNDS\n";
	  return;
	}
	std::stack<std::string> column;

	for(int i = 0; i < LIST->length(); i++){
	  switch(LIST->getPTR(i)->getCOLUMNDATATYPE()){
		case CSV::DATATYPE::INT:
		  column.push(std::to_string(LIST->getPTR(i)->getElementsINT()[index]));
		  break;
		case CSV::DATATYPE::DOUBLE:
		  column.push(std::to_string(LIST->getPTR(i)->getElementsDBL()[index]));
		  break;
		case CSV::DATATYPE::CHAR:
		  column.push(LIST->getPTR(i)->getElementsCHAR()[index]);
		  break;
		case CSV::DATATYPE::STRING:
		  column.push(LIST->getPTR(i)->getElementsSTR()[index]);
		  break;
	  }
	}

	std::string app = "";
	app.append(std::to_string(index + 1) + ". ");
	while (!column.empty()) {
	  app.append(column.top() + " | ");
	  column.pop();
	}
	std::cout << app << "\n";

  }
}

}