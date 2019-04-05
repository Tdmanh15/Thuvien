#include<iostream>
#include<fstream>
#include<ctime>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip>
#include<windows.h>
#include<graphics.h>
#include <sstream>
#define MAX 100

using namespace std;

struct Book
{
	string Tensach;
	string Masach;
	int Vitri;
	int Trangthai;
};

struct NodeSach
{
	Book sach;
	NodeSach *next;
};
typedef NodeSach *PTR_Sach;

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




struct Date
{
	int day;
	int month;
	int year;
};


struct MuonTra
{
	string TenSachMT;
	string MaSachMT;
	Date NgayMuon;
	Date NgayTra;
	int TrangThaiM;
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
	int TrangThaiMuon=0;
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
};typedef NodeDocGia *NODEPTR;






void Menu();
void NhapTheDocGia(int &NhapMaThe);
void Initialize(NODEPTR &root);
void Insert_Node(NODEPTR &p,int x, DocGia a);

void ThemTheDocGia(NODEPTR &root);
void XoaTheDocGia();
void SuaTheDocGia();
int TrangThaiThe();

void InDanhSachDocGia();

void NhapThongTinDauSach();

void InThongTinDauSach();
void SearchSach();
void InMuonSach();
void InTraSach();
void LietKe();
void InDanhSachDocGiaMuonQuaHan();
void Top10SachMuonNhieuNhat();
void LuuCSDL(NODEPTR &root , ofstream &FileDocGia);
void GiaoDien(int luachon);



int main()
{
	int luachon=1;
	NODEPTR root;
	ofstream FileDocGia;
	ThemTheDocGia(root);
//	LuuCSDL(root, FileDocGia);
//	GiaoDien(luachon);
	return 0;
}

// xay dung ham do hoa.
void gotoxy(int x, int y)
{
    static HANDLE  h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x,y};
    SetConsoleCursorPosition(h,c);
}
int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}
int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void hidecursor()
{
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.dwSize = 30;
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
void unhidecursor(){
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.dwSize = 30;
	CursorInfo.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
void Inxy(int x, int y, string z, bool lightbar){
	gotoxy(x,y);
	if(lightbar){
		SetColor(0);
		SetBGColor(15);
	}
	cout<<z<<string(48-z.length(),' ');
	SetColor(15);
	SetBGColor(0);	
}
void Inxy(int x, int y, string z){
	gotoxy(x,y);
	cout<<z;	
}
//Ket thuc xay dung ham do hoa.

bool SoSanhChuoi(string s1, string s2)
	{
		for(int i = 0; i < s1.length(); i++)//string.length() => Tra ve so ki tu chuoi so
		{
			s1[i] = toupper(s1[i]);//toupper(int c) => bien doi ki tu thuong thanh in hoa
		}
		for(int i = 0; i < s2.length(); i++)
		{
			s2[i] = toupper(s2[i]);
		}
		if(s1 == s2)
			return true;
		else 
			return false;		
	}
void Xoa_Khoang_Trang_Thua_Dau_Va_Cuoi(string &str)
{
	// Buoc 1: Xóa het tat ca các kí tu khoang trang thua dau chuoi
	// cho vòng lap while lap cho den khi nào kiem tra kí tu dau tiên - vi trí 0(la ki tu dau) không phai là khoang trong thì dung
	while (str[0] == ' ')
	{
		str.erase(str.begin() + 0); // xóa kí tu tai vi trí 0
	}


	// Buoc 2: Xóa het tat ca các kí tu khoang trang thua o cuoi chuoi
	while (str[str.length() - 1] == ' ')
	{
		str.erase(str.begin() + str.length() - 1); // xóa kí tu tai vi trí cuoi cua chuoi
	}
}

// hàm xóa khoang trang thua o giua các tu
void Xoa_Khoang_Trang_Giua_Cac_Tu(string &str)
{
	for (int i = 0; i < str.length(); i++)
	{
		// neu 2 kí tu liên tiep nhau mà có nhieu hon 2 khoang trang ==> xóa di 1 kí tu
		if (str[i] == ' ' && str[i + 1] == ' ')//ktra ki tu truoc va sau xem có cùng la khoang trang
		{
			str.erase(str.begin() + i);
			i--;// xoa di 1 khoang trang thi phai tru i di 1 cho du vong lap
		}
	}
}

// hàm viet hoa kí tu dau cua moi tu
void In_Hoa_Ki_Tu_Dau_Moi_Tu(string &str)
{
	// Buoc 1: chuyen chuoi str ve chuoi in thuong
	strlwr((char *)str.c_str()); // hàm chuyen chuoi str ve chuoi in thuong
	// Buoc 2: viet hoa kí tu dau cua moi tu
	if (str[0] != ' ')
	{
		if (str[0] >= 97 && str[0] <= 122)// 97-a và 122-z trong bang ma ACSII
		{
			str[0] -= 32;//65-a =>32 là khoang cach tu a-A trong bang ma
		}
		
	}
	// kí tu tai vi trí i là khoang trong, i + 1 khác khoang trong thì kí tu tai vi trí i + 1 chính là kí tu dau tiên cua moi tu
	for (int i = 0; i < str.length() - 1; i++)
	{
		if (str[i] == ' ' && str[i + 1] != ' ')
		{
			if (str[i + 1] >= 97 && str[i + 1] <= 122)
			{
				str[i + 1] -= 32; // <=> str[i + 1] = str[i + 1] - 32;
			}
		}
	}
}	
string ChuanHoaChuoi(string s)
{
	string str = s;
	Xoa_Khoang_Trang_Thua_Dau_Va_Cuoi(str);
	Xoa_Khoang_Trang_Giua_Cac_Tu(str);
	In_Hoa_Ki_Tu_Dau_Moi_Tu(str);
	return str;
}
void NhapTheDocGia(int &NhapMaThe)
{
	
}
//Bat dau tao cay nhi phan

void Initialize(NODEPTR &root)//Khoi tao cay
{
	root==NULL;
}
void Insert_Node(NODEPTR &p,int x, DocGia a)//them khoa x vao cay voi goc la root
{
	if(p==NULL)//p hien la nut la
	{
		p=new NodeDocGia;
		p->key=x;
		p->docgia=a;
		p->left=NULL;
		p->right=NULL;
	}
	else if(x<p->key)
	Insert_Node(p->left,x,a);
	else if(x>p->key)
	Insert_Node(p->right,x,a);
}
//Ket thuc
void ThemTheDocGia(NODEPTR &root)
{
	DocGia dg;
	int count =0;
	string ho,ten,gt;
	int num; //So doc gia ban muon nhap
	cout<<"Ban muon them bao nhieu doc gia :";
	cin>>num;
	for(int i=0;i<num;i++)
	{
		count+=1;
		dg.MaThe=count;
		int ktra=0;
		cout<<"Ma The Doc Gia : "<<dg.MaThe<<endl;
		do
		{
			cout<<"Moi Nhap Ho Doc Gia : ";
			fflush(stdin); //dùng de xoá bo nho dêm
			getline(cin,ho);
		if(ho == "")
			{
				ktra+=1;
				cout<<"Nhap Ho Khong Hop Le . "<<endl<<"Moi Nhap Lai.";
				cout<<"Ma The Doc Gia : "<<dg.MaThe<<endl;
				cout<<"Moi Nhap Ho Doc Gia : ";
				fflush(stdin); //dùng de xoá bo nho dêm
				getline(cin,ho);
			}
		else
		break;
	}while(ktra==0);
	if(SoSanhChuoi(ho,"thoat")==true)
	return;
	else if(SoSanhChuoi(ho,"thoat")==false)
	dg.Ho=ChuanHoaChuoi(ho);
	do
		{
		cout<<"Moi Nhap Ten Doc Gia : ";
		fflush(stdin); //dùng de xoá bo nho dêm
		getline(cin,ten);
		if(ten == "")
			{
				ktra+=1;
				cout<<"Nhap Ten Khong Hop Le . "<<endl<<"Moi Nhap Lai.";
				cout<<"Ma The Doc Gia : "<<dg.MaThe<<endl;
				cout<<"Ho Doc Gia : "<<ho<<endl;
				cout<<"Moi Nhap Ten Doc Gia : ";
				fflush(stdin); //dùng de xoá bo nho dêm
				getline(cin,ten);
			}
			else
			break;
		}while(ktra==0);
		if(SoSanhChuoi(ten,"thoat")==true)
		return;
		else if(SoSanhChuoi(ten,"thoat")==false)	
		dg.Ten=ChuanHoaChuoi(ten);
		do
			{
			cout<<"Moi Nhap Gio Tinh Doc Gia (Nam/Nu) : ";
			fflush(stdin); //dùng de xoá bo nho dêm
			getline(cin,gt);
			if(gt=="")
				{
					if(SoSanhChuoi(gt,"Nam")==false||SoSanhChuoi(gt,"Nu")==false)
						{
							ktra+=1;
							cout<<"Nhap Gioi Tinh Khong Hop Le . "<<endl<<"Moi Nhap Lai.";
							cout<<"Moi Nhap Gioi Tinh Doc Gia : ";
							fflush(stdin); //dùng de xoá bo nho dêm
							getline(cin,gt);
						}
				}
					else
					break;
			}while(ktra==0);
	dg.GioiTinh=ChuanHoaChuoi(gt);
	dg.dsMuonTra = NULL;
	dg.TrangThaiThe =1;
	dg.TrangThaiMuon=0;
	Insert_Node(root,dg.MaThe,dg);
	cout<<"Da Them Doc Gia Thanh Cong."<<endl;
	}
}
void XoaTheDocGia()
{
	
}
void SuaTheDocGia()
{
	
}

int TrangThaiThe()
{
	
}

void InDanhSachDocGia()
{
	
}

void NhapThongTinDauSach()
{
	
}

void InThongTinDauSach()
{
	
}
void SearchSach()
{
	
}
void InMuonSach()
{
	
}
void InTraSach()
{
	
}
void LietKe()
{
	
}
void InDanhSachDocGiaMuonQuaHan()
{
	
}
void Top10SachMuonNhieuNhat()
{
	
}
void LuuCSDL(NODEPTR &root , ofstream &FileDocGia)
{
		FileDocGia.open("FileDocGia.txt");
	if(!FileDocGia)
	{
		cout<<"Khong the mo file"<<endl;
	}
	//Luu danh sach doc gia
		const int STACKSIZE = MAX;
		NODEPTR Stack[STACKSIZE];
		int sp = -1;
		NODEPTR p = root;
		
		while(p!=NULL)
		{
			FileDocGia<<p->docgia.MaThe<<endl;
			FileDocGia<<p->docgia.Ho<<endl;
			FileDocGia<<p->docgia.Ten<<endl;
			
			
			if(p->right!=NULL)
				Stack[++sp]=p->right;
			if(p->left!=NULL)
				p=p->left;
			//else if(sp == -1)break;
		//	else p=Stack[sp--];
	}
		cout<<"Da luu thanh cong"<<endl;
		FileDocGia.close();
}
void Menu(int i, bool lightbar)
{
	hidecursor();	
	switch (i)
	{
		case 1:
			Inxy(28,2,"1. NHAP THE DOC GIA",lightbar);
			break;
		case 2:
			Inxy(28,3,"2. IN DANH SACH DOC GIA",lightbar);
			break;
		case 3:
			Inxy(28,4,"3. NHAP THONG TIN DAU SACH",lightbar);
			break;
		case 4:
			Inxy(28,5,"4. IN DANH SACH DAU SACH",lightbar);
			break;
		case 5:
			Inxy(28,6,"5. TIM SACH",lightbar);
			break;
		case 6:
			Inxy(28,8,"6. MUON SACH",lightbar);
			break;
		case 7:
			Inxy(28,9,"7. TRA SACH",lightbar);
			break;
		case 8:
			Inxy(20,10," Thoat",lightbar);
	}
}
void GiaoDien(int luachon)
{
	system("cls");
	Inxy(32,0,"QUAN LY THU VIEN");
	for(int i=1;i<=8;i++)
	{
		Menu(i,false);
	}
		Menu(luachon,true);
}

