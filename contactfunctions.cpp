//Necessary header files for different classes
#include "contactfunctions.h"
#include "contact.h"
#include "contactbst.h"
#include "myvector.h"

//function to list the commands for the management system
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"del <key>          :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markfv <key>       :Mark as favourite"<<endl
		<<"umarkfv <key>      :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printfv            :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}

//Vector constructor
template <typename T>
MyVector<T>::MyVector()
{
	v_size = 0;
	v_capacity = 100;
	data = new T[v_capacity];
}

//Vector constructor with argument
template <typename T>
MyVector<T>::MyVector(int cap)
{
	v_size = 0;
	v_capacity = cap;
	data = new T[v_capacity];
}

//Vector destructor
template <typename T>
MyVector<T>::~MyVector()
{
	delete[] data;
}

//Vector insert method
template <typename T>
void MyVector<T>::push_back(T* element)
{
	//Increase the size of the vector if it is about to exceed capacity by copying into a new array
	if (v_size == v_capacity)
	{
		v_capacity++;
		T *old = data;
		data = *new T*[v_capacity];
		for (int i = 0; i < v_size + 1; i++)
		{
			data[i] = old[i];
		}
		delete[] old;
	} 
	data[v_size++] = *element;
	return;
}

//Delete method for the vector at a certain index
template <typename T>
void MyVector<T>::erase(int index)
{
	for (int i = index +1; i < v_size; i++)
	{
		data[i-1] = data[i];
	}
	v_size--;
}

//Return element at a specific index in array of vector
template <typename T>
T& MyVector<T>::at(int index) throw(out_of_range)
{
	if (index >= v_size)
	{
		throw out_of_range("Out of range.");
	}
	else
	{
		return data[index];
	}
}

//Return front element of vector
template <typename T>
const T& MyVector<T>::front()
{
	return data[0];
}

//Return back element of vector
template <typename T>
const T& MyVector<T>::back()
{
	return data[v_size-1];
}

//Return size of vector
template <typename T>
int MyVector<T>::size() const
{
	return v_size;
}

//Return capacity of vector
template <typename T>
int MyVector<T>::capacity() const
{
	return v_capacity;
}

//Return if empty or not
template <typename T>
bool MyVector<T>::empty() const
{
	return v_size == 0;
}

//Constructor for contact class
Contact::Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav)
{
	this->fname = fname;
	this->lname = lname;
	this->email = email;
	this->primaryPhone = primaryPhone;
	this->city = city;
	this->country = country;
	this->isFav = isFav;
}

//Constructor for BST Node
Node::Node(string key, MyVector<Contact>* contactVector)
{
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->contactVector = contactVector;
}

//Destructor for BST Node
Node::~Node()
{
	cout<<"Deleted: "<<this->key<<endl;
}

//Constructor for BST 
ContactBST::ContactBST()
{
	this->root=nullptr;
}

//Destructor for BST
ContactBST::~ContactBST()
{
	while(root)
		root = del(root,root->key);
}

//Helper method for add
void ContactBST::insert_helper(string key, Contact* data)
{	
	root = add(root, key, data);
} 

//Helper method for remove
void ContactBST::remove_helper(string key)
{
	root = del(root, key);
} 

//Return root of BST
Node* ContactBST::getRoot()
{
	return root;
}

//Find node with minimum value in BST by recursively going towards the left side
Node* ContactBST::findMin(Node *ptr)
{
	Node* min = ptr;
	if (min->left != nullptr)
	{
		min = findMin(min->left);
	}
	return min;
}

//Find node with maximum value in BST by recursively going towards the right side
Node* ContactBST::findMax(Node *ptr)
{
	Node* max = ptr;
	if (max->right != nullptr)
	{
		max = findMin(max->right);
	}
	return max;
}

//Import the contents of a CSV file into the BST
int ContactBST::importCSV(Node* ptr, string path)
{
	int imported = 0;
    string CFN, CLN, CEM, CPP, CCT, CCO, Cline;
	string CFV, key;
    ifstream Cfile(path);
    while(Cfile >> Cline)
    {
		cout<<"once"<<endl;
		stringstream ss(Cline);
        getline(ss, CFN, ',');
        getline(ss, CLN, ',');
        getline(ss, CEM, ',');
        getline(ss, CPP, ',');
        getline(ss, CCT, ',');
		getline(ss, CCO, ',');
		getline(ss, CFV,'\n');
		bool fv;
		if (CFV == "1")
		{
			fv = true;
		}
		else
		{
			fv = false;
		}
		Contact* newcontact = new Contact(CFN, CLN, CEM, CPP, CCT, CCO, fv);
		imported++;
		key = CFN + ' ' + CLN;
		root = add(root, key, newcontact);
    }
	return imported;
}

//Export the contents of a BST into a CSV file by recursively writing data into file
int ContactBST::exportCSV(Node* ptr, string path)
{
	if (ptr == nullptr)
	{
		return -1;
	}
	exportCSV(ptr->left, path);
	int exported = 0;
	ofstream outcontactdata;
    outcontactdata.open(path, ofstream::out | ofstream::app);
	for (int i = 0; i < ptr->contactVector->size(); i++)
	{
		exported++;
		outcontactdata << ptr->getData()->at(i).fname <<", "<< ptr->getData()->at(i).lname <<", "<< ptr->getData()->at(i).email <<", "<< ptr->getData()->at(i).primaryPhone <<", "<< ptr->getData()->at(i).city <<", "<< ptr->getData()->at(i).country <<", "<< ptr->getData()->at(i).isFav<<endl;
	}
    outcontactdata.close();
	exportCSV(ptr->right, path);
	return exported;
}

//Helper function for add 
void ContactBST::add_helper()
{		
		//Collect information from user
		string first, last, email, number, city, country, key;
		string favechoice;
		bool fave;
		cout<<"Please enter the details of the contact: "<<endl;
		cout<<"First Name: "<<endl;
		cin >> first;
		cout<<"Last Name: "<<endl;
		cin >> last;
		cout<<"Email: "<<endl;
		cin >> email;
		cout<<"Phone#: "<<endl;
		cin >> number;
		cout<<"City: "<<endl;
		cin >> city;
		cout<<"Country: "<<endl;
		cin >> country;
		cout<<"Do you want to add the contact in you favourites (y/n) : "<<endl;
		cin >> favechoice;
		if (favechoice == "y")
		{
			fave = true;
		}
		else if (favechoice == "n")
		{
			fave = false;
		}
		Contact* newcontact = new Contact(first, last, email, number, city, country, fave); //Create a new contact object
		key = first + ' ' + last;
		root = add(root, key, newcontact); //Add the contact object into BST
}

Node* ContactBST::add(Node* ptr,string key, Contact* data)
{
	if (ptr == nullptr)
	{
		MyVector<Contact>* newcontact = new MyVector<Contact> ();
		newcontact->push_back(data);
		ptr = new Node(key, newcontact); //Set the ptr to the new node created for the inputted data
	}
	else if (key.compare(ptr->key) > 0) //Compare used to alphabetically input the Node into the BST
	{
		ptr->right = add(ptr->right, key, data);
	}
	else if (key.compare(ptr->key) < 0)
	{
		ptr->left = add(ptr->left, key, data);
	}
    else if (key.compare(ptr->key) == 0)
    {
		ptr->contactVector->push_back(data); //If two keys are identical, put them in same vector
    }
	/*else if (ptr == getRoot())
	{
		insert_helper(key, data);
	}*/
	return ptr;
}

//Update details of a contact
Node* ContactBST::update(Node* ptr, string key)
{
	if (ptr == nullptr)
	{
		cout<<"Contact does not exist."<<endl;
		return ptr;
	}
	else if (key.compare(ptr->key) > 0)
	{
		ptr->right = update(ptr->right, key);
	}
	else if (key.compare(ptr->key) < 0)
	{
		ptr->left = update(ptr->left, key);
	}
    else if (key.compare(ptr->key) == 0)
    {
		cout << ptr->getData()->size() <<" records found: "<<endl;
		for (int i = 0; i < ptr->contactVector->size(); i++) //List contacts with same key found
		{
			cout<<i+1<<". ";
			ptr->getData()->at(i).printcontact();
		}
		cout<<"Please select the record you want to edit: ";
		int recordchoice;
		cin >> recordchoice;
		for (int i = 0; i < ptr->contactVector->size(); i++)
		{
			if (i == recordchoice-1)
			{
				while(true)
				{
					cout<<"Which field do you want to edit? 1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) City, or 6) Country: ";
					int editchoice;
					cin >>editchoice;
					if (editchoice == 1)
					{
						cout<<"Please enter the new first name: ";
						string newfname;
						cin >> newfname;
						Contact* newcontact = new Contact(newfname, ptr->getData()->at(i).lname, ptr->getData()->at(i).email, ptr->getData()->at(i).primaryPhone, ptr->getData()->at(i).city, ptr->getData()->at(i).country, ptr->getData()->at(i).isFav);
						string newkey = newfname + ' ' + ptr->getData()->at(i).lname;
						add(root, newkey, newcontact);
						del(root, key); //Insert a new contact with the old credentials but new name then delete old contact
					}
					if (editchoice == 2)
					{
						cout<<"Please enter the new last name: ";
						string newlname;
						cin >> newlname;
						Contact* newcontact = new Contact(ptr->getData()->at(i).fname, newlname , ptr->getData()->at(i).email, ptr->getData()->at(i).primaryPhone, ptr->getData()->at(i).city, ptr->getData()->at(i).country, ptr->getData()->at(i).isFav);
						string newkey = ptr->getData()->at(i).fname + ' ' + newlname;
						add(root, newkey, newcontact);
						del(root, key); //Insert a new contact with the old credentials but new name then delete old contact
					}
					else if (editchoice == 3)
					{
						cout<<"Please enter the new email: ";
						string newemail;
						cin >> newemail;
						ptr->getData()->at(i).email = newemail;
					}
					else if (editchoice == 4)
					{
						cout<<"Please enter the new phone numner: ";
						string newnumber;
						cin >> newnumber;
						ptr->getData()->at(i).primaryPhone = newnumber;
					}
					else if (editchoice == 5)
					{
						cout<<"Please enter the new city: ";
						string newcity;
						cin >> newcity;
						ptr->getData()->at(i).city = newcity;
					}
					else if (editchoice == 6)
					{
						cout<<"Please enter the new country: ";
						string newcountry;
						cin >> newcountry;
						ptr->getData()->at(i).country = newcountry;
					}
					else
					{
						cout<<"Invalid choice."<<endl;
						return ptr;
					}
					cout<<"Do you want to edit another field (y/n)? ";
					string exitchoice;
					cin >> exitchoice;
					if (exitchoice == "y")
					{
						continue;
					}
					else if (exitchoice == "n")
					{
						break;
					}
				}
				return ptr;
			}
		}
    }
}

Node* ContactBST::del(Node* ptr,string key)
{
	if (ptr == nullptr)
	{
		cout<<"Contact does not exist."<<endl;
		return ptr;
	}
	else if (key.compare(ptr->key) > 0)
	{
		ptr->right = del(ptr->right, key);
	}
	else if (key.compare(ptr->key) < 0)
	{
		ptr->left = del(ptr->left, key);
	}
    else if (key.compare(ptr->key) == 0)
    {
		cout << ptr->getData()->size() <<" records found: "<<endl;
		for (int i = 0; i < ptr->contactVector->size(); i++)
		{
			cout<<i+1<<". ";
			ptr->getData()->at(i).printcontact();
		}
		cout << "Please select the record you would like to delete: ";
		int recordchoice;
		cin >> recordchoice;
		for (int i = 0; i < ptr->contactVector->size(); i++)
		{
			if (i == recordchoice-1)
			{
				if (ptr->left == nullptr && ptr->right == nullptr)
				{
					ptr->contactVector->erase(i); //Erase the element at position i of vector but keep vector
					if (ptr->contactVector->size() == 0) //If the vector only has 1 element before deletion, then delete the node too
					{
						delete ptr;
						ptr = nullptr;
						return ptr;
					}
					return ptr;
				}
				else if (ptr->left == NULL)
				{
					ptr->contactVector->erase(i);
					if (ptr->contactVector->size() == 0)
					{
						Node* temp = ptr;
						ptr = ptr->right;
						delete temp;
						return ptr;
					}
					return ptr;
				}
				else if (ptr->right == NULL)
				{
					ptr->contactVector->erase(i);
					if (ptr->contactVector->size() == 0)
					{
						Node* temp = ptr;
						ptr = ptr->left;
						delete temp;
						return ptr;
					}
					return ptr;
				}
				else
				{
					ptr->contactVector->erase(i);
					//if node has two children, find min of right subtree then recursively delete
					if (ptr->contactVector->size() == 0)
					{
						Node* temp = findMin(ptr->right);
						ptr->key = temp->key;
						MyVector<Contact>* tempvec = new MyVector<Contact> ();
						tempvec = ptr->contactVector;
						ptr->contactVector = temp->contactVector;
						temp->contactVector = tempvec;
						ptr->right = del(ptr->right, temp->key);
						return ptr;
					}
					return ptr;
				}
			}
		}
	}
}
//Search the BST using the key
Node* ContactBST::search(Node* ptr,string key)
{
	if (ptr == nullptr)
	{
		cout<<"Contact does not exist."<<endl;
		return ptr;
	}
	else if (key.compare(ptr->key) > 0)
	{
		ptr->right = search(ptr->right, key);
	}
	else if (key.compare(ptr->key) < 0)
	{
		ptr->left = search(ptr->left, key);
	}
	else
	{
		cout<<ptr->contactVector->size()<< " records found: "<<endl;
		for (int i = 0; i < ptr->contactVector->size(); i++)
		{
			cout<<i+1<<". ";
			ptr->getData()->at(i).printcontact();
		}
	}
	return ptr;
}

//Mark a contact as a favorite
bool ContactBST::markFav(Node* ptr, string key)
{
	if (ptr == nullptr)
	{
		cout<<"Contact does not exist."<<endl;
		return 0;
	}
	else if (key.compare(ptr->key) > 0)
	{
		ptr->right = search(ptr->right, key);
	}
	else if (key.compare(ptr->key) < 0)
	{
		ptr->left = search(ptr->left, key);
	}
	else
	{
		cout<<ptr->contactVector->size()<<" records found: "<<endl;
		for (int i = 0; i < ptr->contactVector->size(); i++)
		{
			cout<<i+1<<". ";
			ptr->getData()->at(i).printcontact();
		}
		cout<<"Please select the record you want to mark as favorite : ";
		int recordchoice;
		cin >> recordchoice;
		for (int i = 0; i < ptr->contactVector->size(); i++)
		{
			if (i == recordchoice - 1)
			{
				ptr->getData()->at(i).isFav = true;
			}
		}
	}
	return 1;
}
//Unmark a contact as a favorite

bool ContactBST::unmarkFav(Node* ptr, string key)
{
	if (ptr == nullptr)
	{
		cout<<"Contact does not exist."<<endl;
		return 0;
	}
	else if (key.compare(ptr->key) > 0)
	{
		ptr->right = search(ptr->right, key);
	}
	else if (key.compare(ptr->key) < 0)
	{
		ptr->left = search(ptr->left, key);
	}
	else
	{
		cout<<ptr->contactVector->size()<<" records found: "<<endl;
		for (int i = 0; i < ptr->contactVector->size(); i++)
		{
			cout<<i+1<<". ";
			ptr->getData()->at(i).printcontact();
		}
		cout<<"Please select the record you want to unmark as favorite : ";
		int recordchoice;
		cin >> recordchoice;
		for (int i = 0; i < ptr->contactVector->size(); i++)
		{
			if (i == recordchoice - 1)
			{
				ptr->getData()->at(i).isFav = false;
			}
		}
	}
	return 1;
}
//Print the tree in ascending order by recursively printing from the left most side
void ContactBST::printASC(Node* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	printASC(ptr->left);
	for (int i = 0; i < ptr->contactVector->size(); i++)
	{
		ptr->getData()->at(i).printcontact();
	}
	printASC(ptr->right);
}

//Print the tree in descending order by recursively printing from the right most side
void ContactBST::printDES(Node* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	printDES(ptr->right);
	for (int i = 0; i < ptr->contactVector->size(); i++)
	{
		ptr->getData()->at(i).printcontact();
	}
	printDES(ptr->left);
}
//Print the favorites recursively and in ascending order
void ContactBST::printFav(Node* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	printFav(ptr->left);
	for (int i = 0; i < ptr->contactVector->size(); i++)
	{
		if (ptr->getData()->at(i).isFav == 1)
		{
			ptr->getData()->at(i).printcontact();
		}
	}
	printFav(ptr->right);
}