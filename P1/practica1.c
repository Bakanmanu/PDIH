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
 Funciones Extra:
    • recuadro(): dibuja un recuadro en la pantalla en modo texto. Recibirá como parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y el color de fondo.
 
***************************************************************************/




#include <stdio.h>
#include <dos.h>
#include <string.h>
#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;

int colortexto=7;
int colorback=0;


// hace una pausa
void pausa(void){
    union REGS inregs, outregs;

    inregs.h.ah = 0x00;
    int86(0x16, &inregs, &outregs);
}


int mi_getchar(void){
    union REGS inregs, outregs;
    int caracter;

    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);

    caracter = outregs.h.al;
    return caracter;
}

void mi_putchar(char c){
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.dl = c;
    int86(0x21, &inregs, &outregs);
}

/**
 gotoxy(): coloca el cursor en una posición determinada
 **/
void gotoxy(int x,int y){
    union REGS inregs, outregs;

    inregs.h.ah=0x02;
    inregs.h.bh=0x00;
    inregs.h.dh=x; // Coordenada x
    inregs.h.dl=y; // Coordenada y
    int86(0x10, &inregs, &outregs);
}
/**
 setvideomode(): fija el modo de video deseado
 **/
void setvideomode(int x){
    union REGS inregs, outregs;

    inregs.h.al = x;
    inregs.h.ah = 0x00;
    int86(0x10, &inregs, &outregs);
}
/**
 getvideomode(): obtiene el modo de video actual
 **/
void getvideomode(void){
    union REGS inregs, outregs;
    unsigned char modo;

    inregs.h.ah = 0xF;

    int86(0x10, &inregs, &outregs);

    modo=outregs.h.al;

    printf("%i",modo);
}
/**
 textcolor(): modifica el color de primer plano con que se mostrarán los caracteres
 **/
void textcolor(int color){
    colortexto=color;
    // union REGS inregs, outregs;

    // inregs.h.ah=0x09;
    // inregs.h.al=97;     // 'a'
    // inregs.h.bl=color;
    // inregs.h.bh=0x00;
    // inregs.x.cx=10;     // numero de repeticiones;

    // int86(0x10, &inregs, &outregs);
}
/**
 textbackground(): modifica el color de fondo con que se mostrarán los caracteres
 **/
void textbackground(int color){
    colorback=color;
}
/**
 clrscr(): borra toda la pantalla
 **/
void clrscr(void){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


/**
 pixel()
 **/
void pixel(int x, int y, BYTE C){
    union REGS inregs, outregs;

    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = C;
    inregs.h.ah = 0x0C;
    int86(0x10, &inregs, &outregs);
}
/**
 getche(): obtiene un carácter de teclado y lo muestra en pantalla
 **/
void getche(void){
    union REGS inregs, outregs;
    int caracter;

    caracter = mi_getchar();
    printf("\nHas pulsado: ");
    mi_putchar((char) caracter);
}
/**
 cputchar(): escribe un carácter en pantalla con el color indicado actualmente
 **/
void cputchar(int c){
    union REGS inregs, outregs;

    inregs.h.ah = 0x09;
    inregs.h.al = c;
    // inregs.h.dl = c;
    inregs.h.bl = colorback << 4 | colortexto;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
    // return;
}
/**
 setcursortype(): fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO.
 **/

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
        setvideomode(MODOGRAFICO); //gráfico
        pixel(10,40,0);
        pixel(10,50,1);
        pixel(15,60,2);
        pixel(20,70,3);
        pausa();
        setvideomode(MODOTEXTO); //texto
        break;
    }
    int86(0x10, &inregs, &outregs);
    
}
/**
 mi_printf(): saca por pantalla utilizando cputchar() una cadena de caracteres
 **/
int i=0;
void mi_printf(const char *str){
    printf("\n");

    for(i; i < strlen(str); i++){
        cputchar((int) str[i]);
        printf("%c", str[i]);
    }
    i=0;
}

int tmp;
/**
 recuadro(): dibuja un recuadro en la pantalla en modo texto. Recibirá como parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y el color de fondo.
 **/
int j;
int color;
void recuadro(int x1,int y1, int x2, int y2,int cp, int cf){
    color=cf << 4 | cp;
    setvideomode(4);
    i=x1;
    j=y1;
    for(i; i<=x2;i++){
        for(j;j<=y2;j++){
            
            pixel(i,j,cp);
        }
        j=y1;
        //printf("\n");
        
    }
    
}
/**
 main(): funcion principal deonde probamos todas las funciones
 **/
int main(){
    
    mi_printf("Pulsa una tecla: ");
    getche();
    mi_printf("Cursor invisible: ");
    setcursortype(0);
    pausa();
    
    mi_printf("Cursor grueso: ");
    setcursortype(2);
    pausa();
    
    mi_printf("Cursor normal: ");
    setcursortype(1);
    pausa();
    
    mi_printf("Probando gotoxy: ");
    gotoxy(20,22);
    pausa();
    
    mi_printf("Probando set videomode a modo grafico: ");
    setvideomode(4);
    pixel(10,40,0);
    pixel(10,50,1);
    pixel(15,60,2);
    pixel(20,70,3);
    pausa();
    setvideomode(3);
    pausa();
    
    mi_printf("Probando set videomode a modo texto: ");
    
    mi_printf("Probando set getvideomode: ");
    getvideomode();
    mi_printf("Leyenda: ");
    mi_printf("Si es menor que 3 o igual a 7 = texto"); 
    mi_printf("En el resto de casos: = Grafico ");
    
    textcolor(1);
    mi_printf("Color de texto cambiado");
    pausa();
    
    textbackground(11);
    mi_printf("Color de fondo cambiado");
    pausa();
    
    clrscr();
    mi_printf("pantalla limpiada");
    
    pausa();
    mi_printf("imprimiendo rectangulo que empieza en el pixel (10,10) y termina en (50,60)");
    recuadro(30,20,50,60,1,3);
    

    pausa();
    setvideomode(3);
    
    return 0;
}

