//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ActnList.hpp>
#include <jpeg.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TImage *img_player;
    TLabel *LMvSpeed1;
    TTimer *t_move_left;
    TTimer *t_move_up;
    TTimer *t_move_down;
    TTimer *t_move_right;
    TLabel *LMvSpeedTxt;
    TLabel *LMvLen1;
    TLabel *LMvLenTxt;
    TTimer *t_sprint;
    TLabel *LMvBoostTxt;
    TLabel *LMvBoost1;
    TLabel *LBoostCdTxt;
    TLabel *LBoostCd1;
    TTimer *t_shoot;
    TImageList *img_list_hp;
    TImage *img_background;
    TImage *img_bullet;
    TImage *img_enemy_1;
    TImage *img_player_hp;
    TImage *img_enemy1_hp;
    TTimer *t_enemy_1;
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall t_move_leftTimer(TObject *Sender);
    void __fastcall t_move_upTimer(TObject *Sender);
    void __fastcall t_move_downTimer(TObject *Sender);
    void __fastcall t_move_rightTimer(TObject *Sender);
    void __fastcall t_sprintTimer(TObject *Sender);
    void __fastcall t_shootTimer(TObject *Sender);
    void __fastcall t_enemy_1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
