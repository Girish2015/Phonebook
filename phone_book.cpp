// READ readme.txt 

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<chrono>
#include <ctime>
#include<stdio.h>
#include<cstring>

using namespace std;

void create();
void view();
void search();
void delete_contact();
void initialize_time();
void insert_into_file();

struct
{
  char phone_no[10];
  char name[30];
  char email[30];
  char *create_time;
  char create_time1[20];
}contact;

fstream phonebook;

int main()
{
  phonebook.open("phonebook.txt",ios::app);
  phonebook.close();
  int ch;
  while(1)
  {
    system("clear");
    cout<<"\n\tPHONE BOOK APP";
    cout<<"\n\n\t1.CREATE NEW CONTACT";
    cout<<"\n\t2.VIEW CONTACT";
    cout<<"\n\t3.SEARCH CONTACT";
    cout<<"\n\t4.DELETE CONTACT";
    cout<<"\n\n\tEnter your choice: ";
    cin>>ch;

    switch(ch)
    {
      case 1:create();
      break;
      case 2:view();
      break;
      case 3:search();
      break;
      case 4:delete_contact();
      break;
      default:return 0;
    }
  }
}

void initialize_time()
{
  std::chrono::time_point<std::chrono::system_clock> t;
  t=std::chrono::system_clock::now();
  std::time_t current_time = std::chrono::system_clock::to_time_t(t);
  contact.create_time=std::ctime(&current_time);
  contact.create_time[strlen(contact.create_time)-1]='\0';
}

void insert_into_file()
{
  phonebook.open("phonebook.txt",ios::app);
  if(phonebook.fail())
    cout<<"File open FAIL!";
  char buf[500];
  sprintf(buf,"%s|%s|%s|%s|",contact.phone_no,contact.name,contact.email,contact.create_time);
  strcat(buf,"\n");
  phonebook.write(buf,strlen(buf));
  phonebook.close();
}

void create()
{
  system("clear");
  cout<<"\n\tEnter the contact name: ";
  cin>>contact.name;
  cout<<"\n\tEnter the contact number: ";
  cin>>contact.phone_no;
  cout<<"\n\tEnter the email ID of contact: ";
  cin>>contact.email;
  initialize_time();
  insert_into_file();
}

void view()
{
  system("clear");
  phonebook.open("phonebook.txt",ios::in);
  if(phonebook.fail())
    cout<<"File open FAIL!";
  cout<<"\n\tALL CONTACTS\n\n";
  char buf[500];
  int i=0;
  while(phonebook.getline(buf,500,'\n'))
  {
    ++i;
    sscanf(buf,"%[^|]|%[^|]|%[^|]|%[^|]",contact.phone_no,contact.name,contact.email,contact.create_time1);
    cout<<"\n"<<i<<".";
    cout<<"\tNAME : "<<contact.name;
    cout<<"\n\tPHONE NUMBER : "<<contact.phone_no;
    cout<<"\n\tE-MAIL : "<<contact.email;
    cout<<"\n\tDATE/TIME ADDED : "<<contact.create_time1;
    cout<<"\n";
  }
  cout<<"\nPress any key for Main Menu";
  char ch;
  cin>>ch;
  phonebook.close();
}

void search()
{
  system("clear");
  phonebook.open("phonebook.txt",ios::in);
  if(phonebook.fail())
    cout<<"File open FAIL!";
  char key[20],buf[500],ch;
  int flag;
  cout<<"\n\tPHONEBOOK SEARCH";
  cout<<"\n\n\tEnter the Name or Phone Number: ";
  cin>>key;
  while(phonebook.getline(buf,500,'\n'))
  {
    sscanf(buf,"%[^|]|%[^|]|%[^|]|%[^|]",contact.phone_no,contact.name,contact.email,contact.create_time1);
    if(strcmp(contact.phone_no,key)==0||strcmp(contact.name,key)==0)
    {
      cout<<"\n\tNAME : "<<contact.name;
      cout<<"\n\tPHONE NUMBER : "<<contact.phone_no;
      cout<<"\n\tE-MAIL : "<<contact.email;
      cout<<"\n\tDATE/TIME ADDED : "<<contact.create_time1;
      flag=1;
      cout<<"\n\n\tEnter any key for Main Menu ";
      cin>>ch;
      break;
    }
  }
    if(flag==0)
    {
      cout<<"\n\tContact not FOUND!";
      cout<<"\n\n\tEnter any key for Main Menu ";
      cin>>ch;
    }
    phonebook.close();
}

void delete_contact()
{
  system("clear");
  phonebook.open("phonebook.txt",ios::in|ios::out);
  if(phonebook.fail())
    cout<<"File open FAIL!";
  char key[20],buf[500],ch;
  int flag;
  cout<<"\n\tDELETE CONTACT";
  cout<<"\n\n\tEnter the Name or Phone Number: ";
  cin>>key;
  while(phonebook.getline(buf,500,'\n'))
  {
    sscanf(buf,"%[^|]|%[^|]|%[^|]|%[^|]",contact.phone_no,contact.name,contact.email,contact.create_time1);
    if(strcmp(contact.phone_no,key)==0||strcmp(contact.name,key)==0)
    {
      cout<<"\n\tNAME : "<<contact.name;
      cout<<"\n\tPHONE NUMBER : "<<contact.phone_no;
      cout<<"\n\tE-MAIL : "<<contact.email;
      cout<<"\n\tDATE/TIME ADDED : "<<contact.create_time1;
      flag=1;
      break;
    }
  }
  phonebook.close();
  if(flag==0)
  {
    cout<<"\n\tContact not FOUND!";
    cout<<"\n\n\tEnter any key for Main Menu ";
    cin>>ch;
  }
  else
  {
    cout<<"\n\tDo you want this CONTACT to be DELETED ?";
    cin>>ch;
    if(ch=='y'||ch=='Y')
    {
      char cmd[100];
      /*char cmd[50]="awk -F "|" '!($1 == ";
      strcat(cmd,key);
      strcat(cmd,""||$2=="");
      strcat(cmd,key);
      strcat(cmd,"\")' phonebook.txt");
      cout<<cmd;
      awk -F "|" '!($1 == "key"||$2=="key")' phonebook.txt
      system(cmd);
      cout<<"\n"
      */
      sprintf(cmd,"awk -F \"|\" '!($1 == \"%s\"||$2==\"%s\")' phonebook.txt>phonebook1.txt",key,key);
      system(cmd);
      system("mv phonebook1.txt phonebook.txt");
      cout<<"\n\tDELETED!";
    }
  }
}
