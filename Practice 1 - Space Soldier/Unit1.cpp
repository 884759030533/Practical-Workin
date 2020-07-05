//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tmain_form *main_form;

int tick_counter = 200;    // num of ticks for movement   5 ticks per second in normal speed
                           //                            20 ticks per second with boost

int sprint_time = 30;      // 3.0 seconds boost (4 times faster)
int sprint_cooldown = 100;  // 7.0 seconds cooldown

int PlPosX = 32;   //    spawn
int PlPosY = 15;   //    point

long bulletXY[2][32767];
int bullet_count = 0;

const int max_x = 64, max_y = 30;  // max points
int grid_pos[max_x][max_y];        // spacefield data

//---------------------------------------------------------------------------
void grid_zero()
{
    for (int i=0; i<max_x; i++)
    {
        for (int j=0; j<max_y; j++)
        {
            grid_pos[i][j] = 0;
        }
    }
}
void draw_ship(int shipID, int shipX, int shipY) // drawing ship at pos(x,y)
{
    for (int j=1;j<=2;j++)
    for (int i=1;i<=3;i++)
    {
        if (true)
        {
            grid_pos[shipX+i][shipY+j] = shipID;
            shipID++;
        }
    }
    /*for (int j=1;j<=2;j++)
    for (int i=1;i<=3;i++)
    {
        main_form->sprite_list->DrawOverlay(main_form->main_grid->Canvas, Rect.Left, Rect.Top, shipID);
        shipID++;
    }// */
}
void player_bullet(int bulletID, int bulletX, int bulletY)
{
    grid_pos[bulletX][bulletY] = bulletID;
}
//---------------------------------------------------------------------------
__fastcall Tmain_form::Tmain_form(TComponent* Owner)
    : TForm(Owner)
{
    //DoubleBuffered = true;
    //Screen->Cursors[crNoDrop] = LoadCursorFromFile("G_cur.ani");
    //Screen->Cursor = crNoDrop; // Load Green-styled Cursor


    draw_ship(1, PlPosX, PlPosY);
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::main_gridDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    sprite_list->Draw(main_grid->Canvas, Rect.Left, Rect.Top, grid_pos[ACol][ARow]); // transparent background
    //Invalidate();
}
//---------------------------------------------------------------------------



void __fastcall Tmain_form::main_gridKeyPress(TObject *Sender, char &Key)
{
    //ShowMessage(IntToStr(Key));

    switch (Key)
    {
        case 97:  { t_move_left->Enabled = true; break; }; // left
        case 100: { t_move_right->Enabled = true; break; }; // right
        case 119: { t_move_up->Enabled = true; break; }; // up
        case 115: { t_move_down->Enabled = true; break; }; // down

        //case 32: { t_bullet->Enabled = true; bullet_count++;  break; }; // do not work at all

        case 27: { main_form->Close(); break; };
    }
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::main_gridKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    switch (Key)
    {
        case 65: { t_move_left->Enabled = false; break; }; // left
        case 68: { t_move_right->Enabled = false; break; }; // right
        case 87: { t_move_up->Enabled = false; break; }; // up
        case 83: { t_move_down->Enabled = false; break; }; // down

        case 16: {
            if (sprint_cooldown>=79)
            {   t_sprint->Enabled = true; tick_counter = 50; break; }
            else break; };

        case 27: { main_form->Close(); break; };
    }
}
//---------------------------------------------------------------------------



void __fastcall Tmain_form::t_move_leftTimer(TObject *Sender)
{
    t_move_left->Interval = tick_counter;
    if ((PlPosX-1)!=-2)
    {
        PlPosX-=1; grid_zero();
        draw_ship(1, PlPosX, PlPosY);
        main_grid->Invalidate();
    }
    else t_move_left->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::t_move_rightTimer(TObject *Sender)
{
    t_move_right->Interval = tick_counter;
    if ((PlPosX+1)!=max_x-3)
    {
        PlPosX+=1; grid_zero();
        draw_ship(1, PlPosX, PlPosY);
        main_grid->Invalidate();
    }
    else t_move_right->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::t_move_upTimer(TObject *Sender)
{
    t_move_up->Interval = tick_counter;
    if ((PlPosY+1)!=0)
    {
        PlPosY-=1; grid_zero();
        draw_ship(1, PlPosX, PlPosY);
        main_grid->Invalidate();
    }
    else t_move_up->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::t_move_downTimer(TObject *Sender)
{
    t_move_down->Interval = tick_counter;
    if ((PlPosY-1)!=max_y-4)
    {
        PlPosY+=1; grid_zero();
        draw_ship(1, PlPosX, PlPosY);
        main_grid->Invalidate();
    }
    else t_move_right->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::t_sprintTimer(TObject *Sender)
{
    if (sprint_time == 0)
    {
        tick_counter = 200;
    }
    if (sprint_cooldown == 0)
    {
        sprint_time = 20; sprint_cooldown = 80;
        t_sprint->Enabled = false;
    }
    sprint_time--;
    sprint_cooldown--;
}
//---------------------------------------------------------------------------


void __fastcall Tmain_form::t_bulletTimer(TObject *Sender)
{
    bulletXY[0][bullet_count] = PlPosX;
    bulletXY[1][bullet_count] = PlPosY;

    player_bullet(7, bulletXY[0][bullet_count], bulletXY[1][bullet_count]);

    bulletXY[1][bullet_count]+=1;

    main_grid->Invalidate();
}
//---------------------------------------------------------------------------

