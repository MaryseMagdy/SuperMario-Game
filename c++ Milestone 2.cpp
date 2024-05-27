#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>

using namespace std;




//CLASS POINT
class Point
{
    public:
        int x, y;

        Point(){
            x = 0;
            y = 0;
            }

        Point(int x, int y) {
        this->x = x;
        this->y = y;
        }

};
//CLASS CELL
class Cell{
public:
    int x;
    int y;
    char type;
    Cell(char c, int x1, int y1){
    this->type='.';
    this->x=x1;
    this->y=y1;
    }
    Cell(){
    this->type = '.';
    this->x=0;
    this->y=0;
    }

    char getType(){
            return type;
        }
    void setType(char type){
        this->type = type;
        }

};

//CLASS CHAMPION
class Champion : public Cell{
    private:
    Point location;
    int health ;
    int gemsScore;

    public:
        Champion(Point loc, int health, int gems) : Cell(){
        this->location = loc;
        this->health = 100;
        this->gemsScore= gems;
        this->type ='C';
        cout<< "Constructor champion() is called"<<endl;

        }

        Champion() : Cell(){
            this->health =100;
        }
        Point getLocation(){
            return location;
        }
        int getHealth(){
            return health;
        }
        int getGemsScore(){
            return gemsScore;
        }
        void setLocation(Point location){
        this->location = location;
        }
        void setHealth(int health){
        this->health = health;
        }
        void setGemsScore(int gemsScore){
        this->gemsScore = gemsScore;
        }
        virtual void print_champ_info(){
            cout<<"Champion's location is:" << "(" <<this->getLocation().x<< "," << this->getLocation().y << ")" << "  Champion's health is:"<< this->getHealth()<<"   Champion's gems score is:"<<this->getGemsScore()<< "/40"<<endl;
        }
        virtual void useAbility(){
        cout<<"Ability x is created"<<endl;
        }


};
//CLASS MAP
class map{

private:
     int rows;
     int columns;
     Cell *** board = new  Cell**[10] ;
    //  Cell *** board;
public:
    map(int width, int height){

        for (int k = 0 ; k<10 ; k++){
        board[k] = new Cell*[10];
          }

        for (int i = 9; i>=0 ;i--){
            for(int j = 0 ; j<=9 ; j++){
                   board[i][j] =  new Cell( i , j , '.');
            }
                   }

    cout<< "Constructor map() is called"<< endl;
    }


    void print_map(){
        for (int i = 9; i>=0 ;i--){
            for(int j = 0 ; j<=9 ; j++){
            cout<<board[i][j]->type<<" " ;
            }
            cout<<endl;
        }
     cout<<"print_map() called"<<endl;
    }

    void randomize_map(){
        Champion c;

        for (int i = 9; i>=0 ;i--){
            for(int j = 0 ; j<=9 ; j++){
                 board[i][j]->setType('.');
            }
                   }

        int  xOfBomb =0;
        int  yOfBomb = 0;
        int xOfThief =0;
         int yOfThief =0;
        int ObsCount = 1;
        int BombCount = 1;
        int ThiefCount = 1;
        int  xOfGem =0;
        int  yOfGem = 0;
        int CoinCount = 0;
        int PotionCount =0;
        int  xOfCoin =0;
        int  yOfCoin = 0;
        int  xOfPotion =0;
        int  yOfPotion = 0;
        int GemCount=0;



                while(BombCount<=10){
                xOfBomb= (rand() % 10);
                yOfBomb = (rand() % 10);

                if (board [xOfBomb][yOfBomb]->type== '.'){
                        board[xOfBomb][yOfBomb]->type = ('B'); //Bomb
                BombCount++;

                }
                }
                while(ThiefCount<=10){
                xOfThief= (rand() % 10);
                yOfThief = (rand() % 10);

                if (board [xOfThief][yOfThief]->type ==  '.'){
                        board[xOfThief][yOfThief]->type = ('T');  //Bomb

                ThiefCount++;
                }
                }

                while(PotionCount <= 20){//WRITE NEXT TIME EXPLAINATION WHY

                xOfPotion = (rand() % 10);
                yOfPotion = (rand() % 10);

                if (board [xOfPotion][yOfPotion]->type == '.'){
                        board[xOfPotion][yOfPotion]->type = ('P') ; //Gem
                PotionCount++;

                }
                  }

                 while( CoinCount < 20){//WRITE NEXT TIME EXPLAINATION WHY

                xOfCoin = (rand() % 10);
                yOfCoin = (rand() % 10);

                if (board [xOfCoin][yOfCoin]->type == '.'){
                        board[xOfCoin][yOfCoin]->type = ('n') ; //Gem
                CoinCount++;

                }
                  }
             GemCount = PotionCount + CoinCount;
             c.setGemsScore(GemCount);

            cout<< "randomize_map() called"<<endl;
            //TODO M OR L
            board[0][0]->setType('C');

    }
   void update(Champion c){
        // map m = map(10,10);
        system("cls");
         print_map();
         c.print_champ_info();

    }

     void move (Champion c){

     //Champion  c =  Champion();
     int targetX = 0;
     int targetY = 0;
     char key = ' ';
     cout<< "Enter a key"<< endl;

      while (c.getGemsScore() < 40 && c.getHealth() >0){
      if( targetX<10 || targetX==0 || targetY<10 ||targetY==0){

        key = _getch();

         if ( key == '8'  ){
            targetX = c.getLocation().x + 1;
			targetY = c.getLocation().y;
		} else if (key =='5' ) {
			targetX = c.getLocation().x - 1;
			targetY = c.getLocation().y;
		} else if (key == '4') {
			targetX = c.getLocation().x;
			targetY = c.getLocation().y - 1;
		} else if (key == '6') {
			targetX = c.getLocation().x;
			targetY = c.getLocation().y + 1;
		}



		//Found obstacle while moving
		if (board[targetX][targetY]->getType() == 'B' ) {
              if(c.getHealth()>=40){
              c.setHealth(c.getHealth()-40);
              board[c.getLocation().x][c.getLocation().y]->setType('.'); //bafdy makan el champion4
              board[targetX][targetY]->setType('C') ; //place the champion in his new loc on map
              c.setLocation(Point(targetX,targetY)); //updating the champ's loc
                }
		}
		else if (board[targetX][targetY]->getType()=='T' ){
            if(c.getHealth()>=40){
              c.setHealth(c.getHealth()-40);
              board[c.getLocation().x][c.getLocation().y]->setType('.'); //bafdy makan el champion4
              board[targetX][targetY]->setType('C') ; //place the champion in his new loc on map
              c.setLocation(Point(targetX,targetY)); //updating the champ's loc
                }
		 }
		//Found Gem while moving
		else if (board[targetX][targetY]->getType() ==  'P'){
            c.setGemsScore(c.getGemsScore()+1);
            board[c.getLocation().x][c.getLocation().y]->setType('.'); //bafdy makan el champion
            board[targetX][targetY]->setType('C') ; //place the champion in his new loc on map
            c.setLocation(Point(targetX,targetY)); //updating the champ's loc

		}
		else if (board[targetX][targetY]->getType() ==  'n'){
            c.setGemsScore(c.getGemsScore()+1);
            board[c.getLocation().x][c.getLocation().y]->setType('.'); //bafdy makan el champion
            board[targetX][targetY]->setType('C') ; //place the champion in his new loc on map
            c.setLocation(Point(targetX,targetY)); //updating the champ's loc

		}
		//Moving mafesh 7aga odamo
		else if (board[targetX][targetY]->getType() == '.'){
            board[c.getLocation().x][c.getLocation().y]->setType('.');  //bafdy makan el champion
            board[targetX][targetY]->setType('C'); //place the champion in his new loc on map
            c.setLocation(Point(targetX,targetY)); //updating the champ's loc

		}

           update(c);
      }

      }

       if (c.getGemsScore() == 40){
        cout<<"You won!!"<<endl;
      }
       else if (c.getHealth() <=0 ){
         cout<<"You lost :("<<endl;
       }

     }
    void setboard(Cell *** board){
    this->board=board;

    }
    Cell *** getboard(){
    return board;
     }

};
class Listner {

map m;
Cell ***  board;
int rows;
int columns;

 void useAbility(){
		Champion c;
		int targetX =0;
		int targetY = 0;
		char key = ' ';
		if( targetX<10 || targetX==0 || targetY<10 ||targetY==0){
		 key=_getch();

        if(board[targetX][targetY]->type == 'B') {
//Cell (targetX, targetY , 'B') || board [targetX][targetY])== new Cell (targetX, targetY , 'B'))
		   if(key == '8'){
		    targetX = c.getLocation().x + 2;
		    targetY = c.getLocation().y;
      	}

		else if (key == '5'){
			targetX = c.getLocation().x - 2;
			targetY = c.getLocation().y;
		}
		else if (key == '4'){
			targetX = c.getLocation().x;
			targetY = c.getLocation().y - 2;
		}
		else if (key == '6'){
			targetX = c.getLocation().x;
			targetY = c.getLocation().y + 2;
		}
	    c.setHealth(c.getHealth());
	  //  m.setboard(m.getboard()[targetX][targetY]);
		}
		 }
		 cout<<"Mario ability is called"<<endl;
	 }
};
class Listener2 {

Cell ***  board;
int rows;
int columns;

 void useAbility(){
	     Champion c;
		int targetX =0;
		int targetY = 0;
		char key = ' ';
		if( targetX<10 || targetX==0 || targetY<10 ||targetY==0){
		 key=_getch();

        if(board[targetX][targetY]->type == 'B') {
//Cell (targetX, targetY , 'B') || board [targetX][targetY])== new Cell (targetX, targetY , 'B'))
		   if(key == '8'){
		    targetX = c.getLocation().x + 2;
		    targetY = c.getLocation().y;
      	}

		else if (key == '5'){
			targetX = c.getLocation().x - 2;
			targetY = c.getLocation().y;
		}
		else if (key == '4'){
			targetX = c.getLocation().x;
			targetY = c.getLocation().y - 2;
		}
		else if (key == '6'){
			targetX = c.getLocation().x;
			targetY = c.getLocation().y + 2;
		}

		for (int i =0; i<10;i++){
                for (int j = 0; j<10 ; j++){
                     if (board[i][j]->getType() == 'B' ||board[i][j]->getType() == 'T'){
                        rows = '.';
                        columns='.';
                     }

                }

		}


	 }
		}
 cout<<"Luigi ability is called"<<endl;
 }
};

//CLASS MARIO
class Mario : public Champion{
    public:
	Mario() : Champion(){
	}
	void print_champ_info(){
	}


        void useAbility(){
        int abilityCounter = 0;
	    while(abilityCounter <= 2){
        abilityCounter++;
        useAbility();
	    }
       }
};
//CLASS LUIGI
class Luigi : public Champion{
    public:
	Luigi() : Champion(){

	}
	    void useAbility(){
        int abilityCounter = 0;
	    while(abilityCounter <= 2){
        abilityCounter++;
        useAbility();
	    }
       }



void print_champ_info(){
}
};

//CLASS OBSTACLE
class Obstacle : public Cell{
private:
    int dmg_amount;
public:
    Obstacle() : Cell(){
    this->dmg_amount = (rand()%5);
    type ='O';
    }
    virtual void execute(Champion c){

    }
    int get_dmg_amount(){
        return dmg_amount;
    }
};
//CLASS BOMB
class Bomb: public Obstacle{
public:
    void execute(Champion c){
        if(c.getHealth() - get_dmg_amount()>=0){
        c.setHealth(c.getHealth() - get_dmg_amount());
        }else{
        c.setHealth(0);
        }
    cout<<"bomb executed with dmg="<< get_dmg_amount()<<endl;
    }

};
//CLASS THIEF
class Thief: public Obstacle{
public:
    void execute(Champion c){
     if(c.getGemsScore() - get_dmg_amount()>=0){
        c.setGemsScore(c.getGemsScore() - get_dmg_amount());
     }else{
        c.setGemsScore(0);
     }
     cout<<"thief executed with dmg ="<<get_dmg_amount()<<endl;
    }

};

//CLASS GEM
class Gem : public Cell{

private:
    int points;
public:
    Gem () : Cell(){
    this->points = 5+(rand() % 10);
    type='G';
    }
 int getPoints(){
    return points;
    }
 void setPoints(int Points){
     this->points = Points;
     }


 virtual void execute(Champion c){
 }
};

//CLASS POTION
class Potion : public Gem{
public:
void execute(Champion c){
if (c.getHealth()+ getPoints()<100){
        c.setHealth(c.getHealth()+getPoints());
}
else
     c.setHealth(100);

cout<<"Potion executed with points = "<< getPoints() <<endl;
}
};

//CLASS COIN
class Coin : public Gem{

public:
    void execute(Champion c){
    c.setGemsScore(c.getGemsScore()+getPoints());
    cout<<"Coin executed with points = "<< getPoints()<<endl;

    }
};



int main()
{
map m(10,10);
Champion c;
m.randomize_map();
m.print_map();

int choice;
char choicePlayer;
    cout<<"Please type in M if you want to play with the great Super Mario"<<endl;
    cout<<"Please type in L if you want to play with the Amazing Luigi"<<endl;
    cin>>choicePlayer;

//not complete
if(choicePlayer=='M'){
    Mario m;
    m.print_champ_info();
}
else if(choicePlayer=='L'){
    Luigi l;
    l.print_champ_info();
}
    cout<<"Please type in 2 : Randomize the map again"<<endl;
    cout<<"Or type in 1 : Eshta Cool I like the map"<<endl;
    cin>>choice;
while (choice ==2 ){
    cout<<"calling random"<<endl;
    m.randomize_map();
    system("cls");
    m.print_map();
    cout<<"Please type in 2 : Randomize the map again"<<endl;
    cout<<"Or type in 1 : Eshta Cool I like the map"<<endl;
    cin>>choice;
}
   if (choice == 1){
    m.move(c);
}
return 0;

}
