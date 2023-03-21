/***************************************************************************
                                Practica 2 PDIH
            Authors: Amador Carmona Mendez y Manuel Zafra Mota
 Requisitos mínimos de la práctica:
 1. Instalar la librería ncurses, crear los programas de ejemplo ofrecidos más arriba, y comprobar su funcionamiento.
 2. Crear un juego sencillo tipo “pong” partiendo del ejemplo del movimiento de la pelotita.
 Requisitos ampliados:
 1. que al iniciar el juego se muestre una pantalla de bienvenida en la que se muestren los datos de quienes han realizado el juego y explicando los controles de juego (p.ej. un recuadro con la explicación). Tras una pausa o pulsación de tecla se iniciará el juego en sí mismo.
 2. que al terminar cada partida se muestre una pantalla de resumen mostrando el
 marcador final y felicitando al ganador. Se dará la opción de volver a jugar o terminar el programa.
 
 ***************************************************************************/

#include <ncurses.h>
#include <unistd.h>
#define DELAY 30000

void pantalla_inicio(){
    int rows, cols;
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        printf("El terminal no tiene soporte de color \n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE,COLOR_BLUE);
    clear();
    refresh();
    getmaxyx(stdscr, rows, cols);
    WINDOW *window = newwin(rows,cols,0,0);
    wbkgd(window, COLOR_PAIR(2));
    box(window, '|', '-');
    mvwprintw(window, 7, 23, "Bienvenidos a nuestro juego Pong");
    mvwprintw(window, 8, 13, "Ralizado por Manuel Zafra Mota y Amador Carmona Mendez ");
    mvwprintw(window, 9, 25, "Pulse un boton para jugar.");
    wrefresh(window);
    getch();
    endwin();
    
}
void pantalla_final(){
    int rows, cols;
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        printf("El terminal no tiene soporte de color \n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE,COLOR_BLUE);
    clear();
    refresh();
    getmaxyx(stdscr, rows, cols);
    WINDOW *window = newwin(rows,cols,0,0);
    wbkgd(window, COLOR_PAIR(2));
    box(window, '|', '-');
    mvwprintw(window, 7, 30, "Juego Terminado ");
    mvwprintw(window, 8, 33, "Resultado: ");
    mvwprintw(window, 9, 23, "Pulse un boton para finalizar.");
    wrefresh(window);
    getch();
    endwin();
    
}
void pantalla_punto(int jugador){
    int rows, cols;
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        printf("El terminal no tiene soporte de color \n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE,COLOR_BLUE);
    clear();
    refresh();
    getmaxyx(stdscr, rows, cols);
    WINDOW *window = newwin(rows,cols,0,0);
    wbkgd(window, COLOR_PAIR(2));
    box(window, '|', '-');
    mvwprintw(window, 10, 25, "Punto para el jugador : %i",jugador);
    //mvwprintw(window, 11, 28, "Marcador |(Jugador 1) %i - (Jugador 2) %i|",marcador1,marcador2);
    mvwprintw(window, 12, 28, "Pulse para continuar");
    wrefresh(window);
    getch();
    endwin();
    
}
void juego(){
    int x = 0, y = 0;
    int max_y = 250, max_x =250;
    int next_x = 0,next_y=0;
    int directionx = 1;
    int directiony = 1;
    int rows, cols;
    //Pantalla de juego
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE,COLOR_BLUE);
    clear();
    refresh();
    getmaxyx(stdscr, rows, cols);
    WINDOW *window = newwin(rows,cols,0,0);
    wbkgd(window, COLOR_PAIR(2));
    box(window, '|', '-');
    noecho();
    
    //Juego
    curs_set(FALSE);
    while(y!=50) {
        clear();
        mvprintw(y, x, "o");
        refresh();
        usleep(DELAY);
        next_x = x + directionx;
        next_y = y + directiony;
        if (next_x >= max_x || next_x < 0) {
            directionx*= -1;
        } else {
            x+= directionx;
        }
        if (next_y >= max_y || next_y < 0) {
            directiony*= -1;
        } else {
            y+= directiony;
        }
    }
    pantalla_punto(1);
    //refrescar pantalla de juego
    wrefresh(window);
}

int main(int argc, char *argv[]) {
    //Realizamos una pantalla que al iniciar el juego se muestre una pantalla de bienvenida en la que se muestren los datos de quienes han realizado el juego y explicando los controles de juego (p.ej. un recuadro con la explicación).
    pantalla_inicio();
    //Implementación del juego
    juego();
    //Realizamos una pantalla que al terminar cada partida se muestre una pantalla de resumen mostrando el marcador final y felicitando al ganador. Se dará la opción de volver a jugar o terminar el programa.
    pantalla_final();
    
    
    
}
