/*
Antony Pierson
Section 1
Assignment 12 - MSQL in C++
Due: 12/5/2018
Function: Prints a report of Book titles, price, and author(s) from a database.
*/

#include <mysql.h>
#include <string>
#include <iostream>
using namespace std;
#define SERVER "courses"
#define USER "z1624182"
#define PASSWORD "1992Jul15"
#define DATABASE "henrybooks"

int main()
{
  MYSQL *connect, mysql;
  connect=mysql_init(&mysql); // Initialize the instance
  connect=mysql_real_connect

  (connect,SERVER,USER,PASSWORD,DATABASE,0,NULL,0);

  if(connect)
  {
    MYSQL_RES *res_set,*res2; /* pointer to receive the return value.*/
    cout << "Antony Pierson Sectin 1\n" << endl;
    string query;
    MYSQL_ROW row,row2; /*  variable for rows. */
    mysql_query(connect,"select Book.Title, Book.Price,Book.BookCode from Book");
    res_set = mysql_store_result(connect);  /* a cursor*/

    while ((row = mysql_fetch_row(res_set)) != NULL)  /*not end of cursor*/
    {
      cout << " Title:  "  << row[0] << endl;
      cout << " Price:  " << "$" << row[1]  <<  endl;

      query = "Select Author.AuthorFirst, Author.AuthorLast from Author, Wrote, Book where Author.AuthorNum = Wrote.AuthorNum and Book.BookCode = Wrote.BookCode and Wrote.BookCode ='";
      query = query + row[2];
      query = query + "';";
	mysql_query(connect,query.c_str());
	res2 = mysql_store_result(connect);

	while((row2 = mysql_fetch_row(res2)) != NULL)
	{
		cout << "Author:  " << row2[0] << " " << row2[1]<<endl;
	}
	cout << "\n";
    }//end while resset

    mysql_free_result(res_set);
    mysql_close(connect);
  } //end if connect
  else
  {
    cout << "Connection Failed! Check your login information\n";
  }
  return 0;
}

