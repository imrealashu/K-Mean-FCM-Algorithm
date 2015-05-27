#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float center[4];
float cc[4];

int bg=0;
int csf=0;
int wm=0;
int gm=0; 
int nrows=0,ncolumns=0;
int array[500][500];
int img1[500][500];
int abc[4];
int clust_img[500][500];
int original_clust[500][500];

int k_mean_min()
{
  printf("k_mean_min() running\n");
  int i,j,min=0,t,k,t1,u;
  float sum=0,sum1=0,sum2=0,sum3=0;
  float avg=0,avg1=0,avg2=0,avg3=0;

  while(1)
  {
    for(i=0;i<nrows;i++)
    {
      for(j=0;j<ncolumns;j++)
      {
        min=abs(array[i][j]-center[0]);
        u=0;
        for(k=1;k<4;k++)
        {
          t=array[i][j]-center[k];
          t1=abs(t);
          if(t1<min)
          {
           min=t1;
           u=k;
         }
       }
       if(u==0)
       {
         sum+=array[i][j];
         bg++;
       }
       else if(u==1)
       {
         sum1+=array[i][j];
         csf++;
       }
       else if(u==2)
       {
         sum2+=array[i][j];
         wm++;
       }
       else if(u==3)
       {
         sum3+=array[i][j];
         gm++;
       }
     }
   }
   printf("\ncount loop ended\n\n");
   printf("\nBG==>%d",bg);
   printf("\nCSF==>%d",csf);
   printf("\nWM==>%d",wm);
   printf("\nGM==>%d",gm);
   avg=sum/bg;
   avg1=sum1/csf;
   avg2=sum2/wm;
   avg3=sum3/gm;

   printf("\n%f  %f  %f  %f\n", avg, avg1, avg2, avg3);
   if((abs(avg-center[0])<0.001)&&(abs(avg1-center[1])<0.001)&&(abs(avg2-center[2])<0.001)&&(abs(avg3-center[3])<0.001))
   {
    printf("\n Else exiting \n");
    break;
  }
  else{
   center[0]=avg;
   center[1]=avg1;
   center[2]=avg2;
   center[3]=avg3;
   printf("\n%f %f %f %f its specificly centers", center[0],center[1],center[2],center[3]);
 }
}
return 0;
}

int main(int argc, char * argv[]){
  if(argc != 3){
    printf("Please enter arguments 1. Original Image.pgm, 2. New Image.pgm\n");
  }else{
    FILE *fp1,*fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8;
    char a;
    char b='\n';
    char type[3];
    int i,j,x,y;
    int min=0;
    int t,u,t1,k;
    int ch,c,r,max;
    int index=0;
    int m,n,so;

    center[0]=20.0;
    center[1]=60.0;
    center[2]=120.0;
    center[3]=150.0;

    cc[0] = 20;
    cc[1] = 60;
    cc[2] = 120;
    cc[3] = 150;

    fp1=fopen(argv[1],"r");
    fp7=fopen(argv[2],"r");
    fp2=fopen("segmented.pgm","w+");
    fp3=fopen("1.pgm","w+");
    fp4=fopen("2.pgm","w+");
    fp5=fopen("3.pgm","w+");
    fp6=fopen("4.pgm","w+");
    fp8=fopen("clustered.pgm","w+");
    
    fscanf(fp7,"%s %c %d %d %d",type,&a,&c,&r,&max);
    fscanf(fp1,"%s %c %d %d %d",type,&a,&c,&r,&max);
    nrows = r;
    ncolumns = c;
    type[2]='\0';
  //printf("%d",max);
  //printf("%s\n%c\n%d\n%d\n%d",type,a,c,r,max);
    fprintf(fp2,"%s\n%c\n%d\n%d\n%d\n",type,a,c,r,max);
    fprintf(fp3,"%s\n%c\n%d\n%d\n%d\n",type,a,c,r,max);
    fprintf(fp4,"%s\n%c\n%d\n%d\n%d\n",type,a,c,r,max);
    fprintf(fp5,"%s\n%c\n%d\n%d\n%d\n",type,a,c,r,max);
    fprintf(fp6,"%s\n%c\n%d\n%d\n%d\n",type,a,c,r,max);
    fprintf(fp8,"%s\n%c\n%d\n%d\n%d\n",type,a,c,r,max);

    
    // for(m=0;m<r;m++){
    //   for(n=0;m<c;n++){
    //     fscanf(fp7,"%d",&so);
    //     original_clust[m][n]=so;
    //   }
    // }
    //printf("\n=>>>>>>>>>>%d", original_clust[100][100]);
    for(x=0;x<r;x++)
     for(y=0;y<c;y++)
     {
      fscanf(fp1,"%d",&ch );
      fscanf(fp7,"%d",&so );
      array[x][y]=ch;
      original_clust[x][y]=so;
    }
    for(x=0;x<r;x++)
     for(y=0;y<c;y++)
     {
     //printf("%d ",original_clust[x][y]);
     }
     k_mean_min();
     for(i=0;i<r;i++)
     {
      for(j=0;j<c;j++)
      {
        min=abs(array[i][j]-center[0]);
        for(k=1;k<4;k++)
        {
          t=array[i][j]-center[k];
          t1=abs(t);
          if(t1<=min)
          {
           min=t1;
           index=k;
         }
       }
       int t2=center[index];
       img1[i][j]=t2;
     }
   }
// printf("%d\n",center[i]);
   for(i=0;i<r;i++){
     for(j=0;j<c;j++){
      fprintf(fp2,"%d ", img1[i][j]);
    }
  }
  for(i=0;i<r;i++){
     for(j=0;j<c;j++){
      if(img1[i][j] == abs(center[0])){
        fprintf(fp3,"%d ", 0);
      }else{
        fprintf(fp3,"%d ", 255);
      }
    }
  }
  for(i=0;i<r;i++){
     for(j=0;j<c;j++){
      if(img1[i][j] == abs(center[1])){
        fprintf(fp4,"%d ", 0);
      }else{
        fprintf(fp4,"%d ", 255);
      }
    }
  }
  for(i=0;i<r;i++){
     for(j=0;j<c;j++){
      if(img1[i][j] == abs(center[2])){
        fprintf(fp5,"%d ", 0);
      }else{
        fprintf(fp5,"%d ", 255);
      }
    }
  }
  for(i=0;i<r;i++){
     for(j=0;j<c;j++){
      if(img1[i][j] == abs(center[3])){
        fprintf(fp6,"%d ", 0);
      }else{
        fprintf(fp6,"%d ", 255);
      }
    }
  }
  int x1=0,x2=0,x3=0,x4=0;
  int y1=0,y2=0,y3=0,y4=0;

  for(i=0;i<r;i++){
     for(j=0;j<c;j++){
      if(img1[i][j] == abs(center[0])){
        clust_img[i][j] == 0;
        fprintf(fp8,"%d ",0);
        y1++;
      }else if(img1[i][j] == abs(center[1])){
        clust_img[i][j] == 1;
        fprintf(fp8,"%d ",1);
        y2++;
      }else if(img1[i][j] == abs(center[2])){
        clust_img[i][j] == 2;
        fprintf(fp8,"%d ",2);
        y3++;
      }else{
        clust_img[i][j] == 3;
        fprintf(fp8,"%d ",3);
        y4++;
      }
    }
  }

  int matched=0,notmatched=0;
  float result,temp,tt,tot_original, tot_segmented;  
  for(x=0;x<r;x++){
    for(y=0;y<c;y++){
      if(original_clust[x][y] == 0)
        x1++;
      else if(original_clust[x][y] == 1)
        x2++;
      else if(original_clust[x][y] == 2)
        x3++;
      else if(original_clust[x][y] ==3)
        x4++;
      else
        notmatched++;
    }
  }
  
printf("\nTotal CLustered Matched in Original: %d", x1+x2+x3+x4);
printf("\nTotal CLustered Matched in segmented: %d\n", y1+y2+y3+y4);

//tt = ((x1+x2+x3+x4)*100)/(y1+y2+y3+y4);
//printf("%.2f\n", tt);
tot_original = x1+x2+x3+x4;
tot_segmented = y1+y2+y3+y4;
temp = (tot_original/tot_segmented)*100;

printf("%.2f",temp);
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  fclose(fp4);
  fclose(fp5);
  fclose(fp6);
  fclose(fp7);
  fclose(fp8);
}
return 0;
}

