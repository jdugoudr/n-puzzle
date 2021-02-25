from PySide6 import QtCore, QtWidgets, QtGui

#class LeftBar(QtWidgets.QPlainTextEdit):
class LeftBar(QtWidgets.QTextEdit):
    #def __init__(self, size, heuristic, moves, timeC, sizeC):
    def __init__(self, values):
        super().__init__()
        titles = ("Size", "Heuristic", "Number of move", "Time complexity", "Size complexity")

        cursor = QtGui.QTextCursor(self.textCursor())
        for i, el in enumerate(values):
            form = QtGui.QTextCharFormat()
            form.setFontWeight(QtGui.QFont.Bold)
            formDefault = QtGui.QTextCharFormat()
            cursor.insertText(titles[i] + " :", form)
            cursor.insertText(" \t{}\n".format(el), formDefault)

#        self.value = "<strong>Size :</strong>             {sz}x{sz}<br>"
#        self.value += "<strong>Heuristic :</strong>       {hrtc}<br>"
#        self.value += "<strong>Numbe of move :</strong>   {mv}<br>"
#        self.value += "<strong>Time complexity :</strong> {tc}<br>"
#        self.value += "<strong>Size complexity :</strong> {sc}"

#        self.value = self.value.format(sz=size, hrtc=heuristic, mv=moves, tc=timeC, sc=sizeC)
        #self.setPlainText(self.value)
#        self.setHtml(self.value)
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

        self.__creatFont()

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

    def __creatFont(self):
        self.font = QtGui.QFont()
        self.font.setBold(True)
        self.font.setPointSize(18)
        self.textBrush = QtGui.QBrush(QtGui.QColor(0,0,0))

        if self.sizeEl >= 80:
            self.backBrush = QtGui.QBrush(QtGui.QColor(250,250,200))
        else:
            self.backBrush = QtGui.QBrush()

    def __populate(self, numbers):
        for i in range(0, self.size):
            for j in range(0, self.size):
                value = self.numbers[i*self.size+j]
                if value == "0":
                    item = QtWidgets.QTableWidgetItem("")
                else:
                    item = QtWidgets.QTableWidgetItem(value)

                item.setFont(self.font)
                item.setForeground(self.textBrush)
                item.setBackground(self.backBrush)
                item.setTextAlignment(QtCore.Qt.AlignHCenter | QtCore.Qt.AlignVCenter)

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
