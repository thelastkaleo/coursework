// Курсовая.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "workadmin.h"
#include "userwork.h"


int main()
{
   std::vector <logindata> userdatalist; 
   unsigned choice = 0;

   initLoginFile(userdatalist);

    do
    {
        std::cout << "1-in 0-out\n";
        std::cout << "Mode:";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int role = authorization(userdatalist);
            if (role == 3)
                std::cout << "Access denied!" << std::endl;
            else if (role == 1)
            {
                std::cout << "Welcom admin!" << std::endl << std::endl;
                adminmenu(userdatalist);
            }
            else
            {
                std::cout << "Welcom user!" << std::endl;
                userenu();
            }

            break;
        }

        case 0:
            std::cout << "Have a good time! Waiting for you back!\n";
            cinclear();
            break;

        default:
            std::cout << "Unknown operation!\n";
        }

    } while (choice != 0);
    return 0;
}


