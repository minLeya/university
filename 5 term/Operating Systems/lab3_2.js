var wdApp = new ActiveXObject("Word.Application");
wdApp.Visible = true;
wdApp.Documents.Add();
wdApp.Documents.Open("C:\\temp\\mydoc.doc");
