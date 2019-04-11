#include<iostream>
#include<fstream>
#include<ctime>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip>
#include<windows.h>
#include <sstream>
#define MAX 500

using namespace std;

struct Book
{
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
typedef struct list
{
	int n=0; //Khai bao so nut
	int nodes[MAX];
}; 
list ds;
struct Date
{
	int day;
	int month;
	int year;
};
struct MuonTra
{
	string MaSachMT;
	Date NgayMuon;
	Date NgayTra;
	int TrangThaiM;
};
struct NodeMuonTra
{
	MuonTra mt;
	NodeMuonTra *next, *prev;
};
typedef NodeMuonTra *PTR_MuonTra;
struct DocGia
{
	int MaThe;    //key
	string Ho;
	string Ten;
	int SoSachMuon=0;
	string GioiTinh;
	int TrangThaiThe;
	PTR_MuonTra dsMuonTra;//Tro den danh sach cac cuon sach da va dang muon.
	 
};
struct NodeDocGia
{
	DocGia docgia;
	struct NodeDocGia *right;
	struct NodeDocGia *left;
};typedef NodeDocGia *NODEPTR;






void Menu();
void NhapTheDocGia(int &NhapMaThe);
void Initialize(NODEPTR &root);
void Insert_Node(NODEPTR &p,int x, DocGia a);
void LNR(NODEPTR &root);
void ThemTheDocGia(NODEPTR &root);
void XoaTheDocGia();
void SuaTheDocGia();
int TrangThaiThe();
bool Check(char *ch);
void InDanhSachDocGia();
void HamBatPhim(int luachon);
void NhapThongTinDauSach();

void InThongTinDauSach();
void SearchSach();
void InMuonSach();
void InTraSach();
void LietKe();
void InDanhSachDocGiaMuonQuaHan();
void Top10SachMuonNhieuNhat();
void LuuCSDL(NODEPTR &root , fstream &FileDocGia);
void GiaoDien(int luachon);



int main()
{
	NODEPTR root;
	int luachon=1;
//	fstream FileDocGia;
//	ThemTheDocGia(root);
//	LuuCSDL(root, FileDocGia);
	HamBatPhim(luachon);

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
int wherex( void )// tra ve vi tri con tro tai x
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}
int wherey( void )//tra ve vi tri con tro tai y
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}

void SetColor(WORD color)// chon mau cho chu
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

void SetBGColor(WORD color)// chon mau nen
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
void hidecursor()// an con tro
{
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.dwSize = 30;
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
void unhidecursor()//hien con tro
{
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.dwSize = 30;
	CursorInfo.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
void Inxy(int x, int y, string z, bool lightbar)
{
	gotoxy(x,y);
	if(lightbar)
	{
		SetColor(20);
		SetBGColor(15);
	}
	cout<<z;
	SetColor(15);
	SetBGColor(20);	
}
void Xuatxy(int x, int y, string z)
{
	gotoxy(x,y);
	cout<<z;	
}
//Ket thuc xay dung ham do hoa.
bool Check(char *ch)// ktra so hay chu
{
	for(int i=0;i<strlen(ch);i++)
	{
		if(ch[i]<48||ch[i]>57)
		{
			cout<<"Nhap sai.Moi Nhap lai."<<endl;
			return false;
		}
	}
	return true;
}
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
		p->docgia.MaThe=x;
		p->docgia=a;
		p->left=NULL;
		p->right=NULL;
	}
	else if(x<p->docgia.MaThe)
	Insert_Node(p->left,x,a);
	else if(x>p->docgia.MaThe)
	Insert_Node(p->right,x,a);
}
void LNR(NODEPTR &root)
{
	int const STACKSIZE =500;
	NODEPTR Stack[STACKSIZE];
	NODEPTR p=root;
	int sp=-1 ;// Khoi tao stack rong
	do
	{
		while(p!=NULL)
		{
			Stack[++sp]=p;
			p=p->left;
		}
		if(sp!=-1)
		{
			p=Stack[sp--];
			if(p->docgia.TrangThaiThe == 0)
				cout<<"|Da huy kich hoat"<<endl;
			else if(p->docgia.TrangThaiThe ==1)
				cout<<"|Da kich hoat"<<endl;
			else cout<<"|Khong xac dinh"<<endl;
			p=p->right;
		}
		else break;
	}while(1);
}

//Ket thuc
void ThemTheDocGia(NODEPTR &root)
{
	DocGia dg;
	int count =0;
	string ho,ten,gt;
	 //So doc gia ban muon nhap
	char temp[MAX];
	int num=0;
		do
		{
			cout<<"Ban muon them bao nhieu doc gia : ";
			cin>>temp;
		}while(!Check(temp));
		num=atoi(temp);
		for(int i=0;i<num;i++)
		{
			count+=1;
			dg.MaThe=count;
			cout<<"Ma The Doc Gia : "<<dg.MaThe<<endl;
			do
			{
				cout<<"Moi Nhap Ho Doc Gia : ";
				fflush(stdin); //dùng de xoá bo nho dêm
				getline(cin,ho);
				if(ho == "")
				{
					cout<<"Nhap Ho Khong Hop Le . Moi Nhap Lai.\n";
					cout<<"Ma The Doc Gia : "<<dg.MaThe<<endl;
				}
				else
				break;
			}while(ho=="");
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
					cout<<"Nhap Ten Khong Hop Le . "<<endl<<"Moi Nhap Lai.";
					cout<<"Ma The Doc Gia : "<<dg.MaThe<<endl;
					cout<<"Ho Doc Gia : "<<ho<<endl;
				}
				else
				break;
			}while(ten=="");
		if(SoSanhChuoi(ten,"thoat")==true)
		return;
		else if(SoSanhChuoi(ten,"thoat")==false)	
		dg.Ten=ChuanHoaChuoi(ten);
			do
			{
				cout<<"Moi Nhap Gioi Tinh Doc Gia : ";
				fflush(stdin); //dùng de xoá bo nho dêm
				getline(cin,gt);
			if(SoSanhChuoi(gt,"Nam")==true||SoSanhChuoi(gt,"Nu")==true)
			break;
			else
				{
					cout<<"Nhap Gioi Tinh Khong Hop Le . Moi Nhap Lai.\n";
					cout<<"Ma The Doc Gia : "<<dg.MaThe<<endl;
					cout<<"Ho Doc Gia : "<<dg.Ho<<endl;
					cout<<"Ten Doc Gia : "<<dg.Ten<<endl;
				}
			}while(gt=="" || SoSanhChuoi(gt,"NAM")==false || SoSanhChuoi(gt,"NU")==false);
		if(SoSanhChuoi(gt,"thoat")==true)
		return;
		else if(SoSanhChuoi(gt,"thoat")==false)	
	dg.GioiTinh=ChuanHoaChuoi(gt);
//	dg.dsMuonTra = NULL;
	//dg.TrangThaiThe =1;
	//dg.SoSachMuon=0;
	//Insert_Node(root,dg.MaThe,dg);
	cout<<dg.MaThe<<" \t"<<dg.Ho<<"\t"<<dg.Ten<<"\t"<<dg.GioiTinh<<endl;
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
void LuuCSDL(NODEPTR &root , fstream &FileDocGia)
{
		FileDocGia.open("C:/Users/Manh/Google Drive/CSDL&Gt/Thuvien/FileDocGia.txt");
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
		}
	if (FileDocGia.fail())
{
	cout << "Luu file that bai !" <<endl;
	
}
	else
	  {
		cout<<"Da luu thanh cong"<<endl;
		}
		FileDocGia.close();
}
void Menu(int i, bool lightbar)
{
	hidecursor();	
	switch (i)
	{
		case 1:
			Inxy(30,2,"1. NHAP THE DOC GIA",lightbar);
			break;
		case 2:
			Inxy(29,3,"2. IN DANH SACH DOC GIA",lightbar);break;
		case 3:
			Inxy(28,4,"3. NHAP THONG TIN DAU SACH",lightbar);break;
		case 4:
			Inxy(29,5,"4. IN DANH SACH DAU SACH",lightbar);break;
		case 5:
			Inxy(31,6,"5. TIM SACH",lightbar);break;
		case 6:
			Inxy(31,7,"6. MUON SACH",lightbar);break;
		case 7:
			Inxy(31,8,"7. TRA SACH",lightbar);break;
		case 8:
			Inxy(33,9," Thoat",lightbar);
	}
}
void GiaoDien(int luachon)
{
	system("cls");
	Xuatxy(32,0,"QUAN LY THU VIEN");
	for(int i=1;i<=8;i++)
	{
		Menu(i,false);
	}
		Menu(luachon,true);
}
void Exit(int i, bool lightbar){
	switch (i){
		case 1:
			Inxy(2,2,"Co",lightbar);break;
		case 2:
			Inxy(2,4,"Khong",lightbar);break;
	}
}
void GiaoDienExit(int luachon)
{
	system("cls");
	for(int i=1;i<=2;i++)
	{
		Exit(i,false);
	}
	Exit(luachon,true);
}
void DieuKhienPhim(int luachon,char key)
{
while(1)
{
	if(kbhit())
	{
		key=getch();
		switch(key)
		{
			case 80:
				Menu(luachon,false);
				if(luachon==8)
				  luachon=1;
				else
				 luachon++;
				Menu(luachon,true);
				break;
			case 72:
				Menu(luachon,false);
				if(luachon==1)
				  luachon=8;
				else
				 luachon--;
				Menu(luachon,true);
				break;
		}
	}
}	
}
void ESC(int x,char key)
{
	while(1)
{
	if(kbhit())
	{
		key=getch();
		switch(key)
		{
			case 27:
				if(x==27)
				break;
		}
	}
}
