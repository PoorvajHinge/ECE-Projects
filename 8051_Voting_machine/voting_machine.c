#include <reg51.h>
sfr ldata = 0xA0;
sbit rs = P1^0;
sbit rw = P1^1;
sbit en = P1^2;
sbit busy = P2^7;
sbit btn0 = P1^3;
sbit btn1 = P1^4;
sbit btn2 = P1^5;
sbit btn3 = P1^6;
sbit resultbtn = P1^7;
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void msdelay(unsigned int);
void lcdready();
void main()
{
//initializing counters
unsigned char v0 = 0;
unsigned char v1 = 0;
unsigned char v2 = 0;
unsigned char v3 = 0;
//btn check low to high
char btn0check = 1;
char btn1check = 1;
char btn2check = 1;
char btn3check = 1;
char resultcheck = 1;
// lcd init
lcdcmd(0x38);
lcdcmd(0x0c);
lcdcmd(0x01);
lcdcmd(0x06);
while(1)
{
if(btn0check == 0 && btn0 == 1)
{
v0++;
btn0check = 1;
}
if(btn1check == 0 && btn1 == 1)
{
v1++;
btn1check = 1;
}

if(btn2check == 0 && btn2 == 1)
{
v2++;
btn2check = 1;
}
if(btn3check == 0 && btn3 == 1)
{
v3++;
btn3check = 1;
}
if(resultcheck == 0 && resultbtn == 1)
{
lcdcmd(0x01);
{
unsigned char max;
unsigned char maxVal;
unsigned char tieCount = 0;
if(v0 > v1){
max = 'A';
maxVal = v0;
}
else{
max = 'B';
maxVal = v1;
}
if(v2 > maxVal) {
max = 'C';
maxVal = v2;
}
if(v3 > maxVal) {
max = 'D';
maxVal = v3;
}
if(v0 == maxVal) tieCount++;
if(v1 == maxVal) tieCount++;
if(v2 == maxVal) tieCount++;
if(v3 == maxVal) tieCount++;
if(tieCount > 1) {
lcdcmd(0x84);
lcddata('T');
lcddata('I');
lcddata('E');
}
else {
lcdcmd(0x81);

lcddata('W');
lcddata('I');
lcddata('N');
lcddata('N');
lcddata('E');
lcddata('R');
lcddata(':');
if(max == 'A') lcddata('A');
else if(max == 'B') lcddata('B');
else if(max == 'C') lcddata('C');
else lcddata('D');
}
}
while(1);
}
lcdcmd(0x80);
lcddata('A');
lcddata(':');
lcddata(48 + (v0/100));
lcddata(48 + (v0/10));
lcddata(48 + (v0%10));
lcdcmd(0x88);
lcddata('B');
lcddata(':');
lcddata(48 + (v1/100));
lcddata(48 + (v1/10));
lcddata(48 + (v1%10));
lcdcmd(0xC0);
lcddata('C');
lcddata(':');
lcddata(48 + (v2/100));
lcddata(48 + (v2/10));
lcddata(48 + (v2%10));
lcdcmd(0xC8);
lcddata('D');
lcddata(':');
lcddata(48 + (v3/100));
lcddata(48 + (v3/10));
lcddata(48 + (v3%10));
lcdcmd(0x80);
if(btn0check != 0) btn0check = btn0;
if(btn1check != 0) btn1check = btn1;
if(btn2check != 0) btn2check = btn2;
if(btn3check != 0) btn3check = btn3;
if(resultcheck != 0) resultcheck = resultbtn;
}

}
void lcdcmd(unsigned char value)
{
lcdready();
ldata = value;
rs = 0;
rw = 0;
en = 1;
msdelay(1);
en = 0;
return;
}
void lcddata(unsigned char value)
{
lcdready();
ldata = value;
rs = 1;
rw = 0;
en = 1;
msdelay(1);
en = 0;
return;
}
void lcdready()
{
busy = 1;
rs = 0;
rw = 1;
while(busy == 1)
{
en = 0;
msdelay(1);
en = 1;
}
return;
}
void msdelay(unsigned int itime)
{
unsigned int i, j;
for(i=0; i<itime; i++)
for(j=0; j<1275; j++);
}
