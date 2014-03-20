#include "rs_erasure.h"

// unsigned char g[]={1,185,199,211,145,4,13,169,242,158,179,8,47,227,94,108,236,94,238,83,50,131,102,25,192,28,111,81,42,237,188,120,100,183,252,104,93,19,163,137,160};//RS(255,215)
unsigned char g[]={1,28,216,183,20,100,46,36,77,36,175,43,188,156,26};//RS(255,241)
// unsigned char g[]={1,111,229,48,180,2,119,93,159,1,175,14,22,207,60,61,8,146,5,224,13,8,243,232,225,15,241,247,155,24,238,183,71,117,172,4,121,131,217,225,34,80,185,236,43,127,174,111,53,29,134,227,44,160,201,122,42,12,80,148,121,242,2,215,138,198,25,188,200,34,57,59,116,88,41,90,183,162,243,213,201,64,247,171,218,37,5,116,235,150,31,99,114,35,126,14,125,71,25,86,229,157,119,225,204,19,125,104,189,139,73,164,231,36,2,16,18,123,45,51,86,238,207,149,122,181,225,198,45,196,154,5,61,106,227,158,76,125,79,121,19,229,90,167,161,169,190,183,212,139,142,19,157,10,101,242,243,161,144,136,123,207,81,218,74,63,34,6,211,77,1};

//x=gf(1:255,8);fprintf('%d,',[0,log(x)]);
unsigned char LOG[]={0,0,1,25,2,50,26,198,3,223,51,238,27,104,199,75,4,100,224,14,52,141,239,129,28,193,105,248,200,8,76,113,5,138,101,47,225,36,15,33,53,147,142,218,240,18,130,69,29,181,194,125,106,39,249,185,201,154,9,120,77,228,114,166,6,191,139,98,102,221,48,253,226,152,37,179,16,145,34,136,54,208,148,206,143,150,219,189,241,210,19,92,131,56,70,64,30,66,182,163,195,72,126,110,107,58,40,84,250,133,186,61,202,94,155,159,10,21,121,43,78,212,229,172,115,243,167,87,7,112,192,247,140,128,99,13,103,74,222,237,49,197,254,24,227,165,153,119,38,184,180,124,17,68,146,217,35,32,137,46,55,63,209,91,149,188,207,205,144,135,151,178,220,252,190,97,242,86,211,171,20,42,93,158,132,60,57,83,71,109,65,162,31,45,67,216,183,123,164,118,196,23,73,236,127,12,111,246,108,161,59,82,41,157,85,170,251,96,134,177,187,204,62,90,203,89,95,176,156,169,160,81,11,245,22,235,122,117,44,215,79,174,213,233,230,231,173,232,116,214,244,234,168,80,88,175};

//x=gf(2,8).^(0:254);fprintf('%d,', x.x );
unsigned char EXP[]={1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,44,88,176,125,250,233,207,131,27,54,108,216,173,71,142};

unsigned char gf_mul(unsigned char in1,unsigned char in2)
{
	return (in1==0||in2==0)?0:EXP[((int)LOG[in1]+LOG[in2])%PARA_N];
}

unsigned char reg1[PARA_N_K+1]={0};
unsigned char reg[PARA_N_K+1]={0};
unsigned char r0[PARA_N+1]={0};

void rsenc(unsigned char msg[],unsigned char code[])
{
	int i,j;
	for (i=0;i<PARA_K;i++)
	{
		r0[i]=msg[i];
	}
	for (i=PARA_K;i<PARA_N+1;i++)
	{
		r0[i]=0;
	}
	for (i=0;i<PARA_N_K+1;i++)
	{
		reg[i]=r0[i];
	}
	for (i=0;i<PARA_K;i++)
	{
		for (j=0;j<PARA_N_K+1;j++)
		{
			reg1[j]=reg[j]^gf_mul(reg[0],g[j]);
		}
		for (j=0;j<PARA_N_K;j++)
		{
			reg[j]=reg1[j+1];
		}
		reg[PARA_N_K]=r0[i+PARA_N_K+1];
	}
	for (i=0;i<PARA_K;i++)
	{
		code[i]=msg[i];		
	}
	for (i=PARA_K;i<PARA_N;i++)
	{
		code[i]=reg[i-PARA_K];
	}
}


unsigned char enc_in[PARA_K]={0};
unsigned char enc_out[PARA_N]={0};
void rs_enc(unsigned char msg[],unsigned char code[])
{
	int i;
	int j;
	
	for (i=0;i<PARA_FRAMESIZE;i++)
	{
		for (j=0;j<PARA_K1;j++)
		{
			enc_in[j+PARA_N-PARA_N1]=msg[j*PARA_FRAMESIZE+i];
		}
		rsenc(enc_in,enc_out);
		for (j=0;j<PARA_N1;j++)
		{
			code[j*PARA_FRAMESIZE+i]=enc_out[j+PARA_N-PARA_N1];
			//				code[i*PARA_N1+j]=i*PARA_N1+j;
		}
	}
}

unsigned char a[PARA_N-PARA_K];
unsigned char a0[PARA_N-PARA_K];
unsigned char sigma[PARA_N-PARA_K];
unsigned char prod_a_ii[PARA_N-PARA_K];

void get_mat(unsigned char Ainv[],unsigned char err_pos[],int num_err)
{
	int i;
	int j;
	int k;
	int temp;	int prod_a_ii;
	for (i=0;i<num_err;i++)
	{
		temp=PARA_N1-err_pos[i]-1;
		temp=temp%PARA_N;
		a[i]=EXP[temp];
	}
	for (i=0;i<num_err;i++)
	{
		memcpy(a0,a,num_err);
		a0[i]=0;		
		memset(sigma,0,num_err);
		sigma[0]=1;
		for (j=0;j<num_err;j++)
		{
			for (k=num_err-1;k>=1;k--)
			{
				sigma[k]^=gf_mul(sigma[k-1],a0[j]);
			}
			
		}
		prod_a_ii=0;
		for (j=0;j<num_err;j++)
		{
			prod_a_ii+=LOG[a[i]^a0[j]];
		}
		prod_a_ii%=PARA_N;
		
		for (j=0;j<num_err;j++)
		{
			if (sigma[num_err-1-j]==0)
			{
				Ainv[i+j*(num_err)]=0;
			}
			else
			{
				temp=LOG[sigma[num_err-1-j]]-prod_a_ii;
				temp=temp<0?(temp+PARA_N):temp;
				Ainv[i+j*(num_err)]=EXP[temp];
			}
		}
	}
	return ;
}


unsigned char  gf_sub(unsigned char rx[], unsigned char power)
{
	int i;
	int temp;
	int y;
	power=power<0?(power+PARA_N):power;
	y=0;
	for (i=0;i<PARA_N1;i++)
	{
		if(rx[i]!=0)
		{
			temp=power*(PARA_N1-1-i);
			temp=LOG[rx[i]]+temp;
			temp%=PARA_N;
			y^=EXP[temp];
		}
	}
	return y;
}


void  gf_mat_mult(unsigned char A[], unsigned char x[],unsigned char y[],int num_err)
{
	int i;int j;
	
	for (i=0;i<num_err;i++)
	{
		y[i]=0;
		for (j=0;j<num_err;j++)
		{
			y[i]^=gf_mul(A[i+j*num_err],x[j]);			
		}
	}
}


unsigned char Ainv[PARA_N_K*PARA_N_K];
unsigned char s[PARA_N_K];
unsigned char d0[PARA_N1];
unsigned char err_value[PARA_N_K];
void rs_dec(unsigned char rx[],unsigned char decode[],unsigned char err_pos[],int num_err)
{
	int i;
	int j;
	char error[]="too many error postions!\n";
	if(num_err>PARA_N_K)
	{
		memcpy(decode,error,sizeof(error));
	}
	get_mat(Ainv,err_pos,num_err);
	for (i=0;i<PARA_FRAMESIZE;i++)
	{
		
		for (j=0;j<PARA_N1;j++)
		{
			d0[j]=rx[j*PARA_FRAMESIZE+i];
		}
		for (j=0;j<num_err;j++)
		{
			d0[err_pos[j]]=0;
		}
		for (j=0;j<num_err;j++)
		{
			s[j]=gf_sub(d0,( unsigned char )(j+1));
		}
		gf_mat_mult(Ainv,s,err_value,num_err);
		for (j=0;j<num_err;j++)
		{
			d0[err_pos[j]]=err_value[j];
		}
		for (j=0;j<PARA_N1;j++)
		{
			decode[j*PARA_FRAMESIZE+i]=d0[j];
		}
		
	}
}


/*

  function rs_matinv()
clc;clear;
% frame_in_bit=32;
frame_in_bit=1936;
para.m=8;
para.n1=84;
para.k1=70;
para.n=255;
para.framesize=frame_in_bit/para.m;
para.k=para.k1+para.n-para.n1;
t=para.n1-para.k1;
% t=2;
rand('seed',0);
msg = randint(para.framesize*para.k1,1,para.n); %#ok<FDEPR>
code=rs_enc(msg,para);
% code=rs_enc_cmex(msg);
[rx,err_pos] = add_easure(code,t,para);
mat_beta_inv=get_mat(err_pos,para);
decode = rs_dec(rx,err_pos,mat_beta_inv,para);
% decode = rs_dec_cmex(double(rx),err_pos-1);
sum(rx(:)~=code(:))
sum(decode(:)~=code(:))
end

function code=rs_enc(msg,para)
msg=reshape(msg,para.framesize,para.k1);
code = gf(zeros(para.framesize,para.n1),para.m);
c0 = rsenc(gf([zeros(para.framesize,para.n-para.n1) msg],para.m),para.n,para.k);
c0 = c0.x;
code = c0(:,para.n-para.n1+1:end);
code=reshape(code,1,[]);
end

function [rx,err_pos] = add_easure(code,t,para)
t1=randperm(para.n1);
err_pos = t1(1:t);
rx = reshape(code,para.framesize,[]);
rx(:,err_pos)=0;
end

function decode = rs_dec(rx,err_pos,mat_beta_inv,para)
decode=reshape(rx,para.framesize,[]);
decode(:,err_pos)=0;
alpha = gf(2,para.m);
gf_sub = @(r,x) r*x.^(length(r)-1:-1:0).';
s = gf( zeros(length(err_pos),1), para.m);
for ii=1:para.framesize
    for jj=1:length(err_pos)
        s(jj) = gf_sub(decode(ii,:), alpha^jj);
    end
    err_value=mat_beta_inv*s;
    decode(ii,err_pos)=err_value.x;
end
decode=reshape(decode,1,[]);
end

function mat_beta_inv=get_mat(err_pos,para)
alpha = gf(2,para.m);
a=alpha.^(para.n1-err_pos);
mat_beta_inv = mat_inv(a,para.m);
end

function Ainv=mat_inv(a,m)
t=length(a);
alpha = gf(2,m);
ZERO = gf(0,m);
ONE = gf(1,m);
Ainv = gf(zeros(t,t),m);


for ii=1:t
    a0=a;
    a0(ii)=ZERO;
    
    sigma=gf(eye(1,t),m);
    for jj=1:t
        sigma(2:end)=sigma(2:end)+sigma(1:end-1)*a0(jj);
    end

    prod_a_ii=alpha^sum(log(a(ii)+a0));
    for jj=1:t
        Ainv(ii,jj)=sigma(t-jj+1)/prod_a_ii;
    end
end
end

function code = encodeq(msg)
% gq=rsgenpoly(255,241);
% rsenc(gf(msg,8),255,241)
n = 255;
k = 241;
t=n-k;
gq=gf(1,8);
alpha=gf(2,8);
for ii=1:t
    gq=conv(gq,[ gf(1,8) alpha^ii ]);
end
msg(:)=1:241;
code = zeros(1,n);
% encode using deconv in gf
% a0*x^0+a1*x^1+a2*x^2
% in deconv:  [a2 a1 a0]
% in encoder: [a0 a1 a2]
% input and output reversed
v = gf([zeros(1,n-k),msg],8);
[~,r] = deconv(v(end:-1:1),gq(end:-1:1));
r = r(end:-1:k+1);
code(:) = [msg r.x];
end


  */