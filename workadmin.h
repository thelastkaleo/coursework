#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>   
#include <sstream> 
#include <conio.h>


static std::string loginFile = "userdata.txt";


struct logindata {

	std::string login;
	std::string pwd;
	int role;
	bool block;
};



void initLoginFile(std::vector <logindata>& userdatalist);


void saveloginfile(std::vector <logindata>& userdatalist);
bool readloginfile(std::vector <logindata>& userdatalist);
void printloginfile(std::vector <logindata>& userdatalist);

bool adduser(std::vector <logindata>& userdatalist);
bool deluser(std::vector <logindata>& userdatalist);
int authorization(std::vector <logindata>& userdatalist);
void adminmenu(std::vector <logindata>& userdatalist);



std::string encrypt_decrypt(std::string toEncrypt);
void enterpass(std::string& pass);
void printmenuadmin();
void cinclear();
void printmenuser();
