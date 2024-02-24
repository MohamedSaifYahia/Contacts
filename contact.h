#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
using namespace std;

//Class for contact object for the values and a function to print
class Contact
{
	private:
		string fname;
		string lname;
		string email;
		string primaryPhone;
		string city;
		string country;
		bool isFav;
	public:
		friend class ContactBST;
		Contact() {}; //No argument constructor
		Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav); //7 argument constructor that initalizes the object
		void printcontact()
		{
			cout<<fname + ' ' + lname<<", "<<email<<", "<<primaryPhone<<", "<<city<<", "<<country<<endl;
		}
		
};

#endif