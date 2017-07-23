#include <ncurses.h>
#include <panel.h>
#include <iostream>
#include <fstream>

WINDOW *con;   						//Console Window
PANEL *con_panel, *main_panel;



void stringHandler(std::string text, std::string command, char *param) {
	if (command == "save") {
		std::fstream fs;
  		fs.open (param, std::fstream::out);
 		fs << command;
		fs.close();
	} else {
		printf("test\n");
	}
}

void charHandler(std::string text, int character, PANEL *conPanel, WINDOW *conH, char *param) {
	std::string command = "";
	int consoleX = 1;		//only x attr is relevant here
    show_panel(conPanel);  //show the console
    update_panels();   		//change is active now
    wrefresh(conH);			//just for beauty, not that important
    character = 0;
    while(character != 27) {
    	character = getch();	//get Input
    	if(character != 'f') {	//10 == ENTER	
    		mvwaddch(con,0,consoleX, character);  	//writes char on the screen
    		consoleX++;								//x attr is incremented
    		wrefresh(con);							//change is active
    		command += character;
    	} else {
    		stringHandler(text, command, param);
    	}
    }
	hide_panel(con_panel);	//hides again -> focus on the main window
}

int main(int argc, char *argv[]) {

	int y = 0, x = 0;
	std::string text = "";
	int character;

    initscr();  /* init ncurses */
	cbreak();
	start_color();
	noecho();
	clear();
    


	//Main Window

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
    keypad(stdscr, TRUE);   /* get keyboard input */
	bkgd(COLOR_PAIR(1));
	refresh();

	//consolewindow
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	con = newwin(1, COLS, LINES - 1, 0); // one line, all colls
	wbkgd(con, COLOR_PAIR(2));	//Backgroundcolor
	mvwaddstr(con, 0, 0, ">");
	wrefresh(con);	//refresh the window
	//curs_set(1);
    
	//Panel

	con_panel = new_panel(con);
	main_panel = new_panel(stdscr);

	hide_panel(con_panel);

    while(true) {
    	character = getch();
    	if(character == 10) { //Enter
    		y++;
    		x = 0;
    		move(y,x);
    	}
    	else if(character == KEY_UP) {
    		if(y > 0) {
    			y--;
    			move(y,x);
    		}
    	}
    	else if(character == KEY_DOWN) {
    		if(y < LINES - 1){
    			y++;
    			move(y,x);
    		}
    	}
    	else if(character == KEY_LEFT) {
    		if(x > 0){
    			x--;
    			move(y,x);
    		}
    	}
    	else if(character == KEY_RIGHT) {
    		if(x < COLS - 1){
    			x++;
    			move(y,x);
    		}
    	}
    	else if(character == KEY_BACKSPACE) {
    		if(x > 0){
    			x--;
    			mvdelch(y,x);
    			move(y,x);
    		}
    	}
    	else if(character == KEY_DC) {
    		if(x < COLS){
    			mvdelch(y,x);
    			move(y,x);
    		}
    	}
    	else if(character == 27) { 	//same es ESC
    		charHandler(text, character, con_panel, con, argv[2]);
    	}
    	else {
    		text += character;
    		mvinsch(y,x,character);
    		x++;
    		move(y,x);
    	}
    }
    

    endwin();   //end ncurses
    

    return 0;
}