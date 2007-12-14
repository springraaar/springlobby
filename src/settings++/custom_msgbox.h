#ifndef CUSTOM_MSG_BOX_H_
#define CUSTOM_MSG_BOX_H_

#include <wx/msgdlg.h>
#include <wx/defs.h>

class wxIcon;
class wxWindow;
class wxPoint;
class wxString;

#define SL_MAIN_WINDOW_PTR CustomMessageBox::getLobbypointer() 
#define SE_FRAME_PTR CustomMessageBox::getSettingspointer()

int customMessageBox(wxWindow *parent, wxIcon* icon , const wxString& message,
        const wxString& caption = wxMessageBoxCaptionStr, 
        long style = wxOK|wxCENTRE,  const int x = -1, const int y = -1 );

class CustomMessageBox : public wxMessageDialog
{
public:
	CustomMessageBox(wxIcon* icon ,wxWindow *parent, const wxString& message,
	        const wxString& caption = wxMessageBoxCaptionStr,
	        long style = wxOK|wxCENTRE, const wxPoint& pos = wxDefaultPosition);
	virtual ~CustomMessageBox();
	static void setLobbypointer(wxWindow*);
	static void setSettingspointer(wxWindow*);
	static wxWindow* getLobbypointer();
	static wxWindow* getSettingspointer();
	
protected:
	static wxWindow* m_settingsWindow;
	static wxWindow* m_lobbyWindow;
};


#endif /*CUSTOM_MSG_DLG_H_*/
