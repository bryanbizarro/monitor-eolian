#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QtGlobal>
#include <QChar>

//Display inicial, valores iniciales, detecta Arduino (no modificar), define parámetros Arduino//

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    qDebug() << "Iniciando interfaz" << endl;

    ui->lcd_mppt_1_iin->display("----");
    ui->lcd_mppt_2_iin->display("----");
    ui->lcd_mppt_1_uout->display("----");
    ui->lcd_mppt_2_uout->display("----");
    //ui->lcd_velocidad->display("----");
    //ui->lcd_torque->display("----");
    ui->lcd_gap->display("----");
    //ui->lcd_max_voltaje->display("----");
    //ui->lcd_min_voltaje->display("----");
    ui->lcd_max_speed->display("----");

    //Iniciar arrays con zeros
    memset(bms_temp, 0, sizeof(bms_temp));
    memset(bms_volt, 0, sizeof(bms_volt));
    memset(bms_amp, 0, sizeof(bms_amp));

    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";

//  Dialog::GetProductVendorID();
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
    if(buffer_split.length() <8 ){
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
            if (unDato.length()==2){
            Dialog::updateValues(unDato[0],unDato[1]);
            } else if (unDato.length()==3){
            Dialog::updateValues(unDato[0], unDato[2], unDato[1].toInt());
            }
        }
    }

}
void Dialog::updateValues(QString name, QString valor, int posicion){
<<<<<<< HEAD
    double value;

    QChar ch = valor.at(0).toLatin1();
    int chValue =  ch.toLatin1();


    try{
        value = (double)chValue;
    }
    catch(...){
        value = 0;
    }
=======

    if(double value = valor.toDouble()){
        qDebug() << value;
        qDebug() << posicion;
>>>>>>> parent of 5a6ae89... Add new variables
        parsed_data = QString::number(value, 'g', 4); // format precision of temperature_value to 4 digits or fewer

        if(name == "CURRENT"){
            qDebug() << "Corriente: " << posicion << ": " << valor;
            amperaje1 = value;
            ui->lcd_packAmp->display(parsed_data);
            //ui->lcd_mppt_1_iin->display(parsed_data);
            //ui->lcd_mppt_2_iin->display(parsed_data);

<<<<<<< HEAD
        } else if (name == "A") {
            //qDebug() << "PACK CURRENT:  " << posicion << ": " << valor;
=======
        } else if (name == "PACK_CURRENT") {
            qDebug() << "PACK CURRENT:  " << posicion << ": " << valor;
>>>>>>> parent of 5a6ae89... Add new variables
            ui->lcd_packAmp->display(parsed_data);


        } else if (name == "PACK_INST_VTG") {
            qDebug() << "PACK INST VOLTAGE:  " << posicion << ": " << valor;
            voltaje1 = value;
            ui->lcd_packVolt->display(parsed_data);


        } else if (name == "PACK_OPEN_VTG") {
            qDebug() << "PACK OPEN VOLTAGE:  " << posicion << ": " << valor;
            voltaje1 = value;
            ui->lcd_openVolt->display(parsed_data);

        } else if (name == "PACK_ABSCURRENT") {
            qDebug() << "PACK ABSOLUTE CURRENT:  " << posicion << ": " << valor;
            voltaje1 = value;
            ui->lcd_absCurrent->display(parsed_data);

        } else if (name == "MAXIM_PACK_VTG") {
            qDebug() << "MAXIMUM PACK VOLTAGE: " << posicion << ": " << valor;
            ui->lcd_maxPackVolt->display(parsed_data);
            //ui->lcd_max_voltaje->display(parsed_data);

        } else if (name == "MINIM_PACK_VTG") {
            qDebug() << "MINIMUM PACK VOLTAGE: " << posicion << ": " << valor;
            ui->lcd_minPackVolt->display(parsed_data);
            //ui->lcd_min_voltaje->display(parsed_data);

        } else if (name == "HIGH_TEMP") {
            qDebug() << "HIGH TEMPERATURE: " << posicion << ": " << valor;
            ui->lcd_highTemp->display(parsed_data);

        } else if (name == "LOW_TEMP"){
            qDebug() << "LOW TEMPERATURE: " << posicion << ": " << valor;
            ui->lcd_lowTemp->display(parsed_data);
            //carga_restante = value;

        } else if (name == "HIGH_TID"){
            qDebug() << "HIGH THERMISTOR ID: " << posicion << ": " << valor;
            ui->lcd_maxTermID->display(parsed_data);

        } else if (name == "LOW_TID"){
            qDebug() << "LOW THERMISTOR ID: " << posicion << ": " << valor;
            ui->lcd_lowTermID->display(parsed_data);

        } else if (name == "AVG_TEMP"){
            qDebug() << "AVERAGE TEMPERATURE: " << posicion << ": " << valor;
            ui->lcd_AvgTemp->display(parsed_data);

        } else if (name == "INT_TEMP"){
            qDebug() << "INTERNAL TEMPERATURE: " << posicion << ": " << valor;
            ui->lcd_internalTemperature->display(parsed_data);

//        } else if (name == "PACK_DCL"){
//            qDebug() << "PACK DCL [" << posicion << "]: " << valor;
//            //bms_temp[posicion-1] = valor.toDouble();
//            //ui->lcd_DCL->display(parsed_data);

//        } else if (name == "PACK_CCL"){
//            qDebug() << "PACK CCL [" << posicion << "]: " << valor;
//            //bms_amp[posicion-1] = valor.toDouble();
//            //ui->lcd_CCL->display(parsed_data);

//        } else if (name == "REL_STATE"){
//            qDebug() << "RELAY STATE [" << posicion << "]: " << valor;
//            //bms_volt[posicion-1] = valor.toDouble();
//            ui->lcd_relayState->display(parsed_data);

//        } else if (name == "PACK_SOC"){
//            qDebug() << "PACK SOC [" << posicion << "]: " << valor;
//            ui->lcd_packSOC->display(parsed_data);

//        } else if (name == "PACK_RES"){
//            qDebug() << "PACK RESISTANCE [" << posicion << "]: " << valor;
//            //ui->lcd_packResistance->display(parsed_data);

//        } else if (name == "PACK_AMPH"){
//            qDebug() << "PACK AMPHOURS [" << posicion << "]: " << valor;
//            ui->lcd_relayState->display(parsed_data);

        } else if (name == "CELL_INSTVTG"){
            qDebug() << "CELL INST VOLTAGE [" << posicion << "]: " << valor;
            bms_volt[posicion] = value*0.0001;

        } else if (name == "TEMP"){
            qDebug() << "TEMP[" << posicion << "]: " << valor;
            bms_temp[posicion] = value;
            ui->temp_bar_60->setValue(400);

        } else if (name == "I1_A"){
            qDebug() << "CORRIENTE A MOTOR 1: " << valor;
            ui->lcd_eng1_IA->display(parsed_data);

        } else if (name == "I1_B"){
            qDebug() << "CORRIENTE B MOTOR 1: " << valor;
            ui->lcd_eng1_IB->display(parsed_data);

        } else if (name == "I1_C"){
            qDebug() << "CORRIENTE C MOTOR 1: " << valor;
            ui->lcd_eng1_IC->display(parsed_data);

        } else if (name == "I2_A"){
            qDebug() << "CORRIENTE A MOTOR 2: " << valor;
            ui->lcd_eng2_IA->display(parsed_data);

        } else if (name == "I2_B"){
            qDebug() << "CORRIENTE B MOTOR 2: " << valor;
            ui->lcd_eng2_IB->display(parsed_data);

        } else if (name == "I2_C"){
            qDebug() << "CORRIENTE C MOTOR 2: " << valor;
            ui->lcd_eng2_IC->display(parsed_data);

        } else if (name == "ENGA"){
            qDebug() << "RPM MOTOR 1: " << valor;
            value = value*538*108/1000;
            parsed_data = QString::number(value, 'g', 4);
            ui->lcd_velocidad->display(parsed_data);

        } else if (name == "ENGB"){
            qDebug() << "RPM MOTOR 2: " << valor;
            value = value*538*108/1000;
            parsed_data = QString::number(value, 'g', 4);
            ui->lcd_velocidad->display(parsed_data);

        } else if (name == "ENG1_TEMP"){
            qDebug() << "TEMP MOTOR 1: " << valor;
            ui->lcd_eng1Temp->display(parsed_data);

        } else if (name == "ENG2_TEMP"){
            qDebug() << "TEMP MOTOR 2: " << valor;
            ui->lcd_eng2Temp->display(parsed_data);

        } else if (name == "MPPT1_UIN"){
            qDebug() << "MPPT 1 UIN: " << valor;
            ui->lcd_mppt_1_uin->display(parsed_data);

        } else if (name == "MPPT1_IIN"){
            qDebug() << "MPPT 1 ININ: " << valor;
            amperaje1 = value;
            ui->lcd_mppt_1_iin->display(parsed_data);

        } else if (name == "MPPT1_UOUT"){
            qDebug() << "MPPT 1 UOUT: " << valor;
            ui->lcd_mppt_1_uout->display(parsed_data);

        } else if (name == "MPPT2_UIN"){
            qDebug() << "MPPT 2 UIN: " << valor;
            ui->lcd_mppt_2_uin->display(parsed_data);

        } else if (name == "MPPT2_IIN"){
            qDebug() << "MPPT 2 ININ: " << valor;
            amperaje2 = value;
            ui->lcd_mppt_2_iin->display(parsed_data);

        } else if (name == "MPPT2_UOUT"){
            qDebug() << "MPPT 2 UOUT: " << valor;
            ui->lcd_mppt_2_uout->display(parsed_data);

        } else {
            qDebug() << "SERIAL READ ERROR";

        }
    }

    Dialog::makeplot();
    mSpeedNeedle->setCurrentValue(speed);
    Dialog::maximavelocidad();
    maxvelaux = maxvel;
    SetupProgressbars();
    ui->lcd_max_speed->display(maxvelaux);

}
void Dialog::makeplot()
{
    // calculate two new data points:
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;

    if (key-lastPointKey > 0.001) // at most add point every 10 ms
    {
        qDebug()<<"grafico:"<<amperaje1<<"\n";
      double value0 = amperaje1;
      double value1 = amperaje2;
      // add data to lines:
      ui->Plot1->graph(0)->addData(key, value0);
      ui->Plot1->graph(1)->addData(key, value1);
      // set data of dots:
      ui->Plot1->graph(2)->clearData();
      ui->Plot1->graph(2)->addData(key, value0);
      ui->Plot1->graph(3)->clearData();
      ui->Plot1->graph(3)->addData(key, value1);
      // remove data of lines that's outside visible range:
      ui->Plot1->graph(0)->removeDataBefore(key-14);
      ui->Plot1->graph(1)->removeDataBefore(key-14);
      // rescale value (vertical) axis to fit the current data:
      ui->Plot1->graph(0)->rescaleValueAxis();
      ui->Plot1->graph(1)->rescaleValueAxis(true);

      double value00 = voltaje1;
      double value11 = voltaje2;
      // add data to lines:
      ui->Plot2->graph(0)->addData(key, value00);
      ui->Plot2->graph(1)->addData(key, value11);
      // set data of dots:
      ui->Plot2->graph(2)->clearData();
      ui->Plot2->graph(2)->addData(key, value00);
      ui->Plot2->graph(3)->clearData();
      ui->Plot2->graph(3)->addData(key, value11);
      // remove data of lines that's outside visible range:
      ui->Plot2->graph(0)->removeDataBefore(key-14);
      ui->Plot2->graph(1)->removeDataBefore(key-14);
      // rescale value (vertical) axis to fit the current data:
      ui->Plot2->graph(0)->rescaleValueAxis();
      ui->Plot2->graph(1)->rescaleValueAxis(true);

      double value000 = speed;
//      double value1 = 0;
      // add data to lines:
      ui->Plot3->graph(0)->addData(key, value000);
//      ui->Plot3->graph(1)->addData(key, value1);
      // set data of dots:
      ui->Plot3->graph(2)->clearData();
      ui->Plot3->graph(2)->addData(key, value000);
//      ui->Plot3->graph(3)->clearData();
//      ui->Plot3->graph(3)->addData(key, value1);
      // remove data of lines that's outside visible range:
      ui->Plot3->graph(0)->removeDataBefore(key-14);
     // ui->Plot3->graph(1)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      ui->Plot3->graph(0)->rescaleValueAxis();
      ui->Plot3->graph(1)->rescaleValueAxis(true);

      double value0000 = torque1; //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
//      double value1 = 0; //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
      // add data to lines:
      ui->Plot4->graph(0)->addData(key, value0000);
//      ui->Plot4->graph(1)->addData(key, value1);
      // set data of dots:
      ui->Plot4->graph(2)->clearData();
      ui->Plot4->graph(2)->addData(key, value0000);
//      ui->Plot4->graph(3)->clearData();
//      ui->Plot4->graph(3)->addData(key, value1);
      // remove data of lines that's outside visible range:
      ui->Plot4->graph(0)->removeDataBefore(key-14);
     // ui->Plot4->graph(1)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      ui->Plot4->graph(0)->rescaleValueAxis();
      ui->Plot4->graph(1)->rescaleValueAxis(true);

      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->Plot1->xAxis->setRange(key+0.25, 14, Qt::AlignRight);
    ui->Plot1->yAxis->setRange(0,100);
    ui->Plot1->replot();

    ui->Plot2->xAxis->setRange(key+0.25, 14, Qt::AlignRight);
    ui->Plot2->yAxis->setRange(0,100);
    ui->Plot2->replot();

    ui->Plot3->xAxis->setRange(key+0.25, 14, Qt::AlignRight);
    ui->Plot3->yAxis->setRange(0,150);
    ui->Plot3->replot();

    ui->Plot4->xAxis->setRange(key+0.25, 14, Qt::AlignRight);
    ui->Plot4->yAxis->setRange(0,100);
    ui->Plot4->replot();

}
void Dialog::maximavelocidad(){
    double newspeed=speed;
    maxvel= qMax(maxvelaux,newspeed);

}
QString Dialog::barTempStyle(double value){
    if ((value >=10)&&(value <20)){
        return safe;
    } else if ((value >=20)&&(value <25)){
        return safe1;
    } else if ((value >=25)&&(value <30)){
        return danger;
    } else if ((value >=30)&&(value <=35)){
        return danger1;
    }
    return danger1;
}

QString Dialog::barAmpStyle(double value){
    if ((value >=0)&&(value <25)){
        return safe;
    } else if ((value >=25)&&(value <50)){
        return safe1;
    } else if ((value >=50)&&(value <75)){
        return danger;
    } else if ((value >=75)&&(value <=100)){
        return danger1;
    }
    return danger1;
}

QString Dialog::barVoltStyle(double value){
    if ((value < 3) || (value > 5)){
        return voltDangerStyle;
    } else if ((value < 3.7) || (value > 4.3)){
        return voltCautionStyle;
    } else {
        return voltSafeStyle;
    }
}

QString Dialog::barSoCStyle(double value){
    if ((value >=0)&&(value <25)){
     return danger111;
    }else if ((value >=25)&&(value <50)){
     return danger11;
    }else if ((value >=50)&&(value <75)){
     return safe111;
    }else if((value >=75)&&(value <=100)){
     return safe11;
    }
    return safe11;
}

void Dialog::SetupProgressbars(){

//Asociar valores

    // Soc Bar

    ui->SoC_bar->setValue(carga_restante);

    //Temp Bars

    ui->temp_bar_01->setValue(bms_temp[0]);
    ui->temp_bar_02->setValue(bms_temp[1]);
    ui->temp_bar_03->setValue(bms_temp[2]);
    ui->temp_bar_04->setValue(bms_temp[3]);
    ui->temp_bar_05->setValue(bms_temp[4]);
    ui->temp_bar_06->setValue(bms_temp[5]);
    ui->temp_bar_07->setValue(bms_temp[6]);
    ui->temp_bar_08->setValue(bms_temp[7]);
    ui->temp_bar_09->setValue(bms_temp[8]);
    ui->temp_bar_10->setValue(bms_temp[9]);

    ui->temp_bar_11->setValue(bms_temp[10]);
    ui->temp_bar_12->setValue(bms_temp[11]);
    ui->temp_bar_13->setValue(bms_temp[12]);
    ui->temp_bar_14->setValue(bms_temp[13]);
    ui->temp_bar_15->setValue(bms_temp[14]);
    ui->temp_bar_16->setValue(bms_temp[15]);
    ui->temp_bar_17->setValue(bms_temp[16]);
    ui->temp_bar_18->setValue(bms_temp[17]);
    ui->temp_bar_19->setValue(bms_temp[18]);
    ui->temp_bar_20->setValue(bms_temp[19]);

    ui->temp_bar_21->setValue(bms_temp[20]);
    ui->temp_bar_22->setValue(bms_temp[21]);
    ui->temp_bar_23->setValue(bms_temp[22]);
    ui->temp_bar_24->setValue(bms_temp[23]);
    ui->temp_bar_25->setValue(bms_temp[24]);
    ui->temp_bar_26->setValue(bms_temp[25]);
    ui->temp_bar_27->setValue(bms_temp[26]);
    ui->temp_bar_28->setValue(bms_temp[27]);
    ui->temp_bar_29->setValue(bms_temp[28]);
    ui->temp_bar_30->setValue(bms_temp[29]);

    ui->temp_bar_31->setValue(bms_temp[30]);
    ui->temp_bar_32->setValue(bms_temp[31]);
    ui->temp_bar_33->setValue(bms_temp[32]);
    ui->temp_bar_34->setValue(bms_temp[33]);
    ui->temp_bar_35->setValue(bms_temp[34]);
    ui->temp_bar_36->setValue(bms_temp[35]);
    ui->temp_bar_37->setValue(bms_temp[36]);
    ui->temp_bar_38->setValue(bms_temp[37]);
    ui->temp_bar_39->setValue(bms_temp[38]);
    ui->temp_bar_40->setValue(bms_temp[39]);

    ui->temp_bar_41->setValue(bms_temp[40]);
    ui->temp_bar_42->setValue(bms_temp[41]);
    ui->temp_bar_43->setValue(bms_temp[42]);
    ui->temp_bar_44->setValue(bms_temp[43]);
    ui->temp_bar_45->setValue(bms_temp[44]);
    ui->temp_bar_46->setValue(bms_temp[45]);
    ui->temp_bar_47->setValue(bms_temp[46]);
    ui->temp_bar_48->setValue(bms_temp[47]);
    ui->temp_bar_49->setValue(bms_temp[48]);
    ui->temp_bar_50->setValue(bms_temp[49]);

    ui->temp_bar_51->setValue(bms_temp[50]);
    ui->temp_bar_52->setValue(bms_temp[51]);
    ui->temp_bar_53->setValue(bms_temp[52]);
    ui->temp_bar_54->setValue(bms_temp[53]);
    ui->temp_bar_55->setValue(bms_temp[54]);
    ui->temp_bar_56->setValue(bms_temp[55]);
    ui->temp_bar_57->setValue(bms_temp[56]);
    ui->temp_bar_58->setValue(bms_temp[57]);
    ui->temp_bar_59->setValue(bms_temp[58]);
    ui->temp_bar_60->setValue(bms_temp[59]);

  //Amp Bars

    ui->amp_bar_1->setValue(bms_amp[0]);
    ui->amp_bar_2->setValue(bms_amp[1]);
    ui->amp_bar_3->setValue(bms_amp[2]);
    ui->amp_bar_4->setValue(bms_amp[3]);
    ui->amp_bar_5->setValue(bms_amp[4]);
    ui->amp_bar_6->setValue(bms_amp[5]);
    ui->amp_bar_7->setValue(bms_amp[6]);
    ui->amp_bar_8->setValue(bms_amp[7]);
    ui->amp_bar_9->setValue(bms_amp[8]);
    ui->amp_bar_10->setValue(bms_amp[9]);

    ui->amp_bar_11->setValue(bms_amp[10]);
    ui->amp_bar_12->setValue(bms_amp[11]);
    ui->amp_bar_13->setValue(bms_amp[12]);
    ui->amp_bar_14->setValue(bms_amp[13]);
    ui->amp_bar_15->setValue(bms_amp[14]);
    ui->amp_bar_16->setValue(bms_amp[15]);
    ui->amp_bar_17->setValue(bms_amp[16]);
    ui->amp_bar_18->setValue(bms_amp[17]);
    ui->amp_bar_19->setValue(bms_amp[18]);
    ui->amp_bar_20->setValue(bms_amp[19]);

    ui->amp_bar_21->setValue(bms_amp[20]);
    ui->amp_bar_22->setValue(bms_amp[21]);
    ui->amp_bar_23->setValue(bms_amp[22]);
    ui->amp_bar_24->setValue(bms_amp[23]);
    ui->amp_bar_25->setValue(bms_amp[24]);
    ui->amp_bar_26->setValue(bms_amp[25]);
    ui->amp_bar_27->setValue(bms_amp[26]);
    ui->amp_bar_28->setValue(bms_amp[27]);
    ui->amp_bar_29->setValue(bms_amp[28]);
    ui->amp_bar_30->setValue(bms_amp[29]);

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

// Determinar estilos de las Progressbars, usando funciones

    //SoC bar

    ui->SoC_bar->setStyleSheet(Dialog::barSoCStyle(carga_restante));

    //Temp bars

    ui->temp_bar_01->setStyleSheet(Dialog::barTempStyle(bms_temp[0]));
    ui->temp_bar_02->setStyleSheet(Dialog::barTempStyle(bms_temp[1]));
    ui->temp_bar_03->setStyleSheet(Dialog::barTempStyle(bms_temp[2]));
    ui->temp_bar_04->setStyleSheet(Dialog::barTempStyle(bms_temp[3]));
    ui->temp_bar_05->setStyleSheet(Dialog::barTempStyle(bms_temp[4]));
    ui->temp_bar_06->setStyleSheet(Dialog::barTempStyle(bms_temp[5]));
    ui->temp_bar_07->setStyleSheet(Dialog::barTempStyle(bms_temp[6]));
    ui->temp_bar_08->setStyleSheet(Dialog::barTempStyle(bms_temp[7]));
    ui->temp_bar_09->setStyleSheet(Dialog::barTempStyle(bms_temp[8]));
    ui->temp_bar_10->setStyleSheet(Dialog::barTempStyle(bms_temp[9]));
    ui->temp_bar_11->setStyleSheet(Dialog::barTempStyle(bms_temp[10]));
    ui->temp_bar_12->setStyleSheet(Dialog::barTempStyle(bms_temp[11]));
    ui->temp_bar_13->setStyleSheet(Dialog::barTempStyle(bms_temp[12]));
    ui->temp_bar_14->setStyleSheet(Dialog::barTempStyle(bms_temp[13]));
    ui->temp_bar_15->setStyleSheet(Dialog::barTempStyle(bms_temp[14]));
    ui->temp_bar_16->setStyleSheet(Dialog::barTempStyle(bms_temp[15]));
    ui->temp_bar_17->setStyleSheet(Dialog::barTempStyle(bms_temp[16]));
    ui->temp_bar_18->setStyleSheet(Dialog::barTempStyle(bms_temp[17]));
    ui->temp_bar_19->setStyleSheet(Dialog::barTempStyle(bms_temp[18]));
    ui->temp_bar_20->setStyleSheet(Dialog::barTempStyle(bms_temp[19]));
    ui->temp_bar_21->setStyleSheet(Dialog::barTempStyle(bms_temp[20]));
    ui->temp_bar_22->setStyleSheet(Dialog::barTempStyle(bms_temp[21]));
    ui->temp_bar_23->setStyleSheet(Dialog::barTempStyle(bms_temp[22]));
    ui->temp_bar_24->setStyleSheet(Dialog::barTempStyle(bms_temp[23]));
    ui->temp_bar_25->setStyleSheet(Dialog::barTempStyle(bms_temp[24]));
    ui->temp_bar_26->setStyleSheet(Dialog::barTempStyle(bms_temp[25]));
    ui->temp_bar_27->setStyleSheet(Dialog::barTempStyle(bms_temp[26]));
    ui->temp_bar_28->setStyleSheet(Dialog::barTempStyle(bms_temp[27]));
    ui->temp_bar_29->setStyleSheet(Dialog::barTempStyle(bms_temp[28]));
    ui->temp_bar_30->setStyleSheet(Dialog::barTempStyle(bms_temp[29]));
    ui->temp_bar_31->setStyleSheet(Dialog::barTempStyle(bms_temp[30]));
    ui->temp_bar_32->setStyleSheet(Dialog::barTempStyle(bms_temp[31]));
    ui->temp_bar_33->setStyleSheet(Dialog::barTempStyle(bms_temp[32]));
    ui->temp_bar_34->setStyleSheet(Dialog::barTempStyle(bms_temp[33]));
    ui->temp_bar_35->setStyleSheet(Dialog::barTempStyle(bms_temp[34]));
    ui->temp_bar_36->setStyleSheet(Dialog::barTempStyle(bms_temp[35]));
    ui->temp_bar_37->setStyleSheet(Dialog::barTempStyle(bms_temp[36]));
    ui->temp_bar_38->setStyleSheet(Dialog::barTempStyle(bms_temp[37]));
    ui->temp_bar_39->setStyleSheet(Dialog::barTempStyle(bms_temp[38]));
    ui->temp_bar_40->setStyleSheet(Dialog::barTempStyle(bms_temp[39]));
    ui->temp_bar_41->setStyleSheet(Dialog::barTempStyle(bms_temp[40]));
    ui->temp_bar_42->setStyleSheet(Dialog::barTempStyle(bms_temp[41]));
    ui->temp_bar_43->setStyleSheet(Dialog::barTempStyle(bms_temp[42]));
    ui->temp_bar_44->setStyleSheet(Dialog::barTempStyle(bms_temp[43]));
    ui->temp_bar_45->setStyleSheet(Dialog::barTempStyle(bms_temp[44]));
    ui->temp_bar_46->setStyleSheet(Dialog::barTempStyle(bms_temp[45]));
    ui->temp_bar_47->setStyleSheet(Dialog::barTempStyle(bms_temp[46]));
    ui->temp_bar_48->setStyleSheet(Dialog::barTempStyle(bms_temp[47]));
    ui->temp_bar_49->setStyleSheet(Dialog::barTempStyle(bms_temp[48]));
    ui->temp_bar_50->setStyleSheet(Dialog::barTempStyle(bms_temp[49]));
    ui->temp_bar_51->setStyleSheet(Dialog::barTempStyle(bms_temp[50]));
    ui->temp_bar_52->setStyleSheet(Dialog::barTempStyle(bms_temp[51]));
    ui->temp_bar_53->setStyleSheet(Dialog::barTempStyle(bms_temp[52]));
    ui->temp_bar_54->setStyleSheet(Dialog::barTempStyle(bms_temp[53]));
    ui->temp_bar_55->setStyleSheet(Dialog::barTempStyle(bms_temp[54]));
    ui->temp_bar_56->setStyleSheet(Dialog::barTempStyle(bms_temp[55]));
    ui->temp_bar_57->setStyleSheet(Dialog::barTempStyle(bms_temp[56]));
    ui->temp_bar_58->setStyleSheet(Dialog::barTempStyle(bms_temp[57]));
    ui->temp_bar_59->setStyleSheet(Dialog::barTempStyle(bms_temp[58]));
    ui->temp_bar_60->setStyleSheet(Dialog::barTempStyle(bms_temp[59]));


    //Amp bars

    ui->amp_bar_1->setStyleSheet(Dialog::barAmpStyle(bms_amp[0]));
    ui->amp_bar_2->setStyleSheet(Dialog::barAmpStyle(bms_amp[1]));
    ui->amp_bar_3->setStyleSheet(Dialog::barAmpStyle(bms_amp[2]));
    ui->amp_bar_4->setStyleSheet(Dialog::barAmpStyle(bms_amp[3]));
    ui->amp_bar_5->setStyleSheet(Dialog::barAmpStyle(bms_amp[4]));
    ui->amp_bar_6->setStyleSheet(Dialog::barAmpStyle(bms_amp[5]));
    ui->amp_bar_7->setStyleSheet(Dialog::barAmpStyle(bms_amp[6]));
    ui->amp_bar_8->setStyleSheet(Dialog::barAmpStyle(bms_amp[7]));
    ui->amp_bar_9->setStyleSheet(Dialog::barAmpStyle(bms_amp[8]));
    ui->amp_bar_10->setStyleSheet(Dialog::barAmpStyle(bms_amp[9]));
    ui->amp_bar_11->setStyleSheet(Dialog::barAmpStyle(bms_amp[10]));
    ui->amp_bar_12->setStyleSheet(Dialog::barAmpStyle(bms_amp[11]));
    ui->amp_bar_13->setStyleSheet(Dialog::barAmpStyle(bms_amp[12]));
    ui->amp_bar_14->setStyleSheet(Dialog::barAmpStyle(bms_amp[13]));
    ui->amp_bar_15->setStyleSheet(Dialog::barAmpStyle(bms_amp[14]));
    ui->amp_bar_16->setStyleSheet(Dialog::barAmpStyle(bms_amp[15]));
    ui->amp_bar_17->setStyleSheet(Dialog::barAmpStyle(bms_amp[16]));
    ui->amp_bar_18->setStyleSheet(Dialog::barAmpStyle(bms_amp[17]));
    ui->amp_bar_19->setStyleSheet(Dialog::barAmpStyle(bms_amp[18]));
    ui->amp_bar_20->setStyleSheet(Dialog::barAmpStyle(bms_amp[19]));
    ui->amp_bar_21->setStyleSheet(Dialog::barAmpStyle(bms_amp[20]));
    ui->amp_bar_22->setStyleSheet(Dialog::barAmpStyle(bms_amp[21]));
    ui->amp_bar_23->setStyleSheet(Dialog::barAmpStyle(bms_amp[22]));
    ui->amp_bar_24->setStyleSheet(Dialog::barAmpStyle(bms_amp[23]));
    ui->amp_bar_25->setStyleSheet(Dialog::barAmpStyle(bms_amp[24]));
    ui->amp_bar_26->setStyleSheet(Dialog::barAmpStyle(bms_amp[25]));
    ui->amp_bar_27->setStyleSheet(Dialog::barAmpStyle(bms_amp[26]));
    ui->amp_bar_28->setStyleSheet(Dialog::barAmpStyle(bms_amp[27]));
    ui->amp_bar_29->setStyleSheet(Dialog::barAmpStyle(bms_amp[28]));
    ui->amp_bar_30->setStyleSheet(Dialog::barAmpStyle(bms_amp[29]));

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

void Dialog::SetupPlots(){

    /*
     *
     * Plot1: Amperajes
     * Plot2: Voltajes
     * Plot3: Velocidad
     * Plot4: Torque
    */

    ui->Plot1->addGraph(); // blue line
    ui->Plot1->graph(0)->setPen(QPen(Qt::blue));
    ui->Plot1->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->Plot1->graph(0)->setAntialiasedFill(false);
    ui->Plot1->addGraph(); // red line
    ui->Plot1->graph(1)->setPen(QPen(Qt::red));
    ui->Plot1->graph(0)->setChannelFillGraph(ui->Plot1->graph(1));

    ui->Plot1->addGraph(); // blue dot
    ui->Plot1->graph(2)->setPen(QPen(Qt::blue));
    ui->Plot1->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->Plot1->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->Plot1->addGraph(); // red dot
    ui->Plot1->graph(3)->setPen(QPen(Qt::red));
    ui->Plot1->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->Plot1->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot1->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->Plot1->xAxis->setDateTimeFormat("mm:ss");
    ui->Plot1->xAxis->setAutoTickStep(false);
    ui->Plot1->xAxis->setTickStep(2);
    ui->Plot1->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Plot1->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot1->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Plot1->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot1->yAxis2, SLOT(setRange(QCPRange)));

    ui->Plot2->addGraph(); // blue line
    ui->Plot2->graph(0)->setPen(QPen(Qt::blue));
    ui->Plot2->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->Plot2->graph(0)->setAntialiasedFill(false);
    ui->Plot2->addGraph(); // red line
    ui->Plot2->graph(1)->setPen(QPen(Qt::red));
    ui->Plot2->graph(0)->setChannelFillGraph(ui->Plot2->graph(1));

    ui->Plot2->addGraph(); // blue dot
    ui->Plot2->graph(2)->setPen(QPen(Qt::blue));
    ui->Plot2->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->Plot2->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->Plot2->addGraph(); // red dot
    ui->Plot2->graph(3)->setPen(QPen(Qt::red));
    ui->Plot2->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->Plot2->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot2->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->Plot2->xAxis->setDateTimeFormat("mm:ss");
    ui->Plot2->xAxis->setAutoTickStep(false);
    ui->Plot2->xAxis->setTickStep(2);
    ui->Plot2->axisRect()->setupFullAxesBox();

    connect(ui->Plot2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Plot2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot2->yAxis2, SLOT(setRange(QCPRange)));


    ui->Plot3->addGraph(); // blue line
    ui->Plot3->graph(0)->setPen(QPen(Qt::blue));
    ui->Plot3->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->Plot3->graph(0)->setAntialiasedFill(false);
    ui->Plot3->addGraph(); // red line
    ui->Plot3->graph(1)->setPen(QPen(Qt::red));
    ui->Plot3->graph(0)->setChannelFillGraph(ui->Plot3->graph(1));

    ui->Plot3->addGraph(); // blue dot
    ui->Plot3->graph(2)->setPen(QPen(Qt::blue));
    ui->Plot3->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->Plot3->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->Plot3->addGraph(); // red dot
    ui->Plot3->graph(3)->setPen(QPen(Qt::red));
    ui->Plot3->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->Plot3->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot3->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->Plot3->xAxis->setDateTimeFormat("mm:ss");
    ui->Plot3->xAxis->setAutoTickStep(false);
    ui->Plot3->xAxis->setTickStep(2);
    ui->Plot3->axisRect()->setupFullAxesBox();

    connect(ui->Plot3->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot3->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Plot3->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot3->yAxis2, SLOT(setRange(QCPRange)));

    ui->Plot4->addGraph(); // blue line
    ui->Plot4->graph(0)->setPen(QPen(Qt::blue));
    ui->Plot4->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->Plot4->graph(0)->setAntialiasedFill(false);
    ui->Plot4->addGraph(); // red line
    ui->Plot4->graph(1)->setPen(QPen(Qt::red));
    ui->Plot4->graph(0)->setChannelFillGraph(ui->Plot4->graph(1));

    ui->Plot4->addGraph(); // blue dot
    ui->Plot4->graph(2)->setPen(QPen(Qt::blue));
    ui->Plot4->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->Plot4->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->Plot4->addGraph(); // red dot
    ui->Plot4->graph(3)->setPen(QPen(Qt::red));
    ui->Plot4->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->Plot4->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->Plot4->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->Plot4->xAxis->setDateTimeFormat("mm:ss");
    ui->Plot4->xAxis->setAutoTickStep(false);
    ui->Plot4->xAxis->setTickStep(2);
    ui->Plot4->axisRect()->setupFullAxesBox();

    connect(ui->Plot4->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot4->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Plot4->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Plot4->yAxis2, SLOT(setRange(QCPRange)));

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
            arduino->setBaudRate(QSerialPort::Baud57600);
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
