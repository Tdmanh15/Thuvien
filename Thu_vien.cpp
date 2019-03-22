#include<iostream>
#include<fstream>
#include<ctime>
#include<string.h>
#define MAX 100

using namespace std;

struct DauSach
{
	string ISBN;
	string Tensach;
	int Sotrang;
	string Tacgia;
	int NXB;
	string Theloai;
	PTR_Sach FirstSach;	
};

struct Book
{
	string Tensach;
	string Masach;
	int Vitri;
	int Trangthai;
};

struct Date
	int day;
	int month;
	int year;{
};

struct NodeSach
{
	Book sach;
	NodeSach *next;
};
typedef NodeSach *PTR_Sach;

struct MuonTra
{
	string TenSachMT;
	string MaSachMT;
	Date NgayMuon;
	Date NgayTra;
	int TrangThaiMT;
};

struct NodeMuonTra
{
	MuonTra mt;
	NodeMuonTra *next;
};
typedef NodeMuonTra *PTR_MuonTra;

struct DocGia
{
	int MaThe;
	string Ho;
	string Ten;
	string GioiTinh;
	int TrangThaiThe;
	PTR_MuonTra dsMuonTra;//Tro den danh sach cac cuon sach da va dang muon.
	 
};

struct NodeDocGia
{
	int key;
	DocGia docgia;
	struct NodeDocGia *right;
	struct NodeDocGia *left;
};
struct NodeDocGia *PTR_DocGia;
PTR_DocGia tree=NULL;



