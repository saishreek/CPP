#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
class bank
{
   public:int acno,deposit,d;
           char type;
           char name[50];
    public:void create_acc();
           void viewall();
           void show();
           int retacno() const;
           void showup();
           void change();
           void dep(int);
           void draw(int);
           int retdeposit() const;


};
void intro();
void write_acc();
void disp();
void searchbank(int num);
void deletebank(int num);
void modifybank(int num);
void deposit_withdraw(int, int);




void bank::dep(int x)
{
	deposit+=x;
}

void bank::draw(int x)
{
	deposit-=x;
}

int bank::retdeposit() const
{
	return deposit;
}


void bank::create_acc()
{

	               cout<<"\nEnter The account No. :";
	               cin>>acno;
	               cout<<"\n\nEnter The Name of The account Holder : ";
	               cin.ignore();
	               cin.getline(name,50);
	               name[0]=toupper(name[0]);
	               cout<<"\nEnter Type of The account (C/S) : ";
                   cin>>type;
	               type=toupper(type);
                   cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	               cin>>deposit;
	               cin.get();
	                cout<<"\n\n\nAccount Created..";
	               cout<<"\nAccount No. : "<<acno;
                   cout<<"\nAccount Holder Name : ";
	               cout<<name;
	               cout<<"\nType of Account : "<<type;
	               cout<<"\nBalance amount : "<<deposit;
	               cin.get();

}



void bank::viewall()
{
                 bank b;
                 ifstream fin;
                 fin.open("Input.txt",ios::binary);
                 if(!fin)
                 {
                    cout<<"NO FILE";
                    return;
                 }


                 cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
                 cout<<"====================================================\n";
	             cout<<"A/c no.      NAME       Type       Balance\n";
	             cout<<"====================================================\n";

                 fin.read((char*)(&b),sizeof(b));
                 while(!fin.eof())
                 {
                    b.show();
                    fin.read((char*)(&b),sizeof(b));
                 }
                 fin.close();
                 cin.get();
}

void bank::show()
{
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(10)<<" "<<deposit<<endl;
}

int bank::retacno() const
{
    return acno;
}

void bank::showup()
{
    cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
	cin.get();
}

void bank::change()
{
    cout<<"\n\nEnter the modified details\n\n";
    cout<<"Enter the name: ";
    cin>>name;
    name[0]=toupper(name[0]);
    cout<<"\n\n Enter account number: ";
    cin>>acno;
    cout<<"\n\n Enter the type of account: ";
    cin>>type;
    type=toupper(type);
    cout<<"\n\n Enter the balance: ";
    cin>>deposit;
}


void intro()
{
    string name;
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : SAISHREE,SUBHIKSHA,BHASKAR,PURUSHOTTAM ";
	cout<<"\n\nINSTITUTION : NIE MYSURU ";
	cin.get();
}

void write_acc()
{
    bank b;
	ofstream fout;
	fout.open("Input.txt",ios::binary|ios::app);
	b.create_acc();
	fout.write((char*)&b,sizeof(b));
	fout.close();
}

void disp()
{
    bank b;
    b.viewall();
    cin.get();
}

void searchbank(int num)
{
    bank b;
    bool flag;
    int balance;
    ifstream fin;
    fin.open("Input.txt",ios::binary);
    if(!fin)
    {
       cout<<"Account not found";
       return;
    }
    cout<<"\n\n BALANCE DETAILS\n\n";
    while( fin.read((char*)(&b),sizeof(b)))
    {
      if(b.retacno()==num)
      {
        flag =true;
        b.showup();
      }
    }

    fin.close();
    if(flag==false)
    {
       cout<<"\n\nAccount does not exist";
       cin.get();
    }

}

void deletebank(int num)
{
    bank b;
    int balance;
    ifstream fin;
    ofstream fout;
    fin.open("Input.txt",ios::binary);
    if(!fin)
    {
       cout<<"Account not found";
       return;
    }
    else
    {
       fout.open("Input1.txt",ios::binary|ios::out);

        while( fin.read((char*)(&b),sizeof(b)))
        {
           if(b.retacno()!=num)
           fout.write((char*)(&b),sizeof(b));
        }
        fin.close();
        fout.close();
        remove("Input.txt");
        cout<<"Account deleted"<<endl;
        rename("Input1.txt","Input.txt");
    }
}

void modifybank(int num)
{
    bank b;
   // bool flag=false;
    fstream file;
    file.open("Input.txt",ios::in|ios::out|ios::binary);
    while(!file.eof())
    {
       file.read((char*)(&b),sizeof(b));
       if(b.retacno()==num)
       {
            b.showup();
            b.change();
            int pos=(-1)*static_cast<int>(sizeof(b));
			file.seekp(pos,ios::cur);
            file.write((char*)(&b),sizeof(b));
       }
    }
    cout<<"\n\nRecord updated....";
    file.close();
}

void deposit_withdraw(int num,int n)
{
   bank b;
   int amt;
   cout<<num<<endl<<n<<endl;
   fstream file;
   file.open("Input.txt",ios::in|ios::out|ios::binary);
   while(!file.eof())
   {
       file.read((char*)(&b),sizeof(bank));
       if(b.retacno()==num)
		{
		   b.show();
		   if(n==1)
           {
               cout<<"\n\n\tTO DEPOSITE AMOUNT ";
               cout<<"\n\nEnter The amount to be deposited";
               cin>>amt;
               b.dep(amt);
               cout<<b.deposit<<endl;

               int pos=static_cast<int>(sizeof(b));
               cout<<pos<<endl;
               file.seekp(-pos,ios::cur);
			   file.write((char*) (&b), sizeof(bank));
               cout<<"\n\n\t Record Updated";
               return;
           }
           if(n==2)
           {
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				b.draw(amt);
				cout<<b.deposit<<endl;

               int pos=static_cast<int>(sizeof(b));
               cout<<pos<<endl;
               file.seekp(-pos,ios::cur);
			   file.write((char*) (&b), sizeof(bank));
               cout<<"\n\n\t Record Updated";
               return;
           }



		}
   }


   file.close();
   return;
}



int main()
{
    int ch,num;
    bank b;
    intro();
    while(1)
{
        system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;

		if(ch!=8)
		{
		    switch(ch)
		{
		    case 1:write_acc();
		           break;
            case 2:cout<<"\n\n\tEnter The account No. : ";
                   cin>>num;
                   deposit_withdraw(num,1);
                   cin.get();
                   break;
            case 3:cout<<"\n\n\tEnter The account No. : ";
                   cin>>num;
                   deposit_withdraw(num,2);
                   cin.get();
                   break;
            case 4:cout<<"\n\n\tEnter The account No. : ";
                   cin>>num;
                   searchbank(num);
                   cin.get();
                   break;
            case 5:disp();
                   break;
            case 6: cout<<"\n\n\tEnter The account No. : ";
                    cin>>num;
                    deletebank(num);
                    disp();
                    break;
            case 7:cout<<"\n\n\tEnter The account No. : ";
                   cin>>num;
                   modifybank(num);
                   break;
	}
  }
		else
		break;


}
cout<<"\n\n\nTHANK YOU";
}

