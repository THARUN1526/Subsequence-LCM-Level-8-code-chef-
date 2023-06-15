#include<stdio.h>
#include<math.h>
int main(void)
{
  int t,n,i,j,max,z,q,max1;
  scanf("%d",&t);
  for(i=0;i<t;i++)
  {
      int c=0;
      int m=0;
     scanf("%d",&n);
     int a[n];
     for(j=0;j<n;j++)
     {
        scanf("%d",&a[j]);
     }
     max=a[0];
	 for(j=0;j<n;j++)
	 {
	     if(a[j]>max)
	     {
	        max=a[j];
	     }
	 }
	 z=max+1;
	 int freq[z];
	 for(j=0;j<z;j++)
	 {
	     freq[j]=0; //frequency of elements of array.
	 }
	 for(j=0;j<n;j++)
	 {
	     freq[a[j]]++; //frequency of elements of array.
	 }
	 max1=freq[0];
	 for(j=0;j<z;j++)
	 {
	     if(freq[j]>max1) //finding maximum of frequencies.
	     {
	        max1=freq[j];
	     }
	 }
	 int u=max1+1; // maximimum of frequencies.
	 int freq2[n]; 
	 int freq3[u];
	 for(j=0;j<z;j++)
     {
        freq3[j]=0; //total combinations of elements having frequency greater than 2.
     }
     freq3[3]=4;
	 for(j=0;j<n;j++)
	 {
	     freq2[j]=0; //no of combinations of elements having frequency greater than 1 in array taking 2 elemensts at a time.
	 }
	 for(j=2;j<n+1;j++)
	 {
	        q=(j/2);
	        if(j%2==0)
	        {
	            freq2[j]=(j)*(q-1)+(q);
	        }
	        else if(j%2!=0)
	        {
	            freq2[j]=(j)*(q);
	        }
	 }
     //printf("%d\n",freq[2]);
	 for(j=0;j<n;j++)
	 {
	     int e=4;
	     if((freq[a[j]])>3)
	     { 
	         if(freq3[freq[a[j]]]==0)
	         {
	            while((freq[a[j]])>=e)
	            {
	                freq3[e]=freq2[e]+freq3[e-1];
	                e++;
	            }
	         }
	     }
	 }
     if(n==1)
     {
         printf("0\n");
     }
     else
     {
        for(j=0;j<n;j++)
        {
            if(freq[a[j]]==2)
            {
                c++;
                freq[a[j]]=0;
            }
            else if(freq[a[j]]>2)
            {
                m=m+freq3[freq[a[j]]];
                freq[a[j]]=0;
            }
        } 
     }
     int b=pow(10,9);
     b=b+7;
     int total=m+c;
     printf("%d\n",(total)%(b));
  }
  return 0;
}