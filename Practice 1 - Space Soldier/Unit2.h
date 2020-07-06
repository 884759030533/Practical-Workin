//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

//---------------------------------------------------------------------------
class Tdebug_form : public TForm
{
__published:	// IDE-managed Components
    TLabel *L_boost_time;
    TLabel *L_boost_cd;
    TLabel *Label3;
    TLabel *Label4;
private:	// User declarations
public:		// User declarations
    __fastcall Tdebug_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tdebug_form *debug_form;
//---------------------------------------------------------------------------
#endif
 