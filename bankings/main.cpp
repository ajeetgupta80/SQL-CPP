#include <iostream>
#include <conio.h>
#include <windows.h>
#include <mysql.h>
#include <sstream>

using namespace std;

int main()
{
    MYSQL* con;
    MYSQL_RES* res;
    MYSQL_ROW row;
    con = mysql_init(0);
    con = mysql_real_connect(con,"localhost","root","","mydb",0,NULL,0);

    // checking if connection is made or not ----------------------
    if(con)
    {
        cout<<"connection succes"<<endl;
    }
    else
    {
        cout<<"connection failed"<<endl;
    }


    // inserting data in table by code ------------------------------------------------

   /*
    stringstream aj;
    aj << "INSERT INTO test(id, name, email , password) VALUES(100, 'abhay','abhay@gmail.com','gupta' )";
    string a = aj.str();

    const char* query = a.c_str();

    if(!(mysql_query(con,query)))
    {

        cout<<"succesfully inserted"<<endl;
    }
    else
    {
        cout<<"faild to insert"<<endl;
    }

    // inserting data in table by the user  -----------------------------------------------------
    int id;
    string name,email,password;
    cout<<"\n\n enter your Id ->" ;
    cin>>id;
    cout<<"\n\n enter your name ->" ;
    cin.ignore();
    getline(cin,name);
    cout<<"\n\n enter your email ->" ;
    cin>>email;
    cout<<"\n\n enter your password ->" ;
    cin>>password;

    stringstream data;
    data << "INSERT INTO test (id , name, email, password) VALUES("<< id <<",' "<< name<<"',' "<< email<<"',' "<< password<<"')";
    string j = data.str();
    const char* qury = j.c_str();
    if(!(mysql_query(con, qury)))
    {
        cout<<"data inserted succesfully"<<endl;
    }
    else
    {
        cout<<"data failed to insert"<<endl;
    }

    */


    // searching id  and showing  related data --------------------------------
    int id;
    int found=0;
    cout<<"\n\n enter the search Id ->";
    cin>>id;
    stringstream a;
    a << "SELECT * FROM test WHERE id = "<<id;
    string b= a.str();
    const char* query = b.c_str();
    if(!(mysql_query(con, query)))
    {

        res = mysql_store_result(con);
        while(row = mysql_fetch_row(res))
        {

            cout<<"\n\n your id -> "<<row[0];
            cout<<"\n\n your name -> "<<row[1];
            cout<<"\n\n your email-> "<<row[2];
            cout<<"\n\n your password -> "<<row[3]<<endl;
            cout<<"---------------------------------------------"<<endl;
            found++;
        }
        if(found == 0)
        {

            cout<<"\n\n ---- record not found -----"<<endl;
        }
    }
    else
    {

        cout<<"\n\n query failed "<<endl;

    }




    getch();
    return 0;
}
