#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include <WinBase.h>
using namespace std;
int indexOfCells=0;

struct Cell{
    int x;
    int y;
};
Cell moves[8]={ {2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1} };
class Knight{
    public:
        int **table;
        Cell cells[64];
        Knight(int **table_);

};
Knight::Knight(int **table_){
        table=table_;
}
int getNumOfMove(int **table,int x,int y){
     if(x>=8 || x<0 || y>=8 || y<0 || table[x][y]==1){
        return 9;
    }
    int numOfMove=0;
    for(int i=0;i<8;i++){
        if(x+moves[i].x<8 && y+ moves[i].y<8 && x+moves[i].x>=0 && y+ moves[i].y>=0 && table[x+ moves[i].x][y+ moves[i].y]==0){
            numOfMove++;
        }
    }
    return numOfMove;
}
int getIndexOfMinMove(int numOfMove[]){
    int index=9;
    int minMove=9;
    for(int i=0;i<8;i++){
            if(numOfMove[i]<minMove){
                minMove=numOfMove[i];
                index=i;
            }
    }
    return index;
}
int *nextMove(int **table,int indexOfMinMove,int x,int y){
    int *xy = (int *)malloc(sizeof(int *) * 2);
    for(int i=0;i<8;i++){
        if(indexOfMinMove==i){
            table[x+moves[i].x][y+moves[i].y]=1;
            xy[0]=x+moves[i].x;
            xy[1]=y+moves[i].y;
            return xy;
        }
    }
}
int main(void){

    sf::Font font;
    if (!font.loadFromFile("CURLZ.TTF"))
        cout << "Error";
    int state=0;
    int x,y;
    sf::RenderWindow window(sf::VideoMode(820, 620), "Knight`s Tour!");
    sf::Texture texture1;
    sf::Sprite sprite1;
    if (!texture1.loadFromFile("Background.png")){
        cout << "Error\n";
    }
    sf::Texture texture2;
    sf::Sprite sprite2;
    if (!texture2.loadFromFile("BackgroundStart.jpg")){
        cout << "Error\n";
    }
    sprite1.setTexture(texture1);
    sprite2.setTexture(texture2);

    while (window.isOpen()){

        sprite2.setPosition(5,46);
        while(state==0){
            int x1,y1;
            window.clear();
            sf::Text play,welcome;
            play.setString("Start");
            play.setFont(font);
            play.setColor(sf::Color::Red);
            play.setCharacterSize(100);
            play.setPosition(40,420);
            welcome.setString("Welcome To Knight`s Tour");
            welcome.setFont(font);
            welcome.setColor(sf::Color::Red);
            welcome.setCharacterSize(55);
            welcome.setPosition(150,40);
            sf::Event event3;
            while (window.pollEvent(event3)){
                if (event3.type == sf::Event::Closed)
                    window.close();
                if ( event3.type == sf::Event::MouseMoved ){
                    x1=event3.mouseMove.x;
                    y1=event3.mouseMove.y;
                }
                if(event3.type==sf::Event::MouseButtonPressed){
                    if(event3.mouseButton.button==sf::Mouse::Left){
                        if(x1>40&&x1<240&&y1>420&&y1<520)
                            state=1;
                    }
                }
            }
            if(x1>40&&x1<240&&y1>420&&y1<520){
                play.setStyle(sf::Text::Bold | sf::Text::Underlined );
                play.setColor(sf::Color::Green);
            }
            window.draw(sprite2);
            window.draw(play);
            window.draw(welcome);
            window.display();
        }
        sprite1.setPosition(206.5,7);
        while(state==1){
            int mouseX=-1,mouseY=-1;
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.mouseButton.button == sf::Mouse::Left){
                        mouseY=(event.mouseButton.x-225)/70;
                        mouseX=(event.mouseButton.y-25)/70;
                    }
                }
            }
            if(mouseX>=0 && mouseX<8 && mouseY>=0 && mouseY<8){
                x=mouseX;
                y=mouseY;
                state=2;
            }
            window.clear();
            window.draw(sprite1);
            window.display();
        }
        system("cls");
        int i,j;
        int **table = (int **)malloc(sizeof(int *) * 8);
        for(i=0; i< 8; i++)
            table[i] = (int (*))malloc(sizeof(int) * 8);

        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                table[i][j]=0;
            }
        }
        table[x][y]=1;
        Knight knight(table);
        knight.cells[indexOfCells].x=x;
        knight.cells[indexOfCells].y=y;
        indexOfCells++;
        while(1){
            int numOfMove[8]={0};
            for(int p=0;p<8;p++){
                numOfMove[p]=getNumOfMove(table,x+moves[p].x,y+moves[p].y);
            }
            int indexOfMinMove=getIndexOfMinMove(numOfMove);
            int *xy;
            xy=nextMove(table,indexOfMinMove,x,y);
            x=xy[0];
            y=xy[1];
            knight.cells[indexOfCells].x=x;
            knight.cells[indexOfCells].y=y;
            indexOfCells++;
            if(indexOfCells==64){
                break;
            }
        }
        for(i=0;i<64;i++){
            cout << "(" << knight.cells[i].x << "," << knight.cells[i].y << ")" << " ";
            if((i+1)%8==0)
                cout << endl;
        }
        int index=0;
        sf::Texture knights;
        if(!knights.loadFromFile("Knight.png"))
            cout << "Error";

        sf::Texture zarbdar;
        if(!zarbdar.loadFromFile("zarbdar.png")){
            cout << "Error";
        }
        sf::RectangleShape zarb(sf::Vector2f(68,68));
        zarb.setTexture(&zarbdar);
        zarb.setPosition(400,200);
        while(state==2){
            int xCor,yCor;
            sf::Text next,solve,previous,restart;

            restart.setString("Restart");
            restart.setFont(font);
            restart.setColor(sf::Color::White);
            restart.setCharacterSize(50);
            restart.setPosition(50,500);

            next.setString("Next");
            next.setFont(font);
            next.setColor(sf::Color::White);
            next.setCharacterSize(50);
            next.setPosition(50,200);

            previous.setString("Previous");
            previous.setFont(font);
            previous.setColor(sf::Color::White);
            previous.setCharacterSize(40);
            previous.setPosition(50,140);

            solve.setString("Solve Fast");
            solve.setFont(font);
            solve.setColor(sf::Color::White);
            solve.setCharacterSize(30);
            solve.setPosition(50,300);

            int thisX=knight.cells[index].x;
            int thisY=knight.cells[index].y;
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
                if ( event.type == sf::Event::MouseMoved ){
                    xCor=event.mouseMove.x;
                    yCor=event.mouseMove.y;
                }
                if(event.type==sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button==sf::Mouse::Left){
                        if(xCor>50&&xCor<200&&yCor>510&&yCor<550){
                            indexOfCells=0;
                            state=1;
                        }
                    }
                }
                if(event.type==sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button==sf::Mouse::Left){
                        if(xCor>50&&xCor<200&&yCor>140&&yCor<190)
                            if(index>0)
                                index--;
                    }
                }
                if(event.type==sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button==sf::Mouse::Left){
                        if(xCor>50&&xCor<160&&yCor>200&&yCor<260)
                            if(index<63)
                                index++;
                    }
                }
                if(event.type==sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button==sf::Mouse::Left){
                        if(xCor>50&&xCor<170&&yCor>300&&yCor<330)
                            state=3;
                    }
                }
            }

            if(xCor>50&&xCor<200&&yCor>510&&yCor<550){
                restart.setStyle(sf::Text::Bold | sf::Text::Underlined );
                restart.setColor(sf::Color::Red);
            }
            if(xCor>50&&xCor<200&&yCor>140&&yCor<190){
                previous.setStyle(sf::Text::Bold | sf::Text::Underlined );
                previous.setColor(sf::Color::Green);
            }
            if(xCor>50&&xCor<160&&yCor>200&&yCor<260){
                next.setStyle(sf::Text::Bold | sf::Text::Underlined );
                next.setColor(sf::Color::Green);
            }
            if(xCor>50&&xCor<170&&yCor>300&&yCor<330){
                solve.setStyle(sf::Text::Bold | sf::Text::Underlined );
                solve.setColor(sf::Color::Green);
            }
            sf::RectangleShape knightRect(sf::Vector2f(70,70));
            knightRect.setTexture(&knights);
            knightRect.setPosition(225+70*thisY,25+70*thisX);
            window.clear();
            window.draw(sprite1);
            for(int k=0;k<index;k++){
                int xPosition=227.5 +knight.cells[k].y * 70,yPosition=30+knight.cells[k].x*70;
                zarb.setPosition(xPosition ,yPosition);
                window.draw(zarb);
            }

            window.draw(knightRect);
            window.draw(next);
            window.draw(solve);
            window.draw(restart);
            window.draw(previous);
            window.display();
        }
        while(state==3){
            int thisX=knight.cells[index].x;
            int thisY=knight.cells[index].y;
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            sf::RectangleShape knightRect(sf::Vector2f(70,70));
            knightRect.setTexture(&knights);
            knightRect.setPosition(225+70*thisY,25+70*thisX);
            window.clear();
            window.draw(sprite1);
            for(int k=0;k<index;k++){
                int xPosition=227.5 +knight.cells[k].y * 70,yPosition=30+knight.cells[k].x*70;
                zarb.setPosition(xPosition ,yPosition);
                window.draw(zarb);
            }
            window.draw(knightRect);
            window.display();
            Sleep(500);
            if(index<63)
                index++;
            if(index==64)
                state==4;
        }
        window.display();
    }
    return 0;
}
