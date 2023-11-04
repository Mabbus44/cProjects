#ifndef WXWINDOW_H
#define WXWINDOW_H

#include <wx/wx.h>
#include "BoardCollection.h"
#include "Board.h"
#include <wx/filedlg.h>
#include <iostream>
#include <fstream>

enum BoardFrameType {board, boardCollection};
enum CollectionListType {start, goal, longest};

class PuzzleSolver2dApp : public wxApp
{
public:
  bool OnInit() override;
};

class BoardFrame : public wxWindow{
  public:
    BoardFrame(wxWindow *parent, wxWindowID id, BoardFrameType type, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);
    ~BoardFrame();

    Board* board() {return _board;}
    bool drawNumbers() {return _drawNumbers;}
    void board(Board* board);
    void drawNumbers(bool drawNumbers) {_drawNumbers = drawNumbers;}
    wxSize DoGetBestSize() const override;

  private:
    Board* _board = nullptr;
    BoardFrameType _type;
    void onClick(wxMouseEvent& event);
    void onRightClick(wxMouseEvent& event);
    void onPaint(wxPaintEvent& event);

    bool _drawNumbers = false;
};

class MainFrame : public wxFrame
{
  public:
    MainFrame();

    void clickSquare(int x, int y);
    void deletePiece(Piece* piece);
    void rightClickSquare(int x, int y);
    void selectCollection(BoardCollection* newCollection);
    void selectCollectionBoard(Board* board);
    void selectPiece(Piece* newPiece);
    void selectPiece(int pieceId);
    void switchCollectionListType();
    void selectBoard(Board* selectedBoard);

  private:
    Board* _selectedBoard = nullptr;
    Board* _selectedCollectionBoard = nullptr;
    BoardCollection* _selectedCollection = nullptr;
    CollectionListType _collectionListType = CollectionListType::start;
    Piece* _selectedPiece = nullptr;
    vector<Board*> _boards;
    vector<BoardCollection*> _collections;
    void free();
    void load(wxCommandEvent& event);
    void onChangeCollectionList(wxCommandEvent& event);
    void onChangeCollectionListType(wxCommandEvent& event);
    void onChangeColor(wxCommandEvent& event);
    void onChangeNeighbour(wxCommandEvent& event);
    void onCreateCollection(wxCommandEvent& event);
    void onDeleteBoard(wxCommandEvent& event);
    void onDeletePiece(wxCommandEvent& event);
    void onExit(wxCommandEvent& event);
    void onNewBoard(wxCommandEvent& event);
    void onNewPiece(wxCommandEvent& event);
    void onSelectPiece(wxCommandEvent& event);
    void onSetGoal(wxCommandEvent& event);
    void onToggleDrawNumber(wxCommandEvent& event);
    void save(wxCommandEvent& event);
    void onSelectBoard(wxCommandEvent& event);
};

enum ID {
  //Menu
  mnuLoadSollution, mnuSaveSollution,
  //Frames
  frmBoardFrame, frmNeighbourFrame,
  //Buttons
  btnNewBoard, btnDeleteBoard, btnCreateCollection, btnNewPiece, btnDeletePiece, btnSetGoal, btnCollectionListType,
  //ListBoxes
  ltbBoards, ltbPieces, ltbSquares, ltbCollections,
  //ComboBoxes
  cmbColors, cmbNeighbours, cmbCollectionList,
  //Labels
  lblCollectionBoardName,
  //Text controls
  tctSizeX, tctSizeY,
  //Checkboxes
  chbDrawNumbers
};

#endif // WXWINDOW_H
