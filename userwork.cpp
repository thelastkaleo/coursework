
#include "userwork.h"
#include "workadmin.h"



bool readticketfile(std::vector <ticket>& ticketlist)
{
	ticketlist.clear();

	std::fstream fin(ticketfile, std::fstream::in);
	if (fin.is_open())
	{
		ticket temp;
		std::string line;


		while (std::getline(fin, line))
		{
			std::istringstream iss(line);
			iss >> temp.transport >> temp.cost;
			ticketlist.push_back(temp);
		}
		fin.close();
		return true;
	}
	else
		return false;
}

bool readsalesfile(std::vector <sales>& saleslist)
{
	saleslist.clear();

	std::fstream fin(salesfile, std::fstream::in);
	if (fin.is_open())
	{
		sales temp;
		std::string line;


		while (std::getline(fin, line))
		{
			std::istringstream iss(line);
			iss >> temp.year >> temp.month >> temp.transport >> temp.quantity;
			saleslist.push_back(temp);
		}
		fin.close();
		return true;
	}
	else
		return false;
}

double monthcost(unsigned int year, std::string month, std::string transport)
{
	
	
	std::vector <ticket> costticket;
	readticketfile(costticket);

	std::vector <sales> datasales;
	readsalesfile(datasales);

	double result = 0;

	for (const auto& val : datasales)
		if (val.year == year && val.month == month && val.transport == transport)
			for (const auto& val1 : costticket)
				if (val1.transport == val.transport)
					result += val.quantity * val1.cost;

	return result;
}

double result(unsigned int year, std::string month)
{
	double resultmonth = 0;

	std::vector <ticket> transportlist;
	readticketfile(transportlist);

	for (const auto& val : transportlist)
		resultmonth += monthcost(year, month, val.transport);

	return resultmonth;
}

void populartransport(unsigned int year, std::string month)
{
	std::vector <sales> poptranslist;
	readsalesfile(poptranslist);


	sales temp;
	for (int i = 0; i< poptranslist.size(); i++)
	{
		
		for (int j = 0; j < poptranslist.size() - 1; j++)
			if (poptranslist.at(j).quantity < poptranslist.at(j + 1).quantity)
			{
				temp = poptranslist.at(j);
				poptranslist.at(j) = poptranslist.at(j + 1);
				poptranslist.at(j + 1) = temp;
			}

	}

	printsaleslist(poptranslist,year,month);

}

void printsaleslist(std::vector <sales>& list, unsigned int year, std::string month)
{
	for (const auto& val : list)
		if(val.year == year && val.month == month)
		std::cout << val.transport << '\t'<< val.quantity << std::endl;


}

void printtransport()
{
	std::vector <ticket> translist;
	readticketfile(translist);

	for (const auto& val : translist)
		std::cout << val.transport << std::endl;


}

void printmenuser()
{

	std::cout << "User menu ----------------------------------" << std::endl;
	std::cout << "1 to view month costs for chosen transport" << std::endl;
	std::cout << "2 to view sum of all month costs" << std::endl;
	std::cout << "3 to view popular transport" << std::endl;
	std::cout << "4 to print list of transport" << std::endl;
	std::cout << "5 to view sales for each transport" << std::endl;
	std::cout << "6 to print menu" << std::endl;
	std::cout << "0 main menu" << std::endl;

}

void userenu()
{

	unsigned int year;
	std::string month;
	std::string transport;
	printmenuser();

	unsigned choice = 0;
	do
	{
		std::cout << "make a choice:";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			std::cout << "Choose a year: ";
			std::cin >> year;
			std::cout << "Choose a month: ";
			std::cin >> month;
			std::cout << "Choose a transport: ";
			std::cin >> transport;
			std::cout << "Month costs: " << monthcost(year, month, transport) << std::endl;
			break;
		}
		case 2:
		{
			std::cout << "Choose a year: ";
			std::cin >> year;
			std::cout << "Choose a month: ";
			std::cin >> month;
			std::cout << "All month costs: " << result(year, month) << std::endl;
			break;
		}
		case 3:
		{	
			std::cout << "Choose a year: ";
			std::cin >> year;
			std::cout << "Choose a month: ";
			std::cin >> month;
			populartransport(year, month);
			break;
		}
		case 4:
			printtransport();
			break;
		case 5:
		{
			std::vector <sales> list;
			readsalesfile(list);
			std::cout << "Choose a year: ";
			std::cin >> year;
			std::cout << "Choose a month: ";
			std::cin >> month;
			printsaleslist(list, year, month);
			break;
		}
		case 6:
			printmenuser();
			break;
		case 0:
			cinclear();
			break;

		default:
			std::cout << "Unknown operation!\n";
		}

	} while (choice != 0);


}