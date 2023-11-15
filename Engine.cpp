#include "Engine.h"

Engine::Engine(int argc, char **argv)
{

    save_map(argc, argv);


    initscr();
    noecho(); 
    curs_set(0);
    keypad(stdscr,true);

    start_color();  
    init_pair(1, COLOR_RED, COLOR_BLACK);    //Color Potter (Orange) & Message Color win Potter
    init_pair(2,COLOR_GREEN, COLOR_BLACK);   //Color Malfoy (Green) & Message Color win Malfoy
    init_pair(3,COLOR_MAGENTA, COLOR_BLACK); //Color wall (Purple)
    init_pair(4,COLOR_CYAN, COLOR_BLACK);    //Color diamond (Cyan)
    init_pair(5,COLOR_WHITE, COLOR_BLACK);   //Color draw message

    load_map();

}

void Engine::save_map(int argc, char **argv)
{
    file.open(argv[1], ios::in); //open file
    if(!file)
    {
        throw 1;
    }
    else
    {
        while(getline(file, line))
        {
            map.push_back(line); //read and push map line by line
        }
    }
    file.close(); //close file
}

void Engine::load_map()
{
    //Draw map on screen: '*' = ACS_BOARD (wall), '.' = space (corridor)
    for(int i = 0; i < map.size(); i++)
    {
		for(int j = 0; j < map[0].size(); j++)
        {
			if(map[i][j] == '*')
            {
                attron(COLOR_PAIR(3));
				mvaddch(i,j, ACS_CKBOARD);  //draw wall
                attroff(COLOR_PAIR(3));
			}
			else if(map[i][j] == '.')
            {
			    mvaddch(i,j, ' '); //draw corridor
			}
		}
	}
}

void Engine::valid_XY(vector<int>& p, vector<int>& m)
{
    time_t t;
    srand((unsigned) time(&t));

    int px, py; //potter position
    int mx, my; //malfoy position

    do
    {
        py = rand() % map.size()-1 + 1; //potter y
        px = rand() % map[0].size()-1 + 1; //potter x

        my = rand() % map.size()-1 + 1; //malfoy y
        mx = rand() % map[0].size()-1 + 1; //malfoy x

    } while (map[py][px] == '*' || map[my][mx] == '*' || ((py == my) && (px == mx)));
    
        
    p.push_back(py);
    p.push_back(px);

    m.push_back(my);
    m.push_back(mx);
}

void Engine::diamond_position()
{
    time_t t;
    srand((unsigned) time(&t));

    int dx, dy;

    do
    {
        
        dy = rand() % map.size()-1 + 1; //diamond y
        dx = rand() % map[0].size()-1 + 1; //diamond x

    } while (map[dy][dx] == '*' || ((dy == pot->get_y()) && (dx == pot->get_x())) 
                                || ((dy == mal->get_y()) && (dx == mal->get_x())));

    diamond_pos.push_back(dy);
    diamond_pos.push_back(dx);
    
}

int Engine::collision()
{
    //Check if (y Potter = y diamond) AND (x Potter = x diamond)
    if((pot->get_y() == diamond_pos[0] && pot->get_x() == diamond_pos[1])
    && (mal->get_y() == diamond_pos[0] && mal->get_x() == diamond_pos[1]))
    {
        return 1; //draw
    }
    else if(pot->get_y() == diamond_pos[0] && pot->get_x() == diamond_pos[1])
    {
        return 2; //Potter win
    }
    else if(mal->get_y() == diamond_pos[0] && mal->get_x() == diamond_pos[1])
    {
        return 3; //Malfoy win
    }
    else
    {
        return 0;
    }
}

void Engine::start()
{
    vector<int> potter_pos;
    vector<int> malfoy_pos;

    valid_XY(potter_pos, malfoy_pos); //valid coordinates for player and villain


    Potter p(this, potter_pos[0], potter_pos[1], 'M'); //Construct Potter
    Malfoy m(this, malfoy_pos[0], malfoy_pos[1], 'L'); //Construct Malfoy

    this->pot = &p;
    this->mal = &m;

    pot->show();
    mal->show();
    
    diamond_position();
    attron(COLOR_PAIR(4));
    mvaddch(diamond_pos[0], diamond_pos[1], ACS_DIAMOND); //draw diamond on screen
    attroff(COLOR_PAIR(4));
    
    refresh(); //show objects on screen

    int pot_choise;
    int mal_choise;
    int number;
    srand(time(NULL));

    while((pot_choise = pot->getMove()) != 6) //move Potter - (stop on ESC)
    {
        mal_choise = mal->getMove(); //move Malfoy
        
        if(pot_choise != 5)//if space key pressed, potter does not move
        {
            if(pot_choise == 1)
            {

                mvaddch(pot->get_y(), pot->get_x(), ' ');//clear current position
                pot->set_y(pot->get_y()-1);//new move (up)
            }
            else if(pot_choise == 2)
            {
                mvaddch(pot->get_y(), pot->get_x(), ' ');//clear current position
                pot->set_y(pot->get_y()+1);//new move (down)
            }
            else if(pot_choise == 3)
            {
                mvaddch(pot->get_y(), pot->get_x(), ' ');//clear current position
                pot->set_x(pot->get_x()-1);//new move (left)
            }
            else if(pot_choise == 4)
            {
                mvaddch(pot->get_y(), pot->get_x(), ' ');//clear current position
                pot->set_x(pot->get_x()+1);//new move (right)
            }
        }

        if(mal_choise == 1)
        {
            mvaddch(mal->get_y(), mal->get_x(), ' ');//clear current position
            mal->set_y(mal->get_y()+1); //new move (down)
        }
        else if(mal_choise == 2)
        {
            mvaddch(mal->get_y(), mal->get_x(), ' ');//clear current position
            mal->set_y(mal->get_y()-1); //new move (up)
        }
        else if(mal_choise == 3)
        {
            mvaddch(mal->get_y(), mal->get_x(), ' ');//clear current position
            mal->set_x(mal->get_x()+1); //new move (right)
        }
        else if(mal_choise == 4)
        {
            mvaddch(mal->get_y(), mal->get_x(), ' ');//clear current position
            mal->set_x(mal->get_x()-1); //new move (left)
        }

        if(collision() == 1) //if draw
        {
            clear();

            attron(COLOR_PAIR(5));
            addstr("Draw\n\n ...Press ESC key to exit");
            attroff(COLOR_PAIR(5));
            
            int c;
            do
            {
                c = getch();
            } while (c != 27); //stop on ESC
            
            break;
        }
        else if(collision() == 2) //if Potter win
        {
            clear();

            attron(COLOR_PAIR(1));
            addstr("Mpampis Won\n\n ...Press ESC key to exit");
            attroff(COLOR_PAIR(1));
            
            int c;
            do
            {
                c = getch();
            } while (c != 27); //stop on ESC

            break;
        }
        else if(collision() == 3) //if Malfoy win
        {
            clear();

            attron(COLOR_PAIR(2));
            addstr("Lukas Won\n\n ...Press ESC key to exit");
            attroff(COLOR_PAIR(2));
            
            int c;
            do
            {
                c = getch();
            } while (c != 27);//stop on ESC

            break;
        }

        pot->show(); //Potter on new position
        mal->show(); //Malfoy on new position
        

        number = rand() % 100 + 1; //random number between 1-100
        if(number >= 1 && number <= 3) //if number between 1 or 3, change diamond position (3% probability of diamond changing position on player's move, to make game a little harder)
        {
            mvaddch(diamond_pos[0], diamond_pos[1], ' '); //clear current diamond position
            diamond_pos.clear(); //clear diamond coordinates
            diamond_position(); //give new valid coordinates

            attron(COLOR_PAIR(4));
            mvaddch(diamond_pos[0], diamond_pos[1], ACS_DIAMOND); //draw diamond on the new coordinates
            attroff(COLOR_PAIR(4));
        }

        refresh(); //show objects on screen
    }
    
    endwin();

}

vector<string> Engine::get_map() const
{
    return map;
}

vector<int> Engine::get_diamond_pos() const
{
    return diamond_pos;
}