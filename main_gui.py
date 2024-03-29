import sys
import re
import math
import random
from PySide6 import QtCore, QtWidgets, QtGui
from my_widgets import LeftBar, InteractionBar, MyTable, RightBar


class MyWidget(QtWidgets.QWidget):
    def __init__(self, size):
        super().__init__()

        self.layout = QtWidgets.QGridLayout(self)
        self.layout.setColumnMinimumWidth(1, 80*size)
        self.layout.setRowMinimumHeight(1, 80*size)
        self.layout.setColumnStretch(1, 1)
        self.layout.setRowStretch(1, 1)

        self.setWindowTitle("N-Puzzle")

    def setInteractionBar(self, interact):
        self.interact = interact
        self.layout.addLayout(self.interact,3,0,1,4)

    def setMap(self, mapZone):
        self.map = mapZone
        self.layout.addWidget(self.map, 1,1,2,2)
        #self.layout.addLayout(self.map, 1,1,1,1)
    
    def setUpBar(self, upBar):
        self.upBar = upBar
        self.layout.addWidget(self.upBar,0,0,1,4)

    def setLeftBar(self, leftBar):
        self.leftBar = leftBar
        self.layout.addWidget(self.leftBar, 1,0,2,1)

    def setRightBar(self, rightBar):
        self.rightBar = rightBar
        self.layout.addWidget(self.rightBar, 1,3,2,1)

def fillListMove(size, textListMove):
    _listMove = []
    for el in textListMove:
        _listMove.append(MyTable(size, 50, el))
    return _listMove

def parseLines(rawText):
    nb_move = 0
    nodeList = []

    timeC = re.findall('.*complexity in time.* ([0-9]*)', rawText)
    sizeC = re.findall('.*complexity in size.* ([0-9]*)', rawText)

    node = re.compile(r'\( ((?:[0-9]+ ?)*) \)', re.M)
    nb = re.compile(r'Number of moves : ([0-9]*)')

    tmp = node.findall(rawText)

    heuristic = ["default"]

    if not tmp:
        nodeList = [["1", "2", "3", "8", "4", "","7", "6", "5"],
            ["1", "2", "3", "8","", "4", "7", "6", "5"]]
        nb_move = 1
        timeC = [2]
        sizeC = [2]
    else:
        heuristic = re.findall("^Heuristic : (.*)$", rawText, re.M)
        nb_move = int(nb.search(rawText).group(1))
        for el in tmp:
            nodeList.append(el.split(' '))

    return nodeList, int(math.sqrt(len(nodeList[0]))), nb_move, timeC[0], sizeC[0], heuristic[0]


if __name__ == "__main__":
    text = ""
    for line in sys.stdin:
        print(line, end='')
        text += line


    app = QtWidgets.QApplication([])


    counter = 0
    timer = QtCore.QTimer()
    timer.setInterval(800)


    nodes, size, nb_move, timeC, sizeC, heuri = parseLines(text)

    _maps = fillListMove(size, nodes)

    # Creation of the MainWindow
    widget = MyWidget(size)


    # Creation of MainWindow contents
    _map = MyTable(size, 80, _maps[0].numbers)
    _map.setBackgroundRole(QtGui.QPalette.WindowText)

    _leftBar = LeftBar((size, heuri, nb_move, timeC, sizeC))

    interactionBar = InteractionBar()

    textLayout = QtWidgets.QPlainTextEdit(text)
    textLayout.setReadOnly(True)

    _rightBar = RightBar(size)
    _rightBar.setCurrentRow(0)
    for el in _maps:
        _rightBar.fillRightBar(el)
    _rightBar.setMinimumWidth(widget.sizeHint().width())

    @QtCore.Slot()
    def playShuffle():
        global timer
        global counter
        if interactionBar.play.text() == "Play":
            interactionBar.play.setText("Pause")
            if counter >= nb_move:
                counter = 0
                _map.copy(_maps[counter].numbers)
            timer.start()
        else:
            timer.stop()
            interactionBar.play.setText("Play")
    
    @QtCore.Slot()
    def nextPress():
        global counter
        if counter < nb_move:
            counter += 1
            _rightBar.setCurrentRow(counter)
            _map.copy(_maps[counter].numbers)
        else:
            global timer
            timer.stop()
            interactionBar.play.setText("Play")
    
    @QtCore.Slot()
    def prevPress():
        global counter
        if counter > 0:
            counter -= 1
            _rightBar.setCurrentRow(counter)
            _map.copy(_maps[counter].numbers)

    @QtCore.Slot()
    def itemClicked(row):
        global counter
        counter = row
        _map.copy(_maps[counter].numbers)


    # Connect all signals and slots
    timer.timeout.connect(nextPress)

    interactionBar.play.clicked.connect(playShuffle)
    interactionBar.prev.clicked.connect(prevPress)
    interactionBar.next.clicked.connect(nextPress)
    
    _rightBar.currentRowChanged.connect(itemClicked)

    # Fill the MainWindow with proper content
    widget.setRightBar(_rightBar)

    widget.setUpBar(textLayout)

    widget.setInteractionBar(interactionBar)


    widget.setMap(_map)
    
    widget.setLeftBar(_leftBar)

    # Launch the app
    widget.show()

    sys.exit(app.exec_())
