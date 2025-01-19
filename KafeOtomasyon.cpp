#include <iomanip> 
#include <cstring> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                  
#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Siparis
{
	char masa_no[6];
	char siparis_detay[250];
	char fiyat[20];
};

void SiparisEkle();
void SiparisListeleme();
void SiparisArama();
void SiparisSil();
void SiparisDuzenle();

int main(){
	
	char anamenu;
	do{
	system("cls");
	
	cout << "|-------Hosgeldiniz------|" << endl ;
	cout << "|      Secim Yapiniz     |" << endl ;
	cout << "|   1- Siparis Ekleme    |" << endl ;
	cout << "|   2- Siparis Listeleme |" << endl ;
	cout << "|     3- Siparis Arama   |"<< endl;
	cout << "|    4- Siparis Sil      |"<< endl;
	cout << "|    5- Siparis Duzenle  |"<< endl;
	cout << "|------------------------|" << endl ;
    char secim;
	cin>> secim;
	
	switch(secim) 
	{
		case '1' : 
		{
		SiparisEkle();
		break;	
		}
		case '2' : 
		{
		 SiparisListeleme()	;
		 break;
		}
		case '3' : 
		{
		 SiparisArama()	;
		 break;
		}
		case '4' : 
		{
		 SiparisSil()	;
		 break;
		}
		case '5' : 
		{
		 SiparisDuzenle();
		 break;
		}
	}
	
	cout << "Anamenuye Donmek icin: a basin cikmak icin: c" <<endl ; 
	anamenu=getche();
	
    }while(anamenu=='a');
     

return 0;
}

Siparis siparis;

void SiparisEkle()
{
	ofstream yaz("siparis.dat",ios::binary |ios::app);
	char secim;
	int adet=0;
	
	do{
	cout << "Masa Numarasi Giriniz : " << endl;
	cin>> siparis.masa_no;
	cout << "Siparis Detayini Giriniz(Lutfen Bosluk Kullanmayiniz) : " << endl;
	cin>>siparis.siparis_detay;
	cout << "Toplam Fiyati Giriniz : " << endl;
	cin>> siparis.fiyat;
	yaz.write((char*)&siparis, sizeof(siparis));	
	adet++;	
	cout << "Baska Siparis Eklemek Istermisin (E/H)" << endl;
	secim=getche();
	cout << endl;
	}while(secim=='e' || secim=='E');
	
	cout << adet << " adet Siparis Ekledi.." << endl;
	
	yaz.close();
	
}

void SiparisListeleme()
{
	
	ifstream oku("siparis.dat",ios::binary |ios::app);
	
	oku.seekg(0,ios::end);
	int kayits=oku.tellg()/sizeof(siparis);
	cout << "Toplam Siparis Kayit Sayisi:"<< kayits << endl;
	
	if(kayits>0)
	{
		for(int i=0; i<kayits;i++)
		{
			oku.seekg(i*sizeof(siparis));
			oku.read((char*)&siparis, sizeof(siparis));	
		
			cout << i+1 << ". Siparis Bilgileri"<< endl;
			cout << "Masa Numarasi : "<< siparis.masa_no <<endl ;
			cout << "Siparis Detayi : "<< siparis.siparis_detay <<endl ;
			cout << "Fiyat : "<< siparis.fiyat <<endl ;
		}
	}
	else
	cout << "Kayit Bulunamadi..." << endl;

	oku.close();
}

void SiparisArama()
{
	
	ifstream oku("siparis.dat",ios::binary |ios::app);
	
	oku.seekg(0,ios::end);
	int kayits=oku.tellg()/sizeof(siparis);
	cout << "Toplam Siparis Sayisi:"<< kayits << endl;

cout <<"Aranan Siparisin Masa Numarasini Giriniz"<< endl;
char sip_no[6];
cin>> sip_no;
 		
	if(kayits>0)
	{
		for(int i=0; i<kayits;i++)
		{
			
			oku.seekg(i*sizeof(siparis));
			oku.read((char*)&siparis, sizeof(siparis));
			
			if(strcmp(siparis.masa_no,sip_no)==0)
			{
			cout <<  "Bulunan Siparisin Bilgileri"<< endl;
			cout << "Siparisin Masa Numarasi : "<< siparis.masa_no <<endl ;
			cout << "Siparis Detayi : "<< siparis.siparis_detay <<endl ;
			cout << "Fiyat : "<< siparis.fiyat <<endl ;
		    }
		}
		
		
	}
	else
	cout << "Kayit Bulunamadi..." << endl;

	oku.close();
}

void SiparisSil()
{
	 char sipno[6];
     char secim= ' ';
     bool var=false;
     
    ifstream oku("siparis.dat",ios::binary |ios::app);
	
	oku.seekg(0,ios::end);

	int kayitsayisi=oku.tellg()/sizeof(siparis);
	
     cout<<"Sileceginiz Siparisin Masa Numarasini Giriniz : ";
     cin>>sipno;

     for(int i=0;i<kayitsayisi;i++)
     {
            oku.seekg(i*sizeof(siparis));
			oku.read((char*)&siparis, sizeof(siparis));
			
     if(strcmp(siparis.masa_no,sipno)==0)
       {
                 cout<<endl;
                 cout<<"Siparisin";
                 cout<<"\nMasa Numarasi : "<<siparis.masa_no;
                  cout<<"\nSiparis Detayi : "<<siparis.siparis_detay<<endl;
                   cout<<"\nFiyat : "<<siparis.fiyat;
                
         	 				  
                cout<<"\n\nSilmek Istediginiz Siparis Bu Mu? [E/H] : ";
                 secim=getche();
            if(secim == 'H' || secim == 'h')
              {      
			    Siparis y_sip;
                ofstream y_dosya("Yedek.dat",ios::app|ios::binary);
                
                strcpy(y_sip.masa_no,siparis.masa_no);
                strcpy(y_sip.siparis_detay,siparis.siparis_detay);
                strcpy(y_sip.fiyat, siparis.fiyat);
				  
                y_dosya.write((char*)&siparis, sizeof(siparis));
                y_dosya.close();
              }
            if(secim=='e'||secim=='E')
              {
   			   	var=true;
  		 	  }
        }
             else
             {
              Siparis y_sip;
              ofstream y_dosya("Yedek.dat",ios::app|ios::binary);
              
              strcpy(y_sip.masa_no,siparis.masa_no);
              strcpy(y_sip.siparis_detay,siparis.siparis_detay);
              strcpy(y_sip.fiyat,siparis.fiyat);
                       
              y_dosya.write((char*)&siparis, sizeof(siparis));
              y_dosya.close();
             }
     }
    oku.close();
    if(var)
    {
               remove("siparis.dat");
               rename("Yedek.dat","siparis.dat");
               cout<<"\n Kayit Silindi"<<endl;
    }
    else
    {
               remove("Yedek.dat");
               cout<<"\n Kayit Bulunamadi"<<endl;                  
    }
	
	
}

void SiparisDuzenle()
{
	 char masa_no[6];
     char secim= ' ';
     bool var=false;
     
    ifstream oku("siparis.dat",ios::binary |ios::app);
	
	oku.seekg(0,ios::end);

	int kayitsayisi=oku.tellg()/sizeof(siparis);
		
     cout<<"Duzelteceginiz Siparisin Masa Numarasini Giriniz : ";
     cin>>masa_no;

     for(int i=0;i<kayitsayisi;i++)
     {
            oku.seekg(i*sizeof(siparis));
			oku.read((char*)&siparis, sizeof(siparis));
			
     		if(strcmp(siparis.masa_no,masa_no)==0)
     		  {
     		  	
                 cout<<endl;
                 cout<<"Siparisin";
                 cout<<"\nMasa Numarasi : "<<siparis.masa_no;
                 cout<<"\nSiparis Detayi : "<<siparis.siparis_detay<<endl;
                 cout<<"\nFiyat : "<<siparis.fiyat;
                 
                  cout<<"\n\nDuzeltmek Istediginiz Siparis Bu Mu? [E/H] : ";
                  secim=getche();
                  if(secim == 'E' || secim == 'e')
                  {
                     	var=true;
                        ofstream dosya("Yedek.dat",ios::app|ios::binary);
                        cout << "\nSiparisin Masa Numarasýný Giriniz : "<< endl;
						cin>> siparis.masa_no;
						cout << "Siparis Detayi Giriniz(Lutfen Bosluk Kullanmayiniz) : " << endl;
						cin>>siparis.siparis_detay;
						cout << "Toplam Fiyat Giriniz : " << endl;
						cin>> siparis.fiyat;
						cout << endl;
		  
                        dosya.write((char*)&siparis, sizeof(siparis));
                        dosya.close();
            	  }
            	 else
                 	{
                         Siparis y_sprs;
                         ofstream y_dosya;
                         y_dosya.open("Yedek.dat",ios::app|ios::binary);
                         
                    	 strcpy(y_sprs.masa_no,siparis.masa_no);
            			 strcpy(y_sprs.siparis_detay,siparis.siparis_detay);
            			 strcpy(y_sprs.fiyat,siparis.fiyat);
                         
             			 y_dosya.write((char*)&y_sprs, sizeof(y_sprs));
                         y_dosya.close();
                   }
     }
 }
    oku.close();
    if(var)
    {
               remove("siparis.dat");
               rename("Yedek.dat","siparis.dat");
               cout<<"\nKayit Duzeltildi."<<endl;
    }
    else
    {
               remove("Yedek.dat");
               cout<<"\nKayit Bulunamadi"<<endl;                  
    }

}



