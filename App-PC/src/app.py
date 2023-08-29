# PyQt5 modules
from PyQt5 import QtWidgets

# Python modules
import sys

# Main window ui import
from src.mainwindow import Stations


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = Stations()
    window.show()
    sys.exit(app.exec())
