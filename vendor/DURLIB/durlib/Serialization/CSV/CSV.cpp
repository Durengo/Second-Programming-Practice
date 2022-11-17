#include "CSV.h"

#include <regex>

namespace DURLIB
{
	namespace CSV
	{

		/*CSV::CSV(const std::string &FILEPATH){
		  this->next = nullptr;
		  if(readCSV(FILEPATH, this) != 0){
			std::cout << "\nCRITICAL ERROR\n";
			delete(this);
		  }
		}*/
		CSV::CSV(const std::string &categoryName)
		{
			this->next = nullptr;
			category = categoryName;
		}
		CSV::~CSV()
		{
		}

		void CSV::freeMem()
		{
			delete (this);
		}

		const std::string &CSV::getCategory() const
		{
			return category;
		}

		void CSV::setCategory(const std::string &category)
		{
			CSV::category = category;
		}

		const std::vector<std::string> &CSV::getElements() const
		{
			return elements;
		}

		void CSV::setElements(const std::string &elements)
		{
			sortElement(elements);
			CSV::elements.push_back(elements);
			elementcount++;
		}

		int CSV::getTotalElements()
		{
			return elementcount;
		}

		int CSV::getCOLUMNDATATYPE() const
		{
			return CSV::COLUMNDATATYPE;
		}

		//--------------INT--------------

		std::map<int, int> CSV::getElementsINT()
		{
			return CSV::elementsINT;
		}

		void CSV::setElementsINT(int key, int value)
		{
			CSV::elementsINT[key] = value;
		}

		//--------------DOUBLE--------------

		std::map<int, double> CSV::getElementsDBL()
		{
			return CSV::elementsDBL;
		}

		void CSV::setElementsDBL(int key, double value)
		{
			CSV::elementsDBL[key] = value;
		}

		//--------------CHAR--------------

		std::map<int, char *> CSV::getElementsCHAR()
		{
			return CSV::elementsCHAR;
		}

		void CSV::setElementsCHAR(int key, char *value)
		{
			CSV::elementsCHAR[key] = value;
		}

		//--------------STRING--------------

		std::map<int, std::string> CSV::getElementsSTR()
		{
			return CSV::elementsSTR;
		}

		void CSV::setElementsSTR(int key, std::string &value)
		{
			CSV::elementsSTR[key] = value;
		}

		void CSV::displayElements()
		{
			std::cout << category << ":\n";
			switch (COLUMNDATATYPE)
			{
			case DATATYPE::INT:
				for (int i = 0; i < CSV::elementcount; i++)
				{
					std::cout << i + 1 << ". " << elementsINT[i] << "\n";
				}
				break;
			case DATATYPE::DOUBLE:
				for (int i = 0; i < CSV::elementcount; i++)
				{
					std::cout << i + 1 << ". " << elementsDBL[i] << "\n";
				}
				break;
			case DATATYPE::CHAR:
				for (int i = 0; i < CSV::elementcount; i++)
				{
					std::cout << i + 1 << ". " << elementsCHAR[i] << "\n";
				}
				break;
			case DATATYPE::STRING:
				for (int i = 0; i < CSV::elementcount; i++)
				{
					std::cout << i + 1 << ". " << elementsSTR[i] << "\n";
				}
				break;
			default:
				break;
			}
		}

		void CSV::sortElement(const std::string &elements)
		{
			int tryint = 0;
			double trydouble = 0.0;
			// std::cout << "\nPARSE ELEMENT = " << elements << "\n";
			if (CSV::COLUMNDATATYPE == 0)
			{
				while (CSV::COLUMNDATATYPE == 0)
				{
					try
					{
						std::regex pattern("^(?=.*[A-Z]).+$");
						std::regex pattern2("^(?=.*[a-z]).+$");
						std::regex pattern3("^(?=.*[0-9]).+$");
						if (std::regex_match(elements, pattern) || std::regex_match(elements, pattern2))
						{
							if (std::regex_match(elements, pattern3) || !elements.find("\\"))
							{
								// std::cout << "NO WHITESPACE FOUND\n";
								COLUMNDATATYPE = DATATYPE::CHAR;
								char *trychar = new char[elements.size() + 1];
								memcpy(trychar, elements.c_str(), elements.size() + 1);
								/*char trychar[elements.length() + 1];
								strcpy(trychar, elements.c_str());*/
								CSV::elementsCHAR[CSV::elementcount] = trychar;
								/*std::cout << elements.c_str() << " / " << trychar << "\n" << CSV::COLUMNDATATYPE << std::endl;
								std::cout << " size of elements: " << sizeof(elements) << " | sizeof trychar: " << sizeof(trychar) << "\n";
								std::cout << "\n size of string: " << sizeof(std::string) << "\n";*/
								break;
							}
							if (elements.find("\\"))
							{
								// std::cout << elements << "\n";
								// std::cout << "WHITESPACE FOUND\n";
								COLUMNDATATYPE = DATATYPE::STRING;
								CSV::elementsSTR[CSV::elementcount] = elements;
								break;
							}
							/*else {
							  std::cout << "NO WHITESPACE FOUND\n";
							  COLUMNDATATYPE = DATATYPE::CHAR;
							  char trychar[elements.length() + 1];
							  strcpy(trychar, elements.c_str());
							  CSV::elementsCHAR[elementcount] = trychar;
							  break;
							}*/
						}
						tryint = std::stoi(elements);
						{
							std::cout << "int found\n";
							COLUMNDATATYPE = DATATYPE::INT;
							CSV::elementsINT[CSV::elementcount] = tryint;
							break;
						}
					}
					// catch (std::invalid_argument &i) {
					catch (std::invalid_argument)
					{
						// std::cout << i.what() << "\n";
					}
					// catch (std::out_of_range &i) {
					catch (std::out_of_range)
					{
						// std::cout << i.what() << "\n";
					}
					try
					{
						trydouble = std::stod(elements);
						{
							std::cout << "double found\n";
							COLUMNDATATYPE = DATATYPE::DOUBLE;
							CSV::elementsDBL[CSV::elementcount] = trydouble;
							break;
						}
					}
					// catch (std::invalid_argument &i) {
					catch (std::invalid_argument)
					{
						// std::cout << i.what() << "\n";
					}
					// catch (std::out_of_range &i) {
					catch (std::out_of_range)
					{
						// std::cout << i.what() << "\n";
					}
				}
			}
			else
			{
				switch (COLUMNDATATYPE)
				{
				case DATATYPE::INT:
					tryint = std::stoi(elements);
					CSV::elementsINT[CSV::elementcount] = tryint;
					break;
				case DATATYPE::DOUBLE:
					trydouble = std::stod(elements);
					CSV::elementsDBL[CSV::elementcount] = trydouble;
					break;
				case DATATYPE::STRING:
					CSV::elementsSTR[CSV::elementcount] = elements;
					break;
				case DATATYPE::CHAR:
					/*char trychar[elements.length() + 1];
					strcpy(trychar, elements.c_str());*/
					char *trychar = new char[elements.size() + 1];
					memcpy(trychar, elements.c_str(), elements.size() + 1);
					CSV::elementsCHAR[CSV::elementcount] = trychar;
					break;
				}
			}
		}

		//----PARSING---

		/*int readCSV(const std::string &FILEPATH, CSV *CSVOBJ) {
		  std::fstream CSVFILE;
		  CSVFILE.open(FILEPATH, std::ios::in);
		  if (CSVFILE.is_open()) { std::cout << "FILE OPENED SUCCESSFULLY\n"; }
		  else { std::cout << "FILE FAILED TO OPEN\n"; return -1; }
		  parseCSV(CSVFILE, CSVOBJ);
		  return 0;
		}

		void parseCSV(std::fstream &CSVFILE, CSV *CSVOBJ) {
		  std::string line, word, temp;

		  std::cout << "\nLoading File...\n";

		  getline(CSVFILE, line);
		  parseColumns(line, CSVOBJ);

		  while (getline(CSVFILE, line)) {
			parseElements(line, CSVOBJ);
		  }
		}

		void parseColumns(const std::string &line, CSV *CSVOBJ) {
		  std::string main = line;
		  std::string temp;
		  bool firstColumnChecked = false;

		  while (!main.empty()) {
			if (main.length() <= 4) {
			  main = "";
			  break;
			}
			//First column
			if (main.find(',') != std::string::npos && !firstColumnChecked) {
			  firstColumnChecked = true;

			  temp = main.substr(1, main.find(',', +1) - 2);
			  main = main.substr(main.find(',', +1), main.length());

			  CSV col;
			  col.setCategory(temp);
			  newCSV.push_back(col);
			}
			//Second column
			if (main.find(',') != std::string::npos) {

			  temp = main.substr(2, main.find(',', +1) - 3);
			  main = main.substr(main.find(',', +1), main.length());

			  CSV col;
			  col.setCategory(temp);
			  newCSV.push_back(col);
			}
		  }
		}

		void parseElements(const std::string &line, CSV *CSVOBJ) {
		  std::string main = line;
		  std::string temp;
		  int colcount = 0;
		  bool firstColumnChecked = false;
		  //std::cout << main << "\n";
		  bool mode = false;

		  while (!main.empty()) {
			if (main.length() == 1) {
			  main = "";
			  break;
			}
			if (main.find(',') != std::string::npos) {
			  temp = main.substr(main.find('"') + 1, main.find('"', +1) - 1);
			  main = main.substr(main.find('"', +2) + 2, main.length());

			  newCSV[colcount].setElements(temp);
			  colcount++;
			  //std::cout << "temp : " << temp << "\n";
			  //std::cout << "main : " << main << "\n";
			}
		  }
		}*/

	}
}