#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QByteArray>
#include <qcgaugewidget.h>
#include <QVector>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:


    void readSerial();
    void updateValues(QString name, QString valor_1, QString valor_2 ="", QString valor_3 ="", QString valor_4 ="", QString valor_5 ="", QString valor_6 ="", QString valor_7 ="", QString valor_8 ="", QString valor_9 ="", QString valor_10 ="", QString valor_11 ="", QString valor_12 ="", QString valor_13 ="", QString valor_14 ="", QString valor_15 ="", QString valor_16 ="", QString valor_17 ="", QString valor_18 ="", QString valor_19 ="", QString valor_20 ="");

    void makeplot();
    void maximavelocidad(double velocidad);

    void calcularvelocidad(double rpm1, double rpm2);

    QString barTempStyle(double value);
    QString barTempStyle1(double value);
    QString barVoltStyle(double value);
    QString barSoCStyle(double value);

    void SetupProgressbars();
    void SetupSpeedometer();
    void SetupPlots();
    void SetupArduino();
    void GetProductVendorID();

    void ActualizarPotenciaKelly(double volt1, double volt2, double volt3, double amp1, double amp2, double amp3, double volt4, double volt5, double volt6, double amp4, double amp5, double amp6);
    void ActualizarPotenciaBMS(double volt, double amp);
    void ActualizarPotenciaMPPT(double volt1, double amp1, double volt2, double amp2, double volt3, double amp3);

private:
    Ui::Dialog *ui;

    // Variables del Serial
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 1027;      // Arduino:9025 |Xbee:1027 | Arduino(?): 2341
    static const quint16 arduino_uno_product_id = 24577;       // Arduino:67   |Xbee:24577| Arduino(?): 0043 66 MEGA
    QByteArray serialData;
    QStringList buffer_split;
    QString serialBuffer;
    QString parsed_data_1;
    QString parsed_data_2;
    QString parsed_data_3;
    QString parsed_data_4;
    QString parsed_data_5;
    QString parsed_data_6;
    QString parsed_data_7;
    QString parsed_data_8;
    QString parsed_data_9;
    QString parsed_data_10;
    QString parsed_data_11;
    QString parsed_data_12;
    QString parsed_data_13;
    QString parsed_data_14;
    QString parsed_data_15;
    QString parsed_data_16;
    QString parsed_data_17;
    QString parsed_data_18;
    QString parsed_data_19;
    QString parsed_data_20;
    QString parsed_data_21;

    //Arrays Volt/Temp con 30 y 60 valores
    double bms_temp[60];
    double bms_volt[30];

    //Variables globales
    double RPM1;
    double RPM2;
    double speed;           //Velocidad
    double carga_restante;  //Pack Soc

    //TEMPERATURAS//
    double Pack_temp;
    double KellyD_temp;
    double KellyI_temp;
    double MPPT1_temp;
    double MPPT2_temp;
    double MPPT3_temp;

    //POTENCIA//
    double pack_true_volt;  //Pack Volt BMS
    double pack_true_amp;   //Pack Current BMS
    double potencia_total_bms;

    double voltaje_fase1_d; //Voltaje/Amperaje fases Kelly Derecho
    double voltaje_fase2_d;
    double voltaje_fase3_d;
    double amperaje_fase1_d;
    double amperaje_fase2_d;
    double amperaje_fase3_d;
    double voltaje_fase1_i; //Voltaje/Amperaje fases Kelly Izquierdo
    double voltaje_fase2_i;
    double voltaje_fase3_i;
    double amperaje_fase1_i;
    double amperaje_fase2_i;
    double amperaje_fase3_i;
    double potencia_fase1_d;//Potencia de fases inversores Kelly Der/Iz
    double potencia_fase2_d;
    double potencia_fase3_d;
    double potencia_fase1_i;
    double potencia_fase2_i;
    double potencia_fase3_i;
    double potencia_total_kelly_d;
    double potencia_total_kelly_i;
    double potencia_total_kellys;

    double voltaje_mppt1;   //Voltaje/Amperajes MPPTS ENTRADA
    double amperaje_mppt1;
    double voltaje_mppt2;
    double amperaje_mppt2;
    double voltaje_mppt3;
    double amperaje_mppt3;

    double potencia_mppt1;  //Potencia calculada
    double potencia_mppt2;
    double potencia_mppt3;
    double potencia_total_mppts;
    double voltaje_out_mppt1;       //Voltajes SALIDA
    double voltaje_out_mppt2;
    double voltaje_out_mppt3;

    double amperaje1=50;       //MPPT
    double voltaje1=40;
    double amperaje2=60;
    double voltaje2;

    //Variables para guardar Max Velocidad
    double maxvel;
    double maxvelaux;

    //Variables de Odómetro
    QcGaugeWidget * mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;

    //Estilo variable SOC
    QString safe_1_soc    = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #93d600,stop: 0.4999 #68d600,stop: 0.5 #68d600,stop: 1 #29D600 );border-top-left-radius: 3px ;border-top-right-radius: 3px;border-bottom-right-radius: 3px ;border-bottom-left-radius: 3px; border: 0px solid black;}QProgressBar{border: 0px;background: white; padding: 1px; text-align: center;border-top-left-radius: 3px ;border-top-right-radius: 3px;border-bottom-right-radius: 3px ;border-bottom-left-radius: 3px;font: 75 10pt;}";
    QString safe_2_soc   = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #f0ff00,stop: 0.4999 #ecee00,stop: 0.5 #ecee00,stop: 1 #93d600 );border-top-left-radius: 3px ;border-top-right-radius: 3px;border-bottom-right-radius: 3px ;border-bottom-left-radius: 3px; border: 0px solid black;}QProgressBar{border: 0px;background: white; padding: 1px; text-align: center;border-top-left-radius: 3px ;border-top-right-radius: 3px;border-bottom-right-radius: 3px ;border-bottom-left-radius: 3px;font: 75 10pt;}";
    QString danger_1_soc  = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #ff8100,stop: 0.4999 #ffb400,stop: 0.5 #ffb400,stop: 1 #f0ff00 );border-top-left-radius: 3px ;border-top-right-radius: 3px;border-bottom-right-radius: 3px ;border-bottom-left-radius: 3px; border: 0px solid black;}QProgressBar{border: 0px;background: white; padding: 1px; text-align: center;border-top-left-radius: 3px ;border-top-right-radius: 3px;border-bottom-right-radius: 3px ;border-bottom-left-radius: 3px;font: 75 10pt;}";
    QString danger_2_soc = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #ff0000,stop: 0.4999 #ff4000,stop: 0.5 #ff4000,stop: 1 #ff8100 );border-top-left-radius: 3px ;border-top-right-radius: 3px;border-bottom-right-radius: 3px ;border-bottom-left-radius: 3px; border: 0px solid black;}QProgressBar{border: 0px;background: white; padding: 1px; text-align: center;border-top-left-radius: 3px ;border-top-right-radius: 3px;border-bottom-right-radius: 3px ;border-bottom-left-radius: 3px;font: 75 10pt;}";

    //Estilo variable temperatura izquierda
    QString fondo_verde_i     = "background-color: #26D000;text-align: center;border-radius: 8px; color: #FFFFFF; font-weight: bold;font-size: 15px;border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";
    QString fondo_amarillo_i  = "background-color: #FDEB00;text-align: center;border-radius: 8px; color: #FFFFFF; font-weight: bold;font-size: 15px;border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";
    QString fondo_naranjo_i   = "background-color: #F1B400;text-align: center;border-radius: 8px; color: #FFFFFF; font-weight: bold;font-size: 15px;border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";
    QString fondo_narojo_i    = "background-color: #DE6013;text-align: center;border-radius: 8px; color: #FFFFFF; font-weight: bold;font-size: 15px;border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";
    QString fondo_rojo_i      = "background-color: #E9292E;text-align: center;border-radius: 8px; color: #FFFFFF; font-weight: bold;font-size: 15px;border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";

    //Estilo variable temperatura derecha
    QString fondo_verde_d     = "background-color: #26D000;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 8px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";
    QString fondo_amarillo_d  = "background-color: #FDEB00;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 8px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";
    QString fondo_naranjo_d   = "background-color: #F1B400;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 8px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";
    QString fondo_narojo_d    = "background-color: #DE6013;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 8px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";
    QString fondo_rojo_d      = "background-color: #E9292E;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 8px;border-bottom-right-radius: 0px ;border-bottom-left-radius: 0px; border: 0px solid black;";

    //Estilo variable voltaje (abajo)
    QString fondo_verde_v     = "background-color: #26D000;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 8px ;border-bottom-left-radius: 8px; border: 0px solid black;";
    QString fondo_amarillo_v  = "background-color: #FDEB00;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 8px ;border-bottom-left-radius: 8px; border: 0px solid black;";
    QString fondo_naranjo_v   = "background-color: #F1B400;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 8px ;border-bottom-left-radius: 8px; border: 0px solid black;";
    QString fondo_narojo_v    = "background-color: #DE6013;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 8px ;border-bottom-left-radius: 8px; border: 0px solid black;";
    QString fondo_rojo_v      = "background-color: #E9292E;text-align: center; border-radius: 5px; color: #FFFFFF; font-weight: bold;font-size: 15px; border-top-left-radius: 0px ;border-top-right-radius: 0px;border-bottom-right-radius: 8px ;border-bottom-left-radius: 8px; border: 0px solid black;";

};

#endif // DIALOG_H
