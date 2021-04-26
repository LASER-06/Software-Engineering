#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#define shift(x, n) (((x) << (n)) | ((x) >> (32-(n))))//���Ƶ�ʱ�򣬸�λһ��Ҫ���㣬�����ǲ������λ
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476
//strBaye�ĳ���
unsigned int strlength;
//A,B,C,D����ʱ����
unsigned int atemp;
unsigned int btemp;
unsigned int ctemp;
unsigned int dtemp;
//����ti unsigned int(abs(sin(i+1))*(2pow32))
const unsigned int k[]={
        0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
        0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,
        0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,
        0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,
        0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
        0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,
        0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,
        0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,
        0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
        0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,
        0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
        0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,
        0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};
//����λ����
const unsigned int s[]={7,12,17,22,7,12,17,22,7,12,17,22,7,
        12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
        4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,
        15,21,6,10,15,21,6,10,15,21,6,10,15,21};
const char str16[]="0123456789abcdef";
void mainLoop(unsigned int M[])
{
    unsigned int f,g;
    unsigned int a=atemp;//A
    unsigned int b=btemp;//B
    unsigned int c=ctemp;//C
    unsigned int d=dtemp;//D
    for (unsigned int i = 0; i < 64; i++)
    {
        if(i<16){
            f=F(b,c,d);
            g=i;
        }else if (i<32)
        {
            f=G(b,c,d);
            g=(5*i+1)%16;
        }else if(i<48){
            f=H(b,c,d);
            g=(3*i+5)%16;
        }else{
            f=I(b,c,d);
            g=(7*i)%16;
        }
        unsigned int tmp=d;//��dֵ�洢������b��a=d;d=c;c=b;b=d��
        d=c;
        c=b;
        b=b+shift((a+f+k[i]+M[g]),s[i]);
//���ϼ�����һ���ط���Ҫ˵�������Ǹ�t��ֵ�����ʱ�򣬲����ǽ�λ��ÿ����������32λ�����ƴ���ʾ���ӵ�ʱ�����н�λ���λ��ʧ���õ���tҲ��32λ�����ƴ���ʾ
        a=tmp;
    }
    atemp=a+atemp;
    btemp=b+btemp;
    ctemp=c+ctemp;
    dtemp=d+dtemp;
}
//������Ĵ������������ڵ�λ�ӵ���Ӧλ����λ������32����10000...��λ��32λ������һ���������Ԫ���У�����һ��Ԫ��װ��δ����ǰ�ж���λ����24��
unsigned int* add(string str)
{
unsigned int num=((str.length()+8)/64)+1;
//��512λ,64���ֽ�Ϊһ�飬��������봮��64���ֽ�Ϊһ�������ֵ�������
unsigned int *strByte=new unsigned int[num*16];    
//64/4=16,������16��������ÿ4�ֽڷ�һ�����飬��Ϊ16�顣
    strlength=num*16;
    for (unsigned int i = 0; i < num*16; i++)
        strByte[i]=0;
    for (unsigned int i=0; i <str.length(); i++)
    {
        strByte[i>>2]|=(str[i])<<((i%4)*8);//һ�������洢�ĸ��ֽڣ�i>>2��ʾi/4 һ��unsigned int��Ӧ4���ֽڣ�����4���ַ���Ϣ
    }
strByte[str.length()>>2]|=0x80<<(((str.length()%4))*8);
//β�����1 һ��unsigned int����4���ַ���Ϣ,������128���ƣ�������
    /*
    *���ԭ���ȣ�����ָλ�ĳ��ȣ�����Ҫ��8��Ȼ����С�������Է��ڵ����ڶ���,���ﳤ��ֻ����32λ
    */
    strByte[num*16-2]=str.length()*8;
    return strByte;
}
string changeHex(int a)
{
    int b;
    string str1;
    string str="";
    for(int i=0;i<4;i++)//4��
    {
        str1="";
        b=((a>>i*8)%(1<<8))&0xff;   //������ÿ���ֽ�
        for (int j = 0; j < 2; j++)//2��
        {
            str1.insert(0,1,str16[b%16]);//(index,count,char)��indexλ�ò���count��char
            b=b/16;
        }
        str+=str1;//���Ⱥ�˳���4��8λʮ�������ַ�
    }
    return str;//��ȡ32λmd5ֵ��1/4��i:32 o:8��
}
string getMD5(string source)
{
    atemp=A;    //��ʼ��
    btemp=B;
    ctemp=C;
    dtemp=D;
    unsigned int *strByte=add(source);
    for(unsigned int i=0;i<strlength/16;i++)
    {
        unsigned int num[16];
        for(unsigned int j=0;j<16;j++)
            num[j]=strByte[i*16+j];
        mainLoop(num);
    }
    return changeHex(atemp).append(changeHex(btemp)).append(changeHex(ctemp)).append(changeHex(dtemp));
}

void XtoB(string md5){
	int a[4]={0};
	int num;
	int len=32;
	int j=0;
	for(int i=0;i<len;i++){
		if(md5[i]>='0'&& md5[i]<='9'){
			num = md5[i]-48;
			while(num!=0){
				a[j] = num%2;
				num = num/2;
				j++;
			}
			cout<<a[3]<<a[2]<<a[1]<<a[0];
			j=0;
			a[3]=a[2]=a[1]=a[0]=0;
		}
		if(md5[i]>='a'&& md5[i]<='f'){
			num = md5[i]-87;
			while(num!=0){
				a[j] = num%2;
				num = num/2;
				j++;
			}
			cout<<a[3]<<a[2]<<a[1]<<a[0];
			j=0;
			a[3]=a[2]=a[1]=a[0]=0;
		}
	}
	cout<<endl;
}

  int main()
{
	string ss;
	string s;
    ifstream inf;
    inf.open("demo.txt");
    //������ļ�
    while (getline(inf, ss)){    //getline(inf,s)�����ж�ȡinf�е��ļ���
        cout << ss << endl;//�ļ�����
		s=getMD5(ss);
		cout<<s<<endl;//MD5�����������
		XtoB(s);
		cout<<endl;
	}
	inf.close();
    return 0;
}
