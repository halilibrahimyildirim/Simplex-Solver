#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<conio.h>
#include<float.h>
#include<math.h>
#include<time.h>
//05/2017
typedef struct amac{//ama� fonksiyonu ad� ve tipini i�eren yap�
	char ad[10];
	char tip[3];
}amac;
typedef struct kisit{//k�s�tlar�n ad�n�,tipini(L,G,N) ve sa� taraf sabitini i�eren yap�
	char tip[3];
	char ad[10];
	float sts;
	bool standart;
}kisit;
typedef struct degisken{//de�i�ken ad�n�,bulundu�u k�s�tlar� ve katsay�lar�n�,varsa alt-ust s�n�rlar�n� ve free olup olmad���n� i�eren yap�
	char ad[10];
	char **kisitad;
	float *kisitdeger;
	float altsinir,ustsinir;
	bool free;//gereksiz bir de�i�ken olabilir
	int tipi;//0=normal,1=yapay,2=art�k
	int kackisitivar;
}degisken;
char* fonks()//Art�k ve dolgu de�i�ken isimlendirmesi
{
	static char stringcik[5];
	static char sayi[3];
	stringcik[0]='S';
	static int i=0;
	i++;
	itoa (i,sayi,10);
	stringcik[1]=sayi[0];
	stringcik[2]=sayi[1];
	stringcik[3]=sayi[2];
	return stringcik;
}
char* fonkr()//Yapay de�i�ken isimlendirmesi
{
	static char stringcik[4];
	static char sayi[3];
	stringcik[0]='R';
	static int i=0;
	i++;
	itoa (i,sayi,10);
	stringcik[1]=sayi[0];
	stringcik[2]=sayi[1];
	stringcik[3]=sayi[2];
	return stringcik;
}
char* fonkkisit()//K�s�t isimlendirmesi
{
	static char stringcik[10];
	static char sayi[3];
	stringcik[0]='K';
	stringcik[1]='i';
	stringcik[2]='s';
	stringcik[3]='i';
	stringcik[4]='t';
	static int i=0;
	i++;
	itoa (i,sayi,10);
	stringcik[5]=sayi[0];
	stringcik[6]=sayi[1];
	stringcik[7]=sayi[2];
	return stringcik;
}
int adara(degisken degiskenler[],int degiskensay,char m[])//gelen m stringini �uana kadar ki t�m de�i�kenler i�inde arar bulursa 1 bulamazsa 0 d�nd�r�r
{
	int i;
	for(i=0;i<degiskensay;i++)
	{
		if(!strcmp(degiskenler[i].ad,m))return 1;
	}
	return 0;
}
int kisitadara(kisit kisitlar[],int kisitsay,char m[])//gelen m stringini �uana kadar ki t�m k�s�tlar i�inde arar bulursa 1 bulamazsa 0 d�nd�r�r
{
	int i;
	for(i=0;i<kisitsay;i++)
	{
		if(!strcmp(kisitlar[i].ad,m))return 1;
	}
	return 0;
}
int main()
{
	int k,i,j;
	clock_t t;
	char m[10],programadi[20];
	amac fonk;//a�a��da de�i�ikli�e gitti�im i�in kullanmad���m de�i�ken.
	FILE *f=fopen("Deneme.mps","r");
	fscanf(f,"%s",m);//NAME okunur
	fscanf(f,"%s",m);//Program�n ad� al�n�r
	strcpy(programadi,m);
	fscanf(f,"%s",m);//OBJSENSE okundu
	int kisitsay=2,kisitindis=0;
	kisit *kisitlar=(kisit*)calloc(kisitsay,sizeof(kisit));//1 k�s�t i�in yer a��ld�
	int degiskensay=1,degiskenindis=0;
	degisken *degiskenler=(degisken *)calloc(degiskensay,sizeof(degisken));//1 de�i�ken i�in yer a��ld�
	t=clock();
	while(!feof(f))//Dosya okuma
	{
		fscanf(f,"%s",m);//Ama� fonksiyonunun MIN ya da MAX oldu�u okundu
		while(strcmp("ROWS",m)!=0)//dosyadan okunan kelime ROWS olmad��� s�rece �al���r
		{
			strcpy(fonk.tip,m);//Ama� fonksiyonunun tipine MIN ya da MAX oldu�unu yazar
			fscanf(f,"%s",m);//ROWS okunur
		}
		fscanf(f,"%s",m);//ROWS i�indeki ilk kelimeyi(bo�lu�a kadar olan k�sm� okur)
		while(strcmp("COLUMNS",m)!=0)//dosyadan okunan kelime COLUMNS olmad��� s�rece �al���r
		{
			if(!strcmp(m,"G") || !strcmp(m,"L") || !strcmp(m,"E") || !strcmp(m,"N"))//tipi G ya da L ya da E ise �al���r(b�y�ke�it,k���ke�it,e�it)
			{
				strcpy(kisitlar[kisitindis].tip,m);//K�s�tlar�n son ve bo� olan indisteki(bo� eleman) k�sm�na tipini yazd�r�r
				fscanf(f,"%s",m);
				strcpy(kisitlar[kisitindis].ad,m);//Son ve bo� olan indise ad�n� yazd�r�r
				if(!strcmp(kisitlar[kisitindis].tip,"N"))//ama� fonksiyonu ise,fonksiyonun ad�na da yazar,ileride kontrol etmek gerekirse diye
				{
					strcpy(fonk.ad,m);
					kisitlar[kisitindis].sts=0;
				}
				kisitlar[kisitindis].standart=false;
				kisitindis++;
				if(kisitindis==kisitsay)//yeni indis,totalde elimizdeki k�s�t say�s�na e�it ise,dizi dolmu�tur yeni gelecek k�s�t i�in yer a��l�r
				{
					kisitsay++;//k�s�t say�s� 1 artar
					kisitlar=(kisit*)realloc(kisitlar,sizeof(kisit)*kisitsay);//yeni bo�luk a��l�r
				}
				fscanf(f,"%s",m);
			}
		}
		degiskenler[degiskenindis].kisitad=(char**)calloc(kisitsay,sizeof(char*));//ba�lang��ta 1 de�i�ken oldu�u farzedilir,1. de�i�kenin k�s�tlar�n�n ad� i�in yer a��l�yor
		degiskenler[degiskenindis].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//1. de�i�kenin k�s�tlarda sahip oldu�u kat say�lar i�in yer a��l�yor
		for(i=0;i<kisitsay;i++)
		{
			degiskenler[degiskenindis].kisitad[i]=(char*)calloc(10,sizeof(char));//k�s�t adlar�n�n al�nabilmesi i�in yer a��l�yor
		}
		degiskenler[degiskenindis].kackisitivar=0;
		kisitindis=0;
		int adkontrol=0;
		char yedekad[10];
		while(strcmp("RHS",m)!=0)//dosyadan okunan kelime RHS olmad��� s�rece �al���r
		{
			if(adkontrol==0)//ayn� de�i�ken i�in birden fazla sat�r yaz�labiliyor(COLUMNS i�inde) ayn� de�i�kenin ad�n� bir kez daha okumas�n diye
			{
				fscanf(f,"%s",m);
				exception:strcpy(degiskenler[degiskenindis].ad,m);//degiskenin ad�n�(dosyadan gelen),de�i�kenin i�ine yazd�r�r.
				adkontrol=1;
				strcpy(yedekad,m);//ayn� de�i�kenin ad� okundu�unda atlayabilmek i�in konuldu
				if(!strcmp("RHS",m))break;//"RHS" okundu�unda kod burada oluyor ve sonsuz d�ng�ye giriyordu engellemek i�in konuldu
			}
			fscanf(f,"%s",m);//bir kelime daha okunuyor
			if(strcmp(yedekad,m)==0)fscanf(f,"%s",m);//�ayet okunan kelime �uan i�ini doldurdu�umuz de�i�kenin ad� ile ayn� ise bir kelime daha okur
			if(kisitadara(kisitlar,kisitsay,m) || !strcmp(m,fonk.ad))//okudu�umuz kelime k�s�t ad�ysa ya da ama� fonksiyonun ad�ysa �al���r
			{
				strcpy(degiskenler[degiskenindis].kisitad[kisitindis],m);//o an ki de�i�kenin i�ine k�s�t�n ad�n� yazd�r�r
			}
			else//Buraya girdi�inde yeni bir de�i�ken ad�n� okumu� oluyor
			{
				kisitindis=0;
				degiskenler[degiskenindis].tipi=1;
				degiskenindis++;
				degiskensay++;
				degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni de�i�ken i�in boyutland�r�l�yor
				degiskenler[degiskenindis].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni de�i�kenin k�s�tlar�n�n adlar� i�in yer a��l�yor
				degiskenler[degiskenindis].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni de�i�kenin k�s�tlardaki katsay�lar� i�in yer a��l�yor
				for(i=0;i<kisitsay;i++)
				{
					degiskenler[degiskenindis].kisitad[i]=(char*)calloc(10,sizeof(char));//k�s�t adlar� i�in yer a��ld�
				}
				degiskenler[degiskenindis].kackisitivar=0;
				goto exception;//goto kullan�m�n� �nlemek i�in,continue + if(yeni bir de�i�ken) kullansak ayn� duruma denk gelirdi.151.sat�ra d�ner
			}
			fscanf(f,"%s",m);
			sscanf(m,"%f",&degiskenler[degiskenindis].kisitdeger[kisitindis]);//de�i�kenin bulundu�u k�s�ttaki katsay�s� okunmu�tur,i�ine yaz�l�r
			degiskenler[degiskenindis].kackisitivar++;
			kisitindis++;
		}
		while(strcmp("BOUNDS",m)!=0)//dosyadan okunan kelime BOUNDS olmad��� s�rece �al���r
		{
			fscanf(f,"%s",m);
			if(!strcmp("ENDATA",m))break;
			if(kisitadara(kisitlar,kisitsay,m))//Okudu�u �ey k�s�t ad�ysa bura �al���r(RHS1 K�sm�n� �nlemek i�in)
			{
				for(i=0;i<kisitsay-1;i++)//T�m k�s�tlar� gezer
				{
					if(!strcmp(kisitlar[i].ad,m))//k�s�t ad�yla dosyadan okudu�umuz kelime ayn� denk geldi�inde yeni bir kelime okur
					{
						fscanf(f,"%s",m);
						sscanf(m,"%f",&kisitlar[i].sts);//okudu�u kelime k�s�t�n sa� taraf sabitidir,k�s�t�n i�ine yazd�r�l�r
						break;
					}
				}
			}
		}
		for(i=0;i<degiskensay-1;i++)//t�m degi�kenlerin alt ve �st s�n�r� ba�ta 0 yap�l�r
		{
			degiskenler[i].ustsinir=0;
			degiskenler[i].altsinir=0;
		}
		if(!strcmp("ENDATA",m))break;
		while(strcmp("ENDATA",m)!=0)//Dosyan�n sonuna kadar okumak i�in || al�nan kelime ENDATA olana kadar �al���r.
		{
			char yedek[10];
			fscanf(f,"%s",m);//De�i�kenin s�n�r�n�n tipini okur(LO,UP,FR)
			strcpy(yedek,m);//de�i�kenin s�n�r�n� yedek de�i�kene atar
			fscanf(f,"%s",m);//Fazladan okuma BND1 k�sm�n� atlamak i�in
			fscanf(f,"%s",m);//de�i�kenin ad�n� al�r
			for(i=0;i<degiskensay-1;i++)//t�m de�i�kenleri gezer
			{
				if(!strcmp(degiskenler[i].ad,m))//de�i�kenin ad� dosyadan okudu�umuz kelime ile ayn� denk geldi�inde �al���r
				{
					if(!strcmp(yedek,"FR"))//de�i�ken FREE ise �al���r
					{
						degiskenler[i].free=true;//gereksiz bir sat�r olabilir,de�i�kenin free oldu�unu belirtiyor
						//FREE bir de�i�ken ile kar��la�t���m�zda xi=(xi^+)-(xi^-) �ekline �evirdi�imiz i�in 1 de�i�ken daha eklenir
						//Yeni a��lan de�i�ken (xi^-) olacakt�r ��nk� zaten (xi^+) free olan de�i�ken ile ayn� �zelliklere sahiptir
						degiskensay++;
						//a�a��da de�i�ken i�in yer a��lma i�lemleri yap�l�r
						degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);
						degiskenler[degiskenindis].kisitad=(char**)calloc(kisitsay,sizeof(char*));
						degiskenler[degiskenindis].kisitdeger=(float*)calloc(kisitsay,sizeof(float));
						for(j=0;j<kisitsay;j++)
						{
							degiskenler[degiskenindis].kisitad[j]=(char*)calloc(10,sizeof(char));
							strcpy(degiskenler[degiskenindis].kisitad[j],degiskenler[i].kisitad[j]);//yeni a��lan de�i�kenin k�s�tlar�,free olan ile ayn� olaca�� i�in ayn�s� i�ine yazd�r�l�r
							if(degiskenler[i].kisitdeger[j]!=0)
							degiskenler[degiskenindis].kisitdeger[j]=degiskenler[i].kisitdeger[j]*-1;//yeni de�i�ken free olan�n ters i�aretlisidir -1 ile �arp�l�r
							else degiskenler[degiskenindis].kisitdeger[j]=0;
						}
						strcpy(degiskenler[degiskenindis].ad,degiskenler[i].ad);//yeni de�i�kenin ad�n� free de�i�kenin ad�yla ayn� yapar
						degiskenler[degiskenindis].kackisitivar=degiskenler[i].kackisitivar;
						strcat(degiskenler[degiskenindis].ad,"-");//sonuna "-" ekler xi^- gibi g�sterim i�in
						degiskenler[degiskenindis].ustsinir=0;
						degiskenler[degiskenindis].altsinir=0;
						degiskenler[i].free=false;//free de�i�kenin art�k free olmad���n� g�sterir,gereksiz bir atama olabilir
						strcat(degiskenler[i].ad,"+");//free de�i�ken art�k xi^+ de�i�keni olmu�tur.ad�n�n sonuna "+" konur
						degiskenler[degiskenindis].tipi=1;
						degiskenindis++;
					}
					if(!strcmp(yedek,"UP"))//de�i�kenin �st s�n�r� giriliyorsa �al���r
					{
						fscanf(f,"%s",m);//De�i�kenin s�n�r de�erini okur.
						sscanf(m,"%f",&degiskenler[i].ustsinir);//de�i�kenin �st s�n�r�na atar
						
						degiskenler[i].free=false;//�st s�n�r� varsa free olamaz.gereksiz bir atama olabilir
					}
					if(!strcmp(yedek,"LO"))
					{
						fscanf(f,"%s",m);//De�i�kenin s�n�r de�erini okur.
						sscanf(m,"%f",&degiskenler[i].altsinir);//de�i�kenin alt s�n�r�na atar
						degiskenler[i].free=false;//alt s�n�r� varsa free olamaz.gereksiz bir atama olabilir
					}
				}
			}
		}
	}
	fclose(f);
	int negatiflik=-1;
	f=fopen("Sonuc.txt","w");
	fprintf(f,"%s\n\n",programadi);
	kisitsay--;//kisitsay fazladan artt�r�lm��t�,a�a��da kisitsay-2 ile �al��mak yerine burada 1 azalt�l�yor.
	for(i=0;i<degiskensay-1;i++)//Bounds k�sm� i�in k�s�t olu�turuluyor
	{
		if(degiskenler[i].altsinir<0)//de�i�kenin alt s�n�r� negatif ise,s�f�ra �teleme yap�l�r
		{
			for(j=0;j<kisitsay;j++)
			{
				for(k=0;k<degiskenler[i].kackisitivar;k++)
				{
					if(!strcmp(kisitlar[j].ad,degiskenler[i].kisitad[k]))
					{
						kisitlar[j].sts+=(degiskenler[i].kisitdeger[k]*degiskenler[i].altsinir*-1);//de�i�kenin bulundu�u t�m k�s�tlar�n sa� taraf sabitlerine de�i�kenin alt s�n�r�n�n ters i�aretlisi eklenir
					}
				}
			}
			negatiflik=i;
		}
		if(degiskenler[i].altsinir>0)//degiskenin alt s�n�r� varsa
		{
			kisitsay++;
			kisitlar=(kisit*)realloc(kisitlar,sizeof(kisit)*kisitsay);
			strcpy(kisitlar[kisitsay-1].tip,"G");//alt s�n�r� varsa k�s�t b�y�k e�ittir
			kisitlar[kisitsay-1].sts=degiskenler[i].altsinir;//k�s�t�n sa� taraf sabiti o alt s�n�ra e�ittir
			kisitlar[kisitsay-1].standart=false;//yeni k�s�t�n daha standart hale gelmedi�ini belirtiyor
			strcpy(kisitlar[kisitsay-1].ad,fonkkisit());
			for(k=0;k<degiskensay-1;k++)
			{
				degiskenler[k].kisitad=(char**)realloc(degiskenler[k].kisitad,kisitsay*sizeof(char*));//yeni de�i�kenin k�s�tlar�n�n adlar� i�in yer a��l�yor
				degiskenler[k].kisitdeger=(float*)realloc(degiskenler[k].kisitdeger,kisitsay*sizeof(float));//yeni de�i�kenin k�s�tlardaki katsay�lar� i�in yer a��l�yor
				degiskenler[k].kisitad[kisitsay-1]=(char*)malloc(10*sizeof(char));//k�s�t adlar� i�in yer a��ld�
			}
			strcpy(degiskenler[i].kisitad[degiskenler[i].kackisitivar],kisitlar[kisitsay-1].ad);//degiskenin o k�s�tta bulundu�unu g�sterir
			degiskenler[i].kisitdeger[degiskenler[i].kackisitivar]=1.0;//degiskenin o k�s�ttaki katsay�s� 1dir
			degiskenler[i].kackisitivar++;
		}
		if(degiskenler[i].ustsinir!=0)
		{
			kisitsay++;
			kisitlar=(kisit*)realloc(kisitlar,sizeof(kisit)*kisitsay);
			strcpy(kisitlar[kisitsay-1].tip,"L");//degi�kenin �st s�n�r� varsa,k�s�t k���k e�ittir.
			kisitlar[kisitsay-1].sts=degiskenler[i].ustsinir;//degi�kenin �st s�n�r� o k�s�t�n sa� taraf sabitine e�ittir
			kisitlar[kisitsay-1].standart=false;//yeni k�s�t�n daha standart hale gelmedi�ini belirtiyor
			strcpy(kisitlar[kisitsay-1].ad,fonkkisit());
			for(k=0;k<degiskensay-1;k++)
			{
				degiskenler[k].kisitad=(char**)realloc(degiskenler[k].kisitad,kisitsay*sizeof(char*));//yeni de�i�kenin k�s�tlar�n�n adlar� i�in yer a��l�yor
				degiskenler[k].kisitdeger=(float*)realloc(degiskenler[k].kisitdeger,kisitsay*sizeof(float));//yeni de�i�kenin k�s�tlardaki katsay�lar� i�in yer a��l�yor
				degiskenler[k].kisitad[kisitsay-1]=(char*)malloc(10*sizeof(char));//k�s�t adlar� i�in yer a��ld�	
			}
			strcpy(degiskenler[i].kisitad[degiskenler[i].kackisitivar],kisitlar[kisitsay-1].ad);//degiskenin o k�s�tta yer ald��� belirtilir
			degiskenler[i].kisitdeger[degiskenler[i].kackisitivar]=1.0;//kat say�s� 1 dir.
			degiskenler[i].kackisitivar++;
			if(i==negatiflik)//de�i�kenin �st s�n�r� da varsa,o k�s�ta da ekleme yap�l�r
			{
				kisitlar[kisitsay-1].sts+=(degiskenler[i].altsinir*-1);
			}
		}
	}
	int kontrolsay,kontrol=0;
	for(i=0;i<kisitsay;i++)//Negatif sa� taraf sabitleri kontrol ediliyor
	{
		for(j=0;j<degiskensay-1;j++)
		{
			for(k=0;k<kisitsay;k++)
			{
				if(kisitlar[i].sts<0)//k�s�t�n sa� taraf sabiti negatif ise o k�s�ttaki t�m de�i�kenlerin katsay�lar� - ile �arp�l�r
				{
					if(!strcmp(degiskenler[j].kisitad[k],kisitlar[i].ad))
					{
						kontrol=1;
						if(degiskenler[j].kisitdeger[k]!=0)
						degiskenler[j].kisitdeger[k]*=-1.0;
					}
				}
			}
			if(kontrol==1)//bu ife giriyorsa k�s�t�n sa� taraf sabiti negatif demektir
			{
				kisitlar[i].sts*=-1;//k�s�t�n sa� taraf sabiti - ile �arp�l�r
				if(!strcmp(kisitlar[i].tip,"L"))strcpy(kisitlar[i].tip,"G");//e�itsizlik y�n de�i�tirir
				if(!strcmp(kisitlar[i].tip,"G"))strcpy(kisitlar[i].tip,"L");//e�itsizlik y�n de�i�tirir
				kontrol=0;
			}
		}
	}
	for(i=0;i<degiskensay-1;i++)//Elimizde �u anda bulunan t�m de�i�kenler,denklemin kendi de�i�kenleri oldu�u i�in tipleri 0 yap�ld�.
	{
		degiskenler[i].tipi=0;
	}
	for(i=0;i<kisitsay;i++)//Standart hale getirilmesi i�in gerekli de�i�kenler ekleniyor
	{
		if(!strcmp(kisitlar[i].tip,"L") && kisitlar[i].standart==false)//K���k e�it durumu i�in yeni de�i�ken ekleniyor
		{
			degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni de�i�ken i�in boyutland�r�l�yor
			degiskenler[degiskensay-1].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni de�i�kenin k�s�tlar�n�n adlar� i�in yer a��l�yor
			degiskenler[degiskensay-1].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni de�i�kenin k�s�tlardaki katsay�lar� i�in yer a��l�yor
			for(j=0;j<kisitsay;j++)
			{
				degiskenler[degiskensay-1].kisitad[j]=(char*)calloc(10,sizeof(char));//k�s�t adlar� i�in yer a��ld�
			}
			degiskenler[degiskensay-1].kackisitivar=0;
			strcpy(degiskenler[degiskensay-1].ad,fonks());
			strcpy(degiskenler[degiskensay-1].kisitad[degiskenler[degiskensay-1].kackisitivar],kisitlar[i].ad);
			degiskenler[degiskensay-1].kisitdeger[degiskenler[degiskensay-1].kackisitivar]=1.0;
			degiskenler[degiskensay-1].kackisitivar++;
			degiskenler[degiskensay-1].tipi=2;
			degiskensay++;
			kisitlar[i].standart=true;
		}
		if(!strcmp(kisitlar[i].tip,"G") && kisitlar[i].standart==false)//B�y�k e�it durumu i�in yeni de�i�ken ekleniyor
		{
			degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni de�i�ken i�in boyutland�r�l�yor
			degiskenler[degiskensay-1].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni de�i�kenin k�s�tlar�n�n adlar� i�in yer a��l�yor
			degiskenler[degiskensay-1].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni de�i�kenin k�s�tlardaki katsay�lar� i�in yer a��l�yor
			for(j=0;j<kisitsay;j++)
			{
				degiskenler[degiskensay-1].kisitad[j]=(char*)calloc(10,sizeof(char));//k�s�t adlar� i�in yer a��ld�
			}
			degiskenler[degiskensay-1].kackisitivar=0;
			strcpy(degiskenler[degiskensay-1].ad,fonks());
			strcpy(degiskenler[degiskensay-1].kisitad[degiskenler[degiskensay-1].kackisitivar],kisitlar[i].ad);
			degiskenler[degiskensay-1].kisitdeger[degiskenler[degiskensay-1].kackisitivar]=-1.0;
			degiskenler[degiskensay-1].kackisitivar++;
			degiskenler[degiskensay-1].tipi=2;
			degiskensay++;
			//A�a��daki k�s�m yapay de�i�ken
			degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni de�i�ken i�in boyutland�r�l�yor
			degiskenler[degiskensay-1].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni de�i�kenin k�s�tlar�n�n adlar� i�in yer a��l�yor
			degiskenler[degiskensay-1].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni de�i�kenin k�s�tlardaki katsay�lar� i�in yer a��l�yor
			for(j=0;j<kisitsay;j++)
			{
				degiskenler[degiskensay-1].kisitad[j]=(char*)calloc(10,sizeof(char));//k�s�t adlar� i�in yer a��ld�
			}
			degiskenler[degiskensay-1].kackisitivar=0;
			strcpy(degiskenler[degiskensay-1].ad,fonkr());
			degiskenler[degiskensay-1].tipi=1;
			strcpy(degiskenler[degiskensay-1].kisitad[degiskenler[degiskensay-1].kackisitivar],kisitlar[i].ad);
			degiskenler[degiskensay-1].kisitdeger[degiskenler[degiskensay-1].kackisitivar]=1.0;
			degiskenler[degiskensay-1].kackisitivar++;
			degiskensay++;
			kisitlar[i].standart=true;
		}
		if(!strcmp(kisitlar[i].tip,"E") && kisitlar[i].standart==false)//E�ittir durumu i�in de�i�ken ekleniyor
		{
			degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni de�i�ken i�in boyutland�r�l�yor
			degiskenler[degiskensay-1].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni de�i�kenin k�s�tlar�n�n adlar� i�in yer a��l�yor
			degiskenler[degiskensay-1].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni de�i�kenin k�s�tlardaki katsay�lar� i�in yer a��l�yor
			for(j=0;j<kisitsay;j++)
			{
				degiskenler[degiskensay-1].kisitad[j]=(char*)calloc(10,sizeof(char));//k�s�t adlar� i�in yer a��ld�
			}
			degiskenler[degiskensay-1].kackisitivar=0;
			strcpy(degiskenler[degiskensay-1].ad,fonkr());
			strcpy(degiskenler[degiskensay-1].kisitad[degiskenler[degiskensay-1].kackisitivar],kisitlar[i].ad);
			degiskenler[degiskensay-1].kisitdeger[degiskenler[degiskensay-1].kackisitivar]=1.0;
			degiskenler[degiskensay-1].kackisitivar++;
			degiskenler[degiskensay-1].tipi=1;
			degiskensay++;
			kisitlar[i].standart=true;
		}
	}
	//A�a��da,de�i�kenlerde eksik olan k�s�t adlar� de�i�kenlere yaz�l�yor,��nk� matrisi yazd�rma i�lemi �yle ger�ekle�tiriliyor.(k�s�t ad�na g�re arama ile)
	for(i=0;i<kisitsay;i++)//Her de�i�ken i�in,bulunmad��� k�s�tlarda asl�nda 0 katsay�s� ile bulundu�u belirtiliyor
	{
		for(j=0;j<degiskensay-1;j++)
		{
			kontrolsay=0;
			for(k=0;k<kisitsay;k++)
			{
				if(!strcmp(kisitlar[i].ad,degiskenler[j].kisitad[k]))//�ayet j. de�i�ken i. k�s�tta bulunuyorsa
				{	
					kontrolsay=1;
					break;
				}
			}
			if(kontrolsay==0)//�ayet j.de�i�ken i. k�s�tta bulunmuyorsa,i. k�s�t�n ad�n� j. de�i�kene de yazar ve de�i�kenin katsay�s�n� 0 yapar
			{
				strcpy(degiskenler[j].kisitad[degiskenler[j].kackisitivar],kisitlar[i].ad);
				degiskenler[j].kisitdeger[degiskenler[j].kackisitivar]=0.0;
				degiskenler[j].kackisitivar++;
			}
		}
	}
	kisit kisitlar1[kisitsay];
	degisken degiskenler1[degiskensay-1];
	for(i=0;i<kisitsay;i++)
		kisitlar1[i]=kisitlar[i];
	for(i=0;i<degiskensay-1;i++)
		degiskenler1[i]=degiskenler[i];
										//�ki a�amal� y�nteme ba�lan�yor
	int totalyapay=0;
	for(i=0;i<degiskensay;i++)//yapay de�i�kenlerin say�s� bulunur(var olup olmad��� incelenir)
	{
		if(degiskenler[i].tipi==1)totalyapay++;
	}
	bool bitti1;
	float bul=0,min,anahtareleman;
	char giren[20];
	int indisj,indisi,iterasyon1=0,iterasyon2=0,iterasyon11=0,iterasyon22=0;
	float matris[kisitsay][degiskensay],matris1[kisitsay][degiskensay];
	int toplam1,toplam2,kontrol1=0;
	for(i=0;i<kisitsay;i++)//elimizde tutulan t�m de�erleri bir matrisin i�ine at�yoruz,kullan�m kolayl��� i�in
	{
		for(j=0;j<degiskensay-1;j++)
		{
			for(k=0;k<kisitsay;k++)
			{
				if(!strcmp(kisitlar[i].ad,degiskenler[j].kisitad[k]))
				{
					matris[i][j]=degiskenler[j].kisitdeger[k];
				}	
			}
		}
		matris[i][degiskensay-1]=kisitlar[i].sts;
	}
	for(i=0;i<degiskensay-1;i++)//kisit adlar� yerine hangi de�i�ken adlar� konulaca��n� buluyor
	{
		toplam1=toplam2=0;
		for(j=0;j<kisitsay;j++)
		{
			if(degiskenler[i].kisitdeger[j]==1 && strcmp(degiskenler[i].kisitad[j],fonk.ad)!=0)//de�i�kenin k�s�ttaki kat say�s� 1 ise
			{
				toplam1++;
			}
			else if(degiskenler[i].kisitdeger[j]!=0 && strcmp(degiskenler[i].kisitad[j],fonk.ad)!=0)//1 de�il ve 0dan farkl� ise
			{
				toplam2++;
			}
		}
		if(toplam1==1 && toplam2==0)//de�i�kenin t�m k�s�tlar i�inde tek bir de�eri varsa ve o da 1 ise,birim matriste yer al�r
		{
			for(k=0;k<kisitsay;k++)
			{
				if(!strcmp(kisitlar[k].ad,degiskenler[i].kisitad[0]) && degiskenler[i].tipi!=0)//0 olmas�n�n sebebi,yeni eklenen de�i�kenin ilk k�s�t� birim matriste yer ald��� k�s�t olur(her zaman)
				{
					strcpy(kisitlar[k].ad,degiskenler[i].ad);//k�s�t�n ad� bulunur ve de�i�kenin ad� ile de�i�tirilir
				}
			}
		}
	}
	if(totalyapay>0)
	{
						//1. a�ama
		float adim1[degiskensay];
		for(i=0;i<degiskensay-1;i++)//r sat�r� i�in adim1 isimli dizi a��ld�
		{
			if(degiskenler[i].tipi==1)//Yapay de�i�ken ise r sat�r� -1 yap�l�r
			{
				adim1[i]=-1;
			}
			else adim1[i]=0;
		}
		adim1[degiskensay-1]=0;//Sts s�tunu
		for(i=0;i<kisitsay;i++)
		{
			for(j=0;j<degiskensay-1;j++)
			{
				if(!strcmp(kisitlar[i].ad,degiskenler[j].ad) && degiskenler[j].tipi==1)//degiskenin ad�,k�s�t�n ad� ile ayn�ysa ve  degiskenin tipi yapay ise
				{
					for(k=0;k<degiskensay;k++)
					{
						adim1[k]+=matris[i][k];//r sat�r�n� tutarl� hale getirme i�lemi
					}
				}
			}
		}
		do
		{
			min=FLT_MAX;
			bitti1=true;
			bul=0;
			for(i=0;i<degiskensay-1;i++)//giren de�i�ken bulunur
			{
				if(adim1[i]>bul)//ama� fonk min ise pozitifler i�inden en b�y��� bulur
				{
					indisj=i;
					bul=adim1[i];
					bitti1=false;
				}
			}
			if(bitti1)break;
			iterasyon1++;//giren de�i�ken varsa,iterasyon 1 artar
			for(i=1;i<kisitsay;i++)//��kan de�i�ken bulunur
			{
				if(matris[i][indisj]!=0 && (matris[i][degiskensay-1]/matris[i][indisj])<min && (matris[i][degiskensay-1]/matris[i][indisj])>0)
				{
					indisi=i;
					min=matris[i][degiskensay-1]/matris[i][indisj];
				}
			}
			anahtareleman=matris[indisi][indisj];
			for(j=0;j<degiskensay;j++)//anahtar sat�r bulunur
			{
				matris[indisi][j]/=anahtareleman;
			}
			anahtareleman=adim1[indisj];
			for(j=0;j<degiskensay;j++)//r sat�r� bulunur
			{
				adim1[j]-=(anahtareleman*matris[indisi][j]);
			}
			strcpy(kisitlar[indisi].ad,degiskenler[indisj].ad);//k�s�t�n ad�,giren de�i�kenin ad�yla de�i�tirilir
			for(i=1;i<kisitsay;i++)//t�m matriste sat�r i�lemleri ger�ekle�tirilir
			{
				anahtareleman=matris[i][indisj];
				if(anahtareleman==0 || i==indisi)continue;//sat�r�n anahtar eleman� 0 ise ya da anahtar sat�ra denk gelindiyse,o i�lem ge�ilir
				for(j=0;j<degiskensay;j++)
				{
					matris[i][j]-=(anahtareleman*matris[indisi][j]);
				}
			}
		}while(1);
	}
	bool sonuc=true;
	for(i=0;i<kisitsay;i++)
	{
		for(j=0;j<degiskensay-1;j++)
		{
			if(!strcmp(kisitlar[i].ad,degiskenler[j].ad) && degiskenler[j].tipi==1)//ilk a�ama bittikten sonra sat�rlarda R de�i�keni duruyorsa �al���r
			{
				sonuc=false;
				fprintf(f,"Modelin uygun cozumu yoktur.\n\n");
				goto son;//�u ana kadar ge�en s�reyi ve yap�lan iterasyon say�s�n� yazd�rmak i�in kullan�ld�
			}
		}
	}
	//2.a�ama
	for(j=0;j<degiskensay;j++)//Ama� fonksiyonu sat�r� - ile �arp�l�r.
		if(matris[0][j]!=0)
		matris[0][j]*=-1;
	bool bitti2,tutarlimi=false;
	for(i=1;i<kisitsay;i++)
	{
		for(j=0;j<degiskensay-1;j++)
		{
			if(!strcmp(kisitlar[i].ad,degiskenler[j].ad) && degiskenler[j].tipi==0 && degiskenler[j].kisitdeger[0]!=0)//Z sat�r� tutarl� m� diye kontrol edilir
			{
				for(k=0;k<degiskensay;k++)
				{
					if(degiskenler[k].tipi!=1)//yapay de�i�ken de�ilse i�lem yap�l�r
					{
						tutarlimi=true;
						matris[0][k]+=(matris[i][k]*degiskenler[j].kisitdeger[0]);
					}
				}
			}
		}
	}
	if(tutarlimi)
		iterasyon2++;//Z sat�r� tutarl� hale getirildiyse,iterasyon 1 artar
	kontrol1=0;
	do
	{
		min=FLT_MAX;
		bitti2=true;
		bul=0;
		for(j=0;j<degiskensay-1;j++)//giren de�i�ken bulunur
		{
			if(!strcmp(fonk.tip,"MIN") && matris[0][j]>bul && degiskenler[j].tipi!=1)//ama� fonk min ise pozitifler i�inden en b�y��� bulur
			{
				indisj=j;
				bul=matris[0][j];
				bitti2=false;
			}
			else if(!strcmp(fonk.tip,"MAX") && fabs(matris[0][j])>bul && matris[0][j]<0 && degiskenler[j].tipi!=1)//ama� fonk max ise negatifler i�inden en b�y��� bulur
			{
				indisj=j;
				bul=fabs(matris[0][j]);
				bitti2=false;
			}
		}
		if(bitti2)break;
		iterasyon2++;//giren de�i�ken varsa,iterasyon 1 artar
		for(i=1;i<kisitsay;i++)//��kan de�i�ken bulunur
		{
			if(matris[i][indisj]!=0 && (matris[i][degiskensay-1]/matris[i][indisj])<min && (matris[i][degiskensay-1]/matris[i][indisj])>0)
			{
				indisi=i;
				min=matris[i][degiskensay-1]/matris[i][indisj];
			}
		}
		if(kontrol1==1)
		{
			if(!strcmp(giren,kisitlar[indisi].ad))//bir �nceki giren de�i�ken,�imdiki ��kan de�i�kene e�itse ��z�m s�n�rland�r��mam��t�r.
			{
				fprintf(f,"Sinirlandirilmamis cozum.");
				exit(0);
			}
			kontrol1=0;
		}
		if(kontrol1==0)
		{
			strcpy(giren,degiskenler[indisj].ad);
			kontrol1=1;
		}
		anahtareleman=matris[indisi][indisj];
		for(j=0;j<degiskensay;j++)//anahtar sat�r bulunur
		{
			if(degiskenler[j].tipi!=1)
			matris[indisi][j]/=anahtareleman;
		}
		strcpy(kisitlar[indisi].ad,degiskenler[indisj].ad);//k�s�t�n ad�,giren de�i�kenin ad�yla de�i�tirilir
		for(i=0;i<kisitsay;i++)//t�m matriste sat�r i�lemleri ger�ekle�tirilir
		{
			anahtareleman=matris[i][indisj];
			if(anahtareleman==0 || i==indisi)continue;//sat�r�n anahtar eleman� 0 ise ya da anahtar sat�ra denk gelindiyse,o i�lem ge�ilir
			for(j=0;j<degiskensay;j++)
			{
				if(degiskenler[j].tipi!=1)
				matris[i][j]-=(anahtareleman*matris[indisi][j]);
			}
		}
	}while(1);
	t=clock()-t;
	int istenen;
	printf("Toplam iterasyon sayisi:%d\n",iterasyon1+iterasyon2);
	printf("Tablosunu gormek istediginiz iterasyonun numarasini giriniz(istemiyorum=-1):");
	scanf("%d",&istenen);
	if(istenen>0 && istenen<=iterasyon1+iterasyon2)//�stenilen tablonun yazd�r�lmas� i�in,simpleks tekrardan uygulan�yor
	{
		totalyapay=0;
		for(i=0;i<degiskensay;i++)
		{
			if(degiskenler1[i].tipi==1)totalyapay++;
		}
		bul=0;
		iterasyon11=0;
		iterasyon22=0;
		kontrol1=0;
		for(i=0;i<kisitsay;i++)//elimizde tutulan t�m de�erleri bir matrisin i�ine at�yoruz,kullan�m kolayl��� i�in
		{
			for(j=0;j<degiskensay-1;j++)
			{
				for(k=0;k<kisitsay;k++)
				{
					if(!strcmp(kisitlar1[i].ad,degiskenler1[j].kisitad[k]))
					{
						matris1[i][j]=degiskenler1[j].kisitdeger[k];
					}	
				}
			}
			matris1[i][degiskensay-1]=kisitlar1[i].sts;
		}
		for(i=0;i<degiskensay-1;i++)//kisit adlar� yerine hangi de�i�ken adlar� konulaca��n� buluyor
		{
			toplam1=toplam2=0;
			for(j=0;j<kisitsay;j++)
			{
				if(degiskenler1[i].kisitdeger[j]==1 && strcmp(degiskenler1[i].kisitad[j],fonk.ad)!=0)//de�i�kenin k�s�ttaki kat say�s� 1 ise
				{
					toplam1++;
				}
				else if(degiskenler1[i].kisitdeger[j]!=0 && strcmp(degiskenler1[i].kisitad[j],fonk.ad)!=0)//1 de�il ve 0dan farkl� ise
				{
					toplam2++;
				}
			}
			if(toplam1==1 && toplam2==0)//de�i�kenin t�m k�s�tlar i�inde tek bir de�eri varsa ve o da 1 ise,birim matriste yer al�r
			{
				for(k=0;k<kisitsay;k++)
				{
					if(!strcmp(kisitlar1[k].ad,degiskenler1[i].kisitad[0]) && degiskenler1[i].tipi!=0)//0 olmas�n�n sebebi,yeni eklenen de�i�kenin ilk k�s�t� birim matriste yer ald��� k�s�t olur(her zaman)
					{
						strcpy(kisitlar1[k].ad,degiskenler1[i].ad);//k�s�t�n ad� bulunur ve de�i�kenin ad� ile de�i�tirilir
					}
				}
			}
		}
		if(totalyapay>0)
		{
							//1. a�ama
			float adim1[degiskensay];
			for(i=0;i<degiskensay-1;i++)//r sat�r� i�in adim1 isimli dizi a��ld�
			{
				if(degiskenler1[i].tipi==1)//Yapay de�i�ken ise r sat�r� -1 yap�l�r
				{
					adim1[i]=-1;
				}
				else adim1[i]=0;
			}
			adim1[degiskensay-1]=0;//Sts s�tunu
			for(i=0;i<kisitsay;i++)
			{
				for(j=0;j<degiskensay-1;j++)
				{
					if(!strcmp(kisitlar1[i].ad,degiskenler1[j].ad) && degiskenler1[j].tipi==1)//degiskenin ad�,k�s�t�n ad� ile ayn�ysa ve  degiskenin tipi yapay ise
					{
						for(k=0;k<degiskensay;k++)
						{
							adim1[k]+=matris1[i][k];//r sat�r�n� tutarl� hale getirme i�lemi
						}
					}
				}
			}
			do
			{
				min=FLT_MAX;
				bitti1=true;
				bul=0;
				for(i=0;i<degiskensay-1;i++)//giren de�i�ken bulunur
				{
					if(adim1[i]>bul)//ama� fonk min ise pozitifler i�inden en b�y��� bulur
					{
						indisj=i;
						bul=adim1[i];
						bitti1=false;
					}
				}
				if(bitti1)break;
				iterasyon11++;//giren de�i�ken varsa,iterasyon 1 artar
				for(i=1;i<kisitsay;i++)//��kan de�i�ken bulunur
				{
					if(matris1[i][indisj]!=0 && (matris1[i][degiskensay-1]/matris1[i][indisj])<min && (matris1[i][degiskensay-1]/matris1[i][indisj])>0)
					{
						indisi=i;
						min=matris1[i][degiskensay-1]/matris1[i][indisj];
					}
				}
				anahtareleman=matris1[indisi][indisj];
				for(j=0;j<degiskensay;j++)//anahtar sat�r bulunur
				{
					matris1[indisi][j]/=anahtareleman;
				}
				anahtareleman=adim1[indisj];
				for(j=0;j<degiskensay;j++)//r sat�r� bulunur
				{
					adim1[j]-=(anahtareleman*matris1[indisi][j]);
				}
				strcpy(kisitlar1[indisi].ad,degiskenler1[indisj].ad);//k�s�t�n ad�,giren de�i�kenin ad�yla de�i�tirilir
				for(i=1;i<kisitsay;i++)//t�m matriste sat�r i�lemleri ger�ekle�tirilir
				{
					anahtareleman=matris1[i][indisj];
					if(anahtareleman==0 || i==indisi)continue;//sat�r�n anahtar eleman� 0 ise ya da anahtar sat�ra denk gelindiyse,o i�lem ge�ilir
					for(j=0;j<degiskensay;j++)
					{
						matris1[i][j]-=(anahtareleman*matris1[indisi][j]);
					}
				}
					if(istenen==iterasyon11)
					{
						fprintf(f,"%d.�terasyon\n",iterasyon11);
						for(i=0;i<degiskensay-1;i++)fprintf(f,"%10s",degiskenler1[i].ad);
						fprintf(f,"%10s\n","STS");
						for(i=1;i<kisitsay;i++)
						{
							fprintf(f,"%s\t",kisitlar1[i].ad);
							for(j=0;j<degiskensay;j++)
							{
								fprintf(f,"%-10.2f",matris1[i][j]);
							}
							fprintf(f,"\n");
						}
						fprintf(f,"%-4s\t","r");
						for(j=0;j<degiskensay;j++)//r sat�r� bulunur
						{
							fprintf(f,"%-10.2f",adim1[j]);
						}
						fprintf(f,"\n\n");
						break;
					}
			}while(1);
		}
		//2.a�ama
		if(istenen!=iterasyon11)
		{
			for(j=0;j<degiskensay;j++)//Ama� fonksiyonu sat�r� - ile �arp�l�r.(sa� taraf sabit b�rak�l�r)
			if(matris1[0][j]!=0)
			matris1[0][j]*=-1;
			tutarlimi=false;
			for(i=1;i<kisitsay;i++)
			{
				for(j=0;j<degiskensay-1;j++)
				{
					if(!strcmp(kisitlar1[i].ad,degiskenler1[j].ad) && degiskenler1[j].tipi==0 && degiskenler1[j].kisitdeger[0]!=0)//Z sat�r� tutarl� m� diye kontrol edilir
					{
						for(k=0;k<degiskensay;k++)
						{
							if(degiskenler1[k].tipi!=1)//yapay de�i�ken de�ilse i�lem yap�l�r
							{
								tutarlimi=true;
								matris1[0][k]+=(matris1[i][k]*degiskenler1[j].kisitdeger[0]);
							}
						}
					}
				}
			}
			if(tutarlimi)
			{
				iterasyon22++;//Z sat�r� tutarl� hale getirildiyse,iterasyon 1 artar
				if(istenen==iterasyon11+iterasyon22)
				{
					fprintf(f,"%d.�terasyon\n",iterasyon11+iterasyon22);
					for(i=0;i<degiskensay-1;i++)
					{
						if(degiskenler1[i].tipi!=1)
						fprintf(f,"%10s",degiskenler1[i].ad);
					}
					fprintf(f,"%10s\n","STS");
					for(i=0;i<kisitsay;i++)
					{
						fprintf(f,"%s\t",kisitlar1[i].ad);
						for(j=0;j<degiskensay;j++)
						{
							if(degiskenler1[j].tipi!=1)
							fprintf(f,"%-10.2f",matris1[i][j]);
						}
						fprintf(f,"\n");
					}
					fprintf(f,"\n");
				}
			}
			if(istenen!=iterasyon11+iterasyon22)
			do
			{
				min=FLT_MAX;
				bitti2=true;
				bul=0;
				for(j=0;j<degiskensay-1;j++)//giren de�i�ken bulunur
				{
					if(!strcmp(fonk.tip,"MIN") && matris1[0][j]>bul && degiskenler1[j].tipi!=1)//ama� fonk min ise pozitifler i�inden en b�y��� bulur
					{
						indisj=j;
						bul=matris1[0][j];
						bitti2=false;
					}
					else if(!strcmp(fonk.tip,"MAX") && fabs(matris1[0][j])>bul && matris1[0][j]<0 && degiskenler1[j].tipi!=1)//ama� fonk max ise negatifler i�inden en b�y��� bulur
					{
						indisj=j;
						bul=fabs(matris1[0][j]);
						bitti2=false;
					}
				}
				if(bitti2)break;
				iterasyon22++;//giren de�i�ken varsa,iterasyon 1 artar
				for(i=1;i<kisitsay;i++)//��kan de�i�ken bulunur
				{
					if(matris1[i][indisj]!=0 && (matris1[i][degiskensay-1]/matris1[i][indisj])<min && (matris1[i][degiskensay-1]/matris1[i][indisj])>0)
					{
						indisi=i;
						min=matris1[i][degiskensay-1]/matris1[i][indisj];
					}
				}
				anahtareleman=matris1[indisi][indisj];
				for(j=0;j<degiskensay;j++)//anahtar sat�r bulunur
				{
					if(degiskenler1[j].tipi!=1)
					matris1[indisi][j]/=anahtareleman;
				}
				strcpy(kisitlar1[indisi].ad,degiskenler1[indisj].ad);//k�s�t�n ad�,giren de�i�kenin ad�yla de�i�tirilir
				for(i=0;i<kisitsay;i++)//t�m matriste sat�r i�lemleri ger�ekle�tirilir
				{
					anahtareleman=matris1[i][indisj];
					if(anahtareleman==0 || i==indisi)continue;//sat�r�n anahtar eleman� 0 ise ya da anahtar sat�ra denk gelindiyse,o i�lem ge�ilir
					for(j=0;j<degiskensay;j++)
					{
						if(degiskenler1[j].tipi!=1)
						matris1[i][j]-=(anahtareleman*matris1[indisi][j]);
					}
				}
					if(istenen==iterasyon11+iterasyon22)
					{
						fprintf(f,"%d.�terasyon\n",iterasyon11+iterasyon22);
						for(i=0;i<degiskensay-1;i++)
						{
							if(degiskenler1[i].tipi!=1)
							fprintf(f,"%10s",degiskenler1[i].ad);
						}
						fprintf(f,"%10s\n","STS");
						for(i=0;i<kisitsay;i++)
						{
							fprintf(f,"%s\t",kisitlar1[i].ad);
							for(j=0;j<degiskensay;j++)
							{
								if(degiskenler1[j].tipi!=1)
								fprintf(f,"%-10.2f",matris1[i][j]);
							}
							fprintf(f,"\n");
						}
						fprintf(f,"\n");
						break;
					}
			}while(1);
		}
	}
	fprintf(f,"Sonu�:\n");
	for(i=0;i<kisitsay;i++)
	{
		for(j=0;j<degiskensay-1;j++)
		{
			if(!strcmp(kisitlar[i].ad,degiskenler[j].ad) && degiskenler[j].tipi==0)
				fprintf(f,"%s = %.2f\n",kisitlar[i].ad,matris[i][degiskensay-1]);
		}
	}
	fprintf(f,"%s = %.2f\n\n",fonk.ad,matris[0][degiskensay-1]);
	son:fprintf(f,"Calisma Suresi:%.3f sn",(float)t/CLOCKS_PER_SEC);
	fprintf(f,"\n�terasyon Sayisi:%d",iterasyon1+iterasyon2);
	exit(0);
}
