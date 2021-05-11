#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h> 
#include <unistd.h>
#include <limits.h>
#include <string.h>
bool isNumber(char ch){
	
	 if (ch == '0' || ch == '1' || ch == '2' || ch == '3'
		|| ch == '4'  || ch == '5'|| ch == '6'|| ch == '7'|| ch == '8'|| ch == '9' )
        return (true); 
    return (false); 
	
}

int checkKeyword(char buffer[]){
    char keywords[12][12] = {"make","MAKE","Make","if","IF","If","go","GO","Go","ifnot","IFNOT","Ifnot"};
    int i, flag = 0;
    for(i = 0; i < 12; ++i){
        if(strcmp(keywords[i], buffer) == 0){
            flag = 1;
            break;
        }
    }
    
 return flag;
}


int checkPunc( char buffer[]){
   
    int i, flag = 0;
    for(i = 0; i < strlen(buffer); ++i){
    	if(buffer[i]!='/'){
    		if(ispunct(buffer[i])){
    			if(buffer[i]=='_'|| buffer[i]=='*'){
    				flag=0;
				}
    			else{
    				flag=1;
    				break;
				}
			}
			else{
				flag=0;
			}
		}  
    }   
 return flag;
}




  
int main() 
{
	FILE *file;
    file = fopen("x.pmk", "r");
    char harf=getc(file);
    if(harf==-1){
    	printf("Dosya Bulunamadi!!!");
    	exit(1);
	}
	char s[100];//directory tuttan array 
// printing current working directory 
printf("Baslangic konumu: %s\n", getcwd(s, 100));
char t[100];//curr directoryi sabit tutan arr

int q;
q=0;
while((t[q] = s[q]) != '\0')
q++;
int check; 
int i=0;
int j=0;  //program akýþý için kullanýlan deðiþkenler
int k=0;
int m=0;
int p=0;
int sayac=0;
int id_length=0;
int id_length2=0;
int uzunluk=0;
char words2[100];
char words[100];
char temp[1];
char tempwords[100];


while(!feof(file)){
while(harf == 32 || (8 < harf && harf < 14)){ //Bosluk karakterleri icin if blogu
            harf = getc(file);
        }

i=0;
k=0;
memset(words2, 0, sizeof words2);//arraylerin  temizlenmesi alt satýrý almak için 
memset(words, 0, sizeof words);
if(harf==';'){
	harf=getc(file);
}
while(harf!='<'){// command kýsmýný alma yeri words arrayine dolacak (go if make) 

if(harf=='}'){//yapýlan iþlemler sonucunda dongude cekilen harfimiz if in bitiþi olursa bunu commande eklememek için.
	harf = getc(file);
}
while(harf == 32 || (8 < harf && harf < 14)){ //Bosluk karakterleri icin if blogu
            harf = getc(file);
        }
if(harf=='{'){
				harf = getc(file);
			}
if(harf=='}'){
				harf = getc(file);
			}
while(harf == 32 || (8 < harf && harf < 14)){ //Bosluk karakterleri icin if blogu
            harf = getc(file);
        }
words[i] = harf;
harf = getc(file); 


while(harf == 32 || (8 < harf && harf < 14)){
    harf = getc(file);
	}
i++;    
}
words[i] = '\0';
id_length=i;

if(harf=='<'){//argumaný aldýðýmýz  kýsým <*/*> gibi
harf = getc(file);
if(isspace(harf)){
    while(isspace(harf)){
        harf=getc(file);
    }
}
while(harf!='>'){ 
words2[k] = harf;
k++;
harf = getc(file);
if(isspace(harf)){
    while(isspace(harf)){
		harf=getc(file);
    }
}
}

if(words[0]!='i'||words[0]!='I'){//if durumunda parantezler ve ; ile bitme durumda oluþan karýþýklýðý onlemek için 
		harf = getc(file);
}



if(harf == ';'){
    printf("EndOfLine\n");
		  }
if(harf == '{'){
    printf("IF BASLANGIC\n");
		  }
}
words2[k] = '\0';

strcpy(tempwords,words2);
printf("%s komutu kontrole girdi\n",words);
printf("argumani: %s\n",words2);


//while(harf == 32 || (8 < harf && harf < 14)){ //Bosluk karakterleri icin if blogu
			//harf = getc(file);}
			
    if(checkKeyword(words)==1){//keyword dogru yazýldý mý kontrolü
const char *delp;// slah ile ayýrýlan elemanlarý tutacak dizi
    

char *path;//commandlerin içinde kullanýlacak
int z;
z=0;
while((path[z] = words2[z]) != '\0')//go da kullanýlmak üzere kayýt ediliyor
z++;

delp = strtok (words2, "/");


while (delp != NULL)  {//words2 bos olmadýgý sürece donecek; 
	
	if(words[0]=='m'||words[0]=='M'){
	uzunluk=strlen(delp)+1;//ortada yýldýz var mý durumu için matematiksel iþlem çözümü	
	if(words2[0]=='/'){//tüm hatalý durumlarda döngü kýrýlacak satýr atlanacak
		printf("Slashla baslayamaz!");
		break;	}
	if(isNumber(words2[0])){
		printf("Sayiyla baslayamaz!!\n");
		break;
	}
	if(checkPunc(tempwords)==1){
		printf("noktalama isareti hatasi\n");
		break;
	}
					  
	if(words2[0]!='*'){//arguman yýldýzla baþlamayýp sonrasýnda yýldýz geldiði zaman satýrý atlayacak
	
	if(words2[uzunluk]=='*'){
		printf("Ortada yildiz olamaz.");
		break;}}

	
	if(words2[k-1]=='/'){//sonda slah oldugu zaman satýrý atlamasý için 
		printf("Slashla bitemez!");
		break;	}  
	
	while(*delp=='*'){//argumanýmýz yýldýz oldugu zaman girecek
			chdir("..");//bir üst satýra terkar sayýsý kadar gidecek
		 	delp = strtok (NULL, "/");}		
	check=mkdir(delp);//dosya olustruma iþlemi argumana göre  eger olustrurusa check=0 olacak
	
	if(check==0){
		printf("%s dosyasi olusturuldu..\n",delp);
	}
	else{
		printf("%s dosyasi oldugu icin acilamadi!!\n",delp);
		
	}
	chdir(delp);//actýgý argumanýn konumuna giderek iç içe dosya olusturmayý saglýyor 	
	sayac++;

	
printf("Make ici konum %s\n", getcwd(s, 100));
	}//Make bitiþ parantezi
	
	else if(words[0]=='g'||words[0]=='G'){	
		
		if(*delp=='*'){//yýldýz geldiði zaman üst konuma geçiyor
			chdir("..");
		}
		chdir(path);//gelmediði zaman x.pmk dan verilene konuma gidiyor
		getcwd(s, 100);//guncel konumumuz alýnýyor
		int q;
		q=0;
		while((t[q] = s[q]) != '\0')//t guncel konumumuza esit oluyor yani curr directory degistirdik
		q++;}
	
	else if((words[0]=='i'&& words[1]=='f'&& words[2]=='n')||(words[0]=='I'&& words[1]=='F'&& words[2]=='N')||(words[0]=='I'&& words[1]=='f'&& words[2]=='n')){
		while(harf == 32 || (8 < harf && harf < 14)){ //Bosluk karakterleri icin if blogu
            harf = getc(file);
        }
		int kont=1;
		kont=chdir(delp);//dosya acýlýrsa kont=0 oluyor 
		
		if(*delp=='*'){//yýldýz oldugu durum
		
		chdir("..");	
		printf("if ici   %s\n", getcwd(s, 100));
		char name[] = "C:\\Users";
if(strcmp(s,name) == 0){
			printf("bir ust konum user ama ifnot oldugu icin calisti\n");
			}
else{//durumun dogru oldugu durumda ifnot oldugu icin ifnotun kapsadýgý satýrlar {}blok olarak ve ya tek satýr okunarak bir sonraki anlamlý satýra gecildigi yer
	

	if(harf=='{'){
	
			while(harf!='}'){
				harf = getc(file);
				if(harf=='}'){
					printf("Ifnot blogu parantez ile bitti\n ");}}
			harf = getc(file);
			}
			
	else{
			while(harf!=';'){

	harf = getc(file);
	if(harf==';'){
		printf("Ifnot tek satýr oldugu icin ; ile bitti\n");
	}}
	harf = getc(file);	
	}	
	break;		
		}}	
	
	else{//içinde arguman oldugu durum
	
	if(kont != 0){
			printf("Durum saglanamadi ama ifnot oldugu icin gerceklesti\n");
					
		}
		else if(kont==0){

printf("Durum saglandi ama ifnot oldugu icin gerceklesmedi\n");//ifnot blogu atlanacak
	if(harf=='{'){//ifnotun parantezli oldugu durum
	
	while(harf!='}'){

	harf = getc(file);
	if(harf=='}'){
		printf("Ifnot parantez ile bitti\n ");
	}}}
	
	else{//eger  kod tek satýrlýksa { ifadesi icermedigi icin bu durumda calýsacak
			while(harf!=';'){
	harf = getc(file);
	if(harf==';'){
		printf(" ifnot virgul ile bitti\n ");
	}}}
	break;}
		}	
	}//ifnot bitiþ parantezi
	
	else{//if commandi kosulu
		if(*delp=='*'){//yýldýz oldugu durum icin
		chdir("..");	
		getcwd(s, 100);//suanki konum alýndý
		char name[] = "C:\\Users";
		if(strcmp(s,name) == 0){//eger bir uste gittiginde user ile karsýlasýyorsa girecek ve if blogunu yoksayacak
			printf("Bir ust dizine giris izniniz yok!!!\n");
		while(harf == 32 || (8 < harf && harf < 14)){ //Bosluk karakterleri icin if blogu
			harf = getc(file);}	
	if(harf=='{'){
		while(harf!='}'){
				harf = getc(file);
	if(harf=='}'){
		printf("IF parantez ile bitti\n");
	}}
	harf = getc(file);		
		}
	
	else{//tek satýrlýk if icin satýr atlama blogu
			while(harf!=';'){
	harf = getc(file);
	if(harf==';'){
		printf("IF virgul ile bitti\n");
	}}
	harf = getc(file);}	
		break;}	}//if<*> ken buraya kadar simdi diger kural
	
	else{//if in icinde * dýsýnda bi arguman oldugu zaman
		int kont=1;
		kont=chdir(delp);//EGER dosya konumuna gidilebildiyse altýnda dosya vardýr kont=0 dýr.
		if(kont!=0){
			printf("Alt dizinde bu dosya bulunmamaktir\n");
			
while(harf == 32 || (8 < harf && harf < 14)){ //Bosluk karakterleri icin if blogu
			harf = getc(file);}
	if(harf=='{'){	
	while(harf!='}'){
	harf = getc(file);
	if(harf=='}'){
		printf("IF parantez ile bitti\n ");
	}}}
	
	else {
		while(harf!=';'){
	harf = getc(file);
	if(harf==';'){
		printf("IF virgul ile bitti\n");
	}}}
	break;}}
	
	
	printf("IF'te bir soruna rastlanmadi\n");
	break;	
	}
	delp = strtok (NULL, "/");
	  }	
}
//Alt tarafta while donugusu oldugu için  / saysýnýn 1 fazlasý kadar hangi durum gerceklestigi yazacagý için  donguye girmeden bastýrdýk

   
chdir(t);//Current dir degistirme kýsmý t arrayi go da degýsýyor make de sabit kalýyor en son isimiz bitince bu konuma donuyoruz
printf("en son konum %s\n", getcwd(s, 100));
printf("\n");
printf("---------------------------------------------------------------------\n");
//harf = getc(file);

}
return 0;
}
