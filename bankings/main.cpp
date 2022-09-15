#include <iostream>
#include <conio.h>
#include <windows.h>
#include <mysql.h>
#include <sstream>

using namespace std;

int main()
{
    MYSQL* con;
    con = mysql_init(0);
    con = mysql_real_connect(con,"localhost","root","","mydb",0,NULL,0);

    if(con)
    {
        cout<<"connection succes"<<endl;
    }
    else
    {
        cout<<"connection failed"<<endl;
    }


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



    getch();
    return 0;
}
