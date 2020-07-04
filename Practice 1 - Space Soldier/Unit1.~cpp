//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tmain_form *main_form;
//---------------------------------------------------------------------------
__fastcall Tmain_form::Tmain_form(TComponent* Owner)
    : TForm(Owner)
{
    DoubleBuffered = true;
    Screen->Cursors[crNoDrop] = LoadCursorFromFile("G_cur.ani");
    Screen->Cursor = crNoDrop; // Load Green-styled Cursor
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::main_gridDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    
    sprite_list->Draw(main_grid->Canvas, Rect.Left, Rect.Top,0);
}
//---------------------------------------------------------------------------

