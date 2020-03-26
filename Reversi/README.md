## Info.h 头文件分析
描述了一个棋子对象的位置以及颜色
```
struct Info {
	size_t row, col;
	Colour colour;
};
```
## State
```
struct State {
	StateType type;  // See above
	Colour colour;   // What colour was the new piece?  (NOT what is my colour)
	Direction direction;  // In which direction from me is the new piece?
};
```
## state.h头文件分析
***state类*** 描述了三种颜色 方向和 三种类型 并封装在state class 内


## gird class
```
class Grid {
	std::vector<std::vector<Cell>> theGrid;  // The actual grid.
	TextDisplay *td = nullptr; // The text display.
	Observer<Info, StateType> *ob = nullptr;  // Another observer (intent:  graphics)
										  // Add private members, if necessary.

public:
	~Grid();

	void setObserver(Observer<Info, State> *ob);
	bool isFull() const;  // Is the game over, i.e., is the grid full?
	Colour whoWon() const; // Who has more pieces when the board is full?
	void init(size_t n); // Sets up an n x n grid.  Clears old grid, if necessary.
	void setPiece(size_t r, size_t c, Colour colour);  // Plays piece at row r, col c.
	void toggle(size_t r, size_t c);  // Flips piece at row r, col c.

	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
	//输出的是TextDisplay类的td 这是一个二维字符串数组
	//
};
```
## cell 头文件分析
***cell类*** 继承了subject 和 observer类
```
class Cell : public Subject<Info, State>, public Observer<Info, State> {
	const size_t r, c;
	Colour colour = Colour::NoColour;

	// Add other private members if necessary

public:
	Cell(size_t r, size_t c);

	void setPiece(Colour colour);    // Place a piece of given colour here.
	void toggle();         // Toggles my colour.

	void notify(Subject<Info, State> &whoFrom) override;// My neighbours will call this
														// when they've changed state
	Info getInfo() const override;
};
```
## observer 头文件
定义了声明了 subject模板类 普通类 cell
observer 是一个抽象基类

cell继承了observer类
```
template <typename InfoType, typename StateType> class Observer {
public:
	virtual void notify(Subject<InfoType, StateType> &whoFrom) = 0; 
	// pass the Subject that called the notify method
	virtual ~Observer() = default;
};
```

## subject 类 虚基类 不可定义及更改 只能继承
```
template <typename InfoType, typename StateType> class Subject {
	std::vector<Observer<InfoType, StateType>*> observers;
	StateType state;
protected:
	void setState(StateType newS);	
public:
	void attach(Observer<InfoType, StateType> *o);
	void notifyObservers();
	virtual InfoType getInfo() const = 0;
	StateType getState() const;
};
```
