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
    Screen->Cursors[crNoDrop] = LoadCursorFromFile("G_cur.ani");
    Screen->Cursor = crNoDrop; // Load Green-styled Cursor
}
//---------------------------------------------------------------------------

int move_length = 20;
int move_speed = 100;
int sprint_timer = 0;
int sprint_cooldown = 80; // 4.0 seconds cooldown

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    //ShowMessage(IntToStr(Key));

    /////////////// start move
    switch (Key)
    {
        case 97:  { t_move_left->Interval = move_speed; break; }
        case 100: { t_move_right->Interval = move_speed; break; }
        case 119: { t_move_up->Interval = move_speed; break; }
        case 115: { t_move_down->Interval = move_speed; break; }

        case 37: { t_move_left->Interval = move_speed; break; }
        case 39: { t_move_right->Interval = move_speed; break; }
        case 38: { t_move_up->Interval = move_speed; break; }
        case 40: { t_move_down->Interval = move_speed; break; }

        case 122: { move_speed/=2; LMvSpeed1->Caption = move_speed; break; }
        case 120: { move_speed*=2; LMvSpeed1->Caption = move_speed; break; }

        /*case 32: {
            if ( (sprint_timer>=0) && (sprint_cooldown<=0) ) break;
            sprint_timer = 55;  // 1.5 seconds
            move_length = 10;   // 2.2 times faster
            t_sprint->Enabled = true;
            t_sprint_cd->Enabled = true;
            break; }  // */

        //case '1': { img_bg->Align = alLeft; break; }
        //case '2': { img_bg->Align = alBottom; break; }
        //case '3': { img_bg->Align = alRight; break; }

        case 27:  { Form1->Close(); break; }
    } //*/
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

    //ShowMessage(IntToStr(Key));

    ////////////////// stop move
    switch (Key)
    {
        case 65: { t_move_left->Interval = 0; break; }
        case 68: { t_move_right->Interval = 0; break; }
        case 87: { t_move_up->Interval = 0; break; }
        case 83: { t_move_down->Interval = 0; break; }

        case 37: { t_move_left->Interval = 0; break; }
        case 39: { t_move_right->Interval = 0; break; }
        case 38: { t_move_up->Interval = 0; break; }
        case 40: { t_move_down->Interval = 0; break; }

        case 16: {
            if ( (sprint_timer>=0) && (sprint_cooldown<=1) ) break;
            sprint_timer = 20;  // 1.5 seconds
            move_length = 40;   // 2.2 times faster
            LMvLenTxt->Caption = IntToStr(move_length);
            t_sprint->Enabled = true;
            t_sprint_cd->Enabled = true;
            break; }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::t_move_leftTimer(TObject *Sender)
{
    if (img_move_test->Left <= 0)
    {
        img_move_test->Left = 0;
        t_move_left->Interval = 0;

    }
    else img_move_test->Left -=move_length;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::t_move_upTimer(TObject *Sender)
{
    if (img_move_test->Top <= 0)
    {
        img_move_test->Top = 0;
        t_move_up->Interval = 0;
    }
    else img_move_test->Top -=move_length;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t_move_downTimer(TObject *Sender)
{
    if (img_move_test->Top+60 >= 530 )
    {
        img_move_test->Top = 470;
        t_move_down->Interval = 0;
    }
    img_move_test->Top +=move_length;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t_move_rightTimer(TObject *Sender)
{
    if (img_move_test->Left+60 >= 1072 )
    {
        img_move_test->Left = 1012;
        t_move_right->Interval = 0;
    }
    img_move_test->Left +=move_length;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t_sprintTimer(TObject *Sender)
{
    LMvBoost1->Caption = IntToStr(sprint_timer);
    sprint_timer--;
    if (sprint_timer <= 0)
    {
        move_length = 5;
        LMvLenTxt->Caption = IntToStr(move_length);
        LMvBoost1->Caption = "0";
        t_sprint->Enabled = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::t_sprint_cdTimer(TObject *Sender)
{
    LBoostCd1->Caption = IntToStr(sprint_cooldown);
    sprint_cooldown-=1;
    if (sprint_cooldown == -1)
    {
        sprint_cooldown = 80;
        t_sprint_cd->Enabled = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::t_shootTimer(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------





