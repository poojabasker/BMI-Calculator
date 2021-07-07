#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<graphics.h>
#include<process.h>
#include<stdlib.h>
#include<iomanip.h>
#include<dos.h>

void END_SCREEN();
void SCREEN1();
void SCREEN2();
void ADMIN_MENU();
void TEACHER_MENU();
int c=1,count=0,a=5;
float tot;

class admin
{
    char name[20], g[3], inf[50];
    int rno, age;
    float h,w,bmi;
    void CALCBMI();
    void INFERENCE();
  public:
    admin();
    void GETDATA();
    void PUTDATA();
    int GETRNO();
    int GETAGE();
    float GETH();
    float GETW();
    float GETBMI();
    void PUTN();
    void PUTG();
    void PUTI();
    void MODIFY();
    admin SEARCH();
}ad,obj;

//GETTING ROLL NUMBER
int admin::GETRNO()
{
 return rno;

}

//GETTING AGE
int admin::GETAGE()
{
 return age;
}

//GETTING HEIGHT
float admin::GETH()
{
 return h;
}

//GETTING WEIGHT
float admin::GETW()
{
 return w;
}

//GETTING BMI
float admin::GETBMI()
{
  CALCBMI();
 return bmi;

}

//PUTTING NAME
void admin::PUTN()
{
 puts(name);
}

//PUTTING GENDER
void admin::PUTG()
{
 cout<<g;
}

//PUTTING INFERENCE
void admin::PUTI()
{
 puts(inf);
}

//CALCULATING BMI
void admin::CALCBMI()
{
 count++;
 bmi=w/pow((h/100),2);
 tot+=bmi;
}

//INFERENCE
void admin::INFERENCE()
{
 if(bmi<16)
  strcpy(inf,"Severely thin");
 else if(bmi>=16 && bmi<17)
  strcpy(inf,"Moderately thin");
 else if(bmi>=17 && bmi<18.5)
  strcpy(inf,"Slightly thin");
 else if(bmi>=18.5 && bmi<25)
  strcpy(inf,"Healthy");
 else if(bmi>=25 && bmi<30)
  strcpy(inf,"Overweight");
 else if(bmi>=30 && bmi<35)
  strcpy(inf,"Obese class I");
 else if(bmi>=35 && bmi<40)
  strcpy(inf,"Obese class II");
 else
  strcpy(inf,"Obese class III");
}

//CONSTRUCTOR FOR CLASS ADMIN

admin::admin()
{
 strcpy("NULL", name);
 strcpy("NULL", g);
 strcpy("NULL", inf);
 rno=age=0;
 h=w=bmi=0.0;
}

//GETTING DATA FOR CLASS ADMIN
void admin::GETDATA()
{
 cin>>rno;
 gets(name);
 cin>>g;
 cin>>age;
 cin>>h;
 cin>>w;
 CALCBMI();
 INFERENCE();
}

//DISPLAY DATA FOR CLASS ADMIN
void admin::PUTDATA()
{

 gotoxy(6,a);
 cout<<rno;
  gotoxy(12,a);
 cout<<name;
  gotoxy(27,a);
 cout<<g;
  gotoxy(33,a);
 cout<<age;
  gotoxy(41,a);
 cout<<h;
  gotoxy(51,a);
 cout<<w;
  gotoxy(58,a);
 cout<<setprecision(2)<<bmi;
  gotoxy(65,a);
 cout<<inf;
 cout<<endl;
 a+=2;
}

//MODIFYING THE ENTRIES IN THE DATAFILE
void admin::MODIFY()
{
 int no, a; char sn[20], gen[3]; float ht, wt;
 cout<<"*to retain the old value enter -1*"<<endl;
 cout<<"Enter the new roll number: "; cin>>no;
 cout<<"Enter new name: "; gets(sn);
 cout<<"Enter gender: "; gets(gen);
 cout<<"Enter age: "; cin>>a;
 cout<<"Enter new height: "; cin>>ht;
 cout<<"Enter new weight: "; cin>>wt;
   if(no!=-1)
    rno=no;
   if(strcmp(sn,"-1")!=0)
    strcpy(name,sn);
   if(strcmp(gen,"-1")!=0)
    strcpy(g,gen);
   if(a!=-1)
    age=a;
   if(ht!=-1)
    h=ht;
   if(wt!=-1)
    w=wt;
 CALCBMI();
 INFERENCE();
}

//SEARCHING FOR THE RECORD
admin admin::SEARCH()
{
 c=0;
 int r,k=0,ck;
 while(k<3)
 {
  ck=1;
  k++;
  ifstream fin("ADMIN_BMI.DAT", ios::binary|ios::in);
  closegraph();
  clrscr();
  cout<<"\nEnter your roll number: ";
  cin>>r;
    if(r<=0)                         //checking if roll number is positive
	{
	cout<<"Invalid roll number!";
	getch();
	ck=0;
	}
  while(!fin.eof())
   {
     fin.read((char*)&ad,sizeof(ad));
     if(r==ad.GETRNO())
      {
	c=1;
	obj=ad;
	return obj;
      }
   }
  if(c==0 && ck==1)
   {
    cout<<"Roll number not found! \n";
    getch();
   }
  fin.close();
 }
 gotoxy(0,0);
 cout<<"Non existent roll number!!"<<endl;
 SCREEN2();
 return obj;
}

//CREATING THE DATAFILE
void CREATE()
{
 char ch;
 clrscr();
 ofstream fout("ADMIN_BMI.DAT",ios::binary|ios::out);
  do
   {
     cout<<"Enter roll number, name, gender, age, height(cm), weight(kg):\n";
     ad.GETDATA();
     fout.write((char*)&ad,sizeof(ad));
     cout<<"Enter more information?(Y/N)"<<endl;

  cin>>ch;
   }while(ch=='y'|| ch=='Y');
 fout.close();
}

//HEADING FOR ADMIN DISPLAY
void DSCREEN()
{
 textcolor(LIGHTMAGENTA);
  gotoxy(2,3);
  cprintf(" ROLL NO.");
 textcolor(LIGHTBLUE);
  gotoxy(13,3);
  cprintf(" NAME ");
 textcolor(LIGHTRED);
  gotoxy(23,3);
  cprintf(" GENDER ");
 textcolor(YELLOW);
  gotoxy(32,3);
  cprintf(" AGE ");
 textcolor(LIGHTMAGENTA);
  gotoxy(38,3);
  cprintf(" HEIGHT ");
 textcolor(LIGHTBLUE);
  gotoxy(48,3);
  cprintf(" WEIGHT ");
 textcolor(LIGHTRED);
  gotoxy(58,3);
  cprintf(" BMI ");
 textcolor(LIGHTGREEN);
  gotoxy(64,3);
  cprintf(" INFERENCE\n");
 textcolor(WHITE);
}

//DISPLAYING THE DATAFILE
void DISPLAY(int var=0)
{
 clrscr();
 char rep;
 textcolor(LIGHTGRAY);
 ifstream fin("ADMIN_BMI.DAT", ios::binary|ios::in);
 DSCREEN();
 while(!fin.eof())
  {
    fin.read((char*)&ad,sizeof(ad));
    if(fin.eof())break;
    if(a<=22)
      ad.PUTDATA();
    else
     {

 cout<<"\nDo you want to view the next set of records?\n";
       cin>>rep;
       if(rep=='y'||rep=='Y')
	{
	  clrscr();
	  DSCREEN();
	  a=5;
	  ad.PUTDATA();
	}
       else if(var==0)
	ADMIN_MENU();
       else if(var==1)
	TEACHER_MENU();
     }
  }
  fin.close();
  getch();
}

//SORTING THE DATAFILE
void SORT()
{
 c=0;
 ifstream fin("ADMIN_BMI.DAT",ios::binary|ios::in);
 ofstream fout("TEMP.DAT",ios::binary|ios::out);
 admin roll[100]; int c=0;
 while(!fin.eof())

 {
  fin.read((char*)&obj,sizeof(obj));
  if(fin.eof())break;
  roll[c]=obj;
  c++;
 }
 fin.close();
 int i,j; admin temp;
 for(i=0; i<c; i++)
 {    for(j=0; j<c-i-1; j++)
       {  if(roll[j].GETRNO()>roll[j+1].GETRNO())
	    {  temp=roll[j];
	       roll[j]=roll[j+1];
	       roll[j+1]=temp;
	    }
       }
 }
 ifstream fin1("ADMIN_BMI.DAT", ios::binary|ios::in);
 while(!fin1.eof())
 {
  for(i=0; i<c; i++)
  {
    fin1.read((char*)&obj,sizeof(obj));
    if(fin1.eof())break;
    obj=roll[i];

    fout.write((char*)&obj,sizeof(obj));
  }
 }
 fin1.close();
 fout.close();
 remove("ADMIN_BMI.DAT");
 rename("TEMP.DAT", "ADMIN_BMI.DAT");
}

//APPENDING ENTRIES IN THE DATAFILE
void INSERT()
{
 int r,flg=1;
 clrscr();
 char ch;
 ofstream fout("ADMIN_BMI.DAT",ios::binary|ios::app);
 ifstream fin("ADMIN_BMI.DAT",ios::binary|ios::in);
 do
   {
     cout<<"Enter roll no to be inserted\n";
     cin>>r;
     while(!fin.eof())
     {
	fin.read((char*)&obj,sizeof(obj));
	if(fin.eof())

	    break;
	if(r==obj.GETRNO())
	{
	   cout<<"Record cannot be inserted\n";
	   delay(700);
	   flg=0;
	   break;
	}
     }
     if(flg==1)
     {
     cout<<"Enter data to be inserted: ";
     cout<<"\nEnter roll number, name, gender, age, height(cm), weight(kg):\n";
     ad.GETDATA();
     fout.write((char*)&ad,sizeof(ad));
     cout<<"Insert more data?(Y/N)"<<endl;
     cin>>ch;
     }
   }while(ch=='y'|| ch=='Y');
 fout.close();
 SORT();
}

//DELETING ENTRIES IN THE DATAFILE
void DELETE()

{
 clrscr();
 ifstream fin("ADMIN_BMI.DAT", ios::binary);
 ofstream fout("TEMP.DAT", ios::binary);
 cout<<"Enter roll number of student whose record has to be deleted: ";
 int x;
 cin>>x;
 while(!fin.eof())
 {
  fin.read((char*)&obj,sizeof(obj));
  if(fin.eof())break;
  if(obj.GETRNO()!=x)
  fout.write((char*)&obj,sizeof(obj));
 }
 fout.close();
 fin.close();
 remove("ADMIN_BMI.DAT");
 rename("TEMP.DAT","ADMIN_BMI.DAT");
 cout<<"Record deleted\n";
 getch();
}

//CALCULATING THE CLASS AVERAGE
float AVERAGE()
{

float BMI=0.0; c=0;
 ifstream fin("ADMIN_BMI.DAT", ios::binary|ios::in);
 while(!fin.eof())
  {
    fin.read((char*)&ad,sizeof(ad));
    if(fin.eof())break;
    c++;
    BMI+=ad.GETBMI();
  }
 BMI/=c;
 fin.close();
 return BMI;
}

//MODYIFYING A RECORD
void MODIFY()
{
 char ans;
 do{
 ifstream fin("ADMIN_BMI.DAT", ios::binary|ios::in);
 ofstream fout("TEMP.DAT", ios::binary|ios::out);
 int x, f=0, pos;
 clrscr();
 cout<<"Enter the roll number of record that has to be modified: \n";
 cin>>x;
 while(!fin.eof())
 {

   fin.read((char*)&obj, sizeof(obj));
   if(fin.eof())break;
   int r=obj.GETRNO();
   if(r==x)
    {
      obj.MODIFY();
      f=1;
    }
   fout.write((char*)&obj,sizeof(obj));
 }
 if(f==0)
  cout<<"Record not found!"<<endl;
 else
  cout<<"Record modified\n";
  cout<<"Do you want to continue?\n";
  cin>>ans;
 getch();
 fin.close();
 fout.close();
 remove("ADMIN_BMI.DAT");
 rename("TEMP.DAT","ADMIN_BMI.DAT");
 }while(ans=='y'||ans=='Y');
}

//ADMIN MENU
void ADMIN_MENU()
{
  void SCREEN1();

  char choice;
  int ch=1;
  do{
  clrscr();
  textcolor(WHITE);
   cprintf("--------------------------------------------------------------------------------\n");
  textcolor(LIGHTBLUE);
   cprintf("                                 ADMIN MENU                                     ");
  textcolor(WHITE);
   cprintf("\n--------------------------------------------------------------------------------\n");
  textcolor(YELLOW);
   cprintf("\n1.Create datafile                                                               ");
  textcolor(LIGHTGREEN);
   cprintf("\n2.View datafile                                                                 ");
  textcolor(LIGHTRED);
   cprintf("\n3.Insert records in the datafile                                                ");
  textcolor(LIGHTBLUE);
   cprintf("\n4.Modify the datafile                                                           ");
  textcolor(GREEN);
   cprintf("\n5.Delete records from the datafile                                              ");
  textcolor(LIGHTMAGENTA);
   cprintf("\n6.Sort the datafile                                                             ");
  textcolor(CYAN);
   cprintf("\n7.Exit Admin menu                                                               ");

  textcolor(YELLOW);
   cprintf("\n8.Exit the program  \n");
  cout<<"\nEnter your choice\n";
  textcolor(WHITE);
  cin>>ch;
  switch(ch)
   {
     case 1: CREATE(); break;
     case 2: a=5; DISPLAY();break;
     case 3: INSERT(); break;
     case 4: MODIFY(); break;
     case 5: DELETE(); break;
     case 6: SORT(); cout<<"Datafile sorted\n"; delay(700);  break;
     case 7: SCREEN1();break;
     case 8: END_SCREEN(); break;
     default: cout<<"Invalid choice!"<<endl;
	      delay(700);
   }
 }while(ch>=1 || ch<=0);
 closegraph();
}

//ADMIN PASSWORD
void ADMIN_PASS()
{
 closegraph();
 clrscr();
 int c=1;
 while(c<=3)
 {
  cout<<"Enter password:\n";
  char p[10];
  cin>>p;
  if(c<=3)
   {
    if(strcmp(p,"apassword")==0)
     {
       ADMIN_MENU();
       break;
     }
    else
     {
       cout<<"\nWrong password.\n";
       c++;
       getch();
       clrscr();
     }
   }
 }
 if(c==4)

 {
   cout<<"\nYOU ARE NOT AUTHORIZED TO VIEW THIS.\n";
   getch();
   SCREEN1();
 }
}

//*******************************END OF ADMIN**********************************

//STUDENT REPORT
void SREPORT(admin adm)
{
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\TurboC3\\bgi\\");
  cleardevice();

  settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
  setcolor(MAGENTA);
   outtextxy(195,20,"REPORT");

  setcolor(LIGHTGRAY);
  setlinestyle(SOLID_LINE,1,THICK_WIDTH);
   rectangle(3,5,638,472);
   rectangle(9,11,632,466);
  setcolor(BLUE);

 setlinestyle(DOTTED_LINE,1,THICK_WIDTH);
   rectangle(6,8,635,469);

  settextstyle(2,HORIZ_DIR,8);
  setcolor(LIGHTCYAN);
  outtextxy(50,135,"ROLL NUMBER: ");
   gotoxy(30,10);
   cout<<adm.GETRNO();
  outtextxy(340,135,"NAME: ");
   gotoxy(53,10);
   adm.PUTN();
  outtextxy(50,183,"AGE: ");
   gotoxy(15,13);
   cout<<adm.GETAGE();
  outtextxy(340,183,"GENDER: ");
   gotoxy(57,13);
   adm.PUTG();
  setcolor(LIGHTBLUE);
   cout.setf(ios::fixed);
   cout<<setprecision(2);
  outtextxy(50,232,"HEIGHT: ");
   gotoxy(20,16);
   cout<<adm.GETH();
  outtextxy(340,232,"WEIGHT: ");
   gotoxy(57,16);

    cout<<adm.GETW();
  outtextxy(50,280,"BMI: ");
   gotoxy(15,19);
   cout<<adm.GETBMI();
   cout.unsetf(ios::fixed);
  outtextxy(340,280,"INFERENCE: ");
   gotoxy(62,19);
   adm.PUTI();
  getch();
  closegraph();
}

//STUDENT ANALYSIS
void SGRAPH(admin obj)
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C:\\TurboC3\\bgi\\");
 float BMI=obj.GETBMI();
 float avg=AVERAGE();
 float y1,y2,y11,y22;
 int i,y;
 cleardevice();

 settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
 setcolor(YELLOW);

 outtextxy(175,0,"ANALYSIS");

 setcolor(WHITE);
 setlinestyle(SOLID_LINE,1,NORM_WIDTH);
  line(20,430,370,430);
  line(20,430,20,100);
 for(i=0,y=400;i<9;i++,y-=30)
  line(15,y,20,y);
 settextstyle(SMALL_FONT,HORIZ_DIR,4);
 char n[][3]={"10","20","30","40","50","60","70","80","90"};
 for(i=0,y=395;i<9;i++,y-=30)
  outtextxy(3,y,n[i]);
  outtextxy(1,125,"100");
  outtextxy(12,425,"0");
  outtextxy(12,85,"BMI");

 y1=430-(3*BMI);
 y11=430-(3*(BMI/2));
 y2=430-(3*avg);
 y22=430-(3*(avg/2));
 setcolor(WHITE);
 setfillstyle(INTERLEAVE_FILL,LIGHTBLUE);
  rectangle(70,430,170,y1);
 floodfill(100,y11,WHITE);
 setfillstyle(INTERLEAVE_FILL,LIGHTGREEN);

   rectangle(220,430,320,y2);
 floodfill(250,y22,WHITE);

 setcolor(WHITE);
 settextstyle(SMALL_FONT,HORIZ_DIR,6);
 outtextxy(90,435,"Your's");
 outtextxy(205,435,"Class average");

 setcolor(DARKGRAY);
 setlinestyle(SOLID_LINE,0,THICK_WIDTH);
 rectangle(410,145,600,200);

 settextstyle(SMALL_FONT,HORIZ_DIR,6);
 setcolor(WHITE);
  cout.setf(ios::fixed);
  cout<<setprecision(2);
 outtextxy(420,157,"AVERAGE BMI = ");
  gotoxy(70,11);
  cout<<avg;
 outtextxy(420,173,"YOUR BMI = ");
  gotoxy(66,12);
  cout<<BMI;
  cout.unsetf(ios::fixed);
 getch();
 closegraph();

}

//STUDENT TIPS
void STIPS(admin obj)
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C:\\TurboC3\\bgi\\");
 float bmi=obj.GETBMI();
 cleardevice();

 settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
 setcolor(LIGHTGREEN);
 outtextxy(270,50,"TIPS");

 if(bmi<=18)
  {
    cout<<"\n\n\n\n\n\n\n\n";
    cout<<"1. Add healthy calories to your diet by adding nut or seed toppings, cheese,       brown rice and whole wheat grains.\n\n";
    cout<<"2. Keep yourself hydrated with smoothies and shakes made with low-fat milk.\n\n";
    cout<<"3. Eat snacks which contains proteins, plenty of good fats and health              carbohydrates.\n\n";
    cout<<"4. To increase your calorie intake, eat small meals throughout the day.\n\n";

    cout<<"5. Strength training can help which includes weight lifting and yoga.\n\n";
    cout<<"6. Apart from bulking up, burn as few calories as possible.\n\n";
  }
 else if(bmi>18 && bmi<=26)
  {
    cout<<"\n\n\n\n\n\n\n\n\n";
    cout<<"1. Have a nutrients dense diet by piling on fruits and vegetables.\n\n";
    cout<<"2. Eat lean meats and low-fat dairy products.\n\n";
    cout<<"3. Include brown grains, not white grains in your diet.\n\n";
    cout<<"4. Do not eat processed junk or packed foods.\n\n";
    cout<<"5. Stay hydrated.\n\n";
    cout<<"6. Exercise regularly.\n\n";
  }
 else
  {
    cout<<"\n\n\n\n\n\n\n\n\n";
    cout<<"1. Choose lean proteins instead of the fatty ones to feel energized.\n\n";
    cout<<"2. Avoid sweetened drinks as they have little nutritional value and will add a     lot of empty calories.\n\n";
    cout<<"3. Don't skip meals as it is not a healthy eating pattern for weight loss.\n\n";
    cout<<"4. Cut out salt from your diet as it leads to water retention.\n\n";
    cout<<"5. Stay hydrated.\n\n";

    cout<<"6. Eat fewer calories than you burn. This can be done by exercising and strength   training.\n\n";
  }
 getch();
 closegraph();
}

//STUDENT MENU
void STUDENT_MENU()
{
 int ans=1;
 void SCREEN2();
 admin found;
 found=obj.SEARCH();
 closegraph();
 clrscr();
 while(ans)
  {
   clrscr();
   textcolor(WHITE);
    cprintf("\n--------------------------------------------------------------------------------\n");
   textcolor(BLUE);
    cprintf("                                 STUDENT MENU                                   ");
   textcolor(WHITE);

    cprintf("\n--------------------------------------------------------------------------------\n");
   textcolor(LIGHTRED);
    cprintf("\n1.Get your report                                                               ");
   textcolor(YELLOW);
    cprintf("\n\n2.Get your graph                                                                ");
   textcolor(LIGHTGREEN);
    cprintf("\n\n3.Get some tips                                                                 ");
   textcolor(BLUE);
    cprintf("\n\n4.Exit student menu  \n");
   cout<<"\n\nEnter your choice\n";
   cin>>ans;
   textcolor(WHITE);
   switch(ans)
   {
     case 1: SREPORT(found);break;
     case 2: SGRAPH(found); break;
     case 3: STIPS(found); break;
     case 4: SCREEN2(); break;
     default: cout<<"Invalid choice!"<<endl;
	      delay(700);
   }
   textcolor(WHITE);
 }
 getch();

}

//**********************************END OF STUDENT*****************************

//TEACHER GRAPH
void TGRAPH()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C:\\TurboC3\\bgi\\");
 int y;
 float y1,y2,y3,BMI;
 cleardevice();

 settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
 setcolor(LIGHTGREEN);
 outtextxy(175,0,"ANALYSIS");

 float pu=0,pn=0,po=0,au,an,ao;
 ifstream fin("ADMIN_BMI.DAT", ios::binary|ios::in);
 while(!fin.eof())
  {
    fin.read((char*)&ad,sizeof(ad));
    if(fin.eof())break;
     BMI=ad.GETBMI();
    if(BMI>0 && BMI<18.5)

      pu++;
    else if(BMI>=18.5 && BMI<25)
      pn++;
    else if(BMI>=25)
      po++;
   }
 fin.close();
 tot=pu+pn+po;
 au=(pu/tot)*360;
 an=(pn/tot)*360;
 //ao=(po/tot)*360;
 arccoordstype arc1,arc2,arc3;

 setcolor(LIGHTBLUE);
 setfillstyle(CLOSE_DOT_FILL,BLUE);
  pieslice(170,260,0,au,150);
 getarccoords(&arc1);
  line(170,260,arc1.xend,arc1.yend);

 setcolor(YELLOW);
 setfillstyle(CLOSE_DOT_FILL,YELLOW);
  pieslice(170,260,au,au+an,150);
 getarccoords(&arc2);
  line(170,260,arc2.xend,arc2.yend);


 if(au+an!=360)
  {
    setcolor(LIGHTRED);
    setfillstyle(CLOSE_DOT_FILL,RED);
     pieslice(170,260,au+an,360,150);
    getarccoords(&arc3);
     line(170,260,arc3.xend,arc3.yend);
  }

 setcolor(DARKGRAY);
 setlinestyle(SOLID_LINE,0,THICK_WIDTH);
  rectangle(340,110,610,205);
 settextstyle(SMALL_FONT,HORIZ_DIR,6);
 setcolor(WHITE);
  outtextxy(460,115,"KEY");
 setcolor(LIGHTBLUE);
  outtextxy(350,139,"Underweight =   student(s)");
   gotoxy(61,10);
   cout<<pu;
 setcolor(YELLOW);
  outtextxy(350,155,"Normal =    student(s)");
   gotoxy(55,11);
   cout<<pn;
 setcolor(LIGHTRED);
  outtextxy(350,173,"Overweight =    student(s)");

   gotoxy(60,12);
   cout<<po;
 getch();
 closegraph();
}

//TEACHER ANALYSIS
void TANALYSIS()
{
 int ch;
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C:/TurboC3//bgi//");
 cleardevice();

 settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
 setcolor(MAGENTA);
  outtextxy(175,0,"ANALYSIS");
 settextstyle(SMALL_FONT,HORIZ_DIR,7);
 setcolor(LIGHTGREEN);
  outtextxy(50,150,"REASONS FOR BEING :");
 setcolor(LIGHTBLUE);
  outtextxy(80,200,"1. Underweight");
 setcolor(YELLOW);
  outtextxy(80,250,"2. Normal");
 setcolor(LIGHTRED);

  outtextxy(80,300,"3. Overweight");
  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n      Enter a choice\n      ";
  cin>>ch;

 cleardevice();
 settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
 setcolor(LIGHTRED);
  if(ch==1)
   {
     outtextxy(145,300,"Reasons for thinness");
      cout<<"\n\n";
      cout<<"1. A person may be underweight due to genetics, metabolism, lack of food or        illness.\n\n";
      cout<<"2. Being underweight is also associated with certain medical conditions            including hyperthyroidism, cancer or tuberculosis.\n\n";
      cout<<"3. Certain prescription medicines can cause nausea and weight loss.\n\n";
      cout<<"4. People with certain eating disorders may also be underweight due to lack of     nutrients/over exercise.\n\n";
      cout<<"5. Underweight might be secondary to or symptomatic of an underlying disease.\n\n\n\n\n\n\n";
   }
  else if(ch==2)
   {

     outtextxy(120,300,"Reasons for being healthy");
      cout<<"\n\n";
      cout<<"1. People are healthy due to proper intake of healthy diet.\n\n";
      cout<<"2. Healthy individuals exercise daily and stay fit.\n\n";
      cout<<"3. Their immune system remains strong and their body is not prone to any kind of   disease.\n\n";
      cout<<"4. Avoiding mental tension and depression can be a factor enhancing their body     fitness.\n\n";
      cout<<"5. Healthy people drink enough water and take appropriate sleep.\n\n\n\n\n\n";
    }
  else if(ch==3)
    {
      outtextxy(120,300,"Reasons for being overweight");
       cout<<"\n\n";
       cout<<"1. People gain weight when the eat oversized food portions and increase their      calorie intake that they burn through activity.\n\n";
       cout<<"2. Genes may also contribute to a person's susceptibility to weight gain.\n\n";
       cout<<"3. Some hormone problems may cause overweight and obesity such as thyroid and      cushing syndrome.\n\n";
       cout<<"4. Tension, depression or boredom can also be one of the reasons for obesity.\n\n";
       cout<<"5. The less people sleep, the more likely they are to be overweight or obese.\n\n\n\n\n\n";

    }
  else
    cout<<"Wrong choice!\n";
 getch();
 closegraph();
}

//TEACHER MENU
void TEACHER_MENU()
{
 int ans=1;
 void SCREEN2();
 clrscr();
  while(ans)
   {
     clrscr();
     textcolor(WHITE);
      cprintf("\n--------------------------------------------------------------------------------\n");
     textcolor(YELLOW);
      cprintf("                                 TEACHER MENU                                   ");
     textcolor(WHITE);
      cprintf("\n--------------------------------------------------------------------------------\n");
     textcolor(LIGHTRED);

      cprintf("\n1.View BMI of all the students                                                  ");
     textcolor(BLUE);
      cprintf("\n\n2.View comparitive graph                                                        ");
     textcolor(LIGHTGREEN);
      cprintf("\n\n3.View the analysis                                                             ");
     textcolor(YELLOW);
      cprintf("\n\n4.Exit teacher menu                                                          ");
     textcolor(WHITE);
      cout<<"\n\n\nEnter your choice\n";
      cin>>ans;
     switch(ans)
      {
       case 1: a=5; DISPLAY(1); break;
       case 2: TGRAPH(); break;
       case 3: TANALYSIS();break;
       case 4: SCREEN2();break;
       default: cout<<"Invalid choice!"<<endl;
		delay(700);
      }
   }
 getch();
}

//TEACHER PASSWORD
void TEACHER_PASS()

{
 closegraph();
 clrscr();
 int c=1;
 while(c<=3)
 {
  cout<<"Enter password:\n";
  char p[10];
  cin>>p;
  if(c<=3)
   {
    if(strcmp(p,"password")==0)
     {
      TEACHER_MENU();
      break;
     }
    else
     {
      cout<<"\nWrong password.\n";
      c++;
      getch();
      clrscr();
     }
   }
 }

 if(c==4)
 {
   cout<<"\nYOU ARE NOT AUTHORIZED TO VIEW THIS.\n";
   getch();
   SCREEN2();
 }
}

//*******************************END OF TEACHER*********************************

//FIRST SCREEN
void BMI_SCREEN()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C://TurboC3//bgi//");
 setcolor(WHITE);
 setlinestyle(SOLID_LINE,0,THICK_WIDTH);
  rectangle(3,5,638,472);
  line(225,265,420,265);
 settextstyle(SANS_SERIF_FONT,HORIZ_DIR,10);
 setcolor(CYAN);
  outtextxy(240,40,"BMI");
 settextstyle(SMALL_FONT,HORIZ_DIR,10);
 setcolor(LIGHTGREEN);
  outtextxy(150,180,"Body Mass Index");

 setcolor(DARKGRAY);
 settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
  outtextxy(215,445,"Press ENTER to continue\n");
 getch();
}

//MAIN MENU
void SCREEN1()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C://TurboC3//bgi//");
 char ch='1';
 cleardevice();
 settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
 setcolor(LIGHTRED);
  outtextxy(240,100,"ADMIN");
 setcolor(LIGHTCYAN);
  outtextxy(255,270,"USER");
 settextstyle(SMALL_FONT,HORIZ_DIR,6);
 setcolor(DARKGRAY);
  outtextxy(290,165,"Press (A)");
  outtextxy(290,335,"Press (U)");
 settextstyle(SMALL_FONT,HORIZ_DIR,7);
 setcolor(LIGHTGRAY);
  outtextxy(235,445,"Press (E) to exit\n");

 setcolor(WHITE);
 setlinestyle(SOLID_LINE,0,THICK_WIDTH);
  rectangle(200,95,446,200);
  rectangle(200,265,446,370);
  rectangle(3,5,638,472);
 while(ch)
 {
  ch=getch();
  switch(ch)
  {
   case 'a':
   case 'A':ADMIN_PASS();break;
   case 'u':
   case 'U':SCREEN2();break;
   case 'e':
   case 'E':END_SCREEN();
   default :break;
  }
 }
 closegraph();
}

//USER MENU
void SCREEN2()
{

 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C://TurboC3//bgi//");
 char ch='1';
 cleardevice();
 settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
 setcolor(YELLOW);
  outtextxy(200,100,"STUDENT");
 setcolor(BLUE);
  outtextxy(200,270,"TEACHER");
 settextstyle(SMALL_FONT,HORIZ_DIR,6);
 setcolor(DARKGRAY);
  outtextxy(290,165,"Press (S)");
  outtextxy(290,335,"Press (T)");
 settextstyle(SMALL_FONT,HORIZ_DIR,7);
 setcolor(LIGHTGRAY);
  outtextxy(115,445,"Press (E) to exit||Press (B) to go back\n");
 setcolor(WHITE);
 setlinestyle(SOLID_LINE,0,THICK_WIDTH);
  rectangle(160,95,486,200);
  rectangle(160,265,486,370);
  rectangle(3,5,638,472);
 while(ch)
 {
  ch=getch();
  switch(ch)

   {
    case 's':
    case 'S':STUDENT_MENU();break;
    case 't':
    case 'T':TEACHER_PASS();break;
    case 'b':
    case 'B':SCREEN1();break;
    case 'e':
    case 'E':END_SCREEN();
    default :break;
   }
 }
 closegraph();
}

//LAST SCREEN
void END_SCREEN()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C://TurboC3//bgi//");
 cleardevice();
 setcolor(WHITE);
 setlinestyle(SOLID_LINE,0,THICK_WIDTH);
  rectangle(3,5,638,472);
 settextstyle(TRIPLEX_FONT,HORIZ_DIR,5);

 setcolor(LIGHTRED);
  outtextxy(20,100,"PROJECT DONE BY : ");
 settextstyle(SMALL_FONT,HORIZ_DIR,8);
 setcolor(YELLOW);
  outtextxy(350,200,"Pooja Basker");
 setcolor(LIGHTBLUE);
  outtextxy(350,280,"N. Swarnavalli");
 setcolor(LIGHTGREEN);
  outtextxy(350,360,"Manika Kesharwani");
 settextstyle(SMALL_FONT,HORIZ_DIR,7);
 setcolor(LIGHTGRAY);
 getch();
 exit(0);
}
//********************************END OF SCREENS*******************************

//MAIN
void main()
{
  clrscr();
  BMI_SCREEN();
  SCREEN1();
  getch();
}
//********************************END OF MAIN*********************************
