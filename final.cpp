#include<iostream>
#include<cstdlib>
#include<time.h>
#include<math.h>
using namespace std;
int* message_passing(int **h,int n ,int k,int *r) 
{
	int max=0,max2=0;
	int temp=0;
	int i,j;
	for(i=0;i<n-k+1;i++)
	{
		temp=0;
		for(j=0;j<n;j++)
		{
			if(h[i][j]==1)
			{
				temp++;			
			}
		}	
		if(max<temp)
		{
			max=temp;
		}
	}
	for(j=0;j<n;j++)
	{
		temp=0;
		for(i=0;i<n-k+1;i++)
		{
			if(h[i][j]==1)
			{
				temp++;			
			}
		}
		if(max2<temp)
		{
			max2=temp;
		}
	}
	int cn[n-k+1][max]={{0}},vn[n][max2+1]={{0}},z=0,mvn[n]={0};
	for(i=0;i<n;i++)
	{
		for(j=0;j<max2+1;j++)
		{
			vn[i][j]=-1;
		}
	}
	cout<<endl<<endl<<"*"<<endl<<endl;
	for(i=0;i<n-k+1;i++)
	{
		z=0;
		for(j=0;j<n;j++)
		{
			if(h[i][j]==1)
			{
				cn[i][z]=j;
				z++;		
			}
		}	
	}

	for(i=0;i<n;i++)
	{
		vn[i][0]=r[i];
	}
	for(j=0;j<n;j++)
	{
		z=1;
		for(i=0;i<n-k+1;i++)
		{
			if(h[i][j]==1)
			{
				vn[j][z]=i;
				z++;
			}
		}
	}
	cout<<endl<<"****Variable Nodes****"<<endl;
	for(i=0;i<n;i++)
	{
		for(j=0;j<max2+1;j++)
		{
			cout<<vn[i][j]<<" ";
		}
		cout<<endl;
	}
	int flag=0,c1=0,c2=0,cnt=0,l3=0;
	while(cnt<=100 && flag==0)
	{
		cnt++;
		flag=1;
		for(i=0;i<n;i++)
		{
			c1=0,c2=0;
			if(vn[i][0]==1)
			{
				c1++;
			}
			else
			{
				c2++;
			}
			for(j=1;j<max2+1;j++)
			{
				if(vn[i][j]!=-1)
				{
					temp=0;
					for(l3=0;l3<max;l3++)
					{
						if(cn[vn[i][j]][l3]!=i)
						{
							temp=temp+vn[cn[vn[i][j]][l3]][0];
						}
					}
					if(temp%2!=0)
					{
						c1++;
					}
					else
					{
						c2++;
					}
				}
				else
				break;	
			}
			if(c1>c2)
			{
				mvn[i]=1;
			}
			else if(c2>c1)
			{
				mvn[i]=0;
			}
			else 
			{	
				if(vn[i][0]==0)
				mvn[i]=1;
				else
				mvn[i]=0;
			}
		}	
		for(z=0;z<n;z++)
		{
			if(vn[z][0]!=mvn[z])
			flag=0;
		}
		for(z=0;z<n;z++)
		{
			vn[z][0]=mvn[z];
		}
		for(z=0;z<n;z++)
		{
			if(vn[z][0]!=r[z])
			break;
		}
		if(z>=n)
		flag=1;
	}
	int *d=new int[n];
	for(i=0;i<n;i++)
	{
		d[i]=vn[i][0];
	}
	return (d);
}
int **H_matrix(int n,int k)
{
	int **h=new int*[n-k+1];
	int i,j;
	int root_n=sqrt(n);
	for(i=0;i<n-k+1;i++)
	{
		h[i]=new int[n];
	}
	
	int temp3=0;
	int temp2=0;
	int temp=0;
	for(i=0;i<n-k+1;i++)
	{
		for(j=0;j<n;j++)
		{
			h[i][j]=0;
		}
		
	}
	for(i=0;i<n-k+1;i++)
	{
		if(temp<root_n)
		{
			for(j=0;j<root_n;j++)
			{
				h[i][temp2]=1;
				temp2++;
			}
		}
		else
		{
			for(j=temp3;j<n;j=j+root_n)
			{
				h[i][j]=1;
			}
			temp3++;
		}
		temp++;
	}
	return (h);
}

int* BSC(int c[],int n,float pr) 
{
	cout<<"\n***ERROR VECTOR***\n";
	int *e=new int[n];
	int i;
		float rndm ;
		for(i=0;i<n;i++)
		{
			rndm=rand()/(double)RAND_MAX;
			 //rndm= (float)((rand())/(float)RAND_MAX);
			if(rndm>pr)
			{
				e[i]=0;
			}	
			else
			{
				e[i]=1;
			}
			cout<<e[i]<<" ";
		}
	//RECEIVED CODEWORD 
	int *r=new int[n];
	
	for(i=0;i<n;i++)
	{
		r[i]=(c[i]+e[i])%2;
		
	}
	return (r);	
} 
int ** Generator_matrix(int n,int k)
{
	int o=sqrt(k);
	int **g=new int*[n],p=0;
	for(int i=0;i<n;i++)
	{
		g[i]=new int[k];
	}
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<k;j++)
		{
			g[i][j]=0;
		}
	}
	int temp=0;
	int temp2=0;
	for(i=0;i<n;i++)
	{
		if(((i+1)%(o+1)==0)||i>=(o*sqrt(n)))
		{ 
		 	if(((i+1)%(o+1)==0)&&(i<(o*sqrt(n))))
		 	{
		 		for(int l=0;l<o;l++)
		 		{
		 			g[i][temp]=1;
		 			temp++;
				}
			}
			else if(i!=n-1)
			{
				for(int r=temp2;r<k;r=r+o)
				{
					g[i][r]=1;
				}
				temp2++;
			}
			else
			{
				for(int r=0;r<k;r++)
				{
					g[n-1][r]=1;
				}
			}
		}
		else
		{
			for(j=0;j<k;j++)
			{		
				if(p==j)
				{	
					g[i][j]=1;
			
				}
				else
				{
					g[i][j]=0;
				}	
			}
			p++;
		}
	}
	return g;

}
int ** Paritycheck(int n,int k)
{
	int **h=new int*[n-k];
	int i,j,root_n=sqrt(n),o=sqrt(k);
	for( i=0;i<n-k;i++)
	{
		h[i]=new int[n];
	}
	int temp=0;
	int temp2=0;
	int temp3=0;
	for(i=0;i<n-k;i++)
	{
		for(j=0;j<n;j++)
		{
			h[i][j]=0;
		}
		
	}
	for(i=0;i<n-k;i++)
	{
		if(temp<o)
		{
			for(j=0;j<root_n;j++)
			{
				h[i][temp2]=1;
				temp2++;
			}
		}
		else
		{
			for(j=temp3;j<n;j=j+root_n)
			{
				h[i][j]=1;
			}
			temp3++;
		}
		temp++;
	}
	return h;
}
int* codeword_bit(int** g,int* m,int n,int k)
{
	int i,j;
	int *c=new int[n];
	for(i=0;i<n;i++)
	{
		c[i]=0;
		for(j=0;j<k;j++)
		{
			c[i]=c[i]+(g[i][j]*m[j]);
		}
		c[i]=c[i]%2;
	}
	return c;
}
int* BEC_received(int n,float probab,int c[])
{
	int i;
	int *e=new int[n];
	float rndm;
	for(i=0;i<n;i++)
	{
		rndm=rand()/(double)RAND_MAX;
		if(rndm>probab)
		{
			e[i]=0;
		}	
		else
		{
			e[i]=1;
		}
	}
	cout<<endl<<endl;
	cout<<"***ERROR VECTOR***"<<endl;
	for(i=0;i<n;i++)
	{
		cout<<e[i]<<" ";
	}
	int* r=new int[n] ;
	for(i=0;i<n;i++)
	{
		if(e[i]==1)
		{
			r[i]=-1;
		}
		else
		{
			r[i]=c[i];
		}
	}
	return r;
}
int* bec_decoder(int n,int k,int* r)
{
	int **h=Paritycheck(n,k);
	int max=0,max2=0;
	int i,j;
	int temp=0;
	for(i=0;i<n-k;i++)
	{
		temp=0;
		for(j=0;j<n;j++)
		{
			if(h[i][j]==1)
			{
				temp++;			
			}
		}	
		if(max<temp)
		{
			max=temp;
		}
	}
	for(j=0;j<n;j++)
	{
		temp=0;
		for(i=0;i<n-k;i++)
		{
			if(h[i][j]==1)
			{
				temp++;			
			}
		}
		if(max2<temp)
		{
			max2=temp;
		}
	}
	int cn[n-k][max]={{0}},vn[n][max2+1]={{0}},z=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<max2+1;j++)
		{
			vn[i][j]=-1;
		}
	}
	for(i=0;i<n-k;i++)
	{
		z=0;
		for(j=0;j<n;j++)
		{
			if(h[i][j]==1)
			{
				cn[i][z]=j;
				z++;		
			}
		}	
	}
	cout<<endl;

	for(i=0;i<n-k;i++)
	{
		
		for(j=0;j<max;j++)
		{
		//	cout<<cn[i][j]<<"\t";
		}
	//	cout<<endl;
	}
	for(i=0;i<n;i++)
	{
		vn[i][0]=r[i];
	}
	for(j=0;j<n;j++)
	{
		z=1;
		for(i=0;i<n-k;i++)
		{
			if(h[i][j]==1)
			{
				vn[j][z]=i;
				z++;
			}
		}
	}
	int flag=0,cnt=0;
	while(flag==0)
	{
		flag=1;
		for(i=0;i<n;i++)
		{
			if(vn[i][0]==-1)
			{
				for(j=1;j<max2+1;j++)
				{
					if(vn[i][j]!=-1)
					{
						temp=0;
					for(k=0;k<max;k++)
					{
						if(cn[vn[i][j]][k]!=i)
						{
							if(vn[cn[vn[i][j]][k]][0]==-1)
							{
								break;
							}
							else
							{
								temp=temp+vn[cn[vn[i][j]][k]][0];
							}
					
						}
					}
					if(k>=max)
					{
						vn[i][0]=temp%2;
						flag=0;
						break;
					}
					}
				}
			}
			
		}
		cnt++;
		
	}
	int *d=new int[n];
	for(i=0;i<n;i++)
	{
		d[i]=vn[i][0];
	}
	return d;
}
int main()
{
	srand(time(0));
	int i,j,k,n,o;
	while(1>0)
	{
		cout<<"ENTER THE VALUE OF k "<<endl;
		cin>>k;
		float x;
		x=sqrt(k);
		o=floor(x);
		if(o-x==0)
		{
			break;
		}
	}
	n=k+1+2*o;
	int root_n=sqrt(n);
	int m[k]={0};
	cout<<"ENTER MESSAGE BITS "<<endl;
/*	for(i=0;i<k;i++)
	{
		cin>>m[i];
	}*/
//GENERATOR MATRIX
	int **g=Generator_matrix(n,k);
	//cout<<"*****GENERATOR MATRIX*****"<<endl;
	/*for(i=0;i<n;i++)
	{
		for(j=0;j<k;j++)
		{
			cout<<g[i][j]<<" ";
		}
		cout<<"\n";
	}*/
//CODEWORD BITS
cout<<endl<<endl<<endl;
int *c=codeword_bit(g,m,n,k);
while(1>0)
{
	int choice;
	cout<<"\n";
	cout<<"0) EXIT"<<endl;
	cout<<"1) BEC CHANNEL"<<endl;
	cout<<"2) BSC CHANNEL"<<endl;
	cout<<"\nENTER YOUR CHOICE::";
	cin>>choice;
	if(choice==1)
	{
		cout<<"\n*****PARITY CHECK MATRIX*****"<<endl;
		int **h=Paritycheck(n,k);
	/*	for(i=0;i<n-k;i++)
		{
			for(j=0;j<n;j++)
			{
				cout<<h[i][j]<<" ";
			}
			cout<<"\n";
		}*/
		
		cout<<"ENTER THE VALUE OF PROBABILITY"<<endl;
		float probab;
		cin>>probab;
		int *r=BEC_received(n,probab,c);
		cout<<"\n***RECEIVED VECTOR***"<<endl;
	/*	for(i=0;i<n;i++)
		{
			if(r[i]!=-1)
			cout<<r[i]<<" ";
			else
			cout<<"E ";
		}*/
		cout<<endl;
		cout<<"*****CODEWORD BITS*****"<<endl;
/*		for(i=0;i<n;i++)
		{
			cout<<c[i]<<" ";
		}
*/
		int *d=bec_decoder(n,k,r),z=0;
		cout<<"\n***DECODED VECTOR***\n";
		for(i=0;i<n;i++)
		{
			if(d[i]==-1)
			z++;
		
		}
		cout<<"#"<<z;
	}
	else if(choice==2)
	{
		
		int **h=H_matrix(n,k);
		cout<<"\n*****PARITY CHECK MATRIX*****"<<endl;
		for(i=0;i<n-k+1;i++)
		{
			for(j=0;j<n;j++)
			{
				cout<<h[i][j]<<" ";
			}
			cout<<"\n";
		}
		float pr=0;
		cout<<"ENTER PROBABILITY "<<endl;
		cin>>pr;
		int *r=BSC(c,n,pr);	
		cout<<"\n***RECEIVED VECTOR***"<<endl;
		for(i=0;i<n;i++)
		{
			cout<<r[i]<<" ";
		}
		cout<<endl;
		cout<<"*****CODEWORD BITS*****"<<endl;
		for(i=0;i<n;i++)
		{
			cout<<c[i]<<" ";
		}
		int *d=message_passing(h,n ,k,r);
		cout<<"\n***DECODED VECTOR***\n";
		for(i=0;i<n;i++)
		{
			cout<<d[i]<<" ";
		}	
	}
	else if(choice==0)
	{
		break;
	}
}
}
