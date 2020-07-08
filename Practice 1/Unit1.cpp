//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    DoubleBuffered = true;
    Screen->Cursors[crNoDrop] = LoadCursorFromFile(".\\cursor\\Cursor 1 (G) (anim).ani");
    Screen->Cursor = crNoDrop; // Load Green-styled Cursor
    //img_list_hp->Draw(img_player_hp->Canvas, img_player_hp->Left, img_player_hp->Top, 6);
    img_player_hp->Picture->LoadFromFile(".\\hp_bars\\Health_bar_6.bmp");
    img_enemy1_hp->Picture->LoadFromFile(".\\hp_bars\\Health_bar_6.bmp");
}
//---------------------------------------------------------------------------

int move_length = 14;
int move_speed = 15;
int sprint_timer = 30;
int sprint_cooldown = 80; // 4.0 seconds cooldown

int low = 6;
int show_hp = 1;

int BPosX, BPosY, Bcd=0;

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
                show_hp = 1; break;
            }
            else
            {
                img_player_hp->Visible = false;
                img_enemy1_hp->Visible = false;
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
                move_length = 25; break; }
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
    if (Bcd <= 10)
    {
        if (img_bullet->Top>= -(img_bullet->Height/2))
        {
            img_bullet->Visible = true;
            if (false)
            {
            //  [if hit enemy or something else]
            }
            else img_bullet->Top -=80;
        }
        else { img_bullet->Visible = false; }
        Bcd++;
    }
    else { Bcd = 0; t_shoot->Enabled = false; }
}
//---------------------------------------------------------------------------





void __fastcall TForm1::t_enemy_1Timer(TObject *Sender)
{
    int HP = 6;
    img_enemy1_hp->Left = img_enemy_1->Left;
    img_enemy1_hp->Top = img_enemy_1->Top+img_enemy_1->Height+10;
    if ((img_bullet->Top <= img_enemy_1->Top-img_enemy_1->Height)&&(img_enemy_1->Left < img_bullet->Left+img_bullet->Width/2 < img_enemy_1->Left+img_enemy_1->Width))
    {
        if (HP-1 == 0) img_enemy_1->Visible = false;
        HP-=1;
        img_enemy1_hp->Picture->LoadFromFile(".\\hp_bars\\Health_bar_"+IntToStr(HP)+".bmp");
    }
}
//---------------------------------------------------------------------------

