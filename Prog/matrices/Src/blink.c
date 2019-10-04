
#include"blink.h"



void mise_zero_oeil(char oeil[GF][GF])
{
  int i,j;
  for(i=0;i<GF;i++)
  {
    for(j=0;j<GF;j++)
    {
      oeil[i][j]=0;
    }
  }
}

void mise_un_oeil(char oeil[GF][GF])
{
  int i,j;
  for(i=0;i<GF;i++)
  {
    for(j=0;j<GF;j++)
    {
      oeil[i][j]=1;
    }
  }
}

void symetrie_centrale_2(char oeil[GF][GF])
{
  int i,j;

  for(i=0;i<GF;i++)
  {
    for(j=0;j<GF;j++)
    {
      oeil[31-i][31-j]=oeil[i][j];
    }
  }
}

void symetrie_centrale_4(char oeil[GF][GF])
{
  int i,j;

  for(i=0;i<GF/2;i++)
  {
    for(j=0;j<GF/2;j++)
    {
      oeil[i][31-j]=oeil[i][j];
      oeil[31-i][j]=oeil[i][j];
      oeil[31-i][31-j]=oeil[i][j];
    }
  }
}

void symetrie_axiale_2(char oeil[GF][GF])
{
  int i,j;

  for(i=0;i<GF;i++)
  {
    for(j=0;j<GF;j++)
    {
      oeil[i][31-j]=oeil[i][j];
    }
  }
}

void inversion_matrice(char oeil[GF][GF])
{
  int i,j;

  for(i=0;i<GF;i++)
  {
    for(j=0;j<GF;j++)
    {
      if(oeil[i][j]==0)
      {
        oeil[i][j]=1;
      }
      else
      {
        oeil[i][j]=0;
      }
    }
  }
}

void remplissage_ligne(char oeil[GF], int debut, int fin)
{
  int i;
  for(i=debut;i<=fin;i++)
  {
    oeil[i]=1;
  }
}

void affichage_matrice(char oeil[GF][GF])
{
  int i,j;
  printf("\n\n");
  for(i=0;i<GF;i++)
  {
    for(j=0;j<GF;j++)
    {
      switch(oeil[i][j])
      {
        case 1 : printf("()"); break;
        case 0 : printf("  "); break;
      }
    }
    printf("\n");
  }
  printf("\n\n");
}

void quart_cercle(char oeil[GF][GF])
{
    int i,j;

    for(i=1;i<(GF/2);i++)
    {
      switch(i)
      {
        case 1 : for(j=8;j<16;j++) oeil[i][j]=1; break;
        case 2 : for(j=8;j<16;j++) oeil[i][j]=1; break;

        case 3 : for(j=6;j<11;j++) oeil[i][j]=1; break;
        case 4 : for(j=6;j<11;j++) oeil[i][j]=1; break;

        case 5 : for(j=5;j<7;j++) oeil[i][j]=1; break;

        case 6 : for(j=3;j<7;j++) oeil[i][j]=1; break;

        case 7 : for(j=3;j<5;j++) oeil[i][j]=1; break;
        case 8 : for(j=3;j<5;j++) oeil[i][j]=1; break;

        case 9 : for(j=1;j<5;j++) oeil[i][j]=1; break;
        case 10 : for(j=1;j<5;j++) oeil[i][j]=1; break;

        default : for(j=1;j<3;j++) oeil[i][j]=1; break;
      }
    }
}

void iris_cercle(char oeil[GF][GF],int centre_i,int centre_j, int type_iris)
{
  int i,j;
  switch(type_iris)
  {
      case 1 :
      for(i=centre_i-4;i<=centre_i+5;i++)
      {
        if(i==centre_i-4||i==centre_i+5)
        {
          for(j=centre_j-1;j<=centre_j+2;j++) oeil[i][j]=1;
        }
        if(i==centre_i-3||i==centre_i+4)
        {
          for(j=centre_j-2;j<=centre_j+3;j++) oeil[i][j]=1;
        }
        if(i==centre_i-2||i==centre_i+3)
        {
          for(j=centre_j-3;j<=centre_j+4;j++) oeil[i][j]=1;
        }
        if(i==centre_i-1||i==centre_i+2)
        {
          for(j=centre_j-4;j<=centre_j+5;j++) oeil[i][j]=1;
        }
        if(i==centre_i||i==centre_i+1)
        {
          for(j=centre_j-4;j<=centre_j+5;j++) oeil[i][j]=1;
        }
      }
      break;

      case 2 :
      for(i=centre_i-4;i<=centre_i+5;i++)
      {
        if(i==centre_i-4||i==centre_i+5)
        {
          for(j=centre_j-1;j<=centre_j+2;j++) oeil[i][j]=1;
        }
        if(i==centre_i-3||i==centre_i+4)
        {
          for(j=centre_j-2;j<=centre_j-1;j++) oeil[i][j]=1; for(j=centre_j+2;j<=centre_j+3;j++) oeil[i][j]=1;
        }
        if(i==centre_i-2||i==centre_i+3)
        {
          for(j=centre_j-3;j<=centre_j-1;j++) oeil[i][j]=1; for(j=centre_j+2;j<=centre_j+4;j++) oeil[i][j]=1;
        }
        if(i==centre_i-1||i==centre_i+2)
        {
          for(j=centre_j-4;j<=centre_j-3;j++) oeil[i][j]=1; for(j=centre_j+4;j<=centre_j+5;j++) oeil[i][j]=1;
        }
        if(i==centre_i||i==centre_i+1)
        {
          for(j=centre_j-4;j<=centre_j-3;j++) oeil[i][j]=1; for(j=centre_j+4;j<=centre_j+5;j++) oeil[i][j]=1;
        }
      }
      break;

      case 3 :
      for(i=centre_i-4;i<=centre_i+5;i++)
      {
        if(i==centre_i-4||i==centre_i+5)
        {
          for(j=centre_j;j<=centre_j+1;j++) oeil[i][j]=1;
        }
        if(i==centre_i-3||i==centre_i+4)
        {
          for(j=centre_j-1;j<=centre_j+2;j++) oeil[i][j]=1;
        }
        if(i==centre_i-2||i==centre_i+3)
        {
          for(j=centre_j-1;j<=centre_j+2;j++) oeil[i][j]=1;
        }
        if(i==centre_i-1||i==centre_i+2)
        {
          for(j=centre_j-2;j<=centre_j+3;j++) oeil[i][j]=1;
        }
        if(i==centre_i||i==centre_i+1)
        {
          for(j=centre_j-2;j<=centre_j+3;j++) oeil[i][j]=1;
        }
      }
      break;
  }
}

void oeil_complet_xy(char oeil[GF][GF], int centre_i, int centre_j, int type_iris)
{
  mise_zero_oeil(oeil);
  contour_oeil(oeil);
  symetrie_centrale_2(oeil);
  iris_cercle(oeil,centre_i,centre_j,type_iris);
}

void contour_oeil(char oeil[GF][GF])
{
  int i,j;


  for(i=0;i<GF;i++)
  {
    switch(i)
    {
      case 0 :
      for(j=0;j<2;j++) oeil[i][j]=1; break;

      case 1 :
      for(j=0;j<4;j++) oeil[i][j]=1; break;

      case 2 :
      for(j=1;j<19;j++) oeil[i][j]=1; break;

      case 3 :
      for(j=1;j<22;j++) oeil[i][j]=1; break;

      case 4 :
      for(j=2;j<23;j++) oeil[i][j]=1; break;

      case 5 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=15;j<24;j++) oeil[i][j]=1; break;

      case 6 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=18;j<25;j++) oeil[i][j]=1; break;

      case 7 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=19;j<26;j++) oeil[i][j]=1; break;

      case 8 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=20;j<27;j++) oeil[i][j]=1; break;

      case 9 :
      for(j=2;j<4;j++) oeil[i][j]=1;  for(j=20;j<28;j++) oeil[i][j]=1; break;

      case 10 :
      for(j=2;j<4;j++) oeil[i][j]=1;  for(j=22;j<28;j++) oeil[i][j]=1; break;

      case 11 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=23;j<29;j++) oeil[i][j]=1; break;

      case 12 :
      for(j=2;j<5;j++) oeil[i][j]=1; for(j=23;j<29;j++) oeil[i][j]=1; break;

      case 13 :
      for(j=2;j<5;j++) oeil[i][j]=1; for(j=24;j<29;j++) oeil[i][j]=1; break;

      case 14 :
      for(j=2;j<6;j++) oeil[i][j]=1; for(j=24;j<30;j++) oeil[i][j]=1; break;

      case 15 :
      for(j=2;j<6;j++) oeil[i][j]=1; for(j=25;j<30;j++) oeil[i][j]=1; break;
    }
  }
}

void deplace_iris_choisi(char oeil[GF][GF], int centre, int type_iris)
{
    iris_cercle(oeil,centre,centre,type_iris);
}

void oeil_complet(char oeil[GF][GF], int centre, int type_iris)
{
  mise_zero_oeil(oeil);
  contour_oeil(oeil);
  symetrie_centrale_2(oeil);
  deplace_iris_choisi(oeil,centre,type_iris);
}

void iris_centre(char oeil[GF][GF])
{
  int i,j;


  for(i=0;i<GF;i++)
  {
    switch(i)
    {
      case 9 :
      for(j=12;j<20;j++) oeil[i][j]=1; break;

      case 10 :
      oeil[i][11]=1; oeil[i][20]=1; break;

      case 11 :
      oeil[i][10]=1; oeil[i][21]=1; break;

      case 12 :
      oeil[i][9]=1; oeil[i][22]=1; break;

      case 13 :
      oeil[i][9]=1; for(j=14;j<18;j++) oeil[i][j]=1; oeil[i][22]=1; break;

      case 14 :
      oeil[i][9]=1; oeil[i][13]=1; oeil[i][18]=1; oeil[i][22]=1; break;

      case 15 :
      oeil[i][9]=1; oeil[i][13]=1; oeil[i][15]=1; oeil[i][16]=1; oeil[i][18]=1; oeil[i][22]=1; break;


      case 16 :
      oeil[i][9]=1; oeil[i][13]=1; oeil[i][15]=1; oeil[i][16]=1; oeil[i][18]=1; oeil[i][22]=1; break;

      case 17 :
      oeil[i][9]=1; oeil[i][13]=1; oeil[i][18]=1; oeil[i][22]=1; break;

      case 18 :
      oeil[i][9]=1; for(j=14;j<18;j++) oeil[i][j]=1; oeil[i][22]=1; break;

      case 19 :
      oeil[i][10]=1; oeil[i][22]=1; break;

      case 20 :
      oeil[i][11]=1; oeil[i][21]=1; break;

      case 21 :
      oeil[i][12]=1; oeil[i][20]=1; break;

      case 22 :
      for(j=12;j<20;j++) oeil[i][j]=1; break;
    }
  }
}

void iris_centre_droit(char oeil[GF][GF])
{
  int i,j;

  for(i=12;i<26;i++)
  {
    switch(i)
    {
      case 12 :  for(j=15;j<23;j++) oeil[i][j]=1; break;

      case 13 :  oeil[i][14]=1; oeil[i][23]=1; break;

      case 14 :  oeil[i][13]=1; oeil[i][24]=1; break;

      case 15 :  oeil[i][12]=1; oeil[i][25]=1; break;

      case 16 :  oeil[i][12]=1; for(j=17;j<21;j++) oeil[i][j]=1; oeil[i][25]=1; break;

      case 17 :  oeil[i][12]=1; oeil[i][16]=1; oeil[i][21]=1; oeil[i][25]=1; break;

      case 18 :  oeil[i][12]=1; oeil[i][16]=1; for(j=18;j<20;j++) oeil[i][j]=1; oeil[i][21]=1; oeil[i][25]=1; break;

      case 19 :  oeil[i][12]=1; oeil[i][16]=1; for(j=18;j<20;j++) oeil[i][j]=1; oeil[i][21]=1; oeil[i][25]=1; break;

      case 20 :  oeil[i][12]=1; oeil[i][16]=1; oeil[i][21]=1; oeil[i][25]=1; break;

      case 21 :  oeil[i][12]=1; for(j=17;j<21;j++) oeil[i][j]=1; oeil[i][25]=1; break;

      case 22 :  oeil[i][13]=1; oeil[i][24]=1; break;

      case 23 :  oeil[i][14]=1; oeil[i][23]=1; break;

      case 24 :  for(j=15;j<23;j++) oeil[i][j]=1; break;

    }
  }
}

void iris_droite(char oeil[GF][GF])
{
  int i,j;

  for(i=16;i<26;i++)
  {
    switch(i)
    {
      case 16 :  for(j=19;j<26;j++) oeil[i][j]=1; break;

      case 17 :  oeil[i][18]=1; break;

      case 18 :  oeil[i][17]=1; break;

      case 19 :  oeil[i][16]=1; break;

      case 20 :  oeil[i][16]=1; for(j=21;j<25;j++) oeil[i][j]=1; break;

      case 21 :  oeil[i][16]=1; oeil[i][20]=1; oeil[i][25]=1; break;

      case 22 :  oeil[i][16]=1; oeil[i][20]=1; for(j=22;j<24;j++) oeil[i][j]=1; oeil[i][25]=1; break;

      case 23 :  oeil[i][16]=1; oeil[i][20]=1; for(j=22;j<24;j++) oeil[i][j]=1; oeil[i][25]=1; break;

      case 24 :  oeil[i][16]=1; oeil[i][20]=1; oeil[i][25]=1; break;

      case 25 :  oeil[i][16]=1; for(j=21;j<25;j++) oeil[i][j]=1; break;
    }
  }
}

void oeil_ouvert(char oeil[GF][GF])
{
  int i,j;


  for(i=0;i<GF;i++)
  {
    switch(i)
    {
      case 0 :
      for(j=0;j<2;j++) oeil[i][j]=1; break;

      case 1 :
      for(j=0;j<4;j++) oeil[i][j]=1; break;

      case 2 :
      for(j=1;j<19;j++) oeil[i][j]=1; break;

      case 3 :
      for(j=1;j<13;j++) oeil[i][j]=1; for(j=19;j<22;j++) oeil[i][j]=1; break;

      case 4 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=12;j<16;j++) oeil[i][j]=1; oeil[i][22]=1; break;

      case 5 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=15;j<18;j++) oeil[i][j]=1; oeil[i][23]=1; break;

      case 6 :
      for(j=2;j<4;j++) oeil[i][j]=1; oeil[i][18]=1; oeil[i][24]=1; break;

      case 7 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=19;j<21;j++) oeil[i][j]=1; oeil[i][25]=1; break;

      case 8 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=20;j<22;j++) oeil[i][j]=1; oeil[i][26]=1; break;

      case 9 :
      for(j=2;j<4;j++) oeil[i][j]=1; for(j=12;j<20;j++) oeil[i][j]=1; for(j=20;j<22;j++) oeil[i][j]=1; oeil[i][26]=1; break;

      case 10 :
      for(j=2;j<4;j++) oeil[i][j]=1; oeil[i][11]=1; oeil[i][20]=1; oeil[i][22]=1; oeil[i][27]=1; break;

      case 11 :
      oeil[i][2]=1; oeil[i][4]=1; oeil[i][10]=1; oeil[i][21]=1; oeil[i][23]=1; oeil[i][27]=1; break;

      case 12 :
      oeil[i][2]=1; oeil[i][4]=1; oeil[i][9]=1; oeil[i][22]=1; oeil[i][23]=1; oeil[i][27]=1; break;

      case 13 :
      oeil[i][2]=1; oeil[i][4]=1; oeil[i][9]=1; for(j=14;j<18;j++) oeil[i][j]=1; oeil[i][22]=1; oeil[i][24]=1; oeil[i][28]=1; break;

      case 14 :
      oeil[i][2]=1; oeil[i][5]=1; oeil[i][9]=1; oeil[i][13]=1; oeil[i][18]=1; oeil[i][22]=1; oeil[i][24]=1; oeil[i][28]=1; break;

      case 15 :
      oeil[i][2]=1; oeil[i][5]=1; oeil[i][9]=1; oeil[i][13]=1; oeil[i][15]=1; oeil[i][16]=1; oeil[i][18]=1; oeil[i][22]=1; oeil[i][25]=1; oeil[i][28]=1;
      break;

      case 16 :
      oeil[i][3]=1; oeil[i][6]=1; oeil[i][9]=1; oeil[i][13]=1; oeil[i][15]=1; oeil[i][16]=1; oeil[i][18]=1; oeil[i][22]=1; oeil[i][25]=1; oeil[i][28]=1;
      break;

      case 17 :
      oeil[i][3]=1; oeil[i][6]=1; oeil[i][9]=1; oeil[i][13]=1; oeil[i][18]=1; oeil[i][22]=1; oeil[i][26]=1; oeil[i][28]=1; break;

      case 18 :
      oeil[i][3]=1; oeil[i][7]=1; oeil[i][9]=1; for(j=14;j<18;j++) oeil[i][j]=1; oeil[i][22]=1; oeil[i][26]=1; oeil[i][28]=1; break;

      case 19 :
      oeil[i][4]=1; for(j=7;j<10;j++) oeil[i][j]=1; oeil[i][22]=1; for(j=26;j<29;j++) oeil[i][j]=1; break;

      case 20 :
      oeil[i][5]=1; for(j=8;j<11;j++) oeil[i][j]=1; oeil[i][21]=1; for(j=27;j<29;j++) oeil[i][j]=1; break;

      case 21 :
      oeil[i][5]=1; for(j=9;j<12;j++) oeil[i][j]=1; oeil[i][20]=1; for(j=27;j<30;j++) oeil[i][j]=1; break;

      case 22 :
      oeil[i][6]=1; for(j=10;j<20;j++) oeil[i][j]=1; for(j=27;j<30;j++) oeil[i][j]=1; break;

      case 23 :
      oeil[i][7]=1; for(j=11;j<13;j++) oeil[i][j]=1; for(j=28;j<30;j++) oeil[i][j]=1; break;

      case 24 :
      oeil[i][8]=1; oeil[i][13]=1; for(j=28;j<30;j++) oeil[i][j]=1;break;

      case 25 :
      for(j=9;j<11;j++) oeil[i][j]=1; for(j=14;j<16;j++) oeil[i][j]=1; for(j=28;j<30;j++) oeil[i][j]=1; break;

      case 26 :
      for(j=10;j<12;j++) oeil[i][j]=1; for(j=16;j<18;j++) oeil[i][j]=1; for(j=28;j<30;j++) oeil[i][j]=1; break;

      case 27 :
      for(j=12;j<15;j++) oeil[i][j]=1; for(j=17;j<20;j++) oeil[i][j]=1; for(j=28;j<30;j++) oeil[i][j]=1; break;

      case 28 :
      for(j=15;j<18;j++) oeil[i][j]=1; for(j=20;j<31;j++) oeil[i][j]=1; break;

      case 29 :
      for(j=18;j<31;j++) oeil[i][j]=1; break;

      case 30 :
      for(j=28;j<32;j++) oeil[i][j]=1; break;

      case 31 :
      for(j=30;j<32;j++) oeil[i][j]=1; break;

    }
  }
}

void demi_crane(char oeil[GF][GF])
{
  int i,j;

  for(i=0;i<GF;i++)
  {
    switch(i)
    {
      case 1 : for(j=10;j<=15;j++) oeil[i][j]=1; break;

      case 2 : for(j=8;j<=15;j++) oeil[i][j]=1; break;

      case 3 : for(j=7;j<=8;j++) oeil[i][j]=1; break;

      case 4 : for(j=6;j<=7;j++) oeil[i][j]=1; break;

      case 5 : for(j=7;j<=11;j++) oeil[i][j]=1; break;

      case 6 : for(j=7;j<=12;j++) oeil[i][j]=1; break;

      case 7 : for(j=10;j<=14;j++) oeil[i][j]=1; break;

      case 8 : for(j=9;j<=11;j++) oeil[i][j]=1; break;

      case 9 : for(j=8;j<=12;j++) oeil[i][j]=1; break;

      case 10 : for(j=8;j<=12;j++) oeil[i][j]=1; break;

      case 11 : for(j=8;j<=12;j++) oeil[i][j]=1; break;

      case 12 : for(j=9;j<=11;j++) oeil[i][j]=1; break;

      case 13 : for(j=6;j<=7;j++) oeil[i][j]=1; break;

      case 14 : for(j=8;j<=11;j++) oeil[i][j]=1; break;

      case 17 : for(j=6;j<=7;j++) oeil[i][j]=1; oeil[i][11]=1; break;

      case 18 : oeil[i][10]=1; break;

      case 19 : for(j=7;j<=9;j++) oeil[i][j]=1; break;

      case 20 : oeil[i][10]=1; break;

      case 21 : for(j=11;j<=15;j++) oeil[i][j]=1; break;

    }
  }
  for(j=5;j<GF/2;j++)
  {
    switch(j)
    {
      case 5 : for(i=5;i<=11;i++) oeil[i][j]=1; break;

      case 6 : for(i=4;i<=17;i++) oeil[i][j]=1; break;

      case 7 : for(i=17;i<=19;i++) oeil[i][j]=1; break;

      //case 9 : for(j=21;j<=26;j++) oeil[i][j]=1; break;

      //case 10 : for(j=23;j<=27;j++) oeil[i][j]=1; break;

      case 12 : for(i=19;i<=21;i++) oeil[i][j]=1; break;

      case 14 : for(i=19;i<=21;i++) oeil[i][j]=1; for(i=14;i<=16;i++) oeil[i][j]=1; break;

      case 15 : for(i=13;i<=15;i++) oeil[i][j]=1; break;
    }
  }

  oeil[9][10]=0;
  oeil[10][9]=0;
  oeil[10][10]=0;
  oeil[10][11]=0;
  oeil[11][10]=0;
}

void demi_machoire(char oeil[GF][GF], int position)
{
  int i,j;

  for(i=21+position;i<=26+position;i++) oeil[i][9]=1;

  for(i=23+position;i<=27+position;i++) oeil[i][10]=1;

  for(i=25+position;i<=28+position;i++)
  {
    for(j=11;j<=15;j++)
    {
      oeil[i][j]=1;
    }
  }

  oeil[26+position][12]=0;
  oeil[26+position][14]=0;
  for(j=11;j<=15;j++) oeil[27+position][j]=0;
}

void crane_complet(char oeil[GF][GF], int position)
{
  mise_zero_oeil(oeil);
  demi_crane(oeil);
  demi_machoire(oeil,position);
  symetrie_axiale_2(oeil);
}

void animation(char oeil[GF][GF], char f)
{

  if((f>=0&&f<=15)||(f>=32&&f<=47))
  {
    oeil_complet(oeil,(f%16)+8,3);
  }
  if((f>=16&&f<=31)||(f>=48&&f<=53))
  {
    oeil_complet(oeil,23-(f%16),3);
  }
  /*if((f>=54&&f<=69)||(f>=86&&f<=102))
  {
    oeil_complet_xy(oeil,(f%16)+8,15,3);
  }
  if(f>=70&&f<=85)
  {
    oeil_complet_xy(oeil,23-(f%16),15,3);
  }*/
  if(f>=54&&f<=61)
  {
    oeil_complet_xy(oeil,(f%16)+8,15,3);
  }
  if(f>=64&&f<=79)
  {
    oeil_complet_xy(oeil,23-(f%16),15,3);
  }
  if(f>=80&&f<=87)
  {
    oeil_complet_xy(oeil,(f%16)+8,15,3);
  }
  switch(f)
  {
    case 88 : crane_complet(oeil,-2); break ;
    case 89 : crane_complet(oeil,-1); break ;
    case 90 : crane_complet(oeil,0); break ;
    case 91 : crane_complet(oeil,1); break ;
    case 92 : crane_complet(oeil,2); break ;
    case 93 : crane_complet(oeil,1); break ;
    case 94 : crane_complet(oeil,0); break ;
    case 95 : crane_complet(oeil,-1); break ;
    case 96 : crane_complet(oeil,-2); break ;
    case 97 : crane_complet(oeil,-1); break ;
    case 98 : crane_complet(oeil,0); break ;
    case 99 : crane_complet(oeil,1); break ;
    case 100 : crane_complet(oeil,2); break ;
    case 101 : crane_complet(oeil,1); break ;
    case 102 : crane_complet(oeil,0); break ;
    case 103 : crane_complet(oeil,-1); break ;
    case 104 : crane_complet(oeil,-2); break ;
    case 105 : crane_complet(oeil,-1); break ;
    case 106 : crane_complet(oeil,0); break ;
    case 107 : crane_complet(oeil,1); break ;
    case 108 : crane_complet(oeil,2); break ;
    case 109 : crane_complet(oeil,1); break ;
    case 110 : crane_complet(oeil,0); break ;
    case 111 : crane_complet(oeil,-1); break ;
    case 112 : crane_complet(oeil,-2); break ;




  }
}
