#pragma once
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <iostream>

static std::string ticketfile = "ticket.txt";
static std::string salesfile = "sales.txt";
static std::string costsfile = "costs.txt";


struct ticket
{
	std::string transport;
    double cost;
};

struct sales
{
	unsigned int year;
	std::string month;
	std::string transport;
	unsigned int quantity;
};

struct costs
{
	unsigned int year;
	std::string month;
	std::string transport;
	unsigned int cost;

};



bool readticketfile(std::vector <ticket>& ticketlist);
bool readsalesfile(std::vector <sales>& saleslist);
double monthcost(unsigned int year, std::string month, std::string transport);
double result(unsigned int year, std::string month);
void populartransport(unsigned int year, std::string month);
void printsaleslist(std::vector <sales>& list, unsigned int year, std::string month);
void printtransport();
void userenu();