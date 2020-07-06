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

int EnPosX = 32;
int EnPosY = 4;

long bulletXY[2][32767];
int bullet_count = -1, b_counter;

const int max_x = 64, max_y = 30;  // max points
int grid_pos[max_x][max_y];        // spacefield data

int debug=0;
//---------------------------------------------------------------------------
void draw_ship(int shipID, int shipX, int shipY);
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
//---------------------------------------------------------------------------    Drawing algorythms
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
    /*if (bulletY+2!=0)
    {
        switch (bulletY)
        {
            case 8:
            case 11: { };
            case 9:
            case 12: { };
            case 10:
            case 13: { };
        }
    } // */
    if (bulletY>=0) {
        grid_pos[bulletX][bulletY] = bulletID;
        grid_pos[bulletX][bulletY+2] = 0; }
    else {
        grid_pos[bulletX][bulletY+2] = 0;
        main_form->t_bullet->Enabled = false; }
}
//---------------------------------------------------------------------------    Constructor
__fastcall Tmain_form::Tmain_form(TComponent* Owner)
    : TForm(Owner)
{
    //DoubleBuffered = true;
    //Screen->Cursors[crNoDrop] = LoadCursorFromFile("G_cur.ani");
    //Screen->Cursor = crNoDrop; // Load Green-styled Cursor


    draw_ship(1, PlPosX, PlPosY);
}
//---------------------------------------------------------------------------    Creating grid

void __fastcall Tmain_form::main_gridDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    sprite_list->Draw(main_grid->Canvas, Rect.Left, Rect.Top, grid_pos[ACol][ARow]); // transparent background
    //Invalidate();
}
//---------------------------------------------------------------------------    ENABLE MOVE



void __fastcall Tmain_form::main_gridKeyPress(TObject *Sender, char &Key)
{
    //ShowMessage(IntToStr(Key));


    switch (Key)
    {
        case 97:  { t_move_left->Enabled = true; break; }; // left
        case 100: { t_move_right->Enabled = true; break; }; // right
        case 119: { t_move_up->Enabled = true; break; }; // up
        case 115: { t_move_down->Enabled = true; break; }; // down

        case 32: {
            bullet_count++;
            bulletXY[0][bullet_count] = PlPosX+2;
            bulletXY[1][bullet_count] = PlPosY-2;

            t_bullet->Enabled = true;
            break; };
        case 96: {
            if (debug==0) { debug_form->Show(); main_form->SetFocus(); debug++; }
            else { debug_form->Close(); debug--; }
            break; }
        case 27: { main_form->Close(); break; };
    }
}
//---------------------------------------------------------------------------    STOP MOVE

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
            if (sprint_cooldown>=79) { t_sprint->Enabled = true; tick_counter = 50; break; }
            else break; };

        case 27: { main_form->Close(); break; };
    }
}
//---------------------------------------------------------------------------    MOVE LEFT



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
//---------------------------------------------------------------------------    MOVE RIGHT

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
//---------------------------------------------------------------------------    MOVE UP

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
//---------------------------------------------------------------------------    MOVE DOWN

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
        sprint_time = 30; sprint_cooldown = 80;
        t_sprint->Enabled = false; return;
    }
    if (sprint_time!=0) sprint_time--;
    sprint_cooldown--;
    debug_form->L_boost_time->Caption = "Boost Time "+IntToStr(sprint_time);
    debug_form->L_boost_cd->Caption = "Boost Cooldown "+IntToStr(sprint_cooldown);
}
//---------------------------------------------------------------------------


void __fastcall Tmain_form::t_bulletTimer(TObject *Sender)
{

    player_bullet(7, bulletXY[0][bullet_count], bulletXY[1][bullet_count]);

    bulletXY[1][bullet_count]-=2;

    main_grid->Invalidate();
}

//---------------------------------------------------------------------------

void __fastcall Tmain_form::t_enemyTimer(TObject *Sender)
{
    if ((EnPosX&&EnPosX+1&&EnPosX+2&&EnPosY&&EnPosY+1)==7)
    { t_enemy->Enabled = false; return; }
    draw_ship(8, EnPosX, EnPosY);
}
//---------------------------------------------------------------------------

