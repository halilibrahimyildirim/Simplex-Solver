#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<conio.h>
#include<float.h>
#include<math.h>
#include<time.h>
//05/2017
typedef struct amac{//amaç fonksiyonu adý ve tipini içeren yapý
	char ad[10];
	char tip[3];
}amac;
typedef struct kisit{//kýsýtlarýn adýný,tipini(L,G,N) ve sað taraf sabitini içeren yapý
	char tip[3];
	char ad[10];
	float sts;
	bool standart;
}kisit;
typedef struct degisken{//deðiþken adýný,bulunduðu kýsýtlarý ve katsayýlarýný,varsa alt-ust sýnýrlarýný ve free olup olmadýðýný içeren yapý
	char ad[10];
	char **kisitad;
	float *kisitdeger;
	float altsinir,ustsinir;
	bool free;//gereksiz bir deðiþken olabilir
	int tipi;//0=normal,1=yapay,2=artýk
	int kackisitivar;
}degisken;
char* fonks()//Artýk ve dolgu deðiþken isimlendirmesi
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
char* fonkr()//Yapay deðiþken isimlendirmesi
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
char* fonkkisit()//Kýsýt isimlendirmesi
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
int adara(degisken degiskenler[],int degiskensay,char m[])//gelen m stringini þuana kadar ki tüm deðiþkenler içinde arar bulursa 1 bulamazsa 0 döndürür
{
	int i;
	for(i=0;i<degiskensay;i++)
	{
		if(!strcmp(degiskenler[i].ad,m))return 1;
	}
	return 0;
}
int kisitadara(kisit kisitlar[],int kisitsay,char m[])//gelen m stringini þuana kadar ki tüm kýsýtlar içinde arar bulursa 1 bulamazsa 0 döndürür
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
	amac fonk;//aþaðýda deðiþikliðe gittiðim için kullanmadýðým deðiþken.
	FILE *f=fopen("Deneme.mps","r");
	fscanf(f,"%s",m);//NAME okunur
	fscanf(f,"%s",m);//Programýn adý alýnýr
	strcpy(programadi,m);
	fscanf(f,"%s",m);//OBJSENSE okundu
	int kisitsay=2,kisitindis=0;
	kisit *kisitlar=(kisit*)calloc(kisitsay,sizeof(kisit));//1 kýsýt için yer açýldý
	int degiskensay=1,degiskenindis=0;
	degisken *degiskenler=(degisken *)calloc(degiskensay,sizeof(degisken));//1 deðiþken için yer açýldý
	t=clock();
	while(!feof(f))//Dosya okuma
	{
		fscanf(f,"%s",m);//Amaç fonksiyonunun MIN ya da MAX olduðu okundu
		while(strcmp("ROWS",m)!=0)//dosyadan okunan kelime ROWS olmadýðý sürece çalýþýr
		{
			strcpy(fonk.tip,m);//Amaç fonksiyonunun tipine MIN ya da MAX olduðunu yazar
			fscanf(f,"%s",m);//ROWS okunur
		}
		fscanf(f,"%s",m);//ROWS içindeki ilk kelimeyi(boþluða kadar olan kýsmý okur)
		while(strcmp("COLUMNS",m)!=0)//dosyadan okunan kelime COLUMNS olmadýðý sürece çalýþýr
		{
			if(!strcmp(m,"G") || !strcmp(m,"L") || !strcmp(m,"E") || !strcmp(m,"N"))//tipi G ya da L ya da E ise çalýþýr(büyükeþit,küçükeþit,eþit)
			{
				strcpy(kisitlar[kisitindis].tip,m);//Kýsýtlarýn son ve boþ olan indisteki(boþ eleman) kýsmýna tipini yazdýrýr
				fscanf(f,"%s",m);
				strcpy(kisitlar[kisitindis].ad,m);//Son ve boþ olan indise adýný yazdýrýr
				if(!strcmp(kisitlar[kisitindis].tip,"N"))//amaç fonksiyonu ise,fonksiyonun adýna da yazar,ileride kontrol etmek gerekirse diye
				{
					strcpy(fonk.ad,m);
					kisitlar[kisitindis].sts=0;
				}
				kisitlar[kisitindis].standart=false;
				kisitindis++;
				if(kisitindis==kisitsay)//yeni indis,totalde elimizdeki kýsýt sayýsýna eþit ise,dizi dolmuþtur yeni gelecek kýsýt için yer açýlýr
				{
					kisitsay++;//kýsýt sayýsý 1 artar
					kisitlar=(kisit*)realloc(kisitlar,sizeof(kisit)*kisitsay);//yeni boþluk açýlýr
				}
				fscanf(f,"%s",m);
			}
		}
		degiskenler[degiskenindis].kisitad=(char**)calloc(kisitsay,sizeof(char*));//baþlangýçta 1 deðiþken olduðu farzedilir,1. deðiþkenin kýsýtlarýnýn adý için yer açýlýyor
		degiskenler[degiskenindis].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//1. deðiþkenin kýsýtlarda sahip olduðu kat sayýlar için yer açýlýyor
		for(i=0;i<kisitsay;i++)
		{
			degiskenler[degiskenindis].kisitad[i]=(char*)calloc(10,sizeof(char));//kýsýt adlarýnýn alýnabilmesi için yer açýlýyor
		}
		degiskenler[degiskenindis].kackisitivar=0;
		kisitindis=0;
		int adkontrol=0;
		char yedekad[10];
		while(strcmp("RHS",m)!=0)//dosyadan okunan kelime RHS olmadýðý sürece çalýþýr
		{
			if(adkontrol==0)//ayný deðiþken için birden fazla satýr yazýlabiliyor(COLUMNS içinde) ayný deðiþkenin adýný bir kez daha okumasýn diye
			{
				fscanf(f,"%s",m);
				exception:strcpy(degiskenler[degiskenindis].ad,m);//degiskenin adýný(dosyadan gelen),deðiþkenin içine yazdýrýr.
				adkontrol=1;
				strcpy(yedekad,m);//ayný deðiþkenin adý okunduðunda atlayabilmek için konuldu
				if(!strcmp("RHS",m))break;//"RHS" okunduðunda kod burada oluyor ve sonsuz döngüye giriyordu engellemek için konuldu
			}
			fscanf(f,"%s",m);//bir kelime daha okunuyor
			if(strcmp(yedekad,m)==0)fscanf(f,"%s",m);//þayet okunan kelime þuan içini doldurduðumuz deðiþkenin adý ile ayný ise bir kelime daha okur
			if(kisitadara(kisitlar,kisitsay,m) || !strcmp(m,fonk.ad))//okuduðumuz kelime kýsýt adýysa ya da amaç fonksiyonun adýysa çalýþýr
			{
				strcpy(degiskenler[degiskenindis].kisitad[kisitindis],m);//o an ki deðiþkenin içine kýsýtýn adýný yazdýrýr
			}
			else//Buraya girdiðinde yeni bir deðiþken adýný okumuþ oluyor
			{
				kisitindis=0;
				degiskenler[degiskenindis].tipi=1;
				degiskenindis++;
				degiskensay++;
				degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni deðiþken için boyutlandýrýlýyor
				degiskenler[degiskenindis].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni deðiþkenin kýsýtlarýnýn adlarý için yer açýlýyor
				degiskenler[degiskenindis].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni deðiþkenin kýsýtlardaki katsayýlarý için yer açýlýyor
				for(i=0;i<kisitsay;i++)
				{
					degiskenler[degiskenindis].kisitad[i]=(char*)calloc(10,sizeof(char));//kýsýt adlarý için yer açýldý
				}
				degiskenler[degiskenindis].kackisitivar=0;
				goto exception;//goto kullanýmýný önlemek için,continue + if(yeni bir deðiþken) kullansak ayný duruma denk gelirdi.151.satýra döner
			}
			fscanf(f,"%s",m);
			sscanf(m,"%f",&degiskenler[degiskenindis].kisitdeger[kisitindis]);//deðiþkenin bulunduðu kýsýttaki katsayýsý okunmuþtur,içine yazýlýr
			degiskenler[degiskenindis].kackisitivar++;
			kisitindis++;
		}
		while(strcmp("BOUNDS",m)!=0)//dosyadan okunan kelime BOUNDS olmadýðý sürece çalýþýr
		{
			fscanf(f,"%s",m);
			if(!strcmp("ENDATA",m))break;
			if(kisitadara(kisitlar,kisitsay,m))//Okuduðu þey kýsýt adýysa bura çalýþýr(RHS1 Kýsmýný önlemek için)
			{
				for(i=0;i<kisitsay-1;i++)//Tüm kýsýtlarý gezer
				{
					if(!strcmp(kisitlar[i].ad,m))//kýsýt adýyla dosyadan okuduðumuz kelime ayný denk geldiðinde yeni bir kelime okur
					{
						fscanf(f,"%s",m);
						sscanf(m,"%f",&kisitlar[i].sts);//okuduðu kelime kýsýtýn sað taraf sabitidir,kýsýtýn içine yazdýrýlýr
						break;
					}
				}
			}
		}
		for(i=0;i<degiskensay-1;i++)//tüm degiþkenlerin alt ve üst sýnýrý baþta 0 yapýlýr
		{
			degiskenler[i].ustsinir=0;
			degiskenler[i].altsinir=0;
		}
		if(!strcmp("ENDATA",m))break;
		while(strcmp("ENDATA",m)!=0)//Dosyanýn sonuna kadar okumak için || alýnan kelime ENDATA olana kadar çalýþýr.
		{
			char yedek[10];
			fscanf(f,"%s",m);//Deðiþkenin sýnýrýnýn tipini okur(LO,UP,FR)
			strcpy(yedek,m);//deðiþkenin sýnýrýný yedek deðiþkene atar
			fscanf(f,"%s",m);//Fazladan okuma BND1 kýsmýný atlamak için
			fscanf(f,"%s",m);//deðiþkenin adýný alýr
			for(i=0;i<degiskensay-1;i++)//tüm deðiþkenleri gezer
			{
				if(!strcmp(degiskenler[i].ad,m))//deðiþkenin adý dosyadan okuduðumuz kelime ile ayný denk geldiðinde çalýþýr
				{
					if(!strcmp(yedek,"FR"))//deðiþken FREE ise çalýþýr
					{
						degiskenler[i].free=true;//gereksiz bir satýr olabilir,deðiþkenin free olduðunu belirtiyor
						//FREE bir deðiþken ile karþýlaþtýðýmýzda xi=(xi^+)-(xi^-) þekline çevirdiðimiz için 1 deðiþken daha eklenir
						//Yeni açýlan deðiþken (xi^-) olacaktýr çünkü zaten (xi^+) free olan deðiþken ile ayný özelliklere sahiptir
						degiskensay++;
						//aþaðýda deðiþken için yer açýlma iþlemleri yapýlýr
						degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);
						degiskenler[degiskenindis].kisitad=(char**)calloc(kisitsay,sizeof(char*));
						degiskenler[degiskenindis].kisitdeger=(float*)calloc(kisitsay,sizeof(float));
						for(j=0;j<kisitsay;j++)
						{
							degiskenler[degiskenindis].kisitad[j]=(char*)calloc(10,sizeof(char));
							strcpy(degiskenler[degiskenindis].kisitad[j],degiskenler[i].kisitad[j]);//yeni açýlan deðiþkenin kýsýtlarý,free olan ile ayný olacaðý için aynýsý içine yazdýrýlýr
							if(degiskenler[i].kisitdeger[j]!=0)
							degiskenler[degiskenindis].kisitdeger[j]=degiskenler[i].kisitdeger[j]*-1;//yeni deðiþken free olanýn ters iþaretlisidir -1 ile çarpýlýr
							else degiskenler[degiskenindis].kisitdeger[j]=0;
						}
						strcpy(degiskenler[degiskenindis].ad,degiskenler[i].ad);//yeni deðiþkenin adýný free deðiþkenin adýyla ayný yapar
						degiskenler[degiskenindis].kackisitivar=degiskenler[i].kackisitivar;
						strcat(degiskenler[degiskenindis].ad,"-");//sonuna "-" ekler xi^- gibi gösterim için
						degiskenler[degiskenindis].ustsinir=0;
						degiskenler[degiskenindis].altsinir=0;
						degiskenler[i].free=false;//free deðiþkenin artýk free olmadýðýný gösterir,gereksiz bir atama olabilir
						strcat(degiskenler[i].ad,"+");//free deðiþken artýk xi^+ deðiþkeni olmuþtur.adýnýn sonuna "+" konur
						degiskenler[degiskenindis].tipi=1;
						degiskenindis++;
					}
					if(!strcmp(yedek,"UP"))//deðiþkenin üst sýnýrý giriliyorsa çalýþýr
					{
						fscanf(f,"%s",m);//Deðiþkenin sýnýr deðerini okur.
						sscanf(m,"%f",&degiskenler[i].ustsinir);//deðiþkenin üst sýnýrýna atar
						
						degiskenler[i].free=false;//üst sýnýrý varsa free olamaz.gereksiz bir atama olabilir
					}
					if(!strcmp(yedek,"LO"))
					{
						fscanf(f,"%s",m);//Deðiþkenin sýnýr deðerini okur.
						sscanf(m,"%f",&degiskenler[i].altsinir);//deðiþkenin alt sýnýrýna atar
						degiskenler[i].free=false;//alt sýnýrý varsa free olamaz.gereksiz bir atama olabilir
					}
				}
			}
		}
	}
	fclose(f);
	int negatiflik=-1;
	f=fopen("Sonuc.txt","w");
	fprintf(f,"%s\n\n",programadi);
	kisitsay--;//kisitsay fazladan arttýrýlmýþtý,aþaðýda kisitsay-2 ile çalýþmak yerine burada 1 azaltýlýyor.
	for(i=0;i<degiskensay-1;i++)//Bounds kýsmý için kýsýt oluþturuluyor
	{
		if(degiskenler[i].altsinir<0)//deðiþkenin alt sýnýrý negatif ise,sýfýra öteleme yapýlýr
		{
			for(j=0;j<kisitsay;j++)
			{
				for(k=0;k<degiskenler[i].kackisitivar;k++)
				{
					if(!strcmp(kisitlar[j].ad,degiskenler[i].kisitad[k]))
					{
						kisitlar[j].sts+=(degiskenler[i].kisitdeger[k]*degiskenler[i].altsinir*-1);//deðiþkenin bulunduðu tüm kýsýtlarýn sað taraf sabitlerine deðiþkenin alt sýnýrýnýn ters iþaretlisi eklenir
					}
				}
			}
			negatiflik=i;
		}
		if(degiskenler[i].altsinir>0)//degiskenin alt sýnýrý varsa
		{
			kisitsay++;
			kisitlar=(kisit*)realloc(kisitlar,sizeof(kisit)*kisitsay);
			strcpy(kisitlar[kisitsay-1].tip,"G");//alt sýnýrý varsa kýsýt büyük eþittir
			kisitlar[kisitsay-1].sts=degiskenler[i].altsinir;//kýsýtýn sað taraf sabiti o alt sýnýra eþittir
			kisitlar[kisitsay-1].standart=false;//yeni kýsýtýn daha standart hale gelmediðini belirtiyor
			strcpy(kisitlar[kisitsay-1].ad,fonkkisit());
			for(k=0;k<degiskensay-1;k++)
			{
				degiskenler[k].kisitad=(char**)realloc(degiskenler[k].kisitad,kisitsay*sizeof(char*));//yeni deðiþkenin kýsýtlarýnýn adlarý için yer açýlýyor
				degiskenler[k].kisitdeger=(float*)realloc(degiskenler[k].kisitdeger,kisitsay*sizeof(float));//yeni deðiþkenin kýsýtlardaki katsayýlarý için yer açýlýyor
				degiskenler[k].kisitad[kisitsay-1]=(char*)malloc(10*sizeof(char));//kýsýt adlarý için yer açýldý
			}
			strcpy(degiskenler[i].kisitad[degiskenler[i].kackisitivar],kisitlar[kisitsay-1].ad);//degiskenin o kýsýtta bulunduðunu gösterir
			degiskenler[i].kisitdeger[degiskenler[i].kackisitivar]=1.0;//degiskenin o kýsýttaki katsayýsý 1dir
			degiskenler[i].kackisitivar++;
		}
		if(degiskenler[i].ustsinir!=0)
		{
			kisitsay++;
			kisitlar=(kisit*)realloc(kisitlar,sizeof(kisit)*kisitsay);
			strcpy(kisitlar[kisitsay-1].tip,"L");//degiþkenin üst sýnýrý varsa,kýsýt küçük eþittir.
			kisitlar[kisitsay-1].sts=degiskenler[i].ustsinir;//degiþkenin üst sýnýrý o kýsýtýn sað taraf sabitine eþittir
			kisitlar[kisitsay-1].standart=false;//yeni kýsýtýn daha standart hale gelmediðini belirtiyor
			strcpy(kisitlar[kisitsay-1].ad,fonkkisit());
			for(k=0;k<degiskensay-1;k++)
			{
				degiskenler[k].kisitad=(char**)realloc(degiskenler[k].kisitad,kisitsay*sizeof(char*));//yeni deðiþkenin kýsýtlarýnýn adlarý için yer açýlýyor
				degiskenler[k].kisitdeger=(float*)realloc(degiskenler[k].kisitdeger,kisitsay*sizeof(float));//yeni deðiþkenin kýsýtlardaki katsayýlarý için yer açýlýyor
				degiskenler[k].kisitad[kisitsay-1]=(char*)malloc(10*sizeof(char));//kýsýt adlarý için yer açýldý	
			}
			strcpy(degiskenler[i].kisitad[degiskenler[i].kackisitivar],kisitlar[kisitsay-1].ad);//degiskenin o kýsýtta yer aldýðý belirtilir
			degiskenler[i].kisitdeger[degiskenler[i].kackisitivar]=1.0;//kat sayýsý 1 dir.
			degiskenler[i].kackisitivar++;
			if(i==negatiflik)//deðiþkenin üst sýnýrý da varsa,o kýsýta da ekleme yapýlýr
			{
				kisitlar[kisitsay-1].sts+=(degiskenler[i].altsinir*-1);
			}
		}
	}
	int kontrolsay,kontrol=0;
	for(i=0;i<kisitsay;i++)//Negatif sað taraf sabitleri kontrol ediliyor
	{
		for(j=0;j<degiskensay-1;j++)
		{
			for(k=0;k<kisitsay;k++)
			{
				if(kisitlar[i].sts<0)//kýsýtýn sað taraf sabiti negatif ise o kýsýttaki tüm deðiþkenlerin katsayýlarý - ile çarpýlýr
				{
					if(!strcmp(degiskenler[j].kisitad[k],kisitlar[i].ad))
					{
						kontrol=1;
						if(degiskenler[j].kisitdeger[k]!=0)
						degiskenler[j].kisitdeger[k]*=-1.0;
					}
				}
			}
			if(kontrol==1)//bu ife giriyorsa kýsýtýn sað taraf sabiti negatif demektir
			{
				kisitlar[i].sts*=-1;//kýsýtýn sað taraf sabiti - ile çarpýlýr
				if(!strcmp(kisitlar[i].tip,"L"))strcpy(kisitlar[i].tip,"G");//eþitsizlik yön deðiþtirir
				if(!strcmp(kisitlar[i].tip,"G"))strcpy(kisitlar[i].tip,"L");//eþitsizlik yön deðiþtirir
				kontrol=0;
			}
		}
	}
	for(i=0;i<degiskensay-1;i++)//Elimizde þu anda bulunan tüm deðiþkenler,denklemin kendi deðiþkenleri olduðu için tipleri 0 yapýldý.
	{
		degiskenler[i].tipi=0;
	}
	for(i=0;i<kisitsay;i++)//Standart hale getirilmesi için gerekli deðiþkenler ekleniyor
	{
		if(!strcmp(kisitlar[i].tip,"L") && kisitlar[i].standart==false)//Küçük eþit durumu için yeni deðiþken ekleniyor
		{
			degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni deðiþken için boyutlandýrýlýyor
			degiskenler[degiskensay-1].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni deðiþkenin kýsýtlarýnýn adlarý için yer açýlýyor
			degiskenler[degiskensay-1].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni deðiþkenin kýsýtlardaki katsayýlarý için yer açýlýyor
			for(j=0;j<kisitsay;j++)
			{
				degiskenler[degiskensay-1].kisitad[j]=(char*)calloc(10,sizeof(char));//kýsýt adlarý için yer açýldý
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
		if(!strcmp(kisitlar[i].tip,"G") && kisitlar[i].standart==false)//Büyük eþit durumu için yeni deðiþken ekleniyor
		{
			degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni deðiþken için boyutlandýrýlýyor
			degiskenler[degiskensay-1].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni deðiþkenin kýsýtlarýnýn adlarý için yer açýlýyor
			degiskenler[degiskensay-1].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni deðiþkenin kýsýtlardaki katsayýlarý için yer açýlýyor
			for(j=0;j<kisitsay;j++)
			{
				degiskenler[degiskensay-1].kisitad[j]=(char*)calloc(10,sizeof(char));//kýsýt adlarý için yer açýldý
			}
			degiskenler[degiskensay-1].kackisitivar=0;
			strcpy(degiskenler[degiskensay-1].ad,fonks());
			strcpy(degiskenler[degiskensay-1].kisitad[degiskenler[degiskensay-1].kackisitivar],kisitlar[i].ad);
			degiskenler[degiskensay-1].kisitdeger[degiskenler[degiskensay-1].kackisitivar]=-1.0;
			degiskenler[degiskensay-1].kackisitivar++;
			degiskenler[degiskensay-1].tipi=2;
			degiskensay++;
			//Aþaðýdaki kýsým yapay deðiþken
			degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni deðiþken için boyutlandýrýlýyor
			degiskenler[degiskensay-1].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni deðiþkenin kýsýtlarýnýn adlarý için yer açýlýyor
			degiskenler[degiskensay-1].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni deðiþkenin kýsýtlardaki katsayýlarý için yer açýlýyor
			for(j=0;j<kisitsay;j++)
			{
				degiskenler[degiskensay-1].kisitad[j]=(char*)calloc(10,sizeof(char));//kýsýt adlarý için yer açýldý
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
		if(!strcmp(kisitlar[i].tip,"E") && kisitlar[i].standart==false)//Eþittir durumu için deðiþken ekleniyor
		{
			degiskenler=(degisken *)realloc(degiskenler,sizeof(degisken)*degiskensay);//yeni deðiþken için boyutlandýrýlýyor
			degiskenler[degiskensay-1].kisitad=(char**)calloc(kisitsay,sizeof(char*));//yeni deðiþkenin kýsýtlarýnýn adlarý için yer açýlýyor
			degiskenler[degiskensay-1].kisitdeger=(float*)calloc(kisitsay,sizeof(float));//yeni deðiþkenin kýsýtlardaki katsayýlarý için yer açýlýyor
			for(j=0;j<kisitsay;j++)
			{
				degiskenler[degiskensay-1].kisitad[j]=(char*)calloc(10,sizeof(char));//kýsýt adlarý için yer açýldý
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
	//Aþaðýda,deðiþkenlerde eksik olan kýsýt adlarý deðiþkenlere yazýlýyor,çünkü matrisi yazdýrma iþlemi öyle gerçekleþtiriliyor.(kýsýt adýna göre arama ile)
	for(i=0;i<kisitsay;i++)//Her deðiþken için,bulunmadýðý kýsýtlarda aslýnda 0 katsayýsý ile bulunduðu belirtiliyor
	{
		for(j=0;j<degiskensay-1;j++)
		{
			kontrolsay=0;
			for(k=0;k<kisitsay;k++)
			{
				if(!strcmp(kisitlar[i].ad,degiskenler[j].kisitad[k]))//þayet j. deðiþken i. kýsýtta bulunuyorsa
				{	
					kontrolsay=1;
					break;
				}
			}
			if(kontrolsay==0)//þayet j.deðiþken i. kýsýtta bulunmuyorsa,i. kýsýtýn adýný j. deðiþkene de yazar ve deðiþkenin katsayýsýný 0 yapar
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
										//Ýki aþamalý yönteme baþlanýyor
	int totalyapay=0;
	for(i=0;i<degiskensay;i++)//yapay deðiþkenlerin sayýsý bulunur(var olup olmadýðý incelenir)
	{
		if(degiskenler[i].tipi==1)totalyapay++;
	}
	bool bitti1;
	float bul=0,min,anahtareleman;
	char giren[20];
	int indisj,indisi,iterasyon1=0,iterasyon2=0,iterasyon11=0,iterasyon22=0;
	float matris[kisitsay][degiskensay],matris1[kisitsay][degiskensay];
	int toplam1,toplam2,kontrol1=0;
	for(i=0;i<kisitsay;i++)//elimizde tutulan tüm deðerleri bir matrisin içine atýyoruz,kullaným kolaylýðý için
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
	for(i=0;i<degiskensay-1;i++)//kisit adlarý yerine hangi deðiþken adlarý konulacaðýný buluyor
	{
		toplam1=toplam2=0;
		for(j=0;j<kisitsay;j++)
		{
			if(degiskenler[i].kisitdeger[j]==1 && strcmp(degiskenler[i].kisitad[j],fonk.ad)!=0)//deðiþkenin kýsýttaki kat sayýsý 1 ise
			{
				toplam1++;
			}
			else if(degiskenler[i].kisitdeger[j]!=0 && strcmp(degiskenler[i].kisitad[j],fonk.ad)!=0)//1 deðil ve 0dan farklý ise
			{
				toplam2++;
			}
		}
		if(toplam1==1 && toplam2==0)//deðiþkenin tüm kýsýtlar içinde tek bir deðeri varsa ve o da 1 ise,birim matriste yer alýr
		{
			for(k=0;k<kisitsay;k++)
			{
				if(!strcmp(kisitlar[k].ad,degiskenler[i].kisitad[0]) && degiskenler[i].tipi!=0)//0 olmasýnýn sebebi,yeni eklenen deðiþkenin ilk kýsýtý birim matriste yer aldýðý kýsýt olur(her zaman)
				{
					strcpy(kisitlar[k].ad,degiskenler[i].ad);//kýsýtýn adý bulunur ve deðiþkenin adý ile deðiþtirilir
				}
			}
		}
	}
	if(totalyapay>0)
	{
						//1. aþama
		float adim1[degiskensay];
		for(i=0;i<degiskensay-1;i++)//r satýrý için adim1 isimli dizi açýldý
		{
			if(degiskenler[i].tipi==1)//Yapay deðiþken ise r satýrý -1 yapýlýr
			{
				adim1[i]=-1;
			}
			else adim1[i]=0;
		}
		adim1[degiskensay-1]=0;//Sts sütunu
		for(i=0;i<kisitsay;i++)
		{
			for(j=0;j<degiskensay-1;j++)
			{
				if(!strcmp(kisitlar[i].ad,degiskenler[j].ad) && degiskenler[j].tipi==1)//degiskenin adý,kýsýtýn adý ile aynýysa ve  degiskenin tipi yapay ise
				{
					for(k=0;k<degiskensay;k++)
					{
						adim1[k]+=matris[i][k];//r satýrýný tutarlý hale getirme iþlemi
					}
				}
			}
		}
		do
		{
			min=FLT_MAX;
			bitti1=true;
			bul=0;
			for(i=0;i<degiskensay-1;i++)//giren deðiþken bulunur
			{
				if(adim1[i]>bul)//amaç fonk min ise pozitifler içinden en büyüðü bulur
				{
					indisj=i;
					bul=adim1[i];
					bitti1=false;
				}
			}
			if(bitti1)break;
			iterasyon1++;//giren deðiþken varsa,iterasyon 1 artar
			for(i=1;i<kisitsay;i++)//çýkan deðiþken bulunur
			{
				if(matris[i][indisj]!=0 && (matris[i][degiskensay-1]/matris[i][indisj])<min && (matris[i][degiskensay-1]/matris[i][indisj])>0)
				{
					indisi=i;
					min=matris[i][degiskensay-1]/matris[i][indisj];
				}
			}
			anahtareleman=matris[indisi][indisj];
			for(j=0;j<degiskensay;j++)//anahtar satýr bulunur
			{
				matris[indisi][j]/=anahtareleman;
			}
			anahtareleman=adim1[indisj];
			for(j=0;j<degiskensay;j++)//r satýrý bulunur
			{
				adim1[j]-=(anahtareleman*matris[indisi][j]);
			}
			strcpy(kisitlar[indisi].ad,degiskenler[indisj].ad);//kýsýtýn adý,giren deðiþkenin adýyla deðiþtirilir
			for(i=1;i<kisitsay;i++)//tüm matriste satýr iþlemleri gerçekleþtirilir
			{
				anahtareleman=matris[i][indisj];
				if(anahtareleman==0 || i==indisi)continue;//satýrýn anahtar elemaný 0 ise ya da anahtar satýra denk gelindiyse,o iþlem geçilir
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
			if(!strcmp(kisitlar[i].ad,degiskenler[j].ad) && degiskenler[j].tipi==1)//ilk aþama bittikten sonra satýrlarda R deðiþkeni duruyorsa çalýþýr
			{
				sonuc=false;
				fprintf(f,"Modelin uygun cozumu yoktur.\n\n");
				goto son;//þu ana kadar geçen süreyi ve yapýlan iterasyon sayýsýný yazdýrmak için kullanýldý
			}
		}
	}
	//2.aþama
	for(j=0;j<degiskensay;j++)//Amaç fonksiyonu satýrý - ile çarpýlýr.
		if(matris[0][j]!=0)
		matris[0][j]*=-1;
	bool bitti2,tutarlimi=false;
	for(i=1;i<kisitsay;i++)
	{
		for(j=0;j<degiskensay-1;j++)
		{
			if(!strcmp(kisitlar[i].ad,degiskenler[j].ad) && degiskenler[j].tipi==0 && degiskenler[j].kisitdeger[0]!=0)//Z satýrý tutarlý mý diye kontrol edilir
			{
				for(k=0;k<degiskensay;k++)
				{
					if(degiskenler[k].tipi!=1)//yapay deðiþken deðilse iþlem yapýlýr
					{
						tutarlimi=true;
						matris[0][k]+=(matris[i][k]*degiskenler[j].kisitdeger[0]);
					}
				}
			}
		}
	}
	if(tutarlimi)
		iterasyon2++;//Z satýrý tutarlý hale getirildiyse,iterasyon 1 artar
	kontrol1=0;
	do
	{
		min=FLT_MAX;
		bitti2=true;
		bul=0;
		for(j=0;j<degiskensay-1;j++)//giren deðiþken bulunur
		{
			if(!strcmp(fonk.tip,"MIN") && matris[0][j]>bul && degiskenler[j].tipi!=1)//amaç fonk min ise pozitifler içinden en büyüðü bulur
			{
				indisj=j;
				bul=matris[0][j];
				bitti2=false;
			}
			else if(!strcmp(fonk.tip,"MAX") && fabs(matris[0][j])>bul && matris[0][j]<0 && degiskenler[j].tipi!=1)//amaç fonk max ise negatifler içinden en büyüðü bulur
			{
				indisj=j;
				bul=fabs(matris[0][j]);
				bitti2=false;
			}
		}
		if(bitti2)break;
		iterasyon2++;//giren deðiþken varsa,iterasyon 1 artar
		for(i=1;i<kisitsay;i++)//çýkan deðiþken bulunur
		{
			if(matris[i][indisj]!=0 && (matris[i][degiskensay-1]/matris[i][indisj])<min && (matris[i][degiskensay-1]/matris[i][indisj])>0)
			{
				indisi=i;
				min=matris[i][degiskensay-1]/matris[i][indisj];
			}
		}
		if(kontrol1==1)
		{
			if(!strcmp(giren,kisitlar[indisi].ad))//bir önceki giren deðiþken,þimdiki çýkan deðiþkene eþitse çözüm sýnýrlandýrýþmamýþtýr.
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
		for(j=0;j<degiskensay;j++)//anahtar satýr bulunur
		{
			if(degiskenler[j].tipi!=1)
			matris[indisi][j]/=anahtareleman;
		}
		strcpy(kisitlar[indisi].ad,degiskenler[indisj].ad);//kýsýtýn adý,giren deðiþkenin adýyla deðiþtirilir
		for(i=0;i<kisitsay;i++)//tüm matriste satýr iþlemleri gerçekleþtirilir
		{
			anahtareleman=matris[i][indisj];
			if(anahtareleman==0 || i==indisi)continue;//satýrýn anahtar elemaný 0 ise ya da anahtar satýra denk gelindiyse,o iþlem geçilir
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
	if(istenen>0 && istenen<=iterasyon1+iterasyon2)//Ýstenilen tablonun yazdýrýlmasý için,simpleks tekrardan uygulanýyor
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
		for(i=0;i<kisitsay;i++)//elimizde tutulan tüm deðerleri bir matrisin içine atýyoruz,kullaným kolaylýðý için
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
		for(i=0;i<degiskensay-1;i++)//kisit adlarý yerine hangi deðiþken adlarý konulacaðýný buluyor
		{
			toplam1=toplam2=0;
			for(j=0;j<kisitsay;j++)
			{
				if(degiskenler1[i].kisitdeger[j]==1 && strcmp(degiskenler1[i].kisitad[j],fonk.ad)!=0)//deðiþkenin kýsýttaki kat sayýsý 1 ise
				{
					toplam1++;
				}
				else if(degiskenler1[i].kisitdeger[j]!=0 && strcmp(degiskenler1[i].kisitad[j],fonk.ad)!=0)//1 deðil ve 0dan farklý ise
				{
					toplam2++;
				}
			}
			if(toplam1==1 && toplam2==0)//deðiþkenin tüm kýsýtlar içinde tek bir deðeri varsa ve o da 1 ise,birim matriste yer alýr
			{
				for(k=0;k<kisitsay;k++)
				{
					if(!strcmp(kisitlar1[k].ad,degiskenler1[i].kisitad[0]) && degiskenler1[i].tipi!=0)//0 olmasýnýn sebebi,yeni eklenen deðiþkenin ilk kýsýtý birim matriste yer aldýðý kýsýt olur(her zaman)
					{
						strcpy(kisitlar1[k].ad,degiskenler1[i].ad);//kýsýtýn adý bulunur ve deðiþkenin adý ile deðiþtirilir
					}
				}
			}
		}
		if(totalyapay>0)
		{
							//1. aþama
			float adim1[degiskensay];
			for(i=0;i<degiskensay-1;i++)//r satýrý için adim1 isimli dizi açýldý
			{
				if(degiskenler1[i].tipi==1)//Yapay deðiþken ise r satýrý -1 yapýlýr
				{
					adim1[i]=-1;
				}
				else adim1[i]=0;
			}
			adim1[degiskensay-1]=0;//Sts sütunu
			for(i=0;i<kisitsay;i++)
			{
				for(j=0;j<degiskensay-1;j++)
				{
					if(!strcmp(kisitlar1[i].ad,degiskenler1[j].ad) && degiskenler1[j].tipi==1)//degiskenin adý,kýsýtýn adý ile aynýysa ve  degiskenin tipi yapay ise
					{
						for(k=0;k<degiskensay;k++)
						{
							adim1[k]+=matris1[i][k];//r satýrýný tutarlý hale getirme iþlemi
						}
					}
				}
			}
			do
			{
				min=FLT_MAX;
				bitti1=true;
				bul=0;
				for(i=0;i<degiskensay-1;i++)//giren deðiþken bulunur
				{
					if(adim1[i]>bul)//amaç fonk min ise pozitifler içinden en büyüðü bulur
					{
						indisj=i;
						bul=adim1[i];
						bitti1=false;
					}
				}
				if(bitti1)break;
				iterasyon11++;//giren deðiþken varsa,iterasyon 1 artar
				for(i=1;i<kisitsay;i++)//çýkan deðiþken bulunur
				{
					if(matris1[i][indisj]!=0 && (matris1[i][degiskensay-1]/matris1[i][indisj])<min && (matris1[i][degiskensay-1]/matris1[i][indisj])>0)
					{
						indisi=i;
						min=matris1[i][degiskensay-1]/matris1[i][indisj];
					}
				}
				anahtareleman=matris1[indisi][indisj];
				for(j=0;j<degiskensay;j++)//anahtar satýr bulunur
				{
					matris1[indisi][j]/=anahtareleman;
				}
				anahtareleman=adim1[indisj];
				for(j=0;j<degiskensay;j++)//r satýrý bulunur
				{
					adim1[j]-=(anahtareleman*matris1[indisi][j]);
				}
				strcpy(kisitlar1[indisi].ad,degiskenler1[indisj].ad);//kýsýtýn adý,giren deðiþkenin adýyla deðiþtirilir
				for(i=1;i<kisitsay;i++)//tüm matriste satýr iþlemleri gerçekleþtirilir
				{
					anahtareleman=matris1[i][indisj];
					if(anahtareleman==0 || i==indisi)continue;//satýrýn anahtar elemaný 0 ise ya da anahtar satýra denk gelindiyse,o iþlem geçilir
					for(j=0;j<degiskensay;j++)
					{
						matris1[i][j]-=(anahtareleman*matris1[indisi][j]);
					}
				}
					if(istenen==iterasyon11)
					{
						fprintf(f,"%d.Ýterasyon\n",iterasyon11);
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
						for(j=0;j<degiskensay;j++)//r satýrý bulunur
						{
							fprintf(f,"%-10.2f",adim1[j]);
						}
						fprintf(f,"\n\n");
						break;
					}
			}while(1);
		}
		//2.aþama
		if(istenen!=iterasyon11)
		{
			for(j=0;j<degiskensay;j++)//Amaç fonksiyonu satýrý - ile çarpýlýr.(sað taraf sabit býrakýlýr)
			if(matris1[0][j]!=0)
			matris1[0][j]*=-1;
			tutarlimi=false;
			for(i=1;i<kisitsay;i++)
			{
				for(j=0;j<degiskensay-1;j++)
				{
					if(!strcmp(kisitlar1[i].ad,degiskenler1[j].ad) && degiskenler1[j].tipi==0 && degiskenler1[j].kisitdeger[0]!=0)//Z satýrý tutarlý mý diye kontrol edilir
					{
						for(k=0;k<degiskensay;k++)
						{
							if(degiskenler1[k].tipi!=1)//yapay deðiþken deðilse iþlem yapýlýr
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
				iterasyon22++;//Z satýrý tutarlý hale getirildiyse,iterasyon 1 artar
				if(istenen==iterasyon11+iterasyon22)
				{
					fprintf(f,"%d.Ýterasyon\n",iterasyon11+iterasyon22);
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
				for(j=0;j<degiskensay-1;j++)//giren deðiþken bulunur
				{
					if(!strcmp(fonk.tip,"MIN") && matris1[0][j]>bul && degiskenler1[j].tipi!=1)//amaç fonk min ise pozitifler içinden en büyüðü bulur
					{
						indisj=j;
						bul=matris1[0][j];
						bitti2=false;
					}
					else if(!strcmp(fonk.tip,"MAX") && fabs(matris1[0][j])>bul && matris1[0][j]<0 && degiskenler1[j].tipi!=1)//amaç fonk max ise negatifler içinden en büyüðü bulur
					{
						indisj=j;
						bul=fabs(matris1[0][j]);
						bitti2=false;
					}
				}
				if(bitti2)break;
				iterasyon22++;//giren deðiþken varsa,iterasyon 1 artar
				for(i=1;i<kisitsay;i++)//çýkan deðiþken bulunur
				{
					if(matris1[i][indisj]!=0 && (matris1[i][degiskensay-1]/matris1[i][indisj])<min && (matris1[i][degiskensay-1]/matris1[i][indisj])>0)
					{
						indisi=i;
						min=matris1[i][degiskensay-1]/matris1[i][indisj];
					}
				}
				anahtareleman=matris1[indisi][indisj];
				for(j=0;j<degiskensay;j++)//anahtar satýr bulunur
				{
					if(degiskenler1[j].tipi!=1)
					matris1[indisi][j]/=anahtareleman;
				}
				strcpy(kisitlar1[indisi].ad,degiskenler1[indisj].ad);//kýsýtýn adý,giren deðiþkenin adýyla deðiþtirilir
				for(i=0;i<kisitsay;i++)//tüm matriste satýr iþlemleri gerçekleþtirilir
				{
					anahtareleman=matris1[i][indisj];
					if(anahtareleman==0 || i==indisi)continue;//satýrýn anahtar elemaný 0 ise ya da anahtar satýra denk gelindiyse,o iþlem geçilir
					for(j=0;j<degiskensay;j++)
					{
						if(degiskenler1[j].tipi!=1)
						matris1[i][j]-=(anahtareleman*matris1[indisi][j]);
					}
				}
					if(istenen==iterasyon11+iterasyon22)
					{
						fprintf(f,"%d.Ýterasyon\n",iterasyon11+iterasyon22);
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
	fprintf(f,"Sonuç:\n");
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
	fprintf(f,"\nÝterasyon Sayisi:%d",iterasyon1+iterasyon2);
	exit(0);
}
