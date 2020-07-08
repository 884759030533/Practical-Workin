//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Unit2.h"
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class Tmain_form : public TForm
{
__published:	// IDE-managed Components
    TDrawGrid *main_grid;
    TImageList *sprite_list;
    TTimer *t_move_left;
    TTimer *t_move_down;
    TTimer *t_move_right;
    TTimer *t_move_up;
    TTimer *t_sprint;
    TTimer *t_bullet;
    TTimer *t_enemy;
    TTimer *T_tick_screen;
    void __fastcall main_gridDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall main_gridKeyPress(TObject *Sender, char &Key);
    void __fastcall main_gridKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall t_move_leftTimer(TObject *Sender);
    void __fastcall t_move_rightTimer(TObject *Sender);
    void __fastcall t_move_upTimer(TObject *Sender);
    void __fastcall t_move_downTimer(TObject *Sender);
    void __fastcall t_sprintTimer(TObject *Sender);
    void __fastcall t_bulletTimer(TObject *Sender);
    void __fastcall t_enemyTimer(TObject *Sender);
    void __fastcall T_tick_screenTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall Tmain_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tmain_form *main_form;
//---------------------------------------------------------------------------
#endif
 