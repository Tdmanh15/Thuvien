#include<iostream>
#include<fstream>
#include<ctime>
#include<string.h>


using namespace std;


struct Book
{
	string ISBN;
	string Book_title;   //Tên sách
	int Number_of_pages;  //sô trang
	string Author;  //Tac gia
	int Publication_year;   //nam xuat ban
	string Type_book;// The loai
	PTR_Sach First; //con tro tro den cac sach thuoc dau sach tuong ung.
	
}
struct List_of_books      //danh muc sach
{
	
}
struct Date
{
	int day;
	int month;
	int year;
};

struct 
