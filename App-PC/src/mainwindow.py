# PyQt5 modules
from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtCore import QTimer

# Project modules
from src.ui.mainwindow import Ui_Stations

# Utilities
from matplotlib.backends.backend_qt5agg import (FigureCanvas, NavigationToolbar2QT as NavigationToolbar)
from matplotlib.figure import Figure
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from src.drv_serial import search_ports
import serial
from serial.tools import list_ports
import numpy as np


class Stations(QMainWindow, Ui_Stations):

    def __init__(self):
        super(Stations, self).__init__()
        self.setupUi(self)
        self.ser = None
        self.serial_opened = False
        self.cont=0

        # inicializo los valores
        self.rolidos = [self.rolido0_val, self.rolido1_val, self.rolido2_val, self.rolido3_val, self.rolido4_val]
        self.cabeceos = [self.cabeceo0_val, self.cabeceo1_val, self.cabeceo2_val, self.cabeceo3_val, self.cabeceo4_val]
        self.orientaciones = [self.orient0_val, self.orient1_val, self.orient2_val, self.orient3_val, self.orient4_val]

        for i in range(len(self.rolidos)):
            self.rolidos[i].setText('0º')
            self.cabeceos[i].setText('0º')
            self.orientaciones[i].setText('0º')

        # inicializo los graficos
        self.init_grafs()

        #self.com_ports = search_ports()

        self.Btn_buscar.clicked.connect(self.look4ports)
        self.Btn_Abrir.clicked.connect(self.open_port)
        self.Btn_Cerrar.clicked.connect(self.close_port)

        self.look4ports()

        # inicializo timer
        self.refresh_timer = QTimer()
        self.refresh_timer.timeout.connect(self.refreshGrafik)

        self.start_refresher()

    def open_port(self):
        if self.comboBox.count() >= 1:
            comx = self.comboBox.currentText()
            comx = comx.split()
            try:
                self.ser = serial.Serial(comx[0], timeout=0)
                self.serial_opened = True
                self.Error_label.setText('Puerto {} abierto'.format(comx[0]))
                self.Error_label.setStyleSheet('color: black')
            except serial.SerialException:
                self.Error_label.setText('No se pudo abrir el puerto')
                self.Error_label.setStyleSheet('color: red')
        else:
            self.Error_label.setText('No hay puertos para abrir')
            self.Error_label.setStyleSheet('color: red')

    def close_port(self):
        if self.serial_opened:
            self.ser.close()
            self.Error_label.setText('Puerto cerrado')
            self.Error_label.setStyleSheet('color: black')
            self.serial_opened = False
        else:
            self.Error_label.setText('No hay un puerto abierto')
            self.Error_label.setStyleSheet('color: red')

    def look4ports(self):
        self.Error_label.setText('Buscando puertos COM abiertos...')
        self.Error_label.setStyleSheet('color: black')
        com_ports = search_ports()
        self.comboBox.clear()
        if com_ports:
            for port, desc, hwid in sorted(com_ports):
                self.comboBox.addItem("{} : {} [{}]".format(port, desc, hwid))
            self.Error_label.setText('Busqueda terminada\nPuertos encontrados: {}'.format(self.comboBox.count()))
        else:
            self.Error_label.setText('No se encontró un puerto COM')
            self.Error_label.setStyleSheet('color: red')

    def start_refresher(self):
        self.refresh_timer.start(50)

    def init_grafs(self):
        self.x_init = np.array([-2, -2, 2, 2])
        self.y_init = np.array([-4, 4, 4, -4])
        self.z_init = np.array([0, 0, 0, 0])

        self.vert0_init = np.arctan(2)*(180/np.pi)
        self.vert1_init = 180 - self.vert0_init
        self.vert2_init = -self.vert1_init
        self.vert3_init = -self.vert0_init
        self.vert_init = [self.vert0_init, self.vert1_init, self.vert2_init, self.vert3_init, ]

        self.figure_station0 = Figure(figsize=(3, 3))
        self.canvas_station0 = FigureCanvas(self.figure_station0)
        self.Imagen_estacion0.addWidget(self.canvas_station0)
        self.ax_station0 = self.figure_station0.add_subplot(projection='3d')

        self.figure_station1 = Figure(figsize=(3, 3))
        self.canvas_station1 = FigureCanvas(self.figure_station1)
        self.Imagen_estacion1.addWidget(self.canvas_station1)
        self.ax_station1 = self.figure_station1.add_subplot(projection='3d')

        self.figure_station2 = Figure(figsize=(3, 3))
        self.canvas_station2 = FigureCanvas(self.figure_station2)
        self.Imagen_estacion2.addWidget(self.canvas_station2)
        self.ax_station2 = self.figure_station2.add_subplot(projection='3d')

        self.figure_station3 = Figure(figsize=(3, 3))
        self.canvas_station3 = FigureCanvas(self.figure_station3)
        self.Imagen_estacion3.addWidget(self.canvas_station3)
        self.ax_station3 = self.figure_station3.add_subplot(projection='3d')

        self.figure_station4 = Figure(figsize=(3, 3))
        self.canvas_station4 = FigureCanvas(self.figure_station4)
        self.Imagen_estacion4.addWidget(self.canvas_station4)
        self.ax_station4 = self.figure_station4.add_subplot(projection='3d')

        self.figures = [self.figure_station0, self.figure_station1, self.figure_station2, self.figure_station3, self.figure_station4]
        self.axes = [self.ax_station0, self.ax_station1, self.ax_station2, self.ax_station3, self.ax_station4]
        self.canvases = [self.canvas_station0, self.canvas_station1, self.canvas_station2, self.canvas_station3, self.canvas_station4]

        self.refreshGrafik()

    def get_info(self):
        if self.serial_opened:
            data = self.ser.read(20)
            dataStr = data.decode('Ascii')
            self.label.setText(dataStr)

    def refreshGrafik(self):
        self.get_info()
        """FOR DEBUG"""
        self.cont += 1
        # self.rolidos[0].setText(str(self.cont)+'º')
        # self.orientaciones[1].setText(str(self.cont)+'º')
        # self.cabeceos[2].setText(str(self.cont)+'º')
        """-----------------------------"""
        rolido_val = [int(i.text()[:-1]) for i in self.rolidos]
        cabeceo_val = [int(i.text()[:-1]) for i in self.cabeceos]
        orient_val = [int(i.text()[:-1]) for i in self.orientaciones]

        sin = np.sin(orient_val * ((np.pi / 180)*np.ones(5)))
        cos = np.cos(orient_val * ((np.pi / 180)*np.ones(5)))

        xx = self.x_init.reshape((4, 1)) * np.cos(rolido_val * ((np.pi / 180) * np.ones(len(rolido_val))))
        yy = self.y_init.reshape((4, 1)) * np.cos(cabeceo_val * ((np.pi / 180) * np.ones(len(cabeceo_val))))
        zz = self.x_init.reshape((4, 1)) * np.sin(rolido_val * ((np.pi / 180) * np.ones(len(rolido_val)))) \
             + self.y_init.reshape((4, 1)) * np.sin(cabeceo_val * ((np.pi / 180) * np.ones(len(rolido_val))))
        for i in range(len(self.axes)):

            vertices = [list(zip(xx[:, i], yy[:, i], zz[:, i]))]
            normal=np.cross([xx[0, i]-xx[1, i], yy[0, i]-yy[1, i], zz[0, i]-zz[1, i]],
                            [xx[2, i]-xx[1, i], yy[2, i]-yy[1, i], zz[2, i]-zz[1, i]])

            self.axes[i].cla()
            self.axes[i].quiver([0], [0], [7], [-sin[i]], [cos[i]], [0],
                                length=2, color='red', normalize=True) #Norte
            self.axes[i].quiver([0], [0], [7], [sin[i]], [-cos[i]], [0],
                                length=2, color='blue', normalize=True)  # Sur
            self.axes[i].quiver([0], [0], [7], [-cos[i]], [-sin[i]], [0],
                                length=2, color='green', normalize=True)  # Oeste
            self.axes[i].quiver([0], [0], [7], [cos[i]], [sin[i]], [0],
                                length=2, color='orange', normalize=True)  # Este
            self.axes[i].text(-sin[i]*2.5, cos[i]*2.5, 7, 'N')
            self.axes[i].text(sin[i]*2.5, -cos[i]*2.5, 7, 'S')
            self.axes[i].text(-cos[i]*2.5, -sin[i]*2.5, 7, 'O')
            self.axes[i].text(cos[i]*3.5, sin[i]*3.5, 7, 'E')

            self.axes[i].add_collection3d(Poly3DCollection(vertices))

            self.axes[i].quiver([xx[2, i], xx[1, i]], [yy[2, i], yy[1, i]], [zz[2, i], zz[1, i]],
                                [normal[0]], [normal[1]], [normal[2]],
                                length=1, color='red', normalize=True)  # Norte
            self.axes[i].set_xlim(-3, 3)
            self.axes[i].set_ylim(-3, 3)
            self.axes[i].set_zlim(-1.5, 4.5)

            self.axes[i].axis('off')

            self.figures[i].tight_layout()
            self.axes[i].view_init(30, 45+orient_val[i])
            self.canvases[i].draw()

    def closeEvent(self, event):
        self.close_port()
        event.accept()


