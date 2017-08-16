#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QtGlobal>

//Display inicial, valores iniciales, detecta Arduino (no modificar), define parámetros Arduino//

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    qDebug() << "Iniciando interfaz" << endl;

    //ui->lcd_velocidad->display("----");
    //ui->lcd_torque->display("----");
    //ui->lcd_gap->display("----");
    //ui->lcd_max_voltaje->display("----");
    //ui->lcd_min_voltaje->display("----");
    //ui->lcd_max_speed->display("----");

    //Iniciar arrays con zeros
    memset(bms_temp, 0, sizeof(bms_temp));
    memset(bms_volt, 0, sizeof(bms_volt));

    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data_1 = "";

  Dialog::GetProductVendorID();
    //double v1 = 2.956;
    //for(int i = 0; i < 30; i++){ bms_volt[i] = v1; v1 += 0.123;}
//    bms_temp[0] = 50.5;
//    bms_temp[1] = 70.3;
//    bms_temp[2] = 10.9;
//    bms_temp[3] = 40.7;

    Dialog::SetupArduino();
    Dialog::SetupPlots();
    Dialog::SetupSpeedometer();
    Dialog::SetupProgressbars();

}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}
void Dialog::readSerial(){
    /*
     * readyRead() doesn't guarantee that the entire message will be received all at once.
     * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
     *
     */
    QStringList buffer_split = serialBuffer.split("\n"); //  split the serialBuffer string, parsing with '\n' as the separator
    //  Check to see if there less than 3 tokens in buffer_split.
    //  If there are at least 3 then this means there were 2 commas,
    //  means there is a parsed temperature value as the second token (between 2 commas)
    if(buffer_split.length() <2 ){
        // no parsed value yet so continue accumulating bytes from serial in the buffer.
        serialData = arduino->readAll();
        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
        serialData.clear();
    }else{
        // the second element of buffer_split is parsed correctly, update the temperature value on temp_lcdNumber
        serialBuffer = "";
        // remover ultimo elemento ("")
        buffer_split.removeLast();

        // actualizar datos usando Fx updateValues

        foreach (QString data, buffer_split) {
            qDebug() << data << endl;
            QStringList unDato = data.split(",");

            if (unDato.length()==2){        // ID + 1 Valor
            Dialog::updateValues(unDato[0],unDato[1]);
            }
            else if (unDato.length()==9){  // ID + 8 Valores
            Dialog::updateValues(unDato[0],unDato[1], unDato[2], unDato[3], unDato[4], unDato[5], unDato[6], unDato[7], unDato[8]);
            }
            else if (unDato.length()==14){  // ID + 13 Valores
            Dialog::updateValues(unDato[0],unDato[1], unDato[2], unDato[3], unDato[4], unDato[5], unDato[6], unDato[7], unDato[8], unDato[9], unDato[10], unDato[11], unDato[12], unDato[13]);
            }
            else if (unDato.length()==15){  // ID + 14 Valores
            Dialog::updateValues(unDato[0],unDato[1], unDato[2], unDato[3], unDato[4], unDato[5], unDato[6], unDato[7], unDato[8], unDato[9], unDato[10], unDato[11], unDato[12], unDato[13], unDato[14]);
            }
            else if (unDato.length()==16){  // ID + 15 Valores
            Dialog::updateValues(unDato[0],unDato[1], unDato[2], unDato[3], unDato[4], unDato[5], unDato[6], unDato[7], unDato[8], unDato[9], unDato[10], unDato[11], unDato[12], unDato[13], unDato[14], unDato[15]);
            }
            else if (unDato.length()==21){  // ID + 20 Valores
            Dialog::updateValues(unDato[0],unDato[1], unDato[2], unDato[3], unDato[4], unDato[5], unDato[6], unDato[7], unDato[8], unDato[9], unDato[10], unDato[11], unDato[12], unDato[13], unDato[14], unDato[15], unDato[16], unDato[17], unDato[18], unDato[19], unDato[20]);
            }
        }
    }

}
void Dialog::updateValues(QString name, QString numero_1, QString numero_2, QString numero_3, QString numero_4, QString numero_5, QString numero_6, QString numero_7, QString numero_8, QString numero_9, QString numero_10, QString numero_11, QString numero_12, QString numero_13, QString numero_14, QString numero_15, QString numero_16, QString numero_17, QString numero_18, QString numero_19, QString numero_20){
    double value_1;
    double value_2;
    double value_3;
    double value_4;
    double value_5;
    double value_6;
    double value_7;
    double value_8;
    double value_9;
    double value_10;
    double value_11;
    double value_12;
    double value_13;
    double value_14;
    double value_15;
    double value_16;
    double value_17;
    double value_18;
    double value_19;
    double value_20;

    try{
        value_1 = numero_1.toDouble();
        value_2 = numero_2.toDouble();
        value_3 = numero_3.toDouble();
        value_4 = numero_4.toDouble();
        value_5 = numero_5.toDouble();
        value_6 = numero_6.toDouble();
        value_7 = numero_7.toDouble();
        value_8 = numero_8.toDouble();
        value_9 = numero_9.toDouble();
        value_10 = numero_10.toDouble();
        value_11 = numero_11.toDouble();
        value_12 = numero_12.toDouble();
        value_13 = numero_13.toDouble();
        value_14 = numero_14.toDouble();
        value_15 = numero_15.toDouble();
        value_16 = numero_16.toDouble();
        value_17 = numero_17.toDouble();
        value_18 = numero_18.toDouble();
        value_19 = numero_19.toDouble();
        value_20 = numero_20.toDouble();

    }catch(...){
        value_1=1;
        value_2=1;
        value_3=1;
        value_4=1;
        value_5=1;
        value_6=1;
        value_7=1;
        value_8=1;
        value_9=1;
        value_10=1;
        value_11=1;
        value_12=1;
        value_13=1;
        value_14=1;
        value_15=1;
        value_16=1;
        value_17=1;
        value_18=1;
        value_19=1;
        value_20=1;
    }
        /*
        qDebug() << value_1;
        qDebug() << value_2;
        qDebug() << value_3;
        qDebug() << value_4;
        qDebug() << value_5;
        qDebug() << value_6;
        qDebug() << value_7;
        qDebug() << value_8;
        qDebug() << value_9;
        qDebug() << value_10;
        qDebug() << value_11;
        qDebug() << value_12;
        qDebug() << value_13;
        qDebug() << value_14;
        qDebug() << value_15;
        qDebug() << value_16;
        qDebug() << value_17;
        qDebug() << value_18;
        qDebug() << value_19;
        qDebug() << value_20;
        */
        parsed_data_1 = QString::number(value_1, 'g', 4); // format precision of temperature_value to 4 digits or fewer
        parsed_data_2 = QString::number(value_2, 'g', 4);
        parsed_data_3 = QString::number(value_3, 'g', 4);
        parsed_data_4 = QString::number(value_4, 'g', 4);
        parsed_data_5 = QString::number(value_5, 'g', 4);
        parsed_data_6 = QString::number(value_6, 'g', 4);
        parsed_data_7 = QString::number(value_7, 'g', 4);
        parsed_data_8 = QString::number(value_8, 'g', 4);
        parsed_data_9 = QString::number(value_9, 'g', 4);
        parsed_data_10 = QString::number(value_10, 'g', 4);
        parsed_data_11 = QString::number(value_11, 'g', 4);
        parsed_data_12 = QString::number(value_12, 'g', 4);
        parsed_data_13 = QString::number(value_13, 'g', 4);
        parsed_data_14 = QString::number(value_14, 'g', 4);
        parsed_data_15 = QString::number(value_15, 'g', 4);
        parsed_data_16 = QString::number(value_16, 'g', 4);
        parsed_data_17 = QString::number(value_17, 'g', 4);
        parsed_data_18 = QString::number(value_18, 'g', 4);
        parsed_data_19 = QString::number(value_19, 'g', 4);
        parsed_data_20 = QString::number(value_20, 'g', 4);


        if(name == "A"){
            carga_restante = value_1;                       // [0] = SOC

            pack_true_amp = value_2*1;
            parsed_data_2 = QString::number(pack_true_amp, 'g', 4);
            ui->lcd_packAmp->display(parsed_data_2);                // [1] = Pack Current

            pack_true_volt = value_3*1;
            parsed_data_3 = QString::number(pack_true_volt, 'g', 4);
            ui->lcd_packVolt->display(parsed_data_3);               // [2] = Pack Inst Volt

            double pack_open_volt = value_4*1;
            parsed_data_4 = QString::number(pack_open_volt, 'g', 4);
            ui->lcd_openVolt->display(parsed_data_4);               // [3] = Pack Open Volt

            double pack_abs_current = value_5*1;
            parsed_data_5 = QString::number(pack_abs_current, 'g', 4);
            ui->lcd_absCurrent->display(parsed_data_5);             // [4] = Pack Abs Current

            double maximum_pack_volt = value_6*0.01;
            parsed_data_6 = QString::number(maximum_pack_volt, 'g', 4);
            ui->lcd_maxPackVolt->display(parsed_data_6);            // [5] = Maximum Pack Volt

            double minimum_pack_volt = value_6*0.01;
            parsed_data_7 = QString::number(minimum_pack_volt, 'g', 4);
            ui->lcd_minPackVolt->display(parsed_data_7);            // [6] = Minimum Pack Volt

            ui->lcd_highTemp->display(parsed_data_8);               // [7] = High Temp
            ui->lcd_maxTermID->display(parsed_data_9);              // [8] = High Temp Thermistor ID
            ui->lcd_lowTemp->display(parsed_data_10);               // [9] = Low Temp
            ui->lcd_lowTermID->display(parsed_data_11);             // [10] = Low Temp Thermistor ID

            Pack_temp = value_12;
            ui->lcd_AvgTemp->display(parsed_data_12);               // [11] = Average Temp

            ui->lcd_internalTemperature->display(parsed_data_13);   // [12] = Internal Temp

            ui->lcd_maxPackVolt_id->display(parsed_data_14);        // [13] = Max Volt ID
            ui->lcd_minPackVolt_id->display(parsed_data_15);        // [14] = Min Volt ID

            Dialog::ActualizarPotenciaBMS(pack_true_volt, pack_true_amp);

        } else if (name == "T"){
            bms_temp[0] = value_1;        // [0] = ID | [2*i-1] = ID | [2*i] = Temp
            bms_temp[1] = value_2;
            bms_temp[2] = value_3;
            bms_temp[3] = value_4;
            bms_temp[4] = value_5;
            bms_temp[5] = value_6;
            bms_temp[6] = value_7;
            bms_temp[7] = value_8;
            bms_temp[8] = value_9;
            bms_temp[9] = value_10;
            bms_temp[10] = value_11;
            bms_temp[11] = value_12;
            bms_temp[12] = value_13;
            bms_temp[13] = value_14;
            bms_temp[14] = value_15;
            bms_temp[15] = value_16;
            bms_temp[16] = value_17;
            bms_temp[17] = value_18;
            bms_temp[18] = value_19;
            bms_temp[19] = value_20;

        } else if (name == "Y"){
            bms_temp[20] = value_1;        // [0] = ID | [2*i-1] = ID | [2*i] = Temp
            bms_temp[21] = value_2;
            bms_temp[22] = value_3;
            bms_temp[23] = value_4;
            bms_temp[24] = value_5;
            bms_temp[25] = value_6;
            bms_temp[26] = value_7;
            bms_temp[27] = value_8;
            bms_temp[28] = value_9;
            bms_temp[29] = value_10;
            bms_temp[30] = value_11;
            bms_temp[31] = value_12;
            bms_temp[32] = value_13;
            bms_temp[33] = value_14;
            bms_temp[34] = value_15;
            bms_temp[35] = value_16;
            bms_temp[36] = value_17;
            bms_temp[37] = value_18;
            bms_temp[38] = value_19;
            bms_temp[39] = value_20;

        } else if (name == "U"){
            bms_temp[40] = value_1;        // [0] = ID | [2*i-1] = ID | [2*i] = Temp
            bms_temp[41] = value_2;
            bms_temp[42] = value_3;
            bms_temp[43] = value_4;
            bms_temp[44] = value_5;
            bms_temp[45] = value_6;
            bms_temp[46] = value_7;
            bms_temp[47] = value_8;
            bms_temp[48] = value_9;
            bms_temp[49] = value_10;
            bms_temp[50] = value_11;
            bms_temp[51] = value_12;
            bms_temp[52] = value_13;
            bms_temp[53] = value_14;
            bms_temp[54] = value_15;
            bms_temp[55] = value_16;
            bms_temp[56] = value_17;
            bms_temp[57] = value_18;
            bms_temp[58] = value_19;
            bms_temp[59] = value_20;

        } else if (name == "V"){
            bms_volt[0] = value_1*0.0001; // [0] = ID | [2*i-1] = ID | [2*i] = Volt
            bms_volt[1] = value_2*0.0001;
            bms_volt[2] = value_3*0.0001;
            bms_volt[3] = value_4*0.0001;
            bms_volt[4] = value_5*0.0001;
            bms_volt[5] = value_6*0.0001;
            bms_volt[6] = value_7*0.0001;
            bms_volt[7] = value_8*0.0001;
            bms_volt[8] = value_9*0.0001;
            bms_volt[9] = value_10*0.0001;
            bms_volt[10] = value_11*0.0001;
            bms_volt[11] = value_12*0.0001;
            bms_volt[12] = value_13*0.0001;
            bms_volt[13] = value_14*0.0001;
            bms_volt[14] = value_15*0.0001;

        } else if (name == "B"){
            bms_volt[15] = value_1*0.0001; // [0] = ID | [2*i-1] = ID | [2*i] = Volt
            bms_volt[16] = value_2*0.0001;
            bms_volt[17] = value_3*0.0001;
            bms_volt[18] = value_4*0.0001;
            bms_volt[19] = value_5*0.0001;
            bms_volt[20] = value_6*0.0001;
            bms_volt[21] = value_7*0.0001;
            bms_volt[22] = value_8*0.0001;
            bms_volt[23] = value_9*0.0001;
            bms_volt[24] = value_10*0.0001;
            bms_volt[25] = value_11*0.0001;
            bms_volt[26] = value_12*0.0001;
            bms_volt[27] = value_13*0.0001;
            bms_volt[28] = value_14*0.0001;
            bms_volt[29] = value_15*0.0001;

        } else if (name == "a"){    //MOTOR 1
            amperaje_fase1_d = value_1*1;
            amperaje_fase2_d = value_2*1;
            amperaje_fase3_d = value_3*1;

            parsed_data_1 = QString::number(amperaje_fase1_d, 'g', 4);
            parsed_data_2 = QString::number(amperaje_fase2_d, 'g', 4);
            parsed_data_3 = QString::number(amperaje_fase3_d, 'g', 4);

            voltaje_fase1_d = value_4*1;
            voltaje_fase2_d = value_5*1;
            voltaje_fase3_d = value_6*1;

            parsed_data_4 = QString::number(voltaje_fase1_d, 'g', 4);
            parsed_data_5 = QString::number(voltaje_fase2_d, 'g', 4);
            parsed_data_6 = QString::number(voltaje_fase3_d, 'g', 4);

            ui->lcd_KellyD_IA->display(parsed_data_1);    // [0-2] Ia, Ib, Ic
            ui->lcd_KellyD_IB->display(parsed_data_2);
            ui->lcd_KellyD_IC->display(parsed_data_3);

            ui->lcd_KellyD_VA->display(parsed_data_4);  // [3-5] Va, Vb, Vc
            ui->lcd_KellyD_VB->display(parsed_data_5);
            ui->lcd_KellyD_VC->display(parsed_data_6);

            Dialog::ActualizarPotenciaKelly(voltaje_fase1_d, voltaje_fase2_d, voltaje_fase3_d, amperaje_fase1_d, amperaje_fase2_d, amperaje_fase3_d, voltaje_fase1_i, voltaje_fase2_i, voltaje_fase3_i, amperaje_fase1_i, amperaje_fase2_i, amperaje_fase3_i);

            //
            RPM1 = value_7;
            ui->lcd_rpm_i->display(parsed_data_7);       // [6] = RPM
            ui->lcd_errorcode1->display(parsed_data_8); // [7] = ERROR CODE
            Dialog::calcularvelocidad(RPM1,RPM2);
            //
            ui->lcd_motor_i_pwm->display(parsed_data_9);   // [8] = PWM
            ui->lcd_motor_i_emr->display(parsed_data_10);   // [9] = EMR

            KellyD_temp = value_11;
            ui->lcd_motor_i_temp->display(parsed_data_11);   // [10] = MOTOR TEMP

            ui->lcd_motor_i_kelly_temp->display(parsed_data_12);   // [11] = KELLY TEMP
            //
            ui->lcd_motor_d_throttle->display(parsed_data_13);   // [12] = Throttle Switch Status DERECHO
            //
            ui->lcd_motor_d_reverse->display(parsed_data_14);   // [13] = Reverse Switch Status DERECHO
            //
        } else if (name == "b"){    //MOTOR 2
            amperaje_fase1_i = value_1*1;
            amperaje_fase2_i = value_2*1;
            amperaje_fase3_i = value_3*1;

            parsed_data_1 = QString::number(amperaje_fase1_i, 'g', 4);
            parsed_data_2 = QString::number(amperaje_fase2_i, 'g', 4);
            parsed_data_3 = QString::number(amperaje_fase3_i, 'g', 4);

            voltaje_fase1_i = value_4*1;
            voltaje_fase2_i = value_5*1;
            voltaje_fase3_i = value_6*1;

            parsed_data_4 = QString::number(voltaje_fase1_i, 'g', 4);
            parsed_data_5 = QString::number(voltaje_fase2_i, 'g', 4);
            parsed_data_6 = QString::number(voltaje_fase3_i, 'g', 4);

            ui->lcd_KellyI_IA->display(parsed_data_1);    // [0-2] Ia, Ib, Ic
            ui->lcd_KellyI_IB->display(parsed_data_2);
            ui->lcd_KellyI_IC->display(parsed_data_3);

            ui->lcd_KellyI_VA->display(parsed_data_4);  // [3-5] Va, Vb, Vc
            ui->lcd_KellyI_VB->display(parsed_data_5);
            ui->lcd_KellyI_VC->display(parsed_data_6);

            Dialog::ActualizarPotenciaKelly(voltaje_fase1_d, voltaje_fase2_d, voltaje_fase3_d, amperaje_fase1_d, amperaje_fase2_d, amperaje_fase3_d, voltaje_fase1_i, voltaje_fase2_i, voltaje_fase3_i, amperaje_fase1_i, amperaje_fase2_i, amperaje_fase3_i);
            //
            RPM2 = value_7;
            ui->lcd_rpm_d->display(parsed_data_7);       // [6] = RPM
            ui->lcd_errorcode2->display(parsed_data_8); // [7] = ERROR CODE
            Dialog::calcularvelocidad(RPM1,RPM2);
            //
            ui->lcd_motor_d_pwm->display(parsed_data_9);   // [8] = PWM
            ui->lcd_motor_d_emr->display(parsed_data_10);   // [9] = EMR

            KellyI_temp = value_11;
            ui->lcd_motor_d_temp->display(parsed_data_11);   // [10] = MOTOR TEMP

            ui->lcd_motor_d_kelly_temp->display(parsed_data_12);   // [11] = KELLY TEMP
            //
            ui->lcd_motor_i_throttle->display(parsed_data_13);   // [12] = Throttle Switch Status IZQUIERDO
            //
            ui->lcd_motor_i_reverse->display(parsed_data_14);   // [13] = Reverse Switch Status IZQUIERDO

        } else if (name == "M"){    //MPPT1
            voltaje_mppt1 = value_1*0.01;
            parsed_data_1 = QString::number(voltaje_mppt1, 'g', 4);
            ui->lcd_mppt1_vin->display(parsed_data_1);    // [0] = Voltaje IN

            amperaje_mppt1 = value_2*0.01;
            parsed_data_2 = QString::number(amperaje_mppt1, 'g', 4);
            ui->lcd_mppt1_iin->display(parsed_data_2);    // [1] = Amperaje IN

            voltaje_out_mppt1 = value_3*0.01;
            parsed_data_3 = QString::number(voltaje_out_mppt1, 'g', 4);
            ui->lcd_mppt1_vout->display(parsed_data_3);   // [2] = Voltaje OUT

            ui->lcd_mppt1_bvlr->display(parsed_data_4);   // [3] = BVLR
            ui->lcd_mppt1_ovt->display(parsed_data_5);    // [4] = OVT
            ui->lcd_mppt1_noc->display(parsed_data_6);    // [5] = NOC
            ui->lcd_mppt1_undv->display(parsed_data_7);   // [6] = UNDV
            ui->lcd_mppt1_temp->display(parsed_data_8);   // [7] = TEMP

        } else if (name == "N"){    //MPPT2
            voltaje_mppt2 = value_1*0.01;
            parsed_data_1 = QString::number(voltaje_mppt2, 'g', 4);
            ui->lcd_mppt2_vin->display(parsed_data_1);    // [0] = Voltaje IN

            amperaje_mppt2 = value_2*0.01;
            parsed_data_2 = QString::number(amperaje_mppt2, 'g', 4);
            ui->lcd_mppt2_iin->display(parsed_data_2);    // [1] = Amperaje IN

            voltaje_out_mppt2 = value_3*0.01;
            parsed_data_3 = QString::number(voltaje_out_mppt2, 'g', 4);
            ui->lcd_mppt2_vout->display(parsed_data_3);   // [2] = Voltaje OUT

            ui->lcd_mppt2_bvlr->display(parsed_data_4);   // [3] = BVLR
            ui->lcd_mppt2_ovt->display(parsed_data_5);    // [4] = OVT
            ui->lcd_mppt2_noc->display(parsed_data_6);    // [5] = NOC
            ui->lcd_mppt2_undv->display(parsed_data_7);   // [6] = UNDV
            ui->lcd_mppt2_temp->display(parsed_data_8);   // [7] = TEMP

        } else if (name == "O"){    //MPPT3
            voltaje_mppt3 = value_1*0.01;
            parsed_data_1 = QString::number(voltaje_mppt3, 'g', 4);
            ui->lcd_mppt3_vin->display(parsed_data_1);    // [0] = Voltaje IN

            amperaje_mppt3 = value_2*0.01;
            parsed_data_2 = QString::number(amperaje_mppt3, 'g', 4);
            ui->lcd_mppt3_iin->display(parsed_data_2);    // [1] = Amperaje IN

            voltaje_out_mppt3 = value_3*0.01;
            parsed_data_3 = QString::number(voltaje_out_mppt3, 'g', 4);
            ui->lcd_mppt3_vout->display(parsed_data_3);   // [2] = Voltaje OUT

            ui->lcd_mppt3_bvlr->display(parsed_data_4);   // [3] = BVLR
            ui->lcd_mppt3_ovt->display(parsed_data_5);    // [4] = OVT
            ui->lcd_mppt3_noc->display(parsed_data_6);    // [5] = NOC
            ui->lcd_mppt3_undv->display(parsed_data_7);   // [6] = UNDV
            ui->lcd_mppt3_temp->display(parsed_data_8);   // [7] = TEMP

        } else {
            qDebug() << "SERIAL READ ERROR";

    }

    Dialog::makeplot();
    mSpeedNeedle->setCurrentValue(speed);
    Dialog::maximavelocidad(speed);
    maxvelaux = maxvel;
    Dialog::SetupProgressbars();

}
void Dialog::makeplot()
{
    // calculate two new data points:
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;

    if (key-lastPointKey > 0.01) // at most add point every 100 ms
    {
      double potencia_kellys = potencia_total_kellys;
      double potencia_mppts = potencia_total_mppts;
      double potencia_bms = potencia_total_bms;
      double velocidad_gr = speed;

      // add data to lines:
      ui->Plot1->graph(0)->addData(key, potencia_kellys);
      ui->Plot1->graph(1)->addData(key, potencia_bms);
      ui->Plot1->graph(2)->addData(key, potencia_mppts);
      ui->Plot1->graph(3)->addData(key, velocidad_gr);

      // set data of dots:
      ui->Plot1->graph(4)->clearData();
      ui->Plot1->graph(4)->addData(key, potencia_kellys);

      ui->Plot1->graph(5)->clearData();
      ui->Plot1->graph(5)->addData(key, potencia_bms);

      ui->Plot1->graph(6)->clearData();
      ui->Plot1->graph(6)->addData(key, potencia_mppts);

      ui->Plot1->graph(7)->clearData();
      ui->Plot1->graph(7)->addData(key, velocidad_gr);

      // remove data of lines that's outside visible range:
      ui->Plot1->graph(0)->removeDataBefore(key-100);
      ui->Plot1->graph(1)->removeDataBefore(key-100);
      ui->Plot1->graph(2)->removeDataBefore(key-100);
      ui->Plot1->graph(3)->removeDataBefore(key-100);

      // rescale value (vertical) axis to fit the current data:
      ui->Plot1->graph(0)->rescaleValueAxis(true);
      ui->Plot1->graph(1)->rescaleValueAxis(true);
      ui->Plot1->graph(2)->rescaleValueAxis(true);
      ui->Plot1->graph(3)->rescaleValueAxis(true);

      double temperatura_kelly_d = KellyD_temp;
      double temperatura_kelly_i = KellyI_temp;
      double temperatura_pack = Pack_temp;

      // add data to lines:
      ui->Plot2->graph(0)->addData(key, temperatura_kelly_d);
      ui->Plot2->graph(1)->addData(key, temperatura_kelly_i);
      ui->Plot2->graph(2)->addData(key, temperatura_pack);

      // set data of dots:
      ui->Plot2->graph(3)->clearData();
      ui->Plot2->graph(3)->addData(key, temperatura_kelly_d);

      ui->Plot2->graph(4)->clearData();
      ui->Plot2->graph(4)->addData(key, temperatura_kelly_i);

      ui->Plot2->graph(5)->clearData();
      ui->Plot2->graph(5)->addData(key, temperatura_pack);

      // remove data of lines that's outside visible range:
      ui->Plot2->graph(0)->removeDataBefore(key-100);
      ui->Plot2->graph(1)->removeDataBefore(key-100);
      ui->Plot2->graph(2)->removeDataBefore(key-100);

      // rescale value (vertical) axis to fit the current data:
      ui->Plot2->graph(0)->rescaleValueAxis(true);
      ui->Plot2->graph(1)->rescaleValueAxis(true);
      ui->Plot2->graph(2)->rescaleValueAxis(true);

      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->Plot1->xAxis->setRange(key+0.1, 100, Qt::AlignRight);
    ui->Plot1->yAxis->setRange(0,150);
    ui->Plot1->replot();

    ui->Plot2->xAxis->setRange(key+0.25, 100, Qt::AlignRight);
    ui->Plot2->yAxis->setRange(0,100);
    ui->Plot2->replot();

}
void Dialog::SetupPlots(){
//    ui->Plot1->graph(0)->setChannelFillGraph(ui->Plot1->graph(1));
//    ui->Plot1->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    //Grafico potencias
    ui->Plot1->addGraph();  // blue line
    ui->Plot1->graph(0)->setPen(QPen(Qt::blue));
    ui->Plot1->graph(0)->setAntialiasedFill(true);

    ui->Plot1->addGraph(); // red line
    ui->Plot1->graph(1)->setPen(QPen(Qt::red));
    ui->Plot1->graph(1)->setAntialiasedFill(true);


    ui->Plot1->addGraph(); // green line
    ui->Plot1->graph(2)->setPen(QPen(Qt::green));
    ui->Plot1->graph(2)->setAntialiasedFill(true);

    ui->Plot1->addGraph(); // black line
    ui->Plot1->graph(3)->setPen(QPen(Qt::black));
    ui->Plot1->graph(3)->setAntialiasedFill(true);

    ui->Plot1->addGraph(); // blue dot
    ui->Plot1->graph(4)->setPen(QPen(Qt::blue));
    ui->Plot1->graph(4)->setLineStyle(QCPGraph::lsNone);
    ui->Plot1->graph(4)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot1->addGraph(); // red dot
    ui->Plot1->graph(5)->setPen(QPen(Qt::red));
    ui->Plot1->graph(5)->setLineStyle(QCPGraph::lsNone);
    ui->Plot1->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot1->addGraph(); // green dot
    ui->Plot1->graph(6)->setPen(QPen(Qt::green));
    ui->Plot1->graph(6)->setLineStyle(QCPGraph::lsNone);
    ui->Plot1->graph(6)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot1->addGraph(); // black dot
    ui->Plot1->graph(7)->setPen(QPen(Qt::black));
    ui->Plot1->graph(7)->setLineStyle(QCPGraph::lsNone);
    ui->Plot1->graph(7)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot1->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->Plot1->xAxis->setDateTimeFormat("");
    ui->Plot1->xAxis->setAutoTickStep(false);
    ui->Plot1->xAxis->setTickStep(2);
    ui->Plot1->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Plot1->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot1->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Plot1->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot1->yAxis2, SLOT(setRange(QCPRange)));

    //Grafico temperaturas
    ui->Plot2->addGraph();  // blue line
    ui->Plot2->graph(0)->setPen(QPen(Qt::blue));
    ui->Plot2->graph(0)->setAntialiasedFill(true);

    ui->Plot2->addGraph(); // red line
    ui->Plot2->graph(1)->setPen(QPen(Qt::red));
    ui->Plot2->graph(1)->setAntialiasedFill(true);


    ui->Plot2->addGraph(); // green line
    ui->Plot2->graph(2)->setPen(QPen(Qt::green));
    ui->Plot2->graph(2)->setAntialiasedFill(true);

    ui->Plot2->addGraph(); // blue dot
    ui->Plot2->graph(3)->setPen(QPen(Qt::blue));
    ui->Plot2->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->Plot2->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot2->addGraph(); // red dot
    ui->Plot2->graph(4)->setPen(QPen(Qt::red));
    ui->Plot2->graph(4)->setLineStyle(QCPGraph::lsNone);
    ui->Plot2->graph(4)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot2->addGraph(); // green dot
    ui->Plot2->graph(5)->setPen(QPen(Qt::green));
    ui->Plot2->graph(5)->setLineStyle(QCPGraph::lsNone);
    ui->Plot2->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot2->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->Plot2->xAxis->setDateTimeFormat("");
    ui->Plot2->xAxis->setAutoTickStep(false);
    ui->Plot2->xAxis->setTickStep(2);
    ui->Plot2->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Plot2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Plot2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot2->yAxis2, SLOT(setRange(QCPRange)));

}
void Dialog::maximavelocidad(double velocidad){
    maxvel= qMax(maxvelaux,velocidad);

}
QString Dialog::barTempStyle(double value){
    if ((value >=10)&&(value <27)){
        return fondo_verde_i;
    }else if ((value >=27)&&(value <29.5)){
        return fondo_amarillo_i;
    }else if ((value >=29.5)&&(value <32)){
        return fondo_naranjo_i;
    }else if ((value >=32)&&(value <=34.5)){
        return fondo_narojo_i;
    }else if ((value >=37)&&(value <=39.5)){
        return fondo_rojo_i;
    }else{
    return fondo_verde_i;
    }
}
QString Dialog::barTempStyle1(double value){
    if ((value >=10)&&(value <27)){
        return fondo_verde_d;
    }else if ((value >=27)&&(value <29.5)){
        return fondo_amarillo_d;
    }else if ((value >=29.5)&&(value <32)){
        return fondo_naranjo_d;
    }else if ((value >=32)&&(value <=34.5)){
        return fondo_narojo_d;
    }else if ((value >=37)&&(value <=39.5)){
        return fondo_rojo_d;
    }else{
    return fondo_verde_d;
    }
}
QString Dialog::barVoltStyle(double value){
    if ((value <= 2.8) || (value >= 4.4)){
        return fondo_rojo_v;
    }else if ((value >2.8)&&(value <= 3.25)){
        return fondo_narojo_v;
    }else if ((value >3.2)&&(value <= 3.65)){
        return fondo_naranjo_v;
    }else if ((value >3.65)&&(value <= 4.05)){
        return fondo_amarillo_v;
    }else if ((value >4.05)&&(value < 4.4)){
        return fondo_verde_v;
    }else{
        return fondo_verde_v;
    }
}
QString Dialog::barSoCStyle(double value){
    if ((value >=0)&&(value <25)){
     return danger_2_soc;
    }else if ((value >=25)&&(value <50)){
     return danger_1_soc;
    }else if ((value >=50)&&(value <75)){
     return safe_2_soc;
    }else if((value >=75)&&(value <=100)){
     return safe_1_soc;
    }
    return safe_1_soc;
}
void Dialog::SetupProgressbars(){

//Asociar valores

    // Soc Bar
    ui->SoC_bar->setValue(carga_restante);      //Set Value por ser ProgressBar

    //Max Vel historica
    ui->lcd_max_speed->display(QString::number(maxvelaux, 'g', 4));

    //Temp Bar
    ui->temp_bar_01->setText(QString::number(bms_temp[0], 'g', 4));
    ui->temp_bar_02->setText(QString::number(bms_temp[1], 'g', 4));
    ui->temp_bar_03->setText(QString::number(bms_temp[2], 'g', 4));
    ui->temp_bar_04->setText(QString::number(bms_temp[3], 'g', 4));
    ui->temp_bar_05->setText(QString::number(bms_temp[4], 'g', 4));
    ui->temp_bar_06->setText(QString::number(bms_temp[5], 'g', 4));
    ui->temp_bar_07->setText(QString::number(bms_temp[6], 'g', 4));
    ui->temp_bar_08->setText(QString::number(bms_temp[7], 'g', 4));
    ui->temp_bar_09->setText(QString::number(bms_temp[8], 'g', 4));
    ui->temp_bar_10->setText(QString::number(bms_temp[9], 'g', 4));

    ui->temp_bar_11->setText(QString::number(bms_temp[10], 'g', 4));
    ui->temp_bar_12->setText(QString::number(bms_temp[11], 'g', 4));
    ui->temp_bar_13->setText(QString::number(bms_temp[12], 'g', 4));
    ui->temp_bar_14->setText(QString::number(bms_temp[13], 'g', 4));
    ui->temp_bar_15->setText(QString::number(bms_temp[14], 'g', 4));
    ui->temp_bar_16->setText(QString::number(bms_temp[15], 'g', 4));
    ui->temp_bar_17->setText(QString::number(bms_temp[16], 'g', 4));
    ui->temp_bar_18->setText(QString::number(bms_temp[17], 'g', 4));
    ui->temp_bar_19->setText(QString::number(bms_temp[18], 'g', 4));
    ui->temp_bar_20->setText(QString::number(bms_temp[19], 'g', 4));

    ui->temp_bar_21->setText(QString::number(bms_temp[20], 'g', 4));
    ui->temp_bar_22->setText(QString::number(bms_temp[21], 'g', 4));
    ui->temp_bar_23->setText(QString::number(bms_temp[22], 'g', 4));
    ui->temp_bar_24->setText(QString::number(bms_temp[23], 'g', 4));
    ui->temp_bar_25->setText(QString::number(bms_temp[24], 'g', 4));
    ui->temp_bar_26->setText(QString::number(bms_temp[25], 'g', 4));
    ui->temp_bar_27->setText(QString::number(bms_temp[26], 'g', 4));
    ui->temp_bar_28->setText(QString::number(bms_temp[27], 'g', 4));
    ui->temp_bar_29->setText(QString::number(bms_temp[28], 'g', 4));
    ui->temp_bar_30->setText(QString::number(bms_temp[29], 'g', 4));

    ui->temp_bar_31->setText(QString::number(bms_temp[30], 'g', 4));
    ui->temp_bar_32->setText(QString::number(bms_temp[31], 'g', 4));
    ui->temp_bar_33->setText(QString::number(bms_temp[32], 'g', 4));
    ui->temp_bar_34->setText(QString::number(bms_temp[33], 'g', 4));
    ui->temp_bar_35->setText(QString::number(bms_temp[34], 'g', 4));
    ui->temp_bar_36->setText(QString::number(bms_temp[35], 'g', 4));
    ui->temp_bar_37->setText(QString::number(bms_temp[36], 'g', 4));
    ui->temp_bar_38->setText(QString::number(bms_temp[37], 'g', 4));
    ui->temp_bar_39->setText(QString::number(bms_temp[38], 'g', 4));
    ui->temp_bar_40->setText(QString::number(bms_temp[39], 'g', 4));

    ui->temp_bar_41->setText(QString::number(bms_temp[40], 'g', 4));
    ui->temp_bar_42->setText(QString::number(bms_temp[41], 'g', 4));
    ui->temp_bar_43->setText(QString::number(bms_temp[42], 'g', 4));
    ui->temp_bar_44->setText(QString::number(bms_temp[43], 'g', 4));
    ui->temp_bar_45->setText(QString::number(bms_temp[44], 'g', 4));
    ui->temp_bar_46->setText(QString::number(bms_temp[45], 'g', 4));
    ui->temp_bar_47->setText(QString::number(bms_temp[46], 'g', 4));
    ui->temp_bar_48->setText(QString::number(bms_temp[47], 'g', 4));
    ui->temp_bar_49->setText(QString::number(bms_temp[48], 'g', 4));
    ui->temp_bar_50->setText(QString::number(bms_temp[49], 'g', 4));

    ui->temp_bar_51->setText(QString::number(bms_temp[50], 'g', 4));
    ui->temp_bar_52->setText(QString::number(bms_temp[51], 'g', 4));
    ui->temp_bar_53->setText(QString::number(bms_temp[52], 'g', 4));
    ui->temp_bar_54->setText(QString::number(bms_temp[53], 'g', 4));
    ui->temp_bar_55->setText(QString::number(bms_temp[54], 'g', 4));
    ui->temp_bar_56->setText(QString::number(bms_temp[55], 'g', 4));
    ui->temp_bar_57->setText(QString::number(bms_temp[56], 'g', 4));
    ui->temp_bar_58->setText(QString::number(bms_temp[57], 'g', 4));
    ui->temp_bar_59->setText(QString::number(bms_temp[58], 'g', 4));
    ui->temp_bar_60->setText(QString::number(bms_temp[59], 'g', 4));

    //Volt Bars

    ui->label_Volt_01->setText(QString::number(bms_volt[0], 'g', 4));
    ui->label_Volt_02->setText(QString::number(bms_volt[1], 'g', 4));
    ui->label_Volt_03->setText(QString::number(bms_volt[2], 'g', 4));
    ui->label_Volt_04->setText(QString::number(bms_volt[3], 'g', 4));
    ui->label_Volt_05->setText(QString::number(bms_volt[4], 'g', 4));
    ui->label_Volt_06->setText(QString::number(bms_volt[5], 'g', 4));
    ui->label_Volt_07->setText(QString::number(bms_volt[6], 'g', 4));
    ui->label_Volt_08->setText(QString::number(bms_volt[7], 'g', 4));
    ui->label_Volt_09->setText(QString::number(bms_volt[8], 'g', 4));
    ui->label_Volt_10->setText(QString::number(bms_volt[9], 'g', 4));

    ui->label_Volt_11->setText(QString::number(bms_volt[10], 'g', 4));
    ui->label_Volt_12->setText(QString::number(bms_volt[11], 'g', 4));
    ui->label_Volt_13->setText(QString::number(bms_volt[12], 'g', 4));
    ui->label_Volt_14->setText(QString::number(bms_volt[13], 'g', 4));
    ui->label_Volt_15->setText(QString::number(bms_volt[14], 'g', 4));
    ui->label_Volt_16->setText(QString::number(bms_volt[15], 'g', 4));
    ui->label_Volt_17->setText(QString::number(bms_volt[16], 'g', 4));
    ui->label_Volt_18->setText(QString::number(bms_volt[17], 'g', 4));
    ui->label_Volt_19->setText(QString::number(bms_volt[18], 'g', 4));
    ui->label_Volt_20->setText(QString::number(bms_volt[19], 'g', 4));

    ui->label_Volt_21->setText(QString::number(bms_volt[20], 'g', 4));
    ui->label_Volt_22->setText(QString::number(bms_volt[21], 'g', 4));
    ui->label_Volt_23->setText(QString::number(bms_volt[22], 'g', 4));
    ui->label_Volt_24->setText(QString::number(bms_volt[23], 'g', 4));
    ui->label_Volt_25->setText(QString::number(bms_volt[24], 'g', 4));
    ui->label_Volt_26->setText(QString::number(bms_volt[25], 'g', 4));
    ui->label_Volt_27->setText(QString::number(bms_volt[26], 'g', 4));
    ui->label_Volt_28->setText(QString::number(bms_volt[27], 'g', 4));
    ui->label_Volt_29->setText(QString::number(bms_volt[28], 'g', 4));
    ui->label_Volt_30->setText(QString::number(bms_volt[29], 'g', 4));

//STYLESHEET

    //SOC BAR
    ui->SoC_bar->setStyleSheet(Dialog::barSoCStyle(carga_restante));

    //Temp bars
    ui->temp_bar_01->setStyleSheet(Dialog::barTempStyle(bms_temp[0]));
    ui->temp_bar_02->setStyleSheet(Dialog::barTempStyle1(bms_temp[1]));
    ui->temp_bar_03->setStyleSheet(Dialog::barTempStyle(bms_temp[2]));
    ui->temp_bar_04->setStyleSheet(Dialog::barTempStyle1(bms_temp[3]));
    ui->temp_bar_05->setStyleSheet(Dialog::barTempStyle(bms_temp[4]));
    ui->temp_bar_06->setStyleSheet(Dialog::barTempStyle1(bms_temp[5]));
    ui->temp_bar_07->setStyleSheet(Dialog::barTempStyle(bms_temp[6]));
    ui->temp_bar_08->setStyleSheet(Dialog::barTempStyle1(bms_temp[7]));
    ui->temp_bar_09->setStyleSheet(Dialog::barTempStyle(bms_temp[8]));
    ui->temp_bar_10->setStyleSheet(Dialog::barTempStyle1(bms_temp[9]));
    ui->temp_bar_11->setStyleSheet(Dialog::barTempStyle(bms_temp[10]));
    ui->temp_bar_12->setStyleSheet(Dialog::barTempStyle1(bms_temp[11]));
    ui->temp_bar_13->setStyleSheet(Dialog::barTempStyle(bms_temp[12]));
    ui->temp_bar_14->setStyleSheet(Dialog::barTempStyle1(bms_temp[13]));
    ui->temp_bar_15->setStyleSheet(Dialog::barTempStyle(bms_temp[14]));
    ui->temp_bar_16->setStyleSheet(Dialog::barTempStyle1(bms_temp[15]));
    ui->temp_bar_17->setStyleSheet(Dialog::barTempStyle(bms_temp[16]));
    ui->temp_bar_18->setStyleSheet(Dialog::barTempStyle1(bms_temp[17]));
    ui->temp_bar_19->setStyleSheet(Dialog::barTempStyle(bms_temp[18]));
    ui->temp_bar_20->setStyleSheet(Dialog::barTempStyle1(bms_temp[19]));
    ui->temp_bar_21->setStyleSheet(Dialog::barTempStyle(bms_temp[20]));
    ui->temp_bar_22->setStyleSheet(Dialog::barTempStyle1(bms_temp[21]));
    ui->temp_bar_23->setStyleSheet(Dialog::barTempStyle(bms_temp[22]));
    ui->temp_bar_24->setStyleSheet(Dialog::barTempStyle1(bms_temp[23]));
    ui->temp_bar_25->setStyleSheet(Dialog::barTempStyle(bms_temp[24]));
    ui->temp_bar_26->setStyleSheet(Dialog::barTempStyle1(bms_temp[25]));
    ui->temp_bar_27->setStyleSheet(Dialog::barTempStyle(bms_temp[26]));
    ui->temp_bar_28->setStyleSheet(Dialog::barTempStyle1(bms_temp[27]));
    ui->temp_bar_29->setStyleSheet(Dialog::barTempStyle(bms_temp[28]));
    ui->temp_bar_30->setStyleSheet(Dialog::barTempStyle1(bms_temp[29]));
    ui->temp_bar_31->setStyleSheet(Dialog::barTempStyle(bms_temp[30]));
    ui->temp_bar_32->setStyleSheet(Dialog::barTempStyle1(bms_temp[31]));
    ui->temp_bar_33->setStyleSheet(Dialog::barTempStyle(bms_temp[32]));
    ui->temp_bar_34->setStyleSheet(Dialog::barTempStyle1(bms_temp[33]));
    ui->temp_bar_35->setStyleSheet(Dialog::barTempStyle(bms_temp[34]));
    ui->temp_bar_36->setStyleSheet(Dialog::barTempStyle1(bms_temp[35]));
    ui->temp_bar_37->setStyleSheet(Dialog::barTempStyle(bms_temp[36]));
    ui->temp_bar_38->setStyleSheet(Dialog::barTempStyle1(bms_temp[37]));
    ui->temp_bar_39->setStyleSheet(Dialog::barTempStyle(bms_temp[38]));
    ui->temp_bar_40->setStyleSheet(Dialog::barTempStyle1(bms_temp[39]));
    ui->temp_bar_41->setStyleSheet(Dialog::barTempStyle(bms_temp[40]));
    ui->temp_bar_42->setStyleSheet(Dialog::barTempStyle1(bms_temp[41]));
    ui->temp_bar_43->setStyleSheet(Dialog::barTempStyle(bms_temp[42]));
    ui->temp_bar_44->setStyleSheet(Dialog::barTempStyle1(bms_temp[43]));
    ui->temp_bar_45->setStyleSheet(Dialog::barTempStyle(bms_temp[44]));
    ui->temp_bar_46->setStyleSheet(Dialog::barTempStyle1(bms_temp[45]));
    ui->temp_bar_47->setStyleSheet(Dialog::barTempStyle(bms_temp[46]));
    ui->temp_bar_48->setStyleSheet(Dialog::barTempStyle1(bms_temp[47]));
    ui->temp_bar_49->setStyleSheet(Dialog::barTempStyle(bms_temp[48]));
    ui->temp_bar_50->setStyleSheet(Dialog::barTempStyle1(bms_temp[49]));
    ui->temp_bar_51->setStyleSheet(Dialog::barTempStyle(bms_temp[50]));
    ui->temp_bar_52->setStyleSheet(Dialog::barTempStyle1(bms_temp[51]));
    ui->temp_bar_53->setStyleSheet(Dialog::barTempStyle(bms_temp[52]));
    ui->temp_bar_54->setStyleSheet(Dialog::barTempStyle1(bms_temp[53]));
    ui->temp_bar_55->setStyleSheet(Dialog::barTempStyle(bms_temp[54]));
    ui->temp_bar_56->setStyleSheet(Dialog::barTempStyle1(bms_temp[55]));
    ui->temp_bar_57->setStyleSheet(Dialog::barTempStyle(bms_temp[56]));
    ui->temp_bar_58->setStyleSheet(Dialog::barTempStyle1(bms_temp[57]));
    ui->temp_bar_59->setStyleSheet(Dialog::barTempStyle(bms_temp[58]));
    ui->temp_bar_60->setStyleSheet(Dialog::barTempStyle1(bms_temp[59]));

    //Volt bars
    ui->label_Volt_01->setStyleSheet(Dialog::barVoltStyle(bms_volt[0]));
    ui->label_Volt_02->setStyleSheet(Dialog::barVoltStyle(bms_volt[1]));
    ui->label_Volt_03->setStyleSheet(Dialog::barVoltStyle(bms_volt[2]));
    ui->label_Volt_04->setStyleSheet(Dialog::barVoltStyle(bms_volt[3]));
    ui->label_Volt_05->setStyleSheet(Dialog::barVoltStyle(bms_volt[4]));
    ui->label_Volt_06->setStyleSheet(Dialog::barVoltStyle(bms_volt[5]));
    ui->label_Volt_07->setStyleSheet(Dialog::barVoltStyle(bms_volt[6]));
    ui->label_Volt_08->setStyleSheet(Dialog::barVoltStyle(bms_volt[7]));
    ui->label_Volt_09->setStyleSheet(Dialog::barVoltStyle(bms_volt[8]));
    ui->label_Volt_10->setStyleSheet(Dialog::barVoltStyle(bms_volt[9]));
    ui->label_Volt_11->setStyleSheet(Dialog::barVoltStyle(bms_volt[10]));
    ui->label_Volt_12->setStyleSheet(Dialog::barVoltStyle(bms_volt[11]));
    ui->label_Volt_13->setStyleSheet(Dialog::barVoltStyle(bms_volt[12]));
    ui->label_Volt_14->setStyleSheet(Dialog::barVoltStyle(bms_volt[13]));
    ui->label_Volt_15->setStyleSheet(Dialog::barVoltStyle(bms_volt[14]));
    ui->label_Volt_16->setStyleSheet(Dialog::barVoltStyle(bms_volt[15]));
    ui->label_Volt_17->setStyleSheet(Dialog::barVoltStyle(bms_volt[16]));
    ui->label_Volt_18->setStyleSheet(Dialog::barVoltStyle(bms_volt[17]));
    ui->label_Volt_19->setStyleSheet(Dialog::barVoltStyle(bms_volt[18]));
    ui->label_Volt_20->setStyleSheet(Dialog::barVoltStyle(bms_volt[19]));
    ui->label_Volt_21->setStyleSheet(Dialog::barVoltStyle(bms_volt[20]));
    ui->label_Volt_22->setStyleSheet(Dialog::barVoltStyle(bms_volt[21]));
    ui->label_Volt_23->setStyleSheet(Dialog::barVoltStyle(bms_volt[22]));
    ui->label_Volt_24->setStyleSheet(Dialog::barVoltStyle(bms_volt[23]));
    ui->label_Volt_25->setStyleSheet(Dialog::barVoltStyle(bms_volt[24]));
    ui->label_Volt_26->setStyleSheet(Dialog::barVoltStyle(bms_volt[25]));
    ui->label_Volt_27->setStyleSheet(Dialog::barVoltStyle(bms_volt[26]));
    ui->label_Volt_28->setStyleSheet(Dialog::barVoltStyle(bms_volt[27]));
    ui->label_Volt_29->setStyleSheet(Dialog::barVoltStyle(bms_volt[28]));
    ui->label_Volt_30->setStyleSheet(Dialog::barVoltStyle(bms_volt[29]));
}
void Dialog::SetupSpeedometer(){

    mSpeedGauge = new QcGaugeWidget;
    mSpeedGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::gray);
    bkg2->addColor(1.0,Qt::darkGray);

    mSpeedGauge->addArc(55);
    mSpeedGauge->addDegrees(65)->setValueRange(0,150);
    mSpeedGauge->addColorBand(50);

    mSpeedGauge->addValues(80)->setValueRange(0,150);

    mSpeedGauge->addLabel(70)->setText("Km/h");
    QcLabelItem *lab = mSpeedGauge->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0,150);
    mSpeedGauge->addBackground(7);
    mSpeedGauge->addGlass(88);
    ui->layout_velocimetro->addWidget(mSpeedGauge);

}
void Dialog::SetupArduino(){

    // Identify the port the arduino uno is on.

        bool arduino_is_available = false;
        QString arduino_uno_port_name;

        //  For each available serial port
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            //  check if the serialport has both a product identifier and a vendor identifier
            if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                //  check if the product ID and the vendor ID match those of the arduino uno
                if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                        && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                    arduino_is_available = true; //    arduino uno is available on this port
                    arduino_uno_port_name = serialPortInfo.portName();
                }
            }
        }

    // Open and configure the arduino port if available

        if(arduino_is_available){
            qDebug() << "Found the arduino port...\n";
            arduino->setPortName(arduino_uno_port_name);
            arduino->open(QSerialPort::ReadOnly);
            arduino->setBaudRate(QSerialPort::Baud115200);
            arduino->setDataBits(QSerialPort::Data8);
            arduino->setFlowControl(QSerialPort::NoFlowControl);
            arduino->setParity(QSerialPort::NoParity);
            arduino->setStopBits(QSerialPort::OneStop);
            QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
        }else{
            qDebug() << "Couldn't find the correct port for the arduino.\n";
            QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
        }

}
void Dialog::GetProductVendorID(){

//  Testing code, prints the description, vendor id, and product id of all ports.
//  Used it to determine the values for the arduino uno

        qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }
}
void Dialog::calcularvelocidad(double RPM11, double RPM22){
    speed = ((RPM11+RPM22)/2)*0.101410611;
}
void Dialog::ActualizarPotenciaKelly(double volt1, double volt2, double volt3, double amp1, double amp2, double amp3, double volt4, double volt5, double volt6, double amp4, double amp5, double amp6){
    potencia_fase1_d = volt1*amp1;
    potencia_fase2_d = volt2*amp2;
    potencia_fase3_d = volt3*amp3;

    potencia_fase1_i = volt4*amp4;
    potencia_fase2_i = volt5*amp5;
    potencia_fase3_i = volt6*amp6;

    potencia_total_kelly_d = potencia_fase1_d + potencia_fase2_d + potencia_fase3_d;
    potencia_total_kelly_i = potencia_fase1_i + potencia_fase2_i + potencia_fase3_i;

    potencia_total_kellys = potencia_total_kelly_d + potencia_total_kelly_i;
}
void Dialog::ActualizarPotenciaBMS(double volt, double amp){
    potencia_total_bms = volt*amp;
}
void Dialog::ActualizarPotenciaMPPT(double volt1, double amp1, double volt2, double amp2, double volt3, double amp3){
    potencia_mppt1 = volt1*amp1;
    potencia_mppt2 = volt2*amp2;
    potencia_mppt3 = volt3*amp3;

    potencia_total_mppts = potencia_mppt1 + potencia_mppt2 + potencia_mppt3;
}
