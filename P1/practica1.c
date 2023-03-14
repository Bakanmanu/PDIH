/***************************************************************************
                            Practica 1 PDIH
        Authors: Amador Carmona Mendez y Manuel Zafra Mota
 
 
 
 Funciones:
    • gotoxy(): coloca el cursor en una posición determinada
    • setcursortype(): fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO.
    • setvideomode(): fija el modo de video deseado
    • getvideomode(): obtiene el modo de video actual
    • textcolor(): modifica el color de primer plano con que se mostrarán los caracteres
    • textbackground(): modifica el color de fondo con que se mostrarán los caracteres
    • clrscr(): borra toda la pantalla
    • cputchar(): escribe un carácter en pantalla con el color indicado actualmente
    • getche(): obtiene un carácter de teclado y lo muestra en pantalla

***************************************************************************/




#include <stdio.h>
#include <dos.h>
#define BYTE unsigned char


BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;
// hace una pausa
void pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    int86(0x16, &inregs, &outregs);
}
void gotoxy(int x,int y){
    union REGS inregs, outregs;
    inregs.h.ah=0x02;
    inregs.h.bh=0x00;
    inregs.h.dh=x; // Coordenada x
    inregs.h.dl=y; // Coordenada y
    int86(0x10, &inregs, &outregs);
}
void setvideomode(int x){
    union REGS inregs, outregs;
    inregs.h.ah=0x00;
    inregs.h.al=x;
    int86(0x10, &inregs, &outregs);
}
int getvideomode(){
    union REGS inregs, outregs;
    unsigned char modo;
    inregs.h.ah = 1;
    int86(0x10, &inregs, &outregs);
    modo=outregs.h.al;
    return modo;
}
void textcolor(int color){
    union REGS regs;
    regs.h.ah = 0x09;   // subcódigo para cambiar el color de texto
    regs.h.al = color;  // color deseado
    regs.h.bh = 0;      // página de pantalla (0 para la página actual)
    int86(0x10, &regs, &regs);  // llamada a la interrupción de DOS
}
void textbackground(int color){
    union REGS regs;
    regs.h.ah = 0x00;   // subcódigo para cambiar el color de fondo
    regs.h.al = color;  // color deseado
    regs.h.bh = 0;      // página de pantalla (0 para la página actual)
    int86(0x10, &regs, &regs);  // llamada a la interrupción de DOS
}
void clrscr(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

// establece el modo de vídeo: 3-texto, 4-gráfico
void modovideo(BYTE modo){
    union REGS inregs, outregs;
    inregs.h.al = modo;
    inregs.h.ah = 0x00;
    int86(0x10, &inregs, &outregs);
}
// pone un pixel en la coordenada X,Y de color C
void pixel(int x, int y, BYTE C){
    union REGS inregs, outregs;
    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = C;
    inregs.h.ah = 0x0C;
    int86(0x10, &inregs, &outregs);
}
int getche(){
    union REGS inregs, outregs;
    int caracter;
    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    caracter = outregs.h.al;
    return caracter;
}
void cputchar(char c){
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.dl = c;
    int86(0x21, &inregs, &outregs);
}

void setcursortype(int tipo_cursor){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    switch(tipo_cursor){
    case 0: //invisible
        inregs.h.ch = 010;
        inregs.h.cl = 000;
        break;
    case 1: //normal
        inregs.h.ch = 010;
        inregs.h.cl = 010;
        break;
    case 2: //grueso
        inregs.h.ch = 000;
        inregs.h.cl = 010;
        break;
    case 3: //modo gráfico
        modovideo(MODOGRAFICO); //gráfico
        pixel(10,40,0);
        pixel(10,50,1);
        pixel(15,60,2);
        pixel(20,70,3);
        pausa();
        modovideo(MODOTEXTO); //texto
        break;
    }
    int86(0x10, &inregs, &outregs);
    
}


int main(){
    clrscr();
    textcolor(0x01);   // cambiar el color de texto a verde
    printf("Hola mundo0000000000000!\n");
    int tmp;
    printf("\nPulsa una tecla... ");
    tmp = getchar();
    printf("\nHas pulsado: ");
    putchar( (char)tmp );
    printf("\nCursor invisible: ");
    setcursortype(0);
    //pausa();
    printf("\nCursor grueso: ");
    setcursortype(2);
    //pausa();
    printf("\nCursor normal: ");
    setcursortype(1);
    //pausa();
    
    clrscr();
    textbackground(0x0B);   // cambiar el color de fondo a cyan
    printf("Holaaaaaaa!\n");
    return 0;
}
