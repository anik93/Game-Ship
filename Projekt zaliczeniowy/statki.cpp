
#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

float angle=0.0;
int mx;
int my;
bool player = true;
int licznikPlayer1 = 0;
int licznikPlayer2 = 0;
bool czyGra = false;
bool zlyStatek1 = true;
bool zlyStatek2 = true;
bool wygra1 = false;
bool wygra2 = false;

enum StanGry{
    puste, statek, trafiony, nieTrafiony, podswietl
};
StanGry stanPlayer1[10][10];
StanGry stanPlayer2[10][10];
void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            stanPlayer1[i][j]=puste;
            stanPlayer2[i][j]=puste;
        }
    }
}

void togglePlayer(){
    player=!player;
}

void kawardat(){
    glBegin(GL_QUADS);
        glVertex3f( -0.5, -0.5, 0.0);
        glVertex3f( 0.5, -0.5, 0.0);
        glVertex3f( 0.5, 0.5, 0.0);
        glVertex3f( -0.5, 0.5, 0.0);
    glEnd();
}

void podswietlTo(float mx, float my){
    printf(" %s","kk");
    int wx = 115;
    int wy = -5;
    bool flaga = false;

    for(int i=0; i<10; i++){

        for(int j=0; j<10; j++){

            for(int k=0; k<10; k++){
                for(int l=0; l<10; l++){
                    if(stanPlayer1[k][l]==podswietl)
                        stanPlayer1[k][l]=puste;
                    if(stanPlayer2[k][l]==podswietl)
                        stanPlayer2[k][l]=puste;
                }
            }

            if(mx>wx && mx<wx+53 && my>wy && my<wy+53){
                if(player && stanPlayer1[i][j]==puste){
                    stanPlayer1[i][j]=podswietl;
                    flaga=true;
                } else if(!player && stanPlayer2[i][j]==puste){
                    stanPlayer2[i][j]=podswietl;
                    flaga=true;
                }
                break;
            }
            wx += 50;
        }
        if(flaga)
            break;
        wx = 115;
        wy += 50;
    }
}

void klik(float mx, float my){
    int wx = 115;
    int wy = -5;
    bool flaga = false;


    for(int i=0; i<10; i++){

        for(int j=0; j<10; j++){

            if(mx>wx && mx<wx+53 && my>wy && my<wy+53){
                if(stanPlayer1[i][j]==statek && player && !czyGra){
                    zlyStatek1=true;
                    break;
                } else if (stanPlayer2[i][j]==statek && !player && !czyGra){
                    zlyStatek2=true;
                    break;
                }
                flaga=true;
                if(stanPlayer1[i][j]==puste && player && !czyGra && stanPlayer1[i][j]!=statek){
                    stanPlayer1[i][j]=statek;
                    licznikPlayer1++;
                    zlyStatek1=false;
                    break;
                } else if(stanPlayer2[i][j]==statek && player && czyGra){
                    stanPlayer2[i][j]=trafiony;
                    break;
                } else if(stanPlayer2[i][j]==puste && player && czyGra){
                    stanPlayer2[i][j]=nieTrafiony;
                    break;

                } else if(stanPlayer2[i][j]==puste && !player && !czyGra && stanPlayer2[i][j]!=statek){
                    stanPlayer2[i][j]=statek;
                    licznikPlayer2++;
                    zlyStatek2=false;
                    break;
                } else if(stanPlayer1[i][j]==statek && !player && czyGra){
                    stanPlayer1[i][j]=trafiony;
                    break;
                } else if(stanPlayer1[i][j]==puste && !player && czyGra){
                    stanPlayer1[i][j]=nieTrafiony;
                    break;
                }
                break;
            }
            wx += 50;
        }
        if(flaga)
            break;
        wx = 115;
        wy += 50;
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-13);
    float ky = 4.9;
    float kx =  -4;
    int licznikWygral1=0;
    int licznikWygral2=0;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(stanPlayer1[i][j]==trafiony){
                licznikWygral2++;
            }
            if(stanPlayer2[i][j]==trafiony){
                licznikWygral1++;
            }
        }
    }

    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){

            glPushMatrix();
            glTranslatef(kx,ky,0);
            //player 1
            if(player){
                if(!czyGra){
                    if(stanPlayer1[i][j]==puste){
                        glColor3f(1.0,0.5,0.5);
                    }else if(stanPlayer1[i][j]==podswietl){
                        glColor3f(0.0,0.5,0.5);
                    }else if(stanPlayer1[i][j]==statek){
                        glColor3f(0.5,0.5,0.5);
                    }
                }else{
                    if(stanPlayer2[i][j]==trafiony){
                        glColor3f(1,0,0);
                    }else if(stanPlayer2[i][j]==nieTrafiony){
                        glColor3f(1,1,1);
                    }else if(stanPlayer2[i][j]==puste || stanPlayer2[i][j]==statek){
                        glColor3f(1.0,0.5,0.5);
                    }
                }
            //player 2
            } else {
                if(!czyGra){
                    if(stanPlayer2[i][j]==puste){
                        glColor3f(1.0,0.5,0.5);
                    }else if(stanPlayer2[i][j]==podswietl){
                        glColor3f(0.0,0.5,0.5);
                    }else if(stanPlayer2[i][j]==statek){
                        glColor3f(0.5,0.4,0.2);
                    }
                }else{
                    if(stanPlayer1[i][j]==trafiony){
                        glColor3f(1,0,0);
                    }else if(stanPlayer1[i][j]==nieTrafiony){
                        glColor3f(1,1,1);
                    }else if(stanPlayer1[i][j]==puste || stanPlayer1[i][j]==statek){
                        glColor3f(1.0,0.5,0.5);
                    }
                }
            }

            if(licznikWygral1==10){
                glColor3f(0.0,0.0,0.0);
            } else if(licznikWygral2==10){
                glColor3f(0.0,0.0,0.0);
            }
            kawardat();
            glPopMatrix();
            kx += 1.1;
        }
        kx = -4;
        ky -=1.1;
        if(licznikPlayer1==10 && licznikPlayer2==10){
            czyGra=true;
        }
    }
}

int main(int argc, char* args[])
{

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int petla=1;
//    Uint32 start;
    SDL_Event myevent;
    init();
    while (petla==1)
    {
//        start=SDL_GetTicks();
        while (SDL_PollEvent(&myevent))
        {

            switch(myevent.type)
            {
                case SDL_QUIT:
                petla=0;
                break;

                case SDL_KEYDOWN:
                    if (myevent.key.keysym.sym==SDLK_SPACE)

                        break;

                case SDL_MOUSEMOTION:
                        mx=myevent.button.x;
                        my=myevent.button.y;

                        podswietlTo(mx,my);
                        break;

                case SDL_MOUSEBUTTONDOWN:
                        if (myevent.button.button==SDL_BUTTON_LEFT){
                            klik(mx,my);
                            if(!zlyStatek1 || !zlyStatek2){
                                togglePlayer();
                                zlyStatek1=true;
                                zlyStatek2=true;
                            }
                            if(czyGra){
                                togglePlayer();
                            }
                        }
                        break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
//        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
