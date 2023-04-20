#include <iostream>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <fstream>  

using namespace std;

struct hocSinh
{
    int soBaoDanh;
    string hoTen;
    string ngaySinh;
    float toan, van, anh, diemTB;
};

struct node
{
    hocSinh* data;
    node* next = NULL;
};

struct linkedList
{
    node* head = NULL;
    node* tail = NULL;
};

void nhapHocSinh(hocSinh* hs)
{
    cout<<"Ho ten: ";
    cin.ignore();
    getline(cin,hs->hoTen);

    cout<<"ngay sinh (dd/mm/yyyy): ";
    cin.ignore();
    getline(cin, hs->ngaySinh);

    cout << "So bao danh: "; 
    cin >> hs->soBaoDanh;
    cout << "Diem toan: "; 
    cin >> hs->toan;
    cout << "Diem van: "; 
    cin >> hs->van;
    cout << "Diem anh: "; 
    cin >> hs->anh;
    hs->diemTB = (hs->toan + hs->van + hs->anh) / 3;
}
node* KhoiTaoNode() {
    hocSinh* hs = new hocSinh;			// Khai báo con tr? d?ng sv
    nhapHocSinh(hs);						// Nh?p thông tin c?a sv
    node* p = new node;						// Khai báo 1 con tr? p có nhi?m v? truy su?t d? li?u trong node và gán giá tr? data, con tr? cho node
    if (p == NULL) {
        cout << "Bo nho day\n";				// Khi p == NULL t?c là b? nh? stack dã d?y 
        return 0;
    }
    p->data = hs;							// Giá giá tr? con tr? là sv
    p->next = NULL;							// Giá tr? con tr? tr? d?n s? là NULL, tránh th?t thoát d? li?u
    return p;
}

void addToTail(linkedList * list, node *p)
{
    if (list->head == NULL)
    {
        list->head = p;
        list->tail = p;
    }
    else
    {
        (list->tail)->next = p;
        list->tail = p;
    }
}

void printList(linkedList list)
{
    cout << setw(8) << "SBD" << setw(20) << "Ho va ten" << setw(15) << "Ngay sinh" << setw(15) << "Toan" << setw(15) << "Van" << setw(15) << "Anh" << setw(20) << "Diem trung binh" << endl;
    for (node* k = list.head; k != NULL; k = k->next) {
        cout << setw(8) << k->data->soBaoDanh << setw(20) << k->data->hoTen << setw(15) << k->data->ngaySinh << setw(15) << k->data->toan << setw(15) << k->data->van << setw(15) << k->data->anh << setw(20)<<setprecision(3) << k->data->diemTB << endl;
    }
}

node* search(linkedList l, int SBD)
{
    node* p = l.head;
    while ( p != NULL)
    {
        if ((p->data)->soBaoDanh == SBD) {
            return p;
        }
        p = p->next;
    }
    p = NULL;
    return p;
}
void timHS(linkedList l) {
    int SBD;
    cout << "Nhap so bao danh: ";
    cin >> SBD;
    node* p = search(l, SBD);
    if (p == NULL) {
        cout << "Khong co du lieu so bao danh can tim";
    }
    else { 
        cout << setw(8) << "SBD" << setw(20) << "Ho va ten" << setw(15) << "Ngay sinh" << setw(15) << "Toan" << setw(15) << "Van" << setw(15) << "Anh" << setw(20) << "Diem trung binh" << endl;
        cout << setw(8) << p->data->soBaoDanh << setw(20) << p->data->hoTen << setw(15) << p->data->ngaySinh << setw(15) << p->data->toan << setw(15) << p->data->van << setw(15) << p->data->anh << setw(20) <<setprecision(0)<< p->data->diemTB << endl;
    }
}
// Ham xoa HS bang so bao danh duoc nhap tu ban phim
void xoaHS(linkedList &list)
{
    int SBD;
    cout << "Nhap so bao danh: ";
    cin >> SBD;
    node* p = search(list, SBD);
    node* q = list.head;
    if (p == NULL)
        cout<<"Khong co du lieu so bao danh can tim ";
    else
    {
        if (q == p)
        {
            list.head = q->next;
            if (q == list.tail)
                list.tail = NULL;
        }else{
            while (q->next != p) 
            {
                q = q->next;
            }
            q->next = p->next;
        }
        free(p);
    }
}

void suaHS(linkedList& list) {
    int SBD;
    cout << "Nhap so bao danh: ";
    cin >> SBD;
    for(node*k=list.head;k!=NULL;k=k->next)
        if (k->data->soBaoDanh == SBD) {
            nhapHocSinh(k->data);
            return;
        }
    cout << "Khong co du lieu sinh vien can tim";
}
void xoaDSHS(linkedList* list)
{
    node* p = list->head;
    while (list->head != list->tail)
    {
        list->head = (list->head)->next;
        free(p);
        p = list->head; 
    }
    list->head = NULL;
    list->tail = NULL;
    free(p);
}

void interchangeSort(linkedList& l) {
    node* i, * j;

    for (i = l.head; i != l.tail; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data->diemTB > j->data->diemTB)
                swap(j->data, i->data);
        }    
    }
}

node * taoNode(hocSinh* hs) {
    node* p = new node;
    if (p == NULL) {
        cout << "Cap phat that bai!";
        return NULL;
    }
    p->data = hs;
    p->next = NULL;
    return p;
}

void copyList(linkedList * list1, linkedList * list2) //copy tu 1 vao 2
{
	node * p = list1->head;
	xoaDSHS(list2);
    while(p != NULL)
    {
    	node * n = taoNode(p->data);
		addToTail(list2, n);
        p = p->next;
    }
}

int length(linkedList * list)
{
    node * p = list->head;
    int len = 0;
    while(p != NULL)
    {
        len++;
        p = p->next;
    }
    return len; 
}

void mergeList(linkedList * list1, linkedList * list2, linkedList * list3)
{
    node * p1 = list1->head;
    node * p2 = list2->head;
    while((p1 != NULL) && (p2 != NULL))
    {
        if((p1->data)->diemTB <= (p2->data)->diemTB) //nho hon cho vao truoc
        {
    		node * n = taoNode(p1->data);
			addToTail(list3, n);
            p1 = p1->next;
        }
        else
        {
			node * n = taoNode(p2->data);
            addToTail(list3, n);
			p2 = p2->next;
        }
    }
    while(p1 != NULL)
    {
		node * n = taoNode(p1->data);
		addToTail(list3, n);
        p1 = p1->next;
    }
    while(p2 != NULL)
    {
		node * n = taoNode(p2->data);
		addToTail(list3, n);
        p2 = p2->next;
    }
}

void mergeSortList(linkedList * list)
{
    int l = length(list);
    if(l != 1)
    {
        int mid = l/2;
        int i = 0, j = 0;
        node * p = list->head;
        
		linkedList * list1 = new linkedList;
        list1->head = NULL;
        list1->tail = NULL;
        
		linkedList * list2 = new linkedList;
        list2->head = NULL;
        list2->tail = NULL;
        
		linkedList * list3 = new linkedList;
        list3->head = NULL;
        list3->tail = NULL;
        
		for(i = 0; i < mid; i++)
        {
            node * n = taoNode(p->data);
            addToTail(list1, n);
			p = p->next;
        }
        
		for(j = mid; j < l; j++)
        {
            node * n = taoNode(p->data);
            addToTail(list2, n);
			p = p->next;
        }
        
        
		mergeSortList(list1);
		mergeSortList(list2);       
        mergeList(list1, list2, list3); 
		copyList(list3, list);
		  
        xoaDSHS(list1);
        xoaDSHS(list2);
    }
}

void xuatDanhSachHS(linkedList list) {
    ofstream fileout;
    fileout.open("DANHSACHSINHVIEN.TXT", ios::out);
    fileout << setw(8) << "SBD" << setw(20) << "Ho va ten" << setw(15) << "Ngay sinh" << setw(15) << "Toan" << setw(15) << "Van" << setw(15) << "Anh" << setw(20) << "Diem trung binh" << endl;
    for (node* k = list.head; k != NULL; k = k->next) {
        fileout << setw(8) << k->data->soBaoDanh << setw(20) << k->data->hoTen << setw(15) << k->data->ngaySinh << setw(15) << k->data->toan << setw(15) << k->data->van << setw(15) << k->data->anh << setw(20) << k->data->diemTB << endl;
    }
}
void docThongTinTuFile(linkedList * list) {

    fstream docFile("danhsach.txt");
    while (!docFile.eof()) {
        hocSinh* hs = new hocSinh;
        docFile >> hs->soBaoDanh;
        docFile.ignore();
        getline(docFile, hs->hoTen);
        getline(docFile, hs->ngaySinh);
        docFile >> hs->toan;
        docFile >> hs->van;
        docFile >> hs->anh;
        hs->diemTB = (hs->toan + hs->van + hs->anh) / 3;
        node* p = taoNode(hs);
        addToTail(list, p);
    }
    docFile.close();
}
    int main() {
        linkedList list;
        linkedList list1;
        int key;
        cout << "*******************************************************\n";
        cout << "**          CHUONG TRINH QUAN LY HOC SINH            **\n";
        cout << "**      1. Them hoc sinh                             **\n";
        cout << "**      2. Them hoc sinh tu file                     **\n";
        cout << "**      3. In danh sach hoc sinh                     **\n";
        cout << "**      4. Tim kiem hoc sinh theo ma so              **\n";
        cout << "**      5. Sua thong tin hoc sinh                    **\n";
        cout << "**      6. Sap xep hoc sinh theo diem trung binh     **\n";
        cout << "**      7. Xoa hoc sinh theo ma so                   **\n";
        cout << "**      8. Xoa toan bo danh sach                     **\n";
        cout << "**      9. Xuat danh sach sinh vien                  **\n";
        cout << "**      0. Thoat chuong trinh                        **\n";
        cout << "*******************************************************\n";
        while (1) {
            cout << "\nMoi ban chon: ";
            cin >> key;
            if (key == 1) {
                cout << "Nhap thong tin sinh vien \n";
                node* p = KhoiTaoNode();
                addToTail(&list, p);
            }
            if (key == 2) {
                docThongTinTuFile(&list);
            }
            if (key == 3) {
                printList(list);
            }
            if (key == 4) {
                timHS(list);
            }
            if (key == 5) {
                suaHS(list);
            }
            if (key == 6) {
                cin.ignore();
                //interchangeSort(list);
                mergeSortList(&list);
            }
            if (key == 7) {
                xoaHS(list);
            }
            if (key == 8) {
                xoaDSHS(&list);
            }
            if (key == 9) {
                xuatDanhSachHS(list);
            }
            if (key == 0) {
                break;
            }
        }
        return 0;
}
