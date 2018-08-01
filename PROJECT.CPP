#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip.h>
void main();
class MENU
{
	public :
			void main_menu(void) ;
			void admin();
			void introduction(void) ;
} ;

class BOOK
{
   protected :
		char book_code[10],no_copies[5];
		char book_name[50],book_author[70];
		float book_prize;
   public:
	void create_book()
	{
		gotoxy(25,2);
		cout<<"......Enter Details......";
		gotoxy(25,4);
		cout<<"Enter Book Code     :";
		cin>>book_code;
		gotoxy(25,6);
		cout<<"Enter Book Name   :";
		gets(book_name);
		gotoxy(25,8);
		cout<<"Enter Book Author :";
		gets(book_author);
		gotoxy(25,10);
		cout<<"Enter Book Prize  :";
		cin>>book_prize;
		gotoxy(25,12);
		cout<<"Enter No of Copies:";
		cin>>no_copies;
		cout<<"\n\n\nBook Added...";
	}

	void show_book()
	{
		cout<<"\nBook no. : "<<book_code;
		cout<<"\nBook Name : ";
		puts(book_name);
		cout<<"\nAuthor Name : ";
		puts(book_author);
		cout<<"\nBook Prize  :"<<book_prize;
	}
	char* retbno()
	{
		return book_code;
	}
	char* retbooknm()
	{
		return book_name;
	}
	void report()
	{cout<<book_code<<setw(20)<<book_name<<setw(20)<<book_author<<setw(20)<<book_prize<<setw(10)<<no_copies<<endl;}
};

class MEMBER : public BOOK
{
	char memb_code[6];
	char memb_name[20],book_nm[40],book_no[20];
	int token;
   public:
	void create_member()
	{
		clrscr();
		cout<<"\nNEW STUDENT ENTRY...\n";
		cout<<"\nEnter The admission no : ";
		cin>>memb_code;
		cout<<"\n\nEnter The Name of The Student : ";
		gets(memb_name);
		token=0;
		cout<<"\n\nStudent Record Created...";
	}
	void show_member()
	{
		cout<<"\nAdmission no : "<<memb_code;
		cout<<"\nStudent Name : ";
		puts(memb_name);
		cout<<"\nNo of Book issued : "<<token;
	}
	char* retmemb_code()
	{
		return memb_code;
	}
	int rettoken()
	{
		return token;
	}
	void addbook(char t[])
	{
		strcpy(book_no,t);
	}
	void addbooknm(char t[])
	{
		strcpy(book_nm,t);
	}
	void addtoken()
	{token=1;}
	void resettoken()
	{token=0;}

	void report()
	{
		cout<<"\t"<<memb_code<<setw(20)<<memb_name;
		if(token==1)
		{
			cout<<setw(10)<<book_no;
			textcolor(GREEN+BLINK) ; textbackground(BLUE) ;
			cprintf(book_nm);
			textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
		}
		cout<<endl;
	}
};

fstream fp,fpt1;
BOOK book;
MEMBER memb;

void add_book()
{
	char ch;
	fp.open("book.txt",ios::out|ios::app);
	do
	{
		clrscr();
		book.create_book();
		fp.write((char*)&book,sizeof(BOOK));
		cout<<"\n\nDo you want to add more record..(y/n?) : ";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void add_member()
{
	char ch;
	fp.open("student.txt",ios::out|ios::app);
	do
	{
		memb.create_member();
		fp.write((char*)&memb,sizeof(MEMBER));
		cout<<"\n\ndo you want to add more record..(y/n?) : ";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void display_book()
{
	clrscr();
	fp.open("book.txt",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN...";
		getch();
		return;
	}
	textcolor(BLUE+BLINK) ; textbackground(YELLOW) ;
	gotoxy(29,3);
	cprintf(" B O O K  D E T A I L E S \n") ;
	textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
	gotoxy(1,5);
	cout<<"===============================================================================\n";
	cout<<"Book Code\t"<<setw(10)<<"Book Name\t"<<setw(15)<<"Author\t"<<setw(15)<<"Book Prize\t"<<setw(15)<<"Book No\n";
	cout<<"===============================================================================\n";
	while(fp.read((char*)&book,sizeof(BOOK)))
	{
		book.report();
	}
	fp.close();
	getch();
}

void display_student()
{
	clrscr();
	fp.open("student.txt",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN...";
		getch();
		return;
	}

	textcolor(BLUE+BLINK) ; textbackground(YELLOW) ;
	gotoxy(29,3);
	cprintf(" M E M B E R  D E T A I L S \n") ;
	textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
	gotoxy(2,5);
	cout<<"=========================================================================\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<" =========================================================================\n";
	while(fp.read((char*)&memb,sizeof(MEMBER)))
	{
		memb.report();
	}

	fp.close();
	getch();
}

////////////delete//////////////
void delete_book()
{
	char n[6];
	clrscr();
	cout<<"\n\n\n\tDELETE BOOK ...";
	cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	fp.open("book.txt",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.txt",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&book,sizeof(BOOK)))
	{
		if(strcmpi(book.retbno(),n)!=0)
		{
			fp2.write((char*)&book,sizeof(BOOK));
		}
	}

	fp2.close();
	fp.close();
	remove("book.txt");
	rename("Temp.txt","book.txt");
	cout<<"\n\n\tRecord Deleted ...";
	getch();
}

void delete_student()
{
	char n[6];
	int flag=0;
	clrscr();
	textcolor(BLUE+BLINK) ; textbackground(BLACK) ;
	gotoxy(29,4);
	cprintf(" D E L E T E  S T U D E N T ") ;
	textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
	cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
	cin>>n;
	fp.open("student.txt",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.txt",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&memb,sizeof(MEMBER)))
	{
		if(strcmpi(memb.retmemb_code(),n)!=0)
			fp2.write((char*)&memb,sizeof(MEMBER));
		else
			flag=1;
	}

	fp2.close();
	fp.close();
	remove("student.txt");
	rename("Temp.txt","student.txt");
	if(flag==1)
		cout<<"\n\n\tRecord Deleted ...";
	else
		cout<<"\n\nRecord not found...";
	getch();
}

/////issue book////////////
void book_issue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter The student's admission no : ";
	cin>>sn;
	fp.open("student.txt",ios::in|ios::out);
	fpt1.open("book.txt",ios::in|ios::out);
	while(fp.read((char*)&memb,sizeof(MEMBER)) && found==0)
	{
		if(strcmpi(memb.retmemb_code(),sn)==0)
		{
			found=1;
			if(memb.rettoken()==0)
			{
				cout<<"\n\n\tEnter the book no : ";
				cin>>bn;
				while(fpt1.read((char*)&book,sizeof(BOOK))&& flag==0)
				{
					if(strcmpi(book.retbno(),bn)==0)
					{
						book.show_book();
						flag=1;
						memb.addbook(book.retbno());
						memb.addbooknm(book.retbooknm());
						memb.addtoken();
						int pos=-1*sizeof(memb);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&memb,sizeof(MEMBER));
						cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
					}
				}
				if(flag==0)
					cout<<"Book no does not exist..";
			}
			else
				cout<<"You have not returned the last book.. ";

		}
	}
	if(found==0)
		cout<<"Student record not exist...";
	getch();
	fp.close();
	fpt1.close();
}

/////////////////////////////////////////////////////////////////////////////
void MENU :: main_menu(void)
{
	char ch ;
	while (1)
	{
		clrscr() ;
		textcolor(RED+BLINK) ; textbackground(BLACK) ;
		gotoxy(29,6);
		cprintf(" B O O K  L I B R A R Y ") ;
		textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
		gotoxy(29,7) ;
		cprintf("~~~~~~~~~~~~~~~~~~~~~~~~") ;
		gotoxy(30,10) ;
		cout <<"1. INTRODUCTION" ;
		gotoxy(30,11) ;
		cout <<"2. ADD NEW BOOK" ;
		gotoxy(30,12) ;
		cout <<"3. ADD NEW MEMBER";
		gotoxy(30,13);
		cout <<"4. LIST OF BOOKS" ;
		gotoxy(30,14);
		cout <<"5. LIST OF MEMBERS";
		gotoxy(30,15);
		cout <<"6. DELETE BOOK";
		gotoxy(30,16) ;
		cout <<"7. DELETE MEMBER";
		gotoxy(30,17);
		cout <<"8. ISSUE BOOK";
		gotoxy(30,18);
		cout <<"9. RETURN BOOK";
		gotoxy(30,19);
		cout <<"0. QUIT" ;
		gotoxy(30,20) ;
		cout <<"Enter your choice : " ;
		ch = getche() ;
		if (ch == '1')
			introduction() ;
		else if (ch == '2')
			add_book() ;
		else if(ch =='3')
			add_member();
		else if (ch == '4')
		       display_book();
		else if (ch == '5')
			display_student();
		else if (ch == '6')
			delete_book();
		else if (ch == '7')
		       delete_student();
		else if (ch == '8')
			book_issue();
		else if (ch == '0')
			break ;
	}
}


//**********************************************************
//ADMIN Function
//**********************************************************
void MENU :: admin()
{
	MENU menu;
	clrscr();
	char pass[10]="admin";
	char p[10];
	gotoxy(12,12);
	cout<<"Welcome In Bytes Softech Pvt. Ltd. Aurangabad Library";
	gotoxy(11,13);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(24,23);
	cout<<"Enter Password :";
	cin>>p;
	if(!strcmp(pass,p))
		menu.main_menu() ;
	else
		main() ;
}


// FUNCTION TO DISPLAY THE INTRODUCTION FOR THE PROJECT.

void MENU :: introduction(void)
{
	clrscr() ;
	gotoxy(31,5) ;
	cout <<"Welcome to Project" ;
	textcolor(BLACK+BLINK) ; textbackground(YELLOW) ;
	gotoxy(33,7) ;
	cprintf(" BOOK LIBRARY ") ;
	textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
	gotoxy(15,10) ;
	cout <<"This  project has facility of maintaining  records" ;
	gotoxy(15,11) ;
	cout <<"of BOOKS and MEMBERS." ;
	gotoxy(15,13) ;
	cout <<"This  project  can  hold more  than  10,000  books" ;
	gotoxy(15,14) ;
	cout <<"records." ;
	gotoxy(15,16) ;
	cout <<"One member can issue one book at a time. If he/she" ;
	gotoxy(15,17) ;
	cout <<"does  not return book upto 15 days he/she have  to" ;
	gotoxy(15,18) ;
	cout <<"pay fine of Rs.1/- per day." ;
	textcolor(LIGHTGRAY+BLINK) ;
	gotoxy(27,24) ;
	cprintf("Press any key to continue") ;
	gotoxy(65,2);
	cprintf("Press 0 to EXIT");
	if(getche()=='0')
		exit(1);
	textcolor(LIGHTGRAY) ;
}

void main()
{
	MENU menu ;
	menu.introduction() ;
	menu.admin();
}