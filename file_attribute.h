#include <stdio.h>
#include <iostream>
#define _POSIX_SOURCE
#include <fstream>
#include <sys/types.h>
#include <time.h>
#include <sys/stat.h>
#include <windows.h>
using namespace std;
string GetMimeType(const string &szExtension);
struct Node
{
	string name;
	string date;
	int size;
	Node *next;
};

Node* print_list(Node* head)
{
	Node *temp = head;

	while(temp != NULL)
	{
		cout << "Name     " << temp -> name <<endl;
		cout << "Size     " << temp -> size << endl ;
		cout << "Last access     " << temp -> date << endl;
		temp = temp->next;
	}

	return head;
}
Node* insertAfter(Node* head, string name, string date, int size)
{
	Node* new_node = new Node;
	new_node -> name = name;
	new_node -> date = date;
	new_node -> size = size;
	new_node -> next == NULL;



	if(head == NULL)
	{
		head = new_node;
		return head;
	}

	Node* temp = head;

while(temp -> next != NULL)
	{
		temp = temp -> next;
	}
	temp -> next = new_node;
	new_node -> next = NULL;
	return head;
}

string get_mime(string s)
{
	int i;
	string ext;
	for(i=s.length()-1;i>=0;i--)	
	{
    	if(s[i]=='.')
    	{
        	break;
    	}
	}	
	for(i=i;i<s.length();i++)
	{
    	ext = ext + s[i];
	}
	
	return (GetMimeType(ext));
		
}

string GetMimeType(const string &szExtension)
{



    // return mime type for extension
    HKEY hKey = NULL;
    string szResult = "application/unknown";

    // open registry key
    if (RegOpenKeyEx(HKEY_CLASSES_ROOT, szExtension.c_str(),
                       0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        // define buffer
        char szBuffer[256] = {0};
        DWORD dwBuffSize = sizeof(szBuffer);

        // get content type
        if (RegQueryValueEx(hKey, "Content Type", NULL, NULL,
                       (LPBYTE)szBuffer, &dwBuffSize) == ERROR_SUCCESS)
        {
            // success
            szResult = szBuffer;
        }

        // close key
        RegCloseKey(hKey);
    }

    // return result
    return szResult;
}


/*int main_code(string s)
{
	string name,date,k;
	int size,i,t;
	struct stat info;
	Node* head = NULL;

	{
    k = s;
	for(i=0;i<=s.length()-1;i++)
	{
		if(s[i]>=65 && s[i]<=90)
		{
			s[i] = s[i]+32;
		}
		if(s[i]=='\\')
        {
            s[i] = '//';
        }
	}
	const char *c = &k[0];
	if(stat(c, &info) !=0)
	{
		cout << "Error" << endl;
		return 0;
	}
	
	name = "";

	for(i=s.length()-1;i>=0;i--)
	{
		if(s[i]=='/')
		{
			break;
		}
	}

	for(i=i+1;i<=s.length()-1 && s[i]!='.';i++)
	{
		name = name + s[i];
	}

		size = int(info.st_size);
		date = string(ctime(&info.st_atime));
		head =	insertAfter(head, name, date, size);

	}

	cout << "Insertion done" << endl;
	print_list(head);
} */


Node* main_code(Node* head1,string s)
{
	
	string name,date,k;
	int size,i,t;
	struct stat info;
	Node* head = head1;
    k = s;
	for(i=0;i<=s.length()-1;i++)
	{
		if(s[i]>=65 && s[i]<=90)
		{
			s[i] = s[i]+32;
		}
		if(s[i]=='\\')
        {
            s[i] = '//';
        }
	}
	cout << "String" << s << endl;
	const char *c = &k[0];
	if(stat(c, &info) != 0)
        cout << "File error" << endl;
    else
    {
	
	name = "";

	for(i=s.length()-1;i>=0;i--)
	{

		if(s[i]=='/')
		{
			break;
		}
		
	}

	for(i=i+1;i<s.length()-1 && s[i] !='.';i++)
	{
		name = name + s[i];
	}
		size = int(info.st_size);
		date = string(ctime(&info.st_atime));
		
		head =	insertAfter(head, name, date, size);
		cout << "Back to API" << endl;
       }
       print_list(head);
		return head;
}

