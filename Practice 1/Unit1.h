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
    TImage *img_move_test;
    TLabel *LMvSpeed1;
    TTimer *t_move_left;
    TTimer *t_move_up;
    TTimer *t_move_down;
    TTimer *t_move_right;
    TImage *img_bg;
    TLabel *LMvSpeedTxt;
    TLabel *LMvLen1;
    TLabel *LMvLenTxt;
    TTimer *t_sprint;
    TLabel *LMvBoostTxt;
    TLabel *LMvBoost1;
    TTimer *t_sprint_cd;
    TLabel *LBoostCdTxt;
    TLabel *LBoostCd1;
    TTimer *t_shoot;
    TImageList *ImageList1;
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall t_move_leftTimer(TObject *Sender);
    void __fastcall t_move_upTimer(TObject *Sender);
    void __fastcall t_move_downTimer(TObject *Sender);
    void __fastcall t_move_rightTimer(TObject *Sender);
    void __fastcall t_sprintTimer(TObject *Sender);
    void __fastcall t_sprint_cdTimer(TObject *Sender);
    void __fastcall t_shootTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
