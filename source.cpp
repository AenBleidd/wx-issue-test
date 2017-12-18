// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/html/htmlwin.h>
#include <wx/clipbrd.h>
class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    wxHtmlWindow* m_txtInformation;
    wxBoxSizer* m_bSizer1;
    wxButton* m_btnClose;
    wxButton* m_pCopySelectedButton;
    wxButton* m_pCopyAllButton;
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_COPYSELECTED
    void OnCopySelected( wxCommandEvent& event );
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_COPYALL
    void OnCopyAll( wxCommandEvent& event );
    void copyTextToClipboard(const wxString& text);
    void OnMouseButtonEvent(wxMouseEvent& event);
    wxDECLARE_EVENT_TABLE();
};
enum
{
    ID_Hello = 1,
    ID_COPYSELECTED = 10001,
    ID_COPYALL = 10002
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello,   MyFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_BUTTON(ID_COPYSELECTED, MyFrame::OnCopySelected)
    EVT_BUTTON(ID_COPYALL, MyFrame::OnCopyAll)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );

    m_bSizer1 = new wxBoxSizer( wxVERTICAL );
    const long style = wxBORDER_NONE;
    m_txtInformation = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, style, wxEmptyString );
    m_txtInformation->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseButtonEvent, this);
    m_txtInformation->Bind(wxEVT_LEFT_UP, &MyFrame::OnMouseButtonEvent, this);
    
    m_bSizer1->Add( m_txtInformation, 1, wxEXPAND | wxALL, 5 );
    
    wxBoxSizer *bSizer2 = new wxBoxSizer(wxHORIZONTAL);
    m_bSizer1->Add(bSizer2, 0, wxALIGN_BOTTOM | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 12);

    m_pCopyAllButton = new wxButton(this, ID_COPYALL, _("Copy &All"), wxDefaultPosition, wxDefaultSize);
    bSizer2->Add(m_pCopyAllButton, 0, wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    m_pCopySelectedButton = new wxButton(this, ID_COPYSELECTED, _("Copy &Selected"), wxDefaultPosition, wxDefaultSize);
    bSizer2->Add(m_pCopySelectedButton, 0, wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    m_pCopySelectedButton->Enable(false);
    SetSizer( m_bSizer1 );

    std::string content;
    content += "<html>";
    content += "<body>";
    content += "<h1>Test</h1>";
    content += "<h2>Test</h2>";
    content += "</body>";
    content += "</html>";
    
    m_txtInformation->SetPage(content);
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::copyTextToClipboard(const wxString& text) {
    if (wxTheClipboard->Open()) {
        wxTheClipboard->Clear();
        wxTheClipboard->SetData(new wxTextDataObject(text));
        wxTheClipboard->Close();
    }
}

void MyFrame::OnMouseButtonEvent(wxMouseEvent& event) {
    m_pCopySelectedButton->Enable(m_txtInformation->SelectionToText() != wxEmptyString);
    event.Skip();
}

void MyFrame::OnCopySelected( wxCommandEvent& ) {
    copyTextToClipboard(m_txtInformation->SelectionToText());
}

void MyFrame::OnCopyAll( wxCommandEvent& ) {
    copyTextToClipboard(m_txtInformation->ToText());
}
