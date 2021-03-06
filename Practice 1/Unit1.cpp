//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include <iostream.h>
#include <fstream.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
int pointsCount[8];
struct GraphicPoint
{ int X; int Y; };


int move_length = 14;
int move_speed = 15;
int sprint_timer = 30;
int sprint_cooldown = 80; // 4.0 seconds cooldown

int low = 6;
int show_hp = 1;

const int enemies = 10; //10 enemies + 1 player;
bool enemy_hit[enemies]; // [0] = player, [1+] = enemies
bool ship_destroyed[enemies];
bool enemy_hitted = false;
int enHP[enemies]; // [0] = player, [1+] = enemies

struct GraphicPointMass          // advanced GraphicPoint struct struct
{ GraphicPoint coord[enemies]; };

int point_id[enemies];
GraphicPointMass spawn_point[2]; // combines all spawn-points from all sets
GraphicPoint enemy_path_1[10]; // main
GraphicPoint enemy_path_2[18]; // 2L  S-form
GraphicPoint enemy_path_3[18]; // 2R  S-form



int BPosX, BPosY, Bcd=0;
//---------------------------------------------------------------------------    ������� �������������� � ���������������� ���
void load_path(char *filename, GraphicPoint *path, GraphicPointMass *coord, int sp_point, int point)
{
    ifstream f(filename);
    for (int i=0; i<enemies; i++)
    {   f>>coord[sp_point].coord[i].X>>coord[sp_point].coord[i].Y; }
    f>>pointsCount[point];
    for (int i=0; i<pointsCount[point]; i++)
    {   f>>path[i].X>>path[i].Y; };
    f.close();
}
//---------------------------------------------------------------------------    Constructor
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    for (int i=0; i<enemies; i++)
    {   enHP[i] = 6; enemy_hit[i] = false; point_id[i] = 0; ship_destroyed[i] = false; }

    DoubleBuffered = true;
    Screen->Cursors[crNoDrop] = LoadCursorFromFile(".\\cursor\\cur1.cur");
    Screen->Cursor = crNoDrop; // Load Green-styled Cursor

    load_path(".\\enemies_path\\1.txt", enemy_path_1, spawn_point, 0, 0);
    load_path(".\\enemies_path\\2L.txt", enemy_path_2, spawn_point, 1, 1);
    load_path(".\\enemies_path\\2R.txt", enemy_path_3, spawn_point, 1, 1);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    //ShowMessage(IntToStr(Key));

    /////////////// start move
    switch (Key)
    {
        case 49:
        case 97:  { t_move_left->Enabled = true; break; }
        case 51:
        case 100: { t_move_right->Enabled = true; break; }
        case 53:
        case 119: { t_move_up->Enabled = true; break; }
        case 50:
        case 115: { t_move_down->Enabled = true; break; }

        case 122: { low--; if (low==-1) low = 6;
            img_player_hp->Picture->LoadFromFile(".\\hp_bars\\Health_bar_"+IntToStr(low)+".bmp"); break; } // Z
        case 120: { low++; if (low==7) low = 1;
            img_player_hp->Picture->LoadFromFile(".\\hp_bars\\Health_bar_"+IntToStr(low)+".bmp"); break; } // X
        case 99:  { break; } // C

        case 32:
        {
            if (Bcd == 0)
            {
                BPosX = (img_player->Left + img_player->Width/2)-(img_bullet->Width/2);
                BPosY = img_player->Top + img_bullet->Top/2;
                img_bullet->Top = BPosY;
                img_bullet->Left = BPosX;
                t_shoot->Enabled = true; break;
            }
            else break;
        }
        case 104: // H
        {
            if (show_hp == 0)
            {
                img_player_hp->Visible = true;
                img_enemy1_hp->Visible = true;
                img_enemy2_hp->Visible = true;
                img_enemy3_hp->Visible = true;
                img_enemy4_hp->Visible = true;
                img_enemy5_hp->Visible = true;
                img_enemy6_hp->Visible = true;
                show_hp = 1; break;
            }
            else
            {
                img_player_hp->Visible = false;
                img_enemy1_hp->Visible = false;
                img_enemy2_hp->Visible = false;
                img_enemy3_hp->Visible = false;
                img_enemy4_hp->Visible = false;
                img_enemy5_hp->Visible = false;
                img_enemy6_hp->Visible = false;
                show_hp = 0; break;
            }
        }

        case 27:  { Form1->Close(); break; }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    //ShowMessage(IntToStr(Key));

    ////////////////// stop move
    switch (Key)
    {
        case 97:
        case 65: { t_move_left->Enabled = false; break; }
        case 99:
        case 68: { t_move_right->Enabled = false; break; }
        case 101:
        case 87: { t_move_up->Enabled = false; break; }
        case 98:
        case 83: { t_move_down->Enabled = false; break; }

        case 16: { if (sprint_cooldown>=79)
            {   t_sprint->Enabled = true;
                move_length = 30; break; }
            else break; };
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::t_move_leftTimer(TObject *Sender)
{
    if (img_player->Left <= 0)
    {
        img_player->Left = 0;
        t_move_left->Enabled = false;
    }
    else
    {
        img_player->Left -=move_length;
        img_player_hp->Left = img_player->Left;
        img_player_hp->Top = img_player->Top+img_player->Height+10;
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::t_move_upTimer(TObject *Sender)
{
    if (img_player->Top <= 0)
    {
        img_player->Top = 0;
        t_move_up->Enabled = false;
    }
    else
    {
        img_player->Top -=move_length;
        img_player_hp->Left = img_player->Left;
        img_player_hp->Top = img_player->Top+img_player->Height+10;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t_move_downTimer(TObject *Sender)
{
    if (img_player->Top+img_player->Height >= Form1->ClientHeight )
    {
        img_player->Top = Form1->ClientHeight-img_player->Height;
        t_move_down->Enabled = false;
    }
    else
    {
        img_player->Top +=move_length;
        img_player_hp->Left = img_player->Left;
        img_player_hp->Top = img_player->Top+img_player->Height+10;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t_move_rightTimer(TObject *Sender)
{
    if (img_player->Left+img_player->Width >= Form1->ClientWidth )
    {
        img_player->Left = Form1->ClientWidth-img_player->Width;
        t_move_right->Enabled = false;
    }
    else
    {
        img_player->Left +=move_length;
        img_player_hp->Left = img_player->Left;
        img_player_hp->Top = img_player->Top+img_player->Height+10;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t_sprintTimer(TObject *Sender)
{
    LMvBoost1->Caption = IntToStr(sprint_timer);
    if (sprint_timer == 0)
    {
        move_length = 14;
    }
    if (sprint_cooldown == 0)
    {
        sprint_timer = 30; sprint_cooldown = 80;
        t_sprint->Enabled = false; return;
    }
    if (sprint_timer!=0) sprint_timer--;
    sprint_cooldown--;
    LMvBoost1->Caption = IntToStr(sprint_timer);
    LBoostCd1->Caption = IntToStr(sprint_cooldown);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t_shootTimer(TObject *Sender)
{
    //img_explosion_effect->Visible = false;
    if (Bcd <= 10)
    {
        if (img_bullet->Top>= -(img_bullet->Height/2))
        {
            for (int i=0; i<8; i++)
            {   enemy_hitted = enemy_hitted||enemy_hit[i]; }
            if (enemy_hitted)
            {
            //  [ image_small_explosion.bmp ]
                /*img_explosion_effect->Visible = true;
                img_explosion_effect->Top = img_bullet->Top+80;
                img_explosion_effect->Left = img_bullet->Left+img_bullet->Width/2-img_explosion_effect->Width/2;
                */
                img_bullet->Left = -80; enemy_hitted = false;
            }
            else
            {
                img_bullet->Visible = true;
                img_bullet->Top -=80;
            }
        }
        else
        {
            img_bullet->Visible = false;
            img_bullet->Left = -80; enemy_hitted = false;
        }
        Bcd++;
    }
    else { Bcd = 0; t_shoot->Enabled = false; }
}
void enemie_shooter(TImage *bullet, bool ship_hitted)
{

}
//---------------------------------------------------------------------------
//(img_bullet->Top <= img_enemy_1->Top-img_enemy_1->Height)&&( )
//img_enemy_1->Left < img_bullet->Left+img_bullet->Width/2 < img_enemy_1->Left+img_enemy_1->Width

//---------------------------------------------------------------------------
void ship_structure (TImage *ship, TImage *health,TImage *bullet, int damage, int id, TImageList *list)
{
    if (enHP[id] != 0)
    {
        //health->Left = ship->Left;
        //health->Top = ship->Top+ship->Height+10;

        enemy_hit[id] = (bullet->Left+bullet->Width <= ship->Left+ship->Width) && (bullet->Left >= ship->Left) && (bullet->Top-100 <= ship->Top-ship->Height);

        if (enemy_hit[id])
        {
            if (enHP[id]-damage > 0)
            {
                Form1->img_bullet->Left = -80; enemy_hitted = false;
                enHP[id]-=damage;
                TRect rect(0,0,health->Width, health->Height);
                health->Canvas->Brush->Color = clLime;
                health->Canvas->FillRect(rect);
                list->Draw(health->Canvas, 0, 0, enHP[id]);
            }
            else
            {
                ship->Visible = false;
                TRect rect(0,0,health->Width, health->Height);
                health->Canvas->Brush->Color = clLime;
                health->Canvas->FillRect(rect);
                list->Draw(health->Canvas, 0, 0, enHP[6]);
                enHP[id] = 0; enemy_hit[id] = false;
                health->Visible = false; ship_destroyed[id] = true;
                return;
            }
        }
    }
}
//---------------------------------------------------------------------------    �������������� ��� �� ����-
void move_ship(TImage *img, TImage *health, const GraphicPoint &dest, int step, bool &need_move)
{
    int midX = img->Left + img->Width/2;
    int midY = img->Top + img->Height/2;
    int dx = dest.X - midX;
    int dy = dest.Y - midY;
    if(abs(dx)<step && abs(dy)<step)
    {
        need_move = false;
        return;
    }
    need_move = true; //*/
    double angle = atan2(dy, dx);
    img->Left += step*cos(angle);
    img->Top += step*sin(angle);                                             //  - �� ����.
    health->Left = img->Left+img->Width/2-health->Width/2;
    health->Top = img->Top+img->Height+10;
}
//-------------------------------------------------
bool all_ships_destroyed(int ship_id, int ship_num)
{
    bool all_destroyed = true;
    for (ship_id; ship_id<=ship_num; ship_id++)
    {
        all_destroyed = all_destroyed && ship_destroyed[ship_id];
    }
    return all_destroyed;
}
//---------------------------------------------------------------------------
void ship_rebuild(int ship_id, TImage *ship, TImage *health, TImageList *list)
{
    ship->Visible = true;
    TRect rect(0,0,health->Width, health->Height);
    health->Canvas->Brush->Color = clLime;
    health->Canvas->FillRect(rect);
    enHP[ship_id] = 6; list->Draw(health->Canvas, 0, 0, enHP[ship_id]);
    enemy_hit[ship_id] = false;
    health->Visible = true; ship_destroyed[ship_id] = false;
}
void ship_regenegate(int ship_id, int ship_num)
{
    for (ship_id; ship_id<=ship_num; ship_id++)
    {
        //ship_rebuild
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::t_enemy_1Timer(TObject *Sender)
{
    randomize();
    bool need_move;
    int _switch = 1;
    ship_structure(img_enemy_1, img_enemy1_hp, img_bullet, 1, 1, img_list_hp);
    ship_structure(img_enemy_2, img_enemy2_hp, img_bullet, 1, 2, img_list_hp);
    ship_structure(img_enemy_3, img_enemy3_hp, img_bullet, 1, 3, img_list_hp);
    ship_structure(img_enemy_4, img_enemy4_hp, img_bullet, 1, 4, img_list_hp);
    ship_structure(img_enemy_5, img_enemy5_hp, img_bullet, 1, 5, img_list_hp);
    ship_structure(img_enemy_6, img_enemy6_hp, img_bullet, 1, 6, img_list_hp);

    if (all_ships_destroyed(1, 6))
    {
        _switch = 0+rand()%3;

        ship_rebuild(1, img_enemy_1, img_enemy1_hp, img_list_hp);
        ship_rebuild(2, img_enemy_2, img_enemy2_hp, img_list_hp);
        ship_rebuild(3, img_enemy_3, img_enemy3_hp, img_list_hp);
        ship_rebuild(4, img_enemy_4, img_enemy4_hp, img_list_hp);
        ship_rebuild(5, img_enemy_5, img_enemy5_hp, img_list_hp);
        ship_rebuild(6, img_enemy_6, img_enemy6_hp, img_list_hp);
    /*  ship_rebuild(1, img_enemy_1, img_enemy1_hp, img_list_hp);
        ship_rebuild(1, img_enemy_1, img_enemy1_hp, img_list_hp);
        ship_rebuild(1, img_enemy_1, img_enemy1_hp, img_list_hp);
        ship_rebuild(1, img_enemy_1, img_enemy1_hp, img_list_hp); // */

        img_enemy_1->Left = spawn_point[_switch].coord[0].X; img_enemy_1->Top = spawn_point[_switch].coord[0].Y;
        img_enemy_2->Left = spawn_point[_switch].coord[1].X; img_enemy_2->Top = spawn_point[_switch].coord[1].Y;
        img_enemy_3->Left = spawn_point[_switch].coord[2].X; img_enemy_3->Top = spawn_point[_switch].coord[2].Y;
        img_enemy_4->Left = spawn_point[_switch].coord[3].X; img_enemy_4->Top = spawn_point[_switch].coord[3].Y;
        img_enemy_5->Left = spawn_point[_switch].coord[4].X; img_enemy_5->Top = spawn_point[_switch].coord[4].Y;
        img_enemy_6->Left = spawn_point[_switch].coord[5].X; img_enemy_6->Top = spawn_point[_switch].coord[5].Y;
    /*  img_enemy_1->Left = spawn_point[_switch].coord[0].X; img_enemy_1->Top = spawn_point[_switch].coord[0].Y;
        img_enemy_1->Left = spawn_point[_switch].coord[0].X; img_enemy_1->Top = spawn_point[_switch].coord[0].Y;
        img_enemy_1->Left = spawn_point[_switch].coord[0].X; img_enemy_1->Top = spawn_point[_switch].coord[0].Y;
        img_enemy_1->Left = spawn_point[_switch].coord[0].X; img_enemy_1->Top = spawn_point[_switch].coord[0].Y; // */
    }
    switch (_switch)
    {
        case 1: {
        move_ship(img_enemy_1, img_enemy1_hp, enemy_path_1[point_id[0]], 10, need_move);
        if(!need_move) point_id[0] = (point_id[0]+1) % pointsCount[0];
        move_ship(img_enemy_2, img_enemy2_hp, enemy_path_1[point_id[1]], 10, need_move);
        if(!need_move) point_id[1] = (point_id[1]+1) % pointsCount[0];
        move_ship(img_enemy_3, img_enemy3_hp, enemy_path_1[point_id[2]], 10, need_move);
        if(!need_move) point_id[2] = (point_id[2]+1) % pointsCount[0];
        move_ship(img_enemy_4, img_enemy4_hp, enemy_path_1[point_id[3]], 10, need_move);
        if(!need_move) point_id[3] = (point_id[3]+1) % pointsCount[0];
        move_ship(img_enemy_5, img_enemy5_hp, enemy_path_1[point_id[4]], 10, need_move);
        if(!need_move) point_id[4] = (point_id[4]+1) % pointsCount[0];
        move_ship(img_enemy_6, img_enemy6_hp, enemy_path_1[point_id[5]], 10, need_move);
        if(!need_move) point_id[5] = (point_id[5]+1) % pointsCount[0];// */
        break; }

        case 2: {
        move_ship(img_enemy_1, img_enemy1_hp, enemy_path_2[point_id[0]], 10, need_move);
        if(!need_move) point_id[0] = (point_id[0]+1) % pointsCount[1];
        move_ship(img_enemy_2, img_enemy2_hp, enemy_path_2[point_id[1]], 10, need_move);
        if(!need_move) point_id[1] = (point_id[1]+1) % pointsCount[1];
        move_ship(img_enemy_3, img_enemy3_hp, enemy_path_2[point_id[2]], 10, need_move);
        if(!need_move) point_id[2] = (point_id[2]+1) % pointsCount[1];
        move_ship(img_enemy_4, img_enemy4_hp, enemy_path_3[point_id[3]], 10, need_move);
        if(!need_move) point_id[3] = (point_id[3]+1) % pointsCount[2];
        move_ship(img_enemy_5, img_enemy5_hp, enemy_path_3[point_id[4]], 10, need_move);
        if(!need_move) point_id[4] = (point_id[4]+1) % pointsCount[2];
        move_ship(img_enemy_6, img_enemy6_hp, enemy_path_3[point_id[5]], 10, need_move);
        if(!need_move) point_id[5] = (point_id[5]+1) % pointsCount[2];
        break; }
    }
    if (all_ships_destroyed(1, 6)) LMvSpeed1->Caption = "True";
    else LMvSpeed1->Caption = "False";

}
//---------------------------------------------------------------------------







