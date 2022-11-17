#include "CSVLL.h"

namespace DURLIB
{
	namespace CSV
	{
		CSVLL::CSVLL(const std::string &FILEPATH)
		{
			this->head = nullptr;
			if (readCSV(FILEPATH, this) != 0)
			{
				std::cout << "\nCRITICAL ERROR\n";
				delete (this);
			}
		}

		int CSVLL::length()
		{
			int len = 0;
			CSV *temp = head;
			while (temp != nullptr)
			{
				len++;
				temp = temp->next;
			}
			return len;
		}

		void CSVLL::displayTable(bool neatly)
		{
			if (head == nullptr)
			{
				std::cout << "\nTABLE IS EMPTY\n";
				return;
			}
			CSV *temp = head;
			std::string tempstring = "";
			std::cout << "\n-----TABLE (COLUMN(-S)) CATEGORIES AND ELEMENTS-----\n";
			std::string TABLE = "COLUMN CATEGORY --->  ";
			switch (neatly)
			{
			case true:
				while (temp != nullptr)
				{
					TABLE.append(temp->getCategory() + " | ");
					temp = temp->next;
				}
				temp = head;
				TABLE.append("\n");
				//	  TABLE.append("ROW NUMBER         | \n"
				//				   "				   | \n"
				//				   "				   V \n");
				TABLE.append("ROW NUMBER| \n"
							 "	  | \n"
							 "	  V \n");
				for (int i = 0; i < this->getHead()->getTotalElements(); i++)
				{
					int count = 0;
					count = i + 1;
					// TABLE.append("				   ");
					TABLE.append("	  ");
					TABLE.append(std::to_string(count));
					TABLE.append(". ");
					while (temp != nullptr)
					{
						// int check = temp->getCOLUMNDATATYPE();
						// std::cout << "\n" << j << " - " << this->getPTR(j)->getCategory() << "";
						// std::cout << "\nJ =" << j << " - length = " << this->length() << "\n";
						// std::cout << temp->getCategory() << "\n";
						switch (temp->getCOLUMNDATATYPE())
						{
						case DATATYPE::INT:
							TABLE.append(std::to_string(temp->getElementsINT()[i]));
							// temp = temp->next;
							break;
						case DATATYPE::DOUBLE:
							TABLE.append(std::to_string(temp->getElementsDBL()[i]));
							// temp = temp->next;
							break;
						case DATATYPE::CHAR:
							tempstring = temp->getElementsCHAR()[i];
							TABLE.append(tempstring);
							tempstring.clear();
							// std::cout << temp->getElementsCHAR()[i];
							// temp = temp->next;
							break;
						case DATATYPE::STRING:
							TABLE.append(temp->getElementsSTR()[i]);
							// std::cout << temp->getElementsSTR()[i];
							// temp = temp->next;
							break;
						default:
							break;
							std::cout << "\nSOMETHING WONG\n";
						}
						temp = temp->next;
						TABLE.append(" | ");
					}
					/*for(int j = 0; j < this->length(); j++){
					  int check = this->getPTR(j)->getCOLUMNDATATYPE();
					  std::cout << "\n" << j << " - " << this->getPTR(j)->getCategory() << "";
					  std::cout << "\nJ =" << j << " - length = " << this->length() << "\n";
					  switch(check){
						case DATATYPE::INT:
							TABLE.append(std::to_string(this->getPTR(j)->getElementsINT()[i]));
						  //temp = temp->next;
						  //break;
						case DATATYPE::DOUBLE:
							TABLE.append(std::to_string(this->getPTR(j)->getElementsDBL()[i]));
						  //temp = temp->next;
						  //break;
						case DATATYPE::CHAR:
							TABLE.append(this->getPTR(j)->getElementsCHAR()[i]);
							//std::cout << temp->getElementsCHAR()[i];
						  //temp = temp->next;
						  //break;
						case DATATYPE::STRING:
							TABLE.append(this->getPTR(j)->getElementsSTR()[i]);
							//std::cout << temp->getElementsSTR()[i];
						  //temp = temp->next;
						  //break;
						default:
						  break;
						  std::cout << "\nSOMETHING WONG\n";
					  }
					  //temp = temp->next;
					  TABLE.append(" | ");
					}*/
					temp = head;
					TABLE.append("\n");
				}
				std::cout << TABLE;
				break;
			case false:
				while (temp != nullptr)
				{
					temp->displayElements();
					temp = temp->next;
				}
				break;
			}
			std::cout << "----------------------------------------------------\n";
		}

		void CSVLL::displayColumn(int index)
		{
			if (head == nullptr)
			{
				std::cout << "\nTABLE IS EMPTY\n";
				return;
			}
			if (index >= length() || index < 0)
			{
				std::cout << "\nINDEX OUT OF BOUNDS\n";
				return;
			}
			CSV *temp = head;
			for (int i = 0; i < index; i++)
			{
				temp = temp->next;
			}
			std::cout << "COLUMN - " << temp->getCategory() << "\n";
			switch (temp->getCOLUMNDATATYPE())
			{
			case DATATYPE::INT:
				for (int i = 0; i < temp->getTotalElements(); i++)
				{
					std::cout << i + 1 << ". " << temp->elementsINT[i] << "\n";
				}
				break;
			case DATATYPE::DOUBLE:
				for (int i = 0; i < temp->getTotalElements(); i++)
				{
					std::cout << i + 1 << ". " << temp->elementsDBL[i] << "\n";
				}
				break;
			case DATATYPE::CHAR:
				for (int i = 0; i < temp->getTotalElements(); i++)
				{
					std::cout << i + 1 << ". " << temp->elementsCHAR[i] << "\n";
				}
				break;
			case DATATYPE::STRING:
				for (int i = 0; i < temp->getTotalElements(); i++)
				{
					std::cout << i + 1 << ". " << temp->elementsSTR[i] << "\n";
				}
				break;
			}
		}

		void CSVLL::displayRow(int index)
		{
			if (head == nullptr)
			{
				std::cout << "\nTABLE IS EMPTY\n";
				return;
			}
			CSV *temp = head;
			if (index > temp->getTotalElements() - 1 || index < 0)
			{
				std::cout << "\nINDEX OUT OF BOUNDS\n";
				return;
			}
			std::string STORE = "";
			while (temp != nullptr)
			{
				for (int i = 0; i < length(); i++)
				{
					STORE.append(temp->getCategory() + " | ");
					temp = temp->next;
				}
				STORE.append("\n");
				temp = head;
				std::string CURRENT;
				int count = 0;
				for (int i = 0; i < length(); i++)
				{
					switch (temp->getCOLUMNDATATYPE())
					{
					case DATATYPE::INT:
						CURRENT.empty();
						count = temp->elementsINT[index];
						CURRENT = std::to_string(count);
						STORE.append(CURRENT + " | ");
						temp = temp->next;
						break;
					case DATATYPE::DOUBLE:
						CURRENT.empty();
						CURRENT = temp->elementsDBL[index];
						STORE.append(CURRENT + " | ");
						temp = temp->next;
						break;
					case DATATYPE::CHAR:
						CURRENT.empty();
						CURRENT = temp->elementsCHAR[index];
						STORE.append(CURRENT + " | ");
						temp = temp->next;
						break;
					case DATATYPE::STRING:
						CURRENT.empty();
						CURRENT = temp->elementsSTR[index];
						STORE.append(temp->elementsSTR[index] + " | ");
						temp = temp->next;
						break;
					}
				}
			}
			std::cout << STORE << "\n";
		}

		CSV *CSVLL::getHead()
		{
			return head;
		}

		CSV *CSVLL::getPTR(int index)
		{
			if (index >= length() || index < 0)
			{
				std::cout << "\nINDEX OUT OF BOUNDS\n";
				return nullptr;
			}
			CSV *temp = head;
			int count = 0;
			while (temp != nullptr)
			{
				if (index == count)
				{
					return temp;
				}
				else
				{
					count++;
					temp = temp->next;
				}
			}
		}

		void CSVLL::addCSVelement(int index, const std::string &element)
		{
			if (index >= length() || index < 0)
			{
				std::cout << "\nINDEX OUT OF BOUNDS\n";
				return;
			}
			CSV *temp = head;
			for (int i = 0; i != index; i++)
			{
				temp = temp->next;
			}
			temp->setElements(element);
		}

		void CSVLL::add(const std::string &category)
		{
			auto *node = new CSV(category);
			if (head == nullptr)
			{
				head = node;
				std::cout << "New Category Created!"
						  << "\"" << category << "\"\n";
				std::cout << "LL LOCATION: HEAD\n";
				return;
			}
			CSV *temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = node;
			std::cout << "New Category Created!"
					  << "\"" << category << "\"\n";
			std::cout << "LL LOCATION: BACK\n";
		}

		void CSVLL::addFront(const std::string &category)
		{
			auto *node = new CSV(category);
			if (head == nullptr)
			{
				head = node;
				std::cout << "New Category Created!"
						  << "\"" << category << "\"\n";
				std::cout << "LL LOCATION: HEAD\n";
				return;
			}
			node->next = head;
			head = node;
			std::cout << "New Category Created!"
					  << "\"" << category << "\"\n";
			std::cout << "LL LOCATION: FRONT (NEW HEAD)\n";
		}

		void CSVLL::add(int index, const std::string &category)
		{
			if (index >= length() || index < 0)
			{
				std::cout << "\nINDEX OUT OF BOUNDS\n";
				return;
			}
			auto *node = new CSV(category);
			int count = 0;
			CSV *temp = head;
			while (temp != nullptr && count < index)
			{
				if (count == index - 1)
				{
					if (temp->next != nullptr)
					{
						node->next = temp->next;
					}
					temp->next = node;
					std::cout << "New Category Created!"
							  << "\"" << category << "\"\n";
					std::cout << "LL LOCATION: AT INDEX: " << index << "\n";
					break;
				}
				count++;
				temp = temp->next;
			}
		}

		void CSVLL::remove()
		{
			if (head == nullptr)
			{
				std::cout << "LL IS EMPTY\n";
				return;
			}
			if (head->next == nullptr)
			{
				std::string tempstr = head->next->getCategory();
				head->next->freeMem();
				head = nullptr;
				std::cout << "CATEGORY "
						  << "\"" + tempstr + "\""
						  << " REMOVED\n";
				std::cout << "LL LOCATION: BACK\n";
				return;
			}

			CSV *temp = head;
			while (temp != nullptr)
			{
				if (temp->next->next == nullptr)
				{
					std::string tempstr = head->next->next->getCategory();
					temp->next->next->freeMem();
					temp->next = nullptr;
					std::cout << "CATEGORY "
							  << "\"" + tempstr + "\""
							  << " REMOVED\n";
					std::cout << "LL LOCATION: BACK\n";
					break;
				}
				temp = temp->next;
			}
		}

		void CSVLL::remove(int index)
		{
			if (head == nullptr)
			{
				std::cout << "\nTABLE IS EMPTY\n";
				return;
			}
			if (index >= length() || index < 0)
			{
				std::cout << "\nINDEX OUT OF BOUNDS\n";
				return;
			}
			if (index == 0)
			{
				removeFront();
				return;
			}

			int count = 0;
			CSV *temp = head;
			while (temp != nullptr)
			{
				if (count == index - 1)
				{
					std::string tempstr = head->next->getCategory();
					temp->next->freeMem();
					temp->next = temp->next->next;
					std::cout << "Category Removed: "
							  << "\"" << tempstr << "\"\n";
					std::cout << "LL LOCATION: AT INDEX: " << index << "\n";
					break;
				}
				count++;
				temp = temp->next;
			}
		}

		void CSVLL::removeFront()
		{
			if (head == nullptr)
			{
				std::cout << "\nTABLE IS EMPTY\n"
						  << std::endl;
				return;
			}
			std::string tempstr = head->getCategory();
			head->freeMem();
			head = head->next;
			std::cout << "Category Removed: "
					  << "\"" << tempstr << "\"\n";
			std::cout << "LL LOCATION: BACK\n";
		}

		CSV *CSVLL::get(int index)
		{
			if (head == nullptr)
			{
				std::cout << "\nTABLE IS EMPTY\n";
				return nullptr;
			}
			if (index >= length() || index < 0)
			{
				std::cout << "\nINDEX OUT OF BOUNDS\n";
				return nullptr;
			}
			if (index == 0)
			{
				return head;
			}
			int count = 0;
			CSV *temp = head;
			while (temp != nullptr)
			{
				if (count++ == index)
				{
					return temp;
					break;
				}
				temp = temp->next;
			}
			return temp;
		}

		//------------PARSING------------

		int readCSV(const std::string &FILEPATH, CSVLL *LIST)
		{
			std::fstream CSVFILE;
			CSVFILE.open(FILEPATH, std::ios::in);
			if (CSVFILE.is_open())
			{
				std::cout << "FILE OPENED SUCCESSFULLY\n";
			}
			else
			{
				std::cout << "FILE FAILED TO OPEN\n";
				return -1;
			}
			parseCSV(CSVFILE, LIST);
			return 0;
		}

		void parseCSV(std::fstream &CSVFILE, CSVLL *LIST)
		{
			std::string line, word, temp;

			std::cout << "\nLoading File...\n";

			getline(CSVFILE, line);
			parseColumns(line, LIST);

			while (getline(CSVFILE, line))
			{
				parseElements(line, LIST);
			}
		}

		void parseColumns(const std::string &line, CSVLL *LIST)
		{
			std::string main = line;
			std::string temp;
			bool firstColumnChecked = false;

			while (!main.empty())
			{
				if (main.length() <= 4)
				{
					main = "";
					break;
				}
				// First column
				if (main.find(',') != std::string::npos && !firstColumnChecked)
				{
					firstColumnChecked = true;

					temp = main.substr(1, main.find(',', +1) - 2);
					main = main.substr(main.find(',', +1), main.length());

					LIST->add(temp);
					// std::cout << "\nTEMP:" << temp << "\n";
					// LIST->add(temp);
					/*CSV col;
					col.setCategory(temp);
					newCSV.push_back(col);*/
				}
				// Second column
				if (main.find(',') != std::string::npos)
				{

					temp = main.substr(2, main.find(',', +1) - 3);
					main = main.substr(main.find(',', +1), main.length());

					LIST->add(temp);
					// std::cout << "\nTEMP:" << temp << "\n";
					/*CSV col;
					col.setCategory(temp);
					newCSV.push_back(col);*/
				}
			}
		}

		void parseElements(const std::string &line, CSVLL *LIST)
		{
			std::string main = line;
			std::string temp;
			int colcount = 0;
			bool firstColumnChecked = false;
			// std::cout << main << "\n";
			bool mode = false;

			while (!main.empty())
			{
				if (main.length() == 1)
				{
					main = "";
					break;
				}
				if (main.find(',') != std::string::npos)
				{
					temp = main.substr(main.find('"') + 1, main.find('"', +1) - 1);
					main = main.substr(main.find('"', +2) + 2, main.length());

					LIST->addCSVelement(colcount, temp);
					// std::cout << "\nTEMP:" << temp << "\n";
					// newCSV[colcount].setElements(temp);
					colcount++;
					// std::cout << "temp : " << temp << "\n";
					// std::cout << "main : " << main << "\n";
				}
			}
		}
	}
}