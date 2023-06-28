SudokuGame
==========
C++ was used to make this application. Qt framework was used to make GUI.

### [Documentation for code](https://stanleystanmarsh.github.io/SudokuGame/)

Sudoku puzzle game with numbers was created in the course of the work. The backend of application is described in [app/grid](https://github.com/StanleyStanMarsh/SudokuGame/tree/main/app/grid) directory. The frontend is described in [app/windows](https://github.com/StanleyStanMarsh/SudokuGame/tree/main/app/windows) directory.

The application consists of [main menu](https://github.com/StanleyStanMarsh/SudokuGame/blob/main/app/windows/widget.h) and [game window](https://github.com/StanleyStanMarsh/SudokuGame/blob/main/app/windows/gamewindow.h).

____
## Backend

To set the "grid" and interact with it, a Grid class has been created with two fields matrix and solving - solved and unsolved matrices, respectively. To create matrices, the QVector class from the Qt framework is used.
	
In the constructor of the Grid class, the matrix field is formed by setting the "base" matrix according to the previously described algorithm. Legal transformations are transposition - the `transpose()` method, the exchange of two rows within the same area - the `swapRows()` method and the exchange of two columns within the same area - the `swapColumns()` method. Using the `mix()` method, the elements of the matrix are "mixed": one of the three matrix transformation methods is randomly called 18 times. Thus, a high speed of operation and sufficient randomness of the "grid" is achieved.
	
Using the `resetToZero()` method, an unsolved matrix is formed: the matrix is copied to solving and elements of the "grid" are randomly selected, which are then "deleted", that is, these elements take a zero value. The number of selected cells depends on the selected difficulty level, which is passed as a parameter to the method. Thus, 51, 31 or 21 filled cells may remain.
____
## Frontend

### Main menu

The main menu is created using the `MainMenu` class, which is inherited from `QWidget`. It has a fixed size of 500 by 500 pixels. The background is a .png image located in the `background_label` object of the `QLabel` type using the predefined `setPixmap()` method. In the main menu there are 3 buttons of the `QPushButton` type (`start_button`, `about_button`, `quit_button`) grouped using the main_box object of the `QGroupBox` type. The style of the buttons is set using the predefined `setStyleSheet()` method, the `kButtonStyle` string of the QString type is passed to it as a parameter. The `main_box` box style is set by the same method using a cboxstyle string of type `QString`. `kButton` Style and `kBoxStyle` are constant members of the `MainMenu` class.

* The "Start game" (`start_button`) button opens the game window using the `QObject::connect binding(start_button, SIGNAL(clicked()), this, SLOT(gameWindowOpen()))`, where `gameWindowOpen()` is a slot that implements switching to the game window.

* Button "More about the game" (`about_button`) opens an additional window on top of the main one, using the binding `QObject::connect(`about_button`, SIGNAL(clicked()), this, SLOT(aboutWindowOpen()))`, where `aboutWindowOpen()` is a slot that implements the creation of an additional window `about_window`. The additional window is an object of the `AboutWindow` class. This class inherits from the `QDialog`. `about_window` class contains the name of the game and the name of the developer, while it is open, there is no way to interact with the main window.

* The "Exit" button closes the main window and thereby terminates the program using `QObject::connect(quit\_button, SIGNAL(clicked()), this, SLOT(close()))`, where `close()` is a predefined slot.

### Game window

The game window is described by the `GameWindow` class, which inherits from `QWidget`. The window has a fixed size of 680 by 710 pixels. In the game window there are 4 buttons of the `QPushButton` type (`return_button`, `generate_button`, `check_button`, `solve_button`), a button with a pop-up list of the `QComboBox` type (`diff_box`), "grid" - a two-dimensional vector of the `QVector` type of fields for entering the `QLineEdit` type (`grid`), as well as a field type Area. The `Area` class is inherited from `QLabel` and the `paintEvent()` event is redefined in it. In the `paintEvent()` method, a `QPainter` type object is created and using the `drawLine()` method, lines are drawn - the boundaries of the regions-sections on the Sudoku grid. The styles of all objects located in the widget of the game window are set by the `setStyleSheet()` method and constant strings `kButtonStyle` and `kBoxStyle` of the `QString` type.

* The "Return" button (`return_button`) returns the user to the main menu using `QObject::connect(return\_button, SIGNAL(clicked()), this, SLOT(returnButtonClicked()))`, where `returnButtonClicked()` is the slot that closes the game window and opens the main menu window.

* The Generate (`generate_button`) button fills the `grid` with numbers using the `QObject::connect binding(generate_button, SIGNAL(clicked()), this, SLOT(generateGrid()))`.
When calling the `generateGrid()` slot, the current difficulty level is taken from the `diff_box` list, the constructor of the `Grid` class is called, that is, the `Grid::matrix` matrix is filled with numbers, and then the `resetToZero()` method of the `Grid` class is called, the value of the difficulty level is passed to its parameters. Then the "grid" of the game window is filled in accordance with the values of the `Grid::solving` matrix, partially filled with zeros. Zeros are not output at the same time, and instead of them there are empty editable text input fields that differ in color. Filled cells are not editable.

* The button with a pop-up list (`diff_box`) allows you to choose one of three difficulty levels: easy, medium, hard.

* Button "Check" (`check_button`) checks the user-filled cells "grids" using the binding `QObject::connect(check\_button, SIGNAL(clicked()), this, SLOT(checkSol()))`.
When calling the `checkSol()` slot, the values of the `grid`, which are editable, are compared step by step with the corresponding values of the `Grid::matrix` matrix. If an incorrect value is written in a particular cell, then the field acquires a red outline. If all the values match, an additional window of the `AboutWindow` type opens with a notification of the correct decision.

* The button "Solve" (`solve_button`) outputs a correctly solved Sudoku using the binding `QObject::connect(resolve_button, SIGNAL(clicked()), this, SLOT(solveGenerated()))`.
When the `solveGenerated()` slot is called, the values of the Grid::matrix matrix are assigned to the values of the `grid` element by element. In this case, all fields become non-editable.

Also, the `closeEvent()` event has been redefined in the `GameWindow` class. When the game window is closed, this event is called, which opens the main menu window.
 	
`Additional` methods `setQLEStyle()`, `setQLEStyleEditable()`, `setQLEStyleMistake()`, `setButtonStyle()` and `CellEdit()` are needed to change the appearance of buttons and text fields.
