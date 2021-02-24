from PySide6 import QtCore, QtWidgets, QtGui

class LeftBar(QtWidgets.QPlainTextEdit):
    def __init__(self, size, heuristic, moves):
        super().__init__()
        self.value = "Size :\t\t{sz}x{sz}\t\nHeuristic :\t\t{hrtc}\nNumbe of move :\t{mv}\n"
        self.value = self.value.format(sz=size, hrtc=heuristic, mv=moves)
        self.setPlainText(self.value)
        self.setReadOnly(True)
        self.setMinimumWidth(135)


class InteractionBar(QtWidgets.QHBoxLayout):
    def __init__(self):
        super().__init__()
        self.play = QtWidgets.QPushButton("Play")
        self.next = QtWidgets.QPushButton("Next")
        self.prev = QtWidgets.QPushButton("Prev")
        self.addStretch()
        self.addWidget(self.prev)
        self.addWidget(self.play)
        self.addWidget(self.next)
        self.addStretch()

class RightBar(QtWidgets.QListWidget):
    def __init__(self, size):
        super().__init__()
        self.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)

    def fillRightBar(self, item):
        witem = QtWidgets.QListWidgetItem(self)
        witem.setSizeHint(QtCore.QSize(item.width(), item.height()))
        self.setItemWidget(witem, item)


class MyTable(QtWidgets.QWidget):
    def __init__(self, sizeMap, sizeEl, content, parent=None):
        super(MyTable, self).__init__(parent)
        self.size = sizeMap
        self.sizeEl = sizeEl
        self.numbers = content
        self.table = QtWidgets.QTableWidget(sizeMap,sizeMap)

        self.cells = []

        self.table.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.table.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)

        hheader = self.table.horizontalHeader()
        vheader = self.table.verticalHeader()
        hheader.hide()
        vheader.hide()

        hheader.setSectionResizeMode(QtWidgets.QHeaderView.Stretch)
        vheader.setSectionResizeMode(QtWidgets.QHeaderView.Stretch)

        self.table.setEnabled(False)

        self.__populate(self.numbers)

        layout = QtWidgets.QHBoxLayout()
        layout.addWidget(self.table)

        self.setLayout(layout)

        self.resize(sizeMap * sizeEl, sizeMap * sizeEl)

    def __populate(self, numbers):
        for i in range(0, self.size):
            for j in range(0, self.size):
                value = self.numbers[i*self.size+j]
                if value == "0":
                    item = QtWidgets.QTableWidgetItem("")
                else:
                    item = QtWidgets.QTableWidgetItem(value)
                self.table.setItem(i, j, item)

    def copy(self, other):
        self.numbers = other
        for i in range(0, self.size):
            for j in range(0, self.size):
                value = self.numbers[i*self.size+j]
                if value == "0":
                    self.table.item(i, j).setText("")
                else:
                    self.table.item(i, j).setText(value)
