#include<iostream>
#include<fstream>
#include<ctime>
#include<string.h>
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
};
struct NodeDocGia *PTR_DocGia;
//PTR_DocGia tree=NULL;






void Menu();
void NhapTheDocGia(int &NhapMaThe);
string GT();
void ThemTheDocGia();
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




int main()
{
	ThemTheDocGia();
	return 0;
}
void Menu()
{
	cout<<"NHAP THE DOC GIA"<<endl;
	cout<<"IN DANH SACH DOC GIA"<<endl;
	cout<<"NHAP THONG TIN DAU SACH"<<endl;
	cout<<"IN DANH SACH DAU SACH"<<endl;
	cout<<"TIM SACH"<<endl;
	cout<<"MUON SACH"<<endl;
	cout<<"TRA SACH"<<endl;
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
	// Buoc 1: X�a het tat ca c�c k� tu khoang trang thua dau chuoi
	// cho v�ng lap while lap cho den khi n�o kiem tra k� tu dau ti�n - vi tr� 0(la ki tu dau) kh�ng phai l� khoang trong th� dung
	while (str[0] == ' ')
	{
		str.erase(str.begin() + 0); // x�a k� tu tai vi tr� 0
	}


	// Buoc 2: X�a het tat ca c�c k� tu khoang trang thua o cuoi chuoi
	while (str[str.length() - 1] == ' ')
	{
		str.erase(str.begin() + str.length() - 1); // x�a k� tu tai vi tr� cuoi cua chuoi
	}
}

// h�m x�a khoang trang thua o giua c�c tu
void Xoa_Khoang_Trang_Giua_Cac_Tu(string &str)
{
	for (int i = 0; i < str.length(); i++)
	{
		// neu 2 k� tu li�n tiep nhau m� c� nhieu hon 2 khoang trang ==> x�a di 1 k� tu
		if (str[i] == ' ' && str[i + 1] == ' ')//ktra ki tu truoc va sau xem c� c�ng la khoang trang
		{
			str.erase(str.begin() + i);
			i--;// xoa di 1 khoang trang thi phai tru i di 1 cho du vong lap
		}
	}
}

// h�m viet hoa k� tu dau cua moi tu
void In_Hoa_Ki_Tu_Dau_Moi_Tu(string &str)
{
	// Buoc 1: chuyen chuoi str ve chuoi in thuong
	strlwr((char *)str.c_str()); // h�m chuyen chuoi str ve chuoi in thuong
	// Buoc 2: viet hoa k� tu dau cua moi tu
	if (str[0] != ' ')
	{
		if (str[0] >= 97 && str[0] <= 122)// 97-a v� 122-z trong bang ma ACSII
		{
			str[0] -= 32;//65-a =>32 l� khoang cach tu a-A trong bang ma
		}
		
	}
	// k� tu tai vi tr� i l� khoang trong, i + 1 kh�c khoang trong th� k� tu tai vi tr� i + 1 ch�nh l� k� tu dau ti�n cua moi tu
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

void ThemTheDocGia()
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
		fflush(stdin); //d�ng de xo� bo nho d�m
		getline(cin,ho);
		if(ho == "")
		{
			ktra+=1;
			cout<<"Nhap Ho Khong Hop Le . "<<endl<<"Moi Nhap Lai.";
			cout<<"Ma The Doc Gia : "<<dg.MaThe<<endl;
			cout<<"Moi Nhap Ho Doc Gia : ";
			fflush(stdin); //d�ng de xo� bo nho d�m
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
		fflush(stdin); //d�ng de xo� bo nho d�m
		getline(cin,ten);
		if(ten == "")
		{
			ktra+=1;
			cout<<"Nhap Ten Khong Hop Le . "<<endl<<"Moi Nhap Lai.";
			cout<<"Ma The Doc Gia : "<<dg.MaThe<<endl;
			cout<<"Ho Doc Gia : "<<ho<<endl;
			cout<<"Moi Nhap Ten Doc Gia : ";
			fflush(stdin); //d�ng de xo� bo nho d�m
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
		fflush(stdin); //d�ng de xo� bo nho d�m
		getline(cin,gt);
		if(gt=="")
		{
			if(SoSanhChuoi(gt,"Nam")==false||SoSanhChuoi(gt,"Nu")==false)
			{
			
			ktra+=1;
			cout<<"Nhap Gioi Tinh Khong Hop Le . "<<endl<<"Moi Nhap Lai.";
			cout<<"Moi Nhap Gioi Tinh Doc Gia : ";
			fflush(stdin); //d�ng de xo� bo nho d�m
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

