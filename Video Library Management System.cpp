/**
 *  Author: Abheet Sethi
 *  Program: Video Library Management System
 */

#include <conio.h>
#include <fstream.h>
#include <stdio.h>
#include<process.h>
#include<string.h>

/**
 *  Declare a global input/output stream for database file.
 */
ifstream fin;
ofstream fout;

/**
 *  Class declaration
 */

class Video
{
 int Barcode;
 int Edition;
 int Cost;
 char Publisher[50];
 char Name[50];

 public:
 void insertData(int Bcode);
 void modifyData();
 void printData();
 int getBarcode();

}video;

/**
 *  Class function definitions
 */

/**
 *  Once a new video record is created, data is inserted here.
 *  Bcode: The barcode of the video whose record is being                                                                                                                                
           inserted 
*/

void Video::insertData(int Bcode)
{
 Barcode=Bcode;
 cout<<"        Enter Name of the Video: ";
 gets(Name);
 cout<<"        Enter the Edition number: ";
 cin>>Edition;
 cout<<"        Enter the Publisher name: ";
 gets(Publisher);
 Cost=-1;
 while(Cost==-1)
 {
  cout<<"        Enter Price: ";
  cin>>Cost;
  if(Cost<0)
   {
    Cost=-1;
    cout<<"         Price can't be negative."<<endl;
   }
 }
}

/**
 *  Used to modify the data of the Video record.
 */

void Video::modifyData()
{
 char ch;
 cout<<"         Name: ";
 puts(Name);
 cout<<"         The current Edition is "<<Edition<<endl;
 cout<<"         Do you wish to change it? (y/n) ";
 cin>>ch;
 if(ch=='y' || ch=='Y')
  {
   cout<<"         Enter the new Edition number: ";
   cin>>Edition;
  }

 cout<<endl<<"         The current Price is "<<Cost<<endl;
 cout<<"         Do you wish to change it? (y/n) ";
 cin>>ch;
 if(ch=='y' || ch=='Y')
  {
   Cost=-1;
   while(Cost==-1)
   {
    cout<<"         Enter the new Price: ";
    cin>>Cost;
    if(Cost<0)
     {
      Cost=-1;
      cout<<"         Price cannot be negative."<<endl;
     }
   }
  }

 cout<<endl<<"         The current Publishe name is ";
 puts(Publisher);
 cout<<"         Do you wish to change it?  (y/n) ";
 cin>>ch;
 if(ch=='y' || ch=='Y')
  {
   cout<<"         Enter the new Publisher name ";
   gets(Publisher);
  }
}

/**
 *  Used to print the data of the Video record.
 */

void Video::printData()
{
 cout<<"        Name: ";
 puts(Name);
 cout<<"        Edition: "<<Edition<<endl;
 cout<<"        Price: " <<Cost<<endl;
 cout<<"        Publisher: ";
 puts(Publisher);
}

/**
 *  Used to get the roll number of the student.
 */

int Video::getBarcode()
{
 return Barcode;
}

/**
 *  Used to check if a Video with a given Barcode already exists.
 *  Bcode: The Barcode which is to be looked up
 *  Returns 0: No Video with the given Barcode found.
 *          1: A Video with the given roll number already exists
 */

int checkBcode(int Bcode)
{
 fin.seekg(ios::beg);
 while(fin.read((char *)&video, sizeof(video)))
  if(video.getBarcode()==Bcode)
   return 1;
 return 0;
}

/**
 *  Main function
 */

void main()
{
 /** The choice the user has made */
 int choice;
 /** The Barcode the user has entered */
 int Bcode;
 do{
    clrscr();
    Bcode=-1;
    fin.open("video.dat", ios::binary);
    fout.open("video.dat", ios::binary | ios::app);

    cout<<"================================================="<<endl;
    cout<<"         Video Library Management System         "<<endl;
    cout<<"================================================="<<endl;

    cout<<"    Select an option "<<endl;
    cout<<"    1. Add a Video "<<endl;
    cout<<"    2. Search a Video "<<endl;
    cout<<"    3. Edit a Video's information"<<endl;
    cout<<"    4. Delete a Video"<<endl;
    cout<<"    5. Show all Videos"<<endl;
    cout<<"    6. Exit"<<endl;
    cout<<endl<<"      Enter your choice: ";
    cin>>choice;

    switch(choice)
    {
     case 1:
	    while(Bcode==-1)
	    {
	     cout<<"        Enter the Barcode of the Video: ";
	     cin>>Bcode;
	     if(Bcode==-1)
	      break;
	     else if(Bcode<0)
	      {
	       cout<<"          Barcode can't be negative."<<endl;
	       Bcode=-1;
	      }
	      else if(checkBcode(Bcode)==1)
	       {
		   cout<<" Video with Barcode "<<Bcode;
             cout<<" already exists!"<<endl;
		   Bcode=-1;
	       }
	      else
	       {
		   video.insertData(Bcode);
		   cout<<"       Saved!";
		   fout.write((char*)&video, sizeof(video));
	       }
	    }
	    break;
     
     case 2:
	    while(Bcode==-1)
	    {
	     cout<<"       Enter Barcode of the Video: ";
	     cin>>Bcode;
	     if(Bcode==-1)
	      break;
	     else if(Bcode<0)
	     {
	      cout<<"          Barcode can't be negative."<<endl;
	      Bcode=-1;
	     }
	     else if(checkBcode(Bcode)==0)
	      {
	       cout<<"          Video with Barcode "<<Bcode;
            cout<<" not found!";
	       Bcode=-1;
	      }
	      else
	       video.printData();
	    }
	    break;
     
     case 3:
	    while(Bcode==-1)
	    {
	     cout<<"        Enter Barcode of the Video: ";
	     cin>>Bcode;
	     if(Bcode==-1)
	      break;
	     else if(Bcode<0)
	      {
	       cout<<"          Barcode can't be negative."<<endl;
	       Bcode=-1;
	      }
	     else if(checkBcode(Bcode)==0)
	      {
	       cout<<"          Video with Barcode "<<Bcode;
            cout<<" not found!";
	       Bcode=-1;
	      }
	     else
	      {
	       video.modifyData();
	       cout<<"       Saved!";
	       fin.seekg (ios::beg);
	       ofstream newFile("temp.dat", ios::binary);
	       newFile.write((char*)&video, sizeof(video));
	       while(fin.read((char*)&video, sizeof(video)))
	       {
		if(video.getBarcode()!=Bcode)
		 newFile.write((char*)&video, sizeof(video));
	       }
	       newFile.close();
	       remove("video.dat");
	       rename("temp.dat", "video.dat");
	      }
	    }
	    break;

     case 4:
	    while(Bcode==-1)
	    {
	     cout<<"       Enter Barcode of the Video: ";
	     cin>>Bcode;
	     if(Bcode==-1)
	      break;
	     else if(Bcode<0)
	      {
	       cout<<"           Barcode can't be negative."<<endl;
	       Bcode=-1;
	      }
	     else if(checkBcode(Bcode)==0)
	      {
	       cout<<"       Video with Barcode "<<Bcode;
            cout<<" not found!";
	       Bcode=-1;
	      }
	     else
	      {
	       char ch;
	       video.printData();
	       cout<<"Are you sure you want to delete this record?";
	       cin>>ch;
	       if(ch=='y' || ch=='Y')
		  {
		   cout<<"          Record successfully deleted!";
		   fin.seekg(ios::beg);
		   ofstream newFile("temp.dat", ios::binary);
		   while(fin.read((char*)&video, sizeof(video)))
		   if(video.getBarcode()!=Bcode)
		   newFile.write((char*)&video, sizeof(video));

		   newFile.close();
		   remove("video.dat");
		   rename("temp.dat", "video.dat");
		  }
	      }
	    }
	    break;
     case 5:
	    Bcode=0;
	    while (fin.read((char*)&video, sizeof(video)))
	    {
	     cout<<"       Barcode: "<<video.getBarcode()<<endl;
	     video.printData();
	     cout<<endl;
	     Bcode++;
	     getch();
	    }
	    if(Bcode==0)
	     cout<<"        No records found!";
	    else
	     cout<<"     Only "<<Bcode<<" video record(s) stored!";
	    break;

     default:
	     if(choice!=6)
	      cout<<"       Invalid option!";
	     break;
    }
   fin.close();
   fout.close();
   getch();

  }while(choice!=6);
}
