#include "WxWindow.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "BoardCollection.h"

bool PuzzleSolver2dApp::OnInit(){
    MainFrame *frame = new MainFrame();
    frame->Show(true);
    return true;
}

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "2D Puzzle solver", wxPoint(10, 10), wxSize(800, 600)){
  //Menu
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID::mnuLoadSollution, "&Load...\tCtrl-L", "Loads sollution from file");
  menuFile->Append(ID::mnuSaveSollution, "&Save...\tCtrl-S", "Saves sollution to file");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");

  SetMenuBar( menuBar );

  CreateStatusBar();
  SetStatusText("Solve 2D puzzles!");

  //Validator for text boxes
  wxTextValidator validator(wxFILTER_INCLUDE_CHAR_LIST);
  wxArrayString letterList;
  wxString valid_chars(wxT("0123456789"));
  size_t len = valid_chars.Length();
  for (size_t i=0; i<len; i++)
    letterList.Add(wxString(valid_chars.GetChar(i)));
  validator.SetIncludes(letterList);

  //Window objects
  wxBoxSizer *sizerMaster = new wxBoxSizer(wxHORIZONTAL);

  // Manual boards
  wxBoxSizer *sizerCol1 = new wxBoxSizer(wxVERTICAL);
  sizerCol1->Add(new wxStaticText(this, wxID_ANY, "Manual boards"));
  sizerCol1->Add(new wxListBox(this, ID::ltbBoards, wxDefaultPosition, wxSize(100, 200)));
  sizerCol1->Add(new wxTextCtrl(this, ID::tctSizeX, "4", wxDefaultPosition, wxDefaultSize, 0, validator));
  sizerCol1->Add(new wxTextCtrl(this, ID::tctSizeY, "5", wxDefaultPosition, wxDefaultSize, 0, validator));
  sizerCol1->Add(new wxButton(this, ID::btnNewBoard, "New board"), 0, 0, 0);
  sizerCol1->Add(new wxButton(this, ID::btnDeleteBoard, "Delete board"), 0, 0, 0);
  sizerCol1->Add(new wxButton(this, ID::btnCreateCollection, "Create collection"), 0, 0, 0);

  // Selected board
  wxBoxSizer *sizerCol2 = new wxBoxSizer(wxVERTICAL);
  sizerCol2->Add(new wxStaticText(this, wxID_ANY, "Board"));
  sizerCol2->Add(new BoardFrame(this, ID::frmBoardFrame, BoardFrameType::board, wxDefaultPosition, wxSize(4*SQUARE_SIZE+2, 5*SQUARE_SIZE+2)));
  sizerCol2->Add(new wxListBox(this, ID::ltbPieces, wxDefaultPosition, wxSize(100, 200)));
  sizerCol2->Add(new wxButton(this, ID::btnNewPiece, "New piece"), 0, 0, 0);
  sizerCol2->Add(new wxButton(this, ID::btnDeletePiece, "Delete piece"), 0, 0, 0);

  // Selected piece
  wxBoxSizer *sizerCol3 = new wxBoxSizer(wxVERTICAL);
  sizerCol3->Add(new wxStaticText(this, wxID_ANY, "Piece"));
  sizerCol3->Add(new wxStaticText(this, wxID_ANY, "Squares"));
  sizerCol3->Add(new wxListBox(this, ID::ltbSquares, wxDefaultPosition, wxSize(100, 200)));
  wxComboBox* b = new wxComboBox(this, ID::cmbColors);
  for(int i = 0; i < COLOR::count; i++)
    b->Append(COLOR_NAME[i]);
  sizerCol3->Add(b);

  // Board Collection
  wxBoxSizer *sizerCol4 = new wxBoxSizer(wxVERTICAL);
  sizerCol4->Add(new wxStaticText(this, wxID_ANY, "Board collections"));
  sizerCol4->Add(new wxListBox(this, ID::ltbCollections, wxDefaultPosition, wxSize(100, 200)));
  sizerCol4->Add(new wxButton(this, ID::btnSetGoal, "Set goal"), 0, 0, 0);

  // Selected board and neighbours
  wxBoxSizer *sizerCol5 = new wxBoxSizer(wxVERTICAL);
  sizerCol5->Add(new wxStaticText(this, ID::lblCollectionBoardName, "Board"));
  sizerCol5->Add(new BoardFrame(this, ID::frmNeighbourFrame, BoardFrameType::boardCollection, wxDefaultPosition, wxSize(4*SQUARE_SIZE+2, 5*SQUARE_SIZE+2)));
  sizerCol5->Add(new wxComboBox(this, ID::cmbNeighbours));
  sizerCol5->Add(new wxButton(this, ID::btnCollectionListType, "Start"), 0, 0, 0);
  sizerCol5->Add(new wxComboBox(this, ID::cmbCollectionList));

  sizerMaster->Add(sizerCol1);
  sizerMaster->Add(sizerCol2);
  sizerMaster->Add(sizerCol3);
  sizerMaster->AddSpacer(50);
  sizerMaster->Add(sizerCol4);
  sizerMaster->Add(sizerCol5);

  SetSizer(sizerMaster);

  //Binds
  Bind(wxEVT_MENU, &MainFrame::onExit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &MainFrame::load, this, ID::mnuLoadSollution);
  Bind(wxEVT_MENU, &MainFrame::save, this, ID::mnuSaveSollution);
  Bind(wxEVT_BUTTON, &MainFrame::onNewBoard, this, ID::btnNewBoard);
  Bind(wxEVT_BUTTON, &MainFrame::onDeleteBoard, this, ID::btnDeleteBoard);
  Bind(wxEVT_BUTTON, &MainFrame::onCreateCollection, this, ID::btnCreateCollection);
  Bind(wxEVT_LISTBOX, &MainFrame::onSelectBoard, this, ID::ltbBoards);

  Bind(wxEVT_BUTTON, &MainFrame::onNewPiece, this, ID::btnNewPiece);
  Bind(wxEVT_BUTTON, &MainFrame::onDeletePiece, this, ID::btnDeletePiece);
  Bind(wxEVT_LISTBOX, &MainFrame::onSelectPiece, this, ID::ltbPieces);

  Bind(wxEVT_COMBOBOX, &MainFrame::onChangeColor, this, ID::cmbColors);
  Bind(wxEVT_COMBOBOX, &MainFrame::onChangeNeighbour, this, ID::cmbNeighbours);
  Bind(wxEVT_COMBOBOX, &MainFrame::onChangeCollectionList, this, ID::cmbCollectionList);

  Bind(wxEVT_BUTTON, &MainFrame::onSetGoal, this, ID::btnSetGoal);
  Bind(wxEVT_BUTTON, &MainFrame::onChangeCollectionListType, this, ID::btnCollectionListType);
}

void MainFrame::selectBoard(Board* selectedBoard){
  cout << "_selectedBoard = " << selectedBoard << endl;
  //Clear piece list
  selectPiece(nullptr);
  wxListBox* ltb = (wxListBox*)FindWindow(ID::ltbPieces);
  ltb->Clear();
  ltb->DeselectAll();

  //Draw selected board
  _selectedBoard = selectedBoard;
  BoardFrame* frm = (BoardFrame*)FindWindow(ID::frmBoardFrame);
  frm->board(selectedBoard);

  //Draw piece list
  if(_selectedBoard != nullptr){
    int pieceCount = _selectedBoard->pieceCount();
    for(int i = 0; i < pieceCount; i++){
      ltb->Append("Piece" + to_string(i));
    }
  }
}

void MainFrame::selectCollection(BoardCollection* newCollection){
  cout << "_selectedCollection = " << newCollection << endl;
  _selectedCollection = newCollection;
  Board* selectedBoard = nullptr;
  if(newCollection != nullptr)
    selectedBoard = newCollection->board(0);
  selectCollectionBoard(selectedBoard);
}

void MainFrame::selectCollectionBoard(Board* board){
  cout << "_selectedCollectionBoard = " << board << endl;
  _selectedCollectionBoard = board;
  auto caption = (wxStaticText*)FindWindow(ID::lblCollectionBoardName);
  caption->SetLabel("Board");
  wxComboBox* cmb = (wxComboBox*)FindWindow(ID::cmbNeighbours);
  cmb->Clear();
  auto frm = (BoardFrame*)FindWindow(ID::frmNeighbourFrame);
  frm->board(board);
  if(board == nullptr)
    return;
  list<string> neighbourDescriptions = board->neighbourDescriptionList();
  for(string s: neighbourDescriptions)
    cmb->Append(s);
  caption->SetLabel(to_string(board->id()) + " (" + to_string(board->stepsLeft()) + ")");
}

void MainFrame::selectPiece(int pieceId){
  if(_selectedBoard == nullptr)
    return;
  selectPiece(_selectedBoard->pieces(pieceId));
}

void MainFrame::selectPiece(Piece* newPiece){
  cout << "_selectPiece = " << _selectedPiece << endl;

  //Clear square list
  wxListBox* ltb = (wxListBox*)FindWindow(ID::ltbSquares);
  ltb->Clear();
  ltb->DeselectAll();

  _selectedPiece = newPiece;

  //Draw square list
  if(_selectedPiece == nullptr)
    return;
  int squareCount = _selectedPiece->squareCount();
  for(int i = 0; i < squareCount; i++){
    tuple<int, int> s = _selectedPiece->square(i);
    ltb->Append("" + to_string(get<0>(s)) + ", " + to_string(get<1>(s)));
  }

  //Change color dropdown
  wxComboBox* cmb = (wxComboBox*)FindWindow(ID::cmbColors);
  cmb->Select(_selectedPiece->color());
}

void MainFrame::clickSquare(int x, int y){
  //Get clicked piece or null
  if(!_selectedBoard->inBounds(x, y))
    return;
  Piece* clickedPiece = _selectedBoard->pieces(x, y);

  //Add square
  if(clickedPiece == nullptr){
    //Add square to piece
    if(_selectedPiece == nullptr)
      return;
    _selectedPiece->addSquare({x, y}, _selectedBoard->boardAddress());

    //Add square to list of squares
    wxListBox* ltb = (wxListBox*)FindWindow(ID::ltbSquares);
    ltb->Append("" + to_string(x) + ", " + to_string(y));

    //Redraw board
    auto frm = (BoardFrame*)FindWindow(ID::frmBoardFrame);
    frm->Refresh();
  }else{
    //Select piece
    if(_selectedBoard == nullptr)
      return;
    selectPiece(_selectedBoard->pieces(x, y));

    //Select listbox row
    if(_selectedPiece == nullptr)
      return;
    int pieceId = _selectedBoard->pieceId(_selectedPiece);
    wxListBox* ltb = (wxListBox*)FindWindow(ID::ltbPieces);
    ltb->Select(pieceId);
  }
}

void MainFrame::rightClickSquare(int x, int y){
  //Get clicked piece or null
  if(!_selectedBoard->inBounds(x, y))
    return;
  Piece* clickedPiece = _selectedBoard->pieces(x, y);

  //Remove square
  if(clickedPiece == nullptr || clickedPiece != _selectedPiece)
    return;
  int squareId = _selectedPiece->removeSquare({x, y}, _selectedBoard->boardAddress());
  if(squareId == -1)
    return;

  //Remove square from list of squares
  wxListBox* ltb = (wxListBox*)FindWindow(ID::ltbSquares);
  ltb->Delete(squareId);

  //Redraw board
  auto frm = (BoardFrame*)FindWindow(ID::frmBoardFrame);
  frm->Refresh();
}

void MainFrame::switchCollectionListType(){
  if(_selectedCollection == nullptr)
    return;
  wxButton* btn = (wxButton*)FindWindow(ID::btnCollectionListType);
  wxComboBox* cmb = (wxComboBox*)FindWindow(ID::cmbCollectionList);
  cmb->Clear();
  list<string> listItems;

  if(_collectionListType == CollectionListType::start){
    listItems = _selectedCollection->goalDescriptionList();
    _collectionListType = CollectionListType::goal;
    btn->SetLabel("Goal");
  }else if(_collectionListType == CollectionListType::goal){
    listItems = _selectedCollection->mostDescriptionList();
    _collectionListType = CollectionListType::longest;
    btn->SetLabel("Longest");
  }else if(_collectionListType == CollectionListType::longest){
    listItems = _selectedCollection->startDescriptionList();
    _collectionListType = CollectionListType::start;
    btn->SetLabel("Start");
  }
  for(string s: listItems){
    cmb->Append(s);
  }
}

void MainFrame::onExit(wxCommandEvent& event){
    Close(true);
}

void MainFrame::load(wxCommandEvent& event){
  free();
  wxFileDialog *LoadDialog = new wxFileDialog(this, _("Load File"), wxEmptyString, wxEmptyString,
      _("Text files (*.txt)|*.txt"),
      wxFD_OPEN, wxDefaultPosition);
	if (LoadDialog->ShowModal() == wxID_OK)
	{
		ifstream inputFile;
		string line;
		inputFile.open(LoadDialog->GetPath());
    auto ltb = (wxListBox*)FindWindow(ID::ltbBoards);
    Board* newBoard = nullptr;
    while(inputFile.peek() != 'e'){
      newBoard = new Board(inputFile);
      _boards.push_back(newBoard);
      ltb->Append("Board" + to_string(_boards.size() - 1));
    }
    getline(inputFile, line);
    if(_boards.size() > 0){
      ltb->Select(_boards.size() - 1);
      selectBoard(newBoard);
    }

    ltb = (wxListBox*)FindWindow(ID::ltbCollections);
    BoardCollection* newCollection = nullptr;
    while(inputFile.peek() != 'e'){
      newCollection = new BoardCollection(inputFile);
      _collections.push_back(newCollection);
      ltb->Append("Collection" + to_string(_collections.size() - 1));
      newCollection->connectGoal(_boards);
    }
    getline(inputFile, line);
    if(_collections.size() > 0){
      ltb->Select(_collections.size() - 1);
      selectCollection(newCollection);
    }
		inputFile.close();
	}
  switchCollectionListType();
	cout << "Load complete" << endl;
	LoadDialog->Destroy();
}

void MainFrame::save(wxCommandEvent& event){
  wxFileDialog *SaveDialog = new wxFileDialog(this, _("Save File As _?"), wxEmptyString, wxEmptyString,
      _("Text files (*.txt)|*.txt"),
      wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
	if (SaveDialog->ShowModal() == wxID_OK)
	{
		ofstream outputFile;
		outputFile.open(SaveDialog->GetPath());
    int i = 0;
    for(Board* b: _boards)
      b->id(i++);
    for(Board* b: _boards)
      outputFile << b->getSaveString();
    outputFile << "e\n";
    for(BoardCollection* c: _collections)
      outputFile << c->getSaveString();
    outputFile << "e\n";
		outputFile.close();
	}
	cout << "Save complete" << endl;
	SaveDialog->Destroy();
}

void MainFrame::onSelectBoard(wxCommandEvent& event){
  cout << "onSelectBoard" << event.GetInt() << endl;
  selectBoard(_boards[event.GetInt()]);
}

void MainFrame::onNewBoard(wxCommandEvent& event){
  wxTextCtrl* tSizeX = (wxTextCtrl*)FindWindow(ID::tctSizeX);
  wxTextCtrl* tSizeY = (wxTextCtrl*)FindWindow(ID::tctSizeY);
  int sizeX;
  int sizeY;
  try{
    sizeX = wxAtoi(tSizeX->GetValue());
    sizeY = wxAtoi(tSizeY->GetValue());
  }catch(exception const& e){
    cout << "Error: invalid x/y size" << endl;
  }

  Board* newBoard = new Board(sizeX, sizeY);
  _boards.push_back(newBoard);
  if(sizeX == 4 && sizeY == 5){
    newBoard->addPiece(new Piece({{1, 4}, {2, 4}}));
    newBoard->addPiece(new Piece({{0, 3}, {0, 2}}, COLOR::green));
    newBoard->addPiece(new Piece({{0, 1}, {0, 0}}, COLOR::green));
    newBoard->addPiece(new Piece({{3, 3}, {3, 2}}, COLOR::green));
    newBoard->addPiece(new Piece({{3, 1}, {3, 0}}, COLOR::green));
    newBoard->addPiece(new Piece({{1, 3}}, COLOR::blue));
    newBoard->addPiece(new Piece({{2, 3}}, COLOR::blue));
    newBoard->addPiece(new Piece({{1, 2}}, COLOR::blue));
    newBoard->addPiece(new Piece({{2, 2}}, COLOR::blue));
    newBoard->addPiece(new Piece({{1, 1}, {2, 1}, {1, 0}, {2, 0}}, COLOR::red));
  }

  auto ltb = (wxListBox*)FindWindow(ID::ltbBoards);
  ltb->Append("Board" + to_string(_boards.size() - 1));
  ltb->Select(_boards.size() - 1);
  selectBoard(newBoard);
}

void MainFrame::onDeleteBoard(wxCommandEvent& event){
  cout << "onDeleteBoard" << endl;
  if(_selectedBoard == nullptr)
    return;

  int boardId = 0;
  while(boardId < (int)_boards.size() && _boards[boardId] != _selectedBoard)
    boardId++;
  _boards.erase(_boards.begin() + boardId);

  wxListBox* ltb = (wxListBox*)FindWindow(ID::ltbBoards);
  ltb->Delete(ltb->GetCount() - 1);
  boardId--;
  if(boardId < 0)
    boardId = 0;
  if(_boards.size() > 0){
    selectBoard(_boards[boardId]);
    ltb->Select(boardId);
  }else{
    selectBoard(nullptr);
    ltb->DeselectAll();
  }
}

void MainFrame::onCreateCollection(wxCommandEvent& event){
  if(_selectedBoard == nullptr){
    cout << "No board selected" << endl;
    return;
  }
  BoardCollection* newCollection = new BoardCollection();
  newCollection->setStartingBoard(_selectedBoard->deepCopy());
  newCollection->generateChildren();
  _collections.push_back(newCollection);

  auto ltb = (wxListBox*)FindWindow(ID::ltbCollections);
  ltb->Append("Collection" + to_string(_collections.size() - 1));
  ltb->Select(_collections.size() - 1);
  selectCollection(newCollection);
}

void MainFrame::onSelectPiece(wxCommandEvent& event){
  selectPiece(event.GetInt());
}

void MainFrame::onNewPiece(wxCommandEvent& event){
  if(_selectedBoard == nullptr)
    return;
  COLOR c = static_cast<COLOR>(_selectedBoard->pieceCount() % COLOR::count);
  _selectedBoard->addPiece(new Piece(c));

  auto ltb = (wxListBox*)FindWindow(ID::ltbPieces);
  ltb->Append("Piece" + to_string(_selectedBoard->pieceCount() - 1));
}

void MainFrame::onDeletePiece(wxCommandEvent& event){
  if(_selectedBoard == nullptr || _selectedPiece == nullptr)
    return;

  int pieceId = 0;
  while(pieceId < _selectedBoard->pieceCount() && _selectedBoard->pieces(pieceId) != _selectedPiece)
    pieceId++;
  _selectedBoard->deletePiece(pieceId);
  selectPiece(nullptr);

  wxListBox* ltb = (wxListBox*)FindWindow(ID::ltbPieces);
  ltb->Delete(ltb->GetCount() - 1);

  pieceId--;
  if(pieceId < 0)
    pieceId = 0;
  if(_selectedBoard->pieceCount() > 0){
    selectPiece(_selectedBoard->pieces(pieceId));
    ltb->Select(pieceId);
  }else{
    selectPiece(nullptr);
    ltb->DeselectAll();
  }

  auto frm = (BoardFrame*)FindWindow(ID::frmBoardFrame);
  frm->Refresh();
}

void MainFrame::onChangeColor(wxCommandEvent& event){
  if(_selectedPiece == nullptr)
    return;
  _selectedPiece->color(event.GetInt());

  auto frm = (BoardFrame*)FindWindow(ID::frmBoardFrame);
  frm->Refresh();
}

void MainFrame::onChangeNeighbour(wxCommandEvent& event){
  cout << "onChangeNeighbour: " << event.GetInt() << endl;
  if(_selectedCollection == nullptr || _selectedCollectionBoard == nullptr)
    return;
  selectCollectionBoard(_selectedCollectionBoard->neighbour(event.GetInt()));
}
void MainFrame::onChangeCollectionList(wxCommandEvent& event){
  cout << "onChangeCollectionList: " << event.GetInt() << endl;
  if(_selectedCollection == nullptr)
    return;
  if(_collectionListType == CollectionListType::goal){
    selectCollectionBoard(_selectedCollection->goalBoard(event.GetInt()));
  }else if(_collectionListType == CollectionListType::longest){
    selectCollectionBoard(_selectedCollection->mostStepsBoard(event.GetInt()));
  }else if(_collectionListType == CollectionListType::start){
    selectCollectionBoard(_selectedCollection->board(event.GetInt()));
  }
}

void MainFrame::onSetGoal(wxCommandEvent& event){
  if(_selectedBoard == nullptr){
    cout << "No board selected" << endl;
    return;
  }
  if(_selectedCollection == nullptr){
    cout << "No collection selected" << endl;
    return;
  }
  _selectedCollection->goal(_selectedBoard->deepCopy());
  switchCollectionListType();
}

void MainFrame::onChangeCollectionListType(wxCommandEvent& event){
  switchCollectionListType();
}

void MainFrame::free(){
  for(Board* b: _boards){
    b->free();
    delete b;
  }
  _boards.clear();
  for(BoardCollection* b: _collections){
    b->free();
    delete b;
  }
  _collections.clear();
  selectBoard(nullptr);
  selectCollection(nullptr);
  wxListBox* ltb = (wxListBox*)FindWindow(ID::ltbBoards);
  ltb->Clear();
  ltb->DeselectAll();
  ltb = (wxListBox*)FindWindow(ID::ltbCollections);
  ltb->Clear();
  ltb->DeselectAll();
}

BoardFrame::BoardFrame(wxWindow *parent, wxWindowID id, BoardFrameType type, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE)
{
  this->SetBackgroundStyle(wxBG_STYLE_PAINT);

  Bind(wxEVT_PAINT, &BoardFrame::onPaint, this);
  Bind(wxEVT_LEFT_UP, &BoardFrame::onClick, this);
  Bind(wxEVT_RIGHT_UP, &BoardFrame::onRightClick, this);
  _type = type;
}

BoardFrame::~BoardFrame()
{

}

wxSize BoardFrame::DoGetBestSize() const {
  if(_board)
    return wxSize(_board->sizeX()*20, _board->sizeY()*20);
  else
    return wxSize(100, 100);
}

void BoardFrame::onPaint(wxPaintEvent& event){
  wxAutoBufferedPaintDC dc(this);
  dc.SetBackground(wxBrush(this->GetParent()->GetBackgroundColour()));
  dc.Clear();

  auto gc = wxGraphicsContext::Create(dc);

  int sizeX = 4 * SQUARE_SIZE;
  int sizeY = 5 * SQUARE_SIZE;
  if(_board){
    sizeX = _board->sizeX() * SQUARE_SIZE;
    sizeY = _board->sizeY() * SQUARE_SIZE;
  }

  if (gc)
  {
    int width = 1;
    gc->SetPen(wxPen(wxColour("#000000")));
    gc->SetBrush(wxBrush(wxColour("#000000")));
    gc->DrawRectangle(0, 0, sizeX, width);
    gc->DrawRectangle(0, sizeY, sizeX, width);
    gc->DrawRectangle(0, 0, width, sizeY);
    gc->DrawRectangle(sizeX, 0, width, sizeY);
    if(_board)
      _board->draw(gc);

    delete gc;
  }
}

void BoardFrame::onClick(wxMouseEvent& event){
  cout << "Click" << endl;
  cout << "" + to_string(event.GetPosition().x) + ", " << to_string(event.GetPosition().y) << endl;
  if(!_board)
    return;
  if(_type == BoardFrameType::board){
    int x = event.GetPosition().x / SQUARE_SIZE;
    int y = event.GetPosition().y / SQUARE_SIZE;
    MainFrame* parent = (MainFrame*)GetParent();
    parent->clickSquare(x, y);
  }else{
    double x = (double)event.GetPosition().x / (double)SQUARE_SIZE;
    double y = (double)event.GetPosition().y / (double)SQUARE_SIZE;
    MainFrame* parent = (MainFrame*)GetParent();
    Board* neighbour = _board->closestNeighbour({x, y});
    if(neighbour != nullptr)
      parent->selectCollectionBoard(neighbour);
  }
}

void BoardFrame::onRightClick(wxMouseEvent& event){
  cout << "RightClick" << endl;
  cout << "" + to_string(event.GetPosition().x) + ", " << to_string(event.GetPosition().y) << endl;
  if(_board == nullptr)
    return;
  if(_type == BoardFrameType::board){
    int x = event.GetPosition().x / SQUARE_SIZE;
    int y = event.GetPosition().y / SQUARE_SIZE;
    MainFrame* parent = (MainFrame*)GetParent();
    parent->rightClickSquare(x, y);
  }
}

void BoardFrame::board(Board* board){
  _board = board;
  if(board)
    this->SetSize(wxSize(SQUARE_SIZE * board->sizeX() + 2, SQUARE_SIZE * board->sizeY() + 2));
  else
    this->SetSize(wxSize(SQUARE_SIZE * 4 + 2, SQUARE_SIZE * 5 + 2));
  Refresh();
}
