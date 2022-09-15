#include <iostream>
#include <conio.h>
#include <windows.h>
#include <mysql.h>
#include <string>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include<stdlib.h>
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;
string starp(int p,string s)
{
    string sk;
    for(int i=0;i<=p;i++)
    {
        sk+=s;
    }
    return sk;
}


class banksystem
{
public:
    static string query;
    static string dat;
    static string up;

    string nam,addr,rec;
    int bal,ac,amm;

    int qstate;

    MYSQL_RES* res;
    MYSQL_ROW row;
    MYSQL* conn;
    string fetch(int some)
    {

    	std::string s1 = SSTR( some );
    	query.clear();
    	rec.clear();
    	query="select * from banks where uid="+s1+"";
        mysql_query(conn,query.c_str());
        res = mysql_store_result(conn);
        while((row=mysql_fetch_row(res)))
        {
            rec+="| ACCOUNT ID : "+string(row[0])+"|NAME : "+string(row[1])+"|ACC TYPE : "+string(row[2])+"|CURRENT BALANCE : "+string(row[3])+"|\n";
        }
        row=NULL;
       mysql_free_result(res);
        res = NULL;
        return rec;
    }
    void welcome();
    void dbcheck();
	void add_acc();
	void view_acc();
	void deposit();
	void withdraw();
	void balance();
	void acList();
	void close();
	void modify();



};
string banksystem::query="";
string banksystem::dat="";
string banksystem::up="";

    void banksystem::dbcheck()
    {

       query="CREATE TABLE IF NOT EXISTS banks (uid int(11) NOT NULL AUTO_INCREMENT,uname varchar(255) NOT NULL,ustatus varchar(255) DEFAULT NULL,bal_amt int(11) NOT NULL,PRIMARY KEY (uid)) ENGINE=MyISAM DEFAULT CHARSET=latin1";
       qstate+= mysql_query(conn,query.c_str());
        query="CREATE TABLE IF NOT EXISTS transhis (tid int(11) NOT NULL,tamt int(11) NOT NULL,tstatus varchar(100) NOT NULL,tdate varchar(200) NOT NULL,KEY tid (tid)) ENGINE=MyISAM DEFAULT CHARSET=latin1";
        qstate+= mysql_query(conn,query.c_str());
        qstate==0 ? cout<<starp(20,"=")<<"All working fine :)"<<starp(20,"=") : cout<<starp(20,"=")<<"Contact your Developer !!"<<starp(20,"=");
    }
  void banksystem::add_acc()
    {
        system("cls");
       cin.ignore();
        cout<<"\nEnter Your Name : ";getline(cin,nam);cout<<endl;
        cout<<"Enter Your Account Type : ";getline(cin,addr);cout<<endl;
        cout<<"Enter balance Amount : ";cin>>bal;cout<<endl;
        try{
        query="insert into banks (uname,ustatus,bal_amt) values ('"+string(nam)+"','"+string(addr)+"',"+ SSTR(bal)+")";
        qstate = mysql_query(conn,query.c_str());
        qstate==0 ? cout<<starp(20,"=")<<"Data has been uploaded to Server.. :)"<<starp(20,"=") : cout<<starp(20,"=")<<"Something is Wrong..."<<starp(20,"=");
         }
         catch (const std::exception& e) {
              std::cout << e.what();
         }


         system("pause");
    }


    void banksystem::view_acc()
    {
        system("cls");
    try{

        string str = "Select * From banks";

       qstate = mysql_query(conn,str.c_str());
       qstate==0 ? cout<<starp(20,"=")<<"Data has been uploaded to Server.. :)"<<starp(20,"=") : cout<<starp(20,"=")<<"Something is Wrong...\n"<<starp(20,"=");
        res = mysql_store_result(conn);
           cout<<"\n\t|\t ACCOUNT ID"<<"\t|\t"
            <<"NAME"<<"\t|\t"
            <<"ACC TYPE"<<"\t|\t"
            <<"CURRENT BALANCE"<<"\t|\t\n";

        while((row=mysql_fetch_row(res)))
        {
            cout<<"\n\t|\t"<<row[0]<<"\t|\t"
            <<""<<row[1]<<"\t|\t"
            <<""<<row[2]<<"\t|\t"
            <<""<<row[3]<<"\t|\t\n";
        }
       }
    catch (...) { /* reference to the base of a polymorphic object*/}
    system("pause");
    }



    void banksystem::deposit()
    {
        system("cls");
        cout<<"Enter Account Number : ";
        cin>>ac;
        cout<<fetch(ac)<<endl;
        cout<<"Enter Amount to deposit : ";
        cin>>amm;
        query="update banks set bal_amt=(bal_amt+"+ SSTR(amm) +") where uid="+ SSTR(ac) +" ";
        qstate = mysql_query(conn,query.c_str());
        qstate==0 ? cout<<"Data has been uploaded to Server.. :)" : cout<<"Something is Wrong...\n";
        query="insert into transhis (tid,tamt,tstatus,tdate) values ("+SSTR(ac)+","+SSTR(amm)+",'credited','"+dat+"')";
        qstate = mysql_query(conn,query.c_str());
        qstate==0 ? cout<<"Data has been uploaded to Server.. :)" : cout<<"Something is Wrong...\n";
        system("pause");
    }


    void banksystem::withdraw()
    {
        system("cls");
        cout<<"Enter Account Number : ";
        cin>>ac;
        cout<<fetch(ac)<<endl;
        cout<<"Enter Amount to withdraw : ";
        cin>>amm;
        query="update banks set bal_amt=(bal_amt-"+SSTR(amm)+") where uid="+SSTR(ac)+" ";
        qstate = mysql_query(conn,query.c_str());
        qstate==0 ? cout<<"Data has been uploaded to Server.. :)" : cout<<"Something is Wrong...\n";
        query="insert into transhis (tid,tamt,tstatus,tdate) values ("+SSTR(ac)+","+SSTR(amm)+",'deducted','"+dat+"')";
        qstate = mysql_query(conn,query.c_str());
        qstate==0 ? cout<<"Data has been uploaded to Server.. :)" : cout<<"Something is Wrong...\n";
        system("pause");
    }


    void banksystem::balance()
    {
        system("cls");
        //freopen("output.doc", "w", stdout);
        cout<<"Enter Account Number : ";
        cin>>ac;
        cout<<starp(80,"=")<<endl;

        cout<<fetch(ac)<<endl;

        cout<<starp(30,"=")<<"Transaction History"<<starp(30,"=")<<endl;
        query="select * from transhis WHERE tid="+SSTR(ac)+"";
        mysql_query(conn,query.c_str());
        mysql_free_result(res);
        res = mysql_store_result(conn);
        cout<<"|\tACCOUNT ID\t"<<"|"
            <<"\tAMOUNT\t"<<"|"
            <<"\tSTATUS\t"<<"|"
            <<"\tDATE\t"<<"|\n";
        while((row=mysql_fetch_row(res)))
        {
            cout<<"|\t\t"<<row[0]<<"\t|\t"
            <<row[1]<<"\t|\t"
            <<row[2]<<"|\t"
            <<row[3]<<"|\n";
        }
        //fclose (stdout);
        system("pause");
    }


    void banksystem::acList()
    {
        system("cls");
        mysql_query(conn,"select * from banks");
        res = mysql_store_result(conn);
        cout<<"| ACCOUNT ID"<<"   |"
            <<"NAME"<<"|"
            <<"ACC TYPE"<<"|"
            <<"CURRENT BALANCE"<<"|\n";
        while((row=mysql_fetch_row(res)))
        {
            cout<<"\t|\t"<<row[0]<<"\t|\t"
            <<row[1]<<"\t|\t"
            <<row[2]<<"\t|\t"
            <<row[3]<<"\t|\t\n";
        }
        system("pause");
    }


    void banksystem::close()
    {
        system("cls");
        cout<<"Enter Account Number";
        cin>>ac;
        query="delete from transhis where tid="+SSTR(ac)+"";

        qstate=mysql_query(conn,query.c_str());

        query="delete from banks where uid="+SSTR(ac)+"";

        qstate= mysql_query(conn,query.c_str());
        qstate==0 ? cout<<"\n"+SSTR(ac)+"Account details has been deleted from Server.. :)\n" : cout<<"Something is Wrong...\n";
        system("pause");
    }

    void banksystem::modify()
    {
        system("cls");
        cout<<"Enter Account Number : ";
        cin>>ac;
        fetch(ac);
        cout<<"Enter \".\" (dot) if you dont want to make changes to data ..";
        cin.ignore();
        cout<<"\nEnter Your Name : ";getline(cin,nam);cout<<endl;
        if(nam!=".")
        {
            query="update banks set uname='"+string(nam)+"' where uid="+SSTR(ac)+"";
            qstate = mysql_query(conn,query.c_str());
        }

        cout<<"Enter Your Account Type : ";getline(cin,addr);cout<<endl;
        if(addr!=".")
        {
            query="update banks set ustatus='"+string(addr)+"' where uid="+SSTR(ac)+"";
            qstate+= mysql_query(conn,query.c_str());
        }

        cout<<"Enter balance Amount : ";cin>>bal;cout<<endl;
        if(cin.fail()==false)
        {
            query="update banks set bal_amt="+SSTR(bal)+" where uid="+SSTR(ac)+"";
            qstate+= mysql_query(conn,query.c_str());

        }
        cin.clear();cin.ignore();
        qstate==0 ? cout<<"Data has been uploaded to Server.. :)" : cout<<"Something is Wrong...\n";
        system("pause");
    }

void banksystem::welcome()
{
    cout<<endl;
    cout<<"========================================================================="<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"****************     B A N K   M A N A G E M E N T      *****************"<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"***************************   S Y S T E M   *****************************"<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"PROJECT : "<<endl;
    cout<<"MADE BY :    AJEET GUPTA         "<<endl;
    cout<<endl;
    cout<<"----         console bank management system                          ----"<<endl;
    cout<<"========================================================================="<<endl;
    cin.get();
}
int main(int argc, char** argv)
{
    system("color 0f");
    banksystem a;
    int a1;
    a.welcome();
    struct tm *newtime;
    time_t ltime;

/* Get the time in seconds */
    time(&ltime);
/* Convert it to the structure tm */
    newtime = localtime(&ltime);
    banksystem::dat=asctime(newtime);//assigning date value o static string

    string host = "localhost";
    string user = "root";
    string pass = "";
    string db = "bank";

   a.conn = mysql_init(0);
 try{
    a.conn=mysql_real_connect(a.conn,host.c_str(), user.c_str(), pass.c_str(), db.c_str(), 0, NULL, 0);
    a.dbcheck();
    }
    catch (const std::exception& ee)
    {
        cout << "Standard exception: " << ee.what() << endl;
    }
if (a.conn)
         cout << starp(60,"=")<<"Connection ok!" << starp(60,"=")<< endl;
    else {
         cout <<starp(60,"=")<< "Connection fail: " << mysql_error(a.conn) <<starp(60,"=")<< endl;
    }

    system("cls");

   do
   {
    system("cls");

    puts("You are Very Valuable to our Company");

    cout<<starp(100,"*")<<endl
    <<"\t 1) Add Account"<<endl
    <<"\t 2) View Account"<<endl
    <<"\t 3) Deposit Amount"<<endl
    <<"\t 4) Withdraw Amount"<<endl
    <<"\t 5) Balance Inquiry"<<endl
    <<"\t 6) All Account Holder List"<<endl
    <<"\t 7) Close an Account"<<endl
    <<"\t 8) Modify an Account"<<endl
    <<"\t 9) Logout"<<endl
    <<"\t 10) Exit"<<endl
    <<starp(100,"*")<<"\nEnter your Choice....."<<endl;
        cin>>a1;
    if(cin.fail())
    {
        cout<<"Plz avoid to enter character"<<endl;
        exit(0);
    }

    try{
        switch(a1)
            {
                case 1: a.add_acc();break;
                case 2:a.view_acc();break;
                case 3: a.deposit();break;
                case 4: a.withdraw();break;
                case 5: a.balance();break;
                case 6: a.acList();break;
                case 7: a.close();break;
                case 8: a.modify();break;
                case 9: a.up="";break;
                case 10: exit(0); break;
                default:cout<<"Plz enter Number from Given Option ONLY..";break;
            }

    }
        catch (const std::exception& e)
        {
            cout << "Standard exception: " << e.what() << endl;
        }
    }while(a1!=9 || a.up!="");

    do
   {
    system("cls");
    puts("You are an Valuable Costumer of BANK");

    cout<<starp(100,"*")<<"\nEnter your Choice....."<<endl
    <<"\t 1) Check your Balance"<<endl
    <<"\t 2) Print Your Balance"<<endl
    <<"\t 3) Logout"<<endl
    <<"\t 4) Exit"<<endl<<starp(100,"*")<<endl;
        cin>>a1;
    if(cin.fail())
    {
        cout<<"Plz avoid to enter character"<<endl;
        cout<<"Plz avoid to enter character"<<endl;
        exit(0);
    }

    try{
        switch(a1)
            {
                case 1: a.balance();break;
                case 2:a.view_acc();break;//have to add print balance...how to write console output into file.
                case 3: a.up="";break;
                case 4: exit(0); break;
                default:cout<<"Plz enter Number from Given Option ONLY..";break;
            }

    }
        catch (const std::exception& e)
        {
            cout << "Standard exception: " << e.what() << endl;
        }
    }while(a1!=9 || a.up!="");

//[ends here]

return 0;
}
