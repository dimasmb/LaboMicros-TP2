# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Stations(object):
    def setupUi(self, Stations):
        Stations.setObjectName("Stations")
        Stations.resize(1000, 700)
        Stations.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.centralwidget = QtWidgets.QWidget(Stations)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.frame_principal = QtWidgets.QFrame(self.centralwidget)
        self.frame_principal.setMinimumSize(QtCore.QSize(1000, 700))
        self.frame_principal.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.frame_principal.setStyleSheet("background-color: rgb(7, 7, 141);")
        self.frame_principal.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_principal.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_principal.setObjectName("frame_principal")
        self.gridLayout = QtWidgets.QGridLayout(self.frame_principal)
        self.gridLayout.setObjectName("gridLayout")
        self.frame_graficos_13 = QtWidgets.QFrame(self.frame_principal)
        self.frame_graficos_13.setStyleSheet("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(204, 204, 204);\n"
"border-radius:10px;")
        self.frame_graficos_13.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_graficos_13.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_graficos_13.setObjectName("frame_graficos_13")
        self.verticalLayout_39 = QtWidgets.QVBoxLayout(self.frame_graficos_13)
        self.verticalLayout_39.setObjectName("verticalLayout_39")
        self.frame_grafs_14 = QtWidgets.QFrame(self.frame_graficos_13)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_grafs_14.sizePolicy().hasHeightForWidth())
        self.frame_grafs_14.setSizePolicy(sizePolicy)
        self.frame_grafs_14.setMinimumSize(QtCore.QSize(0, 0))
        self.frame_grafs_14.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.frame_grafs_14.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.frame_grafs_14.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_grafs_14.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_grafs_14.setObjectName("frame_grafs_14")
        self.horizontalLayout_40 = QtWidgets.QHBoxLayout(self.frame_grafs_14)
        self.horizontalLayout_40.setObjectName("horizontalLayout_40")
        self.frame_typefilter_15 = QtWidgets.QFrame(self.frame_grafs_14)
        self.frame_typefilter_15.setStyleSheet("background-color: rgb(144, 144, 144);")
        self.frame_typefilter_15.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_typefilter_15.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_typefilter_15.setObjectName("frame_typefilter_15")
        self.verticalLayout_40 = QtWidgets.QVBoxLayout(self.frame_typefilter_15)
        self.verticalLayout_40.setObjectName("verticalLayout_40")
        self.Title_estacion0_10 = QtWidgets.QLabel(self.frame_typefilter_15)
        font = QtGui.QFont()
        font.setPointSize(20)
        self.Title_estacion0_10.setFont(font)
        self.Title_estacion0_10.setAlignment(QtCore.Qt.AlignCenter)
        self.Title_estacion0_10.setObjectName("Title_estacion0_10")
        self.verticalLayout_40.addWidget(self.Title_estacion0_10)
        self.Imagen_estacion4 = QtWidgets.QVBoxLayout()
        self.Imagen_estacion4.setObjectName("Imagen_estacion4")
        self.verticalLayout_40.addLayout(self.Imagen_estacion4)
        self.verticalLayout_41 = QtWidgets.QVBoxLayout()
        self.verticalLayout_41.setObjectName("verticalLayout_41")
        self.horizontalLayout_41 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_41.setObjectName("horizontalLayout_41")
        self.label_28 = QtWidgets.QLabel(self.frame_typefilter_15)
        self.label_28.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_28.setObjectName("label_28")
        self.horizontalLayout_41.addWidget(self.label_28)
        self.rolido4_val = QtWidgets.QLabel(self.frame_typefilter_15)
        self.rolido4_val.setText("")
        self.rolido4_val.setObjectName("rolido4_val")
        self.horizontalLayout_41.addWidget(self.rolido4_val)
        self.verticalLayout_41.addLayout(self.horizontalLayout_41)
        self.horizontalLayout_42 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_42.setObjectName("horizontalLayout_42")
        self.label_29 = QtWidgets.QLabel(self.frame_typefilter_15)
        self.label_29.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_29.setObjectName("label_29")
        self.horizontalLayout_42.addWidget(self.label_29)
        self.cabeceo4_val = QtWidgets.QLabel(self.frame_typefilter_15)
        self.cabeceo4_val.setText("")
        self.cabeceo4_val.setObjectName("cabeceo4_val")
        self.horizontalLayout_42.addWidget(self.cabeceo4_val)
        self.verticalLayout_41.addLayout(self.horizontalLayout_42)
        self.horizontalLayout_43 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_43.setObjectName("horizontalLayout_43")
        self.label_30 = QtWidgets.QLabel(self.frame_typefilter_15)
        self.label_30.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_30.setObjectName("label_30")
        self.horizontalLayout_43.addWidget(self.label_30)
        self.orient4_val = QtWidgets.QLabel(self.frame_typefilter_15)
        self.orient4_val.setText("")
        self.orient4_val.setObjectName("orient4_val")
        self.horizontalLayout_43.addWidget(self.orient4_val)
        self.verticalLayout_41.addLayout(self.horizontalLayout_43)
        self.verticalLayout_40.addLayout(self.verticalLayout_41)
        self.horizontalLayout_40.addWidget(self.frame_typefilter_15)
        self.verticalLayout_39.addWidget(self.frame_grafs_14)
        self.gridLayout.addWidget(self.frame_graficos_13, 1, 1, 1, 1)
        self.frame_graficos_2 = QtWidgets.QFrame(self.frame_principal)
        self.frame_graficos_2.setStyleSheet("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(204, 204, 204);\n"
"border-radius:10px;")
        self.frame_graficos_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_graficos_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_graficos_2.setObjectName("frame_graficos_2")
        self.verticalLayout_8 = QtWidgets.QVBoxLayout(self.frame_graficos_2)
        self.verticalLayout_8.setObjectName("verticalLayout_8")
        self.frame_grafs_2 = QtWidgets.QFrame(self.frame_graficos_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_grafs_2.sizePolicy().hasHeightForWidth())
        self.frame_grafs_2.setSizePolicy(sizePolicy)
        self.frame_grafs_2.setMinimumSize(QtCore.QSize(0, 0))
        self.frame_grafs_2.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.frame_grafs_2.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.frame_grafs_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_grafs_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_grafs_2.setObjectName("frame_grafs_2")
        self.horizontalLayout_7 = QtWidgets.QHBoxLayout(self.frame_grafs_2)
        self.horizontalLayout_7.setObjectName("horizontalLayout_7")
        self.frame_typefilter_3 = QtWidgets.QFrame(self.frame_grafs_2)
        self.frame_typefilter_3.setStyleSheet("background-color: rgb(144, 144, 144);")
        self.frame_typefilter_3.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_typefilter_3.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_typefilter_3.setObjectName("frame_typefilter_3")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(self.frame_typefilter_3)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.Title_estacion0 = QtWidgets.QLabel(self.frame_typefilter_3)
        font = QtGui.QFont()
        font.setPointSize(20)
        self.Title_estacion0.setFont(font)
        self.Title_estacion0.setAlignment(QtCore.Qt.AlignCenter)
        self.Title_estacion0.setObjectName("Title_estacion0")
        self.verticalLayout_5.addWidget(self.Title_estacion0)
        self.Imagen_estacion0 = QtWidgets.QVBoxLayout()
        self.Imagen_estacion0.setObjectName("Imagen_estacion0")
        self.verticalLayout_5.addLayout(self.Imagen_estacion0)
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(self.frame_typefilter_3)
        self.label.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.rolido0_val = QtWidgets.QLabel(self.frame_typefilter_3)
        self.rolido0_val.setText("")
        self.rolido0_val.setObjectName("rolido0_val")
        self.horizontalLayout.addWidget(self.rolido0_val)
        self.verticalLayout_3.addLayout(self.horizontalLayout)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.label_3 = QtWidgets.QLabel(self.frame_typefilter_3)
        self.label_3.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_3.addWidget(self.label_3)
        self.cabeceo0_val = QtWidgets.QLabel(self.frame_typefilter_3)
        self.cabeceo0_val.setText("")
        self.cabeceo0_val.setObjectName("cabeceo0_val")
        self.horizontalLayout_3.addWidget(self.cabeceo0_val)
        self.verticalLayout_3.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label_5 = QtWidgets.QLabel(self.frame_typefilter_3)
        self.label_5.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_5.setObjectName("label_5")
        self.horizontalLayout_4.addWidget(self.label_5)
        self.orient0_val = QtWidgets.QLabel(self.frame_typefilter_3)
        self.orient0_val.setText("")
        self.orient0_val.setObjectName("orient0_val")
        self.horizontalLayout_4.addWidget(self.orient0_val)
        self.verticalLayout_3.addLayout(self.horizontalLayout_4)
        self.verticalLayout_5.addLayout(self.verticalLayout_3)
        self.horizontalLayout_7.addWidget(self.frame_typefilter_3)
        self.verticalLayout_8.addWidget(self.frame_grafs_2)
        self.gridLayout.addWidget(self.frame_graficos_2, 0, 0, 1, 1)
        self.frame_graficos_6 = QtWidgets.QFrame(self.frame_principal)
        self.frame_graficos_6.setStyleSheet("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(204, 204, 204);\n"
"border-radius:10px;")
        self.frame_graficos_6.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_graficos_6.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_graficos_6.setObjectName("frame_graficos_6")
        self.verticalLayout_10 = QtWidgets.QVBoxLayout(self.frame_graficos_6)
        self.verticalLayout_10.setObjectName("verticalLayout_10")
        self.frame_grafs_4 = QtWidgets.QFrame(self.frame_graficos_6)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_grafs_4.sizePolicy().hasHeightForWidth())
        self.frame_grafs_4.setSizePolicy(sizePolicy)
        self.frame_grafs_4.setMinimumSize(QtCore.QSize(0, 0))
        self.frame_grafs_4.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.frame_grafs_4.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.frame_grafs_4.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_grafs_4.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_grafs_4.setObjectName("frame_grafs_4")
        self.horizontalLayout_9 = QtWidgets.QHBoxLayout(self.frame_grafs_4)
        self.horizontalLayout_9.setObjectName("horizontalLayout_9")
        self.frame_typefilter_5 = QtWidgets.QFrame(self.frame_grafs_4)
        self.frame_typefilter_5.setStyleSheet("background-color: rgb(144, 144, 144);")
        self.frame_typefilter_5.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_typefilter_5.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_typefilter_5.setObjectName("frame_typefilter_5")
        self.verticalLayout_11 = QtWidgets.QVBoxLayout(self.frame_typefilter_5)
        self.verticalLayout_11.setObjectName("verticalLayout_11")
        self.Title_estacion0_2 = QtWidgets.QLabel(self.frame_typefilter_5)
        font = QtGui.QFont()
        font.setPointSize(20)
        self.Title_estacion0_2.setFont(font)
        self.Title_estacion0_2.setAlignment(QtCore.Qt.AlignCenter)
        self.Title_estacion0_2.setObjectName("Title_estacion0_2")
        self.verticalLayout_11.addWidget(self.Title_estacion0_2)
        self.Imagen_estacion1 = QtWidgets.QVBoxLayout()
        self.Imagen_estacion1.setObjectName("Imagen_estacion1")
        self.verticalLayout_11.addLayout(self.Imagen_estacion1)
        self.verticalLayout_14 = QtWidgets.QVBoxLayout()
        self.verticalLayout_14.setObjectName("verticalLayout_14")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label_2 = QtWidgets.QLabel(self.frame_typefilter_5)
        self.label_2.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_2.addWidget(self.label_2)
        self.rolido1_val = QtWidgets.QLabel(self.frame_typefilter_5)
        self.rolido1_val.setText("")
        self.rolido1_val.setObjectName("rolido1_val")
        self.horizontalLayout_2.addWidget(self.rolido1_val)
        self.verticalLayout_14.addLayout(self.horizontalLayout_2)
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.label_4 = QtWidgets.QLabel(self.frame_typefilter_5)
        self.label_4.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_5.addWidget(self.label_4)
        self.cabeceo1_val = QtWidgets.QLabel(self.frame_typefilter_5)
        self.cabeceo1_val.setText("")
        self.cabeceo1_val.setObjectName("cabeceo1_val")
        self.horizontalLayout_5.addWidget(self.cabeceo1_val)
        self.verticalLayout_14.addLayout(self.horizontalLayout_5)
        self.horizontalLayout_10 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_10.setObjectName("horizontalLayout_10")
        self.label_6 = QtWidgets.QLabel(self.frame_typefilter_5)
        self.label_6.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_6.setObjectName("label_6")
        self.horizontalLayout_10.addWidget(self.label_6)
        self.orient1_val = QtWidgets.QLabel(self.frame_typefilter_5)
        self.orient1_val.setText("")
        self.orient1_val.setObjectName("orient1_val")
        self.horizontalLayout_10.addWidget(self.orient1_val)
        self.verticalLayout_14.addLayout(self.horizontalLayout_10)
        self.verticalLayout_11.addLayout(self.verticalLayout_14)
        self.horizontalLayout_9.addWidget(self.frame_typefilter_5)
        self.verticalLayout_10.addWidget(self.frame_grafs_4)
        self.gridLayout.addWidget(self.frame_graficos_6, 0, 1, 1, 1)
        self.frame_graficos_7 = QtWidgets.QFrame(self.frame_principal)
        self.frame_graficos_7.setStyleSheet("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(204, 204, 204);\n"
"border-radius:10px;")
        self.frame_graficos_7.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_graficos_7.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_graficos_7.setObjectName("frame_graficos_7")
        self.verticalLayout_32 = QtWidgets.QVBoxLayout(self.frame_graficos_7)
        self.verticalLayout_32.setObjectName("verticalLayout_32")
        self.frame_grafs_12 = QtWidgets.QFrame(self.frame_graficos_7)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_grafs_12.sizePolicy().hasHeightForWidth())
        self.frame_grafs_12.setSizePolicy(sizePolicy)
        self.frame_grafs_12.setMinimumSize(QtCore.QSize(0, 0))
        self.frame_grafs_12.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.frame_grafs_12.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.frame_grafs_12.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_grafs_12.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_grafs_12.setObjectName("frame_grafs_12")
        self.horizontalLayout_29 = QtWidgets.QHBoxLayout(self.frame_grafs_12)
        self.horizontalLayout_29.setObjectName("horizontalLayout_29")
        self.frame_typefilter_13 = QtWidgets.QFrame(self.frame_grafs_12)
        self.frame_typefilter_13.setStyleSheet("background-color: rgb(144, 144, 144);")
        self.frame_typefilter_13.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_typefilter_13.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_typefilter_13.setObjectName("frame_typefilter_13")
        self.verticalLayout_33 = QtWidgets.QVBoxLayout(self.frame_typefilter_13)
        self.verticalLayout_33.setObjectName("verticalLayout_33")
        self.Title_estacion0_7 = QtWidgets.QLabel(self.frame_typefilter_13)
        font = QtGui.QFont()
        font.setPointSize(20)
        self.Title_estacion0_7.setFont(font)
        self.Title_estacion0_7.setAlignment(QtCore.Qt.AlignCenter)
        self.Title_estacion0_7.setObjectName("Title_estacion0_7")
        self.verticalLayout_33.addWidget(self.Title_estacion0_7)
        self.Imagen_estacion2 = QtWidgets.QVBoxLayout()
        self.Imagen_estacion2.setObjectName("Imagen_estacion2")
        self.verticalLayout_33.addLayout(self.Imagen_estacion2)
        self.verticalLayout_34 = QtWidgets.QVBoxLayout()
        self.verticalLayout_34.setObjectName("verticalLayout_34")
        self.horizontalLayout_30 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_30.setObjectName("horizontalLayout_30")
        self.label_19 = QtWidgets.QLabel(self.frame_typefilter_13)
        self.label_19.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_19.setObjectName("label_19")
        self.horizontalLayout_30.addWidget(self.label_19)
        self.rolido2_val = QtWidgets.QLabel(self.frame_typefilter_13)
        self.rolido2_val.setText("")
        self.rolido2_val.setObjectName("rolido2_val")
        self.horizontalLayout_30.addWidget(self.rolido2_val)
        self.verticalLayout_34.addLayout(self.horizontalLayout_30)
        self.horizontalLayout_31 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_31.setObjectName("horizontalLayout_31")
        self.label_20 = QtWidgets.QLabel(self.frame_typefilter_13)
        self.label_20.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_20.setObjectName("label_20")
        self.horizontalLayout_31.addWidget(self.label_20)
        self.cabeceo2_val = QtWidgets.QLabel(self.frame_typefilter_13)
        self.cabeceo2_val.setText("")
        self.cabeceo2_val.setObjectName("cabeceo2_val")
        self.horizontalLayout_31.addWidget(self.cabeceo2_val)
        self.verticalLayout_34.addLayout(self.horizontalLayout_31)
        self.horizontalLayout_32 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_32.setObjectName("horizontalLayout_32")
        self.label_21 = QtWidgets.QLabel(self.frame_typefilter_13)
        self.label_21.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_21.setObjectName("label_21")
        self.horizontalLayout_32.addWidget(self.label_21)
        self.orient2_val = QtWidgets.QLabel(self.frame_typefilter_13)
        self.orient2_val.setText("")
        self.orient2_val.setObjectName("orient2_val")
        self.horizontalLayout_32.addWidget(self.orient2_val)
        self.verticalLayout_34.addLayout(self.horizontalLayout_32)
        self.verticalLayout_33.addLayout(self.verticalLayout_34)
        self.horizontalLayout_29.addWidget(self.frame_typefilter_13)
        self.verticalLayout_32.addWidget(self.frame_grafs_12)
        self.gridLayout.addWidget(self.frame_graficos_7, 0, 2, 1, 1)
        self.frame_graficos_12 = QtWidgets.QFrame(self.frame_principal)
        self.frame_graficos_12.setStyleSheet("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(204, 204, 204);\n"
"border-radius:10px;")
        self.frame_graficos_12.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_graficos_12.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_graficos_12.setObjectName("frame_graficos_12")
        self.verticalLayout_36 = QtWidgets.QVBoxLayout(self.frame_graficos_12)
        self.verticalLayout_36.setObjectName("verticalLayout_36")
        self.frame_grafs_13 = QtWidgets.QFrame(self.frame_graficos_12)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_grafs_13.sizePolicy().hasHeightForWidth())
        self.frame_grafs_13.setSizePolicy(sizePolicy)
        self.frame_grafs_13.setMinimumSize(QtCore.QSize(0, 0))
        self.frame_grafs_13.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.frame_grafs_13.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.frame_grafs_13.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_grafs_13.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_grafs_13.setObjectName("frame_grafs_13")
        self.horizontalLayout_36 = QtWidgets.QHBoxLayout(self.frame_grafs_13)
        self.horizontalLayout_36.setObjectName("horizontalLayout_36")
        self.frame_typefilter_14 = QtWidgets.QFrame(self.frame_grafs_13)
        self.frame_typefilter_14.setStyleSheet("background-color: rgb(144, 144, 144);")
        self.frame_typefilter_14.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_typefilter_14.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_typefilter_14.setObjectName("frame_typefilter_14")
        self.verticalLayout_37 = QtWidgets.QVBoxLayout(self.frame_typefilter_14)
        self.verticalLayout_37.setObjectName("verticalLayout_37")
        self.Title_estacion0_9 = QtWidgets.QLabel(self.frame_typefilter_14)
        font = QtGui.QFont()
        font.setPointSize(20)
        self.Title_estacion0_9.setFont(font)
        self.Title_estacion0_9.setAlignment(QtCore.Qt.AlignCenter)
        self.Title_estacion0_9.setObjectName("Title_estacion0_9")
        self.verticalLayout_37.addWidget(self.Title_estacion0_9)
        self.Imagen_estacion3 = QtWidgets.QVBoxLayout()
        self.Imagen_estacion3.setObjectName("Imagen_estacion3")
        self.verticalLayout_37.addLayout(self.Imagen_estacion3)
        self.verticalLayout_38 = QtWidgets.QVBoxLayout()
        self.verticalLayout_38.setObjectName("verticalLayout_38")
        self.horizontalLayout_37 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_37.setObjectName("horizontalLayout_37")
        self.label_25 = QtWidgets.QLabel(self.frame_typefilter_14)
        self.label_25.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_25.setObjectName("label_25")
        self.horizontalLayout_37.addWidget(self.label_25)
        self.rolido3_val = QtWidgets.QLabel(self.frame_typefilter_14)
        self.rolido3_val.setText("")
        self.rolido3_val.setObjectName("rolido3_val")
        self.horizontalLayout_37.addWidget(self.rolido3_val)
        self.verticalLayout_38.addLayout(self.horizontalLayout_37)
        self.horizontalLayout_38 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_38.setObjectName("horizontalLayout_38")
        self.label_26 = QtWidgets.QLabel(self.frame_typefilter_14)
        self.label_26.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_26.setObjectName("label_26")
        self.horizontalLayout_38.addWidget(self.label_26)
        self.cabeceo3_val = QtWidgets.QLabel(self.frame_typefilter_14)
        self.cabeceo3_val.setText("")
        self.cabeceo3_val.setObjectName("cabeceo3_val")
        self.horizontalLayout_38.addWidget(self.cabeceo3_val)
        self.verticalLayout_38.addLayout(self.horizontalLayout_38)
        self.horizontalLayout_39 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_39.setObjectName("horizontalLayout_39")
        self.label_27 = QtWidgets.QLabel(self.frame_typefilter_14)
        self.label_27.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_27.setObjectName("label_27")
        self.horizontalLayout_39.addWidget(self.label_27)
        self.orient3_val = QtWidgets.QLabel(self.frame_typefilter_14)
        self.orient3_val.setText("")
        self.orient3_val.setObjectName("orient3_val")
        self.horizontalLayout_39.addWidget(self.orient3_val)
        self.verticalLayout_38.addLayout(self.horizontalLayout_39)
        self.verticalLayout_37.addLayout(self.verticalLayout_38)
        self.horizontalLayout_36.addWidget(self.frame_typefilter_14)
        self.verticalLayout_36.addWidget(self.frame_grafs_13)
        self.gridLayout.addWidget(self.frame_graficos_12, 1, 0, 1, 1)
        self.frame_graficos_16 = QtWidgets.QFrame(self.frame_principal)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_graficos_16.sizePolicy().hasHeightForWidth())
        self.frame_graficos_16.setSizePolicy(sizePolicy)
        self.frame_graficos_16.setStyleSheet("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(204, 204, 204);\n"
"border-radius:10px;")
        self.frame_graficos_16.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_graficos_16.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_graficos_16.setObjectName("frame_graficos_16")
        self.verticalLayout_24 = QtWidgets.QVBoxLayout(self.frame_graficos_16)
        self.verticalLayout_24.setObjectName("verticalLayout_24")
        self.frame_grafs_18 = QtWidgets.QFrame(self.frame_graficos_16)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_grafs_18.sizePolicy().hasHeightForWidth())
        self.frame_grafs_18.setSizePolicy(sizePolicy)
        self.frame_grafs_18.setMinimumSize(QtCore.QSize(0, 0))
        self.frame_grafs_18.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.frame_grafs_18.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.frame_grafs_18.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_grafs_18.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_grafs_18.setObjectName("frame_grafs_18")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.frame_grafs_18)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.Title_tipofiltro_24 = QtWidgets.QLabel(self.frame_grafs_18)
        font = QtGui.QFont()
        font.setPointSize(20)
        self.Title_tipofiltro_24.setFont(font)
        self.Title_tipofiltro_24.setAlignment(QtCore.Qt.AlignCenter)
        self.Title_tipofiltro_24.setObjectName("Title_tipofiltro_24")
        self.verticalLayout_2.addWidget(self.Title_tipofiltro_24)
        self.Error_label = QtWidgets.QLabel(self.frame_grafs_18)
        self.Error_label.setStyleSheet("color: rgb(255, 0, 0);")
        self.Error_label.setText("")
        self.Error_label.setAlignment(QtCore.Qt.AlignCenter)
        self.Error_label.setObjectName("Error_label")
        self.verticalLayout_2.addWidget(self.Error_label)
        self.horizontalLayout_44 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_44.setObjectName("horizontalLayout_44")
        self.comboBox = QtWidgets.QComboBox(self.frame_grafs_18)
        self.comboBox.setMaximumSize(QtCore.QSize(250, 16777215))
        self.comboBox.setStyleSheet("QComboBox{\n"
"background-color: rgb(220, 220, 220);\n"
"}")
        self.comboBox.setObjectName("comboBox")
        self.horizontalLayout_44.addWidget(self.comboBox)
        self.Btn_buscar = QtWidgets.QPushButton(self.frame_grafs_18)
        self.Btn_buscar.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.Btn_buscar.setMouseTracking(False)
        self.Btn_buscar.setFocusPolicy(QtCore.Qt.StrongFocus)
        self.Btn_buscar.setWhatsThis("")
        self.Btn_buscar.setAutoFillBackground(False)
        self.Btn_buscar.setStyleSheet("QPushButton{\n"
"    background-color: rgb(132, 132, 132);\n"
"    border-radius: 5px;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-color: black;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    \n"
"    background-color: rgb(0, 85, 255);\n"
"}\n"
"")
        self.Btn_buscar.setCheckable(False)
        self.Btn_buscar.setObjectName("Btn_buscar")
        self.horizontalLayout_44.addWidget(self.Btn_buscar)
        self.verticalLayout_2.addLayout(self.horizontalLayout_44)
        self.Btn_Abrir = QtWidgets.QPushButton(self.frame_grafs_18)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Btn_Abrir.sizePolicy().hasHeightForWidth())
        self.Btn_Abrir.setSizePolicy(sizePolicy)
        self.Btn_Abrir.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.Btn_Abrir.setMouseTracking(False)
        self.Btn_Abrir.setFocusPolicy(QtCore.Qt.StrongFocus)
        self.Btn_Abrir.setWhatsThis("")
        self.Btn_Abrir.setAutoFillBackground(False)
        self.Btn_Abrir.setStyleSheet("QPushButton{\n"
"    background-color: rgb(132, 132, 132);\n"
"    border-radius: 5px;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-color: black;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    \n"
"    background-color: rgb(0, 85, 255);\n"
"}\n"
"")
        self.Btn_Abrir.setCheckable(False)
        self.Btn_Abrir.setObjectName("Btn_Abrir")
        self.verticalLayout_2.addWidget(self.Btn_Abrir)
        self.Btn_Cerrar = QtWidgets.QPushButton(self.frame_grafs_18)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Btn_Cerrar.sizePolicy().hasHeightForWidth())
        self.Btn_Cerrar.setSizePolicy(sizePolicy)
        self.Btn_Cerrar.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.Btn_Cerrar.setMouseTracking(False)
        self.Btn_Cerrar.setFocusPolicy(QtCore.Qt.StrongFocus)
        self.Btn_Cerrar.setWhatsThis("")
        self.Btn_Cerrar.setAutoFillBackground(False)
        self.Btn_Cerrar.setStyleSheet("QPushButton{\n"
"    background-color: rgb(132, 132, 132);\n"
"    border-radius: 5px;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-color: black;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    \n"
"    background-color: rgb(0, 85, 255);\n"
"}\n"
"")
        self.Btn_Cerrar.setCheckable(False)
        self.Btn_Cerrar.setObjectName("Btn_Cerrar")
        self.verticalLayout_2.addWidget(self.Btn_Cerrar)
        self.label_7 = QtWidgets.QLabel(self.frame_grafs_18)
        font = QtGui.QFont()
        font.setPointSize(10)
        self.label_7.setFont(font)
        self.label_7.setAlignment(QtCore.Qt.AlignCenter)
        self.label_7.setObjectName("label_7")
        self.verticalLayout_2.addWidget(self.label_7)
        self.verticalLayout_24.addWidget(self.frame_grafs_18)
        self.gridLayout.addWidget(self.frame_graficos_16, 1, 2, 1, 1)
        self.verticalLayout.addWidget(self.frame_principal)
        Stations.setCentralWidget(self.centralwidget)

        self.retranslateUi(Stations)
        QtCore.QMetaObject.connectSlotsByName(Stations)

    def retranslateUi(self, Stations):
        _translate = QtCore.QCoreApplication.translate
        Stations.setWindowTitle(_translate("Stations", "Estaciones"))
        self.Title_estacion0_10.setText(_translate("Stations", "ESTACIÓN 4"))
        self.label_28.setText(_translate("Stations", "ROLIDO:"))
        self.label_29.setText(_translate("Stations", "CABECEO:"))
        self.label_30.setText(_translate("Stations", "ORIENTACIÓN:"))
        self.Title_estacion0.setText(_translate("Stations", "ESTACIÓN 0"))
        self.label.setText(_translate("Stations", "ROLIDO:"))
        self.label_3.setText(_translate("Stations", "CABECEO:"))
        self.label_5.setText(_translate("Stations", "ORIENTACIÓN:"))
        self.Title_estacion0_2.setText(_translate("Stations", "ESTACIÓN 1"))
        self.label_2.setText(_translate("Stations", "ROLIDO:"))
        self.label_4.setText(_translate("Stations", "CABECEO:"))
        self.label_6.setText(_translate("Stations", "ORIENTACIÓN:"))
        self.Title_estacion0_7.setText(_translate("Stations", "ESTACIÓN 2"))
        self.label_19.setText(_translate("Stations", "ROLIDO:"))
        self.label_20.setText(_translate("Stations", "CABECEO:"))
        self.label_21.setText(_translate("Stations", "ORIENTACIÓN:"))
        self.Title_estacion0_9.setText(_translate("Stations", "ESTACIÓN 3"))
        self.label_25.setText(_translate("Stations", "ROLIDO:"))
        self.label_26.setText(_translate("Stations", "CABECEO:"))
        self.label_27.setText(_translate("Stations", "ORIENTACIÓN:"))
        self.Title_tipofiltro_24.setText(_translate("Stations", "TP2 - Estaciones"))
        self.Btn_buscar.setText(_translate("Stations", "Buscar"))
        self.Btn_Abrir.setText(_translate("Stations", "Abrir puerto seleccionado"))
        self.Btn_Cerrar.setText(_translate("Stations", "Cerrar puerto actual"))
        self.label_7.setText(_translate("Stations", "\n"
"Autores:\n"
"Batinic Rey, Joaquín\n"
"Bosch, Dimas\n"
"Cardozo, Juan Francisco\n"
"Irigoyen, Enrique"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Stations = QtWidgets.QMainWindow()
    ui = Ui_Stations()
    ui.setupUi(Stations)
    Stations.show()
    sys.exit(app.exec_())
