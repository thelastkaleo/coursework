
#include "workadmin.h"


std::string stringencrypt_decrypt(std::string toEncrypt)
{
	char key[10] = { 'K', 'C', 'Q', 'r', '&', '2', 'y', '-' , '#' , '>' };
	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
	{
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
		if (output[i] == ' ' || output[i] == '\0' || output[i] == '\t' || output[i] == L'\r' || output[i] == L'\n' || output[i] == '\x1a')
			output[i] = toEncrypt[i];
	}

	return output;
}

void initLoginFile(std::vector <logindata>& userdatalist)
{
	userdatalist.clear();

	std::ifstream datafile(loginFile);
	datafile.seekg(0, datafile.end);
	int size = datafile.tellg();
	datafile.seekg(0, datafile.beg);

	datafile.close();

	if (size <= 0)
	{
		logindata admin;
		admin.login = "admin";
		admin.pwd = "12345";
		admin.role = 1;
		userdatalist.push_back(admin);

		saveloginfile(userdatalist);
	}

}

void saveloginfile( std::vector <logindata>& userdatalist)
{
	std::fstream fout(loginFile,   std::fstream::out );

	for (const auto& val : userdatalist)
		fout << val.login << " " << stringencrypt_decrypt(val.pwd) << " " << val.role << std::endl;


	fout.close();
}

bool readloginfile(std::vector <logindata>& userdatalist)
{
	userdatalist.clear();

	std::fstream fin(loginFile,  std::fstream::in);
	if (fin.is_open())
	{
		logindata temp;
		std::string line;


		while (std::getline(fin, line))
		{
			std::istringstream iss(line);
			iss >> temp.login >> temp.pwd >> temp.role;
			temp.pwd = stringencrypt_decrypt(temp.pwd);
			userdatalist.push_back(temp);
		}
		fin.close();
		return true;
	}
	else
		return false;
}

void printloginfile(std::vector <logindata>& userdatalist)
{

	userdatalist.clear();
	readloginfile(userdatalist);

	for (const auto& val : userdatalist)
		std::cout << val.login << " " << val.pwd  << ((val.role == 1) ? " adm" : " 9usr") << std::endl;
	
}

bool adduser(std::vector <logindata>& userdatalist)
{
	userdatalist.clear();
	logindata newuser;

	std::cout << "Enter login for add user:";
	std::cin >> newuser.login;

	std::cout << "Enter pass:";
	std::cin >> newuser.pwd;

	std::cout << "Enter role (1-admin, 0-user):";
	std::cin >> newuser.role;

	readloginfile(userdatalist);

	for (const auto& val : userdatalist)
		if (val.login == newuser.login)
		  	 return false;
	
	userdatalist.push_back(newuser);
	saveloginfile(userdatalist);

	return true;
}

bool deluser(std::vector<logindata>& userdatalist)
{
	userdatalist.clear();
	std::string userlogin;

	std::cout << "Enter login for del user:";
	std::cin >> userlogin;

	if (userlogin == "admin")
	{
		std::cout << "Can't del user '" + userlogin + "'" << std::endl;
		return false;
	}


	readloginfile(userdatalist);

	for (std::vector<logindata>::iterator itr = userdatalist.begin(); itr != userdatalist.end(); itr++)
		if (itr->login == userlogin )
		{
			std::cout << "Del user '" + userlogin + "'? (Y/N)";
			std::string answer;

			std::cin >> answer;

			if (answer == "Y" or answer == "y" )
			{
				userdatalist.erase(itr);
				userdatalist.shrink_to_fit();
				saveloginfile(userdatalist);
				return true;
			}
		}
	
	return false;
}

int authorization(std::vector<logindata>& userdatalist)
{
	logindata user;

	std::cout << "Enter login:";
	std::cin >> user.login;

	std::cout << "Enter pass:";
	enterpass(user.pwd);

	userdatalist.clear();
	readloginfile(userdatalist);

	for (const auto& val : userdatalist)
		if (val.login == user.login  && val.pwd == user.pwd)
			return val.role;

	return 3;
}

void enterpass(std::string& pass)
{
	char p =0;

	while (p != 13)
	{
		p = _getch();
		
		if (p != '\b' && isalnum(p))
		{
			std::cout << '*';
			pass.push_back(p);
		}

	} ;

}

void printmenuadmin()
{

	std::cout << "Admin menu ----------------------------------" << std::endl;
	std::cout << "1 to add user" << std::endl;
	std::cout << "2 to del user" << std::endl;
	std::cout << "3 to get list of users" << std::endl;
	std::cout << "4 to print menu" << std::endl;
	std::cout << "0 main menu" << std::endl;

}


void cinclear()
{
	std::cin.clear();
	std::cin.ignore(1024, '\n');
}

void adminmenu(std::vector <logindata>& userdatalist)
{

	printmenuadmin();

	unsigned choice = 0;
	do
	{
		std::cout << "make a choice:";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		
			if (!adduser(userdatalist))
				std::cout << "bad user name:" << std::endl;
			else
				std::cout << "user ok" << std::endl;

		
		break;

		case 2:
		
			if (deluser(userdatalist))
				 std::cout << "User deleted" << std::endl;
		
			break;

		case 3:
			printloginfile(userdatalist);
			break;

		case 4:
            printmenuadmin();
			break;
		case 0:
			cinclear();
			break;

		default:
			std::cout << "Unknown operation!\n";
		}

	} while (choice != 0);


}
