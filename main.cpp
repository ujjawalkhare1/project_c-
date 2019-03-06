#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#define _POSIX_SOURCE
#include <fstream>
#include <sys/types.h>
#include <time.h>
#include <sys/stat.h>
#include <string>
#include <cstring>
using namespace std;


#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4
#define NAME_SORT 5
#define DATE_SORT 6
#define SIZE_SORT 7
#define FILE_NUMBER 8
/* This is where all the input to the window goes to */

struct Node
{
	string name;
	string date;
	int size;
	Node *next;
};

Node* main_code(Node* head, string s);
string print_list(Node* head, string s);
Node* sort_size(Node* head);
Node* insertAfter(Node* head, string name, string date, int size);
Node* sort_name(Node* head);
Node* sort_date(Node* head);

int file_count = 0;
void AddControl(HWND hwnd);
void AddMenus(HWND hwnd);

HWND handler1, handler_name,handler_date, handler_size,handler_enter, output_handler, handler_file_number, input_file_numbers;


Node* head1 = NULL;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

		/* Upon destruction, tell the main thread to stop */
		case WM_COMMAND:

			switch(wParam)
			{
				case FILE_MENU_EXIT:
					DestroyWindow(hwnd);
					break;
				case FILE_MENU_NEW:
					MessageBeep(MB_ICONINFORMATION);
					break;
				case GENERATE_BUTTON:
					char s[10000];
					GetWindowText(handler1,s,10000);
					head1 = main_code(head1,s);
				//	handler1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 270,182,250,30,hwnd, NULL, NULL, NULL);
					cout << "List after insertion \n";
					//print_list(head1);
					break;
				case NAME_SORT:
					if(head1 != NULL)
					{

					head1 = sort_name(head1);
					}
					cout << "Back to API from name sorting" << endl;
					print_list(head1, "Sorted files according to name:  ");

                    break;
				case DATE_SORT:
					if(head1!= NULL)
					head1 = sort_date(head1);
					cout << "Back to API from date sorting" << endl;
					print_list(head1,"Sorted files according to date:  ");
					break;
				case SIZE_SORT:

					if(head1!= NULL)
					head1 = sort_size(head1);
					print_list(head1,"Sorted files according to size:  ");
					break;
			}
			break;
		case WM_CREATE:
			AddMenus(hwnd);
			AddControl(hwnd);
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}

		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */




	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Window API",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		840, /* width */
		640, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
HMENU hMenu;
void AddMenus(HWND hwnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();

	AppendMenu(hFileMenu, MF_STRING,FILE_MENU_NEW,"New");
	AppendMenu(hFileMenu, MF_STRING,FILE_MENU_OPEN,"Open");
	AppendMenu(hFileMenu, MF_STRING,FILE_MENU_EXIT,"Exit");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	//AppendMenu(hMenu, MF_STRING, NULL, "Help");
	SetMenu(hwnd, hMenu);

}
// Feb 03 23:06:29 2019
void AddControl(HWND hwnd)
{
	CreateWindow("STATIC","Address of file",  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER ,270,150,250,30,hwnd,NULL,NULL,NULL);
	handler1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 270,182,250,30,hwnd, NULL, NULL, NULL);
	handler_enter = CreateWindow("BUTTON","Enter",  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER ,270,215,250,30,hwnd,(HMENU)GENERATE_BUTTON ,NULL,NULL);
	handler_name = CreateWindow("BUTTON","Sort by Name",  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER ,210,250,105,50,hwnd,(HMENU)NAME_SORT ,NULL,NULL);
	handler_date = CreateWindow("BUTTON","Sort by Last access",  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER ,320,250,150,50,hwnd,(HMENU)DATE_SORT ,NULL,NULL);
	handler_size = CreateWindow("BUTTON","Sort by Size",  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER ,475,250,100,50,hwnd,(HMENU)SIZE_SORT ,NULL,NULL);
	output_handler = CreateWindow("EDIT","",  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | ES_MULTILINE | ES_AUTOVSCROLL ,270,310,250,130,hwnd,NULL,NULL,NULL);
}


string print_list(Node* head, string s)
{
		cout << " print function" << endl;
		s = "     "+s+"    ";
	Node *temp = head;
    char a[100000];
	while(temp != NULL)
	{
		cout << "Name     " << temp -> name <<endl;
		cout << "Size     " << temp -> size << endl ;
		cout << "Last access     " << temp -> date << endl;
		s = s + temp -> name+"\n ";
		temp = temp->next;
	}

        SetWindowText(output_handler,s.c_str());
		return &s[0];
}


Node* main_code(Node* head, string s)
{
	string name,date,k;
	int size,i,t;
	struct stat info;

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
	if(stat(c, &info) != 0)
        SetWindowText(output_handler,"File error");
    else
       {

        file_count++;
        char b[100];
        string b2;
        itoa (file_count,b,10);
        string message = "Number of files uploaded:  ";
        int j=0;
        while(b[j]!= '\0')
        {
            b2 += b[j];
            j++;
        }
        message = message + b2;
        SetWindowText(output_handler,message.c_str());

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
		cout << "Initial date" << date << endl;
		// Feb 03 23:06:29 2019
		string a,m;
		int l;
		a = date.substr(4,3);
		if(a=="Feb")
            m = "02";
        else if(a=="Jan")
            m = "01";
        else if(a=="Mar")
            m = "03";
        else if(a=="Apr")
            m = "04";
        else if(a=="May")
            m = "05";
        else if(a=="Jun")
            m = "06";
        else if(a=="Jul")
            m = "07";
        else if(a=="Aug")
            m = "08";
        else if(a=="Sep")
            m = "09";
        else if(a=="Oct")
            m = "10";
        else if(a=="Nov")
            m = "11";
        else if(a=="Dec")
            m = "12";
        l = date.length();
        a = date.substr(l-5,4);
        a = a+m+date.substr(8,2);
		head =	insertAfter(head, name, a, size);
		cout << "Back to API" << endl;
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

Node* sort_name(Node* head)
{
    cout << "Sort by Name" << endl;
	Node* start = head;
	Node* ptr;
	Node* lptr = NULL;
	string temp;
	int t,swap;
	if(start==NULL)
	{
		cout << "Head NULL";
		return head;
	}

	do
	{
		swap = 0;
		ptr = start;

		while(ptr->next != lptr)
		{
			if(ptr->name > ptr -> next -> name)
			{
					temp = ptr -> name;
					ptr -> name = ptr -> next -> name;
					ptr -> next -> name = temp;


					temp = ptr -> date;
					ptr -> date = ptr -> next -> date;
					ptr -> next -> date = temp;

					t = ptr -> size;
					ptr -> size = ptr -> next -> size;
					ptr -> next -> size = t;
					swap = 1;
			}
			ptr = ptr-> next;
		}
		lptr = ptr;
	}while(swap);

	return head;

}

Node* sort_date(Node* head)
{

	Node* start = head;
	Node* ptr;
	Node* lptr = NULL;
	string temp;
	int t,swap;
	if(start==NULL)
	{
		cout << "Head NULL";
		return head;
	}

	do
	{
		swap = 0;
		ptr = start;

		while(ptr->next != lptr)
		{

			if(ptr-> date > ptr -> next -> date)
			{
					temp = ptr -> name;
					ptr -> name = ptr -> next -> name;
					ptr -> next -> name = temp;


					temp = ptr -> date;
					ptr -> date = ptr -> next -> date;
					ptr -> next -> date = temp;

					t = ptr -> size;
					ptr -> size = ptr -> next -> size;
					ptr -> next -> size = t;
					swap = 1;
			}
			ptr = ptr-> next;
		}
		lptr = ptr;
	}while(swap);

	return head;

}

Node* sort_size(Node* head)
{
	cout << "Sort by size"<< endl;
	Node* start = head;
	Node* ptr;
	Node* lptr = NULL;
	string temp;
	int t,swap;
	if(start==NULL)
	{
		return head;
	}

	do
	{
		swap = 0;
		ptr = start;


		while(ptr->next != lptr)
		{

			if(ptr-> size > ptr -> next -> size)
			{
					temp = ptr -> name;
					ptr -> name = ptr -> next -> name;
					ptr -> next -> name = temp;


					temp = ptr -> date;
					ptr -> date = ptr -> next -> date;
					ptr -> next -> date = temp;

					t = ptr -> size;
					ptr -> size = ptr -> next -> size;
					ptr -> next -> size = t;
					swap = 1;
			}
			ptr = ptr-> next;
		}
		lptr = ptr;
	}while(swap);

	return head;

}

