//---------------------------------------------------------------------------

#include <fmx.h>

#pragma hdrstop

#include "Unit1.h"
#include <System.Sysutils.hpp>
#include <FMX.Graphics.hpp>
#include <System.IOUtils.hpp>
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.iPhone55in.fmx", _PLAT_IOS)
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)

TForm1 *Form1;

UnicodeString executablePath = ExtractFilePath(ParamStr(0));
char currentPlayerSymbol = 'X';
unsigned int XScoreCounterNum = 0;
unsigned int OScoreCounterNum = 0;
char OBombClicked = 'f';
char OMalletClicked = 'f';
char OLineEraseClicked = 'f';
char OShieldClicked = 'f';
char XBombClicked = 'f';
char XMalletClicked = 'f';
char XLineEraseClicked = 'f';
char XShieldClicked = 'f';
int ShieldStatus[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int ShieldTurns[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

char TForm1::CheckIsWinner() {
     if(!Button1->Text.IsEmpty() && Button1->Text==Button2->Text && Button1->Text==Button3->Text)
        return Button1->Text.SubString(0, 1)[1];
     if(!Button4->Text.IsEmpty() && Button4->Text==Button5->Text && Button4->Text==Button6->Text)
        return Button4->Text.SubString(0, 1)[1];
     if(!Button7->Text.IsEmpty() && Button7->Text==Button8->Text && Button7->Text==Button9->Text)
        return Button7->Text.SubString(0, 1)[1];
     if(!Button1->Text.IsEmpty() && Button1->Text==Button4->Text && Button1->Text==Button7->Text)
        return Button1->Text.SubString(0, 1)[1];
     if(!Button2->Text.IsEmpty() && Button2->Text==Button5->Text && Button2->Text==Button8->Text)
        return Button2->Text.SubString(0, 1)[1];
     if(!Button3->Text.IsEmpty() && Button3->Text==Button6->Text && Button3->Text==Button9->Text)
        return Button3->Text.SubString(0, 1)[1];
     if(!Button1->Text.IsEmpty() && Button1->Text==Button5->Text && Button1->Text==Button9->Text)
        return Button1->Text.SubString(0, 1)[1];
     if(!Button3->Text.IsEmpty() && Button3->Text==Button5->Text && Button3->Text==Button7->Text)
        return Button3->Text.SubString(0, 1)[1];
     if(!Button1->Text.IsEmpty() && !Button2->Text.IsEmpty() && !Button3->Text.IsEmpty() && !Button4->Text.IsEmpty() && !Button5->Text.IsEmpty() && !Button6->Text.IsEmpty() && !Button7->Text.IsEmpty() && !Button8->Text.IsEmpty() && !Button9->Text.IsEmpty())
        return 'y';
     return 'z';
}

void TForm1::DisableButtons() {
	Button1->Enabled=false;
        Button2->Enabled=false;
        Button3->Enabled=false;
        Button4->Enabled=false;
        Button5->Enabled=false;
        Button6->Enabled=false;
        Button7->Enabled=false;
        Button8->Enabled=false;
        Button9->Enabled=false;
}

void TForm1::EnableButtons() {
	Button1->Enabled=true;
        Button2->Enabled=true;
        Button3->Enabled=true;
        Button4->Enabled=true;
        Button5->Enabled=true;
        Button6->Enabled=true;
        Button7->Enabled=true;
        Button8->Enabled=true;
        Button9->Enabled=true;
}

void TForm1::ClearButtons() {
    	Button1->Text="";
    	Button2->Text="";
    	Button3->Text="";
    	Button4->Text="";
    	Button5->Text="";
    	Button6->Text="";
    	Button7->Text="";
    	Button8->Text="";
    	Button9->Text="";
}

void TForm1::ResetPowerups() {
        TBitmap *newImage = new TBitmap();

        OBombClicked = 'f';
        try {
            newImage->LoadFromFile(executablePath + "graphics\\Bomb.png");
            OBomb->Bitmap = newImage;
        }
        catch (Exception &e) {
            // Handle the exception if the image file is not found
            ShowMessage("Error loading image: " + e.Message);
        }

	OMalletClicked = 'f';
        try {
            newImage->LoadFromFile(executablePath + "graphics\\Mallet.png");
            OMallet->Bitmap = newImage;
        }
        catch (Exception &e) {
            // Handle the exception if the image file is not found
            ShowMessage("Error loading image: " + e.Message);
        }

	OLineEraseClicked = 'f';
        try {
            newImage->LoadFromFile(executablePath + "graphics\\Eraser.png");
            OLineErase->Bitmap = newImage;
        }
        catch (Exception &e) {
            // Handle the exception if the image file is not found
            ShowMessage("Error loading image: " + e.Message);
        }

	OShieldClicked = 'f';
        try {
            newImage->LoadFromFile(executablePath + "graphics\\Shield.png");
            OShield->Bitmap = newImage;
        }
        catch (Exception &e) {
            // Handle the exception if the image file is not found
            ShowMessage("Error loading image: " + e.Message);
        }

	XBombClicked = 'f';
        try {
            newImage->LoadFromFile(executablePath + "graphics\\Bomb.png");
            XBomb->Bitmap = newImage;
        }
        catch (Exception &e) {
            // Handle the exception if the image file is not found
            ShowMessage("Error loading image: " + e.Message);
        }

	XMalletClicked = 'f';
        try {
            newImage->LoadFromFile(executablePath + "graphics\\Mallet.png");
            XMallet->Bitmap = newImage;
        }
        catch (Exception &e) {
            // Handle the exception if the image file is not found
            ShowMessage("Error loading image: " + e.Message);
        }

	XLineEraseClicked = 'f';
        try {
            newImage->LoadFromFile(executablePath + "graphics\\Eraser.png");
            XLineErase->Bitmap = newImage;
        }
        catch (Exception &e) {
            // Handle the exception if the image file is not found
            ShowMessage("Error loading image: " + e.Message);
        }

	XShieldClicked = 'f';
        try {
            newImage->LoadFromFile(executablePath + "graphics\\Shield.png");
            XShield->Bitmap = newImage;
        }
        catch (Exception &e) {
            // Handle the exception if the image file is not found
            ShowMessage("Error loading image: " + e.Message);
        }

        delete newImage;

        //Reset shield powerups
         for(int i = 0; i < 9; i++) {
            ShieldTurns[i] = 0;
            ShieldStatus[i] = 0;
            TButton* Button = dynamic_cast<TButton*>(FindComponent("Button" + IntToStr(i+1)));
            Button->FontColor = TAlphaColorRec::Black;
            SetIndicatorClear(Button);
            //////
         }
}

void TForm1::DisablePowerups() {
        OBombClicked = 'x';
	OMalletClicked = 'x';
	OLineEraseClicked = 'x';
	OShieldClicked = 'x';
	XBombClicked = 'x';
	XMalletClicked = 'x';
	XLineEraseClicked = 'x';
	XShieldClicked = 'x';
}

void TForm1::CancelPowerups() {
        if(OBombClicked != 'x') {
           OBombClicked = 'f';
           WinnerLabel->Text = "";
           TurnMessageLabel->Text = "It is your turn player:";
           CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
           OBombIndicator->Visible = false;
        }
        if(OMalletClicked != 'x') {
           OMalletClicked = 'f';
           WinnerLabel->Text = "";
           TurnMessageLabel->Text = "It is your turn player:";
           CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
           OMalletIndicator->Visible = false;
        }
        if(OLineEraseClicked != 'x') {
           OLineEraseClicked = 'f';
           WinnerLabel->Text = "";
           TurnMessageLabel->Text = "It is your turn player:";
           CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
           OLineEraseIndicator->Visible = false;
        }
        if(OShieldClicked != 'x') {
           OShieldClicked = 'f';
           WinnerLabel->Text = "";
           TurnMessageLabel->Text = "It is your turn player:";
           CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
           OShieldIndicator->Visible = false;
        }
        if(XBombClicked != 'x') {
           XBombClicked = 'f';
           WinnerLabel->Text = "";
           TurnMessageLabel->Text = "It is your turn player:";
           CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
           XBombIndicator->Visible = false;
        }
        if(XMalletClicked != 'x') {
           XMalletClicked = 'f';
           WinnerLabel->Text = "";
           TurnMessageLabel->Text = "It is your turn player:";
           CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
           XMalletIndicator->Visible = false;
        }
	if(XLineEraseClicked != 'x') {
           XLineEraseClicked = 'f';
           WinnerLabel->Text = "";
           TurnMessageLabel->Text = "It is your turn player:";
           CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
           XLineEraseIndicator->Visible = false;
        }
	if(XShieldClicked != 'x') {
           XShieldClicked = 'f';
           WinnerLabel->Text = "";
           TurnMessageLabel->Text = "It is your turn player:";
           CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
           XShieldIndicator->Visible = false;
        }
}

void TForm1::ChangeButtonFontColor(TButton* button, TAlphaColor Color) {
    button->StyledSettings = button->StyledSettings >> TStyledSetting::ssFontColor;
    button->FontColor = Color;
}

void TForm1::ResetButtonFontColor() {
    ChangeButtonFontColor(Button1, TAlphaColorRec::Black);
    ChangeButtonFontColor(Button2, TAlphaColorRec::Black);
    ChangeButtonFontColor(Button3, TAlphaColorRec::Black);
    ChangeButtonFontColor(Button4, TAlphaColorRec::Black);
    ChangeButtonFontColor(Button5, TAlphaColorRec::Black);
    ChangeButtonFontColor(Button6, TAlphaColorRec::Black);
    ChangeButtonFontColor(Button7, TAlphaColorRec::Black);
    ChangeButtonFontColor(Button8, TAlphaColorRec::Black);
    ChangeButtonFontColor(Button9, TAlphaColorRec::Black);
}

void TForm1::ResetButtonFillColor() {
    SetIndicatorClear(Button1);
    SetIndicatorClear(Button2);
    SetIndicatorClear(Button3);
    SetIndicatorClear(Button4);
    SetIndicatorClear(Button5);
    SetIndicatorClear(Button6);
    SetIndicatorClear(Button7);
    SetIndicatorClear(Button8);
    SetIndicatorClear(Button9);
}

void TForm1::EndTurn() {

    if(currentPlayerSymbol == 'X')
        currentPlayerSymbol = 'O';
    else
    	currentPlayerSymbol = 'X';
    CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;

    ResetButtonFontColor();
    ResetButtonFillColor();

    //Sets Shield Tiles and Reduces Turns
    for(int i = 0; i < 9; i++) {
        if(ShieldTurns[i] > 0) {
            ShieldTurns[i]--;
            if(ShieldTurns[i] == 0) {
                ShieldStatus[i] = 0;
            } else {
              TButton* Button = dynamic_cast<TButton*>(FindComponent("Button" + IntToStr(i+1)));
              if(Button != NULL) {
                SetIndicatorColor(Button, TAlphaColorRec::Aqua);
              }
            }
        }
    }

}

void TForm1::SetIndicatorColor(TButton* button, TAlphaColor color) {
    String buttonName = button->Name;
    String indicatorName = buttonName + "Indicator";
    TComponent* indicatorComponent = this->FindComponent(indicatorName);

    if (indicatorComponent && dynamic_cast<TRectangle*>(indicatorComponent)) {
        TRectangle* indicator = static_cast<TRectangle*>(indicatorComponent);
        indicator->Fill->Color = color;
        indicator->Fill->Kind = TBrushKind::Solid;
    }
}

void TForm1::SetIndicatorClear(TButton* button) {
    String buttonName = button->Name;
    String indicatorName = buttonName + "Indicator";
    TComponent* indicatorComponent = this->FindComponent(indicatorName);

    if (indicatorComponent && dynamic_cast<TRectangle*>(indicatorComponent)) {
        TRectangle* indicator = static_cast<TRectangle*>(indicatorComponent);
        indicator->Fill->Color = TAlphaColorRec::White;
        indicator->Fill->Kind = TBrushKind::None;
    }
}

void TForm1::UseShieldPowerup(char playerSymbol, char &shieldClicked, TButton* Sender) {
    TButton* clickedButton = Sender;
    if(XShieldClicked == 't' || OShieldClicked == 't') {
        if(XShieldClicked == 't') {
            XShieldClicked = 'x';
            if(clickedButton->Text.IsEmpty()) {
                XShieldClicked = 'f';
                WinnerLabel->Text = "";
                TurnMessageLabel->Text = "It is your turn player:";
                CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
                XShieldIndicator->Visible = false;
                ResetButtonFillColor();
                SetShieldTiles();
                return;
            }
        } else if (OShieldClicked == 't') {
            OShieldClicked = 'x';
            if(clickedButton->Text.IsEmpty()) {
                OShieldClicked = 'f';
                WinnerLabel->Text = "";
                TurnMessageLabel->Text = "It is your turn player:";
                CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
                OShieldIndicator->Visible = false;
                ResetButtonFillColor();
                SetShieldTiles();
                return;
            }
        } else
            return;


        int buttonIndex = Sender->Tag;
        int protectedTurns = 4;
        ShieldStatus[buttonIndex] = 1;
        ShieldTurns[buttonIndex] = protectedTurns;
        SetIndicatorColor(clickedButton, TAlphaColorRec::Aqua);

        //Replace Shield with Shield Gray
        TBitmap *newImage = new TBitmap();

        if(OShieldClicked == 'x') {
            try {
                newImage->LoadFromFile(executablePath + "graphics\\ShieldGray.png");
                OShield->Bitmap = newImage;
                OShieldIndicator->Visible = false;
            }
            catch (Exception &e) {
                // Handle the exception if the image file is not found
                ShowMessage("Error loading image: " + e.Message);
            }
        }
        if(XShieldClicked == 'x'){
            try {
                newImage->LoadFromFile(executablePath + "graphics\\ShieldGray.png");
                XShield->Bitmap = newImage;
                XShieldIndicator->Visible = false;
            }
            catch (Exception &e) {
                // Handle the exception if the image file is not found
                ShowMessage("Error loading image: " + e.Message);
            }
        }

        delete newImage;

        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        EndTurn();
        return;

    }else
        return;
}

void TForm1::SetShieldTiles() {
    for(int i = 0; i < 9; i++) {
        if(ShieldTurns[i] > 0) {
            if(ShieldTurns[i] == 0) {
                ShieldStatus[i] = 0;
            } else {
              TButton* Button = dynamic_cast<TButton*>(FindComponent("Button" + IntToStr(i+1)));
              if(Button != NULL) {
                SetIndicatorColor(Button, TAlphaColorRec::Aqua);
              }
            }
        }
    }
}

void TForm1::UseBombPowerup(char playerSymbol, char &bombClicked, TButton* Sender) {

    TButton* clickedButton = Sender;
    if(OBombClicked == 't' || XBombClicked == 't') {
        if(OBombClicked == 't') {
            OBombClicked = 'x';
        } else if (XBombClicked == 't') {
            XBombClicked = 'x';
        } else
            return;

        if (clickedButton == Button1) {
            if (ShieldStatus[0] == 0) Button1->Text = "";
            if (ShieldStatus[1] == 0) Button2->Text = "";
            if (ShieldStatus[3] == 0) Button4->Text = "";
            if (ShieldStatus[4] == 0) Button5->Text = "";
        } else if (clickedButton == Button2) {
            if (ShieldStatus[0] == 0) Button1->Text = "";
            if (ShieldStatus[1] == 0) Button2->Text = "";
            if (ShieldStatus[2] == 0) Button3->Text = "";
            if (ShieldStatus[4] == 0) Button5->Text = "";
        } else if (clickedButton == Button3) {
            if (ShieldStatus[1] == 0) Button2->Text = "";
            if (ShieldStatus[2] == 0) Button3->Text = "";
            if (ShieldStatus[4] == 0) Button5->Text = "";
            if (ShieldStatus[5] == 0) Button6->Text = "";
        } else if (clickedButton == Button4) {
            if (ShieldStatus[0] == 0) Button1->Text = "";
            if (ShieldStatus[3] == 0) Button4->Text = "";
            if (ShieldStatus[4] == 0) Button5->Text = "";
            if (ShieldStatus[6] == 0) Button7->Text = "";
        } else if (clickedButton == Button5) {
            if (ShieldStatus[1] == 0) Button2->Text = "";
            if (ShieldStatus[3] == 0) Button4->Text = "";
            if (ShieldStatus[4] == 0) Button5->Text = "";
            if (ShieldStatus[5] == 0) Button6->Text = "";
            if (ShieldStatus[7] == 0) Button8->Text = "";
        } else if (clickedButton == Button6) {
            if (ShieldStatus[2] == 0) Button3->Text = "";
            if (ShieldStatus[4] == 0) Button5->Text = "";
            if (ShieldStatus[5] == 0) Button6->Text = "";
            if (ShieldStatus[8] == 0) Button9->Text = "";
        } else if (clickedButton == Button7) {
            if (ShieldStatus[3] == 0) Button4->Text = "";
            if (ShieldStatus[4] == 0) Button5->Text = "";
            if (ShieldStatus[6] == 0) Button7->Text = "";
            if (ShieldStatus[7] == 0) Button8->Text = "";
        } else if (clickedButton == Button8) {
            if (ShieldStatus[4] == 0) Button5->Text = "";
            if (ShieldStatus[6] == 0) Button7->Text = "";
            if (ShieldStatus[7] == 0) Button8->Text = "";
            if (ShieldStatus[8] == 0) Button9->Text = "";
        } else if (clickedButton == Button9) {
            if (ShieldStatus[4] == 0) Button5->Text = "";
            if (ShieldStatus[5] == 0) Button6->Text = "";
            if (ShieldStatus[7] == 0) Button8->Text = "";
            if (ShieldStatus[8] == 0) Button9->Text = "";
        }

        //Replace Bomb with BombGray
        TBitmap *newImage = new TBitmap();

        if(OBombClicked == 'x') {
            try {
                newImage->LoadFromFile(executablePath + "graphics\\BombGray.png");
                OBomb->Bitmap = newImage;
                OBombIndicator->Visible = false;
            }
            catch (Exception &e) {
                // Handle the exception if the image file is not found
                ShowMessage("Error loading image: " + e.Message);
            }
        }
        if(XBombClicked == 'x'){
            try {
                newImage->LoadFromFile(executablePath + "graphics\\BombGray.png");
                XBomb->Bitmap = newImage;
                XBombIndicator->Visible = false;
            }
            catch (Exception &e) {
                // Handle the exception if the image file is not found
                ShowMessage("Error loading image: " + e.Message);
            }
        }

        delete newImage;

        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        EndTurn();
        return;
    } else {
        return;
    }
}

void TForm1::UseMalletPowerup(char playerSymbol, char &malletClicked, TButton* Sender) {
    TButton* clickedButton = Sender;
    if(XMalletClicked == 't' || OMalletClicked == 't') {
        if(XMalletClicked == 't') {
            XMalletClicked = 'x';
            if(clickedButton->Text.IsEmpty()) {
                XMalletClicked = 'f';
                WinnerLabel->Text = "";
                TurnMessageLabel->Text = "It is your turn player:";
                CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
                XMalletIndicator->Visible = false;
                ResetButtonFillColor();
                SetShieldTiles();
                return;
            }
        } else if (OMalletClicked == 't') {
            OMalletClicked = 'x';
            if(clickedButton->Text.IsEmpty()) {
                OMalletClicked = 'f';
                WinnerLabel->Text = "";
                TurnMessageLabel->Text = "It is your turn player:";
                CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
                OMalletIndicator->Visible = false;
                ResetButtonFillColor();
                SetShieldTiles();
                return;
            }
        } else
            return;



        if(clickedButton == Button1) {
        	if (ShieldStatus[0] == 0) Button1->Text = "";
        }
        else if(clickedButton == Button2) {
        	if (ShieldStatus[1] == 0) Button2->Text = "";
        }
        else if(clickedButton == Button3) {
        	if (ShieldStatus[2] == 0) Button3->Text = "";
        }
        else if(clickedButton == Button4) {
        	if (ShieldStatus[3] == 0) Button4->Text = "";
        }
        else if(clickedButton == Button5) {
        	if (ShieldStatus[4] == 0) Button5->Text = "";
        }
        else if(clickedButton == Button6) {
        	if (ShieldStatus[5] == 0) Button6->Text = "";
        }
        else if(clickedButton == Button7) {
        	if (ShieldStatus[6] == 0) Button7->Text = "";
        }
        else if(clickedButton == Button8) {
        	if (ShieldStatus[7] == 0) Button8->Text = "";
        }
        else if(clickedButton == Button9) {
        	if (ShieldStatus[8] == 0) Button9->Text = "";
        }

        //Replace Mallet with MalletGray
        TBitmap *newImage = new TBitmap();

        if(OMalletClicked == 'x') {
            try {
                newImage->LoadFromFile(executablePath + "graphics\\MalletGray.png");
                OMallet->Bitmap = newImage;
                OMalletIndicator->Visible = false;
            }
            catch (Exception &e) {
                // Handle the exception if the image file is not found
                ShowMessage("Error loading image: " + e.Message);
            }
        }
        if(XMalletClicked == 'x'){
            try {
                newImage->LoadFromFile(executablePath + "graphics\\MalletGray.png");
                XMallet->Bitmap = newImage;
                XMalletIndicator->Visible = false;
            }
            catch (Exception &e) {
                // Handle the exception if the image file is not found
                ShowMessage("Error loading image: " + e.Message);
            }
        }

        delete newImage;

        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        EndTurn();
        return;

    }else
        return;
}

void TForm1::UseLineErasePowerup(char playerSymbol, char &eraserClicked, TButton* Sender) {
    TButton* clickedButton = Sender;
    if(XLineEraseClicked == 't' || OLineEraseClicked == 't') {
        if(XLineEraseClicked == 't') {
            XLineEraseClicked = 'x';
        } else if (OLineEraseClicked == 't') {
            OLineEraseClicked = 'x';
        } else
            return;

        if(clickedButton == Button1) {
        	if (ShieldStatus[0] == 0) Button1->Text = "";
                if (ShieldStatus[1] == 0) Button2->Text = "";
                if (ShieldStatus[2] == 0) Button3->Text = "";
        }
        else if(clickedButton == Button2) {
        	if (ShieldStatus[0] == 0) Button1->Text = "";
                if (ShieldStatus[1] == 0) Button2->Text = "";
                if (ShieldStatus[2] == 0) Button3->Text = "";
        }
        else if(clickedButton == Button3) {
        	if (ShieldStatus[0] == 0) Button1->Text = "";
                if (ShieldStatus[1] == 0) Button2->Text = "";
                if (ShieldStatus[2] == 0) Button3->Text = "";
        }
        else if(clickedButton == Button4) {
        	if (ShieldStatus[3] == 0) Button4->Text = "";
                if (ShieldStatus[4] == 0) Button5->Text = "";
                if (ShieldStatus[5] == 0) Button6->Text = "";
        }
        else if(clickedButton == Button5) {
        	if (ShieldStatus[3] == 0) Button4->Text = "";
                if (ShieldStatus[4] == 0) Button5->Text = "";
                if (ShieldStatus[5] == 0) Button6->Text = "";
        }
        else if(clickedButton == Button6) {
        	if (ShieldStatus[3] == 0) Button4->Text = "";
                if (ShieldStatus[4] == 0) Button5->Text = "";
                if (ShieldStatus[5] == 0) Button6->Text = "";
        }
        else if(clickedButton == Button7) {
        	if (ShieldStatus[6] == 0) Button7->Text = "";
                if (ShieldStatus[7] == 0) Button8->Text = "";
                if (ShieldStatus[8] == 0) Button9->Text = "";
        }
        else if(clickedButton == Button8) {
        	if (ShieldStatus[6] == 0) Button7->Text = "";
                if (ShieldStatus[7] == 0) Button8->Text = "";
                if (ShieldStatus[8] == 0) Button9->Text = "";
        }
        else if(clickedButton == Button9) {
        	if (ShieldStatus[6] == 0) Button7->Text = "";
                if (ShieldStatus[7] == 0) Button8->Text = "";
                if (ShieldStatus[8] == 0) Button9->Text = "";
        }

        //Replace Eraser with EraserGray
        TBitmap *newImage = new TBitmap();

        if(OLineEraseClicked == 'x') {
            try {
                newImage->LoadFromFile(executablePath + "graphics\\EraserGray.png");
                OLineErase->Bitmap = newImage;
                OLineEraseIndicator->Visible = false;
            }
            catch (Exception &e) {
                // Handle the exception if the image file is not found
                ShowMessage("Error loading image: " + e.Message);
            }
        }
        if(XLineEraseClicked == 'x'){
            try {
                newImage->LoadFromFile(executablePath + "graphics\\EraserGray.png");
                XLineErase->Bitmap = newImage;
                XLineEraseIndicator->Visible = false;
            }
            catch (Exception &e) {
                // Handle the exception if the image file is not found
                ShowMessage("Error loading image: " + e.Message);
            }
        }

        delete newImage;

        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        EndTurn();
        return;

    }else
        return;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonClick(TObject *Sender)
{
    TButton* clickedButton = dynamic_cast<TButton*>(Sender);

    if(XMalletClicked == 't' || OMalletClicked == 't') {
        if(currentPlayerSymbol == 'X') {
            UseMalletPowerup('X', XMalletClicked, clickedButton);
            return;
        } else {
            UseMalletPowerup('O', OMalletClicked, clickedButton);
            return;
        }
    }

    if(XLineEraseClicked == 't' || OLineEraseClicked == 't') {
        if(currentPlayerSymbol == 'X') {
            UseLineErasePowerup('X', XLineEraseClicked, clickedButton);
            return;
        } else {
            UseLineErasePowerup('O', OLineEraseClicked, clickedButton);
            return;
        }
    }

     if(XBombClicked == 't' || OBombClicked == 't') {
        if(currentPlayerSymbol == 'X') {
            UseBombPowerup('X', XBombClicked, clickedButton);
            return;
        } else {
            UseBombPowerup('O', OBombClicked, clickedButton);
            return;
        }
    }

    if(XShieldClicked == 't' || OShieldClicked == 't') {
        if(currentPlayerSymbol == 'X') {
            UseShieldPowerup('X', XShieldClicked, clickedButton);
            return;
        } else {
            UseShieldPowerup('O', OShieldClicked, clickedButton);
            return;
        }
    }


    if(clickedButton->Text == 'X' || clickedButton->Text == 'O')
        return;

    clickedButton->Text = currentPlayerSymbol;

    char winner = CheckIsWinner();

    if(winner != 'z') {
        if(winner == 'X') {
            WinnerLabel->Text = "Player X, You've WON!!!";
            XScoreCounterNum++;
            XScoreCounter->Text = std::to_string(XScoreCounterNum).c_str();
        } else if(winner == 'O') {
            WinnerLabel->Text = "Player O, You've WON!!!";
            OScoreCounterNum++;
            OScoreCounter->Text = std::to_string(OScoreCounterNum).c_str();
        } else {
            WinnerLabel->Text = "It's a Tie!!!";
        }
        TurnMessageLabel->Text = "";
        CurrentPlayerSymbolLabel->Text = "";
        DisableButtons();
        DisablePowerups();
        return;
    }

    EndTurn();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonMouseEnter(TObject *Sender)
{
   TButton* hoveredButton = dynamic_cast<TButton*>(Sender);

   if(XMalletClicked == 't' || OMalletClicked == 't') {
        if(hoveredButton == Button1)
        	if(Button1Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button1, TAlphaColorRec::Red);
        if(hoveredButton == Button2)
        	if(Button2Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button2, TAlphaColorRec::Red);
        if(hoveredButton == Button3)
        	if(Button3Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button3, TAlphaColorRec::Red);
        if(hoveredButton == Button4)
        	if(Button4Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button4, TAlphaColorRec::Red);
        if(hoveredButton == Button5)
        	if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
        if(hoveredButton == Button6)
        	if(Button6Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button6, TAlphaColorRec::Red);
        if(hoveredButton == Button7)
        	if(Button7Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button7, TAlphaColorRec::Red);
        if(hoveredButton == Button8)
        	if(Button8Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button8, TAlphaColorRec::Red);
        if(hoveredButton == Button9)
        	if(Button9Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button9, TAlphaColorRec::Red);
   }

   if(XLineEraseClicked == 't' || OLineEraseClicked == 't') {
        if(hoveredButton == Button1) {
        	if(Button1Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button1, TAlphaColorRec::Red);
                if(Button2Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button2, TAlphaColorRec::Red);
                if(Button3Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button3, TAlphaColorRec::Red);
        }
        else if(hoveredButton == Button2) {
        	if(Button1Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button1, TAlphaColorRec::Red);
                if(Button2Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button2, TAlphaColorRec::Red);
                if(Button3Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button3, TAlphaColorRec::Red);
        }
        else if(hoveredButton == Button3) {
        	if(Button1Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button1, TAlphaColorRec::Red);
                if(Button2Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button2, TAlphaColorRec::Red);
                if(Button3Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button3, TAlphaColorRec::Red);
        }
        else if(hoveredButton == Button4) {
        	if(Button4Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button4, TAlphaColorRec::Red);
                if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
                if(Button6Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button6, TAlphaColorRec::Red);
        }
        else if(hoveredButton == Button5) {
        	if(Button4Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button4, TAlphaColorRec::Red);
                if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
                if(Button6Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button6, TAlphaColorRec::Red);
        }
        else if(hoveredButton == Button6) {
        	if(Button4Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button4, TAlphaColorRec::Red);
                if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
                if(Button6Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button6, TAlphaColorRec::Red);
        }
        else if(hoveredButton == Button7) {
        	if(Button7Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button7, TAlphaColorRec::Red);
                if(Button8Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button8, TAlphaColorRec::Red);
                if(Button9Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button9, TAlphaColorRec::Red);
        }
        else if(hoveredButton == Button8) {
        	if(Button7Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button7, TAlphaColorRec::Red);
                if(Button8Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button8, TAlphaColorRec::Red);
                if(Button9Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button9, TAlphaColorRec::Red);
        }
        else if(hoveredButton == Button9) {
        	if(Button7Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button7, TAlphaColorRec::Red);
                if(Button8Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button8, TAlphaColorRec::Red);
                if(Button9Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button9, TAlphaColorRec::Red);
        }
   }

   if(XBombClicked == 't' || OBombClicked == 't') {

    if (hoveredButton == Button1) {
        if(Button1Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button1, TAlphaColorRec::Red);
        if(Button2Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button2, TAlphaColorRec::Red);
        if(Button4Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button4, TAlphaColorRec::Red);
        if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
    } else if (hoveredButton == Button2) {
        if(Button1Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button1, TAlphaColorRec::Red);
        if(Button2Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button2, TAlphaColorRec::Red);
        if(Button3Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button3, TAlphaColorRec::Red);
        if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
    } else if (hoveredButton == Button3) {
        if(Button2Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button2, TAlphaColorRec::Red);
        if(Button3Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button3, TAlphaColorRec::Red);
        if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
        if(Button6Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button6, TAlphaColorRec::Red);
    } else if (hoveredButton == Button4) {
        if(Button1Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button1, TAlphaColorRec::Red);
        if(Button4Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button4, TAlphaColorRec::Red);
        if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
        if(Button7Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button7, TAlphaColorRec::Red);
    } else if (hoveredButton == Button5) {
        if(Button2Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button2, TAlphaColorRec::Red);
        if(Button4Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button4, TAlphaColorRec::Red);
        if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
        if(Button6Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button6, TAlphaColorRec::Red);
        if(Button8Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button8, TAlphaColorRec::Red);
    } else if (hoveredButton == Button6) {
        if(Button3Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button3, TAlphaColorRec::Red);
        if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
        if(Button6Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button6, TAlphaColorRec::Red);
        if(Button9Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button9, TAlphaColorRec::Red);
    } else if (hoveredButton == Button7) {
        if(Button4Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button4, TAlphaColorRec::Red);
        if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
        if(Button7Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button7, TAlphaColorRec::Red);
        if(Button8Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button8, TAlphaColorRec::Red);
    } else if (hoveredButton == Button8) {
        if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
        if(Button7Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button7, TAlphaColorRec::Red);
        if(Button8Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button8, TAlphaColorRec::Red);
        if(Button9Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button9, TAlphaColorRec::Red);
    } else if (hoveredButton == Button9) {
        if(Button5Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button5, TAlphaColorRec::Red);
        if(Button6Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button6, TAlphaColorRec::Red);
        if(Button8Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button8, TAlphaColorRec::Red);
        if(Button9Indicator->Fill->Kind != TBrushKind::Solid) SetIndicatorColor(Button9, TAlphaColorRec::Red);
    }
   }
}

//----------------------------------------------------------------------------

void __fastcall TForm1::ButtonMouseLeave(TObject *Sender)
{
   TButton* hoveredButton = dynamic_cast<TButton*>(Sender);

   if(XMalletClicked == 't' || OMalletClicked == 't') {
        if(hoveredButton == Button1)
        	if(Button1Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button1);
        if(hoveredButton == Button2)
        	if(Button2Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button2);
        if(hoveredButton == Button3)
        	if(Button3Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button3);
        if(hoveredButton == Button4)
        	if(Button4Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button4);
        if(hoveredButton == Button5)
        	if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
        if(hoveredButton == Button6)
        	if(Button6Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button6);
        if(hoveredButton == Button7)
        	if(Button7Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button7);
        if(hoveredButton == Button8)
        	if(Button8Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button8);
        if(hoveredButton == Button9)
        	if(Button9Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button9);
   }

   if(XLineEraseClicked == 't' || OLineEraseClicked == 't') {
        if(hoveredButton == Button1) {
        	if(Button1Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button1);
                if(Button2Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button2);
                if(Button3Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button3);
        }
        else if(hoveredButton == Button2) {
        	if(Button1Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button1);
                if(Button2Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button2);
                if(Button3Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button3);
        }
        else if(hoveredButton == Button3) {
        	if(Button1Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button1);
                if(Button2Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button2);
                if(Button3Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button3);
        }
        else if(hoveredButton == Button4) {
        	if(Button4Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button4);
                if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
                if(Button6Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button6);
        }
        else if(hoveredButton == Button5) {
        	if(Button4Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button4);
                if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
                if(Button6Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button6);
        }
        else if(hoveredButton == Button6) {
        	if(Button4Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button4);
                if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
                if(Button6Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button6);
        }
        else if(hoveredButton == Button7) {
        	if(Button7Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button7);
                if(Button8Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button8);
                if(Button9Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button9);
        }
        else if(hoveredButton == Button8) {
        	if(Button7Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button7);
                if(Button8Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button8);
                if(Button9Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button9);
        }
        else if(hoveredButton == Button9) {
        	if(Button7Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button7);
                if(Button8Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button8);
                if(Button9Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button9);
        }
   }

   if(OBombClicked == 't' || XBombClicked == 't') {

    if (hoveredButton == Button1) {
        if(Button1Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button1);
        if(Button2Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button2);
        if(Button4Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button4);
        if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
    } else if (hoveredButton == Button2) {
        if(Button1Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button1);
        if(Button2Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button2);
        if(Button3Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button3);
        if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
    } else if (hoveredButton == Button3) {
        if(Button2Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button2);
        if(Button3Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button3);
        if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
        if(Button6Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button6);
    } else if (hoveredButton == Button4) {
        if(Button1Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button1);
        if(Button4Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button4);
        if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
        if(Button7Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button7);
    } else if (hoveredButton == Button5) {
        if(Button2Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button2);
        if(Button4Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button4);
        if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
        if(Button6Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button6);
        if(Button8Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button8);
    } else if (hoveredButton == Button6) {
        if(Button3Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button3);
        if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
        if(Button6Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button6);
        if(Button9Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button9);
    } else if (hoveredButton == Button7) {
        if(Button4Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button4);
        if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
        if(Button7Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button7);
        if(Button8Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button8);
    } else if (hoveredButton == Button8) {
        if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
        if(Button7Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button7);
        if(Button8Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button8);
        if(Button9Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button9);
    } else if (hoveredButton == Button9) {
        if(Button5Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button5);
        if(Button6Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button6);
        if(Button8Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button8);
        if(Button9Indicator->Fill->Color != TAlphaColorRec::Aqua) SetIndicatorClear(Button9);
    }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ReplayButtonClick(TObject *Sender)
{
    EnableButtons();
    ClearButtons();
    ResetPowerups();
    WinnerLabel->Text = "";
    CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
    TurnMessageLabel->Text = "It is your turn player:";

}
//---------------------------------------------------------------------------

void __fastcall TForm1::XBombClick(TObject *Sender)
{
    if(currentPlayerSymbol == 'O')
        return;

    if(XBombClicked == 't') {
        XBombClicked = 'f';
        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
        XBombIndicator->Visible = false;
        return;
    }

    if(XBombClicked != 'x') {
        CancelPowerups();
    	XBombClicked = 't';
    	TurnMessageLabel->Text = "";
        WinnerLabel->Text = "Place a Bomb!";
    	CurrentPlayerSymbolLabel->Text = "";
        XBombIndicator->Visible = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::OBombClick(TObject *Sender)
{
    if(currentPlayerSymbol == 'X')
        return;

    if(OBombClicked == 't') {
        OBombClicked = 'f';
        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
        OBombIndicator->Visible = false;
        return;
    }

    if(OBombClicked != 'x') {
        CancelPowerups();
    	OBombClicked = 't';
    	TurnMessageLabel->Text = "";
        WinnerLabel->Text = "Place a Bomb!";
    	CurrentPlayerSymbolLabel->Text = "";
        OBombIndicator->Visible = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::XMalletClick(TObject *Sender)
{
    if(currentPlayerSymbol == 'O')
        return;

    if(XMalletClicked == 't') {
        XMalletClicked = 'f';
        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
        XMalletIndicator->Visible = false;
        return;
    }

    if(XMalletClicked != 'x') {
        CancelPowerups();
    	XMalletClicked = 't';
    	TurnMessageLabel->Text = "";
        WinnerLabel->Text = "Break a Tile!";
    	CurrentPlayerSymbolLabel->Text = "";
        XMalletIndicator->Visible = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::OMalletClick(TObject *Sender)
{
    if(currentPlayerSymbol == 'X')
        return;

    if(OMalletClicked == 't') {
        OMalletClicked = 'f';
        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
        OMalletIndicator->Visible = false;
        return;
    }

    if(OMalletClicked != 'x') {
        CancelPowerups();
    	OMalletClicked = 't';
    	TurnMessageLabel->Text = "";
        WinnerLabel->Text = "Break a Tile!";
    	CurrentPlayerSymbolLabel->Text = "";
        OMalletIndicator->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::XLineEraseClick(TObject *Sender)
{
    if(currentPlayerSymbol == 'O')
        return;

    if(XLineEraseClicked == 't') {
        XLineEraseClicked = 'f';
        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
        XLineEraseIndicator->Visible = false;
        return;
    }


    if(XLineEraseClicked != 'x') {
        CancelPowerups();
    	XLineEraseClicked = 't';
    	TurnMessageLabel->Text = "";
        WinnerLabel->Text = "Erase a Horizontal Line";
    	CurrentPlayerSymbolLabel->Text = "";
        XLineEraseIndicator->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OLineEraseClick(TObject *Sender)
{
    if(currentPlayerSymbol == 'X')
        return;

    if(OLineEraseClicked == 't') {
        OLineEraseClicked = 'f';
        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
        OLineEraseIndicator->Visible = false;
        return;
    }


    if(OLineEraseClicked != 'x') {
        CancelPowerups();
    	OLineEraseClicked = 't';
    	TurnMessageLabel->Text = "";
        WinnerLabel->Text = "Erase a Horizontal Line";
    	CurrentPlayerSymbolLabel->Text = "";
        OLineEraseIndicator->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::XShieldClick(TObject *Sender)
{
    if(currentPlayerSymbol == 'O')
        return;

    if(XShieldClicked == 't') {
        XShieldClicked = 'f';
        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
        XShieldIndicator->Visible = false;
        return;
    }

    if(XShieldClicked != 'x') {
        CancelPowerups();
    	XShieldClicked = 't';
    	TurnMessageLabel->Text = "";
        WinnerLabel->Text = "Protect a Tile";
    	CurrentPlayerSymbolLabel->Text = "";
        XShieldIndicator->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OShieldClick(TObject *Sender)
{
    if(currentPlayerSymbol == 'X')
        return;

    if(OShieldClicked == 't') {
        OShieldClicked = 'f';
        WinnerLabel->Text = "";
        TurnMessageLabel->Text = "It is your turn player:";
        CurrentPlayerSymbolLabel->Text = currentPlayerSymbol;
        OShieldIndicator->Visible = false;
        return;
    }

    if(OShieldClicked != 'x') {
        CancelPowerups();
    	OShieldClicked = 't';
    	TurnMessageLabel->Text = "";
        WinnerLabel->Text = "Protect a Tile";
    	CurrentPlayerSymbolLabel->Text = "";
        OShieldIndicator->Visible = true;
    }
}
//---------------------------------------------------------------------------


