#include <iostream>
#include <stdio.h>
using namespace std;

//由于每个节点都有特定的问题状态，所以我们也要实现一个State类：
class State
{
public:
  int    board;
  int    playerNo;
  int    visitCount;
  double winScore;
  State()
  {
    board = new Board();
  }

  State(State state)
  {
    board      = new Board(state.getBoard());
    playerNo   = state.getPlayerNo();
    visitCount = state.getVisitCount();
    winScore   = state.getWinScore();
  }

  State(Board board)
  {
    board = new Board(board);
  }

  Board getBoard()
  {
    return board;
  }

  void setBoard(Board board)
  {
    board = board;
  }

  int getPlayerNo()
  {
    return playerNo;
  }

  void setPlayerNo(int playerNo)
  {
    playerNo = playerNo;
  }

  int getOpponent()
  {
    return 3 - playerNo;
  }

  int getVisitCount()
  {
    return visitCount;
  }

  void setVisitCount(int visitCount)
  {
    visitCount = visitCount;
  }

  double getWinScore()
  {
    return winScore;
  }

  void setWinScore(double winScore)
  {
    winScore = winScore;
  }

  List<State> getAllPossibleStates()
  {
    List<State>    possibleStates     = new ArrayList<>();
    List<Position> availablePositions = board.getEmptyPositions();
    availablePositions.forEach(p->{
      State newState = new State(board);
      newState.setPlayerNo(3 - playerNo);
      newState.getBoard().performMove(newState.getPlayerNo(), p);
      possibleStates.add(newState);
    });
    return possibleStates;
  }

  void incrementVisit()
  {
    visitCount++;
  }

  void addScore(double score)
  {
    if (winScore != Integer.MIN_VALUE)
      winScore += score;
  }

  void randomPlay()
  {
    List<Position> availablePositions = board.getEmptyPositions();
    int            totalPossibilities = availablePositions.size();
    int            selectRandom       = (int)(Math.random() * totalPossibilities);
    board.performMove(playerNo, availablePositions.get(selectRandom));
  }

  void togglePlayer()
  {
    playerNo = 3 - playerNo;
  }
};
//我们需要Tree和Node类的基本实现来获得树搜索功能：
class Node
{
public:
  State      state;
  Node       parent;
  List<Node> childArray;

  Node()
  {
    state = new State();
    childArray = new ArrayList<>();
  }

  Node(State state)
  {
    state = state;
    childArray = new ArrayList<>();
  }

  Node(State state, Node parent, List<Node> childArray)
  {
    state      = state;
    parent     = parent;
    childArray = childArray;
  }

  Node(Node node)
  {
    childArray = new ArrayList<>();
    state      = new State(node.getState());
    if (node.getParent() != null)
      parent = node.getParent();
    List<Node> childArray = node.getChildArray();
    for (Node child : childArray)
    {
      childArray.add(new Node(child));
    }
  }

  State getState()
  {
    return state;
  }

  void setState(State state)
  {
    state = state;
  }

  Node getParent()
  {
    return parent;
  }

  void setParent(Node parent)
  {
    parent = parent;
  }

  List<Node> getChildArray()
  {
    return childArray;
  }

  void setChildArray(List<Node> childArray)
  {
    childArray = childArray;
  }

  Node getRandomChildNode()
  {
    int noOfPossibleMoves = childArray.size();
    int selectRandom      = (int)(Math.random() * noOfPossibleMoves);
    return childArray.get(selectRandom);
  }

  Node getChildWithMaxScore()
  {
    return Collections.max(childArray, Comparator.comparing(c->{
      return c.getState().getVisitCount();
    }));
  }
};
class Tree
{
public:
  Node root;

  Tree()
  {
    root = new Node();
  }

  Tree(Node root)
  {
    root = root;
  }

  Node getRoot()
  {
    return root;
  }

  void setRoot(Node root)
  {
    root = root;
  }

  void addChild(Node parent, Node child)
  {
    parent.getChildArray().add(child);
  }
};
//实现MonteCarloTreeSearch类，它将负责从给定的游戏位置找到下一个最佳移动：
class MonteCarloTreeSearch
{
public:
  static int WIN_SCORE = 10;
  int        level;
  int        opponent;
  MonteCarloTreeSearch()
  {
    level = 3;
  }

  int getLevel()
  {
    return level;
  }

  void setLevel(int level)
  {
    level = level;
  }

  int getMillisForCurrentLevel()
  {
    return 2 * (level - 1) + 1;
  }

  Board findNextMove(Board board, int playerNo)
  {
    long start = System.currentTimeMillis();
    long end   = start + 60 * getMillisForCurrentLevel();

    opponent      = 3 - playerNo;
    Tree tree     = new Tree();
    Node rootNode = tree.getRoot();
    rootNode.getState().setBoard(board);
    rootNode.getState().setPlayerNo(opponent);

    while (System.currentTimeMillis() < end)
    {
      // Phase 1 - Selection
      Node promisingNode = selectPromisingNode(rootNode);
      // Phase 2 - Expansion
      if (promisingNode.getState().getBoard().checkStatus() == Board.IN_PROGRESS)
        expandNode(promisingNode);

      // Phase 3 - Simulation
      Node nodeToExplore = promisingNode;
      if (promisingNode.getChildArray().size() > 0)
      {
        nodeToExplore = promisingNode.getRandomChildNode();
      }
      int playoutResult = simulateRandomPlayout(nodeToExplore);
      // Phase 4 - Update
      backPropogation(nodeToExplore, playoutResult);
    }

    Node winnerNode = rootNode.getChildWithMaxScore();
    tree.setRoot(winnerNode);
    return winnerNode.getState().getBoard();
  }

  Node selectPromisingNode(Node rootNode)
  {
    Node node = rootNode;
    while (node.getChildArray().size() != 0)
    {
      node = UCT.findBestNodeWithUCT(node);
    }
    return node;
  }

  void expandNode(Node node)
  {
    List<State> possibleStates = node.getState().getAllPossibleStates();
    possibleStates.forEach(state->{
      Node newNode = new Node(state);
      newNode.setParent(node);
      newNode.getState().setPlayerNo(node.getState().getOpponent());
      node.getChildArray().add(newNode);
    });
  }

  void backPropogation(Node nodeToExplore, int playerNo)
  {
    Node tempNode = nodeToExplore;
    while (tempNode != null)
    {
      tempNode.getState().incrementVisit();
      if (tempNode.getState().getPlayerNo() == playerNo)
        tempNode.getState().addScore(WIN_SCORE);
      tempNode = tempNode.getParent();
    }
  }

  int simulateRandomPlayout(Node node)
  {
    Node  tempNode    = new Node(node);
    State tempState   = tempNode.getState();
    int   boardStatus = tempState.getBoard().checkStatus();

    if (boardStatus == opponent)
    {
      tempNode.getParent().getState().setWinScore(Integer.MIN_VALUE);
      return boardStatus;
    }
    while (boardStatus == Board.IN_PROGRESS)
    {
      tempState.togglePlayer();
      tempState.randomPlay();
      boardStatus = tempState.getBoard().checkStatus();
    }

    return boardStatus;
  }
};

//我们继续迭代所有四个阶段，直到预定义的时间，最后，我们得到一个具有可靠统计数据的树，以做出决定。
//现在，让我们为所有阶段实现方法。
//我们将从选择阶段开始，这也需要UCT实现：

class UCT
{
public:
  static double uctValue(int totalVisit, double nodeWinScore, int nodeVisit)
  {
    if (nodeVisit == 0)
    {
      return Integer.MAX_VALUE;
    }
    return (nodeWinScore / (double)nodeVisit) + 1.41 * Math.sqrt(Math.log(totalVisit) / (double)nodeVisit);
  }

  static Node findBestNodeWithUCT(Node node)
  {
    int parentVisit = node.getState().getVisitCount();
    return Collections.max(
        node.getChildArray(),
        Comparator.comparing(c->uctValue(parentVisit, c.getState().getWinScore(), c.getState().getVisitCount())));
  }
};
class Position
{
public:
  int x;
  int y;

  Position()
  {
  }

  Position(int x, int y)
  {
    x = x;
    y = y;
  }

  int getX()
  {
    return x;
  }

  void setX(int x)
  {
    x = x;
  }

  int getY()
  {
    return y;
  }

  void setY(int y)
  {
    y = y;
  }

};

//现在已经完成了MCTS的实施。需要一个Tic-Tac-Toe特定的Board类实现。
class Board
{
public:
  int        boardValues[3][3];
  static int DEFAULT_BOARD_SIZE = 3;
  static int IN_PROGRESS        = -1;
  static int DRAW               = 0;
  static int P1                 = 1;
  static int P2                 = 2;
  Board()
  {
    boardValues = new int[DEFAULT_BOARD_SIZE][DEFAULT_BOARD_SIZE];
  }
  Board(int boardSize)
  {
    boardValues = new int[boardSize][boardSize];
  }

  Board(int[][] boardValues)
  {
    boardValues = boardValues;
  }

  Board(int[][] boardValues, int totalMoves)
  {
    boardValues = boardValues;
    totalMoves  = totalMoves;
  }

  Board(Board board)
  {
    int boardLength     = board.getBoardValues().length;
    boardValues    = new int[boardLength][boardLength];
    int[][] boardValues = board.getBoardValues();
    int n               = boardValues.length;
    for (int i = 0; i < n; i++)
    {
      int m = boardValues[i].length;
      for (int j = 0; j < m; j++)
      {
        boardValues[i][j] = boardValues[i][j];
      }
    }
  }

  void performMove(int player, Position p)
  {
    totalMoves++;
    boardValues[p.getX()][p.getY()] = player;
  }

  int[][] getBoardValues()
  {
    return boardValues;
  }

  void setBoardValues(int[][] boardValues)
  {
    boardValues = boardValues;
  }

  int checkStatus()
  {
    int boardSize = boardValues.length;
    int maxIndex  = boardSize - 1;
    int[] diag1   = new int[boardSize];
    int[] diag2   = new int[boardSize];

    for (int i = 0; i < boardSize; i++)
    {
      int[] row = boardValues[i];
      int[] col = new int[boardSize];
      for (int j = 0; j < boardSize; j++)
      {
        col[j] = boardValues[j][i];
      }

      int checkRowForWin = checkForWin(row);
      if (checkRowForWin != 0)
        return checkRowForWin;

      int checkColForWin = checkForWin(col);
      if (checkColForWin != 0)
        return checkColForWin;

      diag1[i] = boardValues[i][i];
      diag2[i] = boardValues[maxIndex - i][i];
    }

    int checkDia1gForWin = checkForWin(diag1);
    if (checkDia1gForWin != 0)
      return checkDia1gForWin;

    int checkDiag2ForWin = checkForWin(diag2);
    if (checkDiag2ForWin != 0)
      return checkDiag2ForWin;

    if (getEmptyPositions().size() > 0)
      return IN_PROGRESS;
    else
      return DRAW;
  }

  int checkForWin(int[] row)
  {
    boolean isEqual  = true;
    int     size     = row.length;
    int     previous = row[0];
    for (int i = 0; i < size; i++)
    {
      if (previous != row[i])
      {
        isEqual = false;
        break;
      }
      previous = row[i];
    }
    if (isEqual)
      return previous;
    else
      return 0;
  }
  void printBoard()
  {
    int size = boardValues.length;
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
      {
        cout << boardValues[i][j] << " ";
      }
      cout << endl;
    }
  }
  List<Position> getEmptyPositions()
  {
    int            size           = boardValues.length;
    List<Position> emptyPositions = new ArrayList<>();
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
      {
        if (boardValues[i][j] == 0)
          emptyPositions.add(new Position(i, j));
      }
    }
    return emptyPositions;
  }
  void printStatus()
  {
    switch (checkStatus())
    {
      case P1:
        cout << "Player 1 wins";
        break;
      case P2:
        cout << "Player 2 wins";
        break;
      case DRAW:
        cout << "Game Draw";
        break;
      case IN_PROGRESS:
        cout << "Game In Progress";
        break;
    }
  }
};
