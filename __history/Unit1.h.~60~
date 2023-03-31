//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Header;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TLabel *TurnMessageLabel;
	TLabel *CurrentPlayerSymbolLabel;
	TLabel *WinnerLabel;
	TLabel *XScoreLabel;
	TLabel *OScoreLabel;
	TLabel *XScoreCounter;
	TLabel *OScoreCounter;
	TButton *ReplayButton;
	TImage *OBomb;
	TImage *OLineErase;
	TImage *OShield;
	TImage *OMallet;
	TImage *XBomb;
	TImage *XMallet;
	TImage *XLineErase;
	TImage *XShield;
	TRectangle *OLineEraseIndicator;
	TRectangle *OMalletIndicator;
	TRectangle *OBombIndicator;
	TRectangle *OShieldIndicator;
	TRectangle *XMalletIndicator;
	TRectangle *XLineEraseIndicator;
	TRectangle *XBombIndicator;
	TRectangle *XShieldIndicator;
	TRectangle *Button9Indicator;
	TRectangle *Button8Indicator;
	TRectangle *Button7Indicator;
	TRectangle *Button6Indicator;
	TRectangle *Button5Indicator;
	TRectangle *Button4Indicator;
	TRectangle *Button3Indicator;
	TRectangle *Button2Indicator;
	TRectangle *Button1Indicator;
	void __fastcall ButtonClick(TObject *Sender);
	void __fastcall ReplayButtonClick(TObject *Sender);
	void __fastcall XBombClick(TObject *Sender);
        void __fastcall OBombClick(TObject *Sender);
	void __fastcall ButtonMouseEnter(TObject *Sender);
	void __fastcall ButtonMouseLeave(TObject *Sender);
	void __fastcall XMalletClick(TObject *Sender);
	void __fastcall OMalletClick(TObject *Sender);
	void __fastcall XLineEraseClick(TObject *Sender);
	void __fastcall OLineEraseClick(TObject *Sender);
	void __fastcall XShieldClick(TObject *Sender);
	void __fastcall OShieldClick(TObject *Sender);
private:	// User declarations
        //bool TForm1::CheckIsWinner();
        char TForm1::CheckIsWinner();
        void TForm1::DisableButtons();
        void TForm1::EnableButtons();
        void TForm1::ClearButtons();
        void TForm1::ResetPowerups();
        void TForm1::DisablePowerups();
        void TForm1::CancelPowerups();
        void TForm1::ChangeButtonFontColor(TButton* button, TAlphaColor color);
        void TForm1::ResetButtonFontColor();
        void TForm1::ResetButtonFillColor();
        void TForm1::EndTurn();
        void TForm1::SetIndicatorColor(TButton* button, TAlphaColor color);
        void TForm1::SetIndicatorClear(TButton* button);
        void TForm1::UseBombPowerup(char playerSymbol, char &bombClicked, TButton* Sender);
        void TForm1::UseMalletPowerup(char playerSymbol, char &malletClicked, TButton* Sender);
        void TForm1::UseLineErasePowerup(char playerSymbol, char &eraserClicked, TButton* Sender);
        void TForm1::UseShieldPowerup(char playerSymbol, char &shieldClicked, TButton* Sender);
        void TForm1::SetShieldTiles();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
