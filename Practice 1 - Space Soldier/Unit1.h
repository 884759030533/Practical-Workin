//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
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
    TImage *Image1;
    void __fastcall main_gridDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
private:	// User declarations
public:		// User declarations
    __fastcall Tmain_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tmain_form *main_form;
//---------------------------------------------------------------------------
#endif
 