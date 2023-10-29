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
    wxSize DoGetBestSize() const override;
    Board* board() {return _board;}
    void board(Board* board);

  private:
    void onPaint(wxPaintEvent& event);
    void onClick(wxMouseEvent& event);
    void onRightClick(wxMouseEvent& event);
    Board* _board = nullptr;
    BoardFrameType _type;
};

class MainFrame : public wxFrame
{
  public:
    MainFrame();
    void selectBoard(Board* newBoard);
    void selectPiece(int pieceId);
    void selectPiece(Piece* newPiece);
    void selectCollection(BoardCollection* newCollection);
    void selectCollectionBoard(Board* board);
    void clickSquare(int x, int y);
    void rightClickSquare(int x, int y);
    void switchCollectionListType();

  private:
    void onSelectBoard(wxCommandEvent& event);
    void onNewBoard(wxCommandEvent& event);
    void onDeleteBoard(wxCommandEvent& event);
    void onCreateCollection(wxCommandEvent& event);
    void onSelectPiece(wxCommandEvent& event);
    void onNewPiece(wxCommandEvent& event);
    void onDeletePiece(wxCommandEvent& event);
    void onChangeColor(wxCommandEvent& event);
    void onChangeNeighbour(wxCommandEvent& event);
    void onChangeCollectionList(wxCommandEvent& event);
    void onSetGoal(wxCommandEvent& event);
    void onChangeCollectionListType(wxCommandEvent& event);
    void onExit(wxCommandEvent& event);
    void free();
    void load(wxCommandEvent& event);
    void save(wxCommandEvent& event);
    vector<Board*> _boards;
    vector<BoardCollection*> _collections;
    Piece* _selectedPiece = nullptr;
    Board* _selectedBoard = nullptr;
    BoardCollection* _selectedCollection = nullptr;
    Board* _selectedCollectionBoard = nullptr;
    CollectionListType _collectionListType = CollectionListType::start;
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
  lblCollectionBoardName
};

#endif // WXWINDOW_H
