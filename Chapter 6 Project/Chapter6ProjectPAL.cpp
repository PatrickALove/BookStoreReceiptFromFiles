/*
Author:        Patrick Love
Date:          10/20/2018
Purpose:       This program grabs input from a file containing multiple lines. It tests that data
               and spits out a Receipt for each book a customer bought.*/




#include<iostream>// directive to include tools for input and output
#include<iomanip>// directive to include tools for manipulating format of output
#include<string>// directive to include tools for string class
#include<fstream>//directive to include tools to read/write data from and to file

using namespace std;

int main()
{
	//Declaring constants setting values so they can be changed easily if needed.
	const double TAX_RATE = .07;
	const double FIFTY_FEE = 50.00; // Fee for 20 or more books.
	const double FORTY_FEE = 40.00;// Fee for 15-19 books.
	const double THIRTY_FEE = 30.00;// Fee for 10-14 books.
	const double TWENTY_FEE = 20.00;// Fee for 5-9 books.
	const double TEN_FEE = 10.00;// Fee for less than 5 books.

	//Declaring variables that are either read from file or a result of processing.
	double price;
	double sub_Total;
	double tax_Amount;
	double fee_Amount;
	double total;

	int quantity;

	//Declaring and intializing bool variables.
	bool isFiction = false;// acts as a flag for processing purposes. 

	//Declaring variables for menu.	
	char genre;
	char enter_Type;// reads char value from file to deterimine if a book is fiction or nonfiction.

	//Declaring sring varibles to be read from file or written to file.
	string title;
	string ISBN;
	string author;
	string book_Type;// to display book type on invoice.
	string str_Genre;// To display genre type on invoice.
	string str_Cutomer_ID;

	//Declaring file input stream object.
	ifstream invoice_Input_File;//object used to read data from the file.


	//Get data from the file.
	//First open the file then use nested loop to read and write the data.
	invoice_Input_File.open("BookOrderData Text File.txt");

	//object used to write data to the file is declared and opened.
	ofstream invoice_Output_File;
	invoice_Output_File.open("chp5_Output_Project_File.txt");

	//Declaring and intializing accumulator variables to be ussed in loop.
	double total_Books_Sold = 0;
	double total_Sales = 0;
	double grand_Total = 0;
	while (invoice_Input_File >> str_Cutomer_ID >> title >> author >> ISBN >> price >> quantity >> enter_Type >> genre)
	{
		// ID genre.
		//Determines string to written into the file based.
		switch (genre)
		{
		case 'M': str_Genre = "Mystery";
			break;
		case 'R': str_Genre = "Romance";
			break;
		case 'D': str_Genre = "Drama";
			break;
		}
		// ID book type and set flag based on type of book.
		if (enter_Type == 'N')
		{
			isFiction = false;
			book_Type = "Nonfiction";
		}
		else if (enter_Type == 'F')
		{
			isFiction = true;
			book_Type = "Fiction";
		}

		//Deteriming fee amount based on input and purchases.
		//Declare variable to be used in deteriming fees.
		int fee_Factor = quantity / 5;//Used to determine int for switch case based on int division in processing
		switch (fee_Factor)
		{
		case 4:	fee_Amount = FIFTY_FEE;
			break;
		case 3: fee_Amount = FORTY_FEE;
			break;
		case 2: fee_Amount = THIRTY_FEE;
			break;
		case 1: fee_Amount = TWENTY_FEE;
			break;
		default: fee_Amount = TEN_FEE;
		}

		// If the below conditiion is met all fees are removed.
		if ((isFiction == false) && (str_Genre == "Romance"))
		{
			fee_Amount = 0;
		}



		//Processing total.		
		sub_Total = price * quantity;
		tax_Amount = sub_Total * TAX_RATE;
		total = sub_Total + tax_Amount;
		grand_Total = sub_Total + tax_Amount + fee_Amount;


		//processing total books sold and total sales.
		total_Sales += sub_Total;
		total_Books_Sold += quantity;

		//Setting formatting specs.
		invoice_Output_File << fixed << setprecision(2);

		//Writing to the output file. 
		invoice_Output_File << "Invoice" << endl;
		invoice_Output_File << "Customer ID: " << str_Cutomer_ID << "\n" << "\n";
		invoice_Output_File << title << '\t' << book_Type << '\t' << str_Genre << '\t' << quantity << '@' << price << '\t' << sub_Total << "\n";
		invoice_Output_File << '\n';
		invoice_Output_File << "Total Book Sales: " << setw(5) << right << sub_Total << "\n";
		invoice_Output_File << "Tax: " << setw(18) << right << tax_Amount << "\n";
		invoice_Output_File << "SubTotal: " << setw(13) << right << total << "\n";
		invoice_Output_File << "Fees: " << setw(17) << right << fee_Amount << "\n";
		invoice_Output_File << "Total: " << setw(16) << right << grand_Total << "\n";
		invoice_Output_File << "----------------------------------------------------------------------------------" << "\n" << "\n";





	}
	//Resetting formatting specs outside of loop.
	invoice_Output_File << fixed << setprecision(2);
	invoice_Output_File << "Total Book Sales: " << setw(23) << right << total_Sales << endl;
	invoice_Output_File << "Average Books Sale: " << setw(21) << right << total_Sales / double(total_Books_Sold);

	//Closing both the input and output files. 
	invoice_Input_File.close();
	invoice_Output_File.close();
	//Pausing the program per teacher's request.

	system("pause");
	return 0;
}
