# wx-issue-test
### SelectedText copy issue from wxHtmlWindow to wxClipboard test application

I have a wxWidgets (3.0.2) application and a wxHtmlWindow created this way:
```c++
wxHtmlWindow* html = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE, wxEmptyString );
```

Then I try to make two functions: OnCopyAll and OnCopySelected.

```c++
void CDlgItemProperties::copyTextToClipboard(const wxString& text) {
    if (text == wxEmptyString) return;
    if (wxTheClipboard->Open()) {
        wxTheClipboard->SetData(new wxTextDataObject(text));
        wxTheClipboard->Close();
    }
}

void CDlgItemProperties::OnCopySelected( wxCommandEvent& ) {
    copyTextToClipboard(html->SelectionToText());
}

void CDlgItemProperties::OnCopyAll( wxCommandEvent& ) {
    copyTextToClipboard(html->ToText());
}
```

The problem is that OnCopyAll works well, data is copied.

But when I try call OnCopySelected new data doesn't copied to clipboard (when I perform paste in some text editor it pastes old data).

After calling OnCopySelected stops working OnCopyAll:

```c++
OnCopyAll(...); // clipboard contains correct data
OnCopySelected(...); // data doesn't change, clipboard still contains old data from the previous function call
OnCopyAll(...); // clipboard still contains old data from the previous call
```

**Important note 1:** this code works well on Windows but works incorrect (as described above) on Linux (tested on Debian 8).

**Important note 2:** wxTheClipboard->SetData() return true (checked with modified code)

**Important note 2:** if I call wxTheClipboard->GetData() after I call wxTheClipboard->Close() it shows correct data but system clipboard still contains old data (checked with modified code)

What I do wrong?
