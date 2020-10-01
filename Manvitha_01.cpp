#include<iostream>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;
class icecream 
    {
        int pno;
        char name[50],flavour[50];
        float price, qty, tax, dis;
        public:
            void ip() 
            {
                cout<<"\nPlease Enter The Product No.,name, flavour, price, discount of The Product ";
                cin>>pno>>name>>flavour>>price>>dis;
            }
            void line()
                {
                       for(int i=1;i<61;i++)
                             cout<<"--";

                             cout<<"\n";
                }
            void table() 
               {
                  cout <<"\n\n\n";
                  cout<<setw(60)<<"CREAMSTONE MENU\n";
                  line();
                  cout<<setw(20)<<"Pno"<<setw(20)<<"Name"<<setw(20)<<"Flavour"<<setw(20)<<"Price"<<setw(20)<<"Discount\n";
                  line();
                 }   

            void op() 
            {
                  cout<<setw(20)<<pno<<setw(20)<<name<<setw(20)<<flavour<<setw(20)<<price<<setw(20)<<dis<<endl;
            }

        int retpno() 
        {
            return pno;
        }

        float retprice() 
        {
            return price;
        }

        char * retname() 
        {
            return name;
        }
        char * retflav()
        {
        	return flavour;
		}

        int retdis() 
        {
            return dis;
        }

};
fstream fp;                                                   // global declaration for stream object, object
icecream ic,c1;
void writeproduct()                                          // function to write in file
{
    fp.open("ppp.txt", ios::out | ios::app);
    ic.ip();
    fp.write((char * ) & ic, sizeof(icecream));
    fp.close();
    cout << "\n\nThe Product Has Been Created ";
}
void displayall()                                            // function to read all records from file
{
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("ppp.txt", ios:: in );
    ic.table();
    while (fp.read((char * ) & ic, sizeof(icecream))) 
    {
        ic.op();
    }
    fp.close();
}
void displaysp(int n)                                          // function to read specific record from file
{
    int f= 0;
    fp.open("ppp.txt", ios:: in );
    while (fp.read((char * ) & ic, sizeof(icecream))) 
    {
        if (ic.retpno() == n) 
        {
            ic.op();
            f= 1;
        }
    }
    fp.close();
    if (f == 0)
        cout << "\n\n record does not exist";
}
void modifyproduct()                     // function to modify record of file 
{
    int no, fo = 0;
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product No. of The Icecream";
    cin >> no;
    fp.open("ppp.txt", ios:: in | ios::out);
    while (fp.read((char * ) & ic, sizeof(icecream)) && fo == 0) 
    {
        if (ic.retpno() == no) 
        {
            ic.op();
            cout << "\nPlease Enter The New Details of Icecream" << endl;
            ic.ip();
            int pos = -1 * sizeof(ic);
            fp.seekp(pos, ios::cur);
            fp.write((char * ) & ic, sizeof(icecream));
            cout << "\n\n\t Record Updated";
            fo = 1;
        }
    }
    fp.close();
    if (fo == 0)
        cout << "\n\n Record Not Found ";
}
void deleteproduct()                       // function to delete record of file
{
    int no;
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Icecream You Want To Delete";
    cin >> no;
    fp.open("ppp.txt", ios:: in | ios::out);
    fstream fp2;
    fp2.open("xxx.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & ic, sizeof(icecream))) 
    {
        if (ic.retpno() != no) 
        {
            fp2.write((char * ) & ic, sizeof(icecream));
        }
    }
    fp2.close();
    fp.close();
    remove("ppp.txt");
    rename("xxx.txt", "ppp.txt");
    cout << "\n\n\tRecord Deleted ..";
}
void menu()                          // function to display all products price list 
{
    fp.open("ppp.txt", ios:: in );
    if (!fp) 
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File ";
        cout << "\n\n\n Program is closing ....";
        exit(0);
    }
    while (fp.read((char * ) & ic, sizeof(icecream))) 
    {
    	ic.op();
    }
    fp.close();
}
void placeorder()                       // function to place order and generating bill for Products
{
	int i;
    int orderarr[50], quant[50], c = 0;
    float amt, damt, total = 0;
    //char s[50];
    char ch = 'Y';
    c1.table();
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    		   do 
                {
                  cout << "\n\nEnter The Product No. Of The Icecream : ";
                  cin >> orderarr[c];
                  cout << "\nQuantity in number : ";
                  cin >> quant[c];
                  c++;
                  cout << "\nDo You Want To Order Another Icecream ? (y/n)";
                  cin >> ch;
                } while (ch == 'y' || ch == 'Y');
    cout<< "\n\nThank You For Placing The Order";
    cout << "\n\n******************************************** INVOICE *****************************************************\n";
    cout<<setw(15)<<"Pno"<<setw(15)<<"Name"<<setw(15)<<"Flavour"<<setw(15)<<"Price"<<setw(15)<<"quantity"<<setw(15)<<"Amount"<<setw(15)<<"dis.price\n";
    for (int x = 0; x <= c; x++) 
            {
                fp.open("ppp.txt", ios:: in );
                while (!fp.eof()) 
                {
                      fp.read((char * ) & ic, sizeof(icecream));
                if (ic.retpno() == orderarr[x]) 
                {
                amt = ic.retprice() * quant[x];
                damt = amt - (amt * ic.retdis() / 100);
                cout<<setw(15)<<orderarr[x]<<setw(15)<<ic.retname()<<setw(15)<<ic.retflav()<<setw(15)<<ic.retprice()<<setw(15)<<quant[x]<<setw(15)<<amt<<setw(15)<<damt<<endl;
                total += damt;
                }
                }
               fp.close();
    
            }
      cout << "\n\n\t\t\t\t\tTOTAL = " << total;  
}
void adminmenu()                                          // ADMINSTRATOR MENU FUNCTION 
{
    char ch2;
    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.QUERY ";
    cout << "\n\n\t4.MODIFY PRODUCT";
    cout << "\n\n\t5.DELETE PRODUCT";
    cout << "\n\n\t6.VIEW PRODUCT MENU";
    cout << "\n\n\t7.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-7) "<<endl;
    ch2 = getche();
    switch (ch2) 
    {
    case '1':
        writeproduct();
        break;
    case '2':
        displayall();
        break;
    case '3':
        int num;
        cout << "\n\n\tPlease Enter The Product No. ";
        cin >> num;
        displaysp(num);
        break;
    case '4':
        modifyproduct();
        break;
    case '5':
        deleteproduct();
        break;
    case '6':
        menu();
    case '7':
        break;
    default:
        cout << "\a";
        adminmenu();
    }
}
int main()                                                       // THE MAIN FUNCTION OF PROGRAM
{
    char ch;
    do 
    {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. CUSTOMER";
        cout << "\n\n\t02. ADMINISTRATOR";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        ch = getche();
        switch (ch) 
        {
        case '1':
            placeorder();
            break;
        case '2':
            adminmenu();
            break;
        case '3':
            exit(0);
            break;
        default:
            cout << "\a";
        }
    } while (ch != '3');
}

