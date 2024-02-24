
//=================================================================================
// Name         : DS Assignment#3 
// Author       : Mohamed Saifeldin Yahia
// Version      : 1.0
// Date Created : 03-20-2022
// Date Modified: 04-19-2022
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include "contactfunctions.h"
#include "contactbst.h"
#include "contact.h"
#include "myvector.h"

int main(void)
{
	//create an instance of BST
	ContactBST myContactBST;
	while(true)
	{
		listCommands();
		cout << ">";
		string choice;
		getline(cin, choice);
		//each if condition checks for the command entered
		if (choice == "add")
		{
			myContactBST.add_helper();
		}
		else if (choice == "edit")
		{
			cout<<"Please enter the key you would like to edit: "<<endl;
			string key;
			getline(cin, key);
			myContactBST.update(myContactBST.getRoot(), key);
		}
		else if (choice == "del")
		{
			cout << "Please enter the key you would like to delete: "<<endl;
			string key;
			getline(cin, key);
			myContactBST.del(myContactBST.getRoot(), key);
		}
		else if (choice == "searchFor")
		{
			cout<<"Please enter the key you would like to search: "<<endl;
			string key;
			getline(cin, key);
			myContactBST.search(myContactBST.getRoot(), key);
		}
		else if (choice == "markfv")
		{
			cout<<"Please enter the key you would like to mark as favorite: "<<endl;
			string key;
			getline(cin, key);
			myContactBST.markFav(myContactBST.getRoot(), key);
		}
		else if (choice == "unmarkfv")
		{
			cout<<"Please enter the key you would like to unmark as favorite: "<<endl;
			string key;
			getline(cin, key);
			myContactBST.unmarkFav(myContactBST.getRoot(), key);
		}
		else if (choice == "printASC")
		{
			myContactBST.printASC(myContactBST.getRoot());
		}
		else if (choice == "printDES")
		{
			myContactBST.printDES(myContactBST.getRoot());
		}
		else if (choice == "printfv")
		{
			myContactBST.printFav(myContactBST.getRoot());
		}
		else if (choice == "import")
		{
			cout << "Please enter the path of the file you wish to import: "<<endl;
			string path;
			cin >> path;
			myContactBST.importCSV(myContactBST.getRoot(), path);
		}
		else if (choice == "export")
		{
			cout << "Please enter the path where you wish to export: "<<endl;
			string path;
			cin >> path;
			myContactBST.exportCSV(myContactBST.getRoot(), path);
		}
		else if (choice == "help")
		{
			continue;
		}
		else if (choice == "exit")
		{
			exit(1);
		}
	}
}
                       








